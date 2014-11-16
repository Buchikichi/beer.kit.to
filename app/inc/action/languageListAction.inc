<?php
class LanguageListAction extends ActionBase {
	function process() {
		$accept = 'en';
		if (!empty($_SERVER['HTTP_ACCEPT_LANGUAGE'])) {
			$accept = substr($_SERVER['HTTP_ACCEPT_LANGUAGE'], 0, 2);
		}
		$dao = new Iso639Dao();
		$list = $dao->getList();
		foreach ($list as &$rec) {
			if ($rec['lang'] == $accept) {
				$rec['checked'] = true;
			}
		}
		$result = array('result'=>'OK', 'list'=>$list);
		echo json_encode($result);
	}
}
