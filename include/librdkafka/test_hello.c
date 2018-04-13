#include "stdio.h"
	 
	#include "zlog.h"
 
	int main(int argc, char** argv)
	{
	    int rc;
	    zlog_category_t *c;
	 
	    rc = zlog_init("test.conf");
	    if (rc) {
	        printf("init failed\n");
	        return -1;
	    }
	 
	    c = zlog_get_category("my_cat");
	    if (!my_cat) {
	        printf("get cat fail\n");
	        zlog_fini();
	        return -2;
	    }
	 
	    ZLOG_INFO(c, "hello, zlog");
	 
    zlog_fini();
	 
	    return 0;
	}
