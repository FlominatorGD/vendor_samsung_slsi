/*
 * Copyright Samsung Electronics Co., LTD.
 *
 * This software is proprietary of Samsung Electronics.
 * No part of this software, either material or conceptual may be copied or distributed, transmitted,
 * transcribed, stored in a retrieval system or translated into any human or computer language in any form by any means,
 * electronic, mechanical, manual or otherwise, or disclosed
 * to third parties without the express written permission of Samsung Electronics.
 */
package com.samsung.slsi.telephony.aidl;

oneway interface ISensorServiceCallback {

    /*
     * onResults
     *
     * error: 0(success), 1(failure)
     *
     */
    void setSensorStatusRsp(in int error, in int phoneId);
}