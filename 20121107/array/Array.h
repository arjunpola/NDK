/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class Array */

#ifndef _Included_Array
#define _Included_Array
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     Array
 * Method:    printIntArr
 * Signature: ([I)V
 */
JNIEXPORT void JNICALL Java_Array_printIntArr
  (JNIEnv *, jobject, jintArray);

/*
 * Class:     Array
 * Method:    getIntArrSum
 * Signature: ([I)I
 */
JNIEXPORT jint JNICALL Java_Array_getIntArrSum
  (JNIEnv *, jobject, jintArray);

/*
 * Class:     Array
 * Method:    printCharArr
 * Signature: ([C)V
 */
JNIEXPORT void JNICALL Java_Array_printCharArr
  (JNIEnv *, jobject, jcharArray);

/*
 * Class:     Array
 * Method:    makeIntArr
 * Signature: (I)[I
 */
JNIEXPORT jintArray JNICALL Java_Array_makeIntArr
  (JNIEnv *, jobject, jint);

/*
 * Class:     Array
 * Method:    makeCharArr
 * Signature: (I)[C
 */
JNIEXPORT jcharArray JNICALL Java_Array_makeCharArr
  (JNIEnv *, jobject, jint);

/*
 * Class:     Array
 * Method:    printInt2DArr
 * Signature: ([[III)V
 */
JNIEXPORT void JNICALL Java_Array_printInt2DArr
  (JNIEnv *, jobject, jobjectArray, jint, jint);

/*
 * Class:     Array
 * Method:    printChar2DArr
 * Signature: ([[CII)V
 */
JNIEXPORT void JNICALL Java_Array_printChar2DArr
  (JNIEnv *, jobject, jobjectArray, jint, jint);

#ifdef __cplusplus
}
#endif
#endif
