<?php
class ItemDetailAction extends ActionBase {
	function process() {
		$lang = $this->getLang();
		$itemId = $this->getParam('itemId');
		$dao = new ItemDao();
		$rec = $dao->getItem($lang, $itemId);
		$result = array('result'=>'OK', 'item'=>$rec);
		echo json_encode($result);
	}
}
