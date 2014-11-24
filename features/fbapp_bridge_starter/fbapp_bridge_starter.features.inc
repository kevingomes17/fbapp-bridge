<?php
/**
 * @file
 * fbapp_bridge_starter.features.inc
 */

/**
 * Implements hook_node_info().
 */
function fbapp_bridge_starter_node_info() {
  $items = array(
    'fbapp_bridge_launch' => array(
      'name' => t('FBApp Bridge Launch'),
      'base' => 'node_content',
      'description' => t('Create a FBApp Bridge Launch node to be rendered as Canvas/Tab page.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
