#include <stdio.h>
#include <jni.h>

void Java_Main_printHelloWorld(JNIEnv *pEnv,jclass clazz)
{
	printf("[C] Hello world \n");
}
