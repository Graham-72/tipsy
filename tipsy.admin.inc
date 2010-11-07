<?php // $Id$

/*
 * Implementation of tipsy admin form
 */
function tipsy_admin() {
  drupal_add_js(drupal_get_path('module', 'tipsy') . '/javascripts/tipsy.admin.js');
  drupal_add_css(drupal_get_path('module', 'tipsy') . '/stylesheets/tipsy.admin.css');
  $settings = _tipsy_get_settings();
  
  $form = array();
  $form['drupal_forms'] = array(
    '#type' => 'fieldset',
    '#title' => t('Drupal forms general settings'),
    '#weight' => -5,
    '#collapsible' => TRUE,
    '#collapsed' => False,
  );
  $form['drupal_forms']['forms'] = array(
    '#type' => 'checkbox',
    '#default_value' => $settings['drupal_forms']['forms'],
    '#title' => t('Apply tipsy for form items descriptions on all Drupal forms.'),
    '#description' => t('Apply tipsy for form items descriptions on all Drupal forms.'),
  );
  $form['drupal_forms']['wrapper'] = array(
      '#tree' => FALSE,
      '#weight' => 0,
      '#prefix' => '<div class="clear-block" id="tipsy-drupal-forms-wrapper">',
      '#suffix' => '</div>',
  );
  $form['drupal_forms']['wrapper']['fade'] = array(
    '#type' => 'checkbox',
    '#default_value' => $settings['drupal_forms']['options']['fade'],
    '#title' => t('Make tipsy fade.'),
    '#required' => TRUE,
  );
  $form['drupal_forms']['wrapper']['gravity'] = array(
    '#type' => 'radios',
    '#default_value' => $settings['drupal_forms']['options']['gravity'],
    '#title' => t('tipsy gravity'),
    '#options' => array(
      'nw' => t('North west'), 'n' => t('North'), 'ne' => t('North east'),
      'w' => t('West'), 'e' => t('East'), 'sw' => t('South west'), 's' => t('South'),
      'se' => t('South east'), 'autoNS' => t('Auto detect North/South'), 'autoWE' => t('Auto detect West/East')
    ),
    '#required' => TRUE,
  );
  $form['drupal_forms']['wrapper']['delayIn'] = array(
    '#type' => 'textfield',
    '#default_value' => $settings['drupal_forms']['options']['delayIn'],
    '#title' => t('Amount of milliseconds when poping in'),
    '#size' => 5,
    '#maxlength' => 5,
    '#required' => TRUE,
  );
  $form['drupal_forms']['wrapper']['delayOut'] = array(
    '#type' => 'textfield',
    '#default_value' => $settings['drupal_forms']['options']['delayOut'],
    '#title' => t('Amount of milliseconds when poping out'),
    '#size' => 5,
    '#maxlength' => 5,
    '#required' => TRUE,
  );
  $form['drupal_forms']['wrapper']['trigger'] = array(
    '#type' => 'radios',
    '#default_value' => $settings['drupal_forms']['options']['trigger'],
    '#title' => t('tipsy trigger'),
    '#options' => array(
      'focus' => t('Focus'), 'hover' => t('Hover'), 'manual' => t('Manual'),
    ),
    '#required' => TRUE,
  );
  $form['drupal_forms']['wrapper']['opacity'] = array(
    '#type' => 'textfield',
    '#default_value' => $settings['drupal_forms']['options']['opacity'],
    '#title' => t('Opacity level for the tipsy tooltip'),
    '#size' => 5,
    '#maxlength' => 5,
    '#required' => TRUE,
  );
  $form['drupal_forms']['wrapper']['offset'] = array(
    '#type' => 'textfield',
    '#default_value' => $settings['drupal_forms']['options']['offset'],
    '#title' => t('Offset'),
    '#size' => 5,
    '#maxlength' => 5,
    '#required' => TRUE,
  );
  
  $form['custom_selectors'] = array(
    '#type' => 'fieldset',
    '#title' => t('Custom selectors'),
    '#weight' => -4,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['custom_selectors']['rules'] = array(
    '#tree' => TRUE,
    '#prefix' => '<div id="tipsy-custom-selectors">',
    '#suffix' => '</div>',
    '#theme' => 'tipsy_custom_selectors_form',
  );
  $form['custom_selectors']['rules_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add another rule'),
    '#submit' => array('tipsy_custom_selectors_add'), // If no javascript action.
    '#ahah' => array(
      'path' => 'tipsy/ahah',
      'wrapper' => 'tipsy-custom-selectors',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  
  if ($settings['custom_selectors']) {
	  foreach ($settings['custom_selectors'] as $delta => $options) {
	    $form['custom_selectors']['rules'][$delta] = tipsy_custom_selector_form($options);
	  }
  } else {
  	$form['custom_selectors']['rules'][0] = tipsy_custom_selector_form();
  }
  
  $form['buttons']['submit'] = array('#type' => 'submit', '#value' => t('Save configuration') );
  $form['#theme'] = 'system_settings_form';
  $form['#submit'][] = 'tipsy_admin_submit';
  return $form;
}

/*
 * Implementation of a single tipsy rule form
 */
function tipsy_custom_selector_form($options = null) {
  $form = array();
  $form['#tree'] = TRUE;
  $form['selector'] = array(
    '#type' => 'textarea',
    '#weight' => 1,
    '#rows' => 2,
    '#default_value' => $options['selector'],
  );
  $form['options'] = array(
    '#type' => 'textarea',
    '#weight' => 2,
    '#rows' => 7,
    '#default_value' => $options['options'] ? str_replace('&amp;', ",\n", urldecode(http_build_query($options['options']))) : '',
  );
  return $form;
}

/*
 * Theme the table form for tipsy rules
 */
function theme_tipsy_custom_selectors_form($form) {
  $rows = array();
  $headers = array(t('Selectors'), t('Options'));
  foreach (element_children($form) as $key) {
    $row = array(
      'data' => array(
        array('data' => drupal_render($form[$key]['selector'])),
        array('data' => drupal_render($form[$key]['options'])),
      ),
    ); $rows[] = $row;
  }
  $output = theme('table', $headers, $rows);
  $output .= drupal_render($form);
  return $output;
}

/*
 * Implementation of form submit function for the admin form
 */
function tipsy_admin_submit($form, &$form_values) {
  $settings = array();
  $settings['drupal_forms'] = array(
    'forms' => $form_values['values']['forms'],
    'options' => array(
      'fade' => $form_values['values']['fade'],
      'gravity' => $form_values['values']['gravity'],
      'delayIn' => $form_values['values']['delayIn'],
      'delayOut' => $form_values['values']['delayOut'],
      'trigger' => $form_values['values']['trigger'],
      'opacity' => $form_values['values']['opacity'],
      'offset' => $form_values['values']['offset']
    )
  );
  foreach($form_values['values']['rules'] as $delta => $rule) {
  	if (trim($rule['selector']) != '') {
	    $settings['custom_selectors'][] = array(
	      'selector' => $rule['selector'],
	      'options' => _tipsy_build_options($form_values['values']['rules'][$delta]['options'])
	    );
  	}
  }
  variable_set('tipsy', $settings);
  drupal_set_message(t('Configuration Saved'));
}

/*
 * This function will work if JavaScript is disabled to add the new tipsy rule form
 */
function tipsy_custom_selectors_add() {
  
}

/*
 * AHAH callback to render the tipsy rules form
 */
function _tipsy_custom_selectors_ahah() {
	$delta = count($_POST['rules']);
  $details = array('delta' => $delta);
  $form_element = tipsy_custom_selector_form();
  drupal_alter('form', $form_element, array(), '_tipsy_custom_selectors_ahah');
  
  // Build the new form.
  $form_state = array('submitted' => FALSE);
  $form_build_id = $_POST['form_build_id'];
  $form = form_get_cache($form_build_id, $form_state);
  $form['custom_selectors']['rules'][$delta] = $form_element;
  form_set_cache($form_build_id, $form, $form_state);
  $form += array('#post' => $_POST, '#programmed' => FALSE,);
  $form = form_builder('tipsy_admin', $form, $form_state);
  
  // Render the new output.
  $rules_form = $form['custom_selectors']['rules'];
  $output = theme('status_messages') . drupal_render($rules_form);
  drupal_json(array('status' => TRUE, 'data' => $output));
}

function _tipsy_build_options($options) {
	$options = str_replace(array("\r", "\r\n", "\n"), '', str_replace(',', '&', $options));
	parse_str($options, $settings);
	foreach($settings as $key => $value) {
		$settings[$key] = trim($value);
	}
	return $settings;
}