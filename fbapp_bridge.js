/** @file */

Drupal.behaviors.fbappBridge_initLaunchedApp = {
	isInitialized: false,
	
	attach: function(context, settings) {
		//console.log(context);
		//console.log(settings);
		//console.log(top.location.href);
		
		if(settings.fbapp_bridge) {
			var isInitialized = Drupal.behaviors.fbappBridge_initLaunchedApp.isInitialized;
			
			if(isInitialized == false) {
				//console.log('initLaunchedApp');
				
				//add the facebook-js-sdk snippet after the body
				var body = jQuery(context).find('body').get(0);
				jQuery(body).prepend("<div id='fb-root'></div>");
				
				// Load the SDK asynchronously
				  (function(d, s, id){
					 var js, fjs = d.getElementsByTagName(s)[0];
					 if (d.getElementById(id)) {return;}
					 js = d.createElement(s); js.id = id;
					 js.src = "//connect.facebook.net/en_US/all.js";
					 fjs.parentNode.insertBefore(js, fjs);
				   }(document, 'script', 'facebook-jssdk'));
				   
				Drupal.behaviors.fbappBridge_initLaunchedApp.isInitialized = true;
			}
		}
	}
};

Drupal.behaviors.fbappBridge_fixLinks = {
	attach: function(context, settings) {
		//console.log('bang');
		//console.log(settings);
		if(settings.fbapp_bridge) {
			//console.log('salaam');
			//Updating all href on the page.
			var newHref = '';
			jQuery('a').each(function() {				
				var anchor = jQuery(this);
				var href = anchor.attr('href');
				
				if(typeof(href) != 'undefined' && href[0] != '#') {
					//console.log(href);
					var tmp = href.match(/fbapp-bridge/);
					if(tmp == null) { //this is not a fbapp-bridge/app url 
						//console.log(this.href+' - '+href);
						if(href == '/') {
							newHref = settings.basePath+'fbapp-bridge/app/'+settings.fbapp_bridge.recId+'/'+settings.fbapp_bridge.pageType;
						} else {
							newHref = settings.basePath+'fbapp-bridge/app/'+settings.fbapp_bridge.recId+'/render-path'+href
						}
						anchor.attr('href', newHref);
					}					
				}
			});
		}
	}
};

Drupal.behaviors.fbappBridge_initFBContent = {
	attach: function(context, settings) {
		if(settings.fbapp_bridge) {
			jQuery('.fbapp-bridge-login-button').css('cursor', 'pointer').click(function() {
				FbappBridge.login();
			});
		}
	}
};

/**
 * Initializes facebook application.
 */
window.fbAsyncInit = function() {
	if (Drupal.settings.fbapp_bridge) {
		//console.log(Drupal.settings.fbapp_bridge);
		
		var config = Drupal.settings.fbapp_bridge;
    	// init the FB JS SDK
		FB.init({
		  appId      : config.appId,      // App ID from the app dashboard
		  channelUrl : config.channelUrl, // Channel file for x-domain comms
		  status     : true,              // Check Facebook Login status
		  xfbml      : true,               // Look for social plugins on the page
		  cookie	 : true				  //this is essential to maintain fb session across PHP & JS.
		});		
		
		//FB.getLoginStatus(FbappBridge.processLoginStatusOnPageLoad);	not required
		FB.Canvas.setSize();
		
		// Additional initialization code such as adding Event Listeners goes here
		//FB.Event.subscribe('auth.login', FbappBridge.userAuthorizedApp);
		FB.Event.subscribe('auth.authResponseChange', FbappBridge.processLoginStatusChange);
		//FB.Event.subscribe('auth.logout', FbappBridge.userLoggedOut);		
		FB.Event.subscribe('auth.statusChange', FbappBridge.processLoginStatusOnPageLoad);
		
		if(config.request_fbuser_login == 1) {
			FbappBridge.login();
		}		
  	}
};

/**
 * Makes sure to invoke these functions only after facebook JS library is loaded.
 * Facebook JS wrapper library. List of helper functions.
 */
var FbappBridge = new function() {
	var thisObj = this;
	
	/*
	this._myfeed = function() {
		FB.ui({
			method: 'feed',
			name: 'Facebook Dialogs',
			link: 'https://developers.facebook.com/docs/reference/dialogs/',
			picture: 'http://fbrell.com/f8.jpg',
			caption: 'Reference Documentation',
			description: 'Dialogs provide a simple, consistent interface for applications to interface with users.'
		  },
		  function(response) {
			if (response && response.post_id) {
			  alert('Post was published.');
			} else {
			  alert('Post was not published.');
			}
		});
	};
	*/
	
	this.feed = function(options) {
		//console.log(options);
		//alert(options.description);
		FB.ui({
			method: 'feed',
			name: options.name,
			link: options.link,
			picture: 'http://turanorecipe.apps-ibtest.com/sites/all/themes/recipe/logo.png', //options.picture,
			caption: options.caption,
			description: options.description
		  },
		  function(response) {
			if (response && response.post_id) {
			  alert('Successfully published post.');
			} else {
			  //alert('Post was not published.');
			}
		});
	};
	
	/**
	 * TODO: 
	 * 1. You might want to request app authorization in this handler.
	 */
	this.processLoginStatusOnPageLoad = function(response) {
		//console.log('a');
		//console.log(response);
		if (response.status === 'connected') {
			// the user is logged in and has authenticated your app, and response.authResponse supplies
			// the user's ID, a valid access token, a signed request, and the time the access token 
			// and signed request each expire
			var uid = response.authResponse.userID;
			var accessToken = response.authResponse.accessToken;
		} else if (response.status === 'not_authorized') {
			// the user is logged in to Facebook, but has not authenticated the app
			//TODO:(1)	
		} else {
			// the user isn't logged in to Facebook. Do a full redirect to get a consistent state.			
		}
	};
	
	/**
	 * Login/Authorize/Permissions
	 * permissions - 'email,user_likes'	 
	 * TODO: Consider scenario where user doesn't grant permissions.
	 */
	this.login = function() {	
		if (Drupal.settings.fbapp_bridge) {
			var permissions = Drupal.settings.fbapp_bridge.permissions;
			FB.login(function(response) {			
			   if (response.authResponse) {
			   	 thisObj.redirectAfterLogin();			     
			   } else {
				 //console.log('User cancelled login or did not fully authorize.');
			   }
			}, {scope: permissions});
		 }
	};
	
	this.redirectAfterLogin = function() {	
		if(Drupal.settings.fbapp_bridge.redirect_page_after_login) {
			top.location.href = Drupal.settings.fbapp_bridge.redirect_page_after_login;
		}
	}
	
	/**
	 * Function invoked when user authorizes the app.
	{
	  status: "",           // Current status of the session 
	  authResponse: {       // Information about the current session 
		userID: ""          // String representing the current user's ID 
		signedRequest: "",  // String with the current signedRequest 
		expiresIn: "",      // UNIX time when the session expires 
		accessToken: "",    // Access token of the user 
	  }
	}
	*/
	this.userAuthorizedApp = function(response) {
		//alert('user authorized app');
		//console.log('User authorized the app '+response);
		//Make AJAX call 
	};
	
	/**
	 {
	   status: "",  // Current status of the session 
	 }
	 */
	this.userLoggedOut = function(response) {
		//console.log('User logged out.');
	};
	
	/**
	 * called when user logs in and status changes to 'connectecd'
	 * called if the user is already 'connected'
	 */
	this.processLoginStatusChange = function(response) {
		//console.log(response);
	};
};