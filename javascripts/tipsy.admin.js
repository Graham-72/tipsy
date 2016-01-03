(function ($) {
    Backdrop.behaviors.tipsyAdmin = {
        attach: function (context, settings) {
            ($('input#edit-forms:checked').length > 0) ? $('#tipsy-backdrop-forms-wrapper').show() : $('#tipsy-backdrop-forms-wrapper').css('display', 'none');
            $('input#edit-forms').click(function () {
                ($(this).is(':checked')) ? $('#tipsy-backdrop-forms-wrapper').slideDown() : $('#tipsy-backdrop-forms-wrapper').slideUp();
            });
        }
    };
})(jQuery);
