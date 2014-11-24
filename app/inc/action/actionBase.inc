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

	protected function getParam($name, $default = '') {
		$val = $default;
		if (!empty($_REQUEST[$name])) {
			$val = $_REQUEST[$name];
		}
		return $val;
	}

	protected function getLang() {
		$lang = $this->getParam('lang');
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
