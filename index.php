<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<link rel="stylesheet" href="http://ajax.googleapis.com/ajax/libs/jqueryui/1.11.2/themes/smoothness/jquery-ui.css"/>
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.0/css/bootstrap.min.css">
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.0/css/bootstrap-theme.min.css">
<link rel="stylesheet" href="css/default.css">
<script src="http://ajax.googleapis.com/ajax/libs/jquery/2.1.1/jquery.min.js"></script>
<script src="http://ajax.googleapis.com/ajax/libs/jqueryui/1.11.2/jquery-ui.min.js"></script>
<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.0/js/bootstrap.min.js"></script>
<script src="js/index.js"></script>
<title>drink.kit.to</title>
</head>

<?php
	define('APP_ROOT', __DIR__.'/app');
	include(APP_ROOT.'/inc/util/autoLoading.inc');
?>
<body>
  <nav class="navbar navbar-default navbar-fixed-top" role="navigation">
    <div class="container">
      <div class="navbar-header"><span class="navbar-brand">drink.kit.to</span></div>
      <div class="navbar-collapse collapse">
        <ul class="nav navbar-nav">
          <li><a href="#country"><span class="glyphicon glyphicon-globe"></span></a></li>
          <li><a href="#shop"><span class="glyphicon glyphicon-book"></span></a></li>
          <li><a href="#kind"><span class="glyphicon glyphicon-glass"></span></a></li>
          <li><a href="#tags"><span class="glyphicon glyphicon-tags"></span></a></li>
<!--
          <li class="dropdown disabled">
            <a href="#test" class="dropdown-toggle disabled" data-toggle="dropdown"><span class="glyphicon glyphicon-heart"></span></a>
            <ul class="dropdown-menu" role="menu"></ul>
          </li>
-->
          <li class="dropdown">
            <a aria-expanded="false" href="#" class="dropdown-toggle" data-toggle="dropdown"><span class="glyphicon glyphicon-pencil"></span><span class="caret"></span></a>
            <ul id="languageList" class="dropdown-menu" role="menu"></ul>
          </li>
          <li><a href="#about"><span class="glyphicon glyphicon-info-sign"></span></a></li>
        </ul>
        <form class="navbar-form navbar-right" role="search">
          <div class="form-group input-group">
            <span class="input-group-addon"><span class="glyphicon glyphicon-search"></span></span>
            <input type="text" placeholder="Search" class="form-control"/>
          </div>
        </form>
      </div><!--/.nav-collapse -->
    </div>
  </nav>
  <nav class="navbar navbar-default" role="navigation"></nav>
<!--  -->
<!--
<div class="panel panel-primary">
順序:
<div class="btn-group btn-group-sm">
  <button type="button" class="btn btn-default">国</button>
  <button type="button" class="btn btn-default">度数</button>
  <button type="button" class="btn btn-default">Right</button>
</div>
</div>
-->
  <div id="resultList" class="list-group" role="list">
<!--
    <a href="#" class="list-group-item">
      <span class="media-left"><img src="./img/64x64.png" class="img-thumbnail"/></span>
      <span class="media-body">
        <img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABcAAAAUCAIAAADp3DFZAAAABmJLR0QA/wD/AP+gvaeTAAAALUlEQVQ4jWNkwAaCvMRWTNPBFP/e9uvP4b+Y4kxYTSEVjJoyasqoKaOmjARTADyKB3dQow4IAAAAAElFTkSuQmCC" title="ベルギー"/>
        <strong class="media-heading">タラスブルバ</strong>
        <span class="badge">4.5</span>
        <span class="label label-primary">エール</span>
        <span class="label label-primary">ホップ</span>
        <br/>
        アルコール度数低めで、ホップの香りを最大限に活かしたゴールデンエール
      </span>
    </a>
    <a href="#" class="list-group-item">
      <span class="media-left"><img src="./img/64x64.png" class="img-thumbnail"/></span>
      <span class="media-body">
        <img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABcAAAAUCAIAAADp3DFZAAAABmJLR0QA/wD/AP+gvaeTAAAALUlEQVQ4jWNkwAaCvMRWTNPBFP/e9uvP4b+Y4kxYTSEVjJoyasqoKaOmjARTADyKB3dQow4IAAAAAElFTkSuQmCC">
        <strong class="media-heading">ジネビア</strong>
        <span class="badge">5.8</span>
        <span class="label label-primary">ホップ</span>
        <br/>
        St.デラセーヌ醸造所で造られる苦味が効いたベルジャンエール
      </span>
    </a>
    <a href="#" class="list-group-item">
      <span class="media-left"><img src="./img/64x64.png" class="img-thumbnail"/></span>
      <span class="media-body">
        <img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABcAAAAUCAIAAADp3DFZAAAABmJLR0QA/wD/AP+gvaeTAAAALUlEQVQ4jWNkwAaCvMRWTNPBFP/e9uvP4b+Y4kxYTSEVjJoyasqoKaOmjARTADyKB3dQow4IAAAAAElFTkSuQmCC">
        <strong class="media-heading">ドゥシャス・デ・ブルゴーニュ</strong>
        <span class="badge">6.2</span>
        <span class="label label-primary">エール</span>
        <br/>
        フランダースエールの傑作。酸味と上品な甘さが絶妙のハーモニーを奏でる
      </span>
    </a>
    <a href="#" class="list-group-item">
      <span class="media-left"><img src="./img/64x64.png" class="img-thumbnail"/></span>
      <span class="media-body">
        <img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABcAAAAUCAIAAADp3DFZAAAABmJLR0QA/wD/AP+gvaeTAAAALUlEQVQ4jWNkwAaCvMRWTNPBFP/e9uvP4b+Y4kxYTSEVjJoyasqoKaOmjARTADyKB3dQow4IAAAAAElFTkSuQmCC">
        <strong class="media-heading">トリプル・カルメリート</strong>
        <span class="badge">8.0</span>
        <span class="label label-primary">エール</span>
        <br/>
        柑橘系の爽やかな香りに、スパイシーとフルーティーのバランスが非常に良い優秀なビール
      </span>
    </a>
    <a href="#" class="list-group-item">
      <span class="media-left"><img src="./img/64x64.png" class="img-thumbnail"/></span>
      <span class="media-body">
      <img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABcAAAAUCAIAAADp3DFZAAAABmJLR0QA/wD/AP+gvaeTAAAALUlEQVQ4jWNkwAaCvMRWTNPBFP/e9uvP4b+Y4kxYTSEVjJoyasqoKaOmjARTADyKB3dQow4IAAAAAElFTkSuQmCC">
      <strong class="media-heading">カンティヨン グーズ</strong>
      <span class="badge">5.0</span>
      <span class="label label-primary">ランビック</span>
      <span class="label label-primary">グーズ</span>
      <br/>
      酸味が非常に強く"すっぱい"という表現がぴったり
      </span>
    </a>
    <a href="#" class="list-group-item">
      <span class="media-left"><img src="./img/64x64.png" class="img-thumbnail"/></span>
      <span class="media-body">
      <img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABcAAAAUCAIAAADp3DFZAAAABmJLR0QA/wD/AP+gvaeTAAAALUlEQVQ4jWNkwAaCvMRWTNPBFP/e9uvP4b+Y4kxYTSEVjJoyasqoKaOmjARTADyKB3dQow4IAAAAAElFTkSuQmCC">
      <strong class="media-heading">セゾン デュポン</strong>
      <span class="badge">6.5</span>
      <span class="label label-primary">エール</span>
      <br/>
      伝統的なセゾンスタイルを忠実に守っており、特徴をしっかりとあらわす
      </span>
    </a>
    <a href="#" class="list-group-item">
      <span class="media-left"><img src="./img/64x64.png" class="img-thumbnail"/></span>
      <span class="media-body">
      <img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABcAAAAUCAIAAADp3DFZAAAABmJLR0QA/wD/AP+gvaeTAAAALUlEQVQ4jWNkwAaCvMRWTNPBFP/e9uvP4b+Y4kxYTSEVjJoyasqoKaOmjARTADyKB3dQow4IAAAAAElFTkSuQmCC">
      <strong class="media-heading">ブラッセルズ レッドフルーツ</strong>
      <span class="badge">3.2</span>
      <span class="label label-primary">ランビック</span>
      <br/>
      3種類のレッドフルーツを使用した珍しいフルーツランビック
      </span>
    </a>
-->
  </div>
  <div id="dialog"></div>
</body>
</html>
