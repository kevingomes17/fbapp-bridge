<?php
/** @file */

/**
 * Lists all the apps that are bridged with Drupal.
 */
function fbapp_bridge_apps_list() {
	$result = db_query("SELECT * FROM {".FBAPP_BRIDGE_TBL."} fb ");
	$data = $result->fetchAll();
	//$html = "<a href='".url("fbapp-bridge/app/add")."'>+ Add Application</a>";
	$html = theme('fbapp_bridge_apps_list', $data);
	return $html;
}

/**
 * Handler for URL: "fbapp-bridge/app/add"
 * @return Returns a HTML form to create a facebook applciation bridge configuration.
 */
function fbapp_bridge_app_add() {
	drupal_set_title("Create App");
	$form_values = array(
		'action' => 'add',
		'app_namespace' => '',
		'app_id' => '',
		'app_secret_key' => '',
		'app_description' => '',
		'anonymous_nid' => '',
		'canvas_nid' => '',
		'tab_nid' => '',
		'anonymous_rid' => '',
		'authenticated_rid' => '',
		'app_theme' => '',
		'perms' => '',
		'debug' => 1,
		'request_user_login_on' => 0
	);
	return drupal_get_form("fbapp_bridge_app_form", $form_values);
}

/**
 * Handler for URL: admin/structure/fbapp-bridge/app/%/edit
 *
 * @param int $rec_id
 *
 * @see fbapp_bridge_app_load()
 */
function fbapp_bridge_app_edit($rec_id) {
	//$breadcrumbs[] = "<a href='".url("/")."'>Home</a>";
	//$breadcrumbs[] = "<a href='".url("fbapp-bridge")."'>Facebook Apps</a>";
	//drupal_set_breadcrumb($breadcrumbs);
	
	$app_rec = fbapp_bridge_app_load($rec_id);
	if(isset($app_rec["rec_id"])) {
		drupal_set_title("App Namespace: ".$app_rec["app_namespace"]);
		$app_rec['action'] = 'edit';
		return drupal_get_form("fbapp_bridge_app_form", $app_rec);
	} else {
		drupal_set_message("Application not found in database.", "warning");
	}
	//drupal_goto('admin/structure/fbapp-bridge/apps');
	drupal_goto(FBAPP_BRIDGE_LANDING_PAGE);
}

/**
 * Handler for URL: "fbapp-bridge/app/%/delete"
 * Displays a status message regarding the delete action. And redirects to "fbapp-bridge/apps"
 * @se fbapp_bridge_app_load()
 */
function fbapp_bridge_app_delete($rec_id) {
	$app_rec = fbapp_bridge_app_load($rec_id);
	if(isset($app_rec['rec_id'])) {
		$num_deleted = db_delete(FBAPP_BRIDGE_TBL)->condition('rec_id', $rec_id)->execute();
		if($num_deleted > 0) {
			drupal_set_message("Successfully deleted application.");
		} else {
			drupal_set_message("Unable to delete application.", "error");
		}
	} else {
		drupal_set_message("Application not found in database.", "warning");
	}	
	//drupal_goto("fbapp-bridge/apps");
	drupal_goto(FBAPP_BRIDGE_LANDING_PAGE);
}

/**
 * Display the form to add/edit application.
 */
function fbapp_bridge_app_form($form, &$form_state) {
	global $base_path, $base_url;
	//print "<pre>"; print_r($form_state); print "</pre>";
	$fs = $form_state['build_info']['args'][0];
	$action = $fs['action'];	
	
	//$fbappBridgeObj = new FbappBridge();
	
	if($action == 'edit') {
		$launch_url = "{$base_url}/fbapp-bridge/app/{$fs['rec_id']}/launch";
		$canvas_url = "{$base_url}/fbapp-bridge/app/{$fs['rec_id']}/canvas";
		$tab_url = "{$base_url}/fbapp-bridge/app/{$fs['rec_id']}/tab";
		$facebook_app_url = "https://apps.facebook.com/{$fs['app_namespace']}";
		$add_to_page_tab = "<a target='_blank' href='https://www.facebook.com/dialog/pagetab?app_id={$fs['app_id']}&next={$launch_url}'>Add app to Page Tab</a>";
		$form['application_info'] = array(
			'#type' => 'markup',
			'#markup' => "<div><strong>Canvas URL:</strong> {$canvas_url}</div> <div><strong>Tab URL:</strong> {$tab_url}</div> <div><strong>Facebook App URL:</strong> {$facebook_app_url}</div> <div>{$add_to_page_tab}</div>",
		);
	}
	
	$form['app_namespace'] = array(
		'#type' => 'textfield',
		'#title' => t('App Namespace'),
		'#description' => t('As given on the app settings page on facebook.com. Example: my-tweets'),
		'#default_value' => $fs['app_namespace'],
		'#required' => TRUE
	);
	$form['app_id'] = array(
		'#type' => 'textfield',
		'#title' => t('Application ID'),
		'#description' => t('As given on the app settings page on facebook.com.'),
		'#default_value' => $fs['app_id'],
		'#required' => TRUE
	);	
	$form['app_secret_key'] = array(
		'#type' => 'textfield',
		'#title' => t('Application Secret Key'),
		'#description' => t('As given on the app settings page on facebook.com.'),
		'#default_value' => $fs['app_secret_key'],
		'#required' => TRUE
	);		
	$form['canvas_nid'] = array(
		'#type' => 'textfield',
		'#title' => t('Canvas Page NID'),
		'#description' => t('Node ID when facebook Canvas Page is laoded.'),
		'#default_value' => $fs['canvas_nid'],
		'#required' => TRUE
	);	
	$form['tab_nid'] = array(
		'#type' => 'textfield',
		'#title' => t('Tab Page NID'),
		'#description' => t('Node ID when facebook Canvas Page is laoded.'),
		'#default_value' => $fs['tab_nid'],
		'#required' => TRUE
	);	
	$form['anonymous_nid'] = array(
		'#type' => 'textfield',
		'#title' => t('Anonymous NID'),
		'#description' => t('Node ID shown to users belonging to role defined in <strong>Anonymous RID</strong>. '),
		'#default_value' => $fs['anonymous_nid'],
		'#required' => FALSE
	);
	$form['perms'] = array(
		'#type' => 'textfield',
		'#title' => t('Extended Permissions'),
		'#description' => t('Comma separated permissions as mentioned on facebook.'),
		'#default_value' => $fs['perms'],
		'#required' => FALSE
	);
	$form['app_theme'] = array(
		'#type' => 'select',
		'#title' => t('Theme to use for the App'),
		'#description' => t('Machine-name of the theme. Leave blank to use the default theme.'),
		'#default_value' => $fs['app_theme'],
		'#options' => fbapp_bridge_get_themes_array(),
		'#required' => FALSE
	);		
	$form['anonymous_rid'] = array(
		'#type' => 'select',
		'#title' => t('Anonymous Role ID'),
		'#description' => t('Role ID to be assigned to anonymous users.'),
		'#default_value' => $fs['anonymous_rid'],
		'#options' =>fbapp_bridge_get_roles_array(),
		'#required' => FALSE
	);
	$form['authenticated_rid'] = array(
		'#type' => 'select',
		'#title' => t('Authenticated Role ID'),
		'#description' => t('Role ID to be assigned to authenticated users.'),
		'#default_value' => $fs['authenticated_rid'],
		'#options' => fbapp_bridge_get_roles_array(),
		'#required' => FALSE
	);	
	$form['app_description'] = array(
		'#type' => 'textarea',
		'#title' => t('Application Description'),
		'#description' => t('Purpose of the facebook application.'),
		'#default_value' => $fs['app_description'],
	);
	$form['request_user_login_on'] = array(
		'#type' => 'select',
		'#title' => t('Request User Login On'),
		'#description' => t('Specify when the authentication dialog should be displayed to users.'),
		'#default_value' => $fs['request_user_login_on'],
		'#options' => FbappBridge::getRequestUserLoginOn_options(),
		'#required' => FALSE
	);
	$form['debug'] = array(
		'#type' => 'select',
		'#title' => t('Enable Debug Mode'),
		'#description' => t('Prints debug statements and displays messages helpful to the developers.'),
		'#default_value' => $fs['debug'],
		'#options' => array(1=>"Yes", 0=>"No"),
		'#required' => FALSE
	);
	
	$form['app_action'] = array(
		'#type' => 'hidden',
		'#default_value' => $action,
	);		
	
	if($action == 'edit') {
		$form['rec_id'] = array(
			'#type' => 'hidden',
			'#default_value' => $fs['rec_id']
		);
	}
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Submit'),
    );
	return $form;
}

/**
 * Validation handler for form generated by "fbapp_bridge_app_form()".
 * Validates the bridge configuration form. 
 */
function fbapp_bridge_app_form_validate($form, &$form_state) {
	$sd = $form_state["values"]; //submitted data	
	$app_action = $sd['app_action'];
	//print "<pre>"; print_r($form_state); print "</pre>";
	
	/*
	if(trim($sd["app_namespace"])) == "") {
		form_set_error("app_namespace", "App Namespace can't be left blank.");
	}
	*/
	if($app_action == "edit") {
		//Check whether another app with the same app_id exists.
	}
}

/**
 * Submit handler for "fbapp_bridge_app_form()" form. Saves the app configuration to the database.
 * @param array $form
 * @param array &$form_state
 */
function fbapp_bridge_app_form_submit($form, &$form_state) {
	//print "<pre>"; print_r($form); print_r($form_state); print "</pre>"; die();
	$data = array(
		'app_namespace' => $form_state['values']['app_namespace'],
		'app_id' => $form_state['values']['app_id'],
		'app_secret_key' => $form_state['values']['app_secret_key'],
		'app_description' => $form_state['values']['app_description'],
		'anonymous_nid' => $form_state['values']['anonymous_nid'],
		'canvas_nid' => $form_state['values']['canvas_nid'],
		'tab_nid' => $form_state['values']['tab_nid'],
		'anonymous_rid' => $form_state['values']['anonymous_rid'],
		'authenticated_rid' => $form_state['values']['authenticated_rid'],
		'app_theme' => $form_state['values']['app_theme'],
		'perms' => $form_state['values']['perms'],
		'debug' => $form_state['values']['debug'],
		'request_user_login_on' => $form_state['values']['request_user_login_on']
	);
	
	if($form_state['values']['app_action'] == 'add') {
		$data['created'] = time();
		drupal_write_record(FBAPP_BRIDGE_TBL, $data);		
		drupal_goto(FBAPP_BRIDGE_LANDING_PAGE);
	} else if($form_state['values']['app_action'] == 'edit') {		
		$data['changed'] = time();
		$num_updated = db_update(FBAPP_BRIDGE_TBL)->fields($data)->condition('rec_id', $form_state['values']['rec_id'], '=')->execute();
		if($num_updated > 0) { drupal_set_message("Successfully updated application details."); }
	}
}

/**
 * Handler for URL: "fbapp-bridge/app/%/blocks"
 * Captures the blocks that should be rendered in the theme regions.
 * @param int $rec_id
 *   Redirects to the main module configuration page if the $rec_id is incorrect. Else displays a form.
 *
 * @see fbapp_bridge_configure_blocks_form()
 */
function fbapp_bridge_configure_blocks($rec_id) {
	//$breadcrumbs[] = "<a href='".url("/")."'>Home</a>";
	//$breadcrumbs[] = "<a href='".url("fbapp-bridge")."'>Facebook Apps</a>";
	//drupal_set_breadcrumb($breadcrumbs);

	$app_rec = fbapp_bridge_app_load($rec_id);
	if(isset($app_rec["rec_id"])) {
		$form_values = $app_rec;
		return drupal_get_form("fbapp_bridge_configure_blocks_form", $form_values);	
	} else {
		drupal_set_message("Invalid App ID provided.","warning");
		//drupal_goto('fbapp-bridge/apps');
		drupal_goto(FBAPP_BRIDGE_LANDING_PAGE);
	}
}

/**
 * Returns form array to configure blocks for the application.
 * @param array $form
 * @param array &$form_state
 *
 * @see fbapp_bridge_configure_blocks()
 * @see fbapp_bridge_get_themes_array()
 * @see fbapp_bridge_get_blocks_array()
 */
function fbapp_bridge_configure_blocks_form($form, &$form_state) {
	$fs = $form_state['build_info']['args'][0];
	
	$themes = fbapp_bridge_get_themes_array();
	$region_options = system_region_list($fs["app_theme"]);	
	$block_options = fbapp_bridge_get_blocks_array();
	
	$app_recs = db_select(FBAPP_BRIDGE_BLOCKS_TBL, 'c')->fields('c')->condition('fbapp_bridge_rec_id', $fs['rec_id'], '=')->condition('theme', $fs["app_theme"], '=')->orderBy("weight", "ASC")->execute()->fetchAll();	
	$html = theme('fbapp_bridge_blocks_list', $app_recs);
	
	drupal_set_title("App Namespace: ".$fs["app_namespace"]);
	
	$form['info'] = array(
		'#type' => 'fieldset',
		'#title' => "Blocks for \"{$themes[$fs['app_theme']]}\" theme",
		'#collapsible' => TRUE,
		'#value' => $html,
	);
	
	$form['theme'] = array(
		'#type' => 'hidden',
		'#value' => $fs['app_theme'],
		'#prefix' => '<table width="100%"><tr><td>',
	);
	
	$form['fbapp_bridge_rec_id'] = array(
		'#type' => 'hidden',
		'#value' => $fs['rec_id'],
	);
	
	$form['block_delta'] = array(
		'#type' => 'select',
		'#title' => t('Block'),
		'#default_value' => '',
		'#options' => $block_options,
		'#required' => TRUE,
		'#suffix' => "</td>",
	);
	
	$form['page_type'] = array(
		'#type' => 'select',
		'#title' => t('Page Type'),
		'#default_value' => '',
		'#options' => array("all" => "All", "canvas" => "Canvas", "tab" => "Tab"),
		'#required' => TRUE,
		'#prefix' => "<td>",		
		'#suffix' => "</td>",		
	);

	$form['region'] = array(
		'#type' => 'select',
		'#title' => t('Region'),
		'#default_value' => '',
		'#options' => $region_options,
		'#required' => TRUE,
		'#prefix' => "<td>",		
		'#suffix' => "</td>",		
	);

	$form['weight'] = array(
		'#type' => 'select',
		'#title' => t('Weight'),
		//'#description' => t('Lighter blocks float to the top.'),
		'#default_value' => '',
		'#options' => array(1=>1,2=>2,3=>3,4=>4,5=>5,6=>6,7=>7,8=>8,9=>9,10=>10,11=>11,12=>12,13=>13,14=>14,15=>15),
		'#required' => TRUE,
		'#prefix' => "<td>",		
		'#suffix' => "</td>",				
	);	
	
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => 'Save',
		'#prefix' => "<td>",		
		'#suffix' => "</td></tr></table>",		
	);	
	return $form;
}

/**
 * Validate handler for form generated by fbapp_bridge_configure_blocks_form().
 * @see fbapp_bridge_configure_blocks_form()
 */
function fbapp_bridge_configure_blocks_form_validate($form, &$form_state) {
	$sd = $form_state["values"]; //submitted data	
	
	$block_delta = explode("|", $sd["block_delta"]);
	$app_rec = db_select(FBAPP_BRIDGE_BLOCKS_TBL, 'c')->fields('c')->condition('fbapp_bridge_rec_id', $sd['fbapp_bridge_rec_id'], '=')->condition('theme', $sd["theme"], '=')->condition('region', $sd['region'], '=')->condition('block_module', $block_delta[0], '=')->condition('block_delta', $block_delta[1], '=')->execute()->fetchAssoc();	
	if(isset($app_rec["rec_id"])) {
		form_set_error("fbapp_bridge_rec_id", "The selected Block-Region pair exists.");
	}
}

/**
 * Submit handler for the form generated by fbapp_bridge_configure_blocks_form().
 * @see fbapp_bridge_configure_blocks_form()
 */
function fbapp_bridge_configure_blocks_form_submit($form, &$form_state) {
	$block_delta = explode("|",$form_state['values']['block_delta']);
	$data = array(
		'theme' => $form_state['values']['theme'],
		'region' => $form_state['values']['region'],
		'weight' => $form_state['values']['weight'],
		'block_module' => $block_delta[0],
		'block_delta' => $block_delta[1],
		'fbapp_bridge_rec_id' => $form_state['values']['fbapp_bridge_rec_id'],
		'page_type' => $form_state['values']['page_type'],
		'created' => time()
	);	
	$num = drupal_write_record(FBAPP_BRIDGE_BLOCKS_TBL, $data);
	if($num > 0) {
		drupal_set_message("Successfully configured block.");
	} else {
		drupal_set_message("Unable to configure block.", "error");
	}
}

/**
 * Handler for URL: "fbapp-bridge/app/%/block/%/delete"
 * Deletes a block.
 * @todo Require a confirmation before deleting.
 */
function fbapp_bridge_block_delete($fbapp_bridge_rec_id, $rec_id) {
	$block_rec = fbapp_bridge_block_load($rec_id);
	if(isset($block_rec['rec_id'])) {
		$num_deleted = db_delete(FBAPP_BRIDGE_BLOCKS_TBL)->condition('rec_id', $rec_id)->execute();
		if($num_deleted > 0) {
			drupal_set_message("Successfully deleted block.");
		} else {
			drupal_set_message("Unable to delete block.", "error");
		}
	} else {
		drupal_set_message("Block not found in database.", "warning");
	}	
	drupal_goto("admin/structure/fbapp-bridge/app/{$fbapp_bridge_rec_id}/blocks");
}

/**
 * @return array $themes_arr 
 *   Returns list of themes stored in {system} table.
 */
function fbapp_bridge_get_themes_array() {
	$result = db_query("SELECT * FROM {system} WHERE type = 'theme' AND status = 1 ORDER BY weight ASC, name ASC");
	$themes = $result->fetchAll();
	$themes_arr = array();
	foreach($themes as $theme) {
		$info = unserialize($theme->info);
		$themes_arr[$theme->name] = $info["name"];
	}
	return $themes_arr;
}

/**
 * @return array $blocks_arr
 *   Returns list of blocks as an associative array.
 */
function fbapp_bridge_get_blocks_array() {
	$result = db_query("SELECT distinct module FROM {block}");
	$modules = $result->fetchAll();
	$blocks_arr = array();
	//print "<pre>"; print_r($blocks); print "</pre>";
	foreach($modules as $module) {
		$module_name = $module->module;		
		//$func_name = $module_name."_block_info";
		//$blocks = call_user_func($func_name);
		$blocks = module_invoke($module_name, 'block_info');
		if(gettype($blocks) == "array") {
			foreach($blocks as $block_machine_name=>$block_info) {
				$blocks_arr[$module_name."|".$block_machine_name] = $module_name.": ".$block_info["info"];
			}
		}
	}	
	return $blocks_arr;
}

/**
 * @return array $roles_arr
 *   Returns roles in the {role} table.
 */
function fbapp_bridge_get_roles_array() {
	$result = db_query("SELECT rid, name, weight FROM {role} ORDER BY weight ASC, name ASC");
	$roles = $result->fetchAll();
	$roles_arr = array();
	foreach($roles as $role) {
		$roles_arr[$role->rid] = $role->name;
	}
	return $roles_arr;
}