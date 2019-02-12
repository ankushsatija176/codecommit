<?php

function mentee_profile_form($form, &$form_state, $account, $category = 'account') {
  global $user;
  
  $query = db_select('mentee', 'm');   
	//$query->join('specialization_subcategory', 'ssc', 'ssc.scid = m.fos_id'); //JOIN node with users
	$query->condition('m.userid', $account->uid,'=');	   
	$query->fields('m');//SELECT the fields from user	
	   //->fields('ssc');
	$result = $query->execute();
	
	$mentee = array();
	if(	$record = $result->fetchAssoc()) {
		$mobile = $record['mobile'];
		//if(isset($record['mobile']))
		//	$mobile = decrypt($record['mobile'], ENCRYPTION_KEY);

		$skype_id = $record['skype_id'];
		//if(isset($record['skype_id']))
		//	$skype_id = decrypt($record['skype_id'], ENCRYPTION_KEY);
			
		$account->mid = $record['mid'];
    $account->parent_mail = $record['parent_mail'];
    $account->first_name = $record['first_name'];
    $account->last_name = $record['last_name'];
    $account->gender = $record['gender'];
    $account->zipcode = $record['zipcode'];
    $account->mobile = $mobile;
    $account->skype_id = $skype_id;
    $account->userid = $account->uid;
		$account->school_name = $record['school_name'];
		$account->state = $record['state'];
    $account->country = (strlen($record['country'])==0)?'USA':$record['country'];
		$account->city = $record['city'];
		$account->birthday = $record['birthday'];
		$account->birthmonth = $record['birthmonth'];
		$account->birthyear = $record['birthyear'];
		$account->yearOfSchool = $record['year_of_school'];
    $account->mentee_type = $record['mentee_type'];
    $account->college_name = $record['college_name'];
    $account->yearOfIntendedTransfer = $record['year_of_intended_transfer'];
		//$account->aom_id = $record['aom_id'];
		$account->fos_id = $record['fos_id'];
		//$account->fos_sub_id = $record['fos_sub_id'];
		$account->mentoring_request_title = $record['mentoring_request_title'];
		$account->mentoring_request = $record['mentoring_request'];
    $account->country_others = '';
    if($account->country != 'USA') {
    	$account->country_others = $record['country'];
    	$account->country = 'Others';
    }
		//$account->hobbies = $record['hobbies'];
	}
	
  $query = db_select('mentee_specialization', 'ms');
	$query->join('specialization_subcategory', 'ssc', 'ssc.scid = ms.spec_id'); //JOIN node with users 
	$query->condition('ms.mentee_id', $account->uid,'=');	   
	$query->fields('ms')//SELECT the fields from user	
	   ->fields('ssc');
	$result = $query->execute();	

  $fieldOfStudy = '';
  $fos_ids = array();
  $counterfos = 0;
  foreach ($result as $fos) {
	  $fieldOfStudy .= $fos->name . ', '; 
	  $fos_ids[$counterfos++] = $fos->spec_id; 
  }
  $account->fieldOfStudy = $fieldOfStudy;
  $account->fos_sub_id = $fos_ids;
  $query = db_select('mentee_aom', 'ma');
  	$query->join('area_mentoring', 'am', 'am.aid = ma.aom_id'); //JOIN node with users 
	$query->condition('ma.mentee_id', $account->uid,'=');	   
	$query->fields('ma')//SELECT the fields from user	
	   ->fields('am');
	$result = $query->execute();	
 	$areaOfMentoring = '';
  	$aom_ids = array();
 	$counteraoi = 0;
  foreach ($result as $aom) {
  	  $areaOfMentoring .= $aom->name . ', ';
  	  $aom_ids[$counteraoi++] =  $aom->aom_id ;
  }
  $account->aom = $areaOfMentoring;
  $account->aom_id = $aom_ids; 

  // During initial form build, add the entity to the form state for use during
  // form building and processing. During a rebuild, use what is in the form
  // state.
  if (!isset($form_state['user'])) {
    $form_state['user'] = $account;
  }
  else {
    $account = $form_state['user'];
  }

  // @todo Legacy support. Modules are encouraged to access the entity using
  //   $form_state. Remove in Drupal 8.
  $form['#user'] = $account;
  $form['#user_category'] = $category;

  if ($category == 'account') {
    mentee_edit_form($form, $form_state);
    // Attach field widgets.
    //$langcode = entity_language('user', $account);
    field_attach_form('user', $account, $form, $form_state, 'EN');
  }

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  if ($category == 'account') {
    $form['actions']['cancel'] = array(
      '#type' => 'submit',
      '#value' => t('Cancel account'),
      '#submit' => array('user_edit_cancel_submit'),
      '#access' => $account->uid > 1 && (($account->uid == $user->uid && user_access('cancel account')) || user_access('administer users')),
    );
  }

  $form['#validate'][] = 'mentee_profile_form_validate';
  // Add the final user profile form submit handler.
  $form['#submit'][] = 'mentee_profile_form_submit';

  return $form;
}

function mentee_profile_form_validate($form, &$form_state) {
  
  //$country_value;
	//$country_key = $form_state['values']['country'];
	//if($country_key == "Others")
	//	$country_value = $form_state['values']['country_others'];
	//else
	//	$country_value = $form['account']['country']['#options'][$country_key];

  //To get user id of the currently logged in user
  global $user;
  $query = db_select('users','u');
  $query->condition('u.uid',$user->uid,'=');
  $query->addField('u', 'mail');
  $result = $query->execute();
  foreach ($result as $record) {
    $email = $record->mail;
  }
  $parentmail = $form_state['values']['parent_mail'];
  if($parentmail == 'Parent E-mail Address *' || !isset($parentmail) || empty($parentmail)){
      form_set_error('parent_mail', t('Please provide a valid Parent E-mail ID.'));
  } else if(!valid_email_address($parentmail)){
    form_set_error('parent_mail', t('Please provide a valid Parent E-mail ID.'));
  } else if($parentmail == $email){
    form_set_error('parent_mail', t('Parent Mail Address cannot be the same as Mentee Mail Address'));
  }

  $mentee_type = $form_state['values']['mentee_type'];
  //For HighSchool students
  if($mentee_type == 'highschool'){
    if($form_state['values']['school_name'] == 'School Name *') {
      form_set_error('school_name', t('School name is required'));
    }
    if(isset($form_state['values']['yearOfSchool'])){
      $birthDate = $form_state['values']['bday'];
      $birthyear = $birthDate['year'];
      $year_of_school_value = 2014 + $form_state['values']['yearOfSchool'];
      if($year_of_school_value <= $birthyear)
        form_set_error('yearOfSchool', t('Graduation year cannot be earlier than birthdate'));
    }
  } else if($mentee_type == 'transfer'){//For Transfer students
    if($form_state['values']['college_name'] == 'Current College Name *' || empty($form_state['values']['college_name'])) {
      form_set_error('college_name', t('College name is required'));
    }
    if(isset($form_state['values']['yearOfIntendedTransfer'])){
      $birthDate = $form_state['values']['bday'];
      $birthyear = $birthDate['year'];
      $year_of_college_value = 2014 + $form_state['values']['yearOfIntendedTransfer'];
      if($year_of_college_value <= $birthyear)
        form_set_error('yearOfIntendedTransfer', t('Intended Transfer year cannot be earlier than birthdate'));
    } else{
      form_set_error('yearOfIntendedTransfer', t('Intended Year of Transfer is required'));
    }
  }
  // element_validate_number($form['account']['zcode'], $form_state);
  $zip_code = $form_state['values']['zipcode'];
  $phone = $form_state['values']['mobile'];
	
	$country_value = $form_state['values']['country'];
    if($country_value !== 'Country *') {
	  //$form_state['values']['country'] = $country_value;
	  
	  if($form_state['values']['country'] == 'Others') {
	  		$country_others = $form_state['values']['country_others'];
	  		if(!isset($country_others) || empty($country_others) || $country_others == 'Please specify country ') {
	  			form_set_error('country_others', t('Country field is required.'));
	  			$form_state['values']['country'] = NULL;
	  		} else
				$form_state['values']['country'] = $country_others;

			$state_others = $form_state['values']['state'];
			if($state_others == NULL || $state_others == '' || $state_others == 'State ') {
				form_set_error('state_others', t('State field is required.'));
				$form_state['values']['state'] = NULL;
			}			
			$form_state['values']['state'] = $state_others;
			
			$city_others = $form_state['values']['city'];
			if(!isset($city_others) || empty($city_others) || $city_others == 'City ') {
				form_set_error('city_others', t('City field is required.'));
				$form_state['values']['city'] = NULL;
			}	
			$form_state['values']['city'] = $city_others;
      //Mobile Number Validation when Country is Others
      if($phone != 'Mobile ' && $phone != NULL) {
        if(!(preg_match('/^\d{10}$/',$phone))){
          //element_validate_number($form['account']['mobile'], $form_state);
          form_set_error('mobile',t('Mobile number must be in the format xxxxxxnnnn'));
        }
      }
      //Zipcode validation when Country is Others
      if($zip_code == 'Zip code *'){    
        form_set_error('zcode',t('Zip code is required'));    
      }else if(strlen($zip_code) != 6 && !preg_match('/^\d{6}$/', $zip_code))  {    
        form_set_error('zcode', t('Zip code should be in nnnnnn format'));    
      }

		} else if($form_state['values']['country'] == 'USA'){
			$form_state['values']['country'] = $form_state['values']['country'];
			$key = $form_state['values']['stateUSA'];
			$state = $form['account']['stateUSA']['#options'][$key];
			if($state =='State *') {
				form_set_error('state', t('State field is required.'));
				$form_state['values']['state'] == NULL;	
			} else{
        $form_state['values']['state'] = $state;
      }
				
			$key = $form_state['values']['cityUSA'];
			$city = $form['account']['cityUSA']['#options'][$key];
			if($city == 'City *') {
				form_set_error('city', t('City field is required.'));
				$form_state['values']['city'] = NULL;	
			} else{	
				$form_state['values']['city'] = $city;
      }
      //Mobile Number Validation when Country is USA
      if($phone != 'Mobile ' && $phone != NULL) {
        if(!(preg_match('/\s{0,1}\(\d{3}\)(\s{0,1})\d{3}\-\d{4}$/',$phone))){
          //element_validate_number($form['account']['mobile'], $form_state);
          form_set_error('mobile',t('Mobile number must be in the format (xxx)xxx-nnnn'));
        }
      }
      //Zipcode validation when Country is USA
      if($zip_code == 'Zip code *'){    
        form_set_error('zcode',t('Zip code is required'));    
      }else if(strlen($zip_code) != 5 && !preg_match('/^[0-9]{5}$/', $zip_code))  {   
        form_set_error('zcode', t('Zip code should be in nnnnn format'));   
      }
		}
	} else {
		form_set_error('country', t('Country field is required.'));
		$form_state['values']['country'] == NULL;
		$form_state['values']['state'] == NULL;
		$form_state['values']['city'] == NULL;
	}
  if(isset($form_state['values']['areaofmentoring'])) {
    $selected_aom = array_filter($form_state['values']['areaofmentoring']);
    if(count($selected_aom) < 1){
      form_set_error('areaofmentoring',t('Area of Interest for Mentoring is required'));
    }
  }
  if($form_state['values']['areaofmentoring'][1] == 1){
    $areaOfSpecializationCount = array_filter($form_state['values']['fieldOfSpecialization']);
    //drupal_set_message('<pre>'.print_r($form_state['values'],true).'</pre>');
    if($form_state['values']['fieldOfStudy'] != 9 && $form_state['values']['fieldOfStudy'] != 10){
      if(empty($areaOfSpecializationCount)){
        form_set_error('fieldOfSpecialization', t('Field of Specialization field is required.'));
      }
    }
    if(count($areaOfSpecializationCount) > 3){
      form_set_error('fieldOfSpecialization', t('More than three Fields of Specialization cannot be selected.'));
    }
  }
}


/**
 * Returns form render array.
 */
function mentee_edit_form(&$form, &$form_state) {

   global $user;
   $account = $form['#user'];
   $register = ($form['#user']->uid > 0 ? FALSE : TRUE);

	// Account information.
  $form['account'] = array(
    '#type'   => 'container',
    '#weight' => -10,
  	'#theme' => 'mentee_edit_theme_form',
  );

  $form['account']['parent_mail'] = array(
    '#type' => 'textfield',
    '#title' => t('Parent E-mail address'),
    '#maxlength' => EMAIL_MAX_LENGTH,
    '#description' => t('A valid e-mail address. All e-mails from the system will be sent to this address. The e-mail address is not made public and will only be used if you wish to receive a new password or wish to receive certain news or notifications by e-mail.'),
    '#required' => TRUE,
    '#default_value' => (!$register ? $account->parent_mail : ''),
    '#size' => 20,
  );
  
   $form['account']['first_name'] = array(
    '#type' => 'textfield',
    '#title' => t('First Name'),
    '#maxlength' => 255,
    //'#description' => t('First name of the user.'),
    '#required' => TRUE,
    '#default_value' => (!$register ? $account->first_name : ''),
   	'#size' => 20,
   	//'#name' => 'First Name',
    //'#attributes' => array('class' => array('username')),
    //'#access' => ($register || ($user->uid == $account->uid && user_access('change own username')) || $admin),
    //'#weight' => -10,
   		'#attributes' => array(
   				'title' => t('First name of the user.'),
   		)
  );
  
  $form['account']['last_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Last name'),
    '#maxlength' => 255,
    //'#description' => t('Last name of the user.'),
    '#required' => FALSE,
    //'#attributes' => array('class' => array('username')),
    '#default_value' => (!$register ? $account->last_name : ''),
  	'#size' => 20,
  	//'#name' => 'Last Name',
    //'#access' => ($register || ($user->uid == $account->uid && user_access('change own username')) || $admin),
    //'#weight' => -10,
  );
  
  $form['account']['bday'] = array(
    '#type' => 'date',
    '#title' => t('Date of birth'),
    //'#description' => t('Birth day of the user.'),
    '#default_value' => array(
      'day' => (!$register ? $account->birthday : ''),
      'month' => (!$register ? $account->birthmonth : ''),
      'year' => (!$register ? $account->birthyear : ''),
    ),
    '#required' => TRUE,
  	'#after_build' => array("format_dob"),
  );
  
  $form['account']['gender'] = array(
    '#title' => t('Gender'),
    '#type' => 'select',
    //'#description' => 'Select the gender.',
    '#default_value' => (!$register ? $account->gender : ''),
    '#required' => TRUE,
    '#options' => array(t('M'), t('F')),
  	'#empty_option' => '--Gender--',
  );
  
  $form['account']['zipcode'] = array(
    '#type' => 'textfield',
    '#title' => t('Zip code'),
    //'#description' => t('Zip code of the user.'),
    '#default_value' => (!$register ? $account->zipcode : ''),
    '#required' => TRUE,
  	'#size' => 20,
  	//'#name' => 'Zip code',
  );
  
  $form['account']['mobile'] = array(
    '#type' => 'textfield',
    '#title' => t('Mobile'),
    '#required' => FALSE,
    '#default_value' => (!$register ? $account->mobile : ''),
  	'#size' => 20,
  	//'#name' => 'Mobile',
  );
  
  $form['account']['skype_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Skype Id'),
    '#default_value' => (!$register ? $account->skype_id : ''),
  	'#size' => 20,
  	//'#name' => 'Skype Id',
  );
 
 /* $form['educational_info']['educationalInformation'] = array(
    '#type' => 'fieldset',
    '#title' => t('Education Information'),
  );
  */

  $form['account']['mentee_type'] = array(
    '#type' => 'radios',
    '#required' => TRUE,
    '#options' => array(
      'highschool' => t('HighSchool Student'),
      'transfer' => t('Transfer Student'),
    ),
    '#default_value' =>  (!$register ? (isset($account->mentee_type) ? $account->mentee_type : 'highschool') : 'highschool'),
    '#title' => t('Student Type'),
  );

  $form['account']['highschool'] = array(
    '#type' => 'fieldset',
    '#title' => t('High School Information'),
    '#states' => array(
      'visible' => array(
        ':input[name="mentee_type"]' => array('value' => 'highschool'),
      ),
    ),
  );

  $form['account']['highschool']['school_name'] = array(
    '#type' => 'textfield',
    '#title' => t('School Name'),
    '#maxlength' => 255,
    //'#description' => t('Name of your school'),
    //'#required' => TRUE,
    '#default_value' => isset($account->school_name) ? $account->school_name : NULL,
    '#size' => 20,
    //'#name' => 'School Name',
    '#states' => array(
      'visible' => array(
        ':input[name="mentee_type"]' => array('value' => 'highschool'),
      ),
    ),
    '#attributes' => array(
      'title' => t("Example - Saint Francis High School"),
    ),
  );
  $form['account']['highschool']['yearOfSchool'] = array(
    '#type' => 'select',
    '#title' => t('Year of High School graduation'),
    //'#description' => t('Year when School attended.'),
    //'#required' => TRUE,
    '#options' => drupal_map_assoc(array(t(date('Y', time())), t(date('Y', strtotime('+1 year'))), t(date('Y', strtotime('+2 years'))), t(date('Y', strtotime('+3 years'))), t(date('Y', strtotime('+4 years'))))),
    '#default_value' => isset($account->yearOfSchool) ? $account->yearOfSchool : NULL,
    '#empty_option' => '-------',
    '#states' => array(
      'visible' => array(
        ':input[name="mentee_type"]' => array('value' => 'highschool'),
      ),
    ),
  );

  $form['account']['transfer'] = array(
    '#type' => 'fieldset',
    '#title' => t('Transfer College Information'),
    '#states' => array(
      'visible' => array(
        ':input[name="mentee_type"]' => array('value' => 'transfer'),
      ),
    ),
  );

  $form['account']['transfer']['college_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Current College Name'),
    '#maxlength' => 255,
    //'#description' => t('Name of your college'),
    //'#required' => TRUE,
    '#default_value' => isset($account->college_name) ? $account->college_name : NULL,
    '#size' => 20,
    '#states' => array(
      'visible' => array(
        ':input[name="mentee_type"]' => array('value' => 'transfer'),
      ),
    ),
    '#attributes' => array(
      'title' => t("Example - Berkeley City College"),
    ),
  );
  $form['account']['transfer']['yearOfIntendedTransfer'] = array(
    '#type' => 'select',
    '#title' => t('Year of Intended Transfer'),
    //'#description' => t('Year when School attended.'),
    //'#required' => TRUE,
    '#options' => drupal_map_assoc(array(t(date('Y', time())), t(date('Y', strtotime('+1 year'))), t(date('Y', strtotime('+2 years'))), t(date('Y', strtotime('+3 years'))), t(date('Y', strtotime('+4 years'))))),
    '#default_value' => isset($account->yearOfIntendedTransfer) ? $account->yearOfIntendedTransfer : NULL,
    '#empty_option' => '-------',
    '#states' => array(
      'visible' => array(
        ':input[name="mentee_type"]' => array('value' => 'transfer'),
      ),
    ),
  );
  
 $form['account']['country'] = array(
    '#type' => 'select',
    '#title' => t('Country'),
    //'#maxlength' => 255,
    '#required' => TRUE,
    '#empty_option' => 'Country *',
  	'#options' => array(
	 				'USA' => t('USA'),
	 				'Others' => t('Others'),
	 		),
  	'#default_value' => isset($account->country) ? $account->country : NULL,
  );
  
  $form['account']['country_others'] = array(
    '#type' => 'textfield',
    '#title' => t('Please specify country'),
    '#maxlength' => 255,
    '#required' => FALSE,
  	'#size' => '20',
  	'#visible' => false,
  	'#states' => array(
  			'visible' => array(
  					':input[name="country"]' => array('value' => 'Others'),
  			),
  	),
  	'#default_value' => isset($account->country_others) ? $account->country_others : NULL,
  );
  
  $form['account']['state'] = array(
  		'#type' => 'textfield',
  		'#title' => t('State'),
  		'#required' => FALSE,
  		//'#autocomplete_path' => 'states/autocomplete',
  		//'#name' => 'State',
  		'#size' => '20',
  		'#states' => array(
  				'visible' => array(
  						':input[name="country"]' => array('value' => 'Others'),
  				),
  		),
  		'#default_value' => isset($account->state) ? $account->state : NULL,
  );
	$stateDefault = get_states_for_country('1');
  
  $value_state_usa = isset($form_state['values']['stateUSA']) ? $form_state['values']['stateUSA'] : NULL;
  if(isset($account->state) && $value_state_usa == NULL){
  	$value_state_usa = array_search($account->state, $stateDefault);
  }
  $form['account']['stateUSA'] = array(
  		'#type' => 'select',
  		'#title' => t('State'),
  		'#required' => FALSE,
  		'#empty_option' => 'State *',
  		//'#autocomplete_path' => 'states/autocomplete',
  		//'#name' => 'State',
  		//'#size' => '20',
  		'#ajax' => array('event' => 'change',
  				'callback' => 'state_ajax_callback',
  				'progress' => array(
  						'message' => '',
						'type' => 'throbber',
  				),
  				'wrapper' => 'dropdown_city_replace_1',
  		),
  		'#options' =>$stateDefault,
  		'#states' => array(
  				'visible' => array(
  						':input[name="country"]' => array('value' => 'USA'),
  				),
  		),
  		'#default_value' => $value_state_usa,
  );
  
  $form['account']['city'] = array(
  		'#type' => 'textfield',
  		'#title' => t('City'),
  		'#required' => FALSE,
  		//'#autocomplete_path' => 'cities/autocomplete',
  		//'#name' => 'City',
  		'#size' => '20',
  		'#states' => array(
  				'visible' => array(
  						':input[name="country"]' => array('value' => 'Others'),
  				),
  		),
  		'#default_value' => isset($account->city) ? $account->city : NULL,
  );
  $cityValues = get_city_for_state($value_state_usa);
  $form['account']['cityUSA'] = array(
  		'#type' => 'select',
  		//'#title' => t('City'),
  		'#required' => FALSE,
  		'#empty_option' => 'City *',
  		//'#autocomplete_path' => 'cities/autocomplete',
  		//'#name' => 'City',
  		//'#size' => '20',
      //'#validated' => TRUE,
  		'#prefix' => '<div id="dropdown_city_replace_1">',
  		'#suffix' => '</div>',
  		'#options' =>$cityValues,
  		/*'#options' => array(
  		 '1' => t('santa ana'),
  				'2' => t('Santa Ana'),
  		),*/
  		'#states' => array(
  				'visible' => array(
  						':input[name="country"]' => array('value' => 'USA'),
  				),
  		),
  		'#default_value' => isset($account->city) ? array_search($account->city, $cityValues) : NULL,
  );
  
  /*
  $form['account']['details'] = array(
    '#type' => 'fieldset',
    '#title' => t('Mentorship request'),
  );*/
  
  $entries = db_query("SELECT aid, name FROM {area_mentoring}");

  $options = array();
  foreach($entries as $record)
  {
    $options[$record->aid] =$record->name;
  }
  $form['account']['areaofmentoring'] = array(
    '#title' => t('Area want mentoring in'),
    '#type' => 'checkboxes',
    //'#description' => 'Select the area you want to be mentored',
    '#required' => TRUE,
    '#options' =>  $options ,
    '#default_value' => isset($account->aom_id) ? $account->aom_id : NULL,
   	//'#default_value' => array(1,2),
  );
  
  $entries = db_query("SELECT cid, name FROM {specialization_category}");

  $options = array();
  foreach($entries as $record)
  {
    $options[$record->cid] =$record->name;
  } 
  
	$value_field_of_study = $account->fos_id;
  //$value_field_of_study = isset($account->fos_id) ? $account->fos_id : key($options);
  
  $form['account']['fieldOfStudy'] = array(
    '#type' => 'select',
    '#title' => t('Field of Study'),
    //'#description' => t('Field of study.'),
    '#required' => FALSE,
    '#options' => $options,
    '#default_value' => isset($account->fos_id) ? $account->fos_id : key($options),
    '#ajax' => array(
    'event' => 'change',
        'callback' => 'mentee_edit_ajax_callback',
        'progress' => array(
        'message' => '',
		'type' => 'throbber',
      ),
        'wrapper' => 'mentee_edit_dropdown_specialization_replace',
      ),
      '#states' => array(
      'visible' => array(
        ':input[name="areaofmentoring"]' => array('value' => '1'),
      ),
    ),
  );

  $spec_options = isset($form_state['values']['fieldOfStudy']) ? $form_state['values']['fieldOfStudy'] : $value_field_of_study;
  
   $form['account']['fieldOfSpecialization'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Field of Specialization'),
    //'#description' => t('Field of study you want to specialize in.'),
    '#required' => FALSE,
    '#prefix' => '<div id="mentee_edit_dropdown_specialization_replace">',
    '#suffix' => '</div>',
    '#options' => mentee_edit_specialization_dropdown_options(isset($spec_options) ? $spec_options : 1),
    '#default_value' => isset($account->fos_sub_id) ? $account->fos_sub_id : '',
    //'#value' => isset($account->fos_sub_id) ? $account->fos_sub_id : '',
    //'#default_value' => isset($form_state['values']['fieldOfSpecialization']) ? $form_state['values']['fieldOfSpecialization'] : '',
    '#states' => array(
      'visible' => array(
        ':input[name="areaofmentoring"]' => array('value' => '1'),
      ),
    ),
  );
    
  $form['account']['mentoring_request'] = array(
    '#type' => 'textarea',
    '#title' => t('About me'),
    //'#description' => t('Your mentoring request'),
    '#default_value' => isset($account->mentoring_request) ? $account->mentoring_request : NULL,
  	//'#name' => 'About me',
  ); 
  
  /*$form['account']['pic'] = array(
  	'#type' => 'managed_file',
  	//'#title' => t('Upload an image'),
  	//'#description' => t('Allowed extensions: gif png jpg jpeg'),
  	'#upload_validators' => array(
    	'file_validate_extensions' => array('gif png jpg jpeg'),
    	// Pass the maximum file size in bytes
    	'file_validate_size' => array(1 * 1024 * 1024),
  	),
  	'#theme' => 'mentor_thumb_upload',
  	'#upload_location' => 'public://pictures/',
  );*/

  //$form['submit'] = array(
  //  '#type' => 'submit',
  //  '#value' => 'Register',
  //);
  //$form['#submit'][] = 'mentor_profile_form_submit';
  return $form;
}

function mentee_edit_ajax_callback($form, $form_state) {
    return $form['account']['fieldOfSpecialization'];
}

function mentee_edit_specialization_dropdown_options($key = '') {
  if($key){
    $entries = db_query("SELECT scid, name FROM {specialization_subcategory} WHERE specialization_category_id = $key");

    $options = array();
    foreach($entries as $record)
    {
      $options[$record->scid] =$record->name;
    }
    return $options;
  }
}


function mentee_profile_form_submit($form, &$form_state) {
	
	$selected_aom = array_filter($form_state['values']['areaofmentoring']);
	$selected_spec = array_filter($form_state['values']['fieldOfSpecialization']);
	//entity_form_submit_build_entity('user', $account, $form, $form_state);
	$mentoring_area = '';
	if(! empty($selected_aom)) {
		$query = "SELECT name FROM {area_mentoring} WHERE aid = ";
		$max = count($selected_aom);
		foreach($selected_aom as $key => $value) {
			$query .= $key;
			if($max > 1) {
				$query .= " or aid = ";
				$max = $max - 1;
			}
				
		}
		$entries = db_query($query);
	}
	foreach($entries as $record) {
		$mentoring_area .= $record->name . ', ';
	
	}
	
	$mentoring_area = substr($mentoring_area, 0, (strlen($mentoring_area) - 2));
	$specialization = NULL;
	$entries = '';
	$fos = NULL;
	if(!empty($selected_aom) && isset($selected_aom[1]) && $selected_aom[1] == 1){
		$fos = $form_state['values']['fieldOfStudy'];
		if(! empty($selected_spec)) {
			$query = "SELECT name FROM {specialization_subcategory} WHERE scid = ";
			$max = count($selected_spec);
			foreach($selected_spec as $key => $value) {
				$query .= $key;
				if($max > 1) {
					$query .= " or scid = ";
					$max = $max - 1;
				}
			}
			$entries = db_query($query);
		} else {
			$entries = db_query("SELECT name FROM {specialization_subcategory} WHERE specialization_category_id = " . $fos);
		}
		foreach($entries as $record) {
			$specialization .= $record->name . ', ';
		}
		$specialization = substr($specialization, 0, (strlen($specialization) - 2));
	}
  $school = ($form_state['values']['school_name'] == "School Name *") ? NULL : $form_state['values']['school_name'];
  $college = ($form_state['values']['college_name'] == "Current College Name *") ? NULL : $form_state['values']['college_name'];
  $mentee_type = $form_state['values']['mentee_type'];
  $city = ($form_state['values']['city']== "City ") ? NULL : $form_state['values']['city'];
  $state = ($form_state['values']['state'] == "State ") ? NULL : $form_state['values']['state'];
  $parent_mail = (empty($form_state['values']['parent_mail']))? NULL : $form_state['values']['parent_mail'];
  $firstname = ($form_state['values']['first_name'] == "First Name *") ? NULL : $form_state['values']['first_name'];
  $lastname = ($form_state['values']['last_name'] == "Last Name *") ? NULL : $form_state['values']['last_name'];
  $zipcode = ($form_state['values']['zipcode'] == "Zip code *")? NULL :$form_state['values']['zipcode'];
  $mobile = ($form_state['values']['mobile'] == "Mobile ")? NULL :$form_state['values']['mobile'];
  $skypeid = ($form_state['values']['skype_id'] == "Skype Id")? NULL :$form_state['values']['skype_id'];
  $aboutme = ($form_state['values']['mentoring_request'] == "About Me")? NULL :$form_state['values']['mentoring_request'];
  $year_of_school = (empty($form_state['values']['yearOfSchool'])? NULL : $form_state['values']['yearOfSchool']);
  $year_of_intended_transfer = (empty($form_state['values']['yearOfIntendedTransfer'])? NULL : $form_state['values']['yearOfIntendedTransfer']);
  $account = $form['#user'];
  //$year_of_school_key = $form_state['values']['yearOfSchool'];
  //$year_of_school_value = $form['account']['yearOfSchool']['#options'][$year_of_school_key];
  $birthDate = $form_state['values']['bday'];
  $account->mid = $form['#user']->mid;
  $account->parent_mail = $parent_mail;
  $account->first_name = $firstname;
  $account->last_name = $lastname;
  $account->birthday = $birthDate['day'];
  $account->birthmonth = $birthDate['month'];
  $account->birthyear = $birthDate['year'];
  $account->gender = $form_state['values']['gender'];
  $account->zipcode = $zipcode;
  $account->mobile = $mobile;
  $account->skype_id = $skypeid;
  $account->userid = $account->uid;
  $account->mentee_type = $mentee_type;
  $account->school_name = $school;
  $account->college_name = $college;
  $account->country = $form_state['values']['country'];
  $account->state = $state;
  $account->city = $city;
  $account->year_of_school = $year_of_school;
  $account->year_of_intended_transfer = $year_of_intended_transfer;
  $account->area_of_mentoring = $mentoring_area;
  $account->fos_id = $fos;
  $account->specialization = $specialization;
  //$account->mentoring_request_title = $form_state['values']['req_title'];
  $account->mentoring_request = $aboutme;
  //$account->hobbies = $form_state['values']['hobby'];
    
	$success = db_update('mentee') // Table name no longer needs {}
	->fields(array(
		'mid' => $form['#user']->mid,
    'parent_mail' => $parent_mail,
		'first_name' => $firstname,
		'last_name' => $lastname,
		'birthday' => $birthDate['day'],
		'birthmonth' => $birthDate['month'],
		'birthyear' => $birthDate['year'],
		'gender' => $form_state['values']['gender'],
		'zipcode' => $zipcode,
		'mobile' => $mobile,
		'skype_id' => $skypeid,
		'userid' => $account->uid,
		'school_name' => $school,
		'country' => $form_state['values']['country'],
		'state' => $state,
		'city' => $city,
		'year_of_school' => $year_of_school,
    'mentee_type' => $mentee_type,
    'college_name' => $college,
    'year_of_intended_transfer' => $year_of_intended_transfer,
		//'aom_id' => $mentorship_details['areaofmentoring'],
		'fos_id' => $fos,
		//'fos_sub_id' => $mentorship_details['fieldOfSpecialization'],
		//'mentoring_request_title' => $mentorship_details['req_title'],
		'mentoring_request' => $aboutme,
		//'hobbies' => $mentorship_details['hobby'],
		'specialization' => $specialization,
		'area_of_mentoring' => $mentoring_area,
		))
	->condition('mid', $form['#user']->mid, '=')
	->execute();
	
	
    //$success = drupal_write_record('mentee', $account, 'mid');
      if ($success === FALSE) {
        // The query failed - better to abort the save than risk further
        // data loss.
        return FALSE;
      }

    $uid = $_SESSION['user']->uid;
    db_delete('mentee_aom')
	  ->condition('mentee_id', $uid)
	  ->execute();
	  
	db_delete('mentee_specialization')
	  ->condition('mentee_id', $uid)
	  ->execute();
      
    foreach($selected_aom as $key => $value) {
		db_insert('mentee_aom')
			->fields(array(
				'mentee_id' => $uid,
				'aom_id' => $key,
		))
		->execute();			
	}
				
	foreach($selected_spec as $key => $value) {
		db_insert('mentee_specialization')
			->fields(array(
				'mentee_id' => $uid,
				'spec_id' => $key,
		))
		->execute();			
	}
	
	$query = db_select('users', 'u'); 
		$query->condition('u.uid', $uid, '=');
		$query->fields('u', array('picture'));
		$result = $query->execute();
		$picture = 0;
		if(	$record = $result->fetchAssoc()) {
			//drupal_set_message('<pre>'.print_r($record,true).'</pre>');
			$picture = $record['picture'];
		}
		
		$account = array();
		$account['uid'] = $uid;
		//$account['status'] = 1;
		if($picture == 0) {
			if($form_state['values']['gender'] == 0) {
				$account['picture'] = 46;
			} else {
				$account['picture'] = 44;
			}
		}
		$success = drupal_write_record('users', $account, 'uid');
  
  //Creating dummy parent account for mentee's signing up using LinkedIn/Facebook
  $registration_type = db_query("SELECT registration_type FROM {user_activation} ua WHERE ua.uid = :uid", array(':uid' => $uid))->fetchField();
  $first_login = db_query("SELECT first_login FROM {user_activation} ua WHERE ua.uid = :uid", array(':uid' => $uid))->fetchField();

  if(($registration_type == 'facebook' || $registration_type == 'linkedin') && $first_login == 11){
    $parent_account = new stdClass();

    if (!empty($edit['pass'])) {
      // Allow alternate password hashing schemes.
      require_once DRUPAL_ROOT . '/' . variable_get('password_inc', 'includes/password.inc');
      $edit['pass'] = user_hash_password(trim($edit['pass']));
      // Abort if the hashing failed and returned FALSE.
      if (!$edit['pass']) {
        return FALSE;
      }
    }
    else {
      // Avoid overwriting an existing password with a blank password.
      unset($edit['pass']);
    }
    if (isset($edit['mail'])) {
      $edit['mail'] = trim($edit['mail']);
    }

    foreach ($edit as $key => $value) {
      $parent_account->$key = $value;
    }
    if(!isset($parent_account->created)) {
      $parent_account->uid = db_next_id(db_query('SELECT MAX(uid) FROM {users}')->fetchField());
      //$account->pid = $parent_account->uid;
      $parent_account->mail = $parent_mail;
      $emailCheckParent = db_query("SELECT COUNT(u.mail) emailCheckParent FROM {users} u WHERE LOWER(u.mail) = LOWER(:mail)", array(':mail' => $parent_account->mail))->fetchField();
      if(!$emailCheckParent){
        if(!empty($parent_account->mail) && isset($parent_account->mail)){
          $parent_account->status = 1;
          $parent_account->name = $parent_mail;
          $parent_account->created = REQUEST_TIME;
          drupal_write_record('users', $parent_account);
          $query = db_insert('users_roles')->fields(array('uid'=>$parent_account->uid, 'rid'=>'11'))->execute();
        }
      }
    }
    db_update('user_activation')
      ->fields(array('first_login' => 0))
      ->condition('uid' , $uid , '=')
      ->execute();
  }
  // Clear the page cache because pages can contain usernames and/or profile information:
  cache_clear_all();

  drupal_set_message(t('The changes have been saved.'));
}


function theme_mentee_edit_theme_form($variables) {
	
	//var_dump($variables['form']);
		$output = '<div class="mentee-profile-form-heading1	"><div class="mentee-profile-form-heading2">
			View/Edit Profile</div></div>';
	
	$form = $variables['form'];
	$basic_1 = '<div class="mentee-profile-form-heading3">';
	$basic_2 = '<div class="mentee-profile-form-heading3">';
	$basic_3 = '<div class="mentee-profile-form-heading3">';
	$basic_4 = '<div class="mentee-profile-form-heading3">';
	$basic_5 = '<div class="mentee-profile-form-heading3">';
	$basic_6 = '<div class="mentee-profile-form-heading3">';
	$educational = '<div class="mentee-profile-form-heading3">';
	$educational1 = '<div class="mentee-profile-form-heading3">';
	$areaNeedingMentoringIn1 = '<div class="mentee-profile-form-heading3">';
	$areaNeedingMentoringIn2 = '<div class="mentee-profile-form-heading3">';
	//var_dump($form);
	foreach ($form as $key => $element) {
		$allowed_elements = array('textfield', 'textarea', 'radio', 'radios', 'checkbox', 'checkboxes', 'markup', 'submit', 'file', 'fieldset', 'item', 'date', 'select', 'hidden');
		$basic_elements1 = array('name',  'mail');
		$basic_elements2 = array('pass');
		$basic_elements3 = array('first_name', 'last_name', 'gender');
		$basic_elements4 = array('bday');
		$basic_elements5 = array('parent_mail','zipcode', 'mobile', 'skype_id');
		$basic_elements6 = array('pic');
		$anmi_elements1 = array('areaofmentoring', 'fieldOfStudy', 'fieldOfSpecialization','degree');
		$anmi_elements2 = array('mentoring_request');
		$educational_elements = array('mentee_type');
    $educational_elements1 = array('country','country_others','state', 'stateUSA', 'city', 'cityUSA');
    $educational_elements2 = array('highschool', 'transfer');
		
		if (is_array($form[$key]) && isset($element['#type']) ) {
			if(in_array($key, $basic_elements1)){
				$basic_1 .= '<div class="container-inline">';
				$basic_1 .= '<div class="mentee-profile-form-element1">&nbsp;';
				$basic_1 .= drupal_render($element);
				$basic_1 .= '</div>';
				$basic_1 .= '</div>';

			}
			if(in_array($key, $basic_elements2)){
				//$basic_2 .= '<div style="float: left; " class="container-inline">';
				//$basic_2 .= '<div style="float: left; width: 100%;">&nbsp;';
				$basic_2 .= drupal_render($element);
				//$basic_2 .= '</div>';
				//$basic_2 .= '</div>';
					
			}
			if(in_array($key, $basic_elements3)){
				$basic_3 .= '<div class="mentee-profile-form-element1 " style="display: inline-block !important; margin-left: 1%;"><div class="mentee-profile-form-element3">'.$element['#title'].'</div>';
				$basic_3 .= '<div class="mentee-profile-form-element1 mentee-profile-form-element2" >';
				$basic_3 .= drupal_render($element);
				$basic_3 .= '</div>';
				$basic_3 .= '</div>';
					
			}if(in_array($key, $basic_elements4)){
				$basic_4 .= '<div class="mentee-profile-form-element3">Date Of Birth</div><div  class=" mentee-profile-form-element1 container-inline">';
				$basic_4 .= '<div class="mentee-profile-form-element1 mentee-profile-form-element2">&nbsp;';
				$basic_4 .= drupal_render($element);
				$basic_4 .= '</div>';
				$basic_4 .= '</div>';

			}if(in_array($key, $basic_elements5)){
				$basic_5 .= '<div class="mentee-profile-form-element1 " style="display: inline-block !important; margin-left: 1%;"><div class="mentee-profile-form-element3">'.$element['#title'].'</div>';
				$basic_5 .= '<div class="mentee-profile-form-element1 mentee-profile-form-element2">';
				$basic_5 .= drupal_render($element);
				$basic_5 .= '</div>';
				$basic_5 .= '</div>';

			}
      if(in_array($key, $basic_elements6)){
				$basic_6 .= '<div class="mentee-profile-form-element3">Upload an Image</div>
						<div class="mentee-profile-form-element1 container-inline">';
				$basic_6 .= '<div class="mentee-profile-form-element1 mentee-profile-form-element2">&nbsp;';
				$basic_6 .= drupal_render($element);
				$basic_6 .= '</div>';
				$basic_6 .= '</div>';
			}
			if(in_array($key, $educational_elements)){
        $educational .= '<div class="mentee-profile-form-element1 mentee-profile-form-element10 container-inline">';
        $educational .= '<div class="mentee-profile-form-element10 ">&nbsp;';
        $educational .= drupal_render($element);
        $educational .= '</div>';
        $educational .= '</div>';
      }
      if(in_array($key, $educational_elements1)){
				if($key == 'cityUSA'){
					$educational1 .= '<div id="div_'.$element['#id'].'" class="mentee-profile-form-element1 " style=" margin-left: 1%;"><div class="mentee-profile-form-element3" style="padding-top:1%; width:100%;">City of High School</div>';
				}else{
					$educational1 .= '<div id="div_'.$element['#id'].'" class="mentee-profile-form-element1 " style=" margin-left: 1%;"><div class="mentee-profile-form-element3" style="padding-top:1%;">'.$element['#title'].'</div>';
				}
				$educational1 .= '<div class="mentee-profile-form-element1 ">';
				$educational1 .= drupal_render($element);
				$educational1 .= '</div>';
				$educational1 .= '</div>';
			}
      if(in_array($key, $educational_elements2)){
        $educational .= '<div class="mentee-profile-form-element1 mentee-profile-form-element10">';
        $educational .= '<div class="mentee-profile-form-element10 ">&nbsp;';
        $educational .= drupal_render($element);
        $educational .= '</div>';
        $educational .= '</div>';
      }
			if(in_array($key, $anmi_elements1) && in_array($element['#type'],$allowed_elements)){
				$areaNeedingMentoringIn1 .= '<div class="mentee-profile-form-element4" >';
				$areaNeedingMentoringIn1 .= '<div class="mentee-profile-form-element5">&nbsp;';
				$areaNeedingMentoringIn1 .= drupal_render($element);
				$areaNeedingMentoringIn1 .= '</div>';
				$areaNeedingMentoringIn1 .= '</div>';
			}
      if(in_array($key, $anmi_elements2) && in_array($element['#type'],$allowed_elements)){
				$areaNeedingMentoringIn2 .= '<div class="mentee-profile-form-element1 mentee-profile-form-element2 " style="display: inline-block !important; margin-left: 1%;"><div class="mentee-profile-form-element3" style="padding-top:1%;">'.$element['#title'].'</div>';
				$areaNeedingMentoringIn2 .= '<div class="mentee-profile-form-element6 ">';
				$areaNeedingMentoringIn2 .= drupal_render($element);
				$areaNeedingMentoringIn2 .= '</div>';
				$areaNeedingMentoringIn2 .= '</div>';
			}
			
		}
	}
	$basic_1 .= '</div>';
	$basic_2 .= '</div>';
	$basic_3 .= '</div>';
	$basic_4 .= '</div>';
	$basic_5 .= '</div>';
	$basic_6 .= '</div>';
	$educational .= '</div>';
	$educational1 .= '</div>';
	$areaNeedingMentoringIn1 .= '</div>';
	$areaNeedingMentoringIn2 .= '</div>';
	$output .= '<div class = "mentee-profile-form-block-heading1">
			<div class="mentee-profile-form-block-heading2 "><b>Basic Information</b></div>';
	$output .= $basic_1.$basic_2.$basic_3.$basic_4.$basic_5.$basic_6;
	$output .= '</div>';
		$output .= '<div class = "mentee-profile-form-block-heading1">
				<div class = "mentee-profile-form-block-heading2"><b>Educational Information</b></div>';
	//$output .= $educational1;
	$output .= $educational.$educational1;
	$output .= '</div>';
	$output .= '<div class = "mentee-profile-form-block-heading1">
			<div class = "mentee-profile-form-block-heading2"><b>Area Needing Mentoring In</b></div>';
	$output .= $areaNeedingMentoringIn1.$areaNeedingMentoringIn2;
	$output .= '</div>';

	
	$output .= '<script type="text/javascript">
		(function ($) {
			if(!$("#edit-areaofmentoring-1").is(":checked")){
        $("#edit-fieldofstudy").parent().parent().parent().hide();
        $("#dropdown_specialization_replace_1").parent().parent().hide();
        $("#mentee_edit_dropdown_specialization_replace").parent().parent().hide();
      }
      $("#edit-areaofmentoring-1").change(function(){
        $("#edit-fieldofstudy").parent().parent().parent().toggle();
        $("#dropdown_specialization_replace_1").parent().parent().toggle();
        $("#mentee_edit_dropdown_specialization_replace").parent().parent().toggle();
      });
      $("#edit-cityusa").css("max-width","50%");
      $("#edit-country").each(function(){
        $valueCountry = $(this).val();
        if($valueCountry == "USA"){
            $("#div_edit-country-others").hide();
            $("#div_edit-state").hide();
            $("#div_edit-city").hide();
        }else if($valueCountry == "Others"){
            $("#div_edit-stateusa").hide();
            $("#div_edit-cityusa").hide();
        }else{
            $("#div_edit-country-others").hide();
            $("#div_edit-state").hide();
            $("#div_edit-city").hide();
            $("#div_edit-stateusa").hide();
            $("#div_edit-cityusa").hide();
        }
        $(this).change(function(){
          $valueCountry = $(this).val();
          if($valueCountry == "USA"){
            $("#div_edit-country-others").hide();
            $("#div_edit-state").hide();
            $("#div_edit-city").hide();
            $("#div_edit-stateusa").show();
            $("#div_edit-cityusa").show();
          }else if($valueCountry == "Others"){
            $("#div_edit-stateusa").hide();
            $("#div_edit-cityusa").hide();
            $("#div_edit-country-others").show();
            $("#div_edit-state").show();
            $("#div_edit-city").show();
          }else{
            $("#div_edit-country-others").hide();
            $("#div_edit-state").hide();
            $("#div_edit-city").hide();
            $("#div_edit-stateusa").hide();
            $("#div_edit-cityusa").hide();
        }
        });
      });
    /*$("div[id^=div_]").each(function(){
        $idval = "#"+$(this).attr("id");
        $subval = $idval.replace("div_","");
      
        $($subval).parent().on("show", function() {
                alert($idval);
          });
 
        $($subval).parent().on("hide", function() {
                alert($idval);
          });
      });
      $(".form-text").each(function(){
                var titleText = $(this).siblings("label").text();
                if(!$(this).val()){
                  $(this).val(titleText) ;
                  $(this).css("color","#ABA6A6");
                  }else if($(this).val() == titleText){
                  $(this).css("color","#ABA6A6");
                  }
                $(this).keydown(function(){
                  if(this.value == titleText) {
                          this.value = "";
                          $(this).css("color","black");
                  }
                  });

                  $(this).blur(function(){
                    if(this.value == "") {
                          this.value = titleText;
                    if(titleText.indexOf("*") > -1){
                      $(this).css("color","red");
                    }else{
                            $(this).css("color","#ABA6A6");
                    }
                  }
                  });
              });*/
      $(".form-textarea").each(function(){
        var titleText = $(this).parent().siblings("label").text();
        if(!$(this).val()){
          $(this).val(titleText) ;
          $(this).css("color","#ABA6A6");
        }else if($(this).val() == titleText){
          $(this).css("color","#ABA6A6");
        }
        $(this).keydown(function(){
          if(this.value == titleText) {
            this.value = "";
            $(this).css("color","black");
          }
        });

        $(this).blur(function(){
          if(this.value == "") {
            this.value = titleText;
            $(this).css("color","#ABA6A6");
          }
        });
      });
      $("label").hide();
      $("label").each(function(){
        if($(this).attr("for").indexOf("areaofmentoring") > -1){
          $(this).show();
        }else if($(this).attr("for").indexOf("fieldofspecialization") > -1){
          $(this).show();
        }else if($(this).attr("for").indexOf("fieldofstudy") > -1){
          $(this).show();
        }else if($(this).attr("for").indexOf("edit-mentee-type") > -1){
          $(this).show();
        }else if($(this).attr("for").indexOf("edit-degree") > -1){
          $(this).show();
        }
        if(($(this).parent().parent().parent().attr("id").indexOf("edit-highschool")) > -1){
          $(this).show();
          $(this).css("margin-left", "0%");
          $(this).css("color","orange")
          $(this).css("font-weight", "normal");
        }
        if(($(this).parent().parent().parent().attr("id").indexOf("edit-transfer")) > -1){
          $(this).show();
          $(this).css("margin-left", "0%");
          $(this).css("color","orange")
          $(this).css("font-weight", "normal");
        }
      });
      $("h1").hide();
      $(".description").hide();

    })(jQuery);

  </script>';
  return $output;
}