#include "Main.h"
#include <stdio.h>

JNIEXPORT jfloat JNICALL Java_Main_getCircleArea
  (JNIEnv *pEnv, jclass clazz, jint r)
{
	jclass CircleClass;
	jmethodID getCircleArea;
	jfieldID PI;
	jfloat result;
	jfloat f;

	CircleClass = (*pEnv)->FindClass(pEnv, "Circle");
	getCircleArea = (*pEnv)->GetStaticMethodID(pEnv, CircleClass, "getCircleArea","(I)F");

	// call static field 
	PI = (*pEnv)->GetStaticFieldID(pEnv, CircleClass, "PI", "F");
	f = (*pEnv)->GetStaticFloatField(pEnv, CircleClass, PI);
    printf("[C] PI of Circle Class = %f \n",f);

	result = (*pEnv)->CallStaticFloatMethod(pEnv, CircleClass, getCircleArea, r);
	return result;
}
