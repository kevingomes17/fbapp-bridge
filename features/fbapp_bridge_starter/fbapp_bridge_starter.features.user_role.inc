<?php
/**
 * @file
 * fbapp_bridge_starter.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function fbapp_bridge_starter_user_default_roles() {
  $roles = array();

  // Exported role: fbapp authorized.
  $roles['fbapp authorized'] = array(
    'name' => 'fbapp authorized',
    'weight' => 3,
  );

  // Exported role: fbapp unauthorized.
  $roles['fbapp unauthorized'] = array(
    'name' => 'fbapp unauthorized',
    'weight' => 4,
  );

  return $roles;
}
