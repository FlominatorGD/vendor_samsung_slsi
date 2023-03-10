/*
 * Copyright (C) 2013 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 *  Manage the listen-mode routing table.
 */

#include <android-base/stringprintf.h>
#include <base/logging.h>
#include <nativehelper/JNIHelp.h>
#include <nativehelper/ScopedLocalRef.h>

#include "JavaClassConstants.h"
#include "RoutingManager.h"
#include "nfa_ce_api.h"
#include "nfa_ee_api.h"
#include "nfc_config.h"

using android::base::StringPrintf;

extern bool gActivated;
extern SyncEvent gDeactivatedEvent;
extern bool nfc_debug_enabled;

const JNINativeMethod RoutingManager::sMethods[] = {
    {"doGetDefaultRouteDestination", "()I",
     (void*)RoutingManager::
         com_android_nfc_cardemulation_doGetDefaultRouteDestination},
    {"doGetDefaultOffHostRouteDestination", "()I",
     (void*)RoutingManager::
         com_android_nfc_cardemulation_doGetDefaultOffHostRouteDestination},
    {"doGetOffHostUiccDestination", "()[B",
     (void*)RoutingManager::
         com_android_nfc_cardemulation_doGetOffHostUiccDestination},
    {"doGetOffHostEseDestination", "()[B",
     (void*)RoutingManager::
         com_android_nfc_cardemulation_doGetOffHostEseDestination},
    {"doGetAidMatchingMode", "()I",
     (void*)RoutingManager::com_android_nfc_cardemulation_doGetAidMatchingMode},
    {"doGetDefaultIsoDepRouteDestination", "()I",
     (void*)RoutingManager::
         com_android_nfc_cardemulation_doGetDefaultIsoDepRouteDestination}};

static const int MAX_NUM_EE = 5;
// SCBR from host works only when App is in foreground
static const uint8_t SYS_CODE_PWR_STATE_HOST = 0x01;
static const uint16_t DEFAULT_SYS_CODE = 0xFEFE;

static const uint8_t AID_ROUTE_QUAL_PREFIX = 0x10;

RoutingManager::RoutingManager() : mAidRoutingConfigured(false) {
  static const char fn[] = "RoutingManager::RoutingManager()";

  mDefaultOffHostRoute =
      NfcConfig::getUnsigned(NAME_DEFAULT_OFFHOST_ROUTE, 0x00);

  if (NfcConfig::hasKey(NAME_OFFHOST_ROUTE_UICC)) {
    mOffHostRouteUicc = NfcConfig::getBytes(NAME_OFFHOST_ROUTE_UICC);
    // VTS 1.2 failed fix
    if (NFC_GetNCIVersion() < NCI_VERSION_2_0) {
      for (uint8_t& routeUicc : mOffHostRouteUicc) {
        routeUicc &= 0x0F;
      }
    }
  }

  if (NfcConfig::hasKey(NAME_OFFHOST_ROUTE_ESE)) {
    mOffHostRouteEse = NfcConfig::getBytes(NAME_OFFHOST_ROUTE_ESE);
    // VTS 1.2 failed fix
    if (NFC_GetNCIVersion() < NCI_VERSION_2_0) {
      for (uint8_t& routeEse : mOffHostRouteEse) {
        routeEse &= 0x0F;
      }
    }
  }

  mDefaultFelicaRoute = NfcConfig::getUnsigned(NAME_DEFAULT_NFCF_ROUTE, 0x00);
  DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf(
      "%s: Active SE for Nfc-F is 0x%02X", fn, mDefaultFelicaRoute);

  mDefaultEe = NfcConfig::getUnsigned(NAME_DEFAULT_ROUTE, 0x00);
  DLOG_IF(INFO, nfc_debug_enabled)
      << StringPrintf("%s: default route is 0x%02X", fn, mDefaultEe);

  mAidMatchingMode =
      NfcConfig::getUnsigned(NAME_AID_MATCHING_MODE, AID_MATCHING_EXACT_ONLY);

  mDefaultSysCodeRoute =
      NfcConfig::getUnsigned(NAME_DEFAULT_SYS_CODE_ROUTE, 0xC0);

  mDefaultSysCodePowerstate =
      NfcConfig::getUnsigned(NAME_DEFAULT_SYS_CODE_PWR_STATE, 0x19);

  mDefaultSysCode = DEFAULT_SYS_CODE;
  if (NfcConfig::hasKey(NAME_DEFAULT_SYS_CODE)) {
    std::vector<uint8_t> pSysCode = NfcConfig::getBytes(NAME_DEFAULT_SYS_CODE);
    if (pSysCode.size() == 0x02) {
      mDefaultSysCode = ((pSysCode[0] << 8) | ((int)pSysCode[1] << 0));
      DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf(
          "%s: DEFAULT_SYS_CODE: 0x%02X", __func__, mDefaultSysCode);
    }
  }

  mOffHostAidRoutingPowerState =
      NfcConfig::getUnsigned(NAME_OFFHOST_AID_ROUTE_PWR_STATE, 0x01);

  mDefaultIsoDepRoute = NfcConfig::getUnsigned(NAME_DEFAULT_ISODEP_ROUTE, 0x0);
  // VTS 1.2 failed fix
  if (NFC_GetNCIVersion() < NCI_VERSION_2_0) {
    mDefaultIsoDepRoute &= 0x0F;
  }

  memset(&mEeInfo, 0, sizeof(mEeInfo));
  mReceivedEeInfo = false;
  mReceivedeSEEeInfo = false; // [SEC] for eSE
  mSeTechMask = 0x00;
  mIsScbrSupported = false;

  mNfcFOnDhHandle = NFA_HANDLE_INVALID;

  mDeinitializing = false;
  mEeInfoChanged = false;
}

RoutingManager::~RoutingManager() {}

bool RoutingManager::initialize(nfc_jni_native_data* native) {
  static const char fn[] = "RoutingManager::initialize()";
  mNativeData = native;
  mRxDataBuffer.clear();

  {
    SyncEventGuard guard(mEeRegisterEvent);
    DLOG_IF(INFO, nfc_debug_enabled) << fn << ": try ee register";
    tNFA_STATUS nfaStat = NFA_EeRegister(nfaEeCallback);
    if (nfaStat != NFA_STATUS_OK) {
      LOG(ERROR) << StringPrintf("%s: fail ee register; error=0x%X", fn,
                                 nfaStat);
      return false;
    }
    mEeRegisterEvent.wait();
  }

  if ((mDefaultOffHostRoute != 0) || (mDefaultFelicaRoute != 0)) {
    // Wait for EE info if needed
    SyncEventGuard guard(mEeInfoEvent);
    if (!mReceivedEeInfo) {
      LOG(INFO) << fn << "Waiting for EE info";
      mEeInfoEvent.wait();
    }
  }

  // [SEC] eSE activation
  if (!isEeActivated(mOffHostRouteEse[0])) {
      if (RoutingManager::getInstance().activateSecureElement() == NFA_STATUS_OK) {
          SyncEventGuard guard(meSeEeInfoEvent);
          if (!mReceivedeSEEeInfo) {
              LOG(INFO) << fn << "Waiting for eSE info";
              meSeEeInfoEvent.wait();
          }
      }
  }

  mSeTechMask = updateEeTechRouteSetting();

  // Tell the host-routing to only listen on Nfc-A
  tNFA_STATUS nfaStat = NFA_CeSetIsoDepListenTech(NFA_TECHNOLOGY_MASK_A | NFA_TECHNOLOGY_MASK_B); // [SEC] Add Listen Tech B
  if (nfaStat != NFA_STATUS_OK)
    LOG(ERROR) << StringPrintf("Failed to configure CE IsoDep technologies");

  // Register a wild-card for AIDs routed to the host
  nfaStat = NFA_CeRegisterAidOnDH(NULL, 0, stackCallback);
  if (nfaStat != NFA_STATUS_OK)
    LOG(ERROR) << fn << "Failed to register wildcard AID for DH";

  updateDefaultRoute();
  updateDefaultProtocolRoute();

  return true;
}

RoutingManager& RoutingManager::getInstance() {
  static RoutingManager manager;
  return manager;
}

void RoutingManager::enableRoutingToHost() {
  static const char fn[] = "RoutingManager::enableRoutingToHost()";
  tNFA_STATUS nfaStat;
  SyncEventGuard guard(mRoutingEvent);

  // [SEC] Disable duplicated set
  // Default routing for T3T protocol
  /* if (!mIsScbrSupported && activeSe == NFC_DH_ID) {
    nfaStat = NFA_EeClearDefaultProtoRouting(mOffHostRouteUicc[0], NFA_PROTOCOL_MASK_T3T); // [SEC] Route T3T
    nfaStat = NFA_EeSetDefaultProtoRouting(activeSe, NFA_PROTOCOL_MASK_T3T, 0,
                                           0, 0, 0, 0);
    if (nfaStat == NFA_STATUS_OK)
      mRoutingEvent.wait();
    else
      LOG(ERROR) << fn << "Fail to set default proto routing for T3T";
  } */

  // [SEC] Disable duplicated set
  // Default routing for IsoDep protocol
  /* tNFA_PROTOCOL_MASK protoMask = NFA_PROTOCOL_MASK_ISO_DEP;
  if (mDefaultIsoDepRoute == NFC_DH_ID || routeToActiveSe) { // [SEC] Set to DH if SE is not exists
    nfaStat = NFA_EeSetDefaultProtoRouting(
        activeSe, protoMask, 0, 0, mSecureNfcEnabled ? 0 : protoMask, 0, 0);
    if (nfaStat == NFA_STATUS_OK)
      mRoutingEvent.wait();
    else
      LOG(ERROR) << fn << "Fail to set default proto routing for IsoDep";
  } */

  // [SEC] Route for ISO-DEP tech
  int activeSe = getActiveSe(mDefaultIsoDepRoute);

  // [SEC] Enable listen tech for discovery
  tNFA_TECHNOLOGY_MASK techMask = NFA_TECHNOLOGY_MASK_A | NFA_TECHNOLOGY_MASK_B | NFA_TECHNOLOGY_MASK_F;
  nfaStat = NFA_CeConfigureUiccListenTech(activeSe, techMask);
  if (nfaStat != NFA_STATUS_OK)
    LOG(ERROR) << fn << "Failed to configure activeSe listen technologies.";

  // Route Nfc-A to host if we don't have a SE
  techMask = NFA_TECHNOLOGY_MASK_A;
  if ((mSeTechMask & NFA_TECHNOLOGY_MASK_A) == 0) {
    if (activeSe == NFC_DH_ID) {
      nfaStat = NFA_EeSetDefaultTechRouting(
        NFC_DH_ID, techMask, 0, 0, mSecureNfcEnabled ? 0 : techMask,
        mSecureNfcEnabled ? 0 : techMask, mSecureNfcEnabled ? 0 : techMask);
    } else {
      nfaStat = NFA_EeSetDefaultTechRouting(
        activeSe, techMask, techMask, 0, mSecureNfcEnabled ? 0 : techMask,
        mSecureNfcEnabled ? 0 : techMask, mSecureNfcEnabled ? 0 : techMask);
    }
    if (nfaStat == NFA_STATUS_OK)
      mRoutingEvent.wait();
    else
      LOG(ERROR) << fn << "Fail to set default tech routing for Nfc-A";
  }

  // [SEC] Route Nfc-B to host if we don't have a SE
  techMask = NFA_TECHNOLOGY_MASK_B;
  if ((mSeTechMask & NFA_TECHNOLOGY_MASK_B) == 0) {
    if (activeSe == NFC_DH_ID) {
      nfaStat = NFA_EeSetDefaultTechRouting(
        NFC_DH_ID, techMask, 0, 0, mSecureNfcEnabled ? 0 : techMask, 0, 0);
    } else {
      nfaStat = NFA_EeSetDefaultTechRouting(
        activeSe, techMask, techMask, 0, mSecureNfcEnabled ? 0 : techMask,
        mSecureNfcEnabled ? 0 : techMask, mSecureNfcEnabled ? 0 : techMask);
    }
    if (nfaStat == NFA_STATUS_OK)
      mRoutingEvent.wait();
    else
      LOG(ERROR) << fn << "Fail to set default tech routing for Nfc-F";
  }

  // [SEC] Route for tech F
  activeSe = getActiveSe(mDefaultFelicaRoute);

  // Route Nfc-F to host if we don't have a SE
  techMask = NFA_TECHNOLOGY_MASK_F;
  if ((mSeTechMask & NFA_TECHNOLOGY_MASK_F) == 0) {
    if (activeSe == NFC_DH_ID) {
      nfaStat = NFA_EeSetDefaultTechRouting(
        activeSe, techMask, 0, 0, mSecureNfcEnabled ? 0 : techMask,
        mSecureNfcEnabled ? 0 : techMask, mSecureNfcEnabled ? 0 : techMask);
    } else {
      nfaStat = NFA_EeSetDefaultTechRouting(
        activeSe, techMask, techMask, 0, mSecureNfcEnabled ? 0 : techMask,
        mSecureNfcEnabled ? 0 : techMask, mSecureNfcEnabled ? 0 : techMask);
    }
    if (nfaStat == NFA_STATUS_OK)
      mRoutingEvent.wait();
    else
      LOG(ERROR) << fn << "Fail to set default tech routing for Nfc-F";
  }
}

void RoutingManager::disableRoutingToHost() {
  static const char fn[] = "RoutingManager::disableRoutingToHost()";
  tNFA_STATUS nfaStat;
  SyncEventGuard guard(mRoutingEvent);

  // Default routing for IsoDep protocol
  // [SEC] if (mDefaultIsoDepRoute == NFC_DH_ID) {
    nfaStat =
        NFA_EeClearDefaultProtoRouting(mOffHostRouteUicc[0], NFA_PROTOCOL_MASK_ISO_DEP);
    nfaStat =
        NFA_EeClearDefaultProtoRouting(mOffHostRouteEse[0], NFA_PROTOCOL_MASK_ISO_DEP);
    nfaStat =
        NFA_EeClearDefaultProtoRouting(NFC_DH_ID, NFA_PROTOCOL_MASK_ISO_DEP);
    if (nfaStat == NFA_STATUS_OK)
      mRoutingEvent.wait();
    else
      LOG(ERROR) << fn << "Fail to set default proto routing for IsoDep";
  // [SEC] }

  // Default routing for Nfc-A technology if we don't have a SE
  // [SEC] if ((mSeTechMask & NFA_TECHNOLOGY_MASK_A) == 0) {
    nfaStat = NFA_EeClearDefaultTechRouting(mOffHostRouteUicc[0], NFA_TECHNOLOGY_MASK_A);
    nfaStat = NFA_EeClearDefaultTechRouting(mOffHostRouteEse[0], NFA_TECHNOLOGY_MASK_A);
    nfaStat = NFA_EeClearDefaultTechRouting(NFC_DH_ID, NFA_TECHNOLOGY_MASK_A);
    if (nfaStat == NFA_STATUS_OK)
      mRoutingEvent.wait();
    else
      LOG(ERROR) << fn << "Fail to set default tech routing for Nfc-A";
  // [SEC] }

  // [SEC] Default routing for Nfc-B technology if we don't have a SE
  // [SEC] if ((mSeTechMask & NFA_TECHNOLOGY_MASK_B) == 0) {
      nfaStat = NFA_EeClearDefaultTechRouting(mOffHostRouteUicc[0], NFA_TECHNOLOGY_MASK_B);
      nfaStat = NFA_EeClearDefaultTechRouting(mOffHostRouteEse[0], NFA_TECHNOLOGY_MASK_B);
      nfaStat = NFA_EeClearDefaultTechRouting(NFC_DH_ID, NFA_TECHNOLOGY_MASK_B);
      if (nfaStat == NFA_STATUS_OK)
          mRoutingEvent.wait();
      else
          LOG(ERROR) << fn << "Fail to set default tech routing for Nfc-A";
  // [SEC] }

  // Default routing for Nfc-F technology if we don't have a SE
  // [SEC] if ((mSeTechMask & NFA_TECHNOLOGY_MASK_F) == 0) {
    nfaStat = NFA_EeClearDefaultTechRouting(mOffHostRouteUicc[0], NFA_TECHNOLOGY_MASK_F);
    nfaStat = NFA_EeClearDefaultTechRouting(mOffHostRouteEse[0], NFA_TECHNOLOGY_MASK_F);
    nfaStat = NFA_EeClearDefaultTechRouting(NFC_DH_ID, NFA_TECHNOLOGY_MASK_F);
    if (nfaStat == NFA_STATUS_OK)
      mRoutingEvent.wait();
    else
      LOG(ERROR) << fn << "Fail to set default tech routing for Nfc-F";
  // [SEC] }

  // Default routing for T3T protocol
  // [SEC] if (!mIsScbrSupported && mDefaultEe == NFC_DH_ID) {
    nfaStat = NFA_EeClearDefaultProtoRouting(mOffHostRouteUicc[0], NFA_PROTOCOL_MASK_T3T);
    nfaStat = NFA_EeClearDefaultProtoRouting(mOffHostRouteEse[0], NFA_PROTOCOL_MASK_T3T);
    nfaStat = NFA_EeClearDefaultProtoRouting(NFC_DH_ID, NFA_PROTOCOL_MASK_T3T);
    if (nfaStat == NFA_STATUS_OK)
      mRoutingEvent.wait();
    else
      LOG(ERROR) << fn << "Fail to set default proto routing for T3T";
  // [SEC] }

  // [SEC] Default routing for Default AID protocol if we don't have a SE
  // [SEC] if (mDefaultEe == NFC_DH_ID) {
      nfaStat = NFA_EeClearDefaultProtoRouting(mOffHostRouteUicc[0], NFA_PROTOCOL_MASK_ISO7816);
      nfaStat = NFA_EeClearDefaultProtoRouting(mOffHostRouteEse[0], NFA_PROTOCOL_MASK_ISO7816);
      nfaStat = NFA_EeClearDefaultProtoRouting(NFC_DH_ID, NFA_PROTOCOL_MASK_ISO7816);
      if (nfaStat == NFA_STATUS_OK)
          mRoutingEvent.wait();
      else
          LOG(ERROR) << fn << "Fail to set default proto routing for AID";
  // [SEC] }
}

bool RoutingManager::addAidRouting(const uint8_t* aid, uint8_t aidLen,
                                   int route, int aidInfo) {
  static const char fn[] = "RoutingManager::addAidRouting";
  DLOG_IF(INFO, nfc_debug_enabled) << fn << ": enter";
  uint8_t powerState = 0x01;
  if (!mSecureNfcEnabled) {
    powerState = (route != 0x00) ? mOffHostAidRoutingPowerState : 0x31; // [SEC] Powerstate for DH
  }
  SyncEventGuard guard(mRoutingEvent);
  mAidRoutingConfigured = false;
  tNFA_STATUS nfaStat =
      NFA_EeAddAidRouting(route, aidLen, (uint8_t*)aid, powerState, aidInfo);
  if (nfaStat == NFA_STATUS_OK) {
    mRoutingEvent.wait();
  }
  if (mAidRoutingConfigured) {
    DLOG_IF(INFO, nfc_debug_enabled) << fn << ": routed AID";
    return true;
  } else {
    LOG(ERROR) << fn << ": failed to route AID";
    return false;
  }
}

bool RoutingManager::removeAidRouting(const uint8_t* aid, uint8_t aidLen) {
  static const char fn[] = "RoutingManager::removeAidRouting";
  DLOG_IF(INFO, nfc_debug_enabled) << fn << ": enter";
  SyncEventGuard guard(mRoutingEvent);
  mAidRoutingConfigured = false;
  tNFA_STATUS nfaStat = NFA_EeRemoveAidRouting(aidLen, (uint8_t*)aid);
  if (nfaStat == NFA_STATUS_OK) {
    mRoutingEvent.wait();
  }
  if (mAidRoutingConfigured) {
    DLOG_IF(INFO, nfc_debug_enabled) << fn << ": removed AID";
    return true;
  } else {
    LOG(ERROR) << fn << ": failed to remove AID";
    return false;
  }
}

bool RoutingManager::commitRouting() {
  static const char fn[] = "RoutingManager::commitRouting";
  tNFA_STATUS nfaStat = 0;
  DLOG_IF(INFO, nfc_debug_enabled) << fn;
  if(mEeInfoChanged) {
    mSeTechMask = updateEeTechRouteSetting();
    mEeInfoChanged = false;
  }
  {
    SyncEventGuard guard(mEeUpdateEvent);
    nfaStat = NFA_EeUpdateNow();
    if (nfaStat == NFA_STATUS_OK) {
      mEeUpdateEvent.wait();  // wait for NFA_EE_UPDATED_EVT
    }
  }
  return (nfaStat == NFA_STATUS_OK);
}

void RoutingManager::onNfccShutdown() {
  static const char fn[] = "RoutingManager:onNfccShutdown";
  if (mDefaultOffHostRoute == 0x00 && mDefaultFelicaRoute == 0x00) return;

  tNFA_STATUS nfaStat = NFA_STATUS_FAILED;
  uint8_t actualNumEe = MAX_NUM_EE;
  tNFA_EE_INFO eeInfo[MAX_NUM_EE];
  mDeinitializing = true;

  memset(&eeInfo, 0, sizeof(eeInfo));
  if ((nfaStat = NFA_EeGetInfo(&actualNumEe, eeInfo)) != NFA_STATUS_OK) {
    LOG(ERROR) << StringPrintf("%s: fail get info; error=0x%X", fn, nfaStat);
    return;
  }
  if (actualNumEe != 0) {
    for (uint8_t xx = 0; xx < actualNumEe; xx++) {
      bool bIsOffHostEEPresent =
          (NFC_GetNCIVersion() < NCI_VERSION_2_0)
              ? (eeInfo[xx].num_interface != 0)
              : (eeInfo[xx].ee_interface[0] !=
                 NCI_NFCEE_INTERFACE_HCI_ACCESS) &&
                    (eeInfo[xx].ee_status == NFA_EE_STATUS_ACTIVE);
      if (bIsOffHostEEPresent) {
        DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf(
            "%s: Handle: 0x%04x Change Status Active to Inactive", fn,
            eeInfo[xx].ee_handle);
        SyncEventGuard guard(mEeSetModeEvent);
        if ((nfaStat = NFA_EeModeSet(eeInfo[xx].ee_handle,
                                     NFA_EE_MD_DEACTIVATE)) == NFA_STATUS_OK) {
          mEeSetModeEvent.wait();  // wait for NFA_EE_MODE_SET_EVT
        } else {
          LOG(ERROR) << fn << "Failed to set EE inactive";
        }
      }
    }
  } else {
    DLOG_IF(INFO, nfc_debug_enabled) << fn << ": No active EEs found";
  }
}

void RoutingManager::notifyActivated(uint8_t technology) {
  JNIEnv* e = NULL;
  ScopedAttach attach(mNativeData->vm, &e);
  if (e == NULL) {
    LOG(ERROR) << "jni env is null";
    return;
  }

  e->CallVoidMethod(mNativeData->manager,
                    android::gCachedNfcManagerNotifyHostEmuActivated,
                    (int)technology);
  if (e->ExceptionCheck()) {
    e->ExceptionClear();
    LOG(ERROR) << "fail notify";
  }
}

void RoutingManager::notifyDeactivated(uint8_t technology) {
  mRxDataBuffer.clear();
  JNIEnv* e = NULL;
  ScopedAttach attach(mNativeData->vm, &e);
  if (e == NULL) {
    LOG(ERROR) << "jni env is null";
    return;
  }

  e->CallVoidMethod(mNativeData->manager,
                    android::gCachedNfcManagerNotifyHostEmuDeactivated,
                    (int)technology);
  if (e->ExceptionCheck()) {
    e->ExceptionClear();
    LOG(ERROR) << StringPrintf("fail notify");
  }
}

void RoutingManager::handleData(uint8_t technology, const uint8_t* data,
                                uint32_t dataLen, tNFA_STATUS status) {
  if (status == NFC_STATUS_CONTINUE) {
    if (dataLen > 0) {
      mRxDataBuffer.insert(mRxDataBuffer.end(), &data[0],
                           &data[dataLen]);  // append data; more to come
    }
    return;  // expect another NFA_CE_DATA_EVT to come
  } else if (status == NFA_STATUS_OK) {
    if (dataLen > 0) {
      mRxDataBuffer.insert(mRxDataBuffer.end(), &data[0],
                           &data[dataLen]);  // append data
    }
    // entire data packet has been received; no more NFA_CE_DATA_EVT
  } else if (status == NFA_STATUS_FAILED) {
    LOG(ERROR) << "RoutingManager::handleData: read data fail";
    goto TheEnd;
  }

  {
    JNIEnv* e = NULL;
    ScopedAttach attach(mNativeData->vm, &e);
    if (e == NULL) {
      LOG(ERROR) << "jni env is null";
      goto TheEnd;
    }

    ScopedLocalRef<jobject> dataJavaArray(
        e, e->NewByteArray(mRxDataBuffer.size()));
    if (dataJavaArray.get() == NULL) {
      LOG(ERROR) << "fail allocate array";
      goto TheEnd;
    }

    e->SetByteArrayRegion((jbyteArray)dataJavaArray.get(), 0,
                          mRxDataBuffer.size(), (jbyte*)(&mRxDataBuffer[0]));
    if (e->ExceptionCheck()) {
      e->ExceptionClear();
      LOG(ERROR) << "fail fill array";
      goto TheEnd;
    }

    e->CallVoidMethod(mNativeData->manager,
                      android::gCachedNfcManagerNotifyHostEmuData,
                      (int)technology, dataJavaArray.get());
    if (e->ExceptionCheck()) {
      e->ExceptionClear();
      LOG(ERROR) << "fail notify";
    }
  }
TheEnd:
  mRxDataBuffer.clear();
}

void RoutingManager::notifyEeUpdated() {
  JNIEnv* e = NULL;
  ScopedAttach attach(mNativeData->vm, &e);
  if (e == NULL) {
    LOG(ERROR) << "jni env is null";
    return;
  }

  e->CallVoidMethod(mNativeData->manager,
                    android::gCachedNfcManagerNotifyEeUpdated);
  if (e->ExceptionCheck()) {
    e->ExceptionClear();
    LOG(ERROR) << "fail notify";
  }
}

void RoutingManager::stackCallback(uint8_t event,
                                   tNFA_CONN_EVT_DATA* eventData) {
  static const char fn[] = "RoutingManager::stackCallback";
  DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf("%s: event=0x%X", fn, event);
  RoutingManager& routingManager = RoutingManager::getInstance();

  switch (event) {
    case NFA_CE_REGISTERED_EVT: {
      tNFA_CE_REGISTERED& ce_registered = eventData->ce_registered;
      DLOG_IF(INFO, nfc_debug_enabled)
          << StringPrintf("%s: NFA_CE_REGISTERED_EVT; status=0x%X; h=0x%X", fn,
                          ce_registered.status, ce_registered.handle);
    } break;

    case NFA_CE_DEREGISTERED_EVT: {
      tNFA_CE_DEREGISTERED& ce_deregistered = eventData->ce_deregistered;
      DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf(
          "%s: NFA_CE_DEREGISTERED_EVT; h=0x%X", fn, ce_deregistered.handle);
    } break;

    case NFA_CE_ACTIVATED_EVT: {
      routingManager.notifyActivated(NFA_TECHNOLOGY_MASK_A);
    } break;

    case NFA_DEACTIVATED_EVT:
    case NFA_CE_DEACTIVATED_EVT: {
      DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf(
          "%s: NFA_DEACTIVATED_EVT, NFA_CE_DEACTIVATED_EVT", fn);
      routingManager.notifyDeactivated(NFA_TECHNOLOGY_MASK_A);
      SyncEventGuard g(gDeactivatedEvent);
      gActivated = false;  // guard this variable from multi-threaded access
      gDeactivatedEvent.notifyOne();
    } break;

    case NFA_CE_DATA_EVT: {
      tNFA_CE_DATA& ce_data = eventData->ce_data;
      DLOG_IF(INFO, nfc_debug_enabled)
          << StringPrintf("%s: NFA_CE_DATA_EVT; stat=0x%X; h=0x%X; data len=%u",
                          fn, ce_data.status, ce_data.handle, ce_data.len);
      getInstance().handleData(NFA_TECHNOLOGY_MASK_A, ce_data.p_data,
                               ce_data.len, ce_data.status);
    } break;
  }
}

void RoutingManager::updateRoutingTable() {
  mSeTechMask = updateEeTechRouteSetting();
  updateDefaultProtocolRoute();
  updateDefaultRoute();
}

void RoutingManager::updateDefaultProtocolRoute() {
  static const char fn[] = "RoutingManager::updateDefaultProtocolRoute";

  int activeSe = getActiveSe(mDefaultIsoDepRoute);

  // Default Routing for ISO-DEP
  tNFA_PROTOCOL_MASK protoMask = NFA_PROTOCOL_MASK_ISO_DEP;
  tNFA_STATUS nfaStat;
  if (activeSe != NFC_DH_ID) {
    nfaStat = NFA_EeClearDefaultProtoRouting(activeSe, protoMask);
    nfaStat = NFA_EeSetDefaultProtoRouting(
        activeSe, protoMask, mSecureNfcEnabled ? 0 : protoMask, 0,
        mSecureNfcEnabled ? 0 : protoMask, mSecureNfcEnabled ? 0 : protoMask,
        mSecureNfcEnabled ? 0 : protoMask);
  } else {
    nfaStat = NFA_EeClearDefaultProtoRouting(NFC_DH_ID, protoMask);
    nfaStat = NFA_EeSetDefaultProtoRouting(
        NFC_DH_ID, protoMask, 0, 0, mSecureNfcEnabled ? 0 : protoMask, 0, 0);
  }
  if (nfaStat == NFA_STATUS_OK)
    DLOG_IF(INFO, nfc_debug_enabled)
        << fn << ": Succeed to register default ISO-DEP route";
  else
    LOG(ERROR) << fn << ": failed to register default ISO-DEP route";

  activeSe = getActiveSe(mDefaultEe);
  // Default routing for T3T protocol
  if (!mIsScbrSupported) {
    SyncEventGuard guard(mRoutingEvent);
    tNFA_PROTOCOL_MASK protoMask = NFA_PROTOCOL_MASK_T3T;
    if (activeSe == NFC_DH_ID) {
      nfaStat =
          NFA_EeSetDefaultProtoRouting(NFC_DH_ID, protoMask, 0, 0, protoMask, 0, 0); // [SEC] Power state added
    } else {
      nfaStat = NFA_EeClearDefaultProtoRouting(activeSe, protoMask);
      nfaStat = NFA_EeSetDefaultProtoRouting(
          activeSe, protoMask, protoMask, 0, mSecureNfcEnabled ? 0 : protoMask, // [SEC] Power state added
          mSecureNfcEnabled ? 0 : protoMask, mSecureNfcEnabled ? 0 : protoMask);
    }
    if (nfaStat == NFA_STATUS_OK)
      mRoutingEvent.wait();
    else
      LOG(ERROR) << fn << "Fail to set default proto routing for T3T";
  }
}

void RoutingManager::updateDefaultRoute() {
  static const char fn[] = "RoutingManager::updateDefaultRoute";

  // [SEC] Set default AID route
  if (NFC_GetNCIVersion() == NCI_VERSION_1_0) {
    int activeSe = getActiveSe(mDefaultEe);

    DLOG_IF(INFO, nfc_debug_enabled) << fn << " Set default AID route";
    tNFA_STATUS nfaStat;
    SyncEventGuard guard(mRoutingEvent);
    tNFA_PROTOCOL_MASK protoMask = NFA_PROTOCOL_MASK_ISO7816;
    if (activeSe == NFC_DH_ID) {
      nfaStat = NFA_EeClearDefaultProtoRouting(mOffHostRouteUicc[0], protoMask);
      nfaStat =
        NFA_EeSetDefaultProtoRouting(NFC_DH_ID, protoMask, 0, 0, protoMask, 0, 0);
    } else {
      nfaStat = NFA_EeClearDefaultProtoRouting(activeSe, protoMask);
      nfaStat = NFA_EeSetDefaultProtoRouting(
          activeSe, protoMask, protoMask, 0, mSecureNfcEnabled ? 0 : protoMask,
          mSecureNfcEnabled ? 0 : protoMask, mSecureNfcEnabled ? 0 : protoMask);
    }
    if (nfaStat == NFA_STATUS_OK)
        mRoutingEvent.wait();
    else
        LOG(ERROR) << fn << "Fail to set default proto routing for AID";
  }

  if (NFC_GetNCIVersion() != NCI_VERSION_2_0) return;

  // Register System Code for routing
  SyncEventGuard guard(mRoutingEvent);
  tNFA_STATUS nfaStat = NFA_EeAddSystemCodeRouting(
      mDefaultSysCode, mDefaultSysCodeRoute,
      mSecureNfcEnabled ? 0x01 : mDefaultSysCodePowerstate);
  if (nfaStat == NFA_STATUS_NOT_SUPPORTED) {
    mIsScbrSupported = false;
    LOG(ERROR) << fn << ": SCBR not supported";
  } else if (nfaStat == NFA_STATUS_OK) {
    mIsScbrSupported = true;
    mRoutingEvent.wait();
    DLOG_IF(INFO, nfc_debug_enabled)
        << fn << ": Succeed to register system code";
  } else {
    LOG(ERROR) << fn << ": Fail to register system code";
  }

  // Register zero lengthy Aid for default Aid Routing
  if (mDefaultEe != mDefaultIsoDepRoute) {
    uint8_t powerState = 0x01;
    if (!mSecureNfcEnabled)
      powerState = (mDefaultEe != 0x00) ? mOffHostAidRoutingPowerState : 0x11;
    nfaStat = NFA_EeAddAidRouting(mDefaultEe, 0, NULL, powerState,
                                  AID_ROUTE_QUAL_PREFIX);
    if (nfaStat == NFA_STATUS_OK)
      DLOG_IF(INFO, nfc_debug_enabled)
          << fn << ": Succeed to register zero length AID";
    else
      LOG(ERROR) << fn << ": failed to register zero length AID";
  }
}

tNFA_TECHNOLOGY_MASK RoutingManager::updateEeTechRouteSetting() {
  static const char fn[] = "RoutingManager::updateEeTechRouteSetting";
  tNFA_TECHNOLOGY_MASK allSeTechMask = 0x00;

  if (mDefaultOffHostRoute == 0 && mDefaultFelicaRoute == 0)
    return allSeTechMask;

  DLOG_IF(INFO, nfc_debug_enabled)
      << fn << ": Number of EE is " << (int)mEeInfo.num_ee;

  tNFA_STATUS nfaStat;
  for (uint8_t i = 0; i < mEeInfo.num_ee; i++) {
    tNFA_HANDLE eeHandle = mEeInfo.ee_disc_info[i].ee_handle;
    tNFA_TECHNOLOGY_MASK seTechMask = 0;

    DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf(
        "%s   EE[%u] Handle: 0x%04x  techA: 0x%02x  techB: "
        "0x%02x  techF: 0x%02x  techBprime: 0x%02x",
        fn, i, eeHandle, mEeInfo.ee_disc_info[i].la_protocol,
        mEeInfo.ee_disc_info[i].lb_protocol,
        mEeInfo.ee_disc_info[i].lf_protocol,
        mEeInfo.ee_disc_info[i].lbp_protocol);

    // [SEC] Set tech A and B following ISO-DEP
    if ((mDefaultIsoDepRoute != 0) &&
        (eeHandle == (mDefaultIsoDepRoute | NFA_HANDLE_GROUP_EE))) {
      if (mEeInfo.ee_disc_info[i].la_protocol != 0)
        seTechMask |= NFA_TECHNOLOGY_MASK_A;
      if (mEeInfo.ee_disc_info[i].lb_protocol != 0)
        seTechMask |= NFA_TECHNOLOGY_MASK_B;
    }
    if ((mDefaultFelicaRoute != 0) &&
        (eeHandle == (mDefaultFelicaRoute | NFA_HANDLE_GROUP_EE))) {
      if (mEeInfo.ee_disc_info[i].lf_protocol != 0)
        seTechMask |= NFA_TECHNOLOGY_MASK_F;
    }

    DLOG_IF(INFO, nfc_debug_enabled)
        << StringPrintf("%s: seTechMask[%u]=0x%02x", fn, i, seTechMask);
    if (seTechMask != 0x00) {
      DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf(
          "Configuring tech mask 0x%02x on EE 0x%04x", seTechMask, eeHandle);

      nfaStat = NFA_CeConfigureUiccListenTech(eeHandle, seTechMask);
      if (nfaStat != NFA_STATUS_OK)
        LOG(ERROR) << fn << "Failed to configure UICC listen technologies.";

      // clear previous before setting new power state
      nfaStat = NFA_EeClearDefaultTechRouting(eeHandle, seTechMask);
      if (nfaStat != NFA_STATUS_OK)
        LOG(ERROR) << fn << "Failed to clear EE technology routing.";

      nfaStat = NFA_EeSetDefaultTechRouting(
          eeHandle, seTechMask, mSecureNfcEnabled ? 0 : seTechMask, 0,
          mSecureNfcEnabled ? 0 : seTechMask,
          mSecureNfcEnabled ? 0 : seTechMask,
          mSecureNfcEnabled ? 0 : seTechMask);
      if (nfaStat != NFA_STATUS_OK)
        LOG(ERROR) << fn << "Failed to configure UICC technology routing.";

      allSeTechMask |= seTechMask;
    }
  }

  // Clear DH technology route on NFC-A
  if ((allSeTechMask & NFA_TECHNOLOGY_MASK_A) != 0) {
    nfaStat = NFA_EeClearDefaultTechRouting(NFC_DH_ID, NFA_TECHNOLOGY_MASK_A);
    if (nfaStat != NFA_STATUS_OK)
      LOG(ERROR) << "Failed to clear DH technology routing on NFC-A.";
  }

  // Clear DH technology route on NFC-F
  if ((allSeTechMask & NFA_TECHNOLOGY_MASK_F) != 0) {
    nfaStat = NFA_EeClearDefaultTechRouting(NFC_DH_ID, NFA_TECHNOLOGY_MASK_F);
    if (nfaStat != NFA_STATUS_OK)
      LOG(ERROR) << "Failed to clear DH technology routing on NFC-F.";
  }

  // [SEC] Enable all tech if default is route DH
  if (mDefaultEe == NFC_DH_ID) {
    tNFA_TECHNOLOGY_MASK seTechMask = 0;
    seTechMask = NFA_TECHNOLOGY_MASK_A | NFA_TECHNOLOGY_MASK_B | NFA_TECHNOLOGY_MASK_F;
    nfaStat = NFA_EeSetDefaultTechRouting(
                  NFC_DH_ID, seTechMask, 0, 0, mSecureNfcEnabled ? 0 : seTechMask,
                  mSecureNfcEnabled ? 0 : seTechMask, mSecureNfcEnabled ? 0 : seTechMask);
    if (nfaStat != NFA_STATUS_OK)
        LOG(ERROR) << fn << "Failed to configure DH technology routing.";
    allSeTechMask |= seTechMask;
  }

  return allSeTechMask;
}

/*******************************************************************************
**
** Function:        nfaEeCallback
**
** Description:     Receive execution environment-related events from stack.
**                  event: Event code.
**                  eventData: Event data.
**
** Returns:         None
**
*******************************************************************************/
void RoutingManager::nfaEeCallback(tNFA_EE_EVT event,
                                   tNFA_EE_CBACK_DATA* eventData) {
  static const char fn[] = "RoutingManager::nfaEeCallback";

  RoutingManager& routingManager = RoutingManager::getInstance();
  if (eventData) routingManager.mCbEventData = *eventData;

  switch (event) {
    case NFA_EE_REGISTER_EVT: {
      SyncEventGuard guard(routingManager.mEeRegisterEvent);
      DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf(
          "%s: NFA_EE_REGISTER_EVT; status=%u", fn, eventData->ee_register);
      routingManager.mEeRegisterEvent.notifyOne();
    } break;

    case NFA_EE_DEREGISTER_EVT: {
      DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf(
          "%s: NFA_EE_DEREGISTER_EVT; status=0x%X", fn, eventData->status);
      routingManager.mReceivedEeInfo = false;
      routingManager.mReceivedeSEEeInfo = false; // [SEC] for eSE
      routingManager.mDeinitializing = false;
    } break;

    case NFA_EE_MODE_SET_EVT: {
      SyncEventGuard guard(routingManager.mEeSetModeEvent);
      DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf(
          "%s: NFA_EE_MODE_SET_EVT; status: 0x%04X  handle: 0x%04X  ", fn,
          eventData->mode_set.status, eventData->mode_set.ee_handle);
      routingManager.mEeSetModeEvent.notifyOne();
    } break;

    case NFA_EE_SET_TECH_CFG_EVT: {
      DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf(
          "%s: NFA_EE_SET_TECH_CFG_EVT; status=0x%X", fn, eventData->status);
      SyncEventGuard guard(routingManager.mRoutingEvent);
      routingManager.mRoutingEvent.notifyOne();
    } break;

    case NFA_EE_CLEAR_TECH_CFG_EVT: {
      DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf(
          "%s: NFA_EE_CLEAR_TECH_CFG_EVT; status=0x%X", fn, eventData->status);
      SyncEventGuard guard(routingManager.mRoutingEvent);
      routingManager.mRoutingEvent.notifyOne();
    } break;

    case NFA_EE_SET_PROTO_CFG_EVT: {
      DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf(
          "%s: NFA_EE_SET_PROTO_CFG_EVT; status=0x%X", fn, eventData->status);
      SyncEventGuard guard(routingManager.mRoutingEvent);
      routingManager.mRoutingEvent.notifyOne();
    } break;

    case NFA_EE_CLEAR_PROTO_CFG_EVT: {
      DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf(
          "%s: NFA_EE_CLEAR_PROTO_CFG_EVT; status=0x%X", fn, eventData->status);
      SyncEventGuard guard(routingManager.mRoutingEvent);
      routingManager.mRoutingEvent.notifyOne();
    } break;

    case NFA_EE_ACTION_EVT: {
      tNFA_EE_ACTION& action = eventData->action;
      if (action.trigger == NFC_EE_TRIG_SELECT)
        DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf(
            "%s: NFA_EE_ACTION_EVT; h=0x%X; trigger=select (0x%X)", fn,
            action.ee_handle, action.trigger);
      else if (action.trigger == NFC_EE_TRIG_APP_INIT) {
        tNFC_APP_INIT& app_init = action.param.app_init;
        DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf(
            "%s: NFA_EE_ACTION_EVT; h=0x%X; trigger=app-init "
            "(0x%X); aid len=%u; data len=%u",
            fn, action.ee_handle, action.trigger, app_init.len_aid,
            app_init.len_data);
      } else if (action.trigger == NFC_EE_TRIG_RF_PROTOCOL)
        DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf(
            "%s: NFA_EE_ACTION_EVT; h=0x%X; trigger=rf protocol (0x%X)", fn,
            action.ee_handle, action.trigger);
      else if (action.trigger == NFC_EE_TRIG_RF_TECHNOLOGY)
        DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf(
            "%s: NFA_EE_ACTION_EVT; h=0x%X; trigger=rf tech (0x%X)", fn,
            action.ee_handle, action.trigger);
      else
        DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf(
            "%s: NFA_EE_ACTION_EVT; h=0x%X; unknown trigger (0x%X)", fn,
            action.ee_handle, action.trigger);
    } break;

    case NFA_EE_DISCOVER_REQ_EVT: {
      DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf(
          "%s: NFA_EE_DISCOVER_REQ_EVT; status=0x%X; num ee=%u", __func__,
          eventData->discover_req.status, eventData->discover_req.num_ee);
      SyncEventGuard guard(routingManager.mEeInfoEvent);
      memcpy(&routingManager.mEeInfo, &eventData->discover_req,
             sizeof(routingManager.mEeInfo));
      // [SEC] Detects and notify UICC and eSE info
      for (uint8_t i = 0; i < routingManager.mEeInfo.num_ee; i++) {
        tNFA_HANDLE eeHandle = routingManager.mEeInfo.ee_disc_info[i].ee_handle;
        if (eeHandle == (routingManager.mOffHostRouteEse[0] | NFA_HANDLE_GROUP_EE)) {
          routingManager.mReceivedeSEEeInfo = true; // [SEC] for eSE
          routingManager.meSeEeInfoEvent.notifyOne();
        }
        if (eeHandle == (routingManager.mOffHostRouteUicc[0] | NFA_HANDLE_GROUP_EE)) {
          routingManager.mReceivedEeInfo = true; // [SEC] for UICC
          routingManager.mEeInfoEvent.notifyOne();
        }
      }
      if ((routingManager.mReceivedEeInfo || routingManager.mReceivedeSEEeInfo)
              && !routingManager.mDeinitializing) {
        routingManager.mEeInfoChanged = true;
        routingManager.notifyEeUpdated();
      }
      routingManager.mReceivedEeInfo = true;
      routingManager.mEeInfoEvent.notifyOne();
    } break;

    case NFA_EE_NO_CB_ERR_EVT:
      DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf(
          "%s: NFA_EE_NO_CB_ERR_EVT  status=%u", fn, eventData->status);
      break;

    case NFA_EE_ADD_AID_EVT: {
      DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf(
          "%s: NFA_EE_ADD_AID_EVT  status=%u", fn, eventData->status);
      SyncEventGuard guard(routingManager.mRoutingEvent);
      routingManager.mAidRoutingConfigured =
          (eventData->status == NFA_STATUS_OK);
      routingManager.mRoutingEvent.notifyOne();
    } break;

    case NFA_EE_ADD_SYSCODE_EVT: {
      SyncEventGuard guard(routingManager.mRoutingEvent);
      routingManager.mRoutingEvent.notifyOne();
      DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf(
          "%s: NFA_EE_ADD_SYSCODE_EVT  status=%u", fn, eventData->status);
    } break;

    case NFA_EE_REMOVE_SYSCODE_EVT: {
      SyncEventGuard guard(routingManager.mRoutingEvent);
      routingManager.mRoutingEvent.notifyOne();
      DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf(
          "%s: NFA_EE_REMOVE_SYSCODE_EVT  status=%u", fn, eventData->status);
    } break;

    case NFA_EE_REMOVE_AID_EVT: {
      DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf(
          "%s: NFA_EE_REMOVE_AID_EVT  status=%u", fn, eventData->status);
      SyncEventGuard guard(routingManager.mRoutingEvent);
      routingManager.mAidRoutingConfigured =
          (eventData->status == NFA_STATUS_OK);
      routingManager.mRoutingEvent.notifyOne();
    } break;

    case NFA_EE_NEW_EE_EVT: {
      DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf(
          "%s: NFA_EE_NEW_EE_EVT  h=0x%X; status=%u", fn,
          eventData->new_ee.ee_handle, eventData->new_ee.ee_status);
    } break;

    case NFA_EE_UPDATED_EVT: {
      DLOG_IF(INFO, nfc_debug_enabled)
          << StringPrintf("%s: NFA_EE_UPDATED_EVT", fn);
      SyncEventGuard guard(routingManager.mEeUpdateEvent);
      routingManager.mEeUpdateEvent.notifyOne();
    } break;

    default:
      DLOG_IF(INFO, nfc_debug_enabled)
          << StringPrintf("%s: unknown event=%u ????", fn, event);
      break;
  }
}

int RoutingManager::registerT3tIdentifier(uint8_t* t3tId, uint8_t t3tIdLen) {
  static const char fn[] = "RoutingManager::registerT3tIdentifier";

  DLOG_IF(INFO, nfc_debug_enabled)
      << fn << ": Start to register NFC-F system on DH";

  if (t3tIdLen != (2 + NCI_RF_F_UID_LEN + NCI_T3T_PMM_LEN)) {
    LOG(ERROR) << fn << ": Invalid length of T3T Identifier";
    return NFA_HANDLE_INVALID;
  }

  mNfcFOnDhHandle = NFA_HANDLE_INVALID;

  uint16_t systemCode;
  uint8_t nfcid2[NCI_RF_F_UID_LEN];
  uint8_t t3tPmm[NCI_T3T_PMM_LEN];

  systemCode = (((int)t3tId[0] << 8) | ((int)t3tId[1] << 0));
  memcpy(nfcid2, t3tId + 2, NCI_RF_F_UID_LEN);
  memcpy(t3tPmm, t3tId + 10, NCI_T3T_PMM_LEN);
  {
    SyncEventGuard guard(mRoutingEvent);
    tNFA_STATUS nfaStat = NFA_CeRegisterFelicaSystemCodeOnDH(
        systemCode, nfcid2, t3tPmm, nfcFCeCallback);
    if (nfaStat == NFA_STATUS_OK) {
      mRoutingEvent.wait();
    } else {
      LOG(ERROR) << fn << ": Fail to register NFC-F system on DH";
      return NFA_HANDLE_INVALID;
    }
  }
  DLOG_IF(INFO, nfc_debug_enabled)
      << fn << ": Succeed to register NFC-F system on DH";

  // Register System Code for routing
  if (mIsScbrSupported) {
    SyncEventGuard guard(mRoutingEvent);
    tNFA_STATUS nfaStat = NFA_EeAddSystemCodeRouting(systemCode, NCI_DH_ID,
                                                     SYS_CODE_PWR_STATE_HOST);
    if (nfaStat == NFA_STATUS_OK) {
      mRoutingEvent.wait();
    }
    if ((nfaStat != NFA_STATUS_OK) || (mCbEventData.status != NFA_STATUS_OK)) {
      LOG(ERROR) << StringPrintf("%s: Fail to register system code on DH", fn);
      return NFA_HANDLE_INVALID;
    }
    DLOG_IF(INFO, nfc_debug_enabled)
        << StringPrintf("%s: Succeed to register system code on DH", fn);
    // add handle and system code pair to the map
    mMapScbrHandle.emplace(mNfcFOnDhHandle, systemCode);
  } else {
    LOG(ERROR) << StringPrintf("%s: SCBR Not supported", fn);
  }

  return mNfcFOnDhHandle;
}

void RoutingManager::deregisterT3tIdentifier(int handle) {
  static const char fn[] = "RoutingManager::deregisterT3tIdentifier";

  DLOG_IF(INFO, nfc_debug_enabled)
      << StringPrintf("%s: Start to deregister NFC-F system on DH", fn);
  {
    SyncEventGuard guard(mRoutingEvent);
    tNFA_STATUS nfaStat = NFA_CeDeregisterFelicaSystemCodeOnDH(handle);
    if (nfaStat == NFA_STATUS_OK) {
      mRoutingEvent.wait();
      DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf(
          "%s: Succeeded in deregistering NFC-F system on DH", fn);
    } else {
      LOG(ERROR) << StringPrintf("%s: Fail to deregister NFC-F system on DH",
                                 fn);
    }
  }
  if (mIsScbrSupported) {
    map<int, uint16_t>::iterator it = mMapScbrHandle.find(handle);
    // find system code for given handle
    if (it != mMapScbrHandle.end()) {
      uint16_t systemCode = it->second;
      mMapScbrHandle.erase(handle);
      if (systemCode != 0) {
        SyncEventGuard guard(mRoutingEvent);
        tNFA_STATUS nfaStat = NFA_EeRemoveSystemCodeRouting(systemCode);
        if (nfaStat == NFA_STATUS_OK) {
          mRoutingEvent.wait();
          DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf(
              "%s: Succeeded in deregistering system Code on DH", fn);
        } else {
          LOG(ERROR) << StringPrintf("%s: Fail to deregister system Code on DH",
                                     fn);
        }
      }
    }
  }
}

void RoutingManager::nfcFCeCallback(uint8_t event,
                                    tNFA_CONN_EVT_DATA* eventData) {
  static const char fn[] = "RoutingManager::nfcFCeCallback";
  RoutingManager& routingManager = RoutingManager::getInstance();

  DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf("%s: 0x%x", __func__, event);

  switch (event) {
    case NFA_CE_REGISTERED_EVT: {
      DLOG_IF(INFO, nfc_debug_enabled)
          << StringPrintf("%s: registerd event notified", fn);
      routingManager.mNfcFOnDhHandle = eventData->ce_registered.handle;
      SyncEventGuard guard(routingManager.mRoutingEvent);
      routingManager.mRoutingEvent.notifyOne();
    } break;
    case NFA_CE_DEREGISTERED_EVT: {
      DLOG_IF(INFO, nfc_debug_enabled)
          << StringPrintf("%s: deregisterd event notified", fn);
      SyncEventGuard guard(routingManager.mRoutingEvent);
      routingManager.mRoutingEvent.notifyOne();
    } break;
    case NFA_CE_ACTIVATED_EVT: {
      DLOG_IF(INFO, nfc_debug_enabled)
          << StringPrintf("%s: activated event notified", fn);
      routingManager.notifyActivated(NFA_TECHNOLOGY_MASK_F);
    } break;
    case NFA_CE_DEACTIVATED_EVT: {
      DLOG_IF(INFO, nfc_debug_enabled)
          << StringPrintf("%s: deactivated event notified", fn);
      routingManager.notifyDeactivated(NFA_TECHNOLOGY_MASK_F);
    } break;
    case NFA_CE_DATA_EVT: {
      DLOG_IF(INFO, nfc_debug_enabled)
          << StringPrintf("%s: data event notified", fn);
      tNFA_CE_DATA& ce_data = eventData->ce_data;
      routingManager.handleData(NFA_TECHNOLOGY_MASK_F, ce_data.p_data,
                                ce_data.len, ce_data.status);
    } break;
    default: {
      DLOG_IF(INFO, nfc_debug_enabled)
          << StringPrintf("%s: unknown event=%u ????", fn, event);
    } break;
  }
}

bool RoutingManager::setNfcSecure(bool enable) {
  mSecureNfcEnabled = enable;
  DLOG_IF(INFO, true) << "setNfcSecure NfcService " << enable;
  return true;
}

void RoutingManager::deinitialize() {
  onNfccShutdown();
  NFA_EeDeregister(nfaEeCallback);
}

// [SEC] Finding active SE
int RoutingManager::getActiveSe(int defaultEe) {
  static const char fn[] = "RoutingManager::getActiveSe";

  if (defaultEe == NFC_DH_ID)
    return defaultEe;

  uint8_t actualNumEe = MAX_NUM_EE;
  tNFA_EE_INFO eeInfo[MAX_NUM_EE];
  memset(&eeInfo, 0, sizeof(eeInfo));
  tNFA_STATUS nfaStat;
  int expectedEe = NFC_DH_ID;

  if ((nfaStat = NFA_EeGetInfo(&actualNumEe, eeInfo)) != NFA_STATUS_OK) {
    LOG(ERROR) << StringPrintf("%s: fail get info; error=0x%X", fn, nfaStat);
    return NFC_DH_ID;
  }
  if (actualNumEe != 0) {
    for (uint8_t xx = 0; xx < actualNumEe; xx++) {
      bool bIsOffHostEEPresent =
          (eeInfo[xx].ee_interface[0] != NCI_NFCEE_INTERFACE_HCI_ACCESS) &&
          (eeInfo[xx].ee_status == NFA_EE_STATUS_ACTIVE);
      if (bIsOffHostEEPresent) {
        DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf(
            "%s: Handle: 0x%04x active se", fn, eeInfo[xx].ee_handle);
        if (eeInfo[xx].ee_handle == (defaultEe | NFA_HANDLE_GROUP_EE)) {
          return defaultEe;
        } else {
          expectedEe = (eeInfo[xx].ee_handle & ~NFA_HANDLE_GROUP_MASK);
        }
      }
    }
  }
  DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf(
                                       "%s: Handle: 0x%04x expected SE", fn, expectedEe);
  return expectedEe;
}

// [SEC] Get default EE
int RoutingManager::getDefaultEe() {
  return mDefaultEe;
}

// [SEC] Set default EE
bool RoutingManager::setDefaultEe(int defaultEe) {
  mDefaultEe = defaultEe;
  mDefaultOffHostRoute = defaultEe;
  mDefaultFelicaRoute = defaultEe;
  DLOG_IF(INFO, true) << "setDefaultEe " << defaultEe;
  return true;
}

// [SEC] Get SE Info
bool RoutingManager::isEeActivated(uint8_t eeHandle) {
  static const char fn[] = "RoutingManager::isEeActivated";

  uint8_t actualNumEe = MAX_NUM_EE;
  tNFA_EE_INFO eeInfo[MAX_NUM_EE];
  memset(&eeInfo, 0, sizeof(eeInfo));
  tNFA_STATUS nfaStat;
  bool isFounded = false;

  if ((nfaStat = NFA_EeGetInfo(&actualNumEe, eeInfo)) != NFA_STATUS_OK) {
      LOG(ERROR) << StringPrintf("%s: fail get info; error=0x%X", fn, nfaStat);
      return false;
  }
  if (actualNumEe != 0) {
    for (uint8_t xx = 0; xx < actualNumEe; xx++) {
      bool bIsOffHostEEPresent =
        (eeInfo[xx].ee_interface[0] != NCI_NFCEE_INTERFACE_HCI_ACCESS) &&
        (eeInfo[xx].ee_status == NFA_EE_STATUS_ACTIVE);
      if (bIsOffHostEEPresent) {
        DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf(
                                                       "%s: Handle: 0x%04x active se", fn, eeInfo[xx].ee_handle);
        if (eeInfo[xx].ee_handle == (eeHandle | NFA_HANDLE_GROUP_EE)) {
          isFounded = true;
        }
      }
    }
  }
  DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf("%s: isFounded %d", fn, isFounded);
  return isFounded;
}

// [SEC] Get SIM detection
bool RoutingManager::isUiccDetected() {
  static const char fn[] = "RoutingManager::getSimDetection";

  uint8_t actualNumEe = MAX_NUM_EE;
  tNFA_EE_INFO eeInfo[MAX_NUM_EE];
  memset(&eeInfo, 0, sizeof(eeInfo));
  tNFA_STATUS nfaStat;

  if ((nfaStat = NFA_EeGetInfo(&actualNumEe, eeInfo)) != NFA_STATUS_OK) {
    LOG(ERROR) << StringPrintf("%s: fail get info; error=0x%X", fn, nfaStat);
    return false;
  }
  if (actualNumEe != 0) {
    for (uint8_t xx = 0; xx < actualNumEe; xx++) {
      bool bIsOffHostEEPresent =
          (eeInfo[xx].ee_interface[0] != NCI_NFCEE_INTERFACE_HCI_ACCESS) &&
          (eeInfo[xx].ee_status == NFA_EE_STATUS_ACTIVE);
      if (bIsOffHostEEPresent) {
        DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf(
            "%s: Handle: 0x%04x active se", fn, eeInfo[xx].ee_handle);
        if (eeInfo[xx].ee_handle == (mOffHostRouteUicc[0] | NFA_HANDLE_GROUP_EE)) {
          return true;
        } else {
          return false;
        }
      }
    }
  }
  return false;
}

// [SEC] eSE activation
bool RoutingManager::activateSecureElement () {
  tNFA_STATUS nfaStat = NFA_STATUS_FAILED;
  uint8_t actualNumEe = MAX_NUM_EE;
  tNFA_EE_INFO eeInfo[MAX_NUM_EE];
  memset(&eeInfo, 0, sizeof(eeInfo));

  if ((nfaStat = NFA_EeGetInfo(&actualNumEe, eeInfo)) != NFA_STATUS_OK) {
    LOG(ERROR) << StringPrintf("fail get info; error=0x%X", nfaStat);
  }

  nfaStat = NFA_STATUS_FAILED;
  if (actualNumEe != 0) {
    for (uint8_t xx = 0; xx < actualNumEe; xx++) {
      if ((eeInfo[xx].num_interface != 0) &&
          (eeInfo[xx].ee_interface[0] != NCI_NFCEE_INTERFACE_HCI_ACCESS) &&
          (eeInfo[xx].ee_status == NFA_EE_STATUS_INACTIVE) &&
          (eeInfo[xx].ee_handle == (mOffHostRouteEse[0] | NFA_HANDLE_GROUP_EE))) { // Activate eSE only
        SyncEventGuard guard(mEeSetModeEvent);
        if ((nfaStat = NFA_EeModeSet(eeInfo[xx].ee_handle, NFA_EE_MD_ACTIVATE)) == NFA_STATUS_OK) {
          mEeSetModeEvent.wait();  // wait for NFA_EE_MODE_SET_EVT
        } else {
          LOG(ERROR) << StringPrintf("Failed to set EE active");
        }
      }
    }
  }
  return nfaStat;
}

// [SEC] Get SE list
jintArray RoutingManager::getSecureElementList(JNIEnv* e) {
  tNFA_STATUS nfaStat = NFA_STATUS_FAILED;
  uint8_t actualNumEe = MAX_NUM_EE;
  tNFA_EE_INFO eeInfo[MAX_NUM_EE];
  memset(&eeInfo, 0, sizeof(eeInfo));

  if ((nfaStat = NFA_EeGetInfo(&actualNumEe, eeInfo)) != NFA_STATUS_OK) {
    LOG(ERROR) << StringPrintf("fail get info; error=0x%X", nfaStat);
    return NULL;
  }

  jintArray seList = e->NewIntArray(actualNumEe);
  jint seId = 0;
  int cnt = 0;
  if (actualNumEe != 0) {
    for (uint8_t xx = 0; xx < actualNumEe; xx++) {
      LOG(INFO) << StringPrintf("searching ee %d", xx);
      if ((eeInfo[xx].num_interface != 0) &&
          (eeInfo[xx].ee_interface[0] != NCI_NFCEE_INTERFACE_HCI_ACCESS)) {
        LOG(INFO) << StringPrintf("find ee %d", seId);
        seId = eeInfo[xx].ee_handle & ~NFA_HANDLE_GROUP_EE;
        e->SetIntArrayRegion(seList, cnt++, 1, &seId);
      }
    }
  }
  return seList;
}

int RoutingManager::registerJniFunctions(JNIEnv* e) {
  static const char fn[] = "RoutingManager::registerJniFunctions";
  DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf("%s", fn);
  return jniRegisterNativeMethods(
      e, "com/android/nfc/cardemulation/AidRoutingManager", sMethods,
      NELEM(sMethods));
}

int RoutingManager::com_android_nfc_cardemulation_doGetDefaultRouteDestination(
    JNIEnv*) {
  return getInstance().mDefaultEe;
}

int RoutingManager::
    com_android_nfc_cardemulation_doGetDefaultOffHostRouteDestination(JNIEnv*) {
  return getInstance().mDefaultOffHostRoute;
}

jbyteArray
RoutingManager::com_android_nfc_cardemulation_doGetOffHostUiccDestination(
    JNIEnv* e) {
  std::vector<uint8_t> uicc = getInstance().mOffHostRouteUicc;
  if (uicc.size() == 0) {
    return NULL;
  }
  CHECK(e);
  jbyteArray uiccJavaArray = e->NewByteArray(uicc.size());
  CHECK(uiccJavaArray);
  e->SetByteArrayRegion(uiccJavaArray, 0, uicc.size(), (jbyte*)&uicc[0]);
  return uiccJavaArray;
}

jbyteArray
RoutingManager::com_android_nfc_cardemulation_doGetOffHostEseDestination(
    JNIEnv* e) {
  std::vector<uint8_t> ese = getInstance().mOffHostRouteEse;
  if (ese.size() == 0) {
    return NULL;
  }
  CHECK(e);
  jbyteArray eseJavaArray = e->NewByteArray(ese.size());
  CHECK(eseJavaArray);
  e->SetByteArrayRegion(eseJavaArray, 0, ese.size(), (jbyte*)&ese[0]);
  return eseJavaArray;
}

int RoutingManager::com_android_nfc_cardemulation_doGetAidMatchingMode(
    JNIEnv*) {
  return getInstance().mAidMatchingMode;
}

int RoutingManager::
    com_android_nfc_cardemulation_doGetDefaultIsoDepRouteDestination(JNIEnv*) {
  return getInstance().mDefaultIsoDepRoute;
}
