
#include "com_example_brightness_MainActivity.h"

#include <android/log.h>
#include <android/bitmap.h>

#define LOG_TAG     ("native-log")
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

static int RGB_clamp(int value)
{
	if(value >255 )
		return 255;

	if(value < 0 )
		return 0;
	
	return value;
}

static void brightness1(AndroidBitmapInfo *info, void *pixels, float brightness)
{
	int xx, yy, red, green, blue;
	uint32_t *line;

	for( yy=0; yy<info->height; yy++ )
	{
		line = (uint32_t *)pixels;
		for( xx=0; xx<info->width; xx++ )
		{
			red = (int)((line[xx]&0x00FF0000) >> 16);
			green = (int)((line[xx]&0x0000FF00) >>8);
			blue = (int)(line[xx]&0x000000FF);

			red = RGB_clamp((int)(red*brightness));
			green = RGB_clamp((int)(green*brightness));
			blue = RGB_clamp((int)(blue*brightness));

			line[xx] = ((red <<16) & 0x00FF0000 ) |
						((green << 8)&0x0000FF00 ) |
						(blue & 0x000000FF);
		}

		pixels = (char *)pixels + info->stride;
	}	
}



JNIEXPORT void JNICALL Java_com_example_brightness_MainActivity_brightness
  (JNIEnv *pEnv, jobject thiz, jobject bitmap, jfloat brightness)
{
	AndroidBitmapInfo info;
	void *pixels;

	if(AndroidBitmap_getInfo(pEnv, bitmap, &info) < 0)
	{
		LOGI("AndroidBitmap_getInfo() failed");
		return;
	}

	if(info.format != ANDROID_BITMAP_FORMAT_RGBA_8888)
	{
		LOGI("bitmap format is not RGBA_8888");
		return;
	}

	if(AndroidBitmap_lockPixels(pEnv, bitmap, &pixels) < 0)
	{
		LOGI("AndroidBitmap_lockPixels() failed");
		return;
	}

	brightness1( &info, pixels, brightness);
	AndroidBitmap_unlockPixels(pEnv, bitmap);
}
