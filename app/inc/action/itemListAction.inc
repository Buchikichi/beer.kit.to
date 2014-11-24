<?php
class ItemListAction extends ActionBase {
	function process() {
		$lang = $this->getLang();
		$keyword = $this->getParam('keyword');
		$dao = new ItemDao();
		$list = $dao->getList($lang, $keyword);
		$result = array('result'=>'OK', 'list'=>$list);
		echo json_encode($result);
	}
}
