/**
 * 
 */
$(document).ready(function() {
	var searchList = $('#searchList');

	setupLanguage();
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
		$.get('about.php').done(function(data) {
			var dlg = $('#dialog');
			dlg.html(data);
			dlg.dialog({
				title: 'About...',
				modal: true,
				buttons: {
					'OK': function() {
						$(this).dialog('close');
					}
				}
			});
		});
		return false;
	});
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
				return false;
			});
		});
	});
}
function getLang() {
	var li = $('#languageList li.active');
	return li.attr('title');

}
/**
 * 
 */
function setupCountry() {
		var dlg = $('#dialog');
		var html = '<div id="countryList" class="list-group"></div>';
		dlg.html(html);
		// Ajax
		var param = {act:'countryList', lang:getLang()};
		$.getJSON('app', param, function(data) {
			var countryList = $('#countryList');

			$(data.list).each(function(ix, rec) {
				var anc = $('<a href="#"></a>');
				var img = $('<img src="data:image/png;base64,' + rec.flag + '"/>');

				anc.addClass('list-group-item');
				anc.append(img);
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
		});
		// ダイアログを開く
		dlg.dialog({
			title: 'Select country.',
			modal: true,
			resizable: false,
			width: 400,
			height: 400,
			buttons: {
				'OK': function() {
					$(this).dialog('close');
				}
			}
		});
}
/**
 * 
 */
function setupShop() {
		var dlg = $('#dialog');
		var search = $('<div class="input-group"></div>');
		var searchIco = $('<span class="input-group-addon glyphicon glyphicon-search"></span>');
		var input = $('<input type="text" class="form-control" autoFocus/>');
		var shopList = $('<div id="shopList" class="list-group"></div>');

		search.append(searchIco);
		search.append(input);
		dlg.empty();
		dlg.append(search);
		dlg.append(shopList);
		// Ajax
		var param = {act:'shopList', lang:getLang()};
		$.getJSON('app', param, function(data) {
			$(data.list).each(function(ix, rec) {
				var anc = $('<a href="#"></a>');
//				var img = $('<img src="data:image/png;base64,' + rec.flag + '"/>');

				anc.addClass('list-group-item');
				anc.prop('orgId', rec.orgId);
//				anc.append(img);
				anc.append(rec.noun);
				anc.click(function() {
					alert(anc.prop('orgId'));
					dlg.dialog('close');
					return false;
				});
				shopList.append(anc);
			});
		});
		var width = 600;
		// ダイアログを開く
		dlg.dialog({
			title: 'Select a shop.',
			modal: true,
			resizable: false,
			width: width,
			height: 600,
			buttons: {
				'Reset': function() {
					$(this).dialog('close');
				}
			}
		});
}
