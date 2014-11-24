<?php
/**
 * All facebook specific functionality is encapsulated in this class.
 * Drupal modules should use the facebook wrapper functions defined in this class, 
    so that updating when facebook API changes becomes easier.
 */
class FbappBridge {
  const USER_LOGIN_NOT_REQUIRED = 0;
  const LOGIN_BTN_ON_UNAUTHORIZED_PAGES = 1;
  const LOGIN_ON_PAGE_LOAD = 2;  

  function FbappBridge() {

  }
  
  static function getRequestUserLoginOn_options() {
  	return array(
      self::USER_LOGIN_NOT_REQUIRED => "User login not required",
      self::LOGIN_BTN_ON_UNAUTHORIZED_PAGES => "Display login button on un-authorized pages", 
      self::LOGIN_ON_PAGE_LOAD => "Request to login on page load. (Browser may block popup)");
  }
  
  private static $mobileDetectObj = null;
  static function getMobileDetect() {
  	if(gettype(FbappBridge::$mobileDetectObj) == "NULL") {
  		FbappBridge::$mobileDetectObj = new Mobile_Detect();
  	}
  	return FbappBridge::$mobileDetectObj;
  }
  
  /** Facebook related functionality below this line *************************************/
  //Make sure the Facebook PHP SDK is loaded
  
  private static $fbObj = null;
  static function initFb($app_id, $secret_key) {    
    if(gettype(FbappBridge::$fbObj) == "NULL") {
		FbappBridge::$fbObj = new Facebook(array(
			'appId' => $app_id,
			'secret' => $secret_key,
			'cookie' => TRUE,
		));
	}
	return FbappBridge::$fbObj;
  }
  
  /**
   * Returns facebook object.
   */
  static function getFb() {    
    if(gettype(FbappBridge::$fbObj) == "NULL") {
		return false;    
    } else {
		return FbappBridge::$fbObj;
  	}
  }
  
  //Returns profile pic URL of a facebook user.
  static function getFbUserProfilePicUrl($fbid) {
	return "https://graph.facebook.com/{$fbid}/picture";
  }
  
  //Returns the facebook app canvas page URL.
  static function getFbAppUrl($app_namespace) {
	return "https://apps.facebook.com/{$app_namespace}/";
  }

  //Returns blank if facebook object is not instantiated.
  static function getFbUserName($fbid) {
  	if(gettype(FbappBridge::$fbObj) != "NULL") {
		$r = FbappBridge::$fbObj->api("/".$fbid);
		return $r["name"];
	} else {
		return "";
	}
  }
  
  //Returns '0' if there's an exception getting the FBID of the user.
  static function getFbUserFbid() {
    $fbid = 0;
  	try {
		$fbid = FbappBridge::$fbObj->getUser();
	} catch(FacebookApiException $e) {
	    //log some debug message
	}
	return $fbid;    
  }
  
  static function getFbLoginUrl() {
    return FbappBridge::$fbObj->getLoginUrl();
  }
  
  static function getFbmlLoginButton($permissions, $js_onlogin_function) {
  	return "<fb:login-button width='400' size='xlarge' scope='".$permissions."' onlogin='".$js_onlogin_function."'></fb:login-button>";
  }
}
