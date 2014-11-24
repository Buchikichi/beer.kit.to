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

	static function escape($str) {
		$result = str_replace('%', '', $str);
		return str_replace('_', '', $result);
	}

	static function like($str) {
		return '%'.self::escape($str).'%';
	}

	function select($query, array $param = null) {
		$stmt = $this->pdo->prepare($query);
		try {
			$stmt->execute($param);
		} catch (PDOException $ex) {
			error_log($ex->getMessage());
		}
		return $stmt->fetchAll(PDO::FETCH_ASSOC);
	}

	function selectOne($query, array $param = null) {
		$result;
		$list = $this->select($query, $param);

		foreach ($list as $rec) {
			$result = $rec;
			break;
		}
		return $result;
	}
}
