/*
 * Copyright Samsung Electronics Co., LTD.
 *
 * This software is proprietary of Samsung Electronics.
 * No part of this software, either material or conceptual may be copied or distributed, transmitted,
 * transcribed, stored in a retrieval system or translated into any human or computer language in any form by any means,
 * electronic, mechanical, manual or otherwise, or disclosed
 * to third parties without the express written permission of Samsung Electronics.
 */

package com.samsung.slsi.telephony.usbmodeswitch;

import android.content.Context;
import android.hardware.usb.UsbManager;
import android.provider.Settings;
import android.util.Log;

public class UsbManagerInterfaceImpl extends AbstractUsbManagerInterface {
    private static final String TAG = "UsbManagerInterfaceImpl";

    UsbManagerInterfaceImpl(Context context) {
        super(context);
    }

    @Override
    public boolean setCurrentUsbFunctions(String functions, boolean makeDefault) {
        UsbManager usbManager = (UsbManager) mContext.getSystemService(Context.USB_SERVICE);
        if (usbManager == null) {
            return false;
        }

        if (functions != null) {
            String currentFunctions = getCurrentUsbFunctions();
            if (currentFunctions.equals(functions)) {
                return true;
            }

            boolean enableAdb = functions.contains("adb");
            Settings.Global.putInt(mContext.getContentResolver(), Settings.Global.ADB_ENABLED, enableAdb ? 1 : 0);
            usbManager.setCurrentFunction(functions, makeDefault);
            Log.d(TAG, "setCurrentFunction=" + functions + " makeDefault=" + makeDefault);

            return true;
        } else {
            usbManager.setCurrentFunction(null, false);
        }

        return false;
    }
}
