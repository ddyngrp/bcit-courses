package com.FrameAnims;

import android.app.Activity;
import android.graphics.drawable.AnimationDrawable;
import android.os.Bundle;
import android.view.MotionEvent;
import android.widget.ImageView;

public class Animation extends Activity {
    /** Called when the activity is first created. */
    AnimationDrawable rocketAnimation;
    
    @Override
    public void onCreate(Bundle savedInstanceState) {
      super.onCreate(savedInstanceState);
      setContentView(R.layout.main);

      ImageView rocketImage = (ImageView) findViewById(R.id.rocket_image);
      rocketImage.setBackgroundResource(R.drawable.rocket_thrust);
      rocketAnimation = (AnimationDrawable) rocketImage.getBackground();
    }

    public boolean onTouchEvent(MotionEvent event) {
      if (event.getAction() == MotionEvent.ACTION_DOWN) {
        rocketAnimation.start();
        return true;
      }
      return super.onTouchEvent(event);
    }
}