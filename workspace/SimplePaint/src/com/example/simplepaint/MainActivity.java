package com.example.simplepaint;

import java.util.ArrayList;

import android.app.Activity;
import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.os.Bundle;
import android.view.Menu;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Toast;

public class MainActivity extends Activity {

	ArrayList<Point> arrPoints;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		MyView view = new MyView(getApplicationContext());
		view.setOnTouchListener(view);
		arrPoints = new ArrayList<Point>();
		setContentView(view);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		getMenuInflater().inflate(R.menu.activity_main, menu);
		return true;
	}

	class Point {
		float x, y;
		boolean dDraw;

		public Point() {
		};

		public Point(float x, float y, boolean b) {
			this.x = x;
			this.y = y;
			this.dDraw = b;
		}
	}

	public class MyView extends View implements View.OnTouchListener {

		Paint mPaint;

		public MyView(Context applicationContext) {
			super(applicationContext);

			mPaint = new Paint();
			mPaint.setColor(Color.BLACK);
			mPaint.setStrokeWidth(10);
			mPaint.setAntiAlias(true);
		}

		@Override
		protected void onDraw(Canvas canvas) {
			canvas.drawColor(Color.WHITE);

			for (int i = 0; i < arrPoints.size(); i++) {
				if (arrPoints.get(i).dDraw) {
					canvas.drawLine(arrPoints.get(i - 1).x,
							arrPoints.get(i - 1).y, arrPoints.get(i).x,
							arrPoints.get(i).y, mPaint);
				}
			}
		}

		@Override
		public boolean onTouch(View v, MotionEvent event) {
			switch (event.getAction()) {
			case MotionEvent.ACTION_DOWN:
				arrPoints.add(new Point(event.getX(), event.getY(), false));
				return true;
			case MotionEvent.ACTION_MOVE:
				arrPoints.add(new Point(event.getX(), event.getY(), true));
				invalidate();
				return true;
			}
			return false;
		}

	}
}
