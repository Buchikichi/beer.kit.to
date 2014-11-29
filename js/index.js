/**
 * 
 */
$(document).ready(function() {
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
		var last = self.prop('last');
		var val = self.val();

		if (last != val) {
			self.prop('last', val);
			resetItemList();
		}
	});
	setupLanguage();
	setupItemList();
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
			li.attr('lang', rec.lang);
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
	return $('#languageList li.active').attr('lang');

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
	var last = '' + countryList.prop('last');

	countryList.empty();
	// Ajax
	var param = {act:'countryList', lang:getLang()};
	$.getJSON('app', param, function(data) {

		$(data.list).each(function(ix, rec) {
			var anc = $('<a href="#"></a>');
			var flag = $('<img src="data:image/png;base64,' + rec.flag + '" class="flag"/>');

			anc.prop('countryCd', rec.countryCd);
			anc.addClass('list-group-item');
			if (last.indexOf(rec.countryCd) != -1) {
				anc.addClass('active');
			}
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
					var country = [];
					$('#countryList a.active').each(function(ix, anc) {
						country.push($(anc).prop('countryCd'));
					});
					var current = country.join(' ');
					if (current != last) {
						countryList.prop('last', current);
						resetItemList();
					}
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
function setupItemList() {
	var resultList = $('#resultList');

	$(document).scroll(function() {
		var anc = resultList.find('a:last');
		if (anc.length == 0) {
			return;
		}
		if (resultList.prop('busy')) {
			return;
		}
		var ancHeight = anc.outerHeight();
		var winHeight = $(window).outerHeight();
		var top = $(document).scrollTop();
		var height = $(document).outerHeight() - winHeight - ancHeight;

		//$('input[name=keyword]').val(top + '|' + height);
		if (height < top) {
			nextItemList();
		}
	});
	resetItemList();
}
function resetItemList() {
	var resultList = $('#resultList');
	resultList.prop('offset', 0);
	resultList.prop('limit', 5);
	resultList.prop('busy', false);
	resultList.prop('done', false);
	resultList.empty();
	showItemList();
}
function nextItemList() {
	var resultList = $('#resultList');

	if (resultList.prop('done')) {
		return;
	}
	var offset = resultList.prop('offset');
	var limit = resultList.prop('limit');

	resultList.prop('offset', offset + limit);
	showItemList();
}
function showItemList() {
	var resultList = $('#resultList');
	var keyword = $('input[name=keyword]').val();
	var country = $('#countryList').prop('last');
	var param = {
		act:'itemList',
		lang:getLang(),
		keyword:keyword,
		country:country,
		offset:resultList.prop('offset'),
		limit:resultList.prop('limit'),
	};
	resultList.prop('busy', true);
	$.getJSON('app', param, function(data) {
		if (data.count == 0) {
			resultList.prop('busy', false);
			resultList.prop('done', true);
			return;
		}
		var template = $('#itemTemplate > a');
		$(data.list).each(function(ix, rec) {
			var anc = template.clone();
			var thumbnail = anc.find('.img-thumbnail');
			var bd = anc.find('.media-body');
			var flag = bd.find('img');
			var name = bd.find('.media-heading');
			var abv = bd.find('.badge');

			if (rec.thumbnail != null) {
				thumbnail.attr('src', 'data:image/jpeg;base64,' + rec.thumbnail);
			}
			flag.attr('src', 'data:image/png;base64,' + rec.flag);
			flag.attr('alt', rec.countryCd);
			name.text(rec.itemName);
			abv.text(rec.abv);
			$(rec.tags).each(function(ix, tagName) {
				var tag = $('<span class="label label-primary">' + tagName + '</span>');
				bd.append(' ');
				bd.append(tag);
			});
			bd.append($('<br/>'));
			bd.append(rec.note);
			anc.click(function() {
				showItemDetail(rec.itemId);
				return false;
			});
			resultList.append(anc);
		});
		resultList.prop('busy', false);
		var winHeight = $(window).outerHeight();
		var pos = resultList.offset();
		var height = resultList.outerHeight();
		if (pos.top + height < winHeight) {
			nextItemList();
		}
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
	var flag = $('#itemNote > img');
	var itemName = $('#itemNote > strong');
	var note = $('#itemNote .note');
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
		note.text(rec.note);
		// 追加項目
		var abv = $('<span class="badge">' + rec.abv + '</span><br/>');

		ext.append(abv);
		$(rec.tags).each(function(ix, tagName) {
			var tag = $('<span class="label label-primary">' + tagName + '</span>');
			ext.append(' ');
			ext.append(tag);
		});
		ext.append($('<br/>'));
		// ダイアログを開く
		showDialog(itemDetail, {
			title: rec.itemName,
			width: 700,
			height: 600,
			buttons: {}
		});
	});
}
