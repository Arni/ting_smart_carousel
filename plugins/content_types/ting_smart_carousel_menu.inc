<?php
/**
 * @file
 * Panels pane to display the smart search form
 */

$plugin = array(
  'title' => t('Ting smart carousel menu'),
  'description' => t("Display menu"),
  'single' => FALSE,
  'content_types' => array('inspiration_carousel'),
  'render callback' => 'ting_smart_carousel_menu_render',
  'category' => t('Ting'),
  'render last' => TRUE,
);




/**
 * Render the smart carousel block.
 */
function ting_smart_carousel_menu_render($subtype, $conf, $panel_args, $context) {
  $menu_links = menu_tree_output(menu_tree_page_data('menu-object-navigation', NULL, TRUE));
  $menu = drupal_render($menu_links);

  $block = new stdClass();

  $block->title = '';
  $block->content = theme('ting_smart_carousel_menu', array('menu' => $menu));;

  return $block;
}


