// $Id$
Drupal.behaviors.tipsyAdmin = function(context) {
	($('input#edit-forms:checked').length > 0) ? $('#tipsy-drupal-forms-wrapper').show() : $('#tipsy-drupal-forms-wrapper').hide();
	$('input#edit-forms').click(function() {
		if($(this).is(':checked')) {
			$('#tipsy-drupal-forms-wrapper').slideDown();
		}
		else {
			$('#tipsy-drupal-forms-wrapper').slideUp();
		}
	});
};