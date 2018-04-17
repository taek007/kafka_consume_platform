<?php

class Consume extends Queue {
	public function	start($msg) {
		echo "receive a##33" . $msg . "\n";
	}
}



