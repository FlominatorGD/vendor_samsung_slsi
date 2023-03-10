#ifndef HIDL_GENERATED_VENDOR_SAMSUNG_SLSI_HARDWARE_WIFI_SUPPLICANT_V1_0_BPHWSUPPLICANTVENDORIFACE_H
#define HIDL_GENERATED_VENDOR_SAMSUNG_SLSI_HARDWARE_WIFI_SUPPLICANT_V1_0_BPHWSUPPLICANTVENDORIFACE_H

#include <hidl/HidlTransportSupport.h>

#include <vendor/samsung_slsi/hardware/wifi/supplicant/1.0/IHwSupplicantVendorIface.h>

namespace vendor {
namespace samsung_slsi {
namespace hardware {
namespace wifi {
namespace supplicant {
namespace V1_0 {

struct BpHwSupplicantVendorIface : public ::android::hardware::BpInterface<ISupplicantVendorIface>, public ::android::hardware::details::HidlInstrumentor {
    explicit BpHwSupplicantVendorIface(const ::android::sp<::android::hardware::IBinder> &_hidl_impl);

    typedef ISupplicantVendorIface Pure;

    typedef android::hardware::details::bphw_tag _hidl_tag;

    virtual bool isRemote() const override { return true; }


    // Methods from ::android::hidl::base::V1_0::IBase follow.
    ::android::hardware::Return<void> interfaceChain(interfaceChain_cb _hidl_cb) override;
    ::android::hardware::Return<void> debug(const ::android::hardware::hidl_handle& fd, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& options) override;
    ::android::hardware::Return<void> interfaceDescriptor(interfaceDescriptor_cb _hidl_cb) override;
    ::android::hardware::Return<void> getHashChain(getHashChain_cb _hidl_cb) override;
    ::android::hardware::Return<void> setHALInstrumentation() override;
    ::android::hardware::Return<bool> linkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient, uint64_t cookie) override;
    ::android::hardware::Return<void> ping() override;
    ::android::hardware::Return<void> getDebugInfo(getDebugInfo_cb _hidl_cb) override;
    ::android::hardware::Return<void> notifySyspropsChanged() override;
    ::android::hardware::Return<bool> unlinkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient) override;

private:
    std::mutex _hidl_mMutex;
    std::vector<::android::sp<::android::hardware::hidl_binder_death_recipient>> _hidl_mDeathRecipients;
};

}  // namespace V1_0
}  // namespace supplicant
}  // namespace wifi
}  // namespace hardware
}  // namespace samsung_slsi
}  // namespace vendor

#endif  // HIDL_GENERATED_VENDOR_SAMSUNG_SLSI_HARDWARE_WIFI_SUPPLICANT_V1_0_BPHWSUPPLICANTVENDORIFACE_H
