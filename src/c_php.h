#ifndef _C_PHP_
#define _C_PHP_

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <errno.h>
/*包含php的sapi的embed头文件*/
#include "sapi/embed/php_embed.h"
#include "main/php_main.h"

#include "glib.h"
#include "zlog.h"


#define PARENT_CLASS_NAME  "Queue"
#define PARENT_FUNCTION_NAME  "start"


zend_class_entry *child_ce;
zval* obj;
zval* function_name;
int last_modify_time = 0;
zend_class_entry *secure_ce = NULL;  
zlog_category_t *z_log = NULL;

char* filename = NULL;

void php_embed_start( char *filename);
void call_function(const char* msg);
int class_call_user_method(uint32_t params_count, zval params[]); 
void php_embed_end();
static int get_file_size_time (const char *filename);
static void execute_function(char* function_name1, zval* msg);
static void include_php( char* filename);
static void get_child_class_entry();

void zlog_start(const char *zlog_filename);
void zlog_end();

PHP_METHOD(PARENT_CLASS_NAME,__construct);  
PHP_METHOD(PARENT_CLASS_NAME,__destruct);  
PHP_METHOD(PARENT_CLASS_NAME,test); 

PHP_FUNCTION(phpcapi_response);


const zend_function_entry secure_methods[]={  
	PHP_ME(PARENT_CLASS_NAME,__construct,NULL,ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)  
	PHP_ME(PARENT_CLASS_NAME,__destruct,NULL,ZEND_ACC_PUBLIC|ZEND_ACC_DTOR)  
	PHP_ME(PARENT_CLASS_NAME,test,NULL,ZEND_ACC_PUBLIC)  
	PHP_FE_END  
}; 

#endif