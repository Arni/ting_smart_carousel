<?php

/**
 * @file
 * Handles search carousel pages data.
 */

/**
 * AJAX callback to retrieve carousel items.
 *
 * @param int $index
 *   Configuration index.
 * @param int $offset
 *   Offset into result to fetch from.
 */
function ting_smart_carousel_result($query, $offset) {
  $start = 0;
  $size = 18;
  $query = urldecode($query);
  $cid = md5('new' . $query);
  //$build =  ting_smart_carousel_find_entities_with_covers($query, $start, $count, array ()); 
  $build = ting_object_tree_find_entities_with_covers($query, $start, $size, array ());

  if (isset($build)) {
    cache_set($cid, $build, 'cache_ting_smart_carousel', REQUEST_TIME + 604800); //86400
  }

  $output = '';
  foreach ($build['objects'] as $item) {
     $output .= '<li class="ding-carousel-item">' . $item . ' </li>';
  }

  // Return JSON output.
  drupal_json_output(array(
    'content' => $output,
    'offset' => 8,
  ));
}
