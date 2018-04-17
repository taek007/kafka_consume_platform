#include <stdio.h>
#include <jni.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
 /*

 g++ -o testjava testjava.cpp -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux -L${JRE_HOME}/lib/i386/client -L/usr/lib/jvm/java-1.8.0-openjdk-1.8.0.151-1.b12.el6_9.x86_64/jre/lib/amd64/server   -ljvm	 -Wl,-rpath,/usr/lib/jvm/java-1.8.0-openjdk-1.8.0.151-1.b12.el6_9.x86_64/jre/lib/amd64/server


 gcc -o testjavac testjava.c -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux -L${JRE_HOME}/lib/i386/client -L/usr/lib/jvm/java-1.8.0-openjdk-1.8.0.151-1.b12.el6_9.x86_64/jre/lib/amd64/server   -ljvm	 -Wl,-rpath,/usr/lib/jvm/java-1.8.0-openjdk-1.8.0.151-1.b12.el6_9.x86_64/jre/lib/amd64/server

 */


jstring stoJstring(JNIEnv* env, const char* pat)
{
  jclass strClass = (*env)->FindClass(env, "java/lang/String");
  jmethodID ctorID = (*env)->GetMethodID(env, strClass, "<init>", "([BLjava/lang/String;)V");
  jbyteArray bytes = (*env)->NewByteArray(env, strlen(pat));
  (*env)->SetByteArrayRegion(env, bytes, 0, strlen(pat), (jbyte*)pat);
  jstring encoding = (*env)->NewStringUTF(env, "utf-8");
  return (jstring)(*env)->NewObject(env, strClass, ctorID, bytes, encoding);
}

 


char* jstringTostring(JNIEnv* env, jstring jstr) {
	char* rtn = NULL;
	jclass clsstring = (*env)->FindClass(env, "java/lang/String");
	jstring strencode = (*env)->NewStringUTF(env,"utf-8");
	jmethodID mid = (*env)->GetMethodID(env,clsstring, "getBytes", "(Ljava/lang/String;)[B");
	jbyteArray barr= (jbyteArray)(*env)->CallObjectMethod(env,jstr, mid, strencode);
	jsize alen = (*env)->GetArrayLength(env,barr);
	jbyte* ba = (*env)->GetByteArrayElements(env,barr,JNI_FALSE);
	if(alen > 0){
		rtn = (char*)malloc(alen + 1);
		memcpy(rtn, ba, alen);
		rtn[alen] = 0;
	}
	(*env)->ReleaseByteArrayElements(env,barr, ba, 0);

	return rtn;
}

jint create_vm(JavaVM** jvm, JNIEnv** env) {  
	JavaVMInitArgs vm_args;
	JavaVMOption options[2];
	
	
	

	//http://www.iteye.com/problems/89141
	//https://blog.csdn.net/qq_32583189/article/details/53172316
	/*
	JNIEnv
	*/
	 options[0].optionString = (char*)"-Djava.compiler=NONE";

	 options[1].optionString = (char*)"-Djava.class.path=.";
	 //options[2].optionString = "-verbose:jni"; //用于跟踪运行时的信息

	 vm_args.version = JNI_VERSION_1_4; // JDK版本号
	 vm_args.nOptions = 2;
	 vm_args.options = options;
	 vm_args.ignoreUnrecognized = JNI_TRUE;

	return JNI_CreateJavaVM(jvm, (void**)env, &vm_args);
}

jclass find_class(JNIEnv* env, const char* class_name) {
	jclass cls;
	jmethodID mid;
	jobject jobj;

	cls = (*env)->FindClass(env, "com/test/MyTest");  // 在这里查找ava类
	if(cls !=0){
		printf("find java class success\n");
		// 构造函数
		mid = (*env)->GetMethodID(env, cls,"<init>","()V");
		if(mid !=0) {
			jobj=(*env)->NewObject(env, cls,mid);
			printf("init ok\n");
		}
	   
	   //打印版本号
	   jint version = (*env)->GetVersion(env);
	   if (version == JNI_VERSION_1_8 ) {
			printf("version is JNI_VERSION_1_8\n");
	   }
	   return cls;
	}
}

<<<<<<< HEAD
int call_function(JNIEnv** env, jclass cls, const char* function_name) {
=======
int call_function(JNIEnv* env, jclass cls, const char* type, const char* function_name, const char* sign) {
>>>>>>> fed1e2a506df6e0dea9bad33cfd5dc5cea417d23
	// 调用add函数
	jmethodID mid;

	mid = (*env)->GetStaticMethodID(env, cls, "add", "(II)I");

	if(mid !=0){
		jint square;
		square = (*env)->CallStaticIntMethod(env, cls, mid, 5,5);
		printf(" square is %d\n", square);
		
	}
}

int destroy_vm(JavaVM* jvm) {
	return (*jvm)->DestroyJavaVM(jvm);
}

int main() {
	JavaVM *jvm;
	JNIEnv *env;
	

	
	
	
	jboolean jnot;
	jobject jobj;
jmethodID mid;
	long status = create_vm(&jvm, &env);
	if(status == JNI_ERR){
		printf("create java jvm fail\n");
		return -1;
	}

		{
		printf("create java jvm success\n");
		jclass cls =find_class(env, "com/test/MyTest");
		//jclass cls = (*env)->FindClass(env, "com/test/MyTest");  // 在这里查找ava类
		if(cls !=0){
			/*
			printf("find java class success\n");
			// 构造函数
			mid = (*env)->GetMethodID(env, cls,"<init>","()V");
			if(mid !=0) {
				jobj=(*env)->NewObject(env, cls,mid);
				printf("init ok\n");
			}
	   
		   //打印版本号
		   jint version = (*env)->GetVersion(env);
		   if (version == JNI_VERSION_1_8 ) {
				printf("version is JNI_VERSION_1_8\n");
		   }
		   */
  
			
		call_function(env, cls, "add");

			/*
			// 调用judge函数
			mid = (*env)->GetMethodID(env, cls, "judge","(Z)Z");
			if(mid !=0){
				jnot = (*env)->CallBooleanMethod(env, jobj, mid, 1);
				if(!jnot) {
					printf("Boolean ok");
				}
			}
			*/
		} else {
			fprintf(stderr, "FindClass failed\n");
		}
	 
		(*jvm)->DestroyJavaVM(jvm);
		fprintf(stdout, "Java VM destory.\n");

		return 0;
	}   

}