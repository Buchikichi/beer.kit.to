<?php
class ItemListAction extends ActionBase {
	function process() {
		$lang = $this->getLang();
		$dao = new ItemDao();
		$list = $dao->getList($lang);
		$result = array('result'=>'OK', 'list'=>$list);
		echo json_encode($result);
	}
}
