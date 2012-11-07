#include <jni.h>
#include <stdio.h>

void printHelloWorld(JNIEnv *pEnv, jobject thiz)
{
	printf("[C] Hello World \n");
}

jstring getHelloWorld(JNIEnv *pEnv, jobject thiz)
{
	return (*pEnv)->NewStringUTF(pEnv, "Hello World");
}

jint JNI_OnLoad(JavaVM *jvm, void *reserved)
{
	JNIEnv *pEnv = NULL;
	JNINativeMethod m_table[2];
	jclass MainClass;

	// JNIEnv Pointer
	if( (*jvm)->GetEnv(jvm, (void **)&pEnv, JNI_VERSION_1_6) != JNI_OK )
	{
		printf( "[C} GetEnv Error \n");
		return JNI_ERR;
	}


	// mapping
	m_table[0].name = "printHelloWorld";
	m_table[0].signature = "()V";
	m_table[0].fnPtr = (void *)printHelloWorld;

	m_table[1].name = "getHelloWorld";
	m_table[1].signature = "()Ljava/lang/String;";
	m_table[1].fnPtr = (void *)getHelloWorld;

	// find class
	MainClass = (*pEnv)->FindClass(pEnv, "Main");

	//  retigser mapping table
	(*pEnv)->RegisterNatives(pEnv, MainClass, m_table,2);

	return JNI_VERSION_1_6;
}
