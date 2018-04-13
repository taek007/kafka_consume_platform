<?php
/*
class Test{

	function saveRecord($msg){
		//实例化redis
   //  $redis = new Redis();
     //连接
  //  $redis->connect('127.0.0.1', 3379);
     //检测是否连接成功
  //  echo "22222 Server is running: " . $redis->ping() ."\n";
	echo "receive: " . $msg ."\n";
	}
}
*/

class consume extends Queue {
	public unction	start($msg) {
		echo "recive:\n" . $msg . "\n";
	}
}

//$msg = "abc";
//PHP_check_syntax("/home/source/librdkafka/examples/newphp", $msg);


/*
for (i = 0; i < argc; i++) {
 516         zval_ptr_dtor(&argv[i]);
 517     }


*/