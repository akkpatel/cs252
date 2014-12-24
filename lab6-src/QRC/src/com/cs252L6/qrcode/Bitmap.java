package com.cs252L6.qrcode;

import android.os.Bundle;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.ContentResolver;
import android.content.DialogInterface;
import android.graphics.BitmapFactory;
import android.util.Log;
import android.view.Menu;
import android.view.ViewGroup.LayoutParams;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.Toast;

public class Bitmap extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_bitmap);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.bitmap, menu);
		return true;
	}
	
	public void createDialog(){
		AlertDialog.Builder myDialog = new AlertDialog.Builder(this);
		myDialog.setTitle("Image Selected");
		myDialog.setIcon(R.drawable.ic_launcher);
		Log.i("Dialog set", "Dialog Set");
		ImageView newView = new ImageView(this);
		ContentResolver cr = getContentResolver();
		//newView.setImageBitmap();
		Log.i("image set", "Image view set");
		LayoutParams imageViewLayoutParams = new LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT);
		newView.setLayoutParams(imageViewLayoutParams);
		LinearLayout layout = new LinearLayout(this);
		layout.addView(newView);
		myDialog.setView(layout);
		myDialog.setPositiveButton("Use Image", new DialogInterface.OnClickListener() {
			
			@Override
			public void onClick(DialogInterface dialog, int which) {
				// TODO Auto-generated method stub
				Toast.makeText(getApplicationContext(), "Used Image", Toast.LENGTH_SHORT).show();
			}
		});
		myDialog.show();
	}

}
