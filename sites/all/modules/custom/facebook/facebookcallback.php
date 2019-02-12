<?php
//callback function to get  return data

function facebook_callback($form_state = array()){
  $fb = new Facebook\Facebook([
  'app_id' => '1385211868366241', // Replace {app-id} with your app id
  'app_secret' => '46b6a3386c9dca617b94520807ffe007',
  'default_graph_version' => 'v2.2',
  ]);

  $helper = $fb->getRedirectLoginHelper();
  //print_r($helper);

  try {
    $accessToken = $helper->getAccessToken();
  } catch(Facebook\Exceptions\FacebookResponseException $e) {
    // When Graph returns an error
    echo 'Graph returned an error: ' . $e->getMessage();
    exit;
  } catch(Facebook\Exceptions\FacebookSDKException $e) {
    // When validation fails or other local issues
    echo 'Facebook SDK returned an error: ' . $e->getMessage();
    exit;
  }

  if (! isset($accessToken)) {
    if ($helper->getError()) {
     header('HTTP/1.0 401 Unauthorized');
     //echo "Error: " . $helper->getError() . "\n";
     //echo "Error Code: " . $helper->getErrorCode() . "\n";
     //echo "Error Reason: " . $helper->getErrorReason() . "\n";
     //echo "Error Description: " . $helper->getErrorDescription() . "\n";
     $msg = "Error occurred due to " . $helper->getErrorDescription() . ". Kindly authorize.";
     drupal_set_message($msg, $type='error');
     drupal_goto('');
    }else {
      header('HTTP/1.0 400 Bad Request');
      //echo 'Bad request';
      drupal_set_message("Request Failed to Facebook. Kindly try back after sometime.", 'error');
      drupal_goto('');
    }
    exit;
  }

  // Logged in
  //echo '<h3>Access Token</h3>';
  //var_dump($accessToken->getValue());

  // The OAuth 2.0 client handler helps us manage access tokens
  $oAuth2Client = $fb->getOAuth2Client();

  // Get the access token metadata from /debug_token
  $tokenMetadata = $oAuth2Client->debugToken($accessToken);
  //echo '<h3>Metadata</h3>';
  //var_dump($tokenMetadata);

  // Validation (these will throw FacebookSDKException's when they fail)
  $tokenMetadata->validateAppId('1385211868366241'); // Replace {app-id} with your app id
  // If you know the user ID this access token belongs to, you can validate it here
  //$tokenMetadata->validateUserId('123');
  $tokenMetadata->validateExpiration();

  if (! $accessToken->isLongLived()) {
    // Exchanges a short-lived access token for a long-lived one
    try {
      $accessToken = $oAuth2Client->getLongLivedAccessToken($accessToken);
    } catch (Facebook\Exceptions\FacebookSDKException $e) {
      drupal_goto('');
      echo "<p>Error getting long-lived access token: " . $helper->getMessage() . "</p>\n\n";
      exit;
    }

    //echo '<h3>Long-lived</h3>';
    //var_dump($accessToken->getValue());
  }

  $_SESSION['fb_access_token'] = (string) $accessToken;
  
  // User is logged in with a long-lived access token.
  // You can redirect them to a members-only page.
  //header('Location: https://example.com/members.php');

  try {
    // Returns a `Facebook\FacebookResponse` object
    $response = $fb->get('/me?fields=id,name,first_name,last_name,email', $accessToken);
  } catch(Facebook\Exceptions\FacebookResponseException $e) {
    drupal_goto('');
    echo 'Graph returned an error: ' . $e->getMessage();
    exit;
  } catch(Facebook\Exceptions\FacebookSDKException $e) {
    drupal_goto('');
    echo 'Facebook SDK returned an error: ' . $e->getMessage();
    exit;
  }

  $userData = $response->getGraphUser();

  //echo 'Name: ' . $userData['name'];
  //echo ' First Name: ' . $userData['first_name'] . ' Last Name: ' . $userData['last_name'];
  // OR
  // echo 'Name: ' . $user->getName();

  //Find whether to login or register
  //return $userData;

  $email = $userData['email'];
  if($_SESSION['action'] === 'login'){
    //To check whether that mail address already exists.
    $emailCheck = db_query("SELECT COUNT(u.mail) emailCheck FROM {users} u WHERE LOWER(u.mail) = LOWER(:mail)", array(':mail' => $email))->fetchField();
    if($emailCheck){
    	$uid = db_query("SELECT uid FROM {users} u WHERE LOWER(u.mail) = LOWER(:mail)", array(':mail' => $email))->fetchField();
      $activated = db_query("SELECT activated FROM {user_activation} ua WHERE ua.uid = :uid", array(':uid' => $uid))->fetchField();
      if($activated == 'Y'){
        $queryRole = db_select('users_roles', 'ur');
        $queryRole->join('role', 'r', 'r.rid = ur.rid'); 
        $queryRole->condition('ur.uid', $uid, '=');   
        $queryRole->fields('r', array('name'));
        $resultRole = $queryRole->execute();
        $role = '';
        if($recordRole = $resultRole->fetchAssoc()) {
         $role = $recordRole['name'];
        }
        
        	// User already registered facebook account to site, log them in
        	$form_state['uid'] = $uid;
        	mentoringcommon_login_submit($form, $form_state);
        	drupal_set_message('You have been successfully logged in.');
        
        
        if($role == 'mentor' || $role == 'mentor-professional' || $role == 'mentor-student') {
          drupal_goto('mentorprofile/' . $uid . '/edit');
        } else if($role == 'mentee' || $role == 'mentee-premium-3-months' || $role == 'mentee-premium-6-months'
          || $role == 'mentee-premium-9-months' ) {
          drupal_goto('menteeprofile/' . $uid . '/edit');
        }
      } else if($activated == 'N'){
        drupal_set_message("Your account is not activated. Kindly activate your account.");
        drupal_goto();
      }
    }
    else{
      //Redirect to home page as there is no account registered by the user
      drupal_set_message("Sorry there is no profile registered with your account. Kindly Register First with Facebook.");
      drupal_goto();
    }
  }
  else if($_SESSION['action'] === 'register'){
  	
  	try {
	   
	  // Returns a `Facebook\FacebookResponse` object
	  $response = $fb->get('/me?fields=id,name, email, first_name,last_name,gender, location, birthday', $accessToken);
	  $user = $response->getGraphUser();
    
	  //To check whether that mail address already exists.
    $emailCheck = db_query("SELECT COUNT(u.mail) emailCheck FROM {users} u WHERE LOWER(u.mail) = LOWER(:mail)", array(':mail' => $email))->fetchField();
    if($emailCheck){
      $uid = db_query("SELECT uid FROM {users} u WHERE LOWER(u.mail) = LOWER(:mail)", array(':mail' => $email))->fetchField();
      
      $queryRole = db_select('users_roles', 'ur');
      $queryRole->join('role', 'r', 'r.rid = ur.rid'); 
      $queryRole->condition('ur.uid', $uid, '=');   
      $queryRole->fields('r', array('name'));
      $resultRole = $queryRole->execute();
      $role = '';
      if($recordRole = $resultRole->fetchAssoc()) {
       $role = $recordRole['name'];
      }
      
      // User already registered facebook account to site, log them in
      $form_state['uid'] = $uid;
      mentoringcommon_login_submit($form, $form_state);
      drupal_set_message('You have been successfully logged in.');
      
      
      if($role == 'mentor' || $role == 'mentor-professional' || $role == 'mentor-student') {
        drupal_goto('mentorprofile/' . $uid . '/edit');
      } else if($role == 'mentee' || $role == 'mentee-premium-3-months' || $role == 'mentee-premium-6-months'
        || $role == 'mentee-premium-9-months' ) {
        drupal_goto('menteeprofile/' . $uid . '/edit');
      }
    }
    else{
      $form = drupal_retrieve_form('user_register_form', $form_state);
      

      $form['account']['name']['#value'] = empty($form_state['input']['name']) ? $user['name'] : $form_state['input']['name'];
      $form['account']['mail']['#parents'] = array('name');
      $form['account']['mail']['#value'] = $user['email'];
      $form['account']['mail']['#parents'] = array('mail');
      $form['account']['pass']['#type'] = 'hidden';
      $form['account']['pass']['#required'] = FALSE;
      $form['account']['registration_type']['#value'] = 'facebook';
      $form['account']['gender']['#value'] = $user['gender'];
      $form['account']['fname']['#value'] = $user['first_name'];
      $form['account']['lname']['#value'] = $user['last_name'];
      $user_type = lists_session("user_third_party_reg_type");
      if($user_type == 'mentor') {
        $form['account']['signup_type']['#value'] = '0';
      } else if ($user_type == 'mentee'){
        $form['account']['signup_type']['#value'] = '1';
      }
      
      
      $form_state['values']['name'] = $user['name'];
      $form_state['values']['mail'] = $user['email'];
      $form_state['values']['pass'] = user_password();
      $form_state['values']['status'] = 1;
      $form_state['values']['fb_visible'] = 1;
      $form_state['values']['fb_avatar'] = 1;
      
      $form_state['values']['registration_type'] = 'facebook';
      if($user['gender'] == 'male')
        $form_state['values']['gender'] = '0';
      else
        $form_state['values']['gender'] = '1';
      $form_state['values']['fname'] = $user['first_name'];
      $form_state['values']['lname'] = $user['last_name'];
      $user_type = lists_session("user_third_party_reg_type");
      //drupal_set_message('user type '. $user_type);
      if($user_type == 'mentor') {
        $form_state['values']['signup_type'] = '0';
      }
      else {
        $form_state['values']['signup_type'] = '1';
      }
       
      facebook_register_form_submit($form, $form_state);
    }
  }
  catch(Facebook\Exceptions\FacebookResponseException $e) {
    echo 'Graph returned an error: ' . $e->getMessage();
    exit;
  } catch(Facebook\Exceptions\FacebookSDKException $e) {
    echo 'Facebook SDK returned an error: ' . $e->getMessage();
    exit;
  }
	
	
	
	//echo 'Name: ' . $user['name'];
  }
}

function facebook_register_form_submit($form, &$form_state) {
	$user = mentoringcommon_sn_user_save($user, $form_state['values'], $form_state);
	//}
	//else {
	//	flog_it('else ----');
		//  $user = $form_state['user'];
		//}
		if (!$user) {
			drupal_set_message(t('Error saving user account.'), 'error');
			drupal_goto();
		}

		$data['data']['fb_avatar'] = isset($form_state['values']['fb_avatar']) ? $form_state['values']['fb_avatar'] : 0;
		$data['data']['fb_visible'] = $form_state['values']['fb_visible'];
		//$user = mentoringcommon_sn_user_save($user, $form_state['values'], $form_state);


		$form_state['uid'] = $user->uid;
		mentoringcommon_login_submit(array(), $form_state);

	}

