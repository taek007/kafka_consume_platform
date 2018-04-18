<?php

class Consume extends Queue {
	public function	start($msg) {
		echo "receive " . $msg . "\n";
	}
}



