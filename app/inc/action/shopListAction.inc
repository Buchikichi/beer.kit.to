<?php
class ShopListAction extends ActionBase {
	function process() {
		$lang = $this->getLang();
		$dao = new ShopDao();
		$list = $dao->getList($lang);
		$result = array('result'=>'OK', 'list'=>$list);
		echo json_encode($result);
	}
}
