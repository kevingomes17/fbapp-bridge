<?php
/**
 * @file
 * fbapp_bridge_config.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function fbapp_bridge_config_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: navigation_facebook-canvas:node/add/facebook-canvas
  $menu_links['navigation_facebook-canvas:node/add/facebook-canvas'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'node/add/facebook-canvas',
    'router_path' => 'node/add/facebook-canvas',
    'link_title' => 'Facebook Canvas',
    'options' => array(
      'attributes' => array(
        'title' => 'Landing page for facebook application Canvas page.',
      ),
      'identifier' => 'navigation_facebook-canvas:node/add/facebook-canvas',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'navigation_add-content:node/add',
  );
  // Exported menu link: navigation_facebook-tab:node/add/facebook-tab
  $menu_links['navigation_facebook-tab:node/add/facebook-tab'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'node/add/facebook-tab',
    'router_path' => 'node/add/facebook-tab',
    'link_title' => 'Facebook Tab',
    'options' => array(
      'attributes' => array(
        'title' => 'Landing page for facebook application tab page.',
      ),
      'identifier' => 'navigation_facebook-tab:node/add/facebook-tab',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'navigation_add-content:node/add',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Facebook Canvas');
  t('Facebook Tab');


  return $menu_links;
}
