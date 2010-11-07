// $Id$
Drupal.behaviors.tipsy = function(context) {
	if (Drupal.settings.tipsy.drupal_forms) {
		var formElement = $('.form-item');
		formElement.each(function(){
			var desc = $(this).find('.description');
			if(desc.length > 0) {
				formSettings = Drupal.settings.tipsy.drupal_forms.options;
				$(this).find('input,textarea,select,.option,.form-checkboxes,.form-radios').tipsy({
					title: function() { return desc.html(); },
					html: true,
					delayIn: parseInt(formSettings.delayIn),
				    delayOut: parseInt(formSettings.delayOut),
				    fade: parseInt(formSettings.fade),
				    gravity: tipsy_determine_gravity(formSettings.gravity),
				    offset: parseInt(formSettings.offset),
				    opacity: parseFloat(formSettings.opacity),
				    trigger: formSettings.trigger
				});
			}
		});
	}
	if (Drupal.settings.tipsy.custom_selectors) {
		var selectors = Drupal.settings.tipsy.custom_selectors;
		$(selectors).each(function(){
			var selector = $(this)[0].selector;
			$(selector).tipsy({});
		});
	}
};

function tipsy_determine_gravity(g) {
	if (g == 'autoWE') { return $.fn.tipsy.autoWE; } 
	else if (g == 'autoNS') { return $.fn.tipsy.autoNS; } 
	else { return g; }
}