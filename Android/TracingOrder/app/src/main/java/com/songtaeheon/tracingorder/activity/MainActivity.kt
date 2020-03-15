package com.songtaeheon.tracingorder.activity

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity

import android.os.Bundle
import android.view.Menu
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.songtaeheon.tracingorder.adapter.MainAdapter
import com.songtaeheon.tracingorder.model.MenuItem
import com.songtaeheon.tracingorder.R

class MainActivity : AppCompatActivity() {

    var menuList = ArrayList<MenuItem>()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        val recyclerView = findViewById<RecyclerView>(R.id.cart_recyclerview)
        menuList.add(MenuItem(getString(R.string.pasta_tomato), 12000, R.drawable.pasta_tomato))
        menuList.add(MenuItem(getString(R.string.pasta_alio), 11000, R.drawable.pasta_alio))

        menuList.add(MenuItem(getString(R.string.risotto_tomato), 8900, R.drawable.risotto_tomato))
        menuList.add(MenuItem(getString(R.string.risotto_cream), 9900, R.drawable.risotto_cream))
        menuList.add(MenuItem(getString(R.string.ade_grapefruit), 4000, R.drawable.ade_grapefruit))
        menuList.add(MenuItem(getString(R.string.ade_greenapple), 4000, R.drawable.ade_greenapple))

        val adapter = MainAdapter(this, menuList);
        recyclerView.adapter = adapter
        recyclerView.layoutManager = LinearLayoutManager(this)

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
                return super.onOptionsItemSelected(item)
            }
            else -> return super.onOptionsItemSelected(item)
        }
    }

}
