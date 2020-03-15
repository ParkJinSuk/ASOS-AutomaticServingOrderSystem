package com.songtaeheon.tracingorder.adapter

import android.content.Context
import android.content.Intent
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Toast
import androidx.recyclerview.widget.RecyclerView
import com.songtaeheon.tracingorder.activity.DishActivity
import com.songtaeheon.tracingorder.model.MenuItem
import com.songtaeheon.tracingorder.R
import kotlinx.android.synthetic.main.main_recycler_item.view.*

class MainAdapter(val mContext : Context, val list:ArrayList<MenuItem> ) : RecyclerView.Adapter<MainAdapter.Holder>() {
    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int) : Holder {
        val view = LayoutInflater.from(mContext).inflate(R.layout.main_recycler_item, parent, false)
        return Holder(view)
    }

    override fun onBindViewHolder(holder: Holder, position: Int) {
        val item = list[position]
        val listener = View.OnClickListener {
            val intent = Intent(mContext, DishActivity::class.java)
            intent.putExtra(mContext.getString(R.string.memu_item), item)
            mContext.startActivity(intent)
        }
        holder.apply{
            bind(listener, item)
            itemView.tag = item
        }
    }

    override fun getItemCount() = list.size


    inner class Holder(itemView : View) : RecyclerView.ViewHolder(itemView){
        private var view = itemView
        fun bind(listener: View.OnClickListener, item: MenuItem) {
            view.thumbnail_imageview.setImageDrawable(mContext.getDrawable(item.imageIndex))
            view.title_edittext.setText(item.name)
            view.price_edittext.setText(String.format(mContext.getString(R.string.price_text),item.price));
            view.setOnClickListener(listener)
        }
    }


}