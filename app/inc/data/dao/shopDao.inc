<?php
class ShopDao extends DaoBase {
	function getList($lang) {
		$query = <<<EOD
SELECT
 *
FROM
 `organization` OG
JOIN `noun` NN on
  OG.orgId = NN.nounId
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
