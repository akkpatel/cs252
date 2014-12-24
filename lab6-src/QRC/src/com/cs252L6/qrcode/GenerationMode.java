package com.cs252L6.qrcode;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.Toast;

public class GenerationMode extends Activity {

	Button textButton, urlButton, imageButton, phoneNoButton;
	ImageButton backButton;
	public int buttonFlag = 0;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.generate_mode);

		textButton = (Button) findViewById(R.id.textButton);
		urlButton = (Button) findViewById(R.id.urlButton);
		imageButton = (Button) findViewById(R.id.imageButton);
		phoneNoButton = (Button) findViewById(R.id.phoneNoButton);
		backButton = (ImageButton) findViewById(R.id.backGMButton);

		textButton.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				buttonFlag = 1;
				//sendToast();
				enterText();
			}
		});
		
		urlButton.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				buttonFlag = 2;
				//sendToast();
				enterText();
			}
		});
		
		imageButton.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				buttonFlag = 3;
				sendToast();
			}
		});
		
		phoneNoButton.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				buttonFlag = 4;
				sendToast();
			}
		});
		
		backButton.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				Intent intent = new Intent(GenerationMode.this, ActivityMain.class);
				startActivity(intent);
			}
		});
	}

	private void sendToast() {
		switch (buttonFlag) {
			case 1:
				Toast.makeText(getApplicationContext(), "Text Button is pressed.", Toast.LENGTH_SHORT).show();
				break;
			case 2:
				Toast.makeText(getApplicationContext(), "Web Address Button is pressed.", Toast.LENGTH_SHORT).show();
				break;
			case 3:
				Toast.makeText(getApplicationContext(), "Image Button is pressed.", Toast.LENGTH_SHORT).show();
				break;
			case 4:
				Toast.makeText(getApplicationContext(), "Phone Number Button is pressed.", Toast.LENGTH_SHORT).show();
				break;
		}
	}
	
	public void enterText(){
		Intent intent = new Intent(GenerationMode.this, SelectText.class);
		startActivity(intent);
	}

}
