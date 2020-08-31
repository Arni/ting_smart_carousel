<?php
/**
 * @file
 * Panels pane to display the smart search form
 */

$plugin = array(
  'title' => t('Ting smart carousel breadcrumb'),
  'description' => t("Display breadcrumb"),
  'single' => FALSE,
  'content_types' => array('inspiration_carousel'),
  'render callback' => 'ting_smart_carousel_breadcrumb_render',
  'category' => t('Ting'),
  'render last' => TRUE,
);



/**
 * Render the smart carousel block.
 */
function ting_smart_carousel_breadcrumb_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  $block->title = '';
  $block->content = '';
  $path_elements = ting_object_tree_get_current_path();
  if (isset($path_elements)) {
    $breadcrumb = ting_object_tree_get_tree_breadcrumb($path_elements['type'], $path_elements['audience'], $path_elements['fiction'], $path_elements['subject']);
    $block->content = '<div class="ting-object-tree-breadcrumb">' . $breadcrumb . '</div>';
  }
  $menu_links = menu_tree_output(menu_tree_page_data('menu-object-navigation', NULL, TRUE));
  $menu = drupal_render($menu_links);

  drupal_add_js(drupal_get_path('module', 'ting_object_tree') . '/js/object_tree_categories.js', 'file');
  $block->content .= theme('ting_object_tree_mobile_menu', array('menu' => $menu));

  return $block;
}
