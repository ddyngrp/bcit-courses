package com.texttospeech;



import android.app.Activity;
import android.os.Bundle;

import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class TextToSpeech2 extends Activity {
        
    private EditText speech;
    private Button buttonSpeech;
    
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        speech = (EditText)findViewById(R.id.speech);
        buttonSpeech = (Button)findViewById(R.id.buttonSpeech);
    	    	
    }


}