
#include "com_example_androidbitmap1_MainActivity.h"

#include <android/bitmap.h>

#include <android/log.h>
#define LOG_TAG     ("native-bitmap")
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

void reverse(AndroidBitmapInfo *info, void *pixels)
{
	unsigned short *buf = pixels;
	int x, y;

	for( y=0; y<info->height; y++ )
	{
		for( x=0; x<info->width; x++ )
		{
			buf[y*(info->width)+x] ^= 0xffff;
		}
	}	
}


JNIEXPORT void JNICALL Java_com_example_androidbitmap1_MainActivity_reverseImage
  (JNIEnv *pEnv, jobject thiz, jobject bitmap)
{
	AndroidBitmapInfo info;
	void *pixels;

	if(AndroidBitmap_getInfo(pEnv, bitmap, &info) < 0)
	{
		LOGI("AndroidBitmap-getInfo() failed");
		return;
	}

	if(info.format != ANDROID_BITMAP_FORMAT_RGB_565)
	{
		LOGI("Bitmap format is not RGB565");
		return;
	}

	if(AndroidBitmap_lockPixels(pEnv, bitmap, &pixels) < 0)
	{
		LOGI("AndroidBitmap_lockPixels() failed" );
		return;
	}

	reverse(&info, pixels);

	AndroidBitmap_unlockPixels(pEnv, bitmap);

}

