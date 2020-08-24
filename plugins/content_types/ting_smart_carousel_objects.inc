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
  if (isset($path_elements)) {
    $query = ting_object_tree_get_query($path_elements['type'], $path_elements['audience'], $path_elements['fiction'], $path_elements['subject']);
    $start = 1;
    $size = 50;
    $result = ting_object_tree_find_entities_with_covers($query, $start, $size, array());
    $block->content = theme('ting_object_tree_list', array('items' => $result['objects']));
  }




  return $block;
}
