#include "com_example_logtest_MainActivity.h"
#include <android/log.h>

#define LOG_TAG ("natvie-log")
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

JNIEXPORT void JNICALL Java_com_example_logtest_MainActivity_printLog
  (JNIEnv *pEnv, jobject thiz)
{
	LOGI("[C] called printLog");
}
