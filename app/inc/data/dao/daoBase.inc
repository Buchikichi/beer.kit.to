<?php
define('DB_HOST', 'localhost');
define('DB_DSN', 'mysql:host='.DB_HOST.';dbname=drink;charset=utf8');
define('DB_USER', 'drink');
define('DB_PASS', 'drunker');

/**
 * Data access object.
 * @author H.Sasai
 *
 */
abstract class DaoBase {
	protected $pdo;

	function __construct() {
		$this->pdo = new PDO(DB_DSN, DB_USER, DB_PASS);
	}

	function connect() {
	}
}
