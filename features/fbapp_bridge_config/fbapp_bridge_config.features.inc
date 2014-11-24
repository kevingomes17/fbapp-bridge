<?php
/**
 * @file
 * fbapp_bridge_config.features.inc
 */

/**
 * Implements hook_node_info().
 */
function fbapp_bridge_config_node_info() {
  $items = array(
    'facebook_canvas' => array(
      'name' => t('Facebook Canvas'),
      'base' => 'node_content',
      'description' => t('Landing page for facebook application Canvas page.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'facebook_tab' => array(
      'name' => t('Facebook Tab'),
      'base' => 'node_content',
      'description' => t('Landing page for facebook application tab page.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
