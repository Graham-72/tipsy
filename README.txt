// $Id$

  -----------------------------------------------------------------------------------------
																		ABOUT THE MODULE
	-----------------------------------------------------------------------------------------
	Tipsy module provides a Facebook-like balloon tooltip for any element you like on the
	page, it integrates tipsy jquery plugin (https://github.com/jaz303/tipsy) by Jason Frame.
	This module is integrated contributed to Drupal by Wikikiwis Team (http://wikikiwis.com).
	
	Currently, this module allows tooltips to appear with a textarea, a textfield, or any 
	other HTML attribute specified in tipsy settings page.
	
	It supplies hover, or focus states, and comes with a bunch of options the is also specified
	in the settings page, without the need to delive into jQuery at all.
	
	-----------------------------------------------------------------------------------------
																		HOW TO USE TIPSY
	-----------------------------------------------------------------------------------------
	First the modules must be enabled admin/build/modules page.
	Then go to admin/settings/tipsy to specify and customize tipsy settings, you will notice that
	you have the option to enable tipsy on all Drupal forms descriptions inside your site.
	You also have have to specify the position where tipsy must appear, the delay of the appear and
	disappear in milliseconds, how tipsy is triggered (hover/focus), the opacity of the balloon,
	and the offset (number of pixels between the balloon and the element).
	
	
	Custom Selectors
	----------------
	In this section you can specify any HTML element and its tipsy options
	The example below applies tipsy tooltips anchor title on primary navigation inside Drupal site
	
	1) Our CSS selector will be => "li.leaf a" (without quotes) which means any anchor inside the li
	   that has the class leaf.
	2) Specify the options the best suits.
	3) Tooltip content will be the "title" (without quotes) of the anchor that will appear inside 
	   the tipsy balloon. Note that leaving this field blank will automatically take the value of the title
	4) Hit save
	
	Note that you can add as many selectors as needed, to DELETE a selector you only have to REMOVE/EMPTY
	its selector textfield and SAVE.
	
	Tooltip content advanced feature
	--------------------------------
	In this field you can provide a jQuery function that returns any value you wish.
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	