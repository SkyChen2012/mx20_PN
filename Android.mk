LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
LOCAL_SRC_FILES:= \
    AnalyzePNMAC.c

LOCAL_C_INCLUDES := bionic/libc/bionic

LOCAL_SHARED_LIBRARIES := \
	libcutils \
	liblog \
	libc \
	libusbhost \
	libselinux

LOCAL_MODULE := AnalyzePNMAC
include $(BUILD_EXECUTABLE)