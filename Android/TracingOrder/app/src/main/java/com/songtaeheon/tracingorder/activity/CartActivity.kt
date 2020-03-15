package com.songtaeheon.tracingorder.activity

import android.content.DialogInterface
import android.os.AsyncTask
import android.os.Bundle
import android.util.Log
import android.view.View
import android.widget.Button
import android.widget.Toast
import androidx.appcompat.app.AlertDialog
import androidx.appcompat.app.AppCompatActivity
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.songtaeheon.tracingorder.DB.DBHandler
import com.songtaeheon.tracingorder.R
import com.songtaeheon.tracingorder.Utils.RequestHttpConnection
import com.songtaeheon.tracingorder.adapter.CartAdapter
import com.songtaeheon.tracingorder.interfaces.CartListener
import com.songtaeheon.tracingorder.model.CartItem
import com.songtaeheon.tracingorder.model.OrderItemSet
import kotlinx.android.synthetic.main.activity_cart.*
import org.json.JSONException
import org.json.JSONObject

class CartActivity : AppCompatActivity(), CartListener {

    lateinit var payButton:Button
    lateinit var recyclerView:RecyclerView
    lateinit var cartList:ArrayList<CartItem>
    var money = 0

    val dbHandler = DBHandler(this)
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_cart)
        cartList = dbHandler.getAllCartList()
        recyclerView = findViewById<RecyclerView>(R.id.cart_recyclerview)
        payButton = findViewById(R.id.payment_button)
        setMoney();
        val adapter = CartAdapter(this, cartList, this)
        recyclerView.adapter = adapter
        recyclerView.layoutManager = LinearLayoutManager(this)
    }

    fun onPaymentClick(view: View){
        var tables = arrayOf("TABLE1", "TABLE2", "TABLE3", "TABLE4", "TABLE5", "TABLE6", "TABLE7", "TABLE8")
        val dialog = AlertDialog.Builder(this)
        var choice = 0
        if(cartList.isEmpty()){
            Toast.makeText(this, "장바구니가 비어있습니다", Toast.LENGTH_LONG).show()
            return
        }
        dialog.setTitle("테이블을 선택하세요.")

        dialog.setSingleChoiceItems(tables, 0, DialogInterface.OnClickListener{ dialog: DialogInterface, which: Int ->
            choice = which
        })

        //결제 확인 버튼 클릭.
        dialog.setPositiveButton("확인", DialogInterface.OnClickListener{dialog: DialogInterface, which: Int ->
            sendData(choice)
        })

        dialog.setNegativeButton("취소", DialogInterface.OnClickListener{dialog: DialogInterface, which: Int ->
            Toast.makeText(this, "결제 취소!", Toast.LENGTH_LONG).show()
        })
        dialog.show()
    }

    override fun deleteCartItem() {
        setMoney();
    }

    fun setMoney(){
        money = 0;
        for(item in cartList)
            money += item.price * item.cnt

        payButton.text = String.format(getString(R.string.payment_button, money))
    }

    fun clearCart(){
        cartList.clear()
        recyclerView.adapter?.notifyDataSetChanged();
        dbHandler.deleteAllCart()
        setMoney()
    }

    fun sendData(choice:Int){
        try {
            val data = OrderItemSet(choice+1, cartList)
            val networkTask = NetworkTask(data)
            networkTask.execute()
        } catch (e: JSONException) {
            e.printStackTrace()
        }
    }


    inner class NetworkTask(val values: OrderItemSet) : AsyncTask<Unit?, Unit?, String?>() {

        override fun doInBackground(vararg p0: Unit?): String? {
            Log.d("ConnectionRequest", values.toString())
            val result: String? // 요청 결과를 저장할 변수.
            val requestHttpConnection = RequestHttpConnection()
            result = requestHttpConnection.request(values) // 해당 URL로 부터 결과물을 얻어온다.
            return result
        }

        override fun onPostExecute(s: String?) {
            super.onPostExecute(s)
            if (s != null) {
                Log.d("ConnectionResult", s)
                Toast.makeText(this@CartActivity, "주문 완료되었습니다.", Toast.LENGTH_LONG).show()
                clearCart()
            }
            else
                Log.e("ConnectionResult", "null")
        }

    }
}
