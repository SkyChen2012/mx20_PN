LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
LOCAL_SRC_FILES:= \
    AnalyzePNMAC.c
LOCAL_MODULE := AnalyzePNMAC
include $(BUILD_EXECUTABLE)