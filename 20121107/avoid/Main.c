#include "Main.h"
#include <stdio.h>

JNIEXPORT jfloat JNICALL Java_Main_getCircleArea
  (JNIEnv *pEnv, jclass clazz, jint r)
{
	jclass CircleClass ;   // cache  ? Local Reference   
	static jclass gCircleClass = NULL;    // global reference
	jmethodID getCircleArea;
	jfieldID PI;
	jfloat result;
	jfloat f;

	if(gCircleClass == NULL)
	{
		CircleClass = (*pEnv)->FindClass(pEnv, "Circle");
		gCircleClass = (*pEnv)->NewGlobalRef(pEnv, CircleClass);
	}
	getCircleArea = (*pEnv)->GetStaticMethodID(pEnv, gCircleClass, "getCircleArea","(I)F");

	// call static field 
	PI = (*pEnv)->GetStaticFieldID(pEnv, gCircleClass, "PI", "F");
	f = (*pEnv)->GetStaticFloatField(pEnv, gCircleClass, PI);
    printf("[C] PI of Circle Class = %f \n",f);

	result = (*pEnv)->CallStaticFloatMethod(pEnv, gCircleClass, getCircleArea, r);
	return result;
}
