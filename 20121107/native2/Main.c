#include "Main.h"

JNIEXPORT jfloat JNICALL Java_Main_getCircleArea
  (JNIEnv *pEnv, jclass clazz, jint r)
{
	jclass CircleClass;
	jmethodID getCircleArea;
	jfloat result;

	CircleClass = (*pEnv)->FindClass(pEnv, "Circle");
	getCircleArea = (*pEnv)->GetStaticMethodID(pEnv, CircleClass, "getCircleArea","(I)F");

	result = (*pEnv)->CallStaticFloatMethod(pEnv, CircleClass, getCircleArea, r);
	return result;
}
