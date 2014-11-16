<?php
class Iso639Dao extends DaoBase {
	function getList() {
		$query = <<<EOD
SELECT
 *
FROM
 `iso639`
ORDER BY
  lang
EOD;
		$stmt = $this->pdo->prepare($query);
		$stmt->execute();
		return $stmt->fetchAll(PDO::FETCH_ASSOC);
	}
}
