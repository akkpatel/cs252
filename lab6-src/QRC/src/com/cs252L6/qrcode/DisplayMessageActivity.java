package com.cs252L6.qrcode;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.ContentResolver;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Bitmap;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;
import android.util.Log;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

import com.google.zxing.BarcodeFormat;
import com.google.zxing.WriterException;
import com.google.zxing.client.android.Contents;
import com.google.zxing.client.android.encode.QRCodeEncoder;
//import android.support.v4.app.NavUtils;

public class DisplayMessageActivity extends Activity {
	public TextView qr_check;
	String qrData;
	Button BackButton, SaveButton;
	ImageView qrImage;
	Bitmap qr_image;
	private Uri newUri;
	private Uri pathUri;
	private Bitmap bitmap;
	
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_display_message);
		// Show the Up button in the action bar.
		BackButton = (Button) findViewById(R.id.backDMButton);
		SaveButton = (Button) findViewById(R.id.saveQRButton);
		qrImage = (ImageView) findViewById(R.id.qrCode);
		qrData = getIntent().getExtras().getString("textData");
		if(generateQR(qrData)){
			qr_check = (TextView) findViewById(R.id.textView2);
			qr_check.setVisibility(View.VISIBLE);
		}else{
			Toast.makeText(this, "Unable to generate QR code.", Toast.LENGTH_SHORT).show();
		}
		
		BackButton.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				Intent intent = new Intent(DisplayMessageActivity.this, ActivityMain.class);
				startActivity(intent);
			}
		});
		
		SaveButton.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
			    saveQRImage();
			}
		});
	}

	/**
	 * Set up the {@link android.app.ActionBar}.
	 */
	private void setupActionBar() {
		getActionBar().setDisplayHomeAsUpEnabled(true);
	}


	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		switch (item.getItemId()) {
		case android.R.id.home:
			// This ID represents the Home or Up button. In the case of this
			// activity, the Up button is shown. Use NavUtils to allow users
			// to navigate up one level in the application structure. For
			// more details, see the Navigation pattern on Android Design:
			//
			// http://developer.android.com/design/patterns/navigation.html#up-vs-back
			//
		//	NavUtils.navigateUpFromSameTask(this);
			return true;
		}
		return super.onOptionsItemSelected(item);
	}
	
	private boolean generateQR(String data){		
		int flag = 0;
		
		ImageView imageView = (ImageView) findViewById(R.id.qrCode);
		int qrcDim = 500;
		QRCodeEncoder qrCodeEncoder = new QRCodeEncoder(data, null,
		        Contents.Type.TEXT, BarcodeFormat.QR_CODE.toString(), qrcDim);

		try {
		    bitmap = qrCodeEncoder.encodeAsBitmap();
		    imageView.setImageBitmap(bitmap);
		    flag = 1;
		} catch (WriterException e) {
		    e.printStackTrace();
		}
		
		if(flag == 1){
			return true;
		}else{
			return false;
		}
	}
	
	private void sendToast(){
		Toast.makeText(this, "Implement save.", Toast.LENGTH_SHORT).show();
	}
	
	private void saveQRImage(){
		AlertDialog.Builder builder = new AlertDialog.Builder(this);
		builder.setTitle("Save Image as...");
		builder.setIcon(R.drawable.ic_launcher);
		final EditText input = new EditText(this);
		LinearLayout.LayoutParams lp = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.FILL_PARENT, LinearLayout.LayoutParams.FILL_PARENT);
		input.setLayoutParams(lp);
		builder.setView(input);
		builder.setPositiveButton("Save as", new DialogInterface.OnClickListener() {
			
			@Override
			public void onClick(DialogInterface dialog, int which) {
				String qrData = input.getEditableText().toString();
				ContentResolver cr = getContentResolver();
				try {
					pathUri = Uri.parse(MediaStore.Images.Media.insertImage(cr, bitmap, qrData , "image.jpg"));
				}catch(Exception e){
					Log.v("inside catch coudn't try", "inside catch coudn't try");
				}
			}
		});
		builder.setNegativeButton("CANCEL", new DialogInterface.OnClickListener() {
			
			@Override
			public void onClick(DialogInterface arg0, int arg1) {
				// TODO Auto-generated method stub
				arg0.cancel();
			}
		});
		AlertDialog list = builder.create();
		list.show();
	}

}
