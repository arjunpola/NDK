package com.example.myvoicerecoder;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.Toast;

public class MainActivity extends Activity {

	static Button btnRecord;
	static Button btnStop;
	static Button btnPlay;
	
	public static native void createEngine();
    public static native void createBufferQueueAudioPlayer();
	public static native boolean createAudioRecorder();
	public static native void startRecording();
	public static native boolean setPlaying(boolean isPlaying);
	public static native void shutdown();
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        btnRecord = (Button)findViewById(R.id.btn_record);
        btnRecord.setOnClickListener(new OnClickListener() {
			boolean createdRecorder = false;        	
        	
			@Override
			public void onClick(View v) {
			    if(!createdRecorder)
			        createdRecorder = createAudioRecorder();
			    
			    startRecording();
			}
		});
        
        btnPlay = (Button)findViewById(R.id.btn_play);
        btnPlay.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				setPlaying(true);
			}
		});
        
        btnStop = (Button)findViewById(R.id.btn_stop);
        btnStop.setOnClickListener(new View.OnClickListener() {
            
            @Override
            public void onClick(View v) {
                    setPlaying(false);
            }
        });
        

        // initialize native audio system
        createEngine();
        createBufferQueueAudioPlayer();
    }

    @Override
    protected void onPause() {
    	setPlaying(false);
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
    
    static {
    	System.loadLibrary("native-recorder");
    }
}
