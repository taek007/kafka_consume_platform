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



int last_modify_time = 0;
int restart = 0;


typedef struct {
	zend_class_entry *child_ce;
	zval* obj;
	zval* function_name;
	zlog_category_t *z_log;
}PHP_VAR;

zend_class_entry *secure_ce;

char* filename = NULL;

PHP_VAR* php_embed_start(const char *script_filename, const char* zlog_conf_name);
int call_function(PHP_VAR* php_var, const char* filename, const char* zlog_conf_file, const char* msg);
int class_call_user_method(zval *obj, zval* function_name,  uint32_t params_count, zval params[]);
void php_embed_end();
static int get_file_size_time (const char *filename);
static void execute_function(char* function_name1, zval* msg);
static void include_php( char* filename);
static zend_class_entry* get_child_class_entry();

zlog_category_t* zlog_start(const char *zlog_filename);
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