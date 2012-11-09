
#include <jni.h>
#include <errno.h>

#include <android_native_app_glue.h>
#include <android/log.h>

#define LOG_TAG ("natvie-log")
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

void android_main(struct android_app *app)
{
	app_dummy();

	while(1)
	{
		int ident;
		int events;
		struct android_poll_source *source;

		while( ident = ALooper_pollAll(-1, NULL, &events, (void **)&source) >=0 )
		{
			if( source != NULL)
			{
				source->process(app, source);
				LOGI("complete evetnt!");
			}

			if(app->destroyRequested != 0)
			{
				return;
			}
		}

	}
}
