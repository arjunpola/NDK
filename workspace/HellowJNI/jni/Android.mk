
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := helloworld
LOCAL_SRC_FILES := com_example_hellowjni_HelloJNIActivity.c

include $(BUILD_SHARED_LIBRARY)


