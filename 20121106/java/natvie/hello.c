
#include <stdio.h>
#include <jni.h> 

//void Java_test_Main_printHelloWorld(JNIEnv *pEnv, jobject thiz)
void Java_test_Main_printHelloWorld(JNIEnv *pEnv, jclass clazz)
{
	printf( "[C] hello, world\n");

}
