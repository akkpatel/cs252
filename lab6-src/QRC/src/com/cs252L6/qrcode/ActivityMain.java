package com.cs252L6.qrcode;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.StreamCorruptedException;
import java.io.UnsupportedEncodingException;
import java.nio.ByteBuffer;
import android.util.Base64;
import android.annotation.TargetApi;

import com.parse.*;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.ContentResolver;
import android.content.ContentValues;
import android.content.DialogInterface;
import android.content.Intent;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.provider.MediaStore;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup.LayoutParams;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

import com.cs252L6.qrcode.util.SystemUiHider;

/**
 * An example full-screen activity that shows and hides the system UI (i.e.
 * status bar and navigation/system bar) with user interaction.
 * 
 * @see SystemUiHider
 */

public class ActivityMain extends Activity { 
	public Button GenerateButton;
	public Button ScanButton;
	public Button QrButton;
	public Button InfoButton;
	public TextView tapView;
	public View lineSp1;
	public View lineSp2;
	public int methodFlag = 0;
	public int buttonFlag = -1;
	public Uri imageUri;
	private Bitmap bitmap;
	private Bitmap storeBitmap;
	public ParseObject file;
	 String DB_NAME = "ImageSave";
	 String TABLE_NAME = "mytable";
	 private String selectedImagePath;
	 private static final String id = "_id";
	 private static final String name = "name";
	 newDatabase db;
	 int flag = 0;
	 private int imageId = 0;
	 public String imageName;
	/**
	 * 
	 * Whether or not the system UI should be auto-hidden after
	 * {@link #AUTO_HIDE_DELAY_MILLIS} milliseconds.
	 */
	private static final boolean AUTO_HIDE = true;

	/**
	 * If {@link #AUTO_HIDE} is set, the number of milliseconds to wait after
	 * user interaction before hiding the system UI.
	 */
	private static final int AUTO_HIDE_DELAY_MILLIS = 3000;

	/**
	 * If set, will toggle the system UI visibility upon interaction. Otherwise,
	 * will show the system UI visibility upon interaction.
	 */
	private static final boolean TOGGLE_ON_CLICK = true;

	/**
	 * The flags to pass to {@link SystemUiHider#getInstance}.
	 */
	private static final int HIDER_FLAGS = SystemUiHider.FLAG_HIDE_NAVIGATION;

	/**
	 * The instance of the {@link SystemUiHider} for this activity.
	 */
	private SystemUiHider mSystemUiHider;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.qrc_activity_main);
		
		GenerateButton = (Button) findViewById(R.id.button1);
		ScanButton = (Button) findViewById(R.id.button2);
		QrButton = (Button) findViewById(R.id.button3);
		InfoButton = (Button) findViewById(R.id.infoButton);
		tapView = (TextView) findViewById(R.id.textView1);
		lineSp1 = (View) findViewById(R.id.lineSp1);
		lineSp2 = (View) findViewById(R.id.lineSp2);	
		Parse.initialize(getApplicationContext(), "yKkIvzOD5a1CtZz1OLJliGQOrUgTyt7kbbalMt9K", "Vmws984qWJi401saErYSogTdi0tyfWIg0kFz2v0q");

		final View controlsView = findViewById(R.id.fullscreen_content_controls);
		final View contentView = findViewById(R.id.fullscreen_content);
		
		GenerateButton.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				selectContent();
			}
		});
		
		ScanButton.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				openScan();
			}
		});
		
		InfoButton.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				Intent intent = new Intent(ActivityMain.this, InfoPage.class);
				startActivity(intent);
			}
		});

		// Set up an instance of SystemUiHider to control the system UI for
		// this activity.
		mSystemUiHider = SystemUiHider.getInstance(this, contentView,
				HIDER_FLAGS);
		mSystemUiHider.setup();
		mSystemUiHider
				.setOnVisibilityChangeListener(new SystemUiHider.OnVisibilityChangeListener() {
					// Cached values.
					int mControlsHeight;
					int mShortAnimTime;

					@Override
					@TargetApi(Build.VERSION_CODES.HONEYCOMB_MR2)
					public void onVisibilityChange(boolean visible) {
						if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB_MR2) {
							// If the ViewPropertyAnimator API is available
							// (Honeycomb MR2 and later), use it to animate the
							// in-layout UI controls at the bottom of the
							// screen.
							if (mControlsHeight == 0) {
								mControlsHeight = controlsView.getHeight();
							}
							if (mShortAnimTime == 0) {
								mShortAnimTime = getResources().getInteger(
										android.R.integer.config_shortAnimTime);
							}
							controlsView
									.animate()
									.translationY(visible ? 0 : mControlsHeight)
									.setDuration(mShortAnimTime);
						} else {
							// If the ViewPropertyAnimator APIs aren't
							// available, simply show or hide the in-layout UI
							// controls.
							controlsView.setVisibility(visible ? View.VISIBLE
									: View.GONE);
						}

						if (visible && AUTO_HIDE) {
							// Schedule a hide().
							delayedHide(AUTO_HIDE_DELAY_MILLIS);
						}
					}
				});

		// Set up the user interaction to manually show or hide the system UI.
		contentView.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View view) {
				if (TOGGLE_ON_CLICK) {
					mSystemUiHider.toggle();
				} else {
					mSystemUiHider.show();
				}
			}
		});

		// Upon interacting with UI controls, delay any scheduled hide()
		// operations to prevent the jarring behavior of controls going away
		// while interacting with the UI.
		//findViewById(R.id.dummy_button).setOnTouchListener(
			//	mDelayHideTouchListener);
		db = new newDatabase(this);
	}
	

	@Override
	protected void onPostCreate(Bundle savedInstanceState) {
		super.onPostCreate(savedInstanceState);

		// Trigger the initial hide() shortly after the activity has been
		// created, to briefly hint to the user that UI controls
		// are available.
		delayedHide(100);
	}

	/**
	 * Touch listener to use for in-layout UI controls to delay hiding the
	 * system UI. This is to prevent the jarring behavior of controls going away
	 * while interacting with activity UI.
	 */
	View.OnTouchListener mDelayHideTouchListener = new View.OnTouchListener() {
		@Override
		public boolean onTouch(View view, MotionEvent motionEvent) {
			if (AUTO_HIDE) {
				delayedHide(AUTO_HIDE_DELAY_MILLIS);
			}
			return false;
		}
	};

	Handler mHideHandler = new Handler();
	Runnable mHideRunnable = new Runnable() {
		@Override
		public void run() {
			mSystemUiHider.hide();
		}
	};

	/**
	 * Schedules a call to hide() in [delay] milliseconds, canceling any
	 * previously scheduled calls.
	 */
	private void delayedHide(int delayMillis) {
		mHideHandler.removeCallbacks(mHideRunnable);
		mHideHandler.postDelayed(mHideRunnable, delayMillis);
	}
	
	public void openScan(){
		//Toast.makeText(this, "Implement Scanner.", Toast.LENGTH_SHORT).show();
		//Log.d("test", "button works!");
	    Intent intent = new Intent("com.google.zxing.client.android.SCAN");
	    intent.putExtra("com.google.zxing.client.android.SCAN.SCAN_MODE", "QR_CODE_MODE");
	    startActivityForResult(intent, 0);
	}
	
    public void onActivityResult(int requestCode, int resultCode, Intent intent) {
    	//Log.d("test", "in Activity Result");
        if (requestCode == 0) {
            if (resultCode == RESULT_OK){
                String contents = intent.getStringExtra("SCAN_RESULT");
                if(contents.contains(".com")){
                	String temp;
                	if(contents.contains("http") || contents.contains("https")){
                		temp = "";
                	}else{
                		temp = "http://";
                	}
                	String finalString = temp + contents;
                	Uri newUri = Uri.parse(finalString);
                	Intent antIntent = new Intent(Intent.ACTION_VIEW, newUri);
                	startActivity(antIntent);
                }else{
                	if(contents.contains(".jpg")){
                		byte[] pic = null;
                		ParseQuery pq = new ParseQuery("Files");
                		pq.whereEqualTo("path",contents);
                		ParseObject result = null;
						try {
							result = pq.getFirst();
						} catch (ParseException e) {
							e.printStackTrace();
						}
                		ParseFile ret = result.getParseFile("file");
                		try {
                			pic = ret.getData();
						}catch(Exception e){
							Log.i("in the catch in parse", "in the catch in parse");
						}
                		String temp = Base64.encodeToString(pic, Base64.DEFAULT);
                		Bitmap nbmap = StringToBitMap(temp);
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
                				imageName = input.getEditableText().toString();
                				Toast.makeText(getApplicationContext(), "Image has been saved to Gallery.", Toast.LENGTH_SHORT).show();
                			}
                		});
                		AlertDialog list = builder.create();
                		list.show();
                		ContentResolver cr = getContentResolver();
                		try{
                			MediaStore.Images.Media.insertImage(cr, nbmap, imageName , "image.jpg");
                		}catch(Exception e){
                			Log.i("inside catch in store","inside catch in store");
                		}

                	}else{
                		showDecodedQR(contents);
                	}
                }
                // Handle successful scan
            }else if (resultCode == RESULT_CANCELED){
                // Handle cancel
                Log.i("Cancelled", "Cancelled");
            }
        }else if(requestCode == 1){
        	if(resultCode == RESULT_OK){
        		imageUri = intent.getData();
        		selectImage(imageUri);
        		//byte[] array = toByteArray(bitmap);
        		//insertData(array);
        	}
        }
    }
	
	public void activateButtons(View view){
		GenerateButton.setVisibility(View.VISIBLE);
		ScanButton.setVisibility(View.VISIBLE);
		QrButton.setVisibility(View.GONE);
		InfoButton.setVisibility(View.GONE);
		tapView.setVisibility(View.GONE);
		lineSp1.setVisibility(View.VISIBLE);
		lineSp2.setVisibility(View.VISIBLE);
		TextView tv = new TextView(this);
		tv = (TextView) findViewById(R.id.fullscreen_content);
		tv.setText("QRCode");
		tv.setTextSize(50);
	}
	
	private void selectContent(){
		AlertDialog.Builder builder = new AlertDialog.Builder(this);
		final String[] type_name = {"Text", "Web Address", "Image", "Phone Number"};
		builder.setTitle("Select the type of content");
		builder.setIcon(R.drawable.ic_launcher);
		builder.setItems(type_name, new DialogInterface.OnClickListener() {
			
			@Override
			public void onClick(DialogInterface dialog, int which) {
				//Toast.makeText(getApplicationContext(), type_name[which], Toast.LENGTH_SHORT).show();
				buttonFlag = which;
				switch(buttonFlag){
					case 0:
						makeEdit();
						break;
					case 1:
						makeEdit();
						break;
					case 2:
						loadImage();
						break;
					case 3:
						makeEdit();
						break;
				}
			}
		});
		AlertDialog list = builder.create();
		list.show();
	}
	
	@SuppressWarnings("deprecation")
	private void makeEdit(){
		AlertDialog.Builder edit = new AlertDialog.Builder(this);
		edit.setTitle("Enter text you would like to encode");
		edit.setIcon(R.drawable.ic_launcher);
		final EditText input = new EditText(this);
		LinearLayout.LayoutParams lp = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.FILL_PARENT, LinearLayout.LayoutParams.FILL_PARENT);
		input.setLayoutParams(lp);
		edit.setView(input);
		edit.setPositiveButton("OK", new DialogInterface.OnClickListener() {
			
			@Override
			public void onClick(DialogInterface dialog, int which) {
				String qrData = input.getEditableText().toString();
				Intent intent = new Intent(ActivityMain.this, DisplayMessageActivity.class);
				intent.putExtra("textData", qrData);
				startActivity(intent);
			}
		});
		edit.setNegativeButton("CANCEL", new DialogInterface.OnClickListener() {
			
			@Override
			public void onClick(DialogInterface dialog, int which) {
				dialog.cancel();
			}
		});
		AlertDialog editText = edit.create();
		editText.show();
	}
	
	private void loadImage(){
		Intent intent = new Intent(Intent.ACTION_PICK, android.provider.MediaStore.Images.Media.EXTERNAL_CONTENT_URI);
		startActivityForResult(intent, 1);
	}
	
	private void showDecodedQR(String display){
		AlertDialog.Builder builder = new AlertDialog.Builder(this);
		builder.setTitle("Encoded QR content is:")
		.setIcon(R.drawable.ic_launcher)
		.setMessage(display)
		.setNeutralButton("OK", null)
		.show();
		
	}
	
	private void selectImage(Uri tempUri){
		selectedImagePath = getPath(tempUri);
		AlertDialog.Builder myDialog = new AlertDialog.Builder(this);
		myDialog.setTitle("Image Selected");
		myDialog.setIcon(R.drawable.ic_launcher);
		ImageView imageView = new ImageView(this);
		ContentResolver cr = getContentResolver();
		try{
			bitmap = android.provider.MediaStore.Images.Media.getBitmap(cr, tempUri);
			bitmap = Bitmap.createScaledBitmap(bitmap, 700, 700, false);
		}catch(Exception e){
			Log.v("inside catch coudn't try", "inside catch coudn't try");
			Toast.makeText(this, e.getMessage(), Toast.LENGTH_SHORT).show();
		}
		imageView.setImageBitmap(bitmap);
		LayoutParams imageViewLayoutParams = new LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT);
		imageView.setLayoutParams(imageViewLayoutParams);
		LinearLayout layout = new LinearLayout(this);
		layout.addView(imageView);
		myDialog.setView(layout);
		myDialog.setPositiveButton("Use Image", new DialogInterface.OnClickListener() {
			
			@Override
			public void onClick(DialogInterface dialog, int which) {
				// TODO Auto-generated method stub
				byte[] temp = BitmapTobyte(bitmap); 
        		insertData(temp);
				insertRecord(imageId,temp,selectedImagePath);
        		String qrData = selectedImagePath;
				Intent intent = new Intent(ActivityMain.this, DisplayMessageActivity.class);
				intent.putExtra("textData", qrData);
				startActivity(intent);
			
				Toast.makeText(getApplicationContext(), "Used Image", Toast.LENGTH_SHORT).show();
			}
		});
		myDialog.setNeutralButton("Cancel", new DialogInterface.OnClickListener() {
			
			@Override
			public void onClick(DialogInterface dialog, int which) {
				// TODO Auto-generated method stub
				dialog.cancel();
			}
		});
		myDialog.setNegativeButton("Use Another", new DialogInterface.OnClickListener() {
			
			@Override
			public void onClick(DialogInterface dialog, int which) {
				// TODO Auto-generated method stub
				loadImage();
			}
		});
		myDialog.show();
	}
	
	public void insertRecord(int colId,byte[] data, String path){
		
		ParseFile file = new ParseFile(data); 
		try {
			file.save();
		} catch (ParseException e) {
			e.printStackTrace();
		}
		
		ParseObject object = new ParseObject("Files");
		object.put("path",path);
		object.put("columnId", colId);
		object.put("file", file);
		
		try {
			object.save();
		} catch (ParseException e) {
			e.printStackTrace();
		}
		return;
	}
	
	public byte[] getRecord(int colId) throws ParseException{
		ParseQuery pq = new ParseQuery("Files");
		pq.whereEqualTo("columnId",colId);
		ParseObject result = pq.getFirst();
		ParseFile ret = result.getParseFile("file");
		return ret.getData();
	}
	
    public String getPath(Uri uri) {
        String[] projection = { MediaStore.Images.Media.DATA };
        Cursor cursor = managedQuery(uri, projection, null, null, null);
        int column_index = cursor
                .getColumnIndexOrThrow(MediaStore.Images.Media.DATA);
        cursor.moveToFirst();
        return cursor.getString(column_index);
    }
    public byte[] toByteArray(Bitmap bmap){
    	  byte[] array;
    	  int width = bmap.getWidth();
    	  int height = bmap.getHeight();
    	  ByteBuffer buff = ByteBuffer.allocate(width*height*4);
    	  bmap.copyPixelsToBuffer(buff);
    	  array = buff.array();
    	  return array;
    }
    public void insertData(byte[] array){
    	  SQLiteDatabase sqlData = db.getReadableDatabase();
    	  ContentValues values = new ContentValues();
    	  values.put("image", array);
    	  values.put("path", selectedImagePath);
    	  sqlData.insert("newTable", null, values);
    	  Cursor cursor = sqlData.rawQuery("SELECT * FROM newTable ;", null);
    	  cursor.moveToFirst();
    	  int newId=0;
    	  while(cursor.moveToNext()){
    	   newId = cursor.getInt(cursor.getColumnIndex("_id"));
    	  }
    	  imageId = newId;
    }
    public void contents(){
    	  SQLiteDatabase sqlData = db.getReadableDatabase();
    	  Cursor cursor = sqlData.rawQuery("SELECT * FROM newTable ;", null);
    	  if(cursor.getCount()>0){
    	   if(cursor.moveToFirst()){
    	    do{
    	     int newPath = cursor.getInt(cursor.getColumnIndex("_id"));
    	    }while(cursor.moveToNext());
    	   }
    	  }
    }
    public void deleteContentsID(int id){
    	  int hi = id;
    	  SQLiteDatabase sqlData = db.getWritableDatabase();
    	  try{
    	   sqlData.delete("newTable", "_id =" + hi, null);
    	  }catch(Exception e){
    	   Log.i("not in the database", "not in the database");
    	  }
    }
    public byte[] BitmapTobyte(Bitmap bitmap){
    	ByteArrayOutputStream baos=new ByteArrayOutputStream();
    	bitmap.compress(Bitmap.CompressFormat.PNG,100, baos);
    	byte [] b=baos.toByteArray();
    	return b;
    }
    public Bitmap StringToBitMap(String encodedString){
    	try{
    		byte [] encodeByte=Base64.decode(encodedString,Base64.DEFAULT);
    		Bitmap bitmap = BitmapFactory.decodeByteArray(encodeByte, 0, encodeByte.length);
    		return bitmap;
    	}catch(Exception e){
    		e.getMessage();
    		return null;
    	}
    }
}
