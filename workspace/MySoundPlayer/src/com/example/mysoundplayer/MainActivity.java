package com.example.mysoundplayer;

import android.app.Activity;
import android.content.res.AssetManager;
import android.os.Bundle;
import android.os.Handler;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class MainActivity extends Activity {

	static boolean isPlayingAsset = false;
	
	static Button btnPlay;
	static Button btnStop;
	
	static AssetManager assetManager;
	
	static Handler mHandler = new Handler() {
		public void handleMessage(android.os.Message msg) {
			btnPlay.setText("play");
		};
	};
	
	static { System.loadLibrary("native-audio"); }
	public static native void createEngine();
	public static native boolean createAssetAudioPlayer(AssetManager assetManager, String filename);
	public static native void setPlayingAssetAudioPlayer(boolean isPlaying);
	public static native void stopAssetAudioPlayer();
	public static native void shutdown();
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        assetManager = getAssets();
        
        btnPlay = (Button)findViewById(R.id.btn_play);
        btnPlay.setOnClickListener(new OnClickListener() {
			
        	boolean created = false;
        	
			@Override
			public void onClick(View view) {
				if (!created) {
					created = createAssetAudioPlayer(assetManager, "xp.wav");
					btnPlay.setText("pause");
                }
                if (created) {
                    isPlayingAsset = !isPlayingAsset;
                    setPlayingAssetAudioPlayer(isPlayingAsset);
                    
                    if(!isPlayingAsset)
                    	btnPlay.setText("play");
                    else
                    	btnPlay.setText("pause");
                }	
			}
		});
        
        btnStop = (Button)findViewById(R.id.btn_stop);
        btnStop.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				
				if(!isPlayingAsset) {
					return;
				}
				else {
					isPlayingAsset = !isPlayingAsset;
					stopAssetAudioPlayer();
					btnPlay.setText("play");
				}
				
			}
		});
        
        createEngine();
    }
    
    public static void stopAudio()
    {
    	if(!isPlayingAsset) {
			return;
    	}
		else {
			isPlayingAsset = !isPlayingAsset;
			stopAssetAudioPlayer();
			mHandler.sendEmptyMessage(0);
		}
    }
    
    @Override
    protected void onPause() {
    	isPlayingAsset = false;
        setPlayingAssetAudioPlayer(false);
    	super.onPause();
    }

    @Override
    protected void onDestroy() {
    	shutdown();
    	super.onDestroy();
    }
    
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.activity_main, menu);
        return true;
    }
}
