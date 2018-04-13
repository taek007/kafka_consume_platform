#include "stdio.h"
#include "stdlib.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <errno.h>
/*
gcc -o c_php  c_php.c  -L. -lc_php  -Wl,-rpath,.

gcc -o test  test.c -L../lib -lc_php -Wl,-rpath,../lib

./test test2.php

*/



int main(int argc, char * argv[]){
	 if (argc <= 1) {
        printf("Usage: ./test /path/to/php");
        return -1;
    }

	//int argc        = 1;
	// char *argv[2]   = { "embed7", "/home/python_test/c_php/test2.php" };
	php_embed_start(argv[1]);

	int i=5;
	while(i> 0){
		i--;
		call_function("abc");
		sleep(3);
	}
	
	php_embed_end();
    return 0;
}