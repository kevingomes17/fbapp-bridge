<?php
/** @file */

/**
 * Theming function to render the HTML markup while displaying the list of applications.
 * @see fbapp_bridge_theme()
 */
function theme_fbapp_bridge_apps_list($items) {
	//print "<pre>"; print_r($items); print "</pre>";
	$html = "";
	if(count($items) > 0) {
		$html = "<table width='100%'>";
		$html .= "<tr><th>App ID | Secret Key</th> <th>Namespace</th> <th>Description</th> <th></th></tr>";
		foreach($items as $i => $rec) {
			$html .= "<tr>";
			$html .= "<td>{$rec->app_id} | {$rec->app_secret_key}</td>";
			$html .= "<td>{$rec->app_namespace}</td>";
			$html .= "<td>{$rec->app_description}</td>";			
			$html .= "<td><a href='".url("admin/structure/fbapp-bridge/app/{$rec->rec_id}/edit")."'>Edit</a> <a href='".url("admin/structure/fbapp-bridge/app/{$rec->rec_id}/delete")."'>Delete</a>";
			if($rec->anonymous_nid != 0 || $rec->authenticated_nid != 0) {
				$html .= " <a href='".url("fbapp-bridge/app/{$rec->rec_id}/launch")."' target='_blank'>Launch</a>";
			}
			$html .= "</td>";
			$html .= "</tr>";
		}
		$html .= "</table>";
	} else {
		$html = "<p>No apps configured yet! Click on <strong>Create App</strong> to configure a Facebook App.</p>";
	}
	return $html;
}

/**
 * Theme the configure blocks form.
 */
function theme_fbapp_bridge_blocks_list($items) {	
	if(count($items) > 0) {
		$html = "<table width='100%'>";
		$html .= "<tr><th>Module: Delta</th> <th>Region</th> <th>Weight</th> <th></th></tr>";
		foreach($items as $i=>$rec) {
			$html .= "<tr>";
			$html .= "<td>{$rec->block_module}: {$rec->block_delta}</td>";
			$html .= "<td>{$rec->region}</td>";
			$html .= "<td>{$rec->weight}</td>";
			$html .= "<td><a href='".url("admin/structure/fbapp-bridge/app/".$rec->fbapp_bridge_rec_id."/block/".$rec->rec_id."/delete")."'>Delete</a></td>";
			$html .= "</tr>";
		}
		$html .= "</table><br/>";
	} else {
		$html = "<p>Start adding blocks to the facebook app.</p><br/>";
	}
	return $html;
}