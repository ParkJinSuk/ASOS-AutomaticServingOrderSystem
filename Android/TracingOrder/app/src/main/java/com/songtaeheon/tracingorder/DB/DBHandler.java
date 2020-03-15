package com.songtaeheon.tracingorder.DB;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.util.Log;

import com.songtaeheon.tracingorder.model.CartItem;

import java.util.ArrayList;

public class DBHandler {

    private final String TAG = "DBHandler";

    private SQLiteOpenHelper mHelper;
    private SQLiteDatabase mDB = null;

    public DBHandler(Context context, String name) {
        mHelper = new DBHelper(context, name, null, 1);
    }

    public DBHandler(Context context) {
        mHelper = new DBHelper(context, DBConstants.DB_NAME, null, 1);
    }

    private Cursor selectAllCartData(){
        mDB = mHelper.getReadableDatabase();
        Cursor c = mDB.rawQuery("SELECT * FROM " + DBConstants.CART_TABLE_NAME, null);
        return c;
    }

    public ArrayList<CartItem> getAllCartList(){
        Log.d(TAG, "getAllMemo");
        ArrayList<CartItem> list = new ArrayList<>();

        Cursor cursor = selectAllCartData();
        if(cursor != null){
            cursor.moveToFirst();
            if(cursor.getCount() != 0) {
                do {
                    CartItem cartItem = new CartItem(
                                    cursor.getInt(cursor.getColumnIndex(DBConstants.ID)),
                                    cursor.getString(cursor.getColumnIndex(DBConstants.NAME)),
                                    cursor.getInt(cursor.getColumnIndex(DBConstants.PRICE)),
                                    cursor.getInt(cursor.getColumnIndex(DBConstants.IMAGE_INDEX)),
                                    cursor.getInt(cursor.getColumnIndex(DBConstants.CNT)));

                    Log.d(TAG, "cart list : " + cartItem.getName() + " 개수 : " + cartItem.getCnt());
                    list.add(cartItem);
                } while (cursor.moveToNext());
            }
        }
        cursor.close();
        return list;
    }




    public void deleteCart(int id)
    {
        Log.d(TAG, "delete");
        mDB = mHelper.getWritableDatabase();
        mDB.delete(DBConstants.CART_TABLE_NAME, "_ID=?", new String[]{Integer.toString(id)});
    }

    public void deleteAllCart()
    {
        Log.d(TAG, "deleteAll");
        mDB = mHelper.getWritableDatabase();
        mDB.delete(DBConstants.CART_TABLE_NAME, null, null);
    }

    public void putItemCart(CartItem cartMenu){
        mDB = mHelper.getReadableDatabase();
        Cursor c = mDB.rawQuery("SELECT * FROM " + DBConstants.CART_TABLE_NAME + " WHERE " + DBConstants.NAME + "=\"" + cartMenu.getName() +"\"", null);
        if(c != null) {
            c.moveToFirst();
            if (c.getCount() == 0) {
                insertCart(cartMenu);
            } else {
                cartMenu.setCnt(cartMenu.getCnt()+c.getInt(c.getColumnIndex(DBConstants.CNT)));
                Log.d(TAG, "cart list : " + cartMenu.getName() + " 개수 : " + cartMenu.getCnt());
                updateCartMenu(cartMenu);
            }
        }


    }
    public void insertCart(CartItem cartMenu){
        mDB = mHelper.getWritableDatabase();

        ContentValues value = new ContentValues();
        value.put(DBConstants.NAME, cartMenu.getName());
        value.put(DBConstants.PRICE, cartMenu.getPrice());
        value.put(DBConstants.CNT, cartMenu.getCnt());
        value.put(DBConstants.IMAGE_INDEX, cartMenu.getImageIndex());

        mDB.replace(DBConstants.CART_TABLE_NAME, null, value);
    }

    public void updateCartMenu(CartItem cartMenu)
    {
        Log.d(TAG, "update");
        mDB = mHelper.getWritableDatabase();

        ContentValues value = new ContentValues();
        value.put(DBConstants.NAME, cartMenu.getName());
        value.put(DBConstants.PRICE, cartMenu.getPrice());
        value.put(DBConstants.CNT, cartMenu.getCnt());
        value.put(DBConstants.IMAGE_INDEX, cartMenu.getImageIndex());
        mDB.update(DBConstants.CART_TABLE_NAME, value, DBConstants.NAME + "=\"" + cartMenu.getName() +"\"", null);
    }




    public void close() {
        mHelper.close();
    }

}