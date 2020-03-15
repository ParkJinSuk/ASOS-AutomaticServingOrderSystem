package com.songtaeheon.tracingorder.model

data class CartItem(val id:Int, val name:String, val price:Int, val imageIndex: Int, var cnt:Int){
    constructor(menuItem: MenuItem, cnt:Int) : this(-1, menuItem.name, menuItem.price, menuItem.imageIndex, cnt)
}