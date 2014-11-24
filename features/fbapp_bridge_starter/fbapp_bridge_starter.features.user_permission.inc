<?php
/**
 * @file
 * fbapp_bridge_starter.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function fbapp_bridge_starter_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create fbapp_bridge_launch content'.
  $permissions['create fbapp_bridge_launch content'] = array(
    'name' => 'create fbapp_bridge_launch content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any fbapp_bridge_launch content'.
  $permissions['delete any fbapp_bridge_launch content'] = array(
    'name' => 'delete any fbapp_bridge_launch content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own fbapp_bridge_launch content'.
  $permissions['delete own fbapp_bridge_launch content'] = array(
    'name' => 'delete own fbapp_bridge_launch content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit any fbapp_bridge_launch content'.
  $permissions['edit any fbapp_bridge_launch content'] = array(
    'name' => 'edit any fbapp_bridge_launch content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit own fbapp_bridge_launch content'.
  $permissions['edit own fbapp_bridge_launch content'] = array(
    'name' => 'edit own fbapp_bridge_launch content',
    'roles' => array(),
    'module' => 'node',
  );

  return $permissions;
}
