/*
 * Copyright Samsung Electronics Co., LTD.
 *
 * This software is proprietary of Samsung Electronics.
 * No part of this software, either material or conceptual may be copied or distributed, transmitted,
 * transcribed, stored in a retrieval system or translated into any human or computer language in any form by any means,
 * electronic, mechanical, manual or otherwise, or disclosed
 * to third parties without the express written permission of Samsung Electronics.
 */

/*
 * messageid.h
 *
 *  Created on: 2014. 7. 3.
 *      Author: sungwoo48.choi
 */

#ifndef __MESSAGE_ID_H__
#define __MESSAGE_ID_H__

#include "systemmessageid.h"

#define MSG_CS_BASE         1000
#define MSG_SS_BASE         1500
#define MSG_SIM_BASE        2000
#define MSG_PS_BASE         3000
#define MSG_NET_BASE        4000
#define MSG_MISC_BASE       5000
#define MSG_SMS_BASE        6000
#define MSG_AUDIO_BASE      7000
#define MSG_IMS_BASE        8000
#define MSG_GPS_BASE        9000
#define MSG_WLAN_BASE       10000
#define MSG_VSIM_BASE       11000
#define MSG_DEBUG_BASE      12000
#define MSG_STK_BASE        13000
#define MSG_EMBMS_BASE      14000



/**
 * CscService
 */
enum CscServiceMsgId {
    MSG_CS_CALL_LIST    = MSG_CS_BASE + 1,
    MSG_CS_CALL_LIST_DONE,

    MSG_CS_CALL_DIAL,
    MSG_CS_CALL_DIAL_DONE,

    MSG_CS_CALL_DIAL_VIDEO,
    MSG_CS_CALL_DIAL_VIDEO_DONE,

    MSG_CS_CALL_EMERGENCY_DIAL,
    MSG_CS_CALL_EMERGENCY_DIAL_DONE,
    //MSG_CS_CALL_DIAL_EMERGENCY_CALL,

    MSG_CS_CALL_ANSWER,
    MSG_CS_CALL_ANSWER_DONE,        //10

    MSG_CS_SS_EXPLICIT_CALL_TRANSFER,
    MSG_CS_SS_EXPLICIT_CALL_TRANSFER_DONE,

    MSG_CS_CALL_HANGUP,
    MSG_CS_CALL_HANGUP_DONE,

    MSG_CS_LAST_CALL_FAIL_CAUSE,
    MSG_CS_LAST_CALL_FAIL_CAUSE_DONE,

    MSG_CS_DTMF_START,
    MSG_CS_DTMF_START_DONE,

    MSG_CS_DTMF,
    MSG_CS_DTMF_DONE,    //20

    MSG_CS_DTMF_STOP,
    MSG_CS_DTMF_STOP_DONE,

    MSG_CS_CALL_STATE_CHANGE_NTF,
    MSG_CS_CALL_RINGING_NTF,

    MSG_CS_SS_HANGUP_WAITING_OR_BACKGROUND,
    MSG_CS_SS_HANGUP_WAITING_OR_BACKGROUND_DONE,

    MSG_CS_SS_HANGUP_FOREGROUND_RESUME_BACKGROUND,
    MSG_CS_SS_HANGUP_FOREGROUND_RESUME_BACKGROUND_DONE,

    MSG_CS_SS_SWITCH_WAITING_OR_HOLDING_AND_ACTIVE,
    MSG_CS_SS_SWITCH_WAITING_OR_HOLDING_AND_ACTIVE_DONE,        //30

    MSG_CS_SS_CONFERENCE,
    MSG_CS_SS_CONFERENCE_DONE,

    MSG_CS_SS_UDUB,
    MSG_CS_SS_UDUB_DONE,

    MSG_CS_SS_SEPARATE_CONNECTION,
    MSG_CS_SS_SEPARATE_CONNECTION_DONE,

    //call & ss implemented till here

    MSG_CS_SS_CALL_DEFLECTION,

    MSG_CS_SS_MANAGE_CALLS_DONE,

    MSG_CS_SS_SET_CALL_BARRING,
    MSG_CS_SS_QUERY_CALL_BARRING,    //40
    MSG_CS_SS_CALL_BARRING_DONE,

    MSG_CS_SS_SET_LINE_ID,
    MSG_CS_SS_SET_LINE_ID_DONE,

    MSG_CS_SS_GET_LINE_ID,
    MSG_CS_SS_GET_LINE_ID_DONE,

    MSG_CS_SS_CALL_LINE_ID_DONE,

    MSG_CS_SS_AOC,
    MSG_CS_SS_AOC_DONE,

    MSG_CS_SS_RETURN_RESULT_NTF,

    MSG_CS_CB_CHID,    //50
    MSG_CS_CB_CHID_DONE,

    MSG_CS_SMS_INCOMING_NTF,
    MSG_CS_SMS_INIT_CP_NTF,

    MSG_CS_SOUND_SET_MUTE,
    MSG_CS_SOUND_SET_MUTE_DONE,
    MSG_CS_SOUND_GET_MUTE,
    MSG_CS_SOUND_GET_MUTE_DONE,
    MSG_CS_SOUND_RINGBACKTONE_NTF,

    MSG_CS_SOUND_WB_AMR_REPORT_NTF,
    MSG_CS_SOUND_CLOCK_CTRL_NTF,    //60
    MSG_CS_SOUND_MIC_CONTROL,
    MSG_CS_SOUND_MIC_CONTROL_DONE,

    MSG_CS_SOUND_OEM_DONE,

    MSG_CS_SOUND_SWITCH_VOICE_CALL,
    MSG_CS_SOUND_SWITCH_VOICE_CALL_DONE,

    MSG_CS_SET_CALL_CONFIRM,
    MSG_CS_SET_CALL_CONFIRM_DONE,
    MSG_CS_SEND_CALL_CONFIRM,
    MSG_CS_SEND_CALL_CONFIRM_DONE,

    MSG_CS_CALL_PRESENT_NTF,    //70

#ifdef SUPPORT_CDMA
    MSG_CS_CDMA_BURST_DTMF,
    MSG_CS_CDMA_BURST_DTMF_DONE,

    MSG_CS_SS_CDMA_FLASH,
    MSG_CS_SS_CDMA_FLASH_DONE,

    MSG_CS_CDMA_SET_PREFERRED_VOICE_PRIVACY_MODE,
    MSG_CS_CDMA_SET_PREFERRED_VOICE_PRIVACY_MODE_DONE,
    MSG_CS_CDMA_QUERY_PREFERRED_VOICE_PRIVACY_MODE,
    MSG_CS_CDMA_QUERY_PREFERRED_VOICE_PRIVACY_MODE_DONE,

    MSG_CS_IND_CDMA_INFO_REC,

    MSG_CS_SS_IND_CDMA_CALL_WAITING,    //80
    MSG_CS_IND_CDMA_OTA_PROVISION_STATUS,
#endif
    MSG_CS_IND_EMERGENCY_SUPPORT_RAT_MODE,
    MSG_CS_IND_ENTER_EMERGENCY_CB_MODE_CHANGED,
    MSG_CS_IND_EXIT_EMERGENCY_CB_MODE_CHANGED,
    MSG_CS_EXIT_EMERGENCY_CB_MODE,
    MSG_CS_EXIT_EMERGENCY_CB_MODE_DONE,
    MSG_CS_IND_RESEND_IN_CALL_MUTE,
};

/**
 * SupplementaryService
 */
enum SupplementaryServiceMsgId {
    MSG_SS_GET_CLIP    = MSG_SS_BASE + 1,
    MSG_SS_GET_CLIP_DONE,

    MSG_SS_SET_CLIR,

    MSG_SS_GET_CLIR,
    MSG_SS_GET_CLIR_DONE,

    MSG_SS_SET_CALL_FORWARDING,
    MSG_SS_SET_CALL_FORWARDING_DONE,

    MSG_SS_QUERY_CALL_FORWARDING,
    MSG_SS_QUERY_CALL_FORWARDING_DONE,

    MSG_SS_SET_CALL_WAITING,
    MSG_SS_SET_CALL_WAITING_DONE,

    MSG_SS_QUERY_CALL_WAITING,
    MSG_SS_QUERY_CALL_WAITING_DONE,

    MSG_SS_CALL_BARRING_PWD,
    MSG_SS_CALL_BARRING_PWD_DONE,

    MSG_SS_SEND_USSD,
    MSG_SS_SEND_USSD_DONE,

    MSG_SS_CANCEL_USSD,
    MSG_SS_CANCEL_USSD_DONE,

    MSG_SS_USSD_NTF,
    MSG_SS_SVC_NTF,

    MSG_SS_QUERY_COLP,
    MSG_SS_QUERY_COLP_DONE,
    MSG_SS_QUERY_COLR,
    MSG_SS_QUERY_COLR_DONE,

    MSG_SS_SEND_ENCODED_USSD,

    MSG_SS_IND,
};

/**
 * SimService
 */
enum SimServiceMsgId {
    MSG_SIM_GET_STATUS = MSG_SIM_BASE + 1,
    MSG_SIM_GET_STATUS_DONE,
    MSG_SIM_VERIFY_PIN,
    MSG_SIM_VERIFY_PIN_DONE,
    MSG_SIM_VERIFY_PUK,
    MSG_SIM_VERIFY_PUK_DONE,
    MSG_SIM_VERIFY_PIN2,
    MSG_SIM_VERIFY_PIN2_DONE,
    MSG_SIM_VERIFY_PUK2,
    MSG_SIM_VERIFY_PUK2_DONE,
    MSG_SIM_CHANGE_PIN,
    MSG_SIM_CHANGE_PIN_DONE,
    MSG_SIM_CHANGE_PIN2,
    MSG_SIM_CHANGE_PIN2_DONE,
    MSG_SIM_VERIFY_NETWORK_LOCK,
    MSG_SIM_VERIFY_NETWORK_LOCK_DONE,
    MSG_SIM_IO,
    MSG_SIM_IO_DONE,
    MSG_SIM_GET_FACILITY_LOCK,
    MSG_SIM_GET_FACILITY_LOCK_DONE,
    MSG_SIM_SET_FACILITY_LOCK,
    MSG_SIM_SET_FACILITY_LOCK_DONE,
    MSG_SIM_GET_ISIM_AUTH,
    MSG_SIM_GET_ISIM_AUTH_DONE,
    MSG_SIM_GET_ISIM_GBA_AUTH,
    MSG_SIM_GET_ISIM_GBA_AUTH_DONE,
    MSG_SIM_TRANSMIT_APDU_BASIC,
    MSG_SIM_TRANSMIT_APDU_BASIC_DONE,
    MSG_SIM_OPEN_CHANNEL,
    MSG_SIM_OPEN_CHANNEL_DONE,
    MSG_SIM_CLOSE_CHANNEL,
    MSG_SIM_CLOSE_CHANNEL_DONE,
    MSG_SIM_TRANSMIT_APDU_CHANNEL,
    MSG_SIM_TRANSMIT_APDU_CHANNEL_DONE,
    MSG_SIM_GET_IMSI,
    MSG_SIM_GET_IMSI_DONE,

    MSG_SIM_STATUS_CHANGED,

    // Lollipop
    MSG_SIM_GET_SIM_AUTH,
    MSG_SIM_GET_SIM_AUTH_DONE,

    MSG_SIM_GET_ATR,
    MSG_SIM_GET_ATR_DONE,

    //PhoneBook
    MSG_SIM_READ_PB_ENTRY,
    MSG_SIM_READ_PB_ENTRY_DONE,
    MSG_SIM_UPDATE_PB_ENTRY,
    MSG_SIM_UPDATE_PB_ENTRY_DONE,
    MSG_SIM_GET_PB_STORAGE_INFO,
    MSG_SIM_GET_PB_STORAGE_INFO_DONE,
    MSG_SIM_GET_PB_STORAGE_LIST,
    MSG_SIM_GET_PB_STORAGE_LIST_DONE,
    MSG_SIM_GET_PB_ENTRY_INFO,
    MSG_SIM_GET_PB_ENTRY_INFO_DONE,
    MSG_SIM_GET_3G_PB_CAPA,
    MSG_SIM_GET_3G_PB_CAPA_DONE,
    MSG_SIM_PB_READY,

    MSG_SIM_ICCID_INFO,

    MSG_SIM_OEM_IMS_SIM_IO,
    MSG_SIM_OEM_IMS_SIM_IO_DONE,

    // Secure Element
    MSG_SIM_OEM_OPEN_CHANNEL,
    MSG_SIM_OEM_OPEN_CHANNEL_DONE,
    MSG_SIM_OEM_TRANSMIT_APDU_LOGICAL,
    MSG_SIM_OEM_TRANSMIT_APDU_LOGICAL_DONE,
    MSG_SIM_OEM_TRNASMIT_APDU_BASIC,
    MSG_SIM_OEM_TRNASMIT_APDU_BASIC_DONE,
    MSG_SIM_OEM_GET_CARD_PRESENT,
    MSG_SIM_OEM_GET_CARD_PRESENT_DONE,

    // New definition
    // Please define new message IDs of SMI(SIT) before HERE!
    MSG_SIM_GET_ICCID = 2900,
    MSG_SIM_GET_ICCID_DONE,
    MSG_SIM_ICCID_NOTIFICATION,

    MSG_SIM_GET_ICC_TYPE,
    MSG_SIM_GET_ICC_TYPE_DONE,
    MSG_SIM_ICC_TYPE_NOTIFICATION,

    MSG_SIM_GET_PIN_STATUS,
    MSG_SIM_GET_PIN_STATUS_DONE,
    MSG_SIM_PIN_STATUS_NOTIFICATION,

    MSG_SIM_GET_LOCK_INFORMATION,
    MSG_SIM_GET_LOCK_INFORMATION_DONE,

    MSG_SIM_GET_SIM_APPLICATION,
    MSG_SIM_GET_SIM_APPLICATION_DONE,

    MSG_SIM_SET_CARRIER_RESTRICTIONS,
    MSG_SIM_SET_CARRIER_RESTRICTIONS_DONE,
    MSG_SIM_GET_CARRIER_RESTRICTIONS,
    MSG_SIM_GET_CARRIER_RESTRICTIONS_DONE,
    MSG_SIM_SET_SIM_CARD_POWER,
    MSG_SIM_SET_SIM_CARD_POWER_DONE,
    MSG_SIM_IND_UICC_SUBSCRIPTION_STATUS_CHANGED,

    MSG_SIM_GET_SIM_LOCK_INFO,
    MSG_SIM_GET_SIM_LOCK_INFO_DONE,
    // Radio Config
    MSG_SIM_GET_SLOT_STATUS,
    MSG_SIM_GET_SLOT_STATUS_DONE,
    MSG_SIM_SET_LOGICAL_TO_PHYSICAL_SLOT_MAPPING,
    MSG_SIM_SET_LOGICAL_TO_PHYSICAL_SLOT_MAPPING_DONE,
    MSG_SIM_SLOT_STATUS_CHANGED,
    MSG_SIM_OEM_ICC_DEPERSONALIZATION,
    MSG_SIM_OEM_ICC_DEPERSONALIZATION_DONE,
};

/**
 * NetworkService
 */
enum NetworkServiceMsgId {
    MSG_NET_VOICE_REGISTRATION_STATE = MSG_NET_BASE + 1,
    MSG_NET_VOICE_REGISTRATION_STATE_DONE,
    MSG_NET_DATA_REGISTRATION_STATE,
    MSG_NET_DATA_REGISTRATION_STATE_DONE,
    MSG_NET_OPERATOR,
    MSG_NET_OPERATOR_DONE,
    MSG_NET_RADIO_POWER,
    MSG_NET_RADIO_POWER_DONE,
    MSG_NET_QUERY_NETWORK_SELECTION_MODE,
    MSG_NET_QUERY_NETWORK_SELECTION_MODE_DONE,
    MSG_NET_GET_RADIO_STATE,
    MSG_NET_GET_RADIO_STATE_DONE,

    MSG_NET_SET_NETWORK_SELECTION_AUTO,
    MSG_NET_SET_NETWORK_SELECTION_AUTO_DONE,
    MSG_NET_SET_NETWORK_SELECTION_MANUAL,
    MSG_NET_SET_NETWORK_SELECTION_MANUAL_DONE,
    MSG_NET_SET_NETWORK_SELECTION_MANUAL_WITH_RAT,
    MSG_NET_QUERY_AVAILABLE_NETWORKS,
    MSG_NET_QUERY_AVAILABLE_NETWORKS_DONE,
    MSG_NET_QUERY_BPLMN_SEARCH,
    MSG_NET_QUERY_BPLMN_SEARCH_DONE,
    MSG_NET_CANCEL_AVAILABLE_NETWORKS,
    MSG_NET_CANCE_AVAILABLE_NETWORKS_DONE,
    MSG_NET_QUERY_AVAILABLE_NETWORKS_WITH_RAN,
    MSG_NET_QUERY_AVAILABLE_NETWORKS_WITH_RAN_DONE,
    MSG_NET_SET_BAND_MODE,
    MSG_NET_SET_BAND_MODE_DONE,
    MSG_NET_QUERY_AVAILABLE_BAND_MODE,
    MSG_NET_QUERY_AVAILABLE_BAND_MODE_DONE,
    MSG_NET_SET_PREF_NETWORK_TYPE,
    MSG_NET_SET_PREF_NETWORK_TYPE_DONE,
    MSG_NET_GET_PREF_NETWORK_TYPE,
    MSG_NET_GET_PREF_NETWORK_TYPE_DONE,
    MSG_NET_VOICE_RADIO_TECH,
    MSG_NET_VOICE_RADIO_TECH_DONE,
    MSG_NET_GET_CELL_INFO_LIST,
    MSG_NET_GET_CELL_INFO_LIST_DONE,
    MSG_NET_SET_UNSOL_CELL_INFO_LIST_RATE,
    MSG_NET_SET_UNSOL_CELL_INFO_LIST_RATE_DONE,
    MSG_NET_ALLOW_DATA,
    MSG_NET_ALLOW_DATA_DONE,
    MSG_NET_SHUTDOWN,
    MSG_NET_SHUTDOWN_DONE,
    MSG_NET_SET_UPLMN,
    MSG_NET_SET_UPLMN_DONE,
    MSG_NET_GET_UPLMN,
    MSG_NET_GET_UPLMN_DONE,
    MSG_NET_SET_DS_NTW_TYPE,
    MSG_NET_SET_DS_NTW_TYPE_DONE,
    MSG_NET_GET_RC_NTW_TYPE,
    MSG_NET_GET_RC_NTW_TYPE_DONE,
    MSG_NET_SET_RC_NTW_TYPE,
    MSG_NET_SET_RC_NTW_TYPE_DONE,
    MSG_NET_GET_DUPLEX_MODE,
    MSG_NET_GET_DUPLEX_MODE_DONE,
    MSG_NET_SET_DUPLEX_MODE,
    MSG_NET_SET_DUPLEX_MODE_DONE,
    MSG_NET_QUERY_AVAILABLE_EMERGENCY_CALL_STATUS,
    MSG_NET_SET_EMERGENCY_CALL_STATUS,
    MSG_NET_SET_EMERGENCY_CALL_STATUS_DONE,

    MSG_NET_NETWORK_STATE_CHANGED,
    MSG_NET_RADIO_STATE_CHANGED,
    MSG_NET_CELL_INFO_LIST_RECEIVED,
    MSG_NET_RADIO_READY,
    MSG_NET_EMERGENCY_ACT_INFO_RECEIVED,

    MSG_NET_EMERGENCY_CALL_LIST_RECEIVED,

    MSG_NET_OEM_SET_PS_SERVICE,
    MSG_NET_OEM_SET_PS_SERVICE_DONE,
    MSG_NET_OEM_GET_PS_SERVICE,
    MSG_NET_OEM_GET_PS_SERVICE_DONE,
    MSG_NET_OEM_GET_IMS_SUPPORT_SERVICE,
    MSG_NET_OEM_GET_IMS_SUPPORT_SERVICE_DONE,

    // Opposite
    MSG_NET_OPPOSITE_ALLOW_DATA,
    MSG_NET_OPPOSITE_ALLOW_DATA_DONE,
    MSG_NET_OPPOSITE_ALLOW_DATA_FINISH,

    MSG_NET_SET_MC_SRCH,
    MSG_NET_SET_MC_SRCH_DONE,

    MSG_NET_RC_INFO_RECV,
    MSG_NET_SCG_BEARER_INFO_RECV,
    MSG_NET_PHYSICAL_CHANNEL_CONFIGS_RECV,
    MSG_NET_HSDPA_STATUS_RECEIVED,
    MSG_NET_IDENTITY_RECEIVED,
#ifdef SUPPORT_CDMA
    MSG_NET_CDMA_SET_ROAMING,
    MSG_NET_CDMA_SET_ROAMING_DONE,
    MSG_NET_CDMA_QUERY_ROAMING,
    MSG_NET_CDMA_QUERY_ROAMING_DONE,
    MSG_NET_SET_CDMA_HYBRID_MODE,
    MSG_NET_SET_CDMA_HYBRID_MODE_DONE,
    MSG_NET_GET_CDMA_HYBRID_MODE,
    MSG_NET_GET_CDMA_HYBRID_MODE_DONE,
#endif
    MSG_NET_SET_DUAL_NTW_AND_ALLOW_DATA,
    MSG_NET_SET_DUAL_NTW_AND_ALLOW_DATA_DONE,
    MSG_NET_IND_TOTAL_OOS,
    MSG_NET_IND_MCC,
    MSG_NET_IND_SIM_FILE_INFO,

    MSG_NET_START_NETWORK_SCAN,
    MSG_NET_START_NETWORK_SCAN_DONE,
    MSG_NET_STOP_NETWORK_SCAN,
    MSG_NET_STOP_NETWORK_SCAN_DONE,
    MSG_NET_IND_NETWORK_SCAN_RESULT,

    MSG_NET_OEM_GET_MANUAL_RAT_MODE,
    MSG_NET_OEM_GET_MANUAL_RAT_MODE_DONE,
    MSG_NET_OEM_SET_MANUAL_RAT_MODE,
    MSG_NET_OEM_SET_MANUAL_RAT_MODE_DONE,
    MSG_NET_OEM_GET_FREQUENCY_LOCK,
    MSG_NET_OEM_GET_FREQUENCY_LOCK_DONE,
    MSG_NET_OEM_SET_FREQUENCY_LOCK,
    MSG_NET_OEM_SET_FREQUENCY_LOCK_DONE,
    MSG_NET_OEM_SET_ENDC_MODE,
    MSG_NET_OEM_SET_ENDC_MODE_DONE,
    MSG_NET_OEM_GET_ENDC_MODE,
    MSG_NET_OEM_GET_ENDC_MODE_DONE,
    MSG_NET_IND_FREQUENCY_INFO,
    MSG_NET_IND_AC_BARRING_INFO,
    MSG_NET_GET_FREQUENCY_INFO,
    MSG_NET_GET_FREQUENCY_INFO_DONE,
    MSG_NET_IND_B2_B1_CONFIG,
};

/**
 * PsService
 */
enum PsServiceMsgId {
    MSG_PS_SETUP_DATA_CALL = MSG_PS_BASE + 1,
    MSG_PS_SETUP_DATA_CALL_DONE,
    MSG_PS_DEACT_DATA_CALL,
    MSG_PS_DEACT_DATA_CALL_DONE,
    MSG_PS_LAST_DATA_CALL_FAIL_CAUSE,            // deprecated
    MSG_PS_LAST_DATA_CALL_FAIL_CAUSE_DONE,       // deprecated
    MSG_PS_GET_DATA_CALL_LIST,
    MSG_PS_GET_DATA_CALL_LIST_DONE,
    MSG_PS_SET_INITIAL_ATTACH_APN,
    MSG_PS_SET_INITIAL_ATTACH_APN_DONE,
    MSG_PS_REFRESH_INITIAL_ATTACH_APN,
    MSG_PS_REFRESH_INITIAL_ATTACH_APN_DONE,
    MSG_PS_DATA_CALL_LIST_CHANGED,
    MSG_PS_IPV6_CONFIGURED,
    MSG_PS_DEDICATED_BEARER_INFO_UPDATED,
    MSG_PS_NAS_TIMER_STATUS_CHANGED,
    MSG_PS_SIM_OPERATOR_INFO_UPDATED,
    MSG_PS_IP_ADDRESSES_CONFIGURED,
    MSG_PS_DATA_CALL_STATUS_CHANGED,
    MSG_PS_SET_DATA_PROFILE,
    MSG_PS_SET_DATA_PROFILE_INITIAL_ATTACH,
    MSG_PS_SET_DATA_PROFILE_DONE,

    MSG_PS_IND_PCO_DATA,
    MSG_PS_START_KEEPALIVE,
    MSG_PS_START_KEEPALIVE_DONE,
    MSG_PS_STOP_KEEPALIVE,
    MSG_PS_STOP_KEEPALIVE_DONE,
    MSG_PS_IND_KEEPALIVE_STATUS,
    /* RadioConfig 1.1 */
    MSG_PS_SET_PREFERRED_DATA_MODEM,
    MSG_PS_SET_PREFERRED_DATA_MODEM_DONE,
};


/**
 * MiscService
 */
enum MiscServiceMsgId {
    MSG_MISC_BASEBAND_VER = MSG_MISC_BASE + 1,
    MSG_MISC_BASEBAND_VER_DONE,
    MSG_MISC_SIGNAL_STR,
    MSG_MISC_SIGNAL_STR_DONE,
    MSG_MISC_QUERY_TTY,
    MSG_MISC_QUERY_TTY_DONE,
    MSG_MISC_SET_TTY,
    MSG_MISC_SET_TTY_DONE,
    MSG_MISC_SCREEN,
    MSG_MISC_SCREEN_DONE,
    MSG_MISC_SEND_DEVICE_STATE,
    MSG_MISC_GET_IMEI,
    MSG_MISC_GET_IMEI_DONE,
    MSG_MISC_GET_IMEISV,
    MSG_MISC_GET_IMEISV_DONE,
    MSG_MISC_DEV_IDENTITY,
    MSG_MISC_DEV_IDENTITY_DONE,

    // NV operations
    MSG_MISC_NV_READ_ITEM,
    MSG_MISC_NV_READ_ITEM_DONE,
    MSG_MISC_NV_WRITE_ITEM,
    MSG_MISC_NV_WRITE_ITEM_DONE,

    MSG_MISC_SET_OPEN_CARRIER_INFO,
    MSG_MISC_SET_OPEN_CARRIER_INFO_DONE,

    MSG_MISC_UNSOL_SIGNAL_STRENGTH,
    MSG_MISC_UNSOL_NITZ_TIME_RECEIVED,

    MSG_MISC_OEM_HIDDEN_REQ,
    MSG_MISC_OEM_SET_ENG_MODE,
    MSG_MISC_OEM_SET_ENG_MODE_DONE,
    MSG_MISC_OEM_SET_SCREEN_LINE,
    MSG_MISC_OEM_SET_SCREEN_LINE_DONE,
    MSG_MISC_UNSOL_OEM_DISPLAY_ENG,
    MSG_MISC_UNSOL_OEM_PIN_CONTROL,
    MSG_MISC_OEM_SET_DEBUG_TRACE,
    MSG_MISC_OEM_SET_DEBUG_TRACE_DONE,
    MSG_MISC_OEM_CANCEL_AVAILABLE_NETWORKS,
    MSG_MISC_OEM_CANCEL_AVAILABLE_NETWORKS_DONE,
    MSG_MISC_OEM_IF_EXECUTE_AM,
    MSG_MISC_OEM_SET_CARRIER_CONFIG,
    MSG_MISC_OEM_SET_ENG_STRING_INPUT,
    MSG_MISC_OEM_SET_ENG_STRING_INPUT_DONE,
    MSG_MISC_OEM_APN_SETTINGS,
    MSG_MISC_OEM_GET_MSL_CODE,
    MSG_MISC_OEM_GET_MSL_CODE_DONE,
    MSG_MISC_OEM_SET_PIN_CONTROL,
    MSG_MISC_OEM_SET_PIN_CONTROL_DONE,
    MSG_MISC_OEM_GET_MANUAL_BAND_MODE,
    MSG_MISC_OEM_GET_MANUAL_BAND_MODE_DONE,
    MSG_MISC_OEM_SET_MANUAL_BAND_MODE,
    MSG_MISC_OEM_SET_MANUAL_BAND_MODE_DONE,
    MSG_MISC_OEM_GET_RF_DESENSE_MODE,
    MSG_MISC_OEM_GET_RF_DESENSE_MODE_DONE,
    MSG_MISC_OEM_SET_RF_DESENSE_MODE,
    MSG_MISC_OEM_SET_RF_DESENSE_MODE_DONE,
    MSG_MISC_OEM_STORE_ADB_SERIAL_NUMBER,
    MSG_MISC_OEM_STORE_ADB_SERIAL_NUMBER_DONE,
    MSG_MISC_OEM_READ_ADB_SERIAL_NUMBER,
    MSG_MISC_OEM_READ_ADB_SERIAL_NUMBER_DONE,
    MSG_MISC_OEM_SET_PREFERRED_CALL_CAPABILITY,
    MSG_MISC_OEM_SET_PREFERRED_CALL_CAPABILITY_DONE,
    MSG_MISC_OEM_GET_PREFERRED_CALL_CAPABILITY,
    MSG_MISC_OEM_GET_PREFERRED_CALL_CAPABILITY_DONE,

    MSG_MISC_AIMS_SEND_SMS_ACK,
    MSG_MISC_AIMS_SEND_SMS_ACK_DONE,
    MSG_MISC_AIMS_SEND_ACK_INCOMING_SMS,
    MSG_MISC_AIMS_SEND_ACK_INCOMING_SMS_DONE,
    MSG_MISC_AIMS_SEND_ACK_INCOMING_CDMA_SMS,
    MSG_MISC_AIMS_SEND_ACK_INCOMING_CDMA_SMS_DONE,

    MSG_MISC_PHONE_RESET,
    MSG_MISC_DATA_STATE_CHANGE,

    // moved from cs service
    MSG_MISC_DTMF_START,
    MSG_MISC_DTMF_START_DONE,
    MSG_MISC_DTMF,
    MSG_MISC_DTMF_DONE,
    MSG_MISC_DTMF_STOP,
    MSG_MISC_DTMF_STOP_DONE,

    // moved from sms service
    MSG_MISC_SMS_ACKNOWLEDGE,
    MSG_MISC_SMS_ACKNOWLEDGE_DONE,
    MSG_MISC_SMS_ACK_WITH_PDU,
    MSG_MISC_SMS_ACK_WITH_PDU_DONE,
    MSG_MISC_SMS_ACKNOWLEDGE_NOTI,

    MSG_MISC_OEM_FCRASH_MNR_REQ,

    MSG_MISC_GET_ACTIVITY_INFO,
    MSG_MISC_GET_ACTIVITY_INFO_DONE,

    // LCE (Link Capacity Estimation)
    MSG_MISC_LCE_START,
    MSG_MISC_LCE_START_DONE,
    MSG_MISC_LCE_STOP,
    MSG_MISC_LCE_STOP_DONE,
    MSG_MISC_PULL_LCEDATA,
    MSG_MISC_PULL_LCEDATA_DONE,
    MSG_MISC_LCEDATA_RECV,

    MSG_MISC_OEM_NOTIFY_CPCRASH,
    MSG_MISC_OEM_NOTIFY_SILENTRESET,

    MSG_MISC_OEM_SEND_SGC,
    MSG_MISC_OEM_SEND_SGC_DONE,

    MSG_MISC_SET_DEVICE_INFO,
    MSG_MISC_SET_DEVICE_INFO_DONE,

#ifdef SUPPORT_CDMA
    MSG_MISC_CDMA_GET_SUBSCRIPT_SOURCE,
    MSG_MISC_CDMA_SET_SUBSCRIPT_SOURCE,
    MSG_MISC_GET_CDMA_SUBSCRIPTION,
    MSG_MISC_GET_CDMA_SUBSCRIPTION_DONE,

    MSG_MISC_GET_HARDWARE_CONFIG,
    MSG_MISC_GET_HARDWARE_CONFIG_DONE,

    // moved from sms service
    MSG_MISC_SMS_CDMA_ACKNOWLEDGE,
    MSG_MISC_SMS_CDMA_ACKNOWLEDGE_DONE,
#endif // SUPPORT_CDMA

    MSG_MISC_SET_VOICE_OPERATION,
    MSG_MISC_SET_VOICE_OPERATION_DONE,

    MSG_MISC_SET_INDICATION_FILTER,
    MSG_MISC_SET_INDICATION_FILTER_DONE,

    MSG_MISC_GET_NEIGHBORING_CELL_IDS,
    MSG_MISC_SET_LOCATION_UPDATES,
    MSG_MISC_SET_LOCATION_UPDATES_DONE,

    MSG_MISC_SET_SUPP_SVC_NOTIFICATION,
    MSG_MISC_SET_SUPP_SVC_NOTIFICATION_DONE,
    MSG_MISC_SET_CARRIER_INFO_IMSI_ENCRYPTION,
    MSG_MISC_SET_CARRIER_INFO_IMSI_ENCRYPTION_DONE,
    MSG_MISC_SET_SIGNAL_STRENGTH_REPORTING_CRITERIA,
    MSG_MISC_SET_SIGNAL_STRENGTH_REPORTING_CRITERIA_DONE,
    MSG_MISC_SET_LINK_CAPACITY_REPORTING_CRITERIA,
    MSG_MISC_SET_LINK_CAPACITY_REPORTING_CRITERIA_DONE,
    MSG_MISC_IND_CURRENT_LINK_CAPACITY_ESTIMATE,
    MSG_MISC_IND_CARRIER_INFO_IMSI_ENCRYPTION,
    MSG_MISC_IND_HARDWARE_CONFIG_CHANGED,
    MSG_MISC_IND_CDMA_PRL_CHANGED,
    MSG_MISC_IND_MODEM_RESTART,

    MSG_MISC_SET_PSENSOR_STATUS,
    MSG_MISC_SET_PSENSOR_STATUS_DONE,
    MSG_MISC_SAR_CONTROL_STATE_IND,

    MSG_MISC_SET_SAR_STATE,
    MSG_MISC_SET_SAR_STATE_DONE,
    MSG_MISC_GET_SAR_STATE,
    MSG_MISC_GET_SAR_STATE_DONE,
    MSG_MISC_SAR_RF_CONNECTION_IND,

    MSG_MISC_SCAN_RSSI,
    MSG_MISC_SCAN_RSSI_DONE,
    MSG_MISC_SCAN_RSSI_RESULT_RECEIVED,

    MSG_MISC_FORWARDING_AT_COMMAND,
    MSG_MISC_FORWARDING_AT_COMMAND_DONE,
    MSG_MISC_UNSOL_AT_COMMAND,

    MSG_MISC_GET_PLMN_NAME_FROM_SE13TABLE,
    MSG_MISC_GET_LONG_PLMN_NAME_FROM_SE13TABLE,
    MSG_MISC_TS25TABLE_DUMP,

    MSG_MISC_OEM_GET_RADIO_NODE,
    MSG_MISC_OEM_GET_RADIO_NODE_DONE,
    MSG_MISC_OEM_SET_RADIO_NODE,
    MSG_MISC_OEM_SET_RADIO_NODE_DONE,
    MSG_MISC_OEM_GET_PROVISION_UPDATE_REQUEST,
    MSG_MISC_OEM_GET_PROVISION_UPDATE_REQUEST_DONE,
    MSG_MISC_OEM_SET_PROVISION_UPDATE_DONE_REQUEST,
    MSG_MISC_OEM_SET_PROVISION_UPDATE_DONE_REQUEST_DONE,
    MSG_MISC_OEM_RADIO_CONFIG_RESET,
    MSG_MISC_OEM_RADIO_CONFIG_RESET_DONE,

    MSG_MISC_GET_PHONE_CAPABILITY,
    MSG_MISC_GET_PHONE_CAPABILITY_DONE,
    MSG_MISC_SET_MODEMS_CONFIG,
    MSG_MISC_SET_MODEMS_CONFIG_DONE,
    MSG_MISC_GET_MODEMS_CONFIG,
    MSG_MISC_GET_MODEMS_CONFIG_DONE,
    MSG_MISC_ENABLE_MODEM,
    MSG_MISC_ENABLE_MODEM_DONE,
    MSG_MISC_GET_MODEM_STACK_STATUS,
    MSG_MISC_GET_MODEM_STACK_STATUS_DONE,
    MSG_MISC_SET_ACTIVATE_VSIM,
    MSG_MISC_SET_ACTIVATE_VSIM_DONE,

    MSG_MISC_OEM_SET_SELFLOG,
    MSG_MISC_OEM_SET_SELFLOG_DONE,
    MSG_MISC_OEM_GET_SELFLOG_STATUS,
    MSG_MISC_OEM_GET_SELFLOG_STATUS_DONE,
    MSG_MISC_UNSOL_SELFLOG_STATUS,
    MSG_MISC_OEM_MODEM_INFO,
    MSG_MISC_OEM_MODEM_INFO_DONE,
    MSG_MISC_OEM_MODEM_INFO_RECEIVED,
    MSG_MISC_OEM_MODEM_RESET,
    MSG_MISC_OEM_MODEM_RESET_DONE,
    MSG_MISC_OEM_SET_RTP_PKTLOSS_THRESHOLD,
    MSG_MISC_OEM_SET_RTP_PKTLOSS_THRESHOLD_DONE,
    MSG_MISC_OEM_RTP_PKTLOSS_THRESHOLD_RECEIVED,
    MSG_MISC_OEM_SET_FUNC_SWITCH_REQ,
    MSG_MISC_OEM_SET_FUNC_SWITCH_REQ_DONE,
    MSG_MISC_OEM_SET_PDCP_DISCARD_TIMER,
    MSG_MISC_OEM_SET_PDCP_DISCARD_TIMER_DONE,
    MSG_MISC_OEM_GET_CQI_INFO,
    MSG_MISC_OEM_GET_CQI_INFO_DONE,
    MSG_MISC_OEM_SET_SAR_SETTING,
    MSG_MISC_OEM_SET_SAR_SETTING_DONE,
    MSG_MISC_SET_IMS_TEST_MODE,
    MSG_MISC_SET_IMS_TEST_MODE_DONE,
    MSG_MISC_OEM_SET_GMO_SWITCH,
    MSG_MISC_OEM_SET_GMO_SWITCH_DONE,
    MSG_MISC_OEM_SET_TCS_FCI_REQ,
    MSG_MISC_OEM_SET_TCS_FCI_REQ_DONE,
    MSG_MISC_OEM_GET_TCS_FCI_INFO,
    MSG_MISC_OEM_GET_TCS_FCI_INFO_DONE,
    MSG_MISC_OEM_SET_CA_BW_FILTER,
    MSG_MISC_OEM_SET_CA_BW_FILTER_DONE,
    MSG_MISC_OEM_CA_BW_FILTER_IND,
    MSG_MISC_SET_MODEM_LOG_DUMP,
    MSG_MISC_SET_MODEM_LOG_DUMP_DONE,
    MSG_MISC_OEM_SET_ELEVATOR_SENSOR,
    MSG_MISC_OEM_SET_ELEVATOR_SENSOR_DONE,
    MSG_MISC_SET_UICC,
    MSG_MISC_SET_UICC_DONE,
    MSG_MISC_UICC_STATUS_CHANGED,
    MSG_MISC_OEM_IND_NTW_ENDC_CAPABILITY,
    MSG_MISC_OEM_SET_SELFLOG_PROFILE,
    MSG_MISC_OEM_SET_SELFLOG_PROFILE_DONE,
    MSG_MISC_OEM_SET_FORBID_LTE_CELL,
    MSG_MISC_OEM_SET_FORBID_LTE_CELL_DONE,
};

/**
 * CSmsService
 */
enum CSmsServiceMsgId {
    MSG_SMS_SEND = MSG_SMS_BASE + 1,
    MSG_SMS_SEND_MORE,
    MSG_SMS_SEND_DONE,
    MSG_SMS_ACKNOWLEDGE,
    MSG_SMS_ACKNOWLEDGE_DONE,
    MSG_SMS_WRITE_SMS_TO_SIM,
    MSG_SMS_WRITE_SMS_TO_SIM_DONE,
    MSG_SMS_DELETE_SMS_ON_SIM,
    MSG_SMS_DELETE_SMS_ON_SIM_DONE,
    MSG_SMS_GET_BROADCAST_SMS_CONFIG,
    MSG_SMS_GET_BROADCAST_SMS_CONFIG_DONE,
    MSG_SMS_SET_BROADCAST_SMS_CONFIG,
    MSG_SMS_SET_BROADCAST_SMS_CONFIG_DONE,
    MSG_SMS_BROADCAST_ACTIVATION,
    MSG_SMS_BROADCAST_ACTIVATION_DONE,
    MSG_SMS_GET_SMSC_ADDRESS,
    MSG_SMS_GET_SMSC_ADDRESS_DONE,
    MSG_SMS_SET_SMSC_ADDRESS,
    MSG_SMS_SET_SMSC_ADDRESS_DONE,
    MSG_SMS_REPORT_SMS_MEMORY_STATUS,
    MSG_SMS_REPORT_SMS_MEMORY_STATUS_DONE,
    MSG_SMS_ACK_WITH_PDU,
    MSG_SMS_ACK_WITH_PDU_DONE,

    MSG_SMS_INCOMING_NEW_SMS,
    MSG_SMS_INCOMING_NEW_SMS_STATUS_REPORT,
    MSG_SMS_INCOMING_NEW_SMS_ON_SIM,
    MSG_SMS_SIM_SMS_STORAGE_FULL,
    MSG_SMS_INCOMING_NEW_BROADCAST_SMS,

#ifdef SUPPORT_CDMA
    MSG_SMS_CDMA_SEND,
    MSG_SMS_CDMA_SEND_DONE,
    MSG_SMS_CDMA_GET_BROADCAST_SMS_CONFIG,
    MSG_SMS_CDMA_GET_BROADCAST_SMS_CONFIG_DONE,
    MSG_SMS_CDMA_SET_BROADCAST_SMS_CONFIG,
    MSG_SMS_CDMA_SET_BROADCAST_SMS_CONFIG_DONE,
    MSG_SMS_CDMA_BROADCAST_ACTIVATION,
    MSG_SMS_CDMA_BROADCAST_ACTIVATION_DONE,
    MSG_SMS_CDMA_WRITE_SMS_TO_RUIM,
    MSG_SMS_CDMA_WRITE_SMS_TO_RUIM_DONE,
    MSG_SMS_CDMA_DELETE_SMS_ON_RUIM,
    MSG_SMS_CDMA_DELETE_SMS_ON_RUIM_DONE,

    MSG_SMS_CDMA_INCOMING_NEW_SMS,
    MSG_SMS_CDMA_RUIM_SMS_STORAGE_FULL,

    MSG_SMS_CDMA_VOICE_MSG_WAITING_INFO,
#endif // SUPPORT_CDMA

    // moved from aims service
    MSG_SMS_AIMS_SEND_SMS,
    MSG_SMS_AIMS_SEND_SMS_DONE,
    MSG_SMS_AIMS_SEND_EXPECT_MORE,
    MSG_SMS_AIMS_SEND_EXPECT_MORE_DONE,

    MSG_SMS_SEND_NOTI,
    MSG_SMS_GET_STORAGE_CAPACITY,
    MSG_SMS_GET_STORAGE_CAPACITY_DONE,
};

/**
 * CAudioService
 */
enum CAudioServiceMsgId {
    MSG_AUDIO_SET_VOLUME = MSG_AUDIO_BASE + 1,
    MSG_AUDIO_SET_VOLUME_DONE,
    MSG_AUDIO_GET_VOLUME,
    MSG_AUDIO_GET_VOLUME_DONE,
    MSG_AUDIO_SET_AUDIOPATH,
    MSG_AUDIO_SET_AUDIOPATH_DONE,
    MSG_AUDIO_GET_AUDIOPATH,
    MSG_AUDIO_GET_AUDIOPATH_DONE,
    MSG_AUDIO_SET_MULTIMIC,
    MSG_AUDIO_SET_MULTIMIC_DONE,
    MSG_AUDIO_GET_MULTIMIC,
    MSG_AUDIO_GET_MULTIMIC_DONE,
    MSG_AUDIO_SET_AUDIO_CLOCK,
    MSG_AUDIO_SET_AUDIO_CLOCK_DONE,
    MSG_AUDIO_SET_AUDIO_LOOPBACK,
    MSG_AUDIO_SET_AUDIO_LOOPBACK_DONE,
    MSG_AUDIO_SET_TTY_MODE,
    MSG_AUDIO_SET_TTY_MODE_DONE,
    MSG_AUDIO_WB_AMR_REPORT_NTF,
    MSG_AUDIO_WB_AMR_SET_CAPABILITY,
    MSG_AUDIO_WB_AMR_SET_CAPABILITY_DONE,
    MSG_AUDIO_WB_AMR_GET_CAPABILITY,
    MSG_AUDIO_WB_AMR_GET_CAPABILITY_DONE,
};

/**
 * CImsService
 */
enum CImsServiceMsgId {
    MSG_IMS_SET_CONF = MSG_IMS_BASE + 1,
    MSG_IMS_SET_CONF_DONE,
    MSG_IMS_GET_CONF,
    MSG_IMS_GET_CONF_DONE,
    MSG_IMS_SIM_AUTH,
    MSG_IMS_SIM_AUTH_DONE,
    MSG_IMS_SET_ERERGENCY_CALL_STATUS,
    MSG_IMS_SET_ERERGENCY_CALL_STATUS_DONE,
    MSG_IMS_SET_SRVCC_CALL_LIST,
    MSG_IMS_SET_SRVCC_CALL_LIST_DONE,
    MSG_IMS_CONFIG,
    MSG_IMS_DEDICATED_PDN_INFO,
    MSG_IMS_EMERGENCY_ACT_INFO,
    MSG_IMS_SET_SRVCC_INFO,
    MSG_IMS_EMERGENCY_CALL_LIST,
    MSG_IMS_GET_GBA_AUTH,
    MSG_IMS_GET_GBA_AUTH_DONE,

    //AIMS support start ---------------------
    MSG_AIMS_DIAL,
    MSG_AIMS_DIAL_DONE,
    MSG_AIMS_ANSWER,
    MSG_AIMS_ANSWER_DONE,
    MSG_AIMS_HANGUP,
    MSG_AIMS_HANGUP_DONE,
    MSG_AIMS_DEREGISTRATION,
    MSG_AIMS_DEREGISTRATION_DONE,
    MSG_AIMS_HIDDEN_MENU,
    MSG_AIMS_HIDDEN_MENU_DONE,
    MSG_AIMS_ADD_PDN_INFO,
    MSG_AIMS_ADD_PDN_INFO_DONE,
    MSG_AIMS_CALL_MANAGE,
    MSG_AIMS_CALL_MANAGE_DONE,
    MSG_AIMS_SEND_DTMF,
    MSG_AIMS_SEND_DTMF_DONE,
    MSG_AIMS_SET_FRAME_TIME,
    MSG_AIMS_SET_FRAME_TIME_DONE,
    MSG_AIMS_GET_FRAME_TIME,
    MSG_AIMS_GET_FRAME_TIME_DONE,
    MSG_AIMS_CALL_MODIFY,
    MSG_AIMS_CALL_MODIFY_DONE,
    MSG_AIMS_RESPONSE_CALL_MODIFY,
    MSG_AIMS_RESPONSE_CALL_MODIFY_DONE,
    MSG_AIMS_TIME_INFO,
    MSG_AIMS_TIME_INFO_DONE,
    MSG_AIMS_CONF_CALL_ADD_REMOVE_USER,
    MSG_AIMS_CONF_CALL_ADD_REMOVE_USER_DONE,
    MSG_AIMS_ENHANCED_CONF_CALL,
    MSG_AIMS_ENHANCED_CONF_CALL_DONE,
    MSG_AIMS_GET_CALL_FORWARD_STATUS,
    MSG_AIMS_GET_CALL_FORWARD_STATUS_DONE,
    MSG_AIMS_SET_CALL_FORWARD_STATUS,
    MSG_AIMS_SET_CALL_FORWARD_STATUS_DONE,
    MSG_AIMS_GET_CALL_WAITING,
    MSG_AIMS_GET_CALL_WAITING_DONE,
    MSG_AIMS_SET_CALL_WAITING,
    MSG_AIMS_SET_CALL_WAITING_DONE,
    MSG_AIMS_GET_CALL_BARRING,
    MSG_AIMS_GET_CALL_BARRING_DONE,
    MSG_AIMS_SET_CALL_BARRING,
    MSG_AIMS_SET_CALL_BARRING_DONE,
    MSG_AIMS_CHG_BARRING_PWD,
    MSG_AIMS_CHG_BARRING_PWD_DONE,
    MSG_AIMS_SEND_USSD_INFO,
    MSG_AIMS_SEND_USSD_INFO_DONE,
    MSG_AIMS_GET_PRESENTATION_SETTINGS,
    MSG_AIMS_GET_PRESENTATION_SETTINGS_DONE,
    MSG_AIMS_SET_PRESENTATION_SETTINGS,
    MSG_AIMS_SET_PRESENTATION_SETTINGS_DONE,
    MSG_AIMS_SET_SELF_CAPABILITY,
    MSG_AIMS_SET_SELF_CAPABILITY_DONE,
    MSG_AIMS_HO_TO_WIFI_READY,
    MSG_AIMS_HO_TO_WIFI_READY_DONE,
    MSG_AIMS_HO_TO_WIFI_CANCEL_IND,
    MSG_AIMS_PAYLOAD_INFO_IND,
    MSG_AIMS_HO_TO_3GPP,
    MSG_AIMS_HO_TO_3GPP_DONE,
    MSG_AIMS_MEDIA_STATE_IND,
    MSG_AIMS_GET_REGISTRATION,
    MSG_AIMS_DEL_PDN_INFO,
    MSG_AIMS_DEL_PDN_INFO_DONE,
    MSG_AIMS_STACK_START_REQ,
    MSG_AIMS_STACK_START_REQ_DONE,
    MSG_AIMS_STACK_STOP_REQ,
    MSG_AIMS_STACK_STOP_REQ_DONE,
    MSG_AIMS_XCAPM_START_REQ,
    MSG_AIMS_XCAPM_START_REQ_DONE,
    MSG_AIMS_XCAPM_STOP_REQ,
    MSG_AIMS_XCAPM_STOP_REQ_DONE,
    MSG_AIMS_RTT_SEND_TEXT,
    MSG_AIMS_RTT_SEND_TEXT_DONE,
    MSG_AIMS_EXIT_EMERGENCY_CB_MODE,
    MSG_AIMS_EXIT_EMERGENCY_CB_MODE_DONE,
    MSG_AIMS_SET_GEO_LOCATION_INFO,
    MSG_AIMS_SET_GEO_LOCATION_INFO_DONE,
    MSG_AIMS_CDMA_SEND_SMS,
    MSG_AIMS_CDMA_SEND_SMS_DONE,
    MSG_AIMS_RCS_MULTI_FRAME_REQ,
    MSG_AIMS_RCS_MULTI_FRAME_REQ_DONE,
    MSG_AIMS_RCS_CHAT_REQ,
    MSG_AIMS_RCS_CHAT_REQ_DONE,
    MSG_AIMS_RCS_GROUP_CHAT_REQ,
    MSG_AIMS_RCS_GROUP_CHAT_REQ_DONE,
    MSG_AIMS_RCS_OFFLINE_MODE_REQ,
    MSG_AIMS_RCS_OFFLINE_MODE_REQ_DONE,
    MSG_AIMS_RCS_FILE_TRANSFER_REQ,
    MSG_AIMS_RCS_FILE_TRANSFER_REQ_DONE,
    MSG_AIMS_RCS_COMMON_MESSAGE_REQ,
    MSG_AIMS_RCS_COMMON_MESSAGE_REQ_DONE,
    MSG_AIMS_RCS_CONTENT_SHARE_REQ,
    MSG_AIMS_RCS_CONTENT_SHARE_REQ_DONE,
    MSG_AIMS_RCS_PRESENCE_REQ,
    MSG_AIMS_RCS_PRESENCE_REQ_DONE,
    MSG_AIMS_XCAP_MANAGE_REQ,
    MSG_AIMS_XCAP_MANAGE_REQ_DONE,
    MSG_AIMS_RCS_CONFIG_MANAGE_REQ,
    MSG_AIMS_RCS_CONFIG_MANAGE_REQ_DONE,
    MSG_AIMS_RCS_TLS_MANAGE_REQ,
    MSG_AIMS_RCS_TLS_MANAGE_REQ_DONE,
    MSG_AIMS_SET_PDN_EST_STATUS,
    MSG_AIMS_SET_PDN_EST_STATUS_DONE,
    MSG_AIMS_SET_HIDDEN_MENU_ITEM,
    MSG_AIMS_SET_HIDDEN_MENU_ITEM_DONE,
    MSG_AIMS_GET_HIDDEN_MENU_ITEM,
    MSG_AIMS_GET_HIDDEN_MENU_ITEM_DONE,
    MSG_AIMS_SET_RTP_RX_STATISTICS,
    MSG_AIMS_SET_RTP_RX_STATISTICS_DONE,

    MSG_IND_AIMS_CALL_RING,
    MSG_IND_AIMS_CALL_STATUS,
    MSG_IND_AIMS_REGISTRATION,
    MSG_IND_AIMS_CALL_MODIFY,
    MSG_IND_AIMS_FRAME_TIME,
    MSG_IND_AIMS_SUPP_SVC_NOTIFICATION,
    MSG_IND_AIMS_NEW_SMS,
    MSG_IND_AIMS_NEW_SMS_STATUS_REPORT,
    MSG_IND_AIMS_ON_USSD,
    MSG_IND_AIMS_CONFERENCE_CALL_EVENT,
    MSG_IND_AIMS_PAYLOAD_INFO,
    MSG_IND_AIMS_VOWIFI_HO_CALL_INFO,
    MSG_IND_AIMS_NEW_CDMA_SMS,
    MSG_IND_AIMS_RINGBACK_TONE,
    MSG_IND_AIMS_CALL_MANAGE,
    MSG_IND_AIMS_CONF_CALL_ADD_REMOVE_USER,
    MSG_IND_AIMS_ENHANCED_CONF_CALL,
    MSG_IND_AIMS_CALL_MODIFY_RSP,
    MSG_IND_AIMS_DTMF_EVENT,
    MSG_IND_AIMS_RTT_NEW_TEXT,
    MSG_IND_AIMS_RTT_FAIL_SENDING_TEXT,
    MSG_IND_AIMS_EXIT_EMERGENCY_CB_MODE,
    MSG_IND_AIMS_DIALOG_INFO,
    MSG_IND_AIMS_RCS_MULTI_FRAME,
    MSG_IND_AIMS_RCS_CHAT,
    MSG_IND_AIMS_RCS_GROUP_CHAT,
    MSG_IND_AIMS_RCS_OFFLINE_MODE,
    MSG_IND_AIMS_RCS_FILE_TRANSFER,
    MSG_IND_AIMS_RCS_COMMON_MESSAGE,
    MSG_IND_AIMS_RCS_CONTENT_SHARE,
    MSG_IND_AIMS_RCS_PRESENCE,
    MSG_IND_AIMS_RCS_XCAP_MANAGE,
    MSG_IND_AIMS_RCS_CONFIG_MANAGE,
    MSG_IND_AIMS_RCS_TLS_MANAGE,
    MSG_IND_AIMS_MEDIA_STATUS,
    MSG_IND_AIMS_SIP_MSG_INFO,
    MSG_IND_AIMS_VOICE_RTQ_QUALITY,
    MSG_IND_AIMS_RTP_RX_STATISTICS,
    //AIMS support end ---------------------

    MSG_WFC_MEDIA_CHANNEL_CONFIG,
    MSG_WFC_MEDIA_CHANNEL_CONFIG_DONE,
    MSG_WFC_DTMF_START,
    MSG_WFC_DTMF_START_DONE,
    MSG_IND_WFC_RTP_RTCP_TIMEOUT,
    MSG_IND_WFC_FIRST_RTP,
    MSG_IND_WFC_RTCP_RX_SR,
    MSG_IND_WFC_RCV_DTMF_NOTI,
    MSG_WFC_SET_VOWIFI_HO_THRESHOLD,
    MSG_WFC_SET_VOWIFI_HO_THRESHOLD_DONE,
};

/**
 * GpsService
 */
enum GpsServiceMsgId {
    MSG_GPS_SET_FREQUENCY_AIDING = MSG_GPS_BASE + 1,
    MSG_GPS_SET_FREQUENCY_AIDING_DONE,
    MSG_GPS_GET_LPP_SUPL_REQ_ECID_INFO,
    MSG_GPS_GET_LPP_SUPL_REQ_ECID_INFO_DONE,
    MSG_GPS_GET_RRLP_SUPL_REQ_ECID_INFO,
    MSG_GPS_GET_RRLP_SUPL_REQ_ECID_INFO_DONE,
    MSG_GPS_MO_LOCATION_REQUEST,
    MSG_GPS_MO_LOCATION_REQUEST_DONE,
    MSG_GPS_GET_LPP_REQ_SERVING_CELL_INFO,
    MSG_GPS_GET_LPP_REQ_SERVING_CELL_INFO_DONE,
    MSG_GPS_SET_SUPL_NI_READY ,             // From AP, To AP
    MSG_GPS_SET_SUPL_NI_READY_DONE,
    MSG_GPS_IND_MEASURE_POS_REQ,
    MSG_GPS_IND_MEASURE_POS_RSP,
    MSG_GPS_IND_ASSIST_DATA,
    MSG_GPS_IND_RELEASE_GPS,                // From AP, To AP
    MSG_GPS_IND_MT_LOCATION_REQUEST,        // From AP, To AP
    MSG_GPS_IND_RESET_GPS_ASSIST_DATA,
    MSG_GPS_IND_LPP_REQUEST_CAPABILITIES,
    MSG_GPS_LPP_PROVIDE_CAPABILITIES_IND,
    MSG_GPS_IND_LPP_REQUEST_ASSIST_DATA,
    MSG_GPS_IND_LPP_PROVIDE_ASSIST_DATA,
    MSG_GPS_IND_LPP_REQUEST_LOCATION_INFO,
    MSG_GPS_LPP_PROVIDE_LOCATION_INFO_IND,
    MSG_GPS_LPP_GPS_ERROR_IND,              // From AP, To AP
    MSG_GPS_IND_SUPL_LPP_DATA_INFO,         // From AP, To AP
    MSG_GPS_IND_SUPL_NI_MESSAGE,            // From AP, To AP
    MSG_GPS_GET_GSM_EXT_INFO_MSG,
    MSG_GPS_GET_GSM_EXT_INFO_MSG_DONE,
    MSG_GPS_CONTROL_PLANE_ENABLE,
    MSG_GPS_CONTROL_PLANE_ENABLE_DONE,
    MSG_GPS_GNSS_LPP_PROFILE_SET,
    MSG_GPS_GNSS_LPP_PROFILE_SET_DONE,
    MSG_GPS_START_MDT_LOC,
    MSG_GPS_RETRIEVE_LOC_INFO,
    MSG_GPS_IND_LPP_UPDATE_UE_LOC_INFO,
    MSG_GPS_IND_GPS_LOCK_MODE,
    // CDMA & HEDGE GANSS
    MSG_GPS_SET_GANSS_MEAS_POS_RSP,
    MSG_GPS_SET_GANSS_MEAS_POS_RSP_DONE,
    MSG_GPS_SET_GPS_LOCK_MODE,
    MSG_GPS_SET_GPS_LOCK_MODE_DONE,
    MSG_GPS_GET_REFERENCE_LOCATION,
    MSG_GPS_GET_REFERENCE_LOCATION_DONE,
    MSG_GPS_SET_PSEUDO_RANGE_MEASUREMENTS,
    MSG_GPS_SET_PSEUDO_RANGE_MEASUREMENTS_DONE,
    MSG_GPS_GET_CDMA_PRECISE_TIME_AIDING_INFO,
    MSG_GPS_GET_CDMA_PRECISE_TIME_AIDING_INFO_DONE,
    MSG_GPS_IND_3GPP_SEND_GANSS_ASSIT_DATA,
    MSG_GPS_IND_GANSS_MEAS_POS_MSG,
    MSG_GPS_IND_CDMA_GPS_POWER_ON,
    MSG_GPS_IND_CDMA_SEND_ACQUSITION_ASSIT_DATA,
    MSG_GPS_IND_CDMA_SESSION_CANCELLATION,
    MSG_GPS_IND_GANSS_AP_POS_CAP_RSP,
    MSG_GPS_IND_GANSS_AP_POS_CAP_REQ,
    MSG_GPS_CDMA_FREQ_AIDING,
    MSG_GPS_CDMA_FREQ_AIDING_DONE,
};

/**
 * WLanService
 */
enum WLanServiceMsgId {
    MSG_WLAN_GET_IMSI = MSG_WLAN_BASE + 1,
    MSG_WLAN_SIM_AUTHENTICATE,
    MSG_WLAN_SIM_AUTHENTICATE_DONE
};

/**
 * Virtual SIM Service
 */
enum VsimServiceMsgId {
    MSG_VSIM_NOTIFICATION = MSG_VSIM_BASE + 1,
    MSG_VSIM_NOTIFICATION_DONE,
    MSG_VSIM_OPERATION,
    MSG_VSIM_OPERATION_DONE,

    MSG_VSIM_OPERATION_IND,
};

/**
 * Debug Service
 */
enum {
    MSG_DEBUG_TRIGGER_IND = MSG_DEBUG_BASE + 1,
};

/**
 * StkService
 */
enum StkServiceMsgId {
    MSG_SAT_STK_IS_RUNNING = MSG_STK_BASE + 1,
    MSG_SAT_SEND_ENVELOPE_CMD,
    MSG_SAT_SEND_ENVELOPE_CMD_DONE,
    MSG_SAT_SEND_TERMINAL_RSP,
    MSG_SAT_SEND_TERMINAL_RSP_DONE,
    MSG_SAT_SEND_ENVELOPE_STATUS,
    MSG_SAT_SEND_ENVELOPE_STATUS_DONE,

    MSG_SAT_PROACTIVE_COMMAND,
    MSG_SAT_SIM_REFRESH,

    MSG_SAT_STK_HANDLE_CALL_SETUP_REQ_FROM_SIM,
    MSG_SAT_STK_HANDLE_CALL_SETUP_REQ_FROM_SIM_DONE,

    MSG_SAT_STK_SESSION_END,
    MSG_SAT_STK_EVENT_NOTIFY,
    MSG_SAT_STK_CALL_SETUP,

    MSG_SAT_STK_CC_ALPHA_NOTIFY,
};

/**
* eMBMS SIM Service
*/
enum CEmbmsServiceMsgId {
    MSG_EMBMS_ENABLE_SERVICE = MSG_EMBMS_BASE + 1,
    MSG_EMBMS_ENABLE_SERVICE_DONE,
    MSG_EMBMS_DISABLE_SERVICE,
    MSG_EMBMS_DISABLE_SERVICE_DONE,
    MSG_EMBMS_SET_SESSION,      // 5
    MSG_EMBMS_SET_SESSION_DONE,
    MSG_EMBMS_UNSOL_COVERAGE,
    MSG_EMBMS_GET_SESSION_LIST,
    MSG_EMBMS_GET_SESSION_LIST_DONE,
    MSG_EMBMS_GET_SIGNAL_STRENGTH,      // 10
    MSG_EMBMS_GET_SIGNAL_STRENGTH_DONE,
    MSG_EMBMS_UNSOL_SIGNAL_STRENGTH,
    MSG_EMBMS_GET_NETWORK_TIME,
    MSG_EMBMS_GET_NETWORK_TIME_DONE,
    MSG_EMBMS_UNSOL_NETWORK_TIME,   // 15
    MSG_EMBMS_UNSOL_SAI_LIST,
    MSG_EMBMS_UNSOL_GLOBAL_CELL_ID,
    MSG_EMBMS_UNSOL_SESSION_LIST_UPDATE,
    MSG_EMBMS_CHECK_AVAIABLE_EMBMS,
    MSG_EMBMS_CHECK_AVAIABLE_EMBMS_DONE,
};

#endif /* __MESSAGE_ID_H__ */
