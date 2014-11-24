<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>RomanConverter</title>
</head>

<body>
<pre>
<?php
	define('APP_ROOT', __DIR__.'/../app/');
	require_once('../app/inc/util/autoLoading.inc');

	$testcase = array(
			"nyankofunjattad",
			"sammaippaitottorisakyuu",
			"hambaiinkaraiewokaushin'you",
			"kin'yuusyoruikinyuu",
			"hampanasemmonchisiki",
			"furoppi-dhisukudoraivu",
			"konzai混在soryaxanailwa",
			"shupa-ten oputhime-ta-",
	);
	$conv = RomanConverter::getInstance();
	foreach ($testcase as $str) {
		echo $conv->convert($str)."\n";
	}
	echo mb_convert_kana('ヴァイエンｼｭﾃﾌｧﾝ.オプ', 'cH', 'UTF-8')."\n";
?>
</pre>
</body>
</html>
