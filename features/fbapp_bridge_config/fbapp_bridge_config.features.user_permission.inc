<?php
/**
 * @file
 * fbapp_bridge_config.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function fbapp_bridge_config_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create facebook_canvas content'.
  $permissions['create facebook_canvas content'] = array(
    'name' => 'create facebook_canvas content',
    'roles' => array(
      'facebook user' => 'facebook user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create facebook_tab content'.
  $permissions['create facebook_tab content'] = array(
    'name' => 'create facebook_tab content',
    'roles' => array(
      'facebook user' => 'facebook user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any facebook_canvas content'.
  $permissions['delete any facebook_canvas content'] = array(
    'name' => 'delete any facebook_canvas content',
    'roles' => array(
      'facebook user' => 'facebook user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any facebook_tab content'.
  $permissions['delete any facebook_tab content'] = array(
    'name' => 'delete any facebook_tab content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own facebook_canvas content'.
  $permissions['delete own facebook_canvas content'] = array(
    'name' => 'delete own facebook_canvas content',
    'roles' => array(
      'facebook user' => 'facebook user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own facebook_tab content'.
  $permissions['delete own facebook_tab content'] = array(
    'name' => 'delete own facebook_tab content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit any facebook_canvas content'.
  $permissions['edit any facebook_canvas content'] = array(
    'name' => 'edit any facebook_canvas content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit any facebook_tab content'.
  $permissions['edit any facebook_tab content'] = array(
    'name' => 'edit any facebook_tab content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit own facebook_canvas content'.
  $permissions['edit own facebook_canvas content'] = array(
    'name' => 'edit own facebook_canvas content',
    'roles' => array(
      'facebook user' => 'facebook user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own facebook_tab content'.
  $permissions['edit own facebook_tab content'] = array(
    'name' => 'edit own facebook_tab content',
    'roles' => array(
      'facebook user' => 'facebook user',
    ),
    'module' => 'node',
  );

  return $permissions;
}
