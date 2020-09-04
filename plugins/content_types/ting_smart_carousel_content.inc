<?php

/**
 * @file
 * Panels pane to display the smart search form
 */
$plugin = array(
  'title' => t('Ting smart carousel content'),
  'description' => t("Display carousel"),
  'admin info' => 'ting_smart_carousel_ting_smart_carousel_content_admin_info',
  'single' => FALSE,
  'content_types' => array('inspiration_carousel'),
  'render callback' => 'ting_smart_carousel_content_type_render',
  'access callback' => 'ting_smart_carousel_ting_smart_carousel_content_content_type_access',
  'category' => t('Ting'),
  'render last' => TRUE,
  'required context' => array(
    new ctools_context_optional(t('Inspirations karrusel'), 'node'),
  )
);

function ting_smart_carousel_ting_smart_carousel_content_content_type_access() {
  $return = FALSE;
  global $user;
  if ($user->uid == '1') {
    $return = TRUE;
  }
  return $return;
}

/**
 * Return a summary for the administration information in panels.
 */
function ting_smart_carousel_ting_smart_carousel_content_admin_info($subtype, $conf, $context) {
  return ting_smart_carousel_get_default_admin_info($subtype, $conf, $context);
}

/**
 * Render the smart carousel block.
 */
function ting_smart_carousel_content_type_render($subtype, $conf, $panel_args, $context) {
  $carousels = array();
  $path = drupal_get_path('module', 'ting_smart_carousel');
  drupal_add_css($path . '/css/smart_carousel_content.css');
  $index = '';
  //$carousel_path = $context->data;

  $block = new stdClass();
  $delta_id = (int) $conf['deltaid'];

  // load the field_collection and pick the delta value from $conf
  if (isset($context[0]->data->field_ting_carousel['und'][$delta_id])) {
    $item_id = $context[0]->data->field_ting_carousel['und'][$delta_id]['value'];
  }
  $page = 1;
  $parameters = drupal_get_query_parameters();
  if (isset($parameters['page'])) {
    $page = $parameters['page'];
  }
file_put_contents("/var/www/drupal7vm/drupal/debug/nav1.txt", print_r($page, TRUE), FILE_APPEND);
  if (!empty($item_id) && $page <= 1) {
    $carousel_entity = entity_load('field_collection_item', array($item_id));
    $ctitle = $carousel_entity[$item_id]->field_ting_carousel_title['und'][0]['value'];
    $cquery = $carousel_entity[$item_id]->field_ting_carousel_search['und'][0]['value'];

    $cqlDoctor = new TingSearchCqlDoctor($cquery);
    $query = $cqlDoctor->string_to_cql();
    $cid = md5('new' . $query);
    $start = 0;
    $count = 18;
    $path = request_path();
    if (false && $cache = cache_get($cid, 'cache_ting_smart_carousel')) {
      $items = $cache->data;
      $offset = -1;
      $log_entry = date("d-m-Y H:i") . ',Cache HIT,' . $path . ',' . $query . "\r\n";
      //file_put_contents('/var/www/work/log/inspirationlog.txt', $log_entry, FILE_APPEND);
    } else {
      $items = array();
      $offset = 0;
      $log_entry = date("d-m-Y H:i") . ',Cache MISS,' . $path . ',' . $query . "\r\n";
      //file_put_contents('/var/www/work/log/inspirationlog.txt', $log_entry, FILE_APPEND);
    }


    $carousels[] = array(
      '#type' => 'ding_carousel',
      '#title' => $ctitle,
      '#path' => 'ting_smart_carousel/results/ajax/' . urlencode($query),
      '#items' => $items,
      '#offset' => $offset,
      // Add a single placeholder to fetch more content later if there is more
      // content.
      '#placeholders' => 1,
    );
  }
  if (!empty($cquery)) {
    $block->title = $ctitle;
    $block->content = array(
      '#type' => 'ding_tabbed_carousel',
      '#title' => $ctitle,
      '#tabs' => $carousels,
    );
  }

  return $block;
}

/**
 * Returns an edit form for the content type.
 */
function ting_smart_carousel_ting_smart_carousel_content_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
  $form['deltaid'] = array(
    '#description' => t('Enter delta value for carousel'),
    '#type' => 'textfield',
    '#size' => '2',
    '#default_value' => $conf['deltaid'],
  );

  return $form;
}

/**
 * Submit callback for settings form.
 */
function ting_smart_carousel_ting_smart_carousel_content_content_type_edit_form_submit($form, &$form_state) {
  foreach (element_children($form) as $key) {
    if (isset($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}
