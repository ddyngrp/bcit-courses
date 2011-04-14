package org.trollop.http;

import android.app.Dialog;
import android.content.Context;
import android.widget.Button;
import android.widget.EditText;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.Window;

public class AuthenticationDialog extends Dialog implements OnClickListener {
	private EditText editUserName;
	private EditText editPassword;
	private Button btnOk;
	private Button btnCancel;
	private String userName;
	private String password;
	
	public AuthenticationDialog(Context context) {
		super(context);
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		setContentView(R.layout.authentication);
		btnOk = (Button)findViewById(R.id.btn_ok);
		btnCancel = (Button)findViewById(R.id.btn_cancel);
		editUserName = (EditText)findViewById(R.id.user_name);
		editPassword = (EditText)findViewById(R.id.password);
		
		btnOk.setOnClickListener(this);
		btnCancel.setOnClickListener(this);
	}

	public void onClick(View v) {
		if (v == btnOk) {
			userName = editUserName.getText().toString();
			password = editPassword.getText().toString();
			dismiss();
		}
		else {
			userName = null;
			password = null;
			dismiss();
		}
	}
	
	public String getUserName() {
		return userName;
	}
	
	public String getPassword() {
		return password;
	}
}
