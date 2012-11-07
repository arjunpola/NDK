#include "Array.h"
#include <stdio.h>
#include <stdlib.h>

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

JNIEXPORT jintArray JNICALL Java_Array_makeIntArr
  (JNIEnv *pEnv, jobject thiz, jint len)
{
	// make temprary dynamic array
	// init array
	// copy to jintArray(VM make it)
	// free array

	jint *pArr;
	int i;
	jintArray jintArr;

	pArr = malloc(sizeof(jint)*(int)len);
	for( i=0 ; i<len ; i++)
		pArr[i] = i+1;

	jintArr = (*pEnv)->NewIntArray(pEnv,len);

	(*pEnv)->SetIntArrayRegion(pEnv, jintArr, 0, len, pArr);

	free(pArr);
	return jintArr;
}

JNIEXPORT jcharArray JNICALL Java_Array_makeCharArr
  (JNIEnv *pEnv, jobject thiz, jint len)
{
	jchar *pArr;
	int i;
	jcharArray jcharArr;

	pArr = malloc(sizeof(jchar)*(int)len);
	for( i=0 ; i<len ; i++)
		pArr[i] = 0x30+i;

	jcharArr = (*pEnv)->NewCharArray(pEnv,len);

	(*pEnv)->SetCharArrayRegion(pEnv, jcharArr,0, len, pArr);
	free(pArr);
	return jcharArr;
}

JNIEXPORT void JNICALL Java_Array_printInt2DArr
  (JNIEnv *pEnv, jobject thiz, jobjectArray objArr, jint row, jint col)
{
	int i, j;
	jint (*pArr)[col];

	pArr = malloc(sizeof(jint)*(int)row*(int)col);
	for( i=0 ; i<row; i++)
	{
		jintArray jarr = (jintArray)(*pEnv)->GetObjectArrayElement(pEnv,objArr, i);
		jint *arr = (*pEnv)->GetIntArrayElements(pEnv,jarr,NULL);
		for(j=0; j<=col; j++)
		{
			pArr[i][j] = arr[j];
		}
	}

	printf("[C] Print int Array2D from java = \n");
	for( i=0 ; i<row ; i++)
	{
		for( j=0 ; j<col ; j++)
		{
			printf("[%d]",pArr[i][j]);
		}
		printf("\n");
	}
	free(pArr);
}
JNIEXPORT void JNICALL Java_Array_printChar2DArr
  (JNIEnv *pEnv, jobject thiz, jobjectArray objArr, jint row, jint col)
{
	int i, j;
	jchar (*pArr)[col];

	pArr = malloc(sizeof(jchar)*(int)row*(int)col);
	for( i=0 ; i<row; i++)
	{
		jcharArray jarr = (jcharArray)(*pEnv)->GetObjectArrayElement(pEnv,objArr, i);
		jchar *arr = (*pEnv)->GetCharArrayElements(pEnv,jarr,NULL);
		for(j=0; j<=col; j++)
		{
			pArr[i][j] = arr[j];
		}
	}

	printf("[C] Print char Array2D from java = \n");
	for( i=0 ; i<row ; i++)
	{
		for( j=0 ; j<col ; j++)
		{
			printf("[%c]",pArr[i][j]);
		}
		printf("\n");
	}
	free(pArr);
}

JNIEXPORT jobjectArray JNICALL Java_Array_makeInt2DArr
  (JNIEnv *pEnv, jobject thiz, jint row, jint col)
{
	jobjectArray objArr;
	jclass intArrClass;
	int i;
	int data = 1;

	// 1.  Find class to make int array object
	intArrClass = (*pEnv)->FindClass(pEnv,"[I");
	if(intArrClass == NULL)
	{
		printf( "[c] FindClass failed\n");
		return NULL;
	}

	objArr = (*pEnv)->NewObjectArray(pEnv, row, intArrClass, NULL);
	if( objArr == NULL )
	{
		printf("[c] NewObjectArray failed\n");
		return NULL;
	}

	for( i=0 ; i<row; i++)
	{
		jint tempArr[128];
		int j;

		jintArray jintArr = (*pEnv)->NewIntArray(pEnv, col);
		if( jintArr == NULL) 
		{
			printf("[c] NewIntArray failed\n");
			return NULL;
		}
		for( j=0 ; j<col ; j++)
		{
			tempArr[j] = data++;
		}
		(*pEnv)->SetIntArrayRegion(pEnv, jintArr, 0, col, tempArr);
		(*pEnv)->SetObjectArrayElement(pEnv, objArr, i, jintArr);
		(*pEnv)->DeleteLocalRef(pEnv, jintArr);
	}

	return objArr;

}
