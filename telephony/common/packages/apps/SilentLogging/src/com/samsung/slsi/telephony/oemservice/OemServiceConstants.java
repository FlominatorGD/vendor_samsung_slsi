/*
 * Copyright Samsung Electronics Co., LTD.
 *
 * This software is proprietary of Samsung Electronics.
 * No part of this software, either material or conceptual may be copied or distributed, transmitted,
 * transcribed, stored in a retrieval system or translated into any human or computer language in any form by any means,
 * electronic, mechanical, manual or otherwise, or disclosed
 * to third parties without the express written permission of Samsung Electronics.
 */

package com.samsung.slsi.telephony.oemservice;

public class OemServiceConstants {

    /* dmd command type */
    public static final int TYPE_COMMAND = 0;
    public static final int TYPE_RAW = 1;
    public static final int TYPE_FACTORY_COMMAND = 2;

    /* dmd mode */
    public static final int MODE_NONE = 0;
    public static final int MODE_EXTERNAL_DM = 1;
    public static final int MODE_SILENT_LOGGING = 2;
    public static final int MODE_ON_BOARD_DM = 3;
    public static final int MODE_EXT_APP_DM = 4;

    /* dmd command id */
    public static final int COMMAND_SET_DM_MODE = 0;
    public static final int COMMAND_SEND_PROFILE = 1;
    public static final int COMMAND_STOP_DM = 2;
    public static final int COMMAND_SAVE_SNAPSHOT = 3;
    public static final int COMMAND_NOTIFY_DM_LOG = 4;
    public static final int COMMAND_REFRESH_FILE_LIST = 5;
    public static final int COMMAND_SAVE_AUTOLOG = 6;
    public static final int COMMAND_SET_DM_MAX_FILE_SIZE = 7;
    public static final int FACTORY_COMMAND_SET_DM_MODE = 100;

    /* sced command id */
    public static final int COMMAND_LOGCAT = 0;
    public static final int COMMAND_LOGCAT_SNAPSHOT = 1;
    public static final int COMMAND_TCP_DUMP = 2;
    public static final int COMMAND_TCP_DUMP_SNAPSHOT = 3;
    public static final int COMMAND_KILL = 4;

    public static byte DEFAULT_PROFILE[] = {
        0x7F, 0x0A, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, (byte)0xA0, 0x00, 0x00, 0x7E, 0x7F, 0x0F, 0x00, 0x00,
        0x0C, 0x00, 0x00, 0x00, (byte)0xA0, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x05, 0x7E, 0x7F, 0x0F, 0x00,
        0x00, 0x0C, 0x00, 0x00, 0x00, (byte)0xA0, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, (byte)0xFF, 0x7E, 0x7F, 0x0F,
        0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, (byte)0xA0, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, (byte)0xFF, 0x7E, 0x7F,
        0x0F, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, (byte)0xA0, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, (byte)0xFF, 0x7E,
        0x7F, 0x0F, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, (byte)0xA0, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, (byte)0xFF,
        0x7E, 0x7F, 0x11, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, (byte)0xA0, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00,
        0x01, 0x01, 0x01, 0x7E, 0x7F, 0x11, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, (byte)0xA0, 0x00, 0x60, 0x00,
        0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0x7E, 0x7F, 0x11, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, (byte)0xA0,
        0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x01, 0x7E, 0x7F, 0x11, 0x00, 0x00, 0x0E, 0x00,
        0x00, 0x00, (byte)0xA0, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x00, 0x7E, 0x7F, 0x11, 0x00,
        0x00, 0x0E, 0x00, 0x00, 0x00, (byte)0xA0, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x01, 0x7E,
        0x7F, 0x11, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, (byte)0xA0, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x02,
        0x03, 0x00, 0x7E, 0x7F, 0x0E, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, (byte)0xA0, 0x00, 0x56, 0x00, 0x00,
        0x00, 0x00, 0x7E, 0x7F, 0x0F, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, (byte)0xA0, 0x00, 0x50, 0x00, 0x00,
        0x00, 0x00, 0x01, 0x7E, 0x7F, 0x0F, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, (byte)0xA0, 0x00, 0x50, 0x00,
        0x00, 0x00, 0x00, 0x02, 0x7E, 0x7F, 0x0E, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, (byte)0xA0, 0x00, 0x74,
        0x00, 0x00, 0x00, 0x00, 0x7E, 0x7F, 0x0E, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, (byte)0xA0, 0x00, 0x78,
        0x00, 0x00, 0x00, 0x00, 0x7E, 0x7F, 0x0E, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, (byte)0xA0, 0x00, 0x70,
        0x00, 0x00, 0x00, 0x00, 0x7E, 0x7F, (byte)0xFB, 0x01, 0x00, (byte)0xF8, 0x01, 0x00, 0x00, (byte)0xA0, 0x00, 0x76,
        0x00, 0x00, 0x00, 0x00, 0x01, (byte)0xF4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,
        0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x03,
        0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x7E, 0x7F, 0x0E, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, (byte)0xA0, 0x00, 0x74, 0x00, 0x00, 0x00,
        0x00, 0x7E, 0x7F, 0x10, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00, (byte)0xA0, 0x00, 0x12, 0x00, 0x00, 0x00,
        0x00, 0x01, 0x02, 0x7E, 0x7F, 0x10, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00, (byte)0xA0, 0x00, 0x22, 0x00,
        0x00, 0x00, 0x00, 0x01, 0x54, 0x7E, 0x7F, 0x10, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00, (byte)0xA0, 0x00,
        0x12, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x7E
    };
    public static final byte[] SET_SDM_MODE_DM = {0x7F, 0x0a, 0x00, 0x00, 0x07, 0x00, 0x00, (byte)0xFF, (byte)0xa0, 0x00, 0x02, 0x7E};

}
