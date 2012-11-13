package com.example.brightness;

import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;
import android.widget.ImageView;
import android.widget.SeekBar;
import android.widget.TextView;

public class MainActivity extends Activity {
    
    static { System.loadLibrary("native-brightness"); }
    
    private ImageView imgView;
    private Bitmap bitmap;
    private Bitmap original;
    
    private SeekBar seekBar;
    private TextView txtView;
    
    private float brightness;
    

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        txtView = (TextView)findViewById(R.id.txt_brightness);
        
        original = BitmapFactory.decodeResource(
                getResources(), R.drawable.cat);
        imgView = (ImageView)findViewById(R.id.img_view);
        imgView.setImageBitmap(original);
        
        seekBar = (SeekBar)findViewById(R.id.seek_bar);
        seekBar.setOnSeekBarChangeListener(
                new SeekBar.OnSeekBarChangeListener() {
            
            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {}
            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {}
            
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress,
                    boolean fromUser) {
                
                brightness = (float)(progress / 10.0f);
                txtView.setText("Brightness = " + brightness);
                
            }
        });
        
    }
    
    public void onClick(View v)
    {
        adjustBrightness();
    }
    
    public native void brightness(Bitmap bitmap, float brightness);
    
    public void adjustBrightness()
    {
        Bitmap bitmap = original.copy(Bitmap.Config.ARGB_8888, true);
        brightness(bitmap, brightness);
        imgView.setImageBitmap(bitmap);
        
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.activity_main, menu);
        return true;
    }
}
