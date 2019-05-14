package com.xiuye.jni;

import com.xiuye.util.log.LogUtil;

public class NewString {

	static {
		System.loadLibrary("jni/com_xiuye_jni_NewString");
	}
	
	private static native String newString(); 
	
	public static void main(String[] args) {
		LogUtil.log(newString());
	}

}
