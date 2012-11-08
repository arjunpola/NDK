package com.example.hellowjni;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.widget.TextView;

public class HelloJNIActivity extends Activity {

	static { System.loadLibrary("helloworld");}
	
	public native String getHelloWorld();
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        TextView txtView = new TextView(this);
        txtView.setText(getHelloWorld());
        setContentView(txtView);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.activity_hello_jni, menu);
        return true;
    }
}
