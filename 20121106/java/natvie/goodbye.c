
#include <stdio.h>
#include <jni.h>

void Java_test_Main_printGoodbye(JNIEnv *pEnv, jclass clazz)
{
	printf("[C] Good bye !! JNI \n");
}
