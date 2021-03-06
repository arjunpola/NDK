package com.example.jnitoast;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;

public class MainActivity extends Activity {
	
	static { System.loadLibrary("toast"); }
	
	public native void displayToast(CharSequence s,int i);
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.activity_main, menu);
        return true;
    }
    
    public void onClick(View v){
    	switch (v.getId()){
    	case R.id.btnlong :
    		displayToast("Hello Tost long",1);
    		return;
    	case R.id.btnshort :
    		displayToast("Hello Tost short",0);
    		return;
    	}
    	return;
    }
    
}

    
