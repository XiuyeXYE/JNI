package com.xiuye.jni;

public class NewString {

	static {
		System.loadLibrary("L");
	}
	
	private static native String newString(); 
	
	public static void main(String[] args) {

	}

}
