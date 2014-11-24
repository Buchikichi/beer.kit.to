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
  INM.noun itemName,
  INO.noun note,
  I3.flag
FROM
  `item` ITM
INNER JOIN `noun` INM on
  ITM.itemId = INM.nounId
  AND INM.lang = :lang
INNER JOIN `iso3166` I3 on
  ITM.countryCd = I3.countryCd
LEFT JOIN `noun` INO on
  ITM.noteId = INO.nounId
  AND INO.lang = :lang
WHERE
  ITM.itemId = :itemId
EOD;
		$dbParam = array(
			'lang'=>$lang,
			'itemId'=>$itemId);
		$rec = $this->selectOne($query, $dbParam);
		$itemId = $rec['itemId'];
		// ABV
		$abv = $itemAttrDao->getABV($itemId);
		$rec['abv'] = $abv;
		// tags
		$tags = $itemTagsDao->getList($itemId, $lang);
		$rec['tags'] = $tags;
		return $rec;
	}

	protected function makeInClause($field, array $values, &$dbParam) {
		$keyList = array();
		foreach ($values as $ix => $val) {
			if (empty($val)) {
				continue;
			}
			$key = ':ccd'.$ix;
			$dbParam[$key] = $val;
			$keyList[] = $key;
		}
		if (count($keyList) == 0) {
			return null;
		}
		return $field.' in ('.implode(',', $keyList).')';
	}

	/**
	 * Get list of items.
	 * @param mixed $param
	 * @return array: list of items
	 */
	function getList($param) {
		$itemAttrDao = new ItemAttrDao();
		$itemTagsDao = new ItemTagsDao();
		$conv = RomanConverter::getInstance();
		// dbParam
		$lang = $param['lang'];
		$keyword = $param['keyword'];
		$country = $param['country'];
		$lower = strtolower($keyword);
		$kana = $lower;
		$kana = str_replace('ヴ', 'ゔ', $kana);
		$kana = @mb_convert_kana($kana, 'cH', 'UTF-8');
		$kana = $conv->convert($kana);
		$dbParam = array(
			'lang'=>$param['lang'],
			'keyword'=>DaoBase::like($keyword),
			'kana'=>DaoBase::like($kana),
		);
		$cond = '';
		$inClause = $this->makeInClause('ITM.countryCd', $country, $dbParam);
		if (!empty($inClause)) {
			$cond .= $inClause;
		}
		if (!empty($cond)) {
			$cond = 'AND '.$cond;
		}
		// LIMIT
		$offset = $param['offset'];
		$limit = $param['limit'];
		// SQL
		$query = <<<EOD
SELECT
  ITM.itemId,
  ITM.countryCd,
  ITM.thumbnail,
  INM.noun itemName,
  INO.noun note,
  I3.flag
FROM
  `item` ITM
INNER JOIN `iso3166` I3 on
  ITM.countryCd = I3.countryCd
INNER JOIN `noun` INM on
  ITM.itemId = INM.nounId
  AND INM.lang = :lang
LEFT JOIN `noun` INO on
  ITM.noteId = INO.nounId
  AND INO.lang = :lang
WHERE
  ITM.itemId in (
    SELECT itemId FROM item
    WHERE
      synonym like :keyword
      OR synonym like :kana
  )
  $cond
ORDER BY
  ITM.countryCd,
  INM.noun
LIMIT $offset, $limit
EOD;
		$list = $this->select($query, $dbParam);
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
