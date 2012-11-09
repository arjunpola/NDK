
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := native-log
LOCAL_SRC_FILES := com_example_logtest_MainActivity.c

LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)
