<?php

/**
 * Implementation of tipsy admin form.
 */
function tipsy_admin($form, &$form_state)
{
  $settings = _tipsy_get_settings();
  $module_path = backdrop_get_path('module', 'tipsy');
  $form = array();

  $form['#attached']['js'][] = $module_path . '/javascripts/tipsy.admin.js';
  $form['#attached']['css'][] = $module_path . '/stylesheets/tipsy.admin.css';

  // Set General Settings for all site forms
  $form['backdrop_forms'] = array(
    '#type' => 'fieldset',
    '#title' => t('Backdrop forms general settings'),
    '#weight' => -5,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['backdrop_forms']['forms'] = array(
    '#type' => 'checkbox',
    '#default_value' => $settings['tipsy_backdrop_forms']['forms'],
    '#title' => t('Apply Tipsy for form items descriptions on all Backdrop forms.'),
    '#description' => t('This will automatically enable Tipsy tooltips to form elements descriptions.'),
  );
  $form['backdrop_forms']['wrapper'] = array(
    '#tree' => TRUE,
    '#weight' => 0,
    '#prefix' => '<div class="clear-block" id="tipsy-backdrop-forms-wrapper">',
    '#suffix' => '</div>',
  );
  $form['backdrop_forms']['wrapper']['options'] = tipsy_options_form($settings['tipsy_backdrop_forms'], TRUE);

  // Set Custom Selectors form
  $form['custom_selectors'] = array(
    '#type' => 'fieldset',
    '#title' => t('Custom selectors'),
    '#weight' => -4,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['custom_selectors']['rules'] = array(
    '#tree' => TRUE,
    '#prefix' => '<div id="tipsy-custom-selectors">',
    '#suffix' => '</div>',
    '#theme' => 'tipsy_custom_selectors_form',
  );
  $form['custom_selectors']['rules_submit'] = array(
    '#type' => 'button',
    '#value' => t('Add another rule'),
    // If no javascript action.
    '#submit' => array('tipsy_custom_selectors_add'),
    '#ajax' => array(
      'callback' => 'tipsy_admin_callback',
      'wrapper' => 'tipsy-custom-selectors',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  if ($settings['tipsy_custom_selectors']) {
    foreach ($settings['tipsy_custom_selectors'] as $delta => $options) {
      $form['custom_selectors']['rules'][$delta] = tipsy_custom_selector_form($options);
    }
  } else {
    $form['custom_selectors']['rules'][0] = tipsy_custom_selector_form();
  }

  // The "Add another rule" button was clicked.
  if (isset($form_state['values']['rules_submit'])) {
    $form['custom_selectors']['rules'][] = tipsy_custom_selector_form();
  }

  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  $form['#theme'] = 'system_settings_form';
  $form['#submit'][] = 'tipsy_admin_submit';
  return $form;
}

/**
 * AJAX callback to render the tipsy rules form.
 */
function tipsy_admin_callback($form, $form_state)
{
  return $form['custom_selectors']['rules'];
}

/**
 * Implementation of form function for the tooltip options.
 * If $backdrop_forms = TRUE, we apply Tipsy on all forms
 * If $backdrop_forms = FALSE, we are dealing with custom settings.

 */
function tipsy_options_form($settings = FALSE, $backdrop_forms = FALSE)
{
  if ($backdrop_forms) {
    $settings = _tipsy_get_settings();
    $settings = $settings['tipsy_backdrop_forms'];
  }

  $form = array();
  $form['fade'] = array(
    '#type' => 'checkbox',
    '#default_value' => $settings['options']['fade'],
    '#description' => t('This will make the tooltip fade.'),
    '#title' => t('Make Tipsy tooltips fade.'),
    '#weight' => 0,
    '#prefix' => '<div class="tipsy-selector-options clear-block">',
  );
  $form['gravity'] = array(
    '#type' => 'select',
    '#default_value' => $settings['options']['gravity'],
    '#title' => t('Tipsy arrow position'),
    '#description' => t('Specify the position of the tooltip when it appears.'),
    '#weight' => 2,
    '#options' => array(
      'nw' => t('North west'),
      'n' => t('North'),
      'ne' => t('North east'),
      'w' => t('West'),
      'e' => t('East'),
      'sw' => t('South west'),
      's' => t('South'),
      'se' => t('South east'),
      'autoNS' => t('Auto detect North/South'),
      'autoWE' => t('Auto detect West/East'),
    ),
  );
  $form['delayIn'] = array(
    '#type' => 'textfield',
    '#default_value' => $settings['options']['delayIn'],
    '#title' => t('Delay when appearing'),
    '#description' => t('Amount of milliseconds for the tooltip to appear.'),
    '#size' => 5,
    '#maxlength' => 5,
    '#weight' => 3,
  );
  $form['delayOut'] = array(
    '#type' => 'textfield',
    '#default_value' => $settings['options']['delayOut'],
    '#title' => t('Delay when disappearing'),
    '#description' => t('Amount of milliseconds for the tooltip to disappear.'),
    '#size' => 5,
    '#maxlength' => 5,
    '#weight' => 4,
  );
  $form['trigger'] = array(
    '#type' => 'select',
    '#default_value' => $settings['options']['trigger'],
    '#description' => t('Specify what action will make the tooltip appear.'),
    '#title' => t('Tipsy trigger'),
    '#weight' => 5,
    '#options' => array(
      'focus' => t('Focus'),
      'hover' => t('Hover'),
    ),
  );
  $form['opacity'] = array(
    '#type' => 'textfield',
    '#default_value' => $settings['options']['opacity'],
    '#title' => t('Tooltip opacity'),
    '#description' => t('A value between 0 and 1.'),
    '#size' => 5,
    '#maxlength' => 4,
    '#weight' => 6,
  );
  $form['offset'] = array(
    '#type' => 'textfield',
    '#default_value' => $settings['options']['offset'],
    '#title' => t('Tooltip offset'),
    '#description' => t('Number of pixels in which the tooltip will distance from the element.'),
    '#size' => 5,
    '#maxlength' => 5,
    '#weight' => 7,
  );
  if ($backdrop_forms == TRUE) {
    $form['html'] = array(
      '#type' => 'checkbox',
      '#default_value' => $settings['options']['html'],
      '#description' => t('This will let HTML code be parsed inside the tooltip.'),
      '#title' => t('Allow HTML in tooltip content.'),
      '#weight' => 1,
    );
    $form['tooltip_content'] = array(
      '#type' => 'fieldset',
      '#title' => t('Tooltip content'),
      '#weight' => 9,
    );
    $form['tooltip_content']['source'] = array(
      '#type' => 'radios',
      '#title' => t('Source'),
      '#default_value' => $settings['options']['tooltip_content']['source'],
      '#options' => array(
        'attribute' => t('HTML attribute'),
        'child' => t('Child element'),
        'sibling' => t('Sibling element'),
      ),
    );
    $form['tooltip_content']['selector'] = array(
      '#type' => 'textarea',
      '#title' => t('Selector'),
      '#default_value' => $settings['options']['tooltip_content']['selector'],
      '#description' => t("The name of the HTML attribute, or a selector pointing to the child or sibling element (e.g: .content). <br /> Refer to the module's README.txt for more information."),
      '#rows' => 1,
      '#maxlength' => 400,
    );
  }
  $form['closure'] = array(
    '#weight' => 10,
    '#suffix' => '</div>',
  );
  return $form;
}

/**
 * Implementation of a single tipsy rule form.
 */
function tipsy_custom_selector_form($options = FALSE)
{
  $form = array();
  $form['#tree'] = TRUE;
  $form['selector'] = array(
    '#type' => 'textarea',
    '#weight' => 1,
    '#rows' => 2,
    '#default_value' => $options['options']['name'],
  );
  $form['options'] = tipsy_options_form($options);
  return $form;
}

/**
 * Theme the table form for tipsy rules.
 */
function theme_tipsy_custom_selectors_form($variables)
{
  $form = $variables['form'];
  $rows = array();
  $headers = array(t('Selectors'), t('Options'));
  foreach (element_children($form) as $key) {
    $row = array(
      'data' => array(
        array('data' => backdrop_render($form[$key]['selector'])),
        array('data' => backdrop_render($form[$key]['options'])),
      ),
    );
    $rows[] = $row;
  }
  $output = theme('table', array('header' => $headers, 'rows' => $rows));
  $output .= backdrop_render_children($form);
  return $output;
}

/**
 * Implements hook_validate().
 *
 * Validation is for admin form.
 */
function tipsy_admin_validate($form, &$form_values)
{
  $backdrop_forms = $form_values['values']['wrapper'];
  if ($form_values['values']['forms'] != 0) {
    if (!is_numeric($backdrop_forms['options']['delayIn']) || $backdrop_forms['options']['delayIn'] == '') {
      form_set_error('wrapper][options][delayIn', t('Invalid value'));
    }
    if (!is_numeric($backdrop_forms['options']['delayOut']) || $backdrop_forms['options']['delayOut'] == '') {
      form_set_error('wrapper][options][delayOut', t('Invalid value'));
    }
    if (!is_numeric($backdrop_forms['options']['opacity']) || $backdrop_forms['options']['opacity'] == '') {
      form_set_error('wrapper][options][opacity', t('Invalid value'));
    }
    if (!is_numeric($backdrop_forms['options']['offset']) || $backdrop_forms['options']['offset'] == '') {
      form_set_error('wrapper][options][offset', t('Invalid value'));
    }
  }

  foreach ($form_values['values']['rules'] as $delta => $rule) {
    if (trim($rule['selector']) != '') {
      if (!is_numeric($rule['options']['delayIn']) || $rule['options']['delayIn'] == '') {
        form_set_error('rules][' . $delta . '][options][delayIn', t('Invalid value'));
      }
      if (!is_numeric($rule['options']['delayOut']) || $rule['options']['delayOut'] == '') {
        form_set_error('rules][' . $delta . '][options][delayOut', t('Invalid value'));
      }
      if (!is_numeric($rule['options']['opacity']) || $rule['options']['opacity'] == '') {
        form_set_error('rules][' . $delta . '][options][opacity', t('Invalid value'));
      }
      if (!is_numeric($rule['options']['offset']) || $rule['options']['offset'] == '') {
        form_set_error('rules][' . $delta . '][options][offset', t('Invalid value'));
      }
    }
  }
}

/**
 * Implementation of form submit function for the admin form.
 */
function tipsy_admin_submit($form, &$form_values)
{
  $settings = array();
  $backdrop_forms = $form_values['values']['wrapper'];
  $settings['forms'] = $form_values['values']['forms'];
  $settings['options'] = array(
    'fade' => $backdrop_forms['options']['fade'],
    'gravity' => $backdrop_forms['options']['gravity'],
    'delayIn' => trim($backdrop_forms['options']['delayIn']),
    'delayOut' => trim($backdrop_forms['options']['delayOut']),
    'trigger' => $backdrop_forms['options']['trigger'],
    'opacity' => trim($backdrop_forms['options']['opacity']),
    'offset' => trim($backdrop_forms['options']['offset']),
  );
  config_set('tipsy.settings', 'tipsy_backdrop_forms', $settings);

  $settings = array();

  foreach ($form_values['values']['rules'] as $delta => $rule) {
    if (trim($rule['selector']) != '') {
      $selectorname = 'option_' . trim($rule['selector']);
      $settings[$selectorname] = array(
        'options' => array(
          'name' => trim($rule['selector']),
          'fade' => $rule['options']['fade'],
          'gravity' => $rule['options']['gravity'],
          'trigger' => $rule['options']['trigger'],
          'delayIn' => trim($rule['options']['delayIn']),
          'delayOut' => trim($rule['options']['delayOut']),
          'opacity' => trim($rule['options']['opacity']),
          'offset' => trim($rule['options']['offset']),
          'html' => $rule['options']['html'],
          'tooltip_content' => array(
            'source' => $rule['options']['tooltip_content']['source'],
            'selector' => trim($rule['options']['tooltip_content']['selector']),
          ),
        ),
      );
    }
  }
  config_set('tipsy.settings', 'tipsy_custom_selectors', $settings);
  backdrop_set_message(t('Configuration saved'));
}
