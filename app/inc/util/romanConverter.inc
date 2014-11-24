<?php
class RomanConverter {
	private static $ME = null;
	private static $CONSONANT_LIST = array(
		"a"=>["あ", "い", "う", "え", "お"],
		"b"=>["ば", "び", "ぶ", "べ", "ぼ"],
		"c"=>["か", "し", "く", "せ", "こ"],
		"ch"=>["ちゃ", "ち", "ちゅ", "ちぇ", "ちょ"],
		"cy"=>["ちゃ", "ち", "ちゅ", "ちぇ", "ちょ"],
		"d"=>["だ", "ぢ", "づ", "で", "ど"],
		"f"=>["ふぁ", "ふぃ", "ふ", "ふぇ", "ふぉ"],
		"g"=>["が", "ぎ", "ぐ", "げ", "ご"],
		"h"=>["は", "ひ", "ふ", "へ", "ほ"],
		"j"=>["じゃ", "じ", "じゅ", "じぇ", "じょ"],
		"k"=>["か", "き", "く", "け", "こ"],
		"l"=>["ぁ", "ぃ", "ぅ", "ぇ", "ぉ"],
		"ly"=>["ゃ", "ぃ", "ゅ", "ぇ", "ょ"],
		"lw"=>["ゎ", "", "", "", ""],
		"m"=>["ま", "み", "む", "め", "も"],
		"n"=>["な", "に", "ぬ", "ね", "の"],
		"p"=>["ぱ", "ぴ", "ぷ", "ぺ", "ぽ"],
		"q"=>["くぁ", "くぃ", "く", "くぇ", "くぉ"],
		"r"=>["ら", "り", "る", "れ", "ろ"],
		"s"=>["さ", "し", "す", "せ", "そ"],
		"sh"=>["しゃ", "し", "しゅ", "しぇ", "しょ"],
		"t"=>["た", "ち", "つ", "て", "と"],
		"v"=>["ゔぁ", "ゔぃ", "ゔ", "ゔぇ", "ゔぉ"],
		"w"=>["わ", "ゐ", "う", "ゑ", "を"],
		"x"=>["ぁ", "ぃ", "ぅ", "ぇ", "ぉ"],
		"y"=>["や", "ゐ", "ゆ", "ゑ", "よ"],
		"z"=>["ざ", "じ", "ず", "ぜ", "ぞ"],
	);

	public static function getInstance() {
		if (is_null(self::$ME)) {
			self::$ME = new self();
		}
		return self::$ME;
	}

	private function choiceLetter($consonant, $vowel) {
		$buff = '';
		$row = null;

		if (isset(self::$CONSONANT_LIST[$consonant])) {
			$row = self::$CONSONANT_LIST[$consonant];
		} else {
			if (1 < strlen($consonant)) {
				$key = substr($consonant, 1);
				$first = $consonant[0];
				$second = $key[0];
	
				if ($first == 'm' || $first == 'n') {
					$buff .= 'ん';
				} else if ($first == $second) {
					$buff .= 'っ';
				}
				if (isset(self::$CONSONANT_LIST[$key])) {
					$row = self::$CONSONANT_LIST[$key];
				}
			}
		}
		if ($row != null) {
			$index = strpos('aiueo', $vowel);
			$buff .= $row[$index];
		}
		return $buff;
	}

	private function choice($candidate) {
		$buff = '';
		$splitPos = strlen($candidate) - 1;
		$consonant = substr($candidate, 0, $splitPos);
		$consonantLen = strlen($consonant);
		$vowel = $candidate[$splitPos];

		if ($consonantLen == 0) {
			// only vowel
			if ($vowel == '-') {
				$buff .= 'ー';
			} else if ($vowel == 'n') {
				$buff .= 'ん';
			} else {
				$buff .= $this->choiceLetter("a", $vowel);
			}
		} else if (1 < $consonantLen && substr($consonant, -1) == "y") {
			// 拗音
			$first = $consonant[0];
			$buff .= $this->choiceLetter($first, 'i');
			$buff .= $this->choiceLetter("ly", $vowel);
		} else if ("dh" == $consonant || "th" == $consonant) {
			// でぃてぃ
			$first = $consonant[0];
			$buff .= $this->choiceLetter($first, 'e');
			$buff .= $this->choiceLetter("ly", $vowel);
		} else {
			$buff .= $this->choiceLetter($consonant, $vowel);
		}
		return $buff;
	}

	private function chop($roman) {
		$buff = '';
		$isLastTarget = true;

		foreach (str_split(strtolower($roman)) as $ch) {
			$isTarget = 'a' <= $ch && $ch <= 'z' || $ch == '-';
			if ($isTarget && !$isLastTarget) {
				$buff .= " ";
			}
			$buff .= $ch;
			if ($ch == 'a' || $ch == 'i' || $ch == 'u' || $ch == 'e'
					|| $ch == 'o' || $ch == '-') {
				$buff .= " ";
			}
			$isLastTarget = $isTarget;
		}
		return preg_split("/[\s']/", $buff);
	}

	public function convert($roman) {
		$buff = '';

		foreach ($this->chop($roman) as $candidate) {
			if (empty($candidate)) {
				continue;
			}
			if (mb_ereg_match('[a-z-]+', $candidate) === false) {
				$buff .= $candidate;
			}
			if ("n" == $candidate) {
				$buff .= 'ん';
				continue;
			}
			if ("-" == $candidate) {
				$buff .=  'ー';
				continue;
			}
			if (strlen($candidate) == 1 && mb_ereg_match("[aiueo]", $candidate) === false) {
				// The middle of the input.
				continue;
			}
			$buff .= $this->choice($candidate);
		}
		return $buff;
	}
}
