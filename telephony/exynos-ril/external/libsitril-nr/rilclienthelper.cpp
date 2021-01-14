/*
 * Copyright Samsung Electronics Co., LTD.
 *
 * This software is proprietary of Samsung Electronics.
 * No part of this software, either material or conceptual may be copied or distributed, transmitted,
 * transcribed, stored in a retrieval system or translated into any human or computer language in any form by any means,
 * electronic, mechanical, manual or otherwise, or disclosed
 * to third parties without the express written permission of Samsung Electronics.
 */
#include "base.h"
#include "rilclienthelper.h"
#include <dlfcn.h>
#include <utils/Log.h>

#define PATH_LIBSITRIL_CILENT "libsitril-client.so"

/**
 * RilClientHelperDLImpl
 */
class RilClientHelperDLImpl : public RilClientHelper {
    DECLARE_MODULE_TAG()
private:
    HANDLE m_handle;
    HANDLE m_client;

    void *(*m_fpRILC_Open)(void);
    int (*m_fpRILC_Close)(void* client);
    int (*m_fpRILC_Reconnect)(void* client);
    int (*m_fpRILC_RegisterUnsolicitedHandler)(void* client, Rilc_OnUnsolicitedResponse handler);
    int (*m_fpIRILC_Send)(void* client, unsigned msgId, void* data, size_t length, Rilc_OnResponse handler, unsigned int channel);

public:
    static RilClientHelperDLImpl *instance;
    static RilClientHelperDLImpl *GetInstance();

public:
    RilClientHelperDLImpl();
    virtual ~RilClientHelperDLImpl();

protected:
    virtual bool Init();
    virtual void Release();

public:
    // @Overriding
    void *Open();
    int Close(void* client);
    int Reconnect(void* client);
    int Send(void* client, unsigned msgId, void* data, size_t length, Rilc_OnResponse handler);
    int Send(void* client, unsigned msgId, void* data, size_t length, Rilc_OnResponse handler, unsigned int channel);
    int RegisterUnsolicitedResponseHandler(void* client, Rilc_OnUnsolicitedResponse handler);
};

IMPLEMENT_MODULE_TAG(RilClientHelperDLImpl, RilClientHelperDLImpl)
RilClientHelperDLImpl *RilClientHelperDLImpl::instance = NULL;
RilClientHelperDLImpl *RilClientHelperDLImpl::GetInstance()
{
    if (instance == NULL) {
        instance = new RilClientHelperDLImpl();
        if (instance != NULL) {
            instance->Init();
        }
    }
    return instance;
}

RilClientHelperDLImpl::RilClientHelperDLImpl()
    : m_handle(0), m_client(0)
{
    RLOGI("%s::%s create instance", TAG, __FUNCTION__);
    m_fpRILC_Open = NULL;
    m_fpRILC_Close = NULL;
    m_fpRILC_Reconnect = NULL;
    m_fpRILC_RegisterUnsolicitedHandler = NULL;
    m_fpIRILC_Send = NULL;
}

RilClientHelperDLImpl::~RilClientHelperDLImpl()
{
    RLOGI("%s::%s release instance", TAG, __FUNCTION__);
    Release();
}

bool RilClientHelperDLImpl::Init()
{
    RLOGI("%s::%s", TAG, __FUNCTION__);
    m_handle = dlopen(PATH_LIBSITRIL_CILENT, RTLD_NOW);
    if (m_handle != NULL) {
        m_fpRILC_Open = (void *(*)(void))dlsym(m_handle, "RILC_Open");
        if (m_fpRILC_Open == NULL) {
            RLOGE("%s::%s error: dlsym failure(RILC_Open)", TAG, __FUNCTION__);
            Release();
            return false;
        }

        m_fpRILC_Close = (int (*)(void*))dlsym(m_handle, "RILC_Close");
        if (m_fpRILC_Close == NULL) {
            RLOGE("%s::%s error: dlsym failure(RILC_Close)", TAG, __FUNCTION__);
            Release();
            return false;
        }

        m_fpRILC_Reconnect = (int (*)(void*))dlsym(m_handle, "RILC_Reconnect");
        if (m_fpRILC_Reconnect == NULL) {
            RLOGE("%s::%s error: dlsym failure(RILC_Reconnect)", TAG, __FUNCTION__);
            Release();
            return false;
        }

        m_fpRILC_RegisterUnsolicitedHandler = (int (*)(void*, Rilc_OnUnsolicitedResponse))dlsym(m_handle, "RILC_RegisterUnsolicitedHandler");
        if (m_fpRILC_RegisterUnsolicitedHandler == NULL) {
            RLOGE("%s::%s error: dlsym failure(RILC_RegisterUnsolicitedHandler)", TAG, __FUNCTION__);
            Release();
            return false;
        }

        m_fpIRILC_Send = (int (*)(void*, unsigned int, void*, size_t, Rilc_OnResponse, unsigned int))dlsym(m_handle, "RILC_Send");
        if (m_fpIRILC_Send == NULL) {
            RLOGE("%s::%s error: dlsym failure(RILC_Send)", TAG, __FUNCTION__);
            Release();
            return false;
        }

        return true;
    }
    RLOGE("%s::%s error: dlopen failure", TAG, __FUNCTION__);

    return false;
}

void RilClientHelperDLImpl::Release()
{
    RLOGI("%s::%s", TAG, __FUNCTION__);
    if (m_handle != NULL) {
        //dlclose(m_handle);
        m_handle = NULL;
    }

    m_fpRILC_Open = NULL;
    m_fpRILC_Close = NULL;
    m_fpRILC_Reconnect = NULL;
    m_fpRILC_RegisterUnsolicitedHandler = NULL;
    m_fpIRILC_Send = NULL;
}

void *RilClientHelperDLImpl::Open()
{
    RLOGI("%s::%s", TAG, __FUNCTION__);
    if (m_handle != NULL && m_fpRILC_Open != NULL) {
        m_client = m_fpRILC_Open();
    }
    return m_client;
}

int RilClientHelperDLImpl::Close(void* client)
{
    RLOGI("%s::%s", TAG, __FUNCTION__);
    if (m_handle != NULL && m_fpRILC_Close != NULL) {
        if (client != NULL) {
            return m_fpRILC_Close(client);
        }
    }
    return RILC_STATUS_FAIL;
}

int RilClientHelperDLImpl::Reconnect(void* client)
{
    RLOGI("%s::%s", TAG, __FUNCTION__);
    if (m_handle != NULL && m_fpRILC_Reconnect != NULL) {
        return m_fpRILC_Reconnect(client);
    }
    return RILC_STATUS_FAIL;
}

int RilClientHelperDLImpl::Send(void* client, unsigned msgId, void* data, size_t length, Rilc_OnResponse handler)
{
    RLOGI("%s::%s", TAG, __FUNCTION__);
    if (m_handle != NULL && m_fpIRILC_Send != NULL) {
        return m_fpIRILC_Send(client, msgId, data, length, handler, RIL_SOCKET_UNKNOWN);
    }
    return RILC_STATUS_FAIL;
}

int RilClientHelperDLImpl::Send(void* client, unsigned msgId, void* data, size_t length, Rilc_OnResponse handler, unsigned int channel)
{
    RLOGI("%s::%s", TAG, __FUNCTION__);
    if (m_handle != NULL && m_fpIRILC_Send != NULL) {
        return m_fpIRILC_Send(client, msgId, data, length, handler, channel);
    }
    return RILC_STATUS_FAIL;
}

int RilClientHelperDLImpl::RegisterUnsolicitedResponseHandler(void* client, Rilc_OnUnsolicitedResponse handler)
{
    RLOGI("%s::%s", TAG, __FUNCTION__);
    if (m_handle != NULL && m_fpRILC_RegisterUnsolicitedHandler != NULL) {
        return m_fpRILC_RegisterUnsolicitedHandler(client, handler);
    }
    return RILC_STATUS_FAIL;
}

// create RilClientHelper instance
RilClientHelper *RilClientHelper::GetInstance()
{
    return RilClientHelperDLImpl::GetInstance();
}
