#include "Calc.h"

JNIEXPORT jint JNICALL Java_Calc_add
  (JNIEnv *pEnv, jobject thiz, jint a, jint b)
{
	return a+b;
}

JNIEXPORT jint JNICALL Java_Calc_sub
  (JNIEnv *pEnv, jobject thiz, jint a, jint b)
{
	return a-b;
}

