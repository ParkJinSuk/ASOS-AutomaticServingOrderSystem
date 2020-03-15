package com.songtaeheon.tracingorder.model

import android.util.Log
import java.net.URLEncoder

class OrderItemSet(val tableNum:Int, val cartList:ArrayList<CartItem>) {

    private fun  makeListToStrForm():String{
        var strList = ""
        for(i in 0 until cartList.size){
            val item = cartList[i]
            strList += item.name +":" + item.cnt
            if(i != cartList.size-1)
                strList += "<br>"
        }
        strList = URLEncoder.encode(strList, "UTF-8")
        return strList
    }

    fun makeDataForm() : String{
        var strData = "table="+tableNum
        strData += "&"

        strData += "food="
        strData += makeListToStrForm()
        return strData;

    }

    override fun toString() = makeDataForm()
}