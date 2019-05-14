#include<jni.h>
#include<iostream>
#include <csignal>
#include<windows.h>
using namespace std;

bool CtrlHandler(DWORD fdwctrltype){cout << "fdwctrltype="<<fdwctrltype << endl;return true;}


LRESULT CALLBACK KeyboardProc(
  _In_ int    code,
  _In_ WPARAM wParam,
  _In_ LPARAM lParam
  ){
	  cout << "===HOOK S===" <<endl;
	  cout << code << endl;
	  cout << wParam << endl;
	  cout << lParam << endl;
	  cout << "===HOOK E===" <<endl;
	  return 0;
  }

int main(){
	SetWindowsHookEx(WH_KEYBOARD,KeyboardProc,NULL,0);
	set_terminate([](){cout<<"terminate" <<endl;});
	signal(SIGINT,[](int sig){cout << "signal=" << sig << endl;});
	atexit([](){cout << "atexit" << endl;});
	at_quick_exit([](){cout << "at_quick_exit" << endl;});
	SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler,true);
	JavaVM *jvm;
	JNIEnv *env;
	JavaVMInitArgs vm_args;
	JavaVMOption options[5];
	options[0].optionString = "-verbose";
	options[1].optionString = "-Xms256m";
	options[2].optionString = "-Xmx1024m";
	options[3].optionString = "-XX:MaxPermSize=1024m";
	options[4].optionString = "-Dsun.java.command=MyJNI";
	vm_args.version = JNI_VERSION_1_8;
	vm_args.nOptions = 5;
	vm_args.options = options;
	vm_args.ignoreUnrecognized = false;
	
	/* load and initialize a Java VM, return a JNI interface
	* pointer in env */
	if(JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args)==JNI_OK){
		
		
		
		/* invoke the Main.test method using the JNI */
		jclass cls = env->FindClass("java/lang/System");
		jfieldID fID = env->GetStaticFieldID(cls,"out","Ljava/io/PrintStream;");
		jobject out = env->GetStaticObjectField(cls,fID);
		jclass outCls = env->GetObjectClass(out);
		jmethodID mID = env->GetMethodID(outCls, "println", "(Ljava/lang/String;)V");
		//ctrl + c 并未结束jvm程序
		while(true){
			/*
			JavaVMInitArgs defaultVMArgs;
			defaultVMArgs.version = JNI_VERSION_1_8;
			defaultVMArgs.nOptions=0;
			defaultVMArgs.options=NULL;
			defaultVMArgs.ignoreUnrecognized=false;
			if(JNI_GetDefaultJavaVMInitArgs(&defaultVMArgs)==JNI_OK){
				for(int i=0;i<defaultVMArgs.nOptions;i++){
					cout << defaultVMArgs.options[i].optionString << endl;
				}
			
			}
			*/
			
			jstring str = env->NewStringUTF("欢迎来到JNI的世界！哈哈哈哈哈哈哈哈");
			env->CallVoidMethod(out,mID,str);
			//存在内存泄漏，可以通过jprofiler 看到
			//一定要释放额!!!!!!!!
			env->DeleteLocalRef(str);
			JavaVM *jvms;
			jsize count=0;
			//只能获取本进程创建的虚拟机
			jint result = JNI_GetCreatedJavaVMs(&jvms,sizeof(JavaVM)*10,&count);
			if(result == JNI_OK){
				cout << jvm << endl;
				cout << count << endl;
			}
		}
		
		//env->CallStaticVoidMethod(cls, mid, 100);
		/* We are done. */
	}
	
	
	
	
	
	
	jvm->DestroyJavaVM();
	
	
	system("pause");

	return 0;
}