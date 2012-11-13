package com.example.androidbitmap1;

import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;
import android.widget.ImageView;

public class MainActivity extends Activity {

    private ImageView mImage;
    private Bitmap mBitmap;
    
    static { System.loadLibrary("native-bitmap"); }
    public native void reverseImage(Bitmap b);
    
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        mBitmap = BitmapFactory.decodeResource(
                getResources(), R.drawable.lena_rgb565);
        
        mImage = (ImageView)findViewById(R.id.img_view);
        mImage.setImageBitmap(mBitmap);
    }
    
    public void onClick(View v)
    {
        reverseImage(mBitmap);
        mImage.setImageBitmap(mBitmap);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.activity_main, menu);
        return true;
    }
}
