#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*

http://php.tedu.cn/data/199171.html


/home/source/php-7.1.6/sapi/embed/php_embed.h

ulimit -c unlimited


gcc -o c2php 1.c  -I/home/source/php-7.1.6 -I/usr/local/php7/include/php/  -I/usr/local/php7/include/php/main    -I/usr/local/php7/include/php/Zend -I/usr/local/php7/include/php/TSRM   -L/home/source/php-7.1.6/libs  -lphp7



CFLAGS="-g -gdwarf-2 -g3" CXXFLAGS="-g -gdwarf-2 -g3"
./configure --prefix=/usr/local/php7 \
--with-curl \
--with-iconv-dir \
--with-kerberos \
--with-libdir=lib64 \
--with-libxml-dir \
--with-mysqli \
--with-openssl \
--with-pcre-regex \
--with-pdo-mysql \
--with-pear \
--with-zlib \
--enable-fpm \
--enable-bcmath \
--enable-mbregex \
--enable-mbstring \
--enable-opcache \
--enable-pcntl \
--enable-sockets \
--enable-zip \
--enable-embed \
--enable-debug


gcc -g  -o c2php 2.c  -I/usr/local/php-7.1.6 -I/usr/local/php-7.1.6/include/php/  -I/usr/local/php-7.1.6/include/php/main    -I/usr/local/php-7.1.6/include/php/Zend -I/usr/local/php-7.1.6/include/php/TSRM   -L/usr/local/php-7.1.6/lib/   -lphp7  -Wl,-rpath,/home/source/php-7.1.6/libs



gcc  -shared -fPIC -g  -o libc_php.so  c_php.c  -I/usr/local/php-7.1.6 -I/usr/local/php-7.1.6/include/php/  -I/usr/local/php-7.1.6/include/php/main    -I/usr/local/php-7.1.6/include/php/Zend -I/usr/local/php-7.1.6/include/php/TSRM   -L/usr/local/php-7.1.6/lib/   -lphp7  -Wl,-rpath,/home/source/php-7.1.6/libs


gcc  -shared -fPIC -g  -o ../lib/libc_php.so  c_php.c `pkg-config --cflags --libs glib-2.0`   -I/usr/local/php7.1.5 -I/usr/local/php7.1.5/include/php/  -I/usr/local/php7.1.5/include/php/main    -I/usr/local/php7.1.5/include/php/Zend -I/usr/local/php7.1.5/include/php/TSRM   -L ../lib  -lphp7  -lzlog -Wl,-rpath,/home/python_test/c_php/c_php/lib



gcc  -shared -fPIC -g  -o ../lib/libc_php.so  c_php.c `pkg-config --cflags --libs glib-2.0`   -I/usr/local/php7.1.5 -I/usr/local/php7.1.5/include/php/  -I/usr/local/php7.1.5/include/php/main    -I/usr/local/php7.1.5/include/php/Zend -I/usr/local/php7.1.5/include/php/TSRM   -L ../lib  -lphp7  -lzlog


gcc  -shared -fPIC -g  -o ./lib/libc_php.so  ./src/c_php.c `pkg-config --cflags --libs glib-2.0`   -I/usr/local/php7.1.5 -I/usr/local/php7.1.5/include/php/  -I/usr/local/php7.1.5/include/php/main    -I/usr/local/php7.1.5/include/php/Zend -I/usr/local/php7.1.5/include/php/TSRM   -L ./lib  -lphp7  -lzlog

gcc -o test  test.c -L../lib -lc_php -Wl,-rpath,../lib

./test test2.php
*/

#include "c_php.h"

static void execute_function(char* function_name1, zval* msg){
	zval retval;	

	zval function;
	ZVAL_STRINGL(&function, function_name1, strlen(function_name1));

	//zval params;
	//ZVAL_STRINGL(&params, msg, strlen(msg));
	
	

	/*
	这个方法也行
	zval retval;	
	zval function;	
	zend_string  *function_string=NULL;
	char* function_name="hahah";
	function_string = zend_string_init(function_name, strlen(function_name), 0);
	ZVAL_STR(&function, function_string); //设置变量的值
	*/
	
    call_user_function(EG(function_table), NULL, &function, &retval, 1, msg TSRMLS_CC);
	
	 // 转字符串
    php_printf("%s\n", Z_STRVAL(retval));

	// zval_dtor(&params);  
    zval_dtor(&retval);  
	 zval_dtor(&function); 
	//zend_string_free(function);
}



PHP_MINIT_FUNCTION(queue){  
        zend_class_entry queue;  
        INIT_CLASS_ENTRY(queue, PARENT_CLASS_NAME ,secure_methods);//初始化  
        secure_ce=zend_register_internal_class_ex(&queue,NULL);  
        secure_ce->ce_flags=ZEND_ACC_IMPLICIT_PUBLIC;  
        return SUCCESS;  
};  

PHP_METHOD(PARENT_CLASS_NAME, __construct){  
	zval *this_ptr = getThis();
	execute_function("get_class", this_ptr);
    php_printf("construct is running");  
};  

PHP_METHOD(PARENT_CLASS_NAME, __destruct){  
   
};  

PHP_METHOD(PARENT_CLASS_NAME, test){  
   php_printf("this is Secure::test");  
};  



/*php脚本调用c函数*/
/*
PHP_FUNCTION(phpcapi_response) {
    RETURN_LONG(42);
}

PHP_MINIT_FUNCTION(cengine) {
    //REGISTER_INI_ENTRIES();
    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(cengine)
{
    //UNREGISTER_INI_ENTRIES();
    return SUCCESS;
}


static zend_function_entry cengine_php_funcs[] = {
    PHP_FE(phpcapi_response,        NULL)
    { NULL, NULL, NULL }
};
*/


/* 注册php模块 */
zend_module_entry php_mymod_module_entry = {
    STANDARD_MODULE_HEADER,
    "c_php", /* extension name */
    NULL,//secure_methods, /* function entries */
	PHP_MINIT(queue),
	NULL,
    NULL, /* RINIT */
    NULL, /* RSHUTDOWN */
    NULL, /* MINFO */
    "1.0", /* version */
    STANDARD_MODULE_PROPERTIES
};

static int cli_seek_file_begin2(zend_file_handle *file_handle, char *script_file, int *lineno)
{
    int c;

    *lineno = 1; 

    file_handle->type = ZEND_HANDLE_FP;
    file_handle->opened_path = NULL;
    file_handle->free_filename = 0; 
    if (!(file_handle->handle.fp = VCWD_FOPEN(script_file, "rb"))) {
        php_printf("Could not open input file: %s\n", script_file);
        return FAILURE;
    }    
    file_handle->filename = script_file;

    /* #!php support */
    c = fgetc(file_handle->handle.fp);
    if (c == '#' && (c = fgetc(file_handle->handle.fp)) == '!') {
        while (c != '\n' && c != '\r' && c != EOF) {
            c = fgetc(file_handle->handle.fp);  /* skip to end of line */
        }    
        /* handle situations where line is terminated by \r\n */
        if (c == '\r') {
            if (fgetc(file_handle->handle.fp) != '\n') {
                zend_long pos = zend_ftell(file_handle->handle.fp);
                zend_fseek(file_handle->handle.fp, pos - 1, SEEK_SET);
            }    
        }    
        *lineno = 2; 
    } else {
        rewind(file_handle->handle.fp);
    }

    return SUCCESS;
}

/*
main/main.c
PHPAPI int php_lint_script(zend_file_handle *file)
{
    zend_op_array *op_array;
    int retval = FAILURE;

    zend_try {
        op_array = zend_compile_file(file, ZEND_INCLUDE);
        zend_destroy_file_handle(file);

        if (op_array) {
            destroy_op_array(op_array);
            efree(op_array);
            retval = SUCCESS;
        }    
    } zend_end_try();
    if (EG(exception)) {
        zend_exception_error(EG(exception), E_ERROR);
    }    

    return retval;
}


*/

static void check_php_script( char *script_file) {
	int exit_status = SUCCESS;
	zend_file_handle file_handle;
	
	int lineno;
		if (cli_seek_file_begin2(&file_handle, script_file, &lineno) != SUCCESS) {
			php_printf("error\n");
		}

	exit_status = php_lint_script(&file_handle);
	if (exit_status!=SUCCESS) {
		zend_printf("Errors parsing %s\n", file_handle.filename);

	}


}

static void include_php( char *filename) {
    zend_first_try {
        char *include_script;
        spprintf(&include_script, 0, "include '%s';", filename);
        if(zend_eval_string(include_script, NULL, filename TSRMLS_CC) != FAILURE) {
			zend_printf("include  %s error\n", filename);
		}
        efree(include_script);
    } zend_end_try();
	check_php_script(filename);
}

//int class_call_user_method(zval *obj, zval* function_name,  uint32_t params_count, zval params[]){ 
int class_call_user_method(uint32_t params_count, zval params[]){ 
	zval retval;
    HashTable *function_table; 

    if(obj) { 
                function_table = &Z_OBJCE_P(obj)->function_table;
        }else{
                function_table = (CG(function_table));
    }

    // 对象初始化内容，不能放在这里
    // if(!obj_ce){

    //      object_init(&obj);
    // }
    // else{

    //      object_init_ex(&obj, obj_ce);
    // }

    zend_fcall_info fci;  
    fci.size = sizeof(fci);  
   // fci.function_table = function_table;  
    fci.object =  obj ? Z_OBJ_P(obj) : NULL;;
    fci.function_name = *function_name;   
    fci.retval = &retval;  
    fci.param_count = params_count;  
    fci.params = params;  
    fci.no_separation = 1;  
    //fci.symbol_table = NULL;  
	
    /**/
    int result;
    result = zend_call_function(&fci, NULL TSRMLS_CC);         //函数调用结束。  
	
    if (result == FAILURE) {
		//todo
        //zend_printf("error\n");
    }else{
		//todo
		//zend_printf("Success\n");
	}
	zval_dtor(&retval);  
}

void get_child_class_entry(){
	zend_class_entry *ce = NULL;
	for (zend_hash_internal_pointer_reset(EG(class_table));
		zend_hash_has_more_elements(EG(class_table)) == SUCCESS;
		zend_hash_move_forward(EG(class_table))) {

			if ((ce = zend_hash_get_current_data_ptr(EG(class_table))) == NULL) {
				continue;
			}

			if (ce->type == ZEND_USER_CLASS && !strcmp( ZSTR_VAL(ce->parent->name), PARENT_CLASS_NAME) ) {
				char* class_name = ZSTR_VAL(ce->name);
				//php_printf("\n%d\n",ce->type);
				//php_printf("%s\n",ZSTR_VAL(ce->name));
				child_ce = ce;
				break;
				/*
				zval obj;
				object_init_ex(&obj, ce);  
				
				zval function_name;
				ZVAL_STRING(&function_name,"saveRecord");

				*/


				/*
				obj = (zval*)emalloc(sizeof(zval)); 
				object_init_ex(obj, ce);  

				function_name = (zval*)emalloc(sizeof(zval)); 
				ZVAL_STRING(function_name,"saveRecord");
				//break;
				*/
			}
	}
	child_ce = ce;
}

void php_embed_start( char *filename_local) {
	filename = filename_local;

	char *array[2] = {"embed7", "/home/python_test/c_php/test2.php"};
	php_embed_init(2,  array TSRMLS_C);
	zend_startup_module(&php_mymod_module_entry);
	include_php(filename);

	/*
		zval obj;
		object_init_ex(&obj, ce);  
		
		zval function_name;
		ZVAL_STRING(&function_name,"saveRecord");

	*/
	
	//获取php代码中继承指定父类Secure的子类,赋值到全局变量 zend_class_entry *child_ce; 中
	get_child_class_entry();

	obj = (zval*)emalloc(sizeof(zval)); 
	object_init_ex(obj, child_ce);  

	function_name = (zval*)emalloc(sizeof(zval)); 
	ZVAL_STRING(function_name, PARENT_FUNCTION_NAME);
}

void call_function(const char* msg){
	int file_modify_time = 0;
	file_modify_time = get_file_size_time(filename);
	
	//文件被修改了
	if(file_modify_time > last_modify_time ){
		last_modify_time = file_modify_time;
		php_embed_end();
		php_embed_start( filename );
	}

	zval params[1];
	ZVAL_STRINGL(&params[0], msg, strlen(msg)+1);

	//class_call_user_method(&obj, &function_name, 1,params);
	zend_try {
		class_call_user_method(1, params);
	}	zend_catch{
			zend_printf("call_user_function  %serror\n", Z_STRVAL_P(function_name));
	}zend_end_try(); 

	zval_dtor(&params[0]); 
}

void php_embed_end(){
	/*
	释放全局变量
	*/
	if(obj !=NULL){
		zval_dtor(obj);  
	}

	if(function_name !=NULL){
		zval_dtor(function_name);
	}

	php_embed_shutdown(TSRMLS_CC); 
}

static int get_file_size_time (const char *filename) {
  struct stat statbuf;
  if (stat (filename, &statbuf) == -1) {
      printf ("Get stat on %s Error：%s\n", filename, strerror (errno));
      return (-1);
  }
  if (S_ISDIR (statbuf.st_mode)){
    return (1);
  }
  if (S_ISREG (statbuf.st_mode)){
	   return statbuf.st_mtime;
    printf ("%s size：modified at %s, %d",
        filename, ctime (&statbuf.st_mtime), statbuf.st_mtime);
  }
  return 0;
 
}

void zlog_start(const char *zlog_filename){
	int rc;
	rc = zlog_init(zlog_filename);
	printf("aaa %s\n", zlog_filename);
	if (rc) {
		printf("init failed\n");
		return;
	}
 
	z_log = zlog_get_category("my_cat");
	if (!z_log) {
		printf("get cat fail\n");
		zlog_fini();
		return;
	}
	zlog_info(z_log, "zlog_filename is:%s", zlog_filename);
}

void zlog_end(){
	zlog_fini();
}


/*
int main(){
    int argc        = 1;
    char *argv[2]   = { "embed7", "/home/python_test/c_php/test2.php" };
    php_embed_start(argc, argv );
	call_function();
	php_embed_end();
   return 0;
}
*/






