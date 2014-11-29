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

<body>
  <nav id="topNav" class="navbar navbar-default navbar-fixed-top" role="navigation">
    <div class="container-fluid">
      <div class="navbar-header">
        <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#topNavbar">
        <span class="sr-only">Toggle navigation</span>
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
        </button>
        <span class="navbar-brand">drink.kit.to</span>
      </div>
      <div id="topNavbar" class="navbar-collapse collapse">
        <ul class="nav navbar-nav">
          <li><a href="#country"><span class="glyphicon glyphicon-globe"></span></a></li>
          <li><a href="#shop"><span class="glyphicon glyphicon-book"></span></a></li>
          <li><a href="#kind"><span class="glyphicon glyphicon-glass"></span></a></li>
          <li><a href="#tags"><span class="glyphicon glyphicon-tags"></span></a></li>
          <li class="dropdown">
            <a aria-expanded="false" href="#" class="dropdown-toggle" data-toggle="dropdown"><span class="glyphicon glyphicon-pencil"></span><span class="caret"></span></a>
            <ul id="languageList" class="dropdown-menu" role="menu"></ul>
          </li>
          <li><a href="#about"><span class="glyphicon glyphicon-info-sign"></span></a></li>
        </ul>
        <div class="navbar-form navbar-right" role="search">
          <div class="form-group input-group">
            <span class="input-group-addon"><span class="glyphicon glyphicon-search"></span></span>
            <input type="text" name="keyword" placeholder="Search" class="form-control" autofocus="autofocus"/>
          </div>
        </div>
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
  <div id="resultList" class="list-group" role="list"></div>
  <div id="itemTemplate" class="list-group" role="list">
    <a href="#" class="list-group-item">
      <span class="media-left"><img src="./img/64x64.png" class="img-thumbnail"/></span>
      <span class="media-body">
        <img src="" class="flag"/>
        <strong class="media-heading"></strong><br/>
        <span class="badge"></span>
      </span>
    </a>
  </div>
  <div id="dialog" class="container">
    <div id="countryList" class="list-group"></div>
    <div id="shopSelection">
      <div class="input-group">
        <span class="input-group-addon glyphicon glyphicon-search"></span>
        <input type="text" class="form-control" autoFocus/>
      </div>
      <div class="list-group shopList"></div>
    </div>
    <div id="itemDetail">
      <div class="panel panel-info">
        <div class="panel-body">
          <span class="media-left"><img id="itemImg" src="" width="256" height="256"/></span>
          <span id="itemNote" class="media-body">
            <img src="" class="flag"/>
            <strong class="media-heading">itemName</strong><br/>
            <span class="note" translate="yes"></span><br/>
            <span class="ext">
            </span>
          </span>
        </div>
      </div>
      <div class="panel panel-success" style="height: 200px; max-height: 200px;">
        <div class="panel-heading">コメント</div>
        <div class="list-group-item">コメントはまだありません.</div>
      </div>
    </div>
    <div id="about"></div>
  </div>
</body>
</html>
