Drupal.behaviors.tipsyAdmin = function(context) {
	($('input#edit-forms:checked').length > 0) ? $('#tipsy-drupal-forms-wrapper').show() : $('#tipsy-drupal-forms-wrapper').css('display', 'none');
	$('input#edit-forms').click(function() {
		($(this).is(':checked')) ? $('#tipsy-drupal-forms-wrapper').slideDown() : $('#tipsy-drupal-forms-wrapper').slideUp();
	});
};