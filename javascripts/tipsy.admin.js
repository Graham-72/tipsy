Drupal.behaviors.tipsyAdmin = function(context) {
	$('input#edit-form-descriptions:checked').click(function() {
		if($(this).is(':checked')) {
			$('.tipsy-form_descriptions_elements-wrapper').slideDown();
		}
		else {
			$('.tipsy-form_descriptions_elements-wrapper').slideUp();
		}
	});
};