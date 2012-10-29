package com.texttospeech;

import java.util.Locale;
import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;
import android.speech.tts.TextToSpeech; //needed to be added

public class TextToSpeech1 extends Activity implements TextToSpeech.OnInitListener{
    /** Called when the activity is first created. */
    
    private TextView morning;
    private TextToSpeech mTts;
    
    @Override
    public void onCreate(Bundle savedInstanceState) {
    	
    	
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        morning = (TextView)findViewById(R.id.morning);
    	mTts = new TextToSpeech(this,this);
        clickEvents();
    }

	@Override
	public void onInit(int status) {
		// TODO Auto-generated method stub
		if(status == TextToSpeech.SUCCESS) {
			int result = mTts.setLanguage(Locale.US);
			
			if(result == TextToSpeech.LANG_MISSING_DATA || result == TextToSpeech.LANG_NOT_SUPPORTED) {
				System.out.println("Language not supported");
			}
			else {
				Toast.makeText(this, "TextToSpeech has been set..", 10).show();
			}
		}
		else {
			Toast.makeText(this, "TestToSpeech is not supported", 10).show();
		}
		
	}
	
	

	private void saySomething() {
		mTts.speak(morning.getText().toString(), TextToSpeech.QUEUE_FLUSH, null);		
	}
	
	public void onDestroy() {
		if(mTts != null) {
			mTts.stop();
			mTts.shutdown();
		}
		super.onDestroy();
	}
	
	public void clickEvents() {
		morning.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				saySomething();
			}
		});
	}
}