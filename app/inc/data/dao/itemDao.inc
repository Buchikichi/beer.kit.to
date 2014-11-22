<?php
class ItemDao extends DaoBase {
	function getList($lang) {
		$itemAttrDao = new ItemAttrDao();
		$itemTagsDao = new ItemTagsDao();
		$query = <<<EOD
SELECT
  ITM.itemId,
  ITM.countryCd,
  ITM.thumbnail,
  ITM.imgsrc,
  ITN.noun itemName,
  I3.flag
FROM
  `item` ITM
JOIN `noun` ITN on
  ITM.itemId = ITN.nounId
  AND ITN.lang = :lang
JOIN `iso3166` I3 on
  ITM.countryCd = I3.countryCd
ORDER BY
  ITN.noun
EOD;
		$param = array('lang'=>$lang);
		$list = $this->select($query, $param);
		foreach ($list as &$rec) {
			$itemId = $rec['itemId'];
			// ABV
			$abv = $itemAttrDao->getABV($itemId);
			$rec['abv'] = $abv;
			// tags
			$tags = $itemTagsDao->getList($itemId, $lang);
			$rec['tags'] = $tags;
		}
		return $list;
	}
}
