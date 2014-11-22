<?php
abstract class ActionBase {
	/**
	 * process.
	 */
	abstract function process();

	/**
	 * Execute.
	 */
	public function execute() {
		$this->process();
	}

	protected function getLang() {
		$lang = null;
		if (!empty($_REQUEST['lang'])) {
			$lang = $_REQUEST['lang'];
		}
		if (empty($lang)) {
			if (!empty($_SERVER['HTTP_ACCEPT_LANGUAGE'])) {
				$lang = substr($_SERVER['HTTP_ACCEPT_LANGUAGE'], 0, 2);
			} else {
				$lang = 'ja';
			}
		}
		return $lang;
	}
}
