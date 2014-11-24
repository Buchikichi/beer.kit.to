<?php
class ItemDao extends DaoBase {
	/**
	 * Get an item info.
	 * @param unknown $lang
	 * @param unknown $itemId
	 * @return multitype:
	 */
	function getItem($lang, $itemId) {
		$itemAttrDao = new ItemAttrDao();
		$itemTagsDao = new ItemTagsDao();
		$query = <<<EOD
SELECT
  ITM.itemId,
  ITM.countryCd,
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
WHERE
  ITM.itemId = :itemId
EOD;
		$param = array(
			'lang'=>$lang,
			'itemId'=>$itemId);
		$rec = $this->selectOne($query, $param);
		$itemId = $rec['itemId'];
		// ABV
		$abv = $itemAttrDao->getABV($itemId);
		$rec['abv'] = $abv;
		// tags
		$tags = $itemTagsDao->getList($itemId, $lang);
		$rec['tags'] = $tags;
		return $rec;
	}

	/**
	 * Get list of items.
	 * @param unknown $lang
	 * @param unknown $keyword
	 * @return array: list of items
	 */
	function getList($lang, $keyword) {
		$itemAttrDao = new ItemAttrDao();
		$itemTagsDao = new ItemTagsDao();
		$conv = RomanConverter::getInstance();
		$query = <<<EOD
SELECT
  ITM.itemId,
  ITM.countryCd,
  ITM.thumbnail,
  ITN.noun itemName,
  I3.flag
FROM
  `item` ITM
JOIN `noun` ITN on
  ITM.itemId = ITN.nounId
  AND ITN.lang = :lang
JOIN `iso3166` I3 on
  ITM.countryCd = I3.countryCd
WHERE
  ITM.itemId in (
    SELECT itemId FROM item
    WHERE
      synonym like :keyword
      OR synonym like :kana
  )
ORDER BY
  ITN.noun
EOD;
		$lower = strtolower($keyword);
		$kana = $lower;
		$kana = str_replace('ヴ', 'ゔ', $kana);
		$kana = @mb_convert_kana($kana, 'cH', 'UTF-8');
		$kana = $conv->convert($kana);
		$param = array(
			'lang'=>$lang,
			'keyword'=>DaoBase::like($keyword),
			'kana'=>DaoBase::like($kana));
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
