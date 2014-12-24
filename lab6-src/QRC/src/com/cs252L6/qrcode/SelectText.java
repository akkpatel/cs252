package com.cs252L6.qrcode;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class SelectText extends Activity{
	
	Button GenerateTextButton, BackButton;
	EditText userText;
	String qrData;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.select_text);
		
		GenerateTextButton = (Button) findViewById(R.id.generateTextButton);
		BackButton = (Button) findViewById(R.id.backSTButton);
		userText = (EditText) findViewById(R.id.editText1);
		
		GenerateTextButton.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				qrData = userText.getText().toString();
				Intent intent = new Intent(SelectText.this, DisplayMessageActivity.class);
				intent.putExtra("textData", qrData);
				startActivity(intent);
			}
		});
		
		BackButton.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				Intent intent = new Intent(SelectText.this, GenerationMode.class);
				startActivity(intent);
			}
		});
		
	}

}
