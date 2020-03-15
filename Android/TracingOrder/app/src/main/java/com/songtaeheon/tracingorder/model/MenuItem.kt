package com.songtaeheon.tracingorder.model

import java.io.Serializable

data class MenuItem (val name:String, val price:Int, val imageIndex: Int) : Serializable{
    var cnt:Int = 0
}