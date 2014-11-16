<?php
define('APP_ROOT', __DIR__);
include('inc/util/autoLoading.inc');

function execute() {
	$act = 'Error';
	if (isset($_REQUEST['act'])) {
		$act = ucfirst($_REQUEST['act']);
	}
	$ref = new ReflectionClass($act.'Action');
	$inst = $ref->newInstance();
	$inst->execute();
}
execute();
