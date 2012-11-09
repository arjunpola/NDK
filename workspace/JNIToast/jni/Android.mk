
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := toast 
LOCAL_SRC_FILES := com_example_jnitoast_MainActivity.c

LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)
