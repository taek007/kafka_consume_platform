# kafka_c_php_consume
c调用php消费kafka数据
==== 

业务方不需要关于队列的连接,数据的消费，只关心自己的业务逻辑<br> 

该项目支持多语言, 消费数据逻辑使用librdkafka<br> 
对于php语言<br> 
php embed为依托, 执行业务逻辑中的相应方法<br> 

example php
``` 
<?php

class Consume extends Queue {
	public function	start($msg) {
		echo "receive " . $msg . "\n";
	}
}
``` 
其中Consume为业务自定义类, Queue为项目中定义的类名，业务方需要继承此父类<br> 
start也为指定的方法, 项目中会执行此方法<br> 
