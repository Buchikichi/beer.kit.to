/**
 * 
 */
$(document).ready(function() {
	var searchList = $('#searchList');

	setupLanguage();
	$('form').submit(function() {return false;});
	$('a[href=#country]').click(function() {
		setupCountry();
		return false;
	});
	$('a[href=#shop]').click(function() {
		setupShop();
		return false;
	});
	$('a[href=#kind]').click(function() {
		return false;
	});
	$('a[href=#tags]').click(function() {
		return false;
	});
	$('a[href=#about]').click(function() {
		showAbout();
		return false;
	});
	$('input[name=keyword]').keyup(function() {
		var self = $(this);
		var lastLen = self.prop('len');
		var len = self.val().length;

		if (lastLen != len) {
			self.prop('len', len);
			resetItemList();
		}
	});
	showItemList();
});
function setupLanguage() {
	var param = {act:'languageList'};
	$.getJSON('app', param, function(data) {
		var languageList = $('#languageList');

		$(data.list).each(function(ix, rec) {
			var li = $('<li></li>');
			var anc = $('<a href="#"></a>');

			anc.append(rec.name);
			if (rec.checked) {
				li.addClass('active');
			}
			li.attr('title', rec.lang);
			li.append(anc);
			languageList.append(li);
			anc.click(function() {
				languageList.dropdown('toggle');
				if (li.hasClass('active')) {
					return false;
				}
				languageList.children('li').each(function() {
					$(this).removeClass('active');
				});
				li.addClass('active');
				resetItemList();
				return false;
			});
		});
	});
}
function getLang() {
	var li = $('#languageList li.active');
	return li.attr('title');

}

function showDialog(target, option) {
	var dlg = $('#dialog');

	$('#dialog > div').hide();
	target.show();
	option.modal = true;
	option.resizable = false;
	dlg.dialog(option);
}

/**
 * 
 */
function setupCountry() {
	var countryList = $('#countryList');

	countryList.empty();
	// Ajax
	var param = {act:'countryList', lang:getLang()};
	$.getJSON('app', param, function(data) {

		$(data.list).each(function(ix, rec) {
			var anc = $('<a href="#"></a>');
			var flag = $('<img src="data:image/png;base64,' + rec.flag + '" class="flag"/>');

			anc.addClass('list-group-item');
			anc.append(flag);
			anc.append(rec.noun);
			anc.click(function() {
				if (anc.hasClass('active')) {
					anc.removeClass('active');
				} else {
					anc.addClass('active');
				}
				return false;
			});
			countryList.append(anc);
		});
		// ダイアログを開く
		showDialog(countryList, {
			title: 'Select country.',
			width: 400,
			height: 400,
			buttons: {
				'OK': function() {
					$(this).dialog('close');
				}
			}
		});
	});
}

/**
 * Select a shop.
 */
function setupShop() {
	var dlg = $('#dialog');
	var shopSelection = $('#shopSelection');
	var shopList = $('#shopSelection div.shopList');

	shopList.empty();
	// Ajax
	var param = {act:'shopList', lang:getLang()};
	$.getJSON('app', param, function(data) {
		$(data.list).each(function(ix, rec) {
			var anc = $('<a href="#"></a>');
//			var img = $('<img src="data:image/png;base64,' + rec.flag + '"/>');

			anc.addClass('list-group-item');
			anc.prop('orgId', rec.orgId);
//			anc.append(img);
			anc.append(rec.noun);
			anc.click(function() {
//				alert(anc.prop('orgId'));
				dlg.dialog('close');
				return false;
			});
			shopList.append(anc);
		});
		// ダイアログを開く
		showDialog(shopSelection, {
			title: 'Select a shop.',
			width: 600,
			height: 600,
			buttons: {
				'Reset': function() {
					$(this).dialog('close');
				}
			}
		});
	});
}

function showAbout() {
	var dlg = $('#dialog');
	var about = $('#about');

	$.get('about.php').done(function(data) {
		about.html(data);
		showDialog(about, {
			title: 'About...',
			width: 300,
			height: 200,
			buttons: {}
		});
	});
}

/**
 * Item list.
 */
function resetItemList() {
	var resultList = $('#resultList');
	resultList.empty();
	showItemList();
}
function showItemList() {
	var resultList = $('#resultList');
	var keyword = $('input[name=keyword]').val();
	var param = {act:'itemList', lang:getLang(), keyword:keyword};
	$.getJSON('app', param, function(data) {
		$(data.list).each(function(ix, rec) {
//<a href="#" class="list-group-item">
//  <span class="media-left"><img src="./img/64x64.png" class="img-thumbnail"/></span>
//  <span class="media-body">
//    <img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABcAAAAUCAIAAADp3DFZAAAABmJLR0QA/wD/AP+gvaeTAAAALUlEQVQ4jWNkwAaCvMRWTNPBFP/e9uvP4b+Y4kxYTSEVjJoyasqoKaOmjARTADyKB3dQow4IAAAAAElFTkSuQmCC" title="ベルギー"/>
//    <strong class="media-heading">タラスブルバ</strong>
//    <span class="badge">4.5</span>
//    <span class="label label-primary">エール</span>
//    <span class="label label-primary">ホップ</span>
//    <br/>
//    アルコール度数低めで、ホップの香りを最大限に活かしたゴールデンエール
//  </span>
//</a>
			var anc = $('<a href="#" class="list-group-item"></a>');
			if (rec.thumbnail == null) {
				var thumbnail = $('<span class="media-left"><img src="./img/64x64.png" class="img-thumbnail"/></span>');
			} else {
				var thumbnail = $('<span class="media-left"><img src="data:image/jpeg;base64,' + rec.thumbnail + '" class="img-thumbnail"/></span>');
			}
			var bd = $('<span class="media-body"></span>');
			var flag = $('<img src="data:image/png;base64,' + rec.flag + '" alt="[' + rec.countryCd + ']" class="flag"/>');
			var name = $('<strong class="media-heading">' + rec.itemName + '</strong>');
			var abv = $('<span class="badge">' + rec.abv + '</span>');

			bd.append(flag);
			bd.append(name);
			bd.append(abv);
			$(rec.tags).each(function(ix, tagName) {
				var tag = $('<span class="label label-primary">' + tagName + '</span>');
				bd.append(' ');
				bd.append(tag);
			});
			bd.append($('<br/>'));
			bd.append('');
			anc.append(thumbnail);
			anc.append(bd);
			anc.click(function() {
				showItemDetail(rec.itemId);
				return false;
			});
			resultList.append(anc);
		});
	});
}

/**
 * Item detail.
 * @param itemId
 */
function showItemDetail(itemId) {
	var dlg = $('#dialog');
	var itemDetail = $('#itemDetail');
	var itemImg = $('#itemImg');
	var itemNote = $('#itemNote');
	var flag = $('#itemNote > img');
	var itemName = $('#itemNote > strong');
	var ext = $('#itemNote .ext');

	ext.empty();
	//<span class="badge">4.5</span><br/>
	//<span class="label label-primary">エール</span>
	//<span class="label label-primary">ホップ</span>
	// Ajax
	var param = {act:'itemDetail', lang:getLang(), itemId:itemId};
	$.getJSON('app', param, function(data) {
		var rec = data.item;

		itemImg.attr('src', 'data:image/jpeg;base64,' + rec.imgsrc);
		flag.attr('src', 'data:image/png;base64,' + rec.flag);
		flag.attr('alt', '[' + rec.countryCd + ']');
		itemName.text(rec.itemName);
		// 追加項目
		var abv = $('<span class="badge">' + rec.abv + '</span><br/>');

		ext.append(abv);
		$(rec.tags).each(function(ix, tagName) {
			var tag = $('<span class="label label-primary">' + tagName + '</span>');
			ext.append(' ');
			ext.append(tag);
		});
		ext.append($('<br/>a'));
		// ダイアログを開く
		showDialog(itemDetail, {
			title: rec.itemName,
			width: 700,
			height: 600,
			buttons: {}
		});
	});
}
