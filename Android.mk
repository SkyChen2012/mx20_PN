#ifeq ($(TARGET_PRODUCT),$(filter $(TARGET_PRODUCT),imx53_hc imx53_combo imx53_le))

LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := test_PN

LOCAL_PRELINK_MODULE := false
LOCAL_SHARED_LIBRARIES := liblog  libdido.a20
LOCAL_SRC_FILES := PN_test.c

include $(BUILD_EXECUTABLE)

#endif
