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
}
