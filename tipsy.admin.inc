<?php

/*
 * Implementation of tipsy form
 */
function tipsy_admin() {
  drupal_add_js(drupal_get_path('module', 'tipsy') . '/javascripts/tipsy.admin.js');
  $settings = _tipsy_get_settings();
  
  $form = array();
  $form['general'] = array(
    '#type' => 'fieldset',
    '#title' => t('General settings'),
    '#weight' => -5,
    '#collapsible' => TRUE,
    '#collapsed' => False,
  );
  $form['general']['form_descriptions'] = array(
    '#type' => 'checkbox',
    '#default_value' => $settings['drupal_forms']['form_descriptions'],
    '#title' => t('Apply tipsy for form items descriptions on all Drupal forms.'),
    '#description' => t('Apply tipsy for form items descriptions on all Drupal forms.'),
  );
  $form['general']['form_descriptions_fade'] = array(
    '#type' => 'checkbox',
    '#default_value' => $settings['drupal_forms']['form_descriptions_fade'],
    '#title' => t('Make tipsy fade.'),
    '#required' => TRUE,
    '#prefix' => '<div class="tipsy-form_descriptions_elements-wrapper">'
  );
  $form['general']['form_descriptions_gravity'] = array(
    '#type' => 'radios',
    '#default_value' => $settings['drupal_forms']['form_descriptions_gravity'],
    '#title' => t('tipsy gravity'),
    '#options' => array(
      'nw' => t('North west'), 'n' => t('North'), 'ne' => t('North east'),
      'w' => t('West'), 'e' => t('East'), 'sw' => t('South west'), 's' => t('South'),
      'se' => t('South east'), 'autoNS' => t('Auto detect North/South'), 'autoWE' => t('Auto detect West/East')
    ),
    '#required' => TRUE,
  );
  $form['general']['form_descriptions_delayin'] = array(
    '#type' => 'textfield',
    '#default_value' => $settings['drupal_forms']['form_descriptions_delayin'],
    '#title' => t('Amount of milliseconds when poping in'),
    '#size' => 5,
    '#maxlength' => 5,
    '#required' => TRUE,
  );
  $form['general']['form_descriptions_delayout'] = array(
    '#type' => 'textfield',
    '#default_value' => $settings['drupal_forms']['form_descriptions_delayout'],
    '#title' => t('Amount of milliseconds when poping out'),
    '#size' => 5,
    '#maxlength' => 5,
    '#required' => TRUE,
  );
  $form['general']['form_descriptions_trigger'] = array(
    '#type' => 'radios',
    '#default_value' => $settings['drupal_forms']['form_descriptions_trigger'],
    '#title' => t('tipsy trigger'),
    '#options' => array(
      'focus' => t('Focus'), 'hover' => t('Hover'), 'manual' => t('Manual'),
    ),
    '#required' => TRUE,
  );
  $form['general']['form_descriptions_opacity'] = array(
    '#type' => 'textfield',
    '#default_value' => $settings['drupal_forms']['form_descriptions_opacity'],
    '#title' => t('Opacity level for the tipsy tooltip'),
    '#size' => 5,
    '#maxlength' => 5,
    '#required' => TRUE,
  );
  $form['general']['form_descriptions_offset'] = array(
    '#type' => 'textfield',
    '#default_value' => $settings['drupal_forms']['form_descriptions_offset'],
    '#title' => t('Offset'),
    '#size' => 5,
    '#maxlength' => 5,
    '#required' => TRUE,
    '#suffix' => '</div>'
  );
  $form['buttons']['submit'] = array('#type' => 'submit', '#value' => t('Save configuration') );
  $form['#theme'] = 'system_settings_form';
  $form['#submit'][] = 'tipsy_admin_submit';
  return $form;
}