#include "Main.h"
#include <stdio.h>

JNIEXPORT void JNICALL Java_Main_printHelloWorld
  (JNIEnv *pEnv, jclass clazz)
{
	printf( "[C] hello world \n");
}

