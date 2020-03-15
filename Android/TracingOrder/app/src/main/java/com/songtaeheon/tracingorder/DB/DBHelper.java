package com.songtaeheon.tracingorder.DB;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.widget.Toast;

public class DBHelper extends SQLiteOpenHelper {
    private final String TAG = "DBHelper";
    private Context context;
    public DBHelper(Context context, String name, SQLiteDatabase.CursorFactory factory, int version) {
        super(context, name, factory, version);
        this.context = context;
    }
    /** * Database가 존재하지 않을 때, 딱 한번 실행된다.
     *  * DB를 만드는 역할을 한다.
     *  * @param db */
    @Override
    public void onCreate(SQLiteDatabase db) {
        //meme table 생성
        StringBuffer sb1 = new StringBuffer();
        sb1.append(" CREATE TABLE IF NOT EXISTS " + DBConstants.CART_TABLE_NAME +" ( ");
        sb1.append(DBConstants.ID + " INTEGER PRIMARY KEY AUTOINCREMENT, ");
        sb1.append(DBConstants.NAME + " TEXT,  ");
        sb1.append(DBConstants.PRICE + "  INTEGER,  ");
        sb1.append(DBConstants.CNT + "  INTEGER,  ");
        sb1.append(DBConstants.IMAGE_INDEX + " INTEGER) ");

        db.execSQL(sb1.toString());
    }
    /** * Application의 버전이 올라가서
     * * Table 구조가 변경되었을 때 실행된다.
     * * @param db * @param oldVersion
     * * @param newVersion
     * */
    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        Toast.makeText(context, "데이터베이스 버전이 올라갔습니다.", Toast.LENGTH_SHORT).show();
    }

}
