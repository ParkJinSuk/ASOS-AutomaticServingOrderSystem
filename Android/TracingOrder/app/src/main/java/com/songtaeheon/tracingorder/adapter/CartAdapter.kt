package com.songtaeheon.tracingorder.adapter

import android.content.Context
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Toast
import androidx.recyclerview.widget.RecyclerView
import com.songtaeheon.tracingorder.DB.DBHandler
import com.songtaeheon.tracingorder.model.CartItem
import com.songtaeheon.tracingorder.R
import com.songtaeheon.tracingorder.interfaces.CartListener
import kotlinx.android.synthetic.main.cart_recycler_item.view.*
import kotlinx.android.synthetic.main.main_recycler_item.view.thumbnail_imageview

class CartAdapter(val mContext : Context, val list:ArrayList<CartItem>, val listener:CartListener ) : RecyclerView.Adapter<CartAdapter.Holder>() {
    val dbHandler = DBHandler(mContext)
    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int) : Holder {
        val view = LayoutInflater.from(mContext).inflate(R.layout.cart_recycler_item, parent, false)
        return Holder(view)
    }

    override fun onBindViewHolder(holder: Holder, position: Int) {
        val item = list[position]
        val listener = View.OnClickListener {
            list.remove(item)
            listener.deleteCartItem();
            dbHandler.deleteCart(item.id)
            notifyItemRemoved(position)
            Toast.makeText(mContext, "${item.name} is deleted", Toast.LENGTH_LONG).show()
        }
        holder.apply{
            bind(listener, item)
            itemView.tag = item
        }
    }

    override fun getItemCount() = list.size


    inner class Holder(itemView : View) : RecyclerView.ViewHolder(itemView){
        private var view = itemView
        fun bind(listener:View.OnClickListener, item: CartItem) {
            view.thumbnail_imageview.setImageDrawable(mContext.getDrawable(item.imageIndex))
            view.name_textView.text = item.name
            view.price_textView.text = String.format(mContext.getString(R.string.price_text),item.price)
            view.cnt_textView.text = String.format(mContext.getString(R.string.cnt_text),item.cnt)
            view.total_price_textView.text = String.format(mContext.getString(R.string.cnt_text),item.cnt*item.price)
            view.delete_imageview.setOnClickListener(listener)
        }
    }


}