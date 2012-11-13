LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := native-bitmap
LOCAL_SRC_FILES := com_example_androidbitmap1_MainActivity.c 

#log library
LOCAL_LDLIBS := -llog -ljnigraphics

include $(BUILD_SHARED_LIBRARY)

