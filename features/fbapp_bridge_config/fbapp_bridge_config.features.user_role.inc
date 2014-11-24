<?php
/**
 * @file
 * fbapp_bridge_config.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function fbapp_bridge_config_user_default_roles() {
  $roles = array();

  // Exported role: facebook user.
  $roles['facebook user'] = array(
    'name' => 'facebook user',
    'weight' => 3,
  );

  return $roles;
}
