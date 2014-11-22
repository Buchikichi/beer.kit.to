<?php
class ItemTagsDao extends DaoBase {
	function getList($itemId, $lang) {
		$resultList = array();
		$query = <<<EOD
SELECT
  TGN.noun
FROM
  item_tags TGS
INNER JOIN noun TGN ON
  TGS.tagId = TGN.nounId
  AND TGN.lang = :lang
WHERE
  TGS.itemId = :itemId
ORDER BY
  TGN.noun
EOD;
		$param = array('itemId'=>$itemId, 'lang'=>$lang);
		$list = $this->select($query, $param);
		foreach ($list as $rec) {
			$resultList[] = $rec['noun'];
		}
		return $resultList;
	}
}
