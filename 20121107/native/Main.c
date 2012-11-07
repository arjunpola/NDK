#include "Main.h"

JNIEXPORT jobject JNICALL Java_Main_createMathObject
  (JNIEnv *pEnv, jclass clazz)
{
	// FindClass -> class information
	// constructor -> mehtodID
	jclass MathClass;
	jobject mathObject;
	jmethodID constructor;

	// find the Math class to create an instance
    MathClass = (*pEnv)->FindClass(pEnv, "Math");
	// finc constructor of Math class
	constructor = (*pEnv)->GetMethodID(pEnv, MathClass, "<init>", "()V");
	// create an instance
	mathObject = (*pEnv)->NewObject(pEnv, MathClass, constructor);
	
	return mathObject;	
}

