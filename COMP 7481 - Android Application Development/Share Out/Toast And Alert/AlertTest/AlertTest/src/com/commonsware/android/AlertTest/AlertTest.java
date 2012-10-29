package com.commonsware.android.AlertTest;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.*;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import java.util.Date;

public class AlertTest extends Activity implements View.OnClickListener {
	  Button alert;
	  Button toast;

	  @Override
	  public void onCreate(Bundle icicle) {
	    super.onCreate(icicle);

	    setContentView(R.layout.main);

	    alert=(Button)findViewById(R.id.alert);
	    alert.setOnClickListener(this);
	    toast=(Button)findViewById(R.id.toast);
	    toast.setOnClickListener(this);
	  }

	  public void onClick(View view) {
	    if (view==alert) {
	      new AlertDialog.Builder(this)
	        .setTitle("MessageDemo")
	        .setMessage("eek!")
	        .setNeutralButton("Close", new DialogInterface.OnClickListener() {
	          public void onClick(DialogInterface dlg, int sumthin) {
	            // do nothing - it will close on its own
	          }
	        })
	        .show();
	    }
	    else {
	      Toast.makeText(this, "<clink, clink>", Toast.LENGTH_SHORT)

	        .show();
	    }
	  }
	}
