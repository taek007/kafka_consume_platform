#include "stdio.h"
#include "stdlib.h"
#include "/home/project/kafka_consume_platform/src/c_php.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <errno.h>
/*
gcc -o c_php  c_php.c  -L. -lc_php  -Wl,-rpath,.

gcc -o test  test.c  -I/usr/local/php7.1.5 -I/usr/local/php7.1.5/include/php/  -I/usr/local/php7.1.5/include/php/main    -I/usr/local/php7.1.5/include/php/Zend -I/usr/local/php7.1.5/include/php/TSRM -L../lib -lc_php -Wl,-rpath,../lib 


gcc -o test  test.c  `pkg-config --cflags --libs glib-2.0` -I/usr/local/php7.1.5 -I/usr/local/php7.1.5/include/php/  -I/usr/local/php7.1.5/include/php/main    -I/usr/local/php7.1.5/include/php/Zend -I/usr/local/php7.1.5/include/php/TSRM -L../lib -lc_php -Wl,-rpath,../lib


./test test2.php

*/


int restart;
int main(){
	

	//printf("%x\n", abc);

	//int argc        = 1;
	 char *argv[3]   = { "embed7", "/home/project/kafka_consume_platform/test/test2.php", "/home/project/kafka_consume_platform/conf/zlog.conf" };

	//work:
		PHP_VAR* php_var = php_embed_start( (const char*)argv[1], (const char*)argv[2]);
		PHP_VAR* php_var_var = NULL;
		//if(restart > 0) {
		//	goto con_work;
		//}
	int i=5;
	int res=0;
	while(i> 0){
		i--;
		con_work:
		res = call_function(php_var, &php_var_var, argv[1], argv[2], "abcww");
		if(res == 1){
			restart++;
			//goto work;
		}
		sleep(3);
	}
	
	php_embed_end();
    return 0;
}