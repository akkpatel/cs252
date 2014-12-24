package com.cs252L6.qrcode;
import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteDatabase.CursorFactory;
import android.database.sqlite.SQLiteOpenHelper;


public class newDatabase extends SQLiteOpenHelper {
 
 private static final String DB_NAME = "ImageSave";
 private static final String TABLE_NAME = "newTable";
 private static final String KeyId = "id";
 private static final String KeyPath = "path";
 private static final String KeyImage = "image";
 public newDatabase(Context context) {
  super(context, DB_NAME, null, 4);
  // TODO Auto-generated constructor stub
 }

 @Override
 public void onCreate(SQLiteDatabase db) {
  // TODO Auto-generated method stub
  db.execSQL("DROP TABLE IF EXISTS " + TABLE_NAME);
  db.execSQL("CREATE TABLE newTable (_id INTEGER PRIMARY KEY, image BLOB, path TEXT);");
 }

 @Override
 public void onUpgrade(SQLiteDatabase db, int arg1, int arg2) {
  // TODO Auto-generated method stub
  onCreate(db);
 }
}

