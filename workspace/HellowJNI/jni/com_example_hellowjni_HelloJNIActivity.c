#include "com_example_hellowjni_HelloJNIActivity.h"

JNIEXPORT jstring JNICALL Java_com_example_hellowjni_HelloJNIActivity_getHelloWorld
  (JNIEnv *pEnv, jobject thiz)
{
	return (*pEnv)->NewStringUTF(pEnv, "[c] hello, world");
}
