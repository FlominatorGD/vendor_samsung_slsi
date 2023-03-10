/*
 * Copyright Samsung Electronics Co., LTD.
 *
 * This software is proprietary of Samsung Electronics.
 * No part of this software, either material or conceptual may be copied or distributed, transmitted,
 * transcribed, stored in a retrieval system or translated into any human or computer language in any form by any means,
 * electronic, mechanical, manual or otherwise, or disclosed
 * to third parties without the express written permission of Samsung Electronics.
 */

#ifndef __RIL_PROTOCOL_UNSOL_COMMANDS_H__
#define __RIL_PROTOCOL_UNSOL_COMMANDS_H__

/*
 * protocol_unsol_commands.h
 *
 *  Created on: 2014. 7. 11.
 *      Author: sungwoo48.choi
 */
#include "sitdef.h"
#include <map>

using namespace std;
typedef std::map<UINT, std::pair<UINT, UINT>> RouteMap;

RouteMap s_ProtocolServiceMap = {
    { SIT_IND_NEW_SMS, std::make_pair(RIL_SERVICE_SMS, MSG_SMS_INCOMING_NEW_SMS ) },
    { SIT_IND_NEW_SMS_STATUS_REPORT, std::make_pair(RIL_SERVICE_SMS, MSG_SMS_INCOMING_NEW_SMS_STATUS_REPORT ) },
    { SIT_IND_NEW_SMS_ON_SIM, std::make_pair(RIL_SERVICE_SMS, MSG_SMS_INCOMING_NEW_SMS_ON_SIM ) },
    { SIT_IND_SIM_SMS_STORAGE_FULL, std::make_pair(RIL_SERVICE_SMS, MSG_SMS_SIM_SMS_STORAGE_FULL ) },
    { SIT_IND_NEW_BCST_SMS, std::make_pair(RIL_SERVICE_SMS, MSG_SMS_INCOMING_NEW_BROADCAST_SMS ) },
    { SIT_IND_SIM_STATUS_CHANGED, std::make_pair(RIL_SERVICE_SIM, MSG_SIM_STATUS_CHANGED ) },
    { SIT_IND_STK_PROACTIVE_COMMAND, std::make_pair(RIL_SERVICE_STK, MSG_SAT_PROACTIVE_COMMAND ) },
    { SIT_IND_STK_SESSION_END, std::make_pair(RIL_SERVICE_STK, MSG_SAT_STK_SESSION_END ) },
    { SIT_IND_SIM_REFRESH, std::make_pair(RIL_SERVICE_STK, MSG_SAT_SIM_REFRESH ) },
    { SIT_IND_SIM_PB_READY, std::make_pair(RIL_SERVICE_SIM, MSG_SIM_PB_READY ) },
    { SIT_IND_ON_USSD, std::make_pair(RIL_SERVICE_SUPPLEMENTARY, MSG_SS_USSD_NTF ) },
    { SIT_IND_SUPP_SVC_NOTIFICATION, std::make_pair(RIL_SERVICE_SUPPLEMENTARY, MSG_SS_SVC_NTF ) },
    { SIT_IND_SS_RETURN_RESULT, std::make_pair(RIL_SERVICE_STK, MSG_CS_SS_RETURN_RESULT_NTF ) },
    { SIT_IND_DATA_CALL_LIST_CHANGED, std::make_pair(RIL_SERVICE_PS, MSG_PS_DATA_CALL_LIST_CHANGED ) },
    { SIT_IND_NTW_STATE_CHANGED, std::make_pair(RIL_SERVICE_NETWORK, MSG_NET_NETWORK_STATE_CHANGED ) },
    { SIT_IND_RADIO_STATE_CHANGED, std::make_pair(RIL_SERVICE_NETWORK, MSG_NET_RADIO_STATE_CHANGED ) },
    { SIT_IND_RADIO_READY, std::make_pair(RIL_SERVICE_NETWORK, MSG_NET_RADIO_READY ) },
    { SIT_IND_NITZ_TIME_RECEIVED, std::make_pair(RIL_SERVICE_MISC, MSG_MISC_UNSOL_NITZ_TIME_RECEIVED ) },
    { SIT_IND_SIGNAL_STRENGTH, std::make_pair(RIL_SERVICE_MISC, MSG_MISC_UNSOL_SIGNAL_STRENGTH ) },
    { SIT_IND_IMS_CONFIGURATION, std::make_pair(RIL_SERVICE_IMS, MSG_IMS_CONFIG ) },
    { SIT_IND_IMS_DEDICATED_PDN, std::make_pair(RIL_SERVICE_IMS, MSG_IMS_DEDICATED_PDN_INFO ) },
    { SIT_IND_RINGBACK_TONE, std::make_pair(RIL_SERVICE_CSC, MSG_CS_SOUND_RINGBACKTONE_NTF ) },
    { SIT_IND_CALL_STATE_CHANGED, std::make_pair(RIL_SERVICE_CSC, MSG_CS_CALL_STATE_CHANGE_NTF) },
    { SIT_IND_EMERGENCY_CALL_LIST, std::make_pair(RIL_SERVICE_CSC, MSG_NET_EMERGENCY_CALL_LIST_RECEIVED) },
    { SIT_IND_CALL_RING, std::make_pair(RIL_SERVICE_CSC, MSG_CS_CALL_RINGING_NTF) },
    { SIT_IND_CELL_INFO_LIST, std::make_pair(RIL_SERVICE_NETWORK, MSG_NET_CELL_INFO_LIST_RECEIVED) },
    { SIT_IND_DEDICATED_BEARER_INFO, std::make_pair(RIL_SERVICE_PS, MSG_PS_DEDICATED_BEARER_INFO_UPDATED) },
    { SIT_IND_NAS_TIMER_STATUS, std::make_pair(RIL_SERVICE_PS, MSG_PS_NAS_TIMER_STATUS_CHANGED) },
    { SIT_IND_SRVCC_HO, std::make_pair(RIL_SERVICE_IMS, MSG_IMS_SET_SRVCC_INFO ) },

    { SIT_IND_GPS_MEASURE_POS_REQ, std::make_pair(RIL_SERVICE_GPS, MSG_GPS_IND_MEASURE_POS_REQ ) },
    { SIT_IND_GPS_ASSIST_DATA, std::make_pair(RIL_SERVICE_GPS, MSG_GPS_IND_ASSIST_DATA ) },
    { SIT_IND_RELEASE_GPS, std::make_pair(RIL_SERVICE_GPS, MSG_GPS_IND_RELEASE_GPS ) },
    { SIT_IND_GPS_MT_LOCATION_REQUEST, std::make_pair(RIL_SERVICE_GPS, MSG_GPS_IND_MT_LOCATION_REQUEST ) },
    { SIT_IND_RESET_GPS_ASSIST_DATA, std::make_pair(RIL_SERVICE_GPS, MSG_GPS_IND_RESET_GPS_ASSIST_DATA ) },
    { SIT_IND_LPP_REQUEST_CAPABILITIES, std::make_pair(RIL_SERVICE_GPS, MSG_GPS_IND_LPP_REQUEST_CAPABILITIES ) },
    { SIT_IND_LPP_PROVIDE_ASSIST_DATA, std::make_pair(RIL_SERVICE_GPS, MSG_GPS_IND_LPP_PROVIDE_ASSIST_DATA ) },
    { SIT_IND_LPP_REQUEST_LOCATION_INFO, std::make_pair(RIL_SERVICE_GPS, MSG_GPS_IND_LPP_REQUEST_LOCATION_INFO ) },
    { SIT_LPP_GPS_ERROR_IND, std::make_pair(RIL_SERVICE_GPS, MSG_GPS_LPP_GPS_ERROR_IND ) },
    { SIT_IND_SUPL_LPP_DATA_INFO, std::make_pair(RIL_SERVICE_GPS, MSG_GPS_IND_SUPL_LPP_DATA_INFO ) },
    { SIT_IND_SUPL_NI_MESSAGE, std::make_pair(RIL_SERVICE_GPS, MSG_GPS_IND_SUPL_NI_MESSAGE ) },
    { SIT_SET_GPS_SUPL_NI_READY, std::make_pair(RIL_SERVICE_GPS, MSG_GPS_SET_SUPL_NI_READY ) },
    { SIT_IND_GPS_START_MDT_LOC, std::make_pair(RIL_SERVICE_GPS, MSG_GPS_START_MDT_LOC ) },
    { SIT_IND_LPP_UPDATE_UE_LOC_INFO, std::make_pair(RIL_SERVICE_GPS, MSG_GPS_IND_LPP_UPDATE_UE_LOC_INFO ) },
    { SIT_IND_3GPP_SEND_GANSS_ASSIT_DATA, std::make_pair(RIL_SERVICE_GPS, MSG_GPS_IND_3GPP_SEND_GANSS_ASSIT_DATA ) },
    { SIT_IND_GANSS_MEAS_POS_MSG, std::make_pair(RIL_SERVICE_GPS, MSG_GPS_IND_GANSS_MEAS_POS_MSG ) },
    { SIT_IND_CDMA_GPS_POWER_ON, std::make_pair(RIL_SERVICE_GPS, MSG_GPS_IND_CDMA_GPS_POWER_ON ) },
    { SIT_IND_CDMA_SEND_ACQUSITION_ASSIT_DATA, std::make_pair(RIL_SERVICE_GPS, MSG_GPS_IND_CDMA_SEND_ACQUSITION_ASSIT_DATA ) },
    { SIT_IND_CDMA_SESSION_CANCELLATION, std::make_pair(RIL_SERVICE_GPS, MSG_GPS_IND_CDMA_SESSION_CANCELLATION ) },
    { SIT_IND_GANSS_AP_POS_CAP_REQ, std::make_pair(RIL_SERVICE_GPS, MSG_GPS_IND_GANSS_AP_POS_CAP_REQ ) },
    { SIT_IND_GPS_LOCK_MODE, std::make_pair(RIL_SERVICE_GPS, MSG_GPS_IND_GPS_LOCK_MODE ) },

    { SIT_IND_DISPLAY_ENG, std::make_pair(RIL_SERVICE_MISC, MSG_MISC_UNSOL_OEM_DISPLAY_ENG ) },
    { SIT_IND_PIN_CONTROL, std::make_pair(RIL_SERVICE_MISC, MSG_MISC_UNSOL_OEM_PIN_CONTROL) },
    { SIT_IND_PHONE_RESET, std::make_pair(RIL_SERVICE_MISC, MSG_MISC_PHONE_RESET) },
    { SIT_IND_CALL_PRESENT_IND, std::make_pair(RIL_SERVICE_CSC, MSG_CS_CALL_PRESENT_NTF) },
    { SIT_IND_WB_AMR_REPORT, std::make_pair(RIL_SERVICE_AUDIO, MSG_AUDIO_WB_AMR_REPORT_NTF ) },
    { SIT_IND_EMERGENCY_ACT_INFO, std::make_pair(RIL_SERVICE_NETWORK, MSG_NET_EMERGENCY_ACT_INFO_RECEIVED ) },
    { SIT_IND_DATA_STATE_CHANGE, std::make_pair(RIL_SERVICE_MISC, MSG_MISC_DATA_STATE_CHANGE) },
    { SIT_IND_TOTAL_OOS, std::make_pair(RIL_SERVICE_NETWORK, MSG_NET_IND_TOTAL_OOS) },
    { SIT_IND_MCC,std::make_pair(RIL_SERVICE_NETWORK, MSG_NET_IND_MCC) },
    { SIT_IND_ICCID_INFO, std::make_pair(RIL_SERVICE_SIM, MSG_SIM_ICCID_INFO ) },
    { SIT_IND_EMERGENCY_SUPPORT_RAT_MODE, std::make_pair(RIL_SERVICE_CSC, MSG_CS_IND_EMERGENCY_SUPPORT_RAT_MODE ) },
    { SIT_IND_SIM_DATA_INFO, std::make_pair(RIL_SERVICE_NETWORK, MSG_NET_IND_SIM_FILE_INFO) },
    // Radio Config
    { SIT_IND_SIM_SLOT_STATUS_CHANGED, std::make_pair(RIL_SERVICE_SIM, MSG_SIM_SLOT_STATUS_CHANGED ) },

#ifdef SUPPORT_CDMA
    // Call & SS
    { SIT_IND_CDMA_INFO_REC, std::make_pair(RIL_SERVICE_CSC, MSG_CS_IND_CDMA_INFO_REC ) },
    { SIT_IND_CDMA_CALL_WAITING, std::make_pair(RIL_SERVICE_CSC, MSG_CS_SS_IND_CDMA_CALL_WAITING ) },
    { SIT_IND_OTA_PROVISION_STATUS, std::make_pair(RIL_SERVICE_CSC, MSG_CS_IND_CDMA_OTA_PROVISION_STATUS) },

    // SMS
    { SIT_IND_CDMA_NEW_SMS, std::make_pair(RIL_SERVICE_SMS, MSG_SMS_CDMA_INCOMING_NEW_SMS ) },
    { SIT_IND_CDMA_RUIM_SMS_STORAGE_FULL, std::make_pair(RIL_SERVICE_SMS, MSG_SMS_CDMA_RUIM_SMS_STORAGE_FULL ) },
    { SIT_IND_CDMA_VOICE_MSG_WAITING_INFO, std::make_pair(RIL_SERVICE_SMS, MSG_SMS_CDMA_VOICE_MSG_WAITING_INFO ) },
#endif // SUPPORT_CDMA

    //AIMS support start ---------------------
    { SIT_IND_AIMS_CALL_RING, std::make_pair(RIL_SERVICE_IMS, MSG_IND_AIMS_CALL_RING ) },
    { SIT_IND_AIMS_CALL_STATUS, std::make_pair(RIL_SERVICE_IMS, MSG_IND_AIMS_CALL_STATUS ) },
    { SIT_IND_AIMS_REGISTRATION, std::make_pair(RIL_SERVICE_IMS, MSG_IND_AIMS_REGISTRATION ) },
    { SIT_IND_AIMS_CALL_MODIFY, std::make_pair(RIL_SERVICE_IMS, MSG_IND_AIMS_CALL_MODIFY ) },
    { SIT_IND_AIMS_FRAME_TIME, std::make_pair(RIL_SERVICE_IMS, MSG_IND_AIMS_FRAME_TIME ) },
    { SIT_IND_AIMS_SUPP_SVC_NOTIFICATION, std::make_pair(RIL_SERVICE_IMS, MSG_IND_AIMS_SUPP_SVC_NOTIFICATION ) },
    { SIT_IND_AIMS_NEW_SMS, std::make_pair(RIL_SERVICE_IMS, MSG_IND_AIMS_NEW_SMS ) },
    { SIT_IND_AIMS_NEW_SMS_STATUS_REPORT, std::make_pair(RIL_SERVICE_IMS, MSG_IND_AIMS_NEW_SMS_STATUS_REPORT ) },
    { SIT_IND_AIMS_ON_USSD, std::make_pair(RIL_SERVICE_IMS, MSG_IND_AIMS_ON_USSD ) },
    { SIT_IND_AIMS_CONFERENCE_CALL_EVENT, std::make_pair(RIL_SERVICE_IMS, MSG_IND_AIMS_CONFERENCE_CALL_EVENT ) },
    { SIT_IND_AIMS_PAYLOAD_INFO_IND, std::make_pair(RIL_SERVICE_IMS, MSG_IND_AIMS_PAYLOAD_INFO ) },
    { SIT_IND_AIMS_VOWIFI_HO_CALL_INFO, std::make_pair(RIL_SERVICE_IMS, MSG_IND_AIMS_VOWIFI_HO_CALL_INFO ) },
    { SIT_IND_AIMS_NEW_CDMA_SMS, std::make_pair(RIL_SERVICE_IMS, MSG_IND_AIMS_NEW_CDMA_SMS ) },
    { SIT_IND_AIMS_RINGBACK_TONE, std::make_pair(RIL_SERVICE_IMS, MSG_IND_AIMS_RINGBACK_TONE ) },
    { SIT_IND_AIMS_CALL_MANAGE, std::make_pair(RIL_SERVICE_IMS, MSG_IND_AIMS_CALL_MANAGE) },
    { SIT_IND_AIMS_CONF_CALL_ADD_REMOVE_USER, std::make_pair(RIL_SERVICE_IMS, MSG_IND_AIMS_CONF_CALL_ADD_REMOVE_USER) },
    { SIT_IND_AIMS_ENHANCED_CONF_CALL, std::make_pair(RIL_SERVICE_IMS, MSG_IND_AIMS_ENHANCED_CONF_CALL) },
    { SIT_IND_AIMS_CALL_MODIFY_RSP, std::make_pair(RIL_SERVICE_IMS, MSG_IND_AIMS_CALL_MODIFY_RSP) },
    { SIT_IND_AIMS_DTMF_EVENT, std::make_pair(RIL_SERVICE_IMS, MSG_IND_AIMS_DTMF_EVENT) },
    { SIT_IND_AIMS_RTT_NEW_TEXT, std::make_pair(RIL_SERVICE_IMS, MSG_IND_AIMS_RTT_NEW_TEXT) },
    { SIT_IND_AIMS_RTT_FAIL_SENDING_TEXT, std::make_pair(RIL_SERVICE_IMS, MSG_IND_AIMS_RTT_FAIL_SENDING_TEXT) },
    { SIT_IND_AIMS_EXIT_EMERGENCY_CB_MODE, std::make_pair(RIL_SERVICE_IMS, MSG_IND_AIMS_EXIT_EMERGENCY_CB_MODE) },
    { SIT_IND_AIMS_DIALOG_INFO, std::make_pair(RIL_SERVICE_IMS, MSG_IND_AIMS_DIALOG_INFO) },
    { SIT_IND_AIMS_RCS_MULTI_FRAME, std::make_pair(RIL_SERVICE_IMS, MSG_IND_AIMS_RCS_MULTI_FRAME) },
    { SIT_IND_AIMS_RCS_CHAT, std::make_pair(RIL_SERVICE_IMS, MSG_IND_AIMS_RCS_CHAT) },
    { SIT_IND_AIMS_RCS_GROUP_CHAT, std::make_pair(RIL_SERVICE_IMS, MSG_IND_AIMS_RCS_GROUP_CHAT) },
    { SIT_IND_AIMS_RCS_OFFLINE_MODE, std::make_pair(RIL_SERVICE_IMS, MSG_IND_AIMS_RCS_OFFLINE_MODE) },
    { SIT_IND_AIMS_RCS_FILE_TRANSFER, std::make_pair(RIL_SERVICE_IMS, MSG_IND_AIMS_RCS_FILE_TRANSFER) },
    { SIT_IND_AIMS_RCS_COMMON_MESSAGE, std::make_pair(RIL_SERVICE_IMS, MSG_IND_AIMS_RCS_COMMON_MESSAGE) },
    { SIT_IND_AIMS_RCS_CONTENT_SHARE, std::make_pair(RIL_SERVICE_IMS, MSG_IND_AIMS_RCS_CONTENT_SHARE) },
    { SIT_IND_AIMS_RCS_PRESENCE, std::make_pair(RIL_SERVICE_IMS, MSG_IND_AIMS_RCS_PRESENCE) },
    { SIT_IND_AIMS_RCS_XCAP_MANAGE, std::make_pair(RIL_SERVICE_IMS, MSG_IND_AIMS_RCS_XCAP_MANAGE) },
    { SIT_IND_AIMS_RCS_CONFIG_MANAGE, std::make_pair(RIL_SERVICE_IMS, MSG_IND_AIMS_RCS_CONFIG_MANAGE) },
    { SIT_IND_AIMS_RCS_TLS_MANAGE, std::make_pair(RIL_SERVICE_IMS, MSG_IND_AIMS_RCS_TLS_MANAGE) },
    { SIT_IND_AIMS_MEDIA_STATUS, std::make_pair(RIL_SERVICE_IMS, MSG_IND_AIMS_MEDIA_STATUS) },
    { SIT_IND_AIMS_SIP_MSG_INFO, std::make_pair(RIL_SERVICE_IMS, MSG_IND_AIMS_SIP_MSG_INFO) },
    { SIT_IND_AIMS_VOICE_RTP_QUALITY, std::make_pair(RIL_SERVICE_IMS, MSG_IND_AIMS_VOICE_RTQ_QUALITY) },
    { SIT_AIMS_IND_RTP_RX_STATISTICS, std::make_pair(RIL_SERVICE_IMS, MSG_IND_AIMS_RTP_RX_STATISTICS) },
    //AIMS support end ----------------------

    //WFC
    { SIT_IND_WFC_RTP_RTCP_TIMEOUT, std::make_pair(RIL_SERVICE_IMS, MSG_IND_WFC_RTP_RTCP_TIMEOUT) },
    { SIT_IND_WFC_FIRST_RTP, std::make_pair(RIL_SERVICE_IMS, MSG_IND_WFC_FIRST_RTP) },
    { SIT_IND_WFC_RTCP_RX_SR, std::make_pair(RIL_SERVICE_IMS, MSG_IND_WFC_RTCP_RX_SR) },
    { SIT_IND_WFC_RCV_DTMF_NOTI, std::make_pair(RIL_SERVICE_IMS, MSG_IND_WFC_RCV_DTMF_NOTI) },

    { SIT_IND_VSIM_OPERATION, std::make_pair(RIL_SERVICE_VSIM, MSG_VSIM_OPERATION_IND) },

    /* eMBSM */
    { SIT_IND_EMBMS_COVERAGE, std::make_pair(RIL_SERVICE_EMBMS, MSG_EMBMS_UNSOL_COVERAGE) },
    { SIT_IND_EMBMS_SESSION_LIST, std::make_pair(RIL_SERVICE_EMBMS, MSG_EMBMS_UNSOL_SESSION_LIST_UPDATE) },
    { SIT_IND_EMBMS_SIGNAL_STRENGTH, std::make_pair(RIL_SERVICE_EMBMS, MSG_EMBMS_UNSOL_SIGNAL_STRENGTH) },
    { SIT_IND_EMBMS_NETWORK_TIME, std::make_pair(RIL_SERVICE_EMBMS, MSG_EMBMS_UNSOL_NETWORK_TIME) },
    { SIT_IND_EMBMS_SAI_LIST, std::make_pair(RIL_SERVICE_EMBMS, MSG_EMBMS_UNSOL_SAI_LIST) },
    { SIT_IND_EMBMS_GLOBAL_CELL_ID, std::make_pair(RIL_SERVICE_EMBMS, MSG_EMBMS_UNSOL_GLOBAL_CELL_ID) },

    { SIT_IND_ENTER_EMERGENCY_CB_MODE, std::make_pair(RIL_SERVICE_CSC, MSG_CS_IND_ENTER_EMERGENCY_CB_MODE_CHANGED) },
    { SIT_IND_EXIT_EMERGENCY_CB_MODE, std::make_pair(RIL_SERVICE_CSC, MSG_CS_IND_EXIT_EMERGENCY_CB_MODE_CHANGED) },
    { SIT_IND_RESEND_IN_CALL_MUTE, std::make_pair(RIL_SERVICE_CSC, MSG_CS_IND_RESEND_IN_CALL_MUTE) },
    { SIT_IND_CDMA_PRL_CHANGED, std::make_pair(RIL_SERVICE_MISC, MSG_MISC_IND_CDMA_PRL_CHANGED) },
    { SIT_IND_UICC_SUBSCRIPTION_STATE_CHANGED, std::make_pair(RIL_SERVICE_SIM, MSG_SIM_IND_UICC_SUBSCRIPTION_STATUS_CHANGED) },
    { SIT_IND_HW_CONFIG_CHANGED, std::make_pair(RIL_SERVICE_MISC, MSG_MISC_IND_HARDWARE_CONFIG_CHANGED) },
    { SIT_IND_RADIO_CAPABILITY, std::make_pair(RIL_SERVICE_NETWORK, MSG_NET_RC_INFO_RECV) },
    { SIT_IND_ON_SS, std::make_pair(RIL_SERVICE_SUPPLEMENTARY, MSG_SS_IND) },
    { SIT_IND_SCG_BEARER_ALLOCATION, std::make_pair(RIL_SERVICE_NETWORK, MSG_NET_SCG_BEARER_INFO_RECV) },
    { SIT_IND_STK_CC_ALPHA_NOTIFY, std::make_pair(RIL_SERVICE_STK, MSG_SAT_STK_CC_ALPHA_NOTIFY) },
    { SIT_IND_LCE_DATA, std::make_pair(RIL_SERVICE_MISC, MSG_MISC_LCEDATA_RECV) },
    { SIT_IND_CURRENT_LINK_CAPACITY_ESTIMATE, std::make_pair(RIL_SERVICE_MISC, MSG_MISC_IND_CURRENT_LINK_CAPACITY_ESTIMATE) },
    { SIT_IND_PCO_DATA, std::make_pair(RIL_SERVICE_PS, MSG_PS_IND_PCO_DATA) },
    { SIT_IND_MODEM_RESTART, std::make_pair(RIL_SERVICE_MISC, MSG_MISC_IND_MODEM_RESTART) },
    { SIT_IND_CARRIER_INFO_IMSI_ENCRYPTION, std::make_pair(RIL_SERVICE_MISC, MSG_MISC_IND_CARRIER_INFO_IMSI_ENCRYPTION) },
    { SIT_IND_SCANNING_NETWORKS, std::make_pair(RIL_SERVICE_NETWORK, MSG_NET_IND_NETWORK_SCAN_RESULT) },
    { SIT_IND_KEEPALIVE_STATUS, std::make_pair(RIL_SERVICE_PS, MSG_PS_IND_KEEPALIVE_STATUS) },
    { SIT_IND_SAR_CONTROL_STATE, std::make_pair(RIL_SERVICE_MISC, MSG_MISC_SAR_CONTROL_STATE_IND) },
    { SIT_OEM_IND_RF_CONNECTION, std::make_pair(RIL_SERVICE_MISC, MSG_MISC_SAR_RF_CONNECTION_IND) },
    { SIT_IND_RSSI_SCAN, std::make_pair(RIL_SERVICE_MISC, MSG_MISC_SCAN_RSSI_RESULT_RECEIVED) },
    { SIT_IND_FORWARDING_AT_COMMAND, std::make_pair(RIL_SERVICE_MISC, MSG_MISC_UNSOL_AT_COMMAND) },
    { SIT_OEM_IND_NW_INFO, std::make_pair(RIL_SERVICE_MISC, MSG_MISC_OEM_MODEM_INFO_RECEIVED) },
    { SIT_OEM_IND_RTP_PKTLOSS_THRESHOLD, std::make_pair(RIL_SERVICE_MISC, MSG_MISC_OEM_RTP_PKTLOSS_THRESHOLD_RECEIVED) },
    { SIT_IND_SELFLOG_STATUS, std::make_pair(RIL_SERVICE_MISC, MSG_MISC_UNSOL_SELFLOG_STATUS) },
    { SIT_IND_FREQUENCY_INFO, std::make_pair(RIL_SERVICE_NETWORK, MSG_NET_IND_FREQUENCY_INFO) },
    { SIT_IND_B2_B1_CONFIG, std::make_pair(RIL_SERVICE_NETWORK, MSG_NET_IND_B2_B1_CONFIG) },
    { SIT_IND_AC_BARRING_INFO, std::make_pair(RIL_SERVICE_NETWORK, MSG_NET_IND_AC_BARRING_INFO) },
    { SIT_OEM_IND_CA_BW_FILTER, std::make_pair(RIL_SERVICE_MISC, MSG_MISC_OEM_CA_BW_FILTER_IND) },
    { SIT_IND_PHYSICAL_CHANNEL_CONFIG, std::make_pair(RIL_SERVICE_NETWORK, MSG_NET_PHYSICAL_CHANNEL_CONFIGS_RECV) },
    { SIT_OEM_IND_ENDC_CAPABILITY, std::make_pair(RIL_SERVICE_MISC, MSG_MISC_OEM_IND_NTW_ENDC_CAPABILITY) },
};
#endif // __RIL_PROTOCOL_UNSOL_COMMANDS_H__
