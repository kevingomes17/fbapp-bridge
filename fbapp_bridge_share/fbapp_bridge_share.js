Drupal.behaviors.FbappBridgeShare = {
	attach: function(context, settings) {
		//console.log(settings);
		if(typeof(settings.fbapp_bridge_share) != 'undefined' && settings.fbapp_bridge_share.is_fbapp_bridge_launch_page == 1) {
			//FbappBridgeShare.initShareTooltip(settings);
			FbappBridgeShare.initShareInPlaceTip(settings);
		}
	}
}; 

var FbappBridgeShare = new function() {
	var thisObj = this;
	var nodeToShare = null;
	
	/**
	 * data - {nid:10, title:'', description: '', picture: ''}
	 */
	this.shareNodeOnFacebook = function(data) {	
		var settings = Drupal.settings;
		var options = {
			name: 'Turano Cookbook',
			link: settings.fbapp_bridge.baseUrl+settings.basePath+'fbapp-bridge/'+data.nid+'/'+settings.fbapp_bridge.recId+'/render-node',
			caption: data.title.replace(/\|/g,"'"),
			description: data.description.replace(/\|/g, "'"),
			picture: data.picture
		};
		FbappBridge.feed(options);
	};
	
	this.initShareTooltip = function(settings) {
		var fbappBridgeSettings = settings.fbapp_bridge;
		var url = settings.basePath+'fbapp-bridge-share/ajax/'+fbappBridgeSettings.recId+'/';
		jQuery('.share-icon-node').each(function() {
			var nidToShare = jQuery(this).attr('nid');
			
			jQuery(this).attr('rel', url+nidToShare).cluetip({
				showTitle: false,
				delayedClose: 3000,
				width: 175,
				multiple: true
			});		
		});
	};
	
	//Hides the hover element and shows share icons in place of it.
	this.initShareInPlaceTip = function(settings) {
		var fbappBridgeSettings = settings.fbapp_bridge;
		var url = settings.basePath+'fbapp-bridge-share/ajax/'+fbappBridgeSettings.recId+'/';
		jQuery('.share-icon-node').hover(function() {
			var thisObj = jQuery(this);
			var nidToShare = jQuery(this).attr('nid');
			
			if(!thisObj.hasClass('share-icon-node-processed')) {
				jQuery.ajax({
					url: url+nidToShare,
					success: function(response) {
						//console.log(response);
						
						if(!thisObj.hasClass('share-icon-node-processed')) {
							thisObj.addClass('share-icon-node-processed');
							thisObj.hide().after(response);
							thisObj.next().hover(function() {},function() {
								thisObj.show().next().hide();
							});
						}
					},
					failure: function() {}
				});
			} else {
				thisObj.hide().next().show();
			}
		});	
	};
};