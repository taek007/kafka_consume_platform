1.生成.class文件
javac -d . MyTest.java

2.产生c 可执行文件
g++ -o testjava testjava.cpp -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux -L${JRE_HOME}/lib/i386/client -L/usr/lib/jvm/java-1.8.0-openjdk-1.8.0.151-1.b12.el6_9.x86_64/jre/lib/amd64/server   -ljvm -Wl,-rpath,/usr/lib/jvm/java-1.8.0-openjdk-1.8.0.151-1.b12.el6_9.x86_64/jre/lib/amd64/server

3../testjava 
create java jvm success
find java class success
init ok
version is JNI_VERSION_1_8
10
Boolean ok
Java VM destory.
