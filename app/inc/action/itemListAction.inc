<?php
class ItemListAction extends ActionBase {
	function process() {
		$lang = $this->getLang();
		$keyword = $this->getParam('keyword');
		$country = $this->getParam('country');
		$offset = $this->getParam('offset', 0);
		$limit = $this->getParam('limit', 10);
		$dao = new ItemDao();
		$param = array(
			'lang'=>$lang,
			'keyword'=>$keyword,
			'country'=>preg_split('/[\s]+/', $country),
			'offset'=>$offset,
			'limit'=>$limit,
		);
		$list = $dao->getList($param);
		$result = array('result'=>'OK', 'count'=>count($list),'list'=>$list);
		echo json_encode($result);
	}
}
