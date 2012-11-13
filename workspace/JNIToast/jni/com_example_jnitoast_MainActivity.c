#include "com_example_jnitoast_MainActivity.h"
#include <stdlib.h>
	
#include <android/log.h>

#define LOG_TAG ("natvie-log")
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

JNIEXPORT void JNICALL Java_com_example_jnitoast_MainActivity_displayToast
  (JNIEnv *pEnv, jobject thiz, jobject txt, jint time)
{
	jclass Toast = NULL;
	jobject toast = NULL;
	jmethodID makeText = NULL;
	jmethodID show = NULL;

	Toast = (*pEnv)->FindClass(pEnv, "android/widget/Toast");
	if(NULL == Toast)
	{
		LOGI("FindClass failed");
		return;
	}
	makeText = (*pEnv)->GetStaticMethodID(pEnv, Toast,"makeText", "(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;");
	if( NULL == makeText )
	{
		LOGI("FindStaticMethod failed");
		return;
	}
	toast = (*pEnv)->CallStaticObjectMethod(pEnv, Toast, makeText, thiz, txt, time);
	if ( NULL == toast) 
	{
		LOGI("CALLSTATICOBJECT FAILED");
		return;
	}
	show = (*pEnv)->GetMethodID(pEnv,Toast,"show","()V");
	if ( NULL == show )
	{
		LOGI("GetMethodID Failed");
		return;
	}
	(*pEnv)->CallVoidMethod(pEnv,toast,show);

}
