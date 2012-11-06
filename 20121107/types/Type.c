#include "Type.h"
#include <stdio.h>

JNIEXPORT void JNICALL Java_Type_printInt
  (JNIEnv *pEnv, jobject thiz, jint i)  // jint  ==> signed  32bit   == int
{
	printf("[C] int from java = %d \n",i);
}
