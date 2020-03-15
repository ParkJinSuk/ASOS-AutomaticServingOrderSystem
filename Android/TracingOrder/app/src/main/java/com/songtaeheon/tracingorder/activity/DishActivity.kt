package com.songtaeheon.tracingorder.activity

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.Menu
import android.widget.*
import com.songtaeheon.tracingorder.DB.DBHandler
import com.songtaeheon.tracingorder.model.CartItem
import com.songtaeheon.tracingorder.model.MenuItem
import com.songtaeheon.tracingorder.R

class DishActivity : AppCompatActivity() {

    var cnt = 1
    private val dbHandler = DBHandler(this)
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_dish)

        val item = intent.getSerializableExtra(getString(R.string.memu_item)) as MenuItem

        val titleTextView = findViewById<TextView>(R.id.title_textview)
        val priceTextView = findViewById<TextView>(R.id.price_textview)
        val imageView = findViewById<ImageView>(R.id.imageView)
        val cartButton = findViewById<Button>(R.id.cart_button)
        val plusButton = findViewById<ImageButton>(R.id.plus_imageButton)
        val minusButton = findViewById<ImageButton>(R.id.minus_imageButton)
        val cntText = findViewById<TextView>(R.id.cnt_textview)

        plusButton.setOnClickListener(({
            if(cnt < 9) {
                cnt += 1
                cntText.text = cnt.toString()
            }else{
                Toast.makeText(this, "한 번에 9개까지 주문 가능합니다.", Toast.LENGTH_SHORT).show()
            }
        }))
        minusButton.setOnClickListener(({
            if(cnt > 1) {
                cnt -= 1
                cntText.text = cnt.toString()
            }
        }))



        titleTextView.text = item.name
        priceTextView.text = String.format(getString(R.string.price_text), item.price)
        imageView.setImageDrawable(getDrawable(item.imageIndex))

        cartButton.setOnClickListener(({
            dbHandler.putItemCart(CartItem(item, cnt))
            Toast.makeText(this, "장바구니에 담았습니다.", Toast.LENGTH_SHORT).show()
        }))
    }

    //액션버튼 메뉴 액션바에 집어 넣기
    override fun onCreateOptionsMenu(menu: Menu?): Boolean {
        menuInflater.inflate(R.menu.menu_cart, menu)
        return true
    }

    override fun onOptionsItemSelected(item: android.view.MenuItem): Boolean {
        when(item.itemId){
            R.id.action_cart -> {
                val myIntent = Intent(this, CartActivity::class.java)
                startActivity(myIntent)
                finish()
                return super.onOptionsItemSelected(item)
            }
        }
        return super.onOptionsItemSelected(item)
    }
}
