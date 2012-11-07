#include "Type.h"
#include <stdio.h>

JNIEXPORT void JNICALL Java_Type_printInt
  (JNIEnv *pEnv, jobject thiz, jint i)  // jint  ==> signed  32bit   == int
{
	printf("[C] int from java = %d \n",i);
}

JNIEXPORT void JNICALL Java_Type_printChar
  (JNIEnv *pEnv, jobject thiz, jchar c) 
{
	printf("[C] char from java = %c",c );
}


JNIEXPORT void JNICALL Java_Type_printShort
  (JNIEnv *pEnv, jobject thiz, jshort s)
{
	printf("[C] short from java =  %d \n",s);
}

JNIEXPORT void JNICALL Java_Type_printLong
  (JNIEnv *pEnv, jobject thiz, jlong l) 
{
	printf("[C] long from java = %lld \n",l);
}

JNIEXPORT void JNICALL Java_Type_printFloat
  (JNIEnv *pEnv, jobject thiz, jfloat f)
{
	printf("[C] float from java = %f\n",f);
}

JNIEXPORT void JNICALL Java_Type_printDouble
  (JNIEnv *pEnv, jobject thiz, jdouble d)
{
	printf("[C] double from java = %f\n", d);
}


JNIEXPORT void JNICALL Java_Type_printBoolean
  (JNIEnv *pEnv, jobject thiz, jboolean b)
{
	printf("[C] boolean from java =  %d \n",b);
}
