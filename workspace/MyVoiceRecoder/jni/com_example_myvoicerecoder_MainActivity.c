#include "com_example_myvoicerecoder_MainActivity.h"

#include <assert.h>
#include <string.h>

#include <android/log.h>
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-recorder", __VA_ARGS__)) 
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-recorder", __VA_ARGS__))


// for native audio
#include <SLES/OpenSLES.h>
#include "SLES/OpenSLES_Android.h"

// for native asset manager
// #include <sys/types.h>
// #include <android/asset_manager.h>
// #include <android/asset_manager_jni.h>

// engine interfaces
static SLObjectItf engineObject = NULL;
static SLEngineItf engineEngine;

// output mix interfaces
static SLObjectItf outputMixObject = NULL;

// buffer queue player interfaces
static SLObjectItf bqPlayerObject = NULL;
static SLPlayItf bqPlayerPlay;
static SLAndroidSimpleBufferQueueItf bqPlayerBufferQueue;
static SLEffectSendItf bqPlayerEffectSend;

// recorder interfaces
static SLObjectItf recorderObject = NULL;
static SLRecordItf recorderRecord;
static SLAndroidSimpleBufferQueueItf recorderBufferQueue;


// 5 seconds of recorded audio at 16 kHz mono, 16-bit signed little endian
#define RECORDER_FRAMES (16000 * 5)
static short recorderBuffer[RECORDER_FRAMES];
static unsigned recorderSize = 0;
static SLmilliHertz recorderSR;

// this callback handler is called every time a buffer finishes recording
void bqRecorderCallback(SLAndroidSimpleBufferQueueItf bq, void *context)
{
    assert(bq == bqRecorderBufferQueue);
    assert(NULL == context);
    // for streaming recording, here we would call Enqueue to give recorder the next buffer to fill
    // but instead, this is a one-time buffer so we stop recording
    SLresult result;
    result = (*recorderRecord)->SetRecordState(recorderRecord, SL_RECORDSTATE_STOPPED);
    if (SL_RESULT_SUCCESS == result) {
        recorderSize = RECORDER_FRAMES * sizeof(short);
        recorderSR = SL_SAMPLINGRATE_16;
    }
}


// create the engine and output mix objects
JNIEXPORT void JNICALL Java_com_example_myvoicerecoder_MainActivity_createEngine
	(JNIEnv* env, jclass clazz)
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

    // create output mix
    result = (*engineEngine)->CreateOutputMix(engineEngine, &outputMixObject, 0, NULL, NULL);
    assert(SL_RESULT_SUCCESS == result);

    // realize the output mix
    result = (*outputMixObject)->Realize(outputMixObject, SL_BOOLEAN_FALSE);
    assert(SL_RESULT_SUCCESS == result);
}


// create buffer queue audio player
JNIEXPORT void JNICALL Java_com_example_myvoicerecoder_MainActivity_createBufferQueueAudioPlayer
	(JNIEnv* env, jclass clazz)
{
	SLresult result;

	// configure audio source
	SLDataLocator_AndroidSimpleBufferQueue loc_bufq = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2};
	SLDataFormat_PCM format_pcm = { SL_DATAFORMAT_PCM,
	   								1,
								   	SL_SAMPLINGRATE_8,
									SL_PCMSAMPLEFORMAT_FIXED_16,
								   	SL_PCMSAMPLEFORMAT_FIXED_16,
									SL_SPEAKER_FRONT_CENTER,
								   	SL_BYTEORDER_LITTLEENDIAN };
	SLDataSource audioSrc = {&loc_bufq, &format_pcm};

	// configure audio sink
	SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, outputMixObject};
	SLDataSink audioSnk = {&loc_outmix, NULL};

	// create audio player
	const SLInterfaceID ids[2] = {SL_IID_BUFFERQUEUE, SL_IID_EFFECTSEND};
	const SLboolean req[2] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};
	result = (*engineEngine)->CreateAudioPlayer(engineEngine, &bqPlayerObject, &audioSrc, &audioSnk,
			2, ids, req);
	assert(SL_RESULT_SUCCESS == result);

	// realize the player
	result = (*bqPlayerObject)->Realize(bqPlayerObject, SL_BOOLEAN_FALSE);
	assert(SL_RESULT_SUCCESS == result);

	// get the play interface
	result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_PLAY, &bqPlayerPlay);
	assert(SL_RESULT_SUCCESS == result);

	// get the buffer queue interface
	result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_BUFFERQUEUE,
			&bqPlayerBufferQueue);
	assert(SL_RESULT_SUCCESS == result);

	// set the player's state to playing
	result = (*bqPlayerPlay)->SetPlayState(bqPlayerPlay, SL_PLAYSTATE_PLAYING);
	assert(SL_RESULT_SUCCESS == result);

}


// select the desired clip and play count, and enqueue the first buffer if idle
JNIEXPORT jboolean JNICALL Java_com_example_myvoicerecoder_MainActivity_setPlaying
  (JNIEnv *env, jclass clazz, jboolean isPlaying)
{
	SLresult result;

	if(!isPlaying)
	{
		LOGI("turn playing off");
		return JNI_TRUE;
	}

	LOGI("playing");
	// CLIP_PLAYBACK
	// we recorded at 16 kHz, but are playing buffers at 8 Khz, so do a primitive down-sample
	if (recorderSR == SL_SAMPLINGRATE_16)
	{
		unsigned i;
		for (i = 0; i < recorderSize; i += 2 * sizeof(short))
			recorderBuffer[i >> 2] = recorderBuffer[i >> 1];

		recorderSR = SL_SAMPLINGRATE_8;
		recorderSize >>= 1;

	}

	result = (*bqPlayerBufferQueue)->Enqueue(bqPlayerBufferQueue, recorderBuffer, recorderSize);
	if (SL_RESULT_SUCCESS != result) {
		return JNI_FALSE;
	}

	return JNI_TRUE;
}


// create audio recorder
JNIEXPORT jboolean JNICALL Java_com_example_myvoicerecoder_MainActivity_createAudioRecorder
(JNIEnv* env, jclass clazz)
{
	SLresult result;

	// configure audio source
	SLDataLocator_IODevice loc_dev = {
		SL_DATALOCATOR_IODEVICE,
		SL_IODEVICE_AUDIOINPUT,
		SL_DEFAULTDEVICEID_AUDIOINPUT,
		NULL };
	SLDataSource audioSrc = {&loc_dev, NULL};

	// configure audio sink
	SLDataLocator_AndroidSimpleBufferQueue loc_bq = {
		SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2
	};
	SLDataFormat_PCM format_pcm = {
		SL_DATAFORMAT_PCM, 1, SL_SAMPLINGRATE_16,
		SL_PCMSAMPLEFORMAT_FIXED_16, SL_PCMSAMPLEFORMAT_FIXED_16,
		SL_SPEAKER_FRONT_CENTER, SL_BYTEORDER_LITTLEENDIAN
	};
	SLDataSink audioSnk = {&loc_bq, &format_pcm};

	// create audio recorder
	// (requires the RECORD_AUDIO permission)
	const SLInterfaceID id[1] = {SL_IID_ANDROIDSIMPLEBUFFERQUEUE};
	const SLboolean req[1] = {SL_BOOLEAN_TRUE};
	result = (*engineEngine)->CreateAudioRecorder(engineEngine, &recorderObject, &audioSrc,
			&audioSnk, 1, id, req);
	if (SL_RESULT_SUCCESS != result) {
		return JNI_FALSE;
	}

	// realize the audio recorder
	result = (*recorderObject)->Realize(recorderObject, SL_BOOLEAN_FALSE);
	if (SL_RESULT_SUCCESS != result) {
		return JNI_FALSE;
	}

	// get the record interface
	result = (*recorderObject)->GetInterface(recorderObject, SL_IID_RECORD, &recorderRecord);
	assert(SL_RESULT_SUCCESS == result);

	// get the buffer queue interface
	result = (*recorderObject)->GetInterface(recorderObject, SL_IID_ANDROIDSIMPLEBUFFERQUEUE,
			&recorderBufferQueue);
	assert(SL_RESULT_SUCCESS == result);

	// register callback on the buffer queue
	result = (*recorderBufferQueue)->RegisterCallback(recorderBufferQueue, bqRecorderCallback,
			NULL);
	assert(SL_RESULT_SUCCESS == result);

	return JNI_TRUE;
}


// set the recording state for the audio recorder
JNIEXPORT void JNICALL Java_com_example_myvoicerecoder_MainActivity_startRecording
(JNIEnv* env, jclass clazz)
{
	SLresult result;

	// in case already recording, stop recording and clear buffer queue
	result = (*recorderRecord)->SetRecordState(recorderRecord, SL_RECORDSTATE_STOPPED);
	assert(SL_RESULT_SUCCESS == result);
	result = (*recorderBufferQueue)->Clear(recorderBufferQueue);
	assert(SL_RESULT_SUCCESS == result);

	// the buffer is not valid for playback yet
	recorderSize = 0;

	// enqueue an empty buffer to be filled by the recorder
	// (for streaming recording, we would enqueue at least 2 empty buffers to start things off)
	result = (*recorderBufferQueue)->Enqueue(recorderBufferQueue, recorderBuffer,
			RECORDER_FRAMES * sizeof(short));
	// the most likely other result is SL_RESULT_BUFFER_INSUFFICIENT,
	// which for this code example would indicate a programming error
	assert(SL_RESULT_SUCCESS == result);

	// start recording
	result = (*recorderRecord)->SetRecordState(recorderRecord, SL_RECORDSTATE_RECORDING);
	assert(SL_RESULT_SUCCESS == result);

}


// shut down the native audio system
JNIEXPORT void JNICALL Java_com_example_myvoicerecoder_MainActivity_shutdown
(JNIEnv* env, jclass clazz)
{

	// destroy buffer queue audio player object, and invalidate all associated interfaces
	if (bqPlayerObject != NULL) {
		(*bqPlayerObject)->Destroy(bqPlayerObject);
		bqPlayerObject = NULL;
		bqPlayerPlay = NULL;
		bqPlayerBufferQueue = NULL;
		bqPlayerEffectSend = NULL;
	}

	// destroy audio recorder object, and invalidate all associated interfaces
	if (recorderObject != NULL) {
		(*recorderObject)->Destroy(recorderObject);
		recorderObject = NULL;
		recorderRecord = NULL;
		recorderBufferQueue = NULL;
	}

	// destroy output mix object, and invalidate all associated interfaces
	if (outputMixObject != NULL) {
		(*outputMixObject)->Destroy(outputMixObject);
		outputMixObject = NULL;
	}

	// destroy engine object, and invalidate all associated interfaces
	if (engineObject != NULL) {
		(*engineObject)->Destroy(engineObject);
		engineObject = NULL;
		engineEngine = NULL;
	}

}
