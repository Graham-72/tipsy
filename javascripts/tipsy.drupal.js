Drupal.behaviors.tipsy = function(context) {
	$('.form-item > .description').prevAll('input,textarea,select,.option,.form-checkboxes,.form-radios').tipsy({
		title: function() { return $(this).next('.description').html(); },
		html: true
	});
};