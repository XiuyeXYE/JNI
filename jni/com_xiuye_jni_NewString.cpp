#include"com_xiuye_jni_NewString.h"
#include<iostream>
using namespace std;

/*
 * Class:     com_xiuye_jni_NewString
 * Method:    newString
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_xiuye_jni_NewString_newString
  (JNIEnv *env, jclass){
  	  jclass cls = env->FindClass("java/lang/String");
	  jmethodID cID = env->GetMethodID(cls,"<init>","([B)V");
	  
	  const char *s = "万里长城，哈哈哈哈哈.";
	  jsize len = strlen(s);
	  jbyteArray bArr = env->NewByteArray(len);
	  jbyte * bs = env->GetByteArrayElements(bArr,NULL);
	  memcpy(bs,s,len);
	  env->SetByteArrayRegion(bArr,0,len,bs);
	  env->ReleaseByteArrayElements(bArr,bs,0);
	  //不要提前delete否则输出是空的
	  //env->DeleteLocalRef(bArr);
	  jobject ret = env->NewObject(cls,cID,bArr);
	  //这里delete 数组仍然能输出字符串
	  //env->DeleteLocalRef(bArr);
	  //直接返回和加个ref效果差不多
	  //ret = env->NewLocalRef(ret);
	  //提前delete会有NullPointerException额。
	  //env->DeleteLocalRef(ret);
	  //env->DeleteGlobalRef(ret);
	  
	  return static_cast<jstring>(ret);
	  //return static_cast<jstring>(ret);
  }
