#include "Array.h"
#include <stdio.h>

JNIEXPORT void JNICALL Java_Array_printIntArr
  (JNIEnv *pEnv, jobject thiz, jintArray arr)
{
	int i;
	int intArr[9];
	(*pEnv)->GetIntArrayRegion(pEnv,arr,0,9,intArr);

	printf( "[C] int Arr from java = ");
	for( i=0; i<9 ; i++)
		printf( "[%d] ", intArr[i]);
	printf("\n");
}

JNIEXPORT jint JNICALL Java_Array_getIntArrSum
  (JNIEnv *pEnv, jobject thiz, jintArray arr)
{
	int i,sum;
	int intArr[9];
	sum = 0;
	(*pEnv)->GetIntArrayRegion(pEnv,arr,0,9,intArr);

	for( i=0; i<9 ; i++)
		sum += intArr[i];
	return sum;
}

JNIEXPORT void JNICALL Java_Array_printCharArr
  (JNIEnv *pEnv, jobject thiz, jcharArray arr)
{
	jchar *pArr;
	int i, len;

	pArr = (*pEnv)->GetCharArrayElements(pEnv, arr, NULL);
	len = (*pEnv)->GetArrayLength(pEnv, arr);

	printf( "[C] charArr form java = " );
	for( i=0 ; i<len ; i++)
	{
		printf("[%c]", pArr[i] );
	}
	printf("\n");

	(*pEnv)->ReleaseCharArrayElements(pEnv, arr, pArr, 0);

}

