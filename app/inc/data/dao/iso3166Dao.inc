<?php
class Iso3166Dao extends DaoBase {
	function getList($lang) {
		$query = <<<EOD
SELECT
 *
FROM
 `iso3166` CC
JOIN `noun` NN on
  CC.nounId = NN.nounId
WHERE
  NN.lang = :lang
ORDER BY
  NN.noun
EOD;
		$param = array('lang'=>$lang);
		$stmt = $this->pdo->prepare($query);
		$stmt->execute($param);
		return $stmt->fetchAll(PDO::FETCH_ASSOC);
	}
}
