<?php
class ItemAttrDao extends DaoBase {
	function getABV($itemId) {
		$abv = '';
		$query = <<<EOD
SELECT
  ATR.val
FROM
  item_attr ATR
WHERE
  ATR.itemId = :itemId
  AND ATR.attrId = :attrId
EOD;
		$attrId = md5('AttrABV');
		$param = array('itemId'=>$itemId, 'attrId'=>$attrId);
		$rec = $this->selectOne($query, $param);
		return $rec['val'];
	}
}
