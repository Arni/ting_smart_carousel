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
  $count = 18;
  $query = urldecode($query);
  file_put_contents("/var/www/drupalvm/drupal/debug/car7.txt", print_r($query , TRUE), FILE_APPEND);
  $build =  ting_smart_carousel_find_entities_with_covers($query, $start, $count, array ()); 
//  $chunk = _ting_search_carousel_get_frontpage_entities(0, 0, TING_SEARCH_CAROUSEL_CHUNK_SIZE);
//  foreach ($chunk['entities'] as $entity) {
//    $build[] = array(
//      '#type' => 'ding_carousel_item',
//      '#content' => ting_object_view($entity, 'teaser'),
//    );
//  }
// file_put_contents("/var/www/drupalvm/drupal/debug/car6.txt", print_r(drupal_render($build), TRUE), FILE_APPEND);
  
//  // If there's more covers, add a placeholder at the end to signal the user
//  // that it's loading.
//  if ($chunk['next_offset'] > -1) {
//    $build[] = array(
//      '#type' => 'ding_carousel_item',
//      '#placeholder' => TRUE,
//    );
//  }

  // Return JSON output.
  drupal_json_output(array(
    'content' => implode($build),
    'offset' => 8//,$chunk['next_offset'],
  ));
}
