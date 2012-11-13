
#include "com_example_mysoundplayer_MainActivity.h"


#include <assert.h>
#include <string.h>

// for __android_log_print(ANDROID_LOG_INFO, "YourApp", "formatted message");
#include <android/log.h>

// for native audio
#include <SLES/OpenSLES.h>
#include "SLES/OpenSLES_Android.h"

// for native asset manager
#include <sys/types.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#define LOG_TAG		("native-sound")
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__))


// engine interfaces
static SLObjectItf engineObject = NULL;
static SLEngineItf engineEngine = NULL;

// output mix interfaces
static SLObjectItf outputMixObject = NULL;
static SLEnvironmentalReverbItf outputMixEnvironmentalReverb = NULL;

// file descriptor player interfaces
static SLObjectItf fdPlayerObject = NULL;
static SLPlayItf fdPlayerPlay;
static SLSeekItf fdPlayerSeek;

// aux effect on the output mix, used by the buffer queue player
static const SLEnvironmentalReverbSettings reverbSettings =
    SL_I3DL2_ENVIRONMENT_PRESET_STONECORRIDOR;

JavaVM *gVM;
jclass MainActivity;



void playStatusCallback(SLPlayItf caller, void *pContext, SLuint32 event)
{
	JNIEnv *env;
	if((*gVM)->AttachCurrentThread(gVM, &env, NULL) != JNI_OK)
	{
		LOGI("GetEnv Failed");
		return;
	}

	LOGI("playStatusCallback");
	switch(event)
	{
		case SL_PLAYEVENT_HEADATEND:
			{
				jmethodID stopAudio;

				LOGI("1");
				if(MainActivity == NULL)
				{
					LOGI("[C] MainActivity is NULL");
					goto error;
				}

				LOGI("2");
				stopAudio = (*env)->GetStaticMethodID(env, MainActivity, "stopAudio", "()V");
				LOGI("3");
				(*env)->CallStaticVoidMethod(env, MainActivity, stopAudio);
				LOGI("4");
			}
			break;
	}

error:
	
	(*gVM)->DetachCurrentThread(gVM);
}

/*
 * Class:     com_example_mysoundplayer_MainActivity
 * Method:    createEngine
 * Signature: ()V
 */
	JNIEXPORT void JNICALL Java_com_example_mysoundplayer_MainActivity_createEngine
(JNIEnv *env, jclass clazz)
{
	SLresult result;

	// create engine
	result = slCreateEngine(&engineObject, 0, NULL, 0, NULL, NULL);
	assert(SL_RESULT_SUCCESS == result);

	// realize the engine
	result = (*engineObject)->Realize(engineObject, SL_BOOLEAN_FALSE);
	assert(SL_RESULT_SUCCESS == result);

	// get the engine interface, which is needed in order to create other objects
	result = (*engineObject)->GetInterface(engineObject, SL_IID_ENGINE, &engineEngine);
	assert(SL_RESULT_SUCCESS == result);

	// create output mix, with environmental reverb specified as a non-required interface
	//const SLInterfaceID ids[1] = {SL_IID_ENVIRONMENTALREVERB};
	//const SLboolean req[1] = {SL_BOOLEAN_FALSE};
	result = (*engineEngine)->CreateOutputMix(engineEngine, &outputMixObject, 0, NULL, NULL);
	assert(SL_RESULT_SUCCESS == result);

	// realize the output mix
	result = (*outputMixObject)->Realize(outputMixObject, SL_BOOLEAN_FALSE);
	assert(SL_RESULT_SUCCESS == result);

	(*env)->GetJavaVM(env, &gVM);
	MainActivity = (*env)->NewGlobalRef(env, clazz);

}

/*
 * Class:     com_example_mysoundplayer_MainActivity
 * Method:    createAssetAudioPlayer
 * Signature: (Landroid/content/res/AssetManager;Ljava/lang/String;)Z
 */
	JNIEXPORT jboolean JNICALL Java_com_example_mysoundplayer_MainActivity_createAssetAudioPlayer
(JNIEnv *env, jclass clazz, jobject assetManager, jstring filename)
{
	SLresult result;

	// convert Java string to UTF-8
	const jbyte *utf8 = (*env)->GetStringUTFChars(env, filename, NULL);
	assert(NULL != utf8);

	// use asset manager to open asset by filename
	AAssetManager* mgr = AAssetManager_fromJava(env, assetManager);
	assert(NULL != mgr);
	AAsset* asset = AAssetManager_open(mgr, (const char *) utf8, AASSET_MODE_UNKNOWN);

	// release the Java string and UTF-8
	(*env)->ReleaseStringUTFChars(env, filename, utf8);

	// the asset might not be found
	if (NULL == asset) {
		return JNI_FALSE;
	}

	// open asset as file descriptor
	off_t start, length;
	int fd = AAsset_openFileDescriptor(asset, &start, &length);
	assert(0 <= fd);
	AAsset_close(asset);

	// configure audio source
	SLDataLocator_AndroidFD loc_fd = {SL_DATALOCATOR_ANDROIDFD, fd, start, length};
	SLDataFormat_MIME format_mime = {SL_DATAFORMAT_MIME, NULL, SL_CONTAINERTYPE_UNSPECIFIED};
	SLDataSource audioSrc = {&loc_fd, &format_mime};

	// configure audio sink
	SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, outputMixObject};
	SLDataSink audioSnk = {&loc_outmix, NULL};

	// create audio player
	const SLInterfaceID ids[1] = {SL_IID_SEEK};
	const SLboolean req[1] = {SL_BOOLEAN_TRUE};
	result = (*engineEngine)->CreateAudioPlayer(engineEngine, &fdPlayerObject, &audioSrc, &audioSnk,
			1, ids, req);
	assert(SL_RESULT_SUCCESS == result);

	// realize the player
	result = (*fdPlayerObject)->Realize(fdPlayerObject, SL_BOOLEAN_FALSE);
	assert(SL_RESULT_SUCCESS == result);

	// get the play interface
	result = (*fdPlayerObject)->GetInterface(fdPlayerObject, SL_IID_PLAY, &fdPlayerPlay);
	assert(SL_RESULT_SUCCESS == result);

	// regist callback function - daniel
	result = (*fdPlayerPlay)->RegisterCallback(fdPlayerPlay, playStatusCallback, NULL);
	assert(SL_RESULT_SUCCESS == result);

	result = (*fdPlayerPlay)->SetCallbackEventsMask(fdPlayerPlay, SL_PLAYEVENT_HEADATEND);
	assert(SL_RESULT_SUCCESS == result);


	// get the seek interface
	result = (*fdPlayerObject)->GetInterface(fdPlayerObject, SL_IID_SEEK, &fdPlayerSeek);
	assert(SL_RESULT_SUCCESS == result);

	// enable whole file looping
	result = (*fdPlayerSeek)->SetLoop(fdPlayerSeek, SL_BOOLEAN_FALSE, 0, SL_TIME_UNKNOWN);
	assert(SL_RESULT_SUCCESS == result);


	return JNI_TRUE;
}

/*
 * Class:     com_example_mysoundplayer_MainActivity
 * Method:    setPlayingAssetAudioPlayer
 * Signature: (Z)V
 */
	JNIEXPORT void JNICALL Java_com_example_mysoundplayer_MainActivity_setPlayingAssetAudioPlayer
(JNIEnv *env, jclass clazz, jboolean isPlaying)
{
	SLresult result;

	// make sure the asset audio player was created
	if (NULL != fdPlayerPlay) {

		// set the player's state
		result = (*fdPlayerPlay)->SetPlayState(fdPlayerPlay, isPlaying ?
				SL_PLAYSTATE_PLAYING : SL_PLAYSTATE_PAUSED);
		assert(SL_RESULT_SUCCESS == result);
	}
}

/*
 * Class:     com_example_mysoundplayer_MainActivity
 * Method:    shutdown
 * Signature: ()V
 */
	JNIEXPORT void JNICALL Java_com_example_mysoundplayer_MainActivity_shutdown
(JNIEnv * env, jclass clazz)
{
	// destroy file descriptor audio player object, and invalidate all associated interfaces
	if (fdPlayerObject != NULL) {
		(*fdPlayerObject)->Destroy(fdPlayerObject);
		fdPlayerObject = NULL;
		fdPlayerPlay = NULL;
		fdPlayerSeek = NULL;
	}

	// destroy output mix object, and invalidate all associated interfaces
	if (outputMixObject != NULL) {
		(*outputMixObject)->Destroy(outputMixObject);
		outputMixObject = NULL;
		outputMixEnvironmentalReverb = NULL;
	}

	// destroy engine object, and invalidate all associated interfaces
	if (engineObject != NULL) {
		(*engineObject)->Destroy(engineObject);
		engineObject = NULL;
		engineEngine = NULL;
	}
}

/*
 * Class:     com_example_mysoundplayer_MainActivity
 * Method:    stopAssetAudioPlayer
 * Signature: ()V
 */
	JNIEXPORT void JNICALL Java_com_example_mysoundplayer_MainActivity_stopAssetAudioPlayer
(JNIEnv *env, jclass clazz)
{
	SLresult result;

	// make sure the asset audio player was created
	if (NULL != fdPlayerPlay) {

		// set the player's state
		result = (*fdPlayerPlay)->SetPlayState(fdPlayerPlay, SL_PLAYSTATE_STOPPED);
		assert(SL_RESULT_SUCCESS == result);
	}
}

