<?php

/**
 * @file
 * Panels pane to display the smart search form
 */
$plugin = array(
  'title' => t('Ting smart carousel objects'),
  'description' => t("Display all objects"),
  'single' => FALSE,
  'content_types' => array('inspiration_carousel'),
  'render callback' => 'ting_smart_carousel_objects_render',
  'category' => t('Ting'),
  'render last' => TRUE,
  'required context' => array(
    new ctools_context_optional(t('Inspirations karrusel'), 'node'),
  )
);

//function ting_smart_carousel_ting_smart_carousel_content_content_type_access() {
//  $return = FALSE;
//  global $user;
//  if ($user->uid == '1') {
//    $return = TRUE;
//  }
//  return $return;
//}

/**
 * Render the smart carousel block.
 */
function ting_smart_carousel_objects_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  $block->title = '';
  $path_elements = ting_object_tree_get_current_path();

  file_put_contents("/var/www/drupal7vm/drupal/debug/nav2.txt", print_r($context[0], TRUE), FILE_APPEND);
  if (isset($context[0]->data))
    $node_wrapper = entity_metadata_wrapper('node', $context[0]->data);
  $query = $node_wrapper->field_search_query->value();
  if (empty($query) && isset($path_elements)) {
    $query = ting_object_tree_get_query($path_elements['type'], $path_elements['audience'], $path_elements['fiction'], $path_elements['subject']);
  }
  file_put_contents("/var/www/drupal7vm/drupal/debug/nav3.txt", print_r($query, TRUE), FILE_APPEND);
  $parameters = drupal_get_query_parameters();
  $page = 1;
  $size = 48;
  if (isset($parameters['page'])) {
    $page = $parameters['page'];
  }
  $title = NULL;
  if (isset($context[0]->data->field_ting_carousel['und'][0]) && $page == 1) {
    $title = 'Alle ' . $path_elements['subject'];
  }

  $result = ting_object_tree_find_entities_with_covers($query, $page, $size, array());
  $block->content = theme('ting_object_tree_list', array('items' => $result['objects'], 'pager' => $result['pager'], 'title' => $title));

  return $block;
}
