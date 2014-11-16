<?php
class CountryListAction extends ActionBase {
	function process() {
		$lang = 'ja';

		if (!empty($_REQUEST['lang'])) {
			$lang = $_REQUEST['lang'];
		}
		$dao = new Iso3166Dao();
		$list = $dao->getList($lang);
		$result = array('result'=>'OK', 'list'=>$list);
		echo json_encode($result);
	}
}
