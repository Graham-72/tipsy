Drupal.behaviors.dakwak = function(context) {
	$(function() {
		$('a[rel=tipsy]').tipsy({fade: true, gravity: 'n'});
	});
	var tipsy_elements = Drupal.settings.tipsy.tipsy_js_settings.tipsy_elements;
	var elements = tipsy_elements.split("\n");

	$.each(elements, function(index, class)) {
		var element = $('.' + class);
		if(!$(element).hasClass('tipsy')) {
			$(element).addClass('tipsy');
		}
	});
};