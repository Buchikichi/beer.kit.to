<?php
class CountryListAction extends ActionBase {
	function process() {
		$lang = $this->getLang();
		$dao = new Iso3166Dao();
		$list = $dao->getList($lang);
		$result = array('result'=>'OK', 'list'=>$list);
		echo json_encode($result);
	}
}
