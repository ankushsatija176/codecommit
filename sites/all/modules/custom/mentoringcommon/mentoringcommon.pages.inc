<?php 

function mentee_fields_form(&$form, &$form_state) {

  //BASIC FORM//
  /*$form['account']['basicInformation'] = array(
    '#type' => 'fieldset',
    '#title' => t('Basic Information'),
  );*/
  $form['account']['parent_mail'] = array(
    '#type' => 'textfield',
    '#title' => t('Parent E-mail address'),
    '#maxlength' => EMAIL_MAX_LENGTH,
    '#description' => t('A valid e-mail address. All e-mails from the system will be sent to this address. The e-mail address is not made public and will only be used if you wish to receive a new password or wish to receive certain news or notifications by e-mail.'),
    '#required' => TRUE,
    '#default_value' => (!$register ? $account->parent_mail : ''),
    '#size' => 20,
  );

  $form['account']['fname'] = array(
    '#type' => 'textfield',
    '#title' => t('First Name'),
    '#maxlength' => 255,
    //'#description' => t('First name of the user.'),
    '#required' => TRUE,
  	//'#name' => 'First Name',
  	'#size' => '20',
    //'#default_value' => isset($values['fname']) ? $values['fname'] : NULL,
  );
  
  $form['account']['lname'] = array(
    '#type' => 'textfield',
    '#title' => t('Last name'),
    '#maxlength' => 255,
    //'#description' => t('Last name of the user.'),
    '#required' => FALSE,
  	//'#name' => 'Last Name',
  	'#size' => '20',
    //'#default_value' => isset($values['lname']) ? $values['lname'] : NULL,
  );
  
  $form['account']['bday'] = array(
    '#type' => 'date',
    '#title' => t('Date of birth'),
    //'#description' => t('Birth day of the user.'),
    '#required' => TRUE,
  	//'#name' => 'Date Of Birth',
    //'#default_value' => isset($values['bday']) ? $values['bday'] : time(),
  	'#after_build' => array("format_dob"),
  );
  
  $form['account']['gender'] = array(
    '#title' => t('Gender'),
    '#type' => 'select',
    //'#description' => 'Select the gender.',
    '#required' => TRUE,
    '#options' => array(t('M'), t('F')),
    '#empty_option' => "Gender *",
  );
  
  $form['account']['zcode'] = array(
    '#type' => 'textfield',
    '#title' => t('Zip code'),
    '#description' => t('e.g. 89076'),
    '#required' => TRUE,
  	//'#name' => 'Zip Code',
  	'#size' => '20',
    //'#default_value' => isset($values['zcode']) ? $values['zcode'] : NULL,
  );
  
  $form['account']['mobile'] = array(
    '#type' => 'textfield',
    '#title' => t('Mobile'),
    '#required' => FALSE,
  	'#description' => t('e.g. (498)345-4566'),
    //'#name' => 'Mobile',
  	'#size' => '20',
    //'#default_value' => isset($values['mobile']) ? $values['mobile'] : NULL,
  );
  
  $form['account']['skype_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Skype ID'),
  	//'#name' => 'Skype ID',
  	'#size' => '20',
    //'#default_value' => isset($values['skype_id']) ? $values['skype_id'] : NULL,
  );
  
  //EDUCATION INFO//
 /* $form['account']['educationalInformation'] = array(
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
    '#title' => t('Student Type'),
    '#default_value' => isset($values['mentee_type']) ? $values['mentee_type'] : 'highschool',
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
    '#title' => t('School Name *'),
    '#maxlength' => 255,
    //'#description' => t('Name of your school'),
    //'#required' => TRUE,
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
      '#required' => FALSE,
      '#options' => drupal_map_assoc(array(t(date('Y', time())), t(date('Y', strtotime('+1 year'))), t(date('Y', strtotime('+2 years'))), t(date('Y', strtotime('+3 years'))), t(date('Y', strtotime('+4 years'))))),
      '#empty_option' => 'Year of Graduation *',
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
    '#title' => t('Current College Name *'),
    '#maxlength' => 255,
    //'#description' => t('Name of your college'),
    //'#required' => TRUE,
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
    '#empty_option' => 'Year of Intended Transfer *',
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
    '#required' => FALSE,
    '#empty_option' => 'Country *',
  	'#options' => array(
	 				'USA' => t('USA'),
	 				'Others' => t('Others'),
	 		),
  	'#default_value' => 'Country *',
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
  );
  
  $form['account']['stateOthers'] = array(
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
  		//'#default_value' => isset($values['state']) ? $values['state'] : NULL,
  );
  $value_state_usa = isset($form_state['values']['stateUSA']) ? $form_state['values']['stateUSA'] : NULL;
  $form['account']['stateUSA'] = array(
    '#type' => 'select',
    '#title' => t('State'),
    '#required' => FALSE,
    '#empty_option' => 'State *',
    //'#autocomplete_path' => 'states/autocomplete',
    //'#name' => 'State',
    //'#size' => '20',
		'#ajax' => array(
  				'event' => 'change',
  				'callback' => 'state_ajax_callback',
  				'progress' => array(
  						'type' => 'throbber',
  						//'message' => t('loading ...'),
  				),
  				'wrapper' => 'dropdown_city_replace_1',
  				'effect'=>'fade',
  		),

  		'#options' =>get_states_for_country('1'),
  		'#states' => array(
  				'visible' => array(
  						':input[name="country"]' => array('value' => 'USA'),
  				),
  		),
  		'#default_value' => $value_state_usa,
  );
  
  $form['account']['cityOthers'] = array(
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
  		),//'#default_value' => isset($values['city']) ? $values['city'] : NULL,
  );
  $form['account']['cityUSA'] = array(
  		'#type' => 'select',
  		//'#title' => t('City'),
  		'#required' => FALSE,
  		'#empty_option' => 'City of High School *',
  		//'#autocomplete_path' => 'cities/autocomplete',
  		//'#name' => 'City',
  		//'#size' => '20',
      '#validated' => TRUE,
  		'#prefix' => '<div id="dropdown_city_replace_1">',
  		'#suffix' => '</div>',
  		'#options' => get_city_for_state($value_state_usa),
  		/*'#options' => array(
  		 '1' => t('santa ana'),
  				'2' => t('Santa Ana'),
  		),*/
  		'#states' => array(
  				'visible' => array(
  						':input[name="country"]' => array('value' => 'USA'),
  				),
  		),
  		//'#default_value' => isset($values['city']) ? $values['city'] : NULL,
  );

  //MENTORSHIP DETAILS//
  /*$form['account']['details'] = array(
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
    //'#multiple' => TRUE,
    '#required' => TRUE,
    '#options' =>  $options ,
    //'#default_value' => isset($values['areaofmentoring']) ? $values['areaofmentoring'] : NULL,
  );
  
  $entries = db_query("SELECT cid, name FROM {specialization_category}");

  $options = array();
  foreach($entries as $record)
  {
    $options[$record->cid] =$record->name;
  }
  //if(empty($values)) {
  
  	$value_field_of_study = isset($form_state['values']['fieldOfStudy']) ? $form_state['values']['fieldOfStudy'] : key($options);
	
  	//drupal_set_message("value".$value_field_of_study);
  /*} else {
  	if(isset($form_state['values']['fieldOfStudy'])) {
  		$value_field_of_study = $form_state['values']['fieldOfStudy'];	
  	} else {
  		$value_field_of_study = $values['fieldOfStudy'];
  	} 
  }*/
  //drupal_set_message("test2 ". $value_field_of_study);
  $form['account']['fieldOfStudy'] = array(
    '#type' => 'select',
    '#title' => t('Field of Study'),
    //'#description' => t('Field of study.'),
    '#required' => FALSE,
    '#options' => $options,
    '#default_value' => $value_field_of_study,
    '#ajax' => array(
   'event' => 'change',
        'callback' => 'mentee_fos_ajax_callback',
        'progress' => array(
        'type' => 'throbber',
      ),
        'wrapper' => 'mentee_dropdown_specialization_replace_1',
      ),
      '#states' => array(
      'visible' => array(
        ':input[name="areaofmentoring"]' => array('value' => '1'),
      ),
    ),
  );
  
  $form['account']['fieldOfSpecialization'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Field of Specialization'),
    //'#description' => t('Field of study you want to specialize in.'),
    '#required' => FALSE,
   // '#multiple' => TRUE,
    //'#options' => $options,
    '#prefix' => '<div id="mentee_dropdown_specialization_replace_1">',
    '#suffix' => '</div>',
    '#options' => mentee_specialization_dropdown_options_1($value_field_of_study),
    '#default_value' => isset($form_state['values']['fieldOfSpecialization']) ? $form_state['values']['fieldOfSpecialization'] : '',
    '#states' => array(
      'visible' => array(
        ':input[name="areaofmentoring"]' => array('value' => '1'),
      ),
    ),
  );
  
  $form['account']['mentoring_request'] = array(
    '#type' => 'textarea',
    '#title' => t(''),
  	//'#name' => 'Your mentoring request',
    //'#description' => t('Your mentoring request'),
    //'#default_value' => isset($values['mentoring_request']) ? $values['mentoring_request'] : NULL,
  ); 
  $form['account']['mentoring_terms'] = array(
  		'#type' => 'checkbox',
  		//'#required' => TRUE,
  		'#title' =>  t(''),
  		//'#default_value' => isset($values['m_type']) ? $values['m_type'] : NULL,
  		'#element_validate' => array('element_validate_checked'),
  );
  
}

function mentee_fos_ajax_callback($form, $form_state) {
	 return $form['account']['fieldOfSpecialization'];
}

function mentee_specialization_dropdown_options_1($key = '' ) {
	/*$keys = '';
	if(is_array($key)){
	foreach ($key as $i){
		if($i != 0)
		$keys .= $i.",";
	}
	$keys = substr($keys, 0, (strlen($keys) - 1));
	}else{
		$keys = $key;
	}
	
  $entries = db_query("SELECT scid, name FROM {specialization_subcategory} WHERE specialization_category_id IN ($keys)");*/
  
  $entries = db_query("SELECT scid, name FROM {specialization_subcategory} WHERE specialization_category_id = $key");
	
  $options = array();
  foreach($entries as $record)
  {
    $options[$record->scid] =$record->name;
  }
  return $options;
}

function mentee_fields_form_submit($form_state, $uid) {
	//	var_dump($form_state['values']);
    try {
    	
      $selected_aom = array();
      $selected_spec = array();  
	  
	  //entity_form_submit_build_entity('user', $account, $form, $form_state);  
	  $specialization = NULL;
		$entries = '';
		$fos = NULL; 
		/*if(isset($form_state['values']['fieldOfSpecialization'])) {
			$selected_spec = array_filter($form_state['values']['fieldOfSpecialization']);
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
				$entries = db_query("SELECT name FROM {specialization_subcategory} WHERE specialization_category_id = $fos");		
			}
			foreach($entries as $record) {
				$specialization .= $record->name . ', '; 	
			}
			$specialization = substr($specialization, 0, (strlen($specialization) - 2)); 
		}*/
		
		$mentoring_area = ''; 
		if(isset($form_state['values']['areaofmentoring'])) {
			$selected_aom = array_filter($form_state['values']['areaofmentoring']);
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
		}
		
		if(!empty($selected_aom) && isset($selected_aom[1]) && $selected_aom[1] == 1){
			$fos = $form_state['values']['fieldOfStudy']; 
			if(isset($form_state['values']['fieldOfSpecialization'])) {
				$selected_spec = array_filter($form_state['values']['fieldOfSpecialization']);
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
					$entries = db_query("SELECT name FROM {specialization_subcategory} WHERE specialization_category_id = $fos");		
				}
				foreach($entries as $record) {
					$specialization .= $record->name . ', '; 	
				}
				$specialization = substr($specialization, 0, (strlen($specialization) - 2)); 
			}
		}
		//$year_of_school_key = $educational_info['yearOfSchool'];
		//$year_of_school_value = $form['educational_info']['educationalInformation']['yearOfSchool']['#options'][$year_of_school_key];
		
    $year_of_school_value = NULL;
    $year_of_intended_transfer_value = NULL;
    if($form_state['values']['mentee_type'] == 'highschool')
      $year_of_school_value = $form_state['values']['yearOfSchool'];
    else if($form_state['values']['mentee_type'] == 'transfer')
      $year_of_intended_transfer_value = $form_state['values']['yearOfIntendedTransfer'];

		$birthDate = $form_state['values']['bday'];
		$nid = db_insert('mentee')
		->fields(array(
		'mid' => $uid,
    'parent_mail' => ($form_state['values']['parent_mail'] != 'Parent E-mail Address *')?$form_state['values']['parent_mail']:'',
		'first_name' => $form_state['values']['fname'],
		'last_name' => ($form_state['values']['lname'] != 'Last name ')?$form_state['values']['lname']:'',
		'birthday' => $birthDate['day'],
		'birthmonth' => $birthDate['month'],
		'birthyear' => $birthDate['year'],
		'gender' => $form_state['values']['gender'],
		'zipcode' => $form_state['values']['zcode'],
		'mobile' => ($form_state['values']['mobile'] != 'Mobile ')?$form_state['values']['mobile']:NULL,
		'skype_id' => ($form_state['values']['skype_id'] !='Skype ID ')?$form_state['values']['skype_id']:'',
		'userid' => $uid,
		'school_name' => ($form_state['values']['school_name'] != 'School Name * ')?$form_state['values']['school_name']:'',
		'country' => $form_state['values']['country'],
		'state' => $form_state['values']['state'],
		'city' => $form_state['values']['city'],
		'year_of_school' => $year_of_school_value,
    'mentee_type' => $form_state['values']['mentee_type'],
    'college_name' => ($form_state['values']['college_name'] != 'Current College Name * ')?$form_state['values']['college_name']:'',
    'year_of_intended_transfer' => $year_of_intended_transfer_value,
		//'aom_id' => $mentorship_details['areaofmentoring'],
		'fos_id' => $fos,
		//'fos_sub_id' => $mentorship_details['fieldOfSpecialization'],
		//'mentoring_request_title' => $mentorship_details['req_title'],
		'mentoring_request' => ($form_state['values']['mentoring_request']!='About me ')?$form_state['values']['mentoring_request']:'',
		//'hobbies' => $mentorship_details['hobby'],
		'specialization' => $specialization,
		'area_of_mentoring' => $mentoring_area,
		))
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
			$picture = $record['picture'];
		}
		
		$account = array();
		$account['uid'] = $uid;
		$account['status'] = 1;
		if($picture == 0) {
			if($form_state['values']['gender'] == 0) {
				$account['picture'] = 46;
			} else {
				$account['picture'] = 44;
			}
		}
		$success = drupal_write_record('users', $account, 'uid');
		
		$query = db_select('user_activation', 'ua'); 
		$query->condition('ua.uid', $uid, '=');
		$query->fields('ua', array('uid', 'activated'));
		$result = $query->execute();	
		$activated = 'N';
		if(	$record = $result->fetchAssoc()) {
			$activated = $record['activated'];
		}
				
		if($activated == 'N'){
			drupal_set_message(t("<p style='color:green; margin:0px !important;'>!activation_text</p>",
      array(
        '!activation_text' => '<strong>The user, '.$form_state['values']['fname'] . (($form_state['values']['lname'] != 'Last name ') ? ' ' . $form_state['values']['lname'] : '' ) .', has been registered successfully, but your account has not yet been verified. Please click on the link in the email sent to your email address from SkoolMentor to activate your account. Without account activation, mentors and mentees cannot connect with each other.</strong>',
      )), 'success');
      //drupal_set_message('The user, '.$form_state['values']['fname'] . (($form_state['values']['lname'] != 'Last name ') ? ' ' . $form_state['values']['lname'] : '' ) .', has been registered successfully, but your account has not yet been verified. Please click on the link sent to your e-mail address to activate your account');
			//drupal_goto('node/1');
	    } else {
	    	drupal_set_message('The user, '.$form_state['values']['fname'] . ' ' . (($form_state['values']['lname'] != 'Last name ') ? ' ' . $form_state['values']['lname'] : '' ) .', has been registered successfully. Please complete the rest of the form now.');
	    //	mentoringcommon_login_submit($form, $form_state);
	    }
		//drupal_goto('mentoring/login'); 
	} catch (Exception $e) {
	    watchdog_exception('user', $e);
	    throw $e;
	}
	
}

function mentor_fields_form(&$form, &$form_state) {
	/*$form['account']['basicInformation'] = array(
    '#type' => 'fieldset',
    '#title' => t('Basic Information'),
    '#collapsible' => TRUE,
  );*/
  
  $form['account']['fname'] = array(
    '#type' => 'textfield',
    '#title' => t('First Name'),
    '#maxlength' => 255,
    '#required' => TRUE,
  	//'#name' => 'First Name',
  	'#size' => '20',
    //'#default_value' => isset($values['fname']) ? $values['fname'] : NULL,
  );
  
  $form['account']['lname'] = array(
    '#type' => 'textfield',
    '#title' => t('Last name'),
    '#maxlength' => 255,
    '#required' => FALSE,
  	//'#name' => 'Last name',
  	'#size' => '20',
    //'#default_value' => isset($values['lname']) ? $values['lname'] : NULL,
  );
  
  $form['account']['bday'] = array(
    '#type' => 'date',
    '#title' => t('Date of birth'),
    '#required' => TRUE,
    //'#default_value' => isset($values['bday']) ? $values['bday'] : time(),
    '#after_build' => array("format_dob"),
  );
  
  $form['account']['gender'] = array(
    '#title' => t('Gender'),
    '#type' => 'select',
    //'#description' => 'Select the gender.',
    '#required' => TRUE,
    '#options' => array(t('M'), t('F')),
  	'#empty_option' => 'Gender *',
    //'#default_value' => isset($values['gender']) ? $values['gender'] : NULL,
  );
  
  $form['account']['country'] = array(
    '#type' => 'select',
    '#title' => t('Country'),
    //'#maxlength' => 255,
    '#empty_option' => 'Country *',
  	'#required' => FALSE,
  	'#options' => array(
	 				'USA' => t('USA'),
	 				'Others' => t('Others'),
	 		),
  	//'#default_value' => 'USA',
  );
  
  $form['account']['country_others'] = array(
    '#type' => 'textfield',
    '#title' => t('Please specify country'),
    '#maxlength' => 255,
    '#required' => FALSE,
  	'#states' => array(
  			'visible' => array(
  					':input[name="country"]' => array('value' => 'Others'),
  			),
  	),
  	'#size' => '20',
  );
  
  $form['account']['stateOthers'] = array(
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
  	//'#default_value' => isset($values['state']) ? $values['state'] : NULL,
  );
  $value_state_usa = isset($form_state['values']['stateUSA']) ? $form_state['values']['stateUSA'] : NULL;
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
 			 					'type' => 'throbber',
  								),
					  		'wrapper' => 'dropdown_city_replace_1',
  						),
  		'#options' =>get_states_for_country('1'),
  		'#states' => array(
  				'visible' => array(
  						':input[name="country"]' => array('value' => 'USA'),
  						),
  				),
  		//'#default_value' => isset($values['state']) ? $values['state'] : NULL,
  );
  
  $form['account']['cityOthers'] = array(
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
  	),//'#default_value' => isset($values['city']) ? $values['city'] : NULL,
  );
  $form['account']['cityUSA'] = array(
  		'#type' => 'select',
  		//'#title' => t('City'),
  		'#required' => FALSE,
  		'#empty_option' => 'City *',
  		//'#autocomplete_path' => 'cities/autocomplete',
  		//'#name' => 'City',
  		//'#size' => '20',
      '#validated' => TRUE,
  		'#prefix' => '<div id="dropdown_city_replace_1">',
  		'#suffix' => '</div>',
  		'#options' => get_city_for_state($value_state_usa),
  		/*'#options' => array(
	 				'1' => t('santa ana'),
	 				'2' => t('Santa Ana'),
	 	),*/
  		'#states' => array(
  				'visible' => array(
  						':input[name="country"]' => array('value' => 'USA'),
  						),
  				),
  	 	//'#default_value' => isset($values['city']) ? $values['city'] : NULL,
  );
  $form['account']['zcode'] = array(
    '#type' => 'textfield',
    '#title' => t('Zip code'),
    '#required' => TRUE,
  	'#description' => t('e.g. 89076'),
  	//'#name' => 'Zip code',
    '#size' => '20',
    //'#default_value' => isset($values['zcode']) ? $values['zcode'] : NULL,
  );
  
  $form['account']['mobile'] = array(
    '#type' => 'textfield',
    '#title' => t('Mobile'),
    '#required' => FALSE,
  	'#description' => t('e.g. (498)345-4566'),
  	//'#name' => 'Mobile',
    '#size' => '20',
    //'#default_value' => isset($values['mobile']) ? $values['mobile'] : NULL,
  );
  
  $form['account']['skype_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Skype Id'),
  	//'#name' => 'Skype Id',
    '#size' => '20',
    //'#default_value' => isset($values['skype_id']) ? $values['skype_id'] : NULL,
  );
  
  $form['account']['m_type'] = array(
    '#type' => 'radios',
    '#required' => TRUE,
    '#options' => array(
      'professional' => t('Professional'),
      'student' => t('Student'),
    ),
    '#title' => t('Work Status'),
  		'#ajax' => array('event' => 'change',
  				'callback' => 'mtype_ajax_callback',
  				'progress' => array(
  						'message' => '',
  				),
  				'wrapper' => 'dropdown_volunteer_default',
  		),
    //'#default_value' => isset($values['m_type']) ? $values['m_type'] : NULL,
  );
  
  $form['account']['professional'] = array(
    '#type' => 'fieldset',
    '#title' => t('Professional Information'),
    '#states' => array(
      'visible' => array(
        ':input[name="m_type"]' => array('value' => 'professional'),
      ),
    ),
  );
  
  $form['account']['professional']['employer'] = array(
    '#type' => 'textfield',
    '#title' => t('Employer'),
    '#required' => TRUE,
    '#maxlength' => 255,
    '#states' => array(
      'visible' => array(
        ':input[name="m_type"]' => array('value' => 'professional'),
      ),
    ),
  	//'#name' => 'Employer',
    '#size' => '20',
    //'#default_value' => isset($values['employer']) ? $values['employer'] : NULL,
  );
  
  $form['account']['professional']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Job Title'),
    '#required' => TRUE,
    '#maxlength' => 255,
    '#states' => array(
      'visible' => array(
        ':input[name="m_type"]' => array('value' => 'professional'),
      ),
    ),
  	//'#name' => 'Job Title',
    '#size' => '20',
    //'#default_value' => isset($values['title']) ? $values['title'] : NULL,
  );
  
  $form['account']['professional']['yearsOfExp'] = array(
    '#title' => t('Yrs. Of Experience'),
    //'#required' => TRUE,
    '#type' => 'select',
    '#options' => array(t('0'),t('1'), t('2'),t('3'), t('4'),t('5'),t('6'), t('7'),t('8'), t('9'),
    					t('10'),t('11'), t('12'),t('13'), t('14'),t('15'),t('16'), t('17'),t('18'), t('19'),
    					t('20'),t('21'), t('22'),t('23'), t('24'),t('25'),t('26'), t('27'),t('28'), t('29'),
    					t('30'),t('31'), t('32'),t('33'), t('34'),t('35'),t('36'), t('37'),t('38'), t('39'), t('40')),
    '#states' => array(
      'visible' => array(
        ':input[name="m_type"]' => array('value' => 'professional'),
      ),
    ),
  	'#empty_option' => 'Yrs. Of Experience *',
    //'#default_value' => isset($values['yearsOfExp']) ? $values['yearsOfExp'] : NULL,
  );
  
  $form['account']['professional']['linkedInProfile'] = array(
    '#type' => 'textfield',
    '#title' => t('Linkedin Profile'),
    '#maxlength' => 255,
    '#states' => array(
      'visible' => array(
        ':input[name="m_type"]' => array('value' => 'professional'),
      ),
    ),
  	//'#name' => 'Linkedin Profile',
    '#size' => '20',
    //'#default_value' => isset($values['linkedInProfile']) ? $values['linkedInProfile'] : NULL,
  );
  
  $form['account']['professional']['lastSchoolAttended'] = array(
    '#type' => 'textfield',
    '#title' => t('Last School Attended'),
    '#required' => TRUE,
    '#maxlength' => 255,
    '#states' => array(
      'visible' => array(
        ':input[name="m_type"]' => array('value' => 'professional'),
      ),
    ),
  	//'#name' => 'Last School Attended',
    '#size' => '20',
    //'#default_value' => isset($values['lastSchoolAttended']) ? $values['lastSchoolAttended'] : NULL,
  );
  
  $form['account']['professional']['yearOfSchool'] = array(
    '#type' => 'select',
    '#title' => t('Year of Graduation'),
    //'#required' => TRUE,
    '#options' => array(t(date('Y' , strtotime('-35 years'))), t(date('Y' , strtotime('-34 years'))), t(date('Y' , strtotime('-33 years'))), t(date('Y' , strtotime('-32 years'))), t(date('Y' , strtotime('-31 years'))),t(date('Y' , strtotime('-30 years'))), t(date('Y' , strtotime('-29 years'))), t(date('Y' , strtotime('-28 years'))), t(date('Y' , strtotime('-27 years'))), t(date('Y' , strtotime('-26 years'))), t(date('Y' , strtotime('-25 years'))), t(date('Y' , strtotime('-24 years'))), t(date('Y' , strtotime('-23 years'))), 
    					t(date('Y' , strtotime('-22 years'))), t(date('Y' , strtotime('-21 years'))), t(date('Y' , strtotime('-20 years'))), t(date('Y' , strtotime('-19 years'))), t(date('Y' , strtotime('-18 years'))), t(date('Y' , strtotime('-17 years'))), t(date('Y' , strtotime('-16 years'))), t(date('Y' , strtotime('-15 years'))), t(date('Y' , strtotime('-14 years'))), t(date('Y' , strtotime('-13 years'))), t(date('Y' , strtotime('-12 years'))), t(date('Y' , strtotime('-11 years'))), 
    					t(date('Y' , strtotime('-10 years'))), t(date('Y' , strtotime('-9 years'))), t(date('Y' , strtotime('-8 years'))), t(date('Y' , strtotime('-7 years'))), t(date('Y' , strtotime('-6 years'))), t(date('Y' , strtotime('-5 years'))), t(date('Y' , strtotime('-4 years'))), t(date('Y' , strtotime('-3 years'))), t(date('Y' , strtotime('-2 years'))), t(date('Y' , strtotime('-1 years'))), t(date('Y', time()))),
    '#states' => array(
      'visible' => array(
        ':input[name="m_type"]' => array('value' => 'professional'),
      ),
    ),
  	'#empty_option' => 'Year of Graduation *',
    //'#default_value' => isset($values['yearOfSchool']) ? $values['yearOfSchool'] : '',
  );
  $form['account']['professional']['workemail'] = array(
  		'#type' => 'textfield',
  		'#title' => t('Work E-mail Address'),
  		'#required' => TRUE,
  		'#maxlength' => 255,
  		'#states' => array(
  				'visible' => array(
  						':input[name="m_type"]' => array('value' => 'professional'),
  				),
  		),
  		//'#name' => 'Last School Attended',
  		'#size' => '20',
  		//'#default_value' => isset($values['lastSchoolAttended']) ? $values['lastSchoolAttended'] : NULL,
  );
  $form['account']['professional']['confirm_workemail'] = array(
      '#type' => 'textfield',
      '#title' => t('Confirm Work E-mail Address'),
      '#required' => TRUE,
      '#maxlength' => 255,
      '#states' => array(
          'visible' => array(
              ':input[name="m_type"]' => array('value' => 'professional'),
          ),
      ),
      //'#name' => 'Last School Attended',
      '#size' => '20',
      //'#default_value' => isset($values['lastSchoolAttended']) ? $values['lastSchoolAttended'] : NULL,
  );
  
  $form['account']['student'] = array(
    '#type' => 'fieldset',
    '#title' => t('Student Information'),
    '#states' => array(
      'visible' => array(
        ':input[name="m_type"]' => array('value' => 'student'),
      ),
    ),
  );
  
  $form['account']['student']['schoolAttending'] = array(
    '#type' => 'textfield',
    '#title' => t('School Attending'),
    '#maxlength' => 255,
    '#required' => TRUE,
    '#states' => array(
      'visible' => array(
        ':input[name="m_type"]' => array('value' => 'student'),
      ),
    ),
  	//'#name' => 'School Attending',
    '#size' => '20',
    //'#default_value' => isset($values['schoolAttending']) ? $values['schoolAttending'] : NULL,
  );
  
  $form['account']['student']['expectedYearOfSchool'] = array(
    '#type' => 'select',
    '#title' => t('Expected year of graduation'),
    //'#required' => TRUE,
    '#options' => array(t(date('Y', time())), t(date('Y', strtotime('+1 year'))), t(date('Y', strtotime('+2 years'))), t(date('Y', strtotime('+3 years'))), t(date('Y', strtotime('+4 years')))),
    '#states' => array(
      'visible' => array(
        ':input[name="m_type"]' => array('value' => 'student'),
      ),
    ),
  	'#empty_option' => 'Year of Graduation *',
    //'#name' => 'Expected year of graduation',
    //'#default_value' => isset($values['yearOfSchool']) ? $values['yearOfSchool'] : '',
  );
  $form['account']['student']['collegeemail'] = array(
  		'#type' => 'textfield',
  		'#title' => t('College E-mail Address'),
  		'#maxlength' => 255,
  		'#required' => TRUE,
  		'#states' => array(
  				'visible' => array(
  						':input[name="m_type"]' => array('value' => 'student'),
  				),
  		),
  		//'#name' => 'School Attending',
  		'#size' => '20',
  		//'#default_value' => isset($values['schoolAttending']) ? $values['schoolAttending'] : NULL,
  );
  $form['account']['student']['confirm_collegeemail'] = array(
      '#type' => 'textfield',
      '#title' => t('Confirm College E-mail Address'),
      '#maxlength' => 255,
      '#required' => TRUE,
      '#states' => array(
          'visible' => array(
              ':input[name="m_type"]' => array('value' => 'student'),
          ),
      ),
      //'#name' => 'School Attending',
      '#size' => '20',
      //'#default_value' => isset($values['schoolAttending']) ? $values['schoolAttending'] : NULL,
  );
  /*$form['account']['academic_details'] = array(
    '#type' => 'fieldset',
    '#title' => t('Academic Details'),
  );*/

  //Adding High School Fields -

  $form['account']['transfer_highschool'] = array(
      '#type' => 'select',
      '#title' => t('Are/Were you a Transfer Student?'),
      '#options' => array(
          '1' => t('Yes'),
          '2' => t('No'),
      ),
      '#default_value' => 2,
  );

  $form['account']['highSchoolName'] = array(
    '#type' => 'textfield',
    '#title' => t('High School/Community College Name'),
    '#required' => FALSE,
    '#maxlength' => 255,
    '#size' => '25',
  );
  
  $form['account']['yearOfHighSchool'] = array(
    '#type' => 'select',
    '#title' => t('Year of High School/Community College Graduation'),
    //'#required' => TRUE,
    '#options' => array(t(date('Y' , strtotime('-35 years'))), t(date('Y' , strtotime('-34 years'))), t(date('Y' , strtotime('-33 years'))), t(date('Y' , strtotime('-32 years'))), t(date('Y' , strtotime('-31 years'))),t(date('Y' , strtotime('-30 years'))), t(date('Y' , strtotime('-29 years'))), t(date('Y' , strtotime('-28 years'))), t(date('Y' , strtotime('-27 years'))), t(date('Y' , strtotime('-26 years'))), t(date('Y' , strtotime('-25 years'))), t(date('Y' , strtotime('-24 years'))), t(date('Y' , strtotime('-23 years'))), 
              t(date('Y' , strtotime('-22 years'))), t(date('Y' , strtotime('-21 years'))), t(date('Y' , strtotime('-20 years'))), t(date('Y' , strtotime('-19 years'))), t(date('Y' , strtotime('-18 years'))), t(date('Y' , strtotime('-17 years'))), t(date('Y' , strtotime('-16 years'))), t(date('Y' , strtotime('-15 years'))), t(date('Y' , strtotime('-14 years'))), t(date('Y' , strtotime('-13 years'))), t(date('Y' , strtotime('-12 years'))), t(date('Y' , strtotime('-11 years'))), 
              t(date('Y' , strtotime('-10 years'))), t(date('Y' , strtotime('-9 years'))), t(date('Y' , strtotime('-8 years'))), t(date('Y' , strtotime('-7 years'))), t(date('Y' , strtotime('-6 years'))), t(date('Y' , strtotime('-5 years'))), t(date('Y' , strtotime('-4 years'))), t(date('Y' , strtotime('-3 years'))), t(date('Y' , strtotime('-2 years'))), t(date('Y' , strtotime('-1 years'))), t(date('Y', time()))),
    '#empty_option' => 'Year of Graduation',
  );

  $form['account']['countrySchool'] = array(
    '#type' => 'select',
    '#title' => t('Country of High School'),
    //'#maxlength' => 255,
    '#empty_option' => 'Country',
    '#required' => FALSE,
    '#options' => array(
          'USA' => t('USA'),
          'Others' => t('Others'),
      ),
    //'#default_value' => 'USA',
  );
  
  $form['account']['country_othersSchool'] = array(
    '#type' => 'textfield',
    '#title' => t('Please specify country'),
    '#maxlength' => 255,
    '#required' => FALSE,
    '#states' => array(
        'visible' => array(
            ':input[name="countrySchool"]' => array('value' => 'Others'),
        ),
    ),
    '#size' => '20',
  );
  
  $form['account']['stateOthersSchool'] = array(
    '#type' => 'textfield',
    '#title' => t('State'),
    '#required' => FALSE,
    //'#autocomplete_path' => 'states/autocomplete',
    //'#name' => 'State',
    '#size' => '20',
    '#states' => array(
        'visible' => array(
            ':input[name="countrySchool"]' => array('value' => 'Others'),
        ),
    ),
    //'#default_value' => isset($values['state']) ? $values['state'] : NULL,
  );
  $value_state_usa_school = isset($form_state['values']['stateUSASchool']) ? $form_state['values']['stateUSASchool'] : NULL;
  $form['account']['stateUSASchool'] = array(
      '#type' => 'select',
      '#title' => t('State of School'),
      '#required' => FALSE,
      '#empty_option' => 'State',
      //'#autocomplete_path' => 'states/autocomplete',
      //'#name' => 'State',
      //'#size' => '20',
      '#ajax' => array('event' => 'change',
                'callback' => 'state_ajax_callback_school',
                'progress' => array(
                'type' => 'throbber',
                  ),
                'wrapper' => 'dropdown_city_replace_2',
              ),
      '#options' =>get_states_for_country('1'),
      '#states' => array(
          'visible' => array(
              ':input[name="countrySchool"]' => array('value' => 'USA'),
              ),
          ),
      //'#default_value' => isset($values['state']) ? $values['state'] : NULL,
  );
  
  $form['account']['cityOthersSchool'] = array(
    '#type' => 'textfield',
    '#title' => t('City of School'),
    '#required' => FALSE,
    //'#autocomplete_path' => 'cities/autocomplete',
    //'#name' => 'City',
    '#size' => '20',
    '#states' => array(
        'visible' => array(
            ':input[name="countrySchool"]' => array('value' => 'Others'),
        ),
    ),//'#default_value' => isset($values['city']) ? $values['city'] : NULL,
  );
  $form['account']['cityUSASchool'] = array(
      '#type' => 'select',
      //'#title' => t('City'),
      '#required' => FALSE,
      '#empty_option' => 'City',
      //'#autocomplete_path' => 'cities/autocomplete',
      //'#name' => 'City',
      //'#size' => '20',
      '#validated' => TRUE,
      '#prefix' => '<div id="dropdown_city_replace_2">',
      '#suffix' => '</div>',
      '#options' => get_city_for_state($value_state_usa_school),
      /*'#options' => array(
          '1' => t('santa ana'),
          '2' => t('Santa Ana'),
    ),*/
      '#states' => array(
          'visible' => array(
              ':input[name="countrySchool"]' => array('value' => 'USA'),
              ),
          ),
      //'#default_value' => isset($values['city']) ? $values['city'] : NULL,
  );
  	$entries = db_query("SELECT aid, name FROM {area_mentoring}");
  	
  	$options = array();
  	foreach($entries as $record)
  	{
  		$options[$record->aid] =$record->name;
  	}
  	
  	$form['account']['areaofmentoring'] = array(
  			'#title' => t('Area Of Interest For Mentoring'),
  			'#type' => 'checkboxes',
  			//'#description' => 'Select the area you want to be mentored',
  			//'#multiple' => TRUE,
  			'#required' => TRUE,
  			'#options' =>  $options ,
  			//'#default_value' => isset($values['areaofmentoring']) ? $values['areaofmentoring'] : NULL,
  	);
  	
  $entries = db_query("SELECT cid, name FROM {specialization_category}");

  $options = array();
  foreach($entries as $record)
  {
    $options[$record->cid] =$record->name;
  }
  
  //if(empty($values)) {
  
  	$value_field_of_study = isset($form_state['values']['fieldOfStudy']) ? $form_state['values']['fieldOfStudy'] : key($options);
  /*} else {
  	if(isset($form_state['values']['fieldOfStudy'])) {
  		$value_field_of_study = $form_state['values']['fieldOfStudy'];	
  	} else {
  		$value_field_of_study = $values['fieldOfStudy'];
  	}
  }*/
  
  $form['account']['fieldOfStudy'] = array(
    '#type' => 'select',
    '#title' => t('Field of Study'),
    //'#description' => t('Field of study.'),
    '#required' => TRUE,
    '#options' => $options,
    '#default_value' => $value_field_of_study,
    '#ajax' => array(
    'event' => 'change',
        'callback' => 'mentor_fields_ajax_callback',
        'progress' => array(
        'type' => 'throbber',
      ),
        'wrapper' => 'dropdown_specialization_replace_1',
      ),
  );
  
  $form['account']['fieldOfSpecialization'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Field of Specialization'),
    //'#description' => t('Field of study you are specialized in.'),
    '#required' => FALSE,
    '#validated' => TRUE,
   // '#multiple' => true,
    //'#options' => $options,
    '#prefix' => '<div id="dropdown_specialization_replace_1">',
    '#suffix' => '</div>',
    '#options' => mentor_fields_specialization_dropdown_options($value_field_of_study),
    '#default_value' => isset($form_state['values']['fieldOfSpecialization']) ? $form_state['values']['fieldOfSpecialization'] : '',
  );
  
  $entries = db_query("SELECT eid, name FROM {education_qualification}");

  $options = array();
  foreach($entries as $record)
  {
    $options[$record->eid] =$record->name;
  }
  
   $form['account']['degree'] = array(
    '#title' => t('Degree'),
    '#type' => 'select',
    //'#description' => 'Your Qualification',
    '#required' => TRUE,
    '#options' =>  $options ,
    '#default_value' => isset($values['degree']) ? $values['degree'] : NULL,
  );
 /* 
  $form['account']['details'] = array(
    '#type' => 'fieldset',
    '#title' => t('General Details'),
    '#collapsible' => TRUE,
  );
  */
  $form['account']['about_me'] = array(
    '#type' => 'textarea',
    '#title' => t(''),
  	//'#name' => 'About myself',
    //'#default_value' => isset($values['about_me']) ? $values['about_me'] : NULL,
  );
  $form['account']['other_colleges_accepted_at'] = array(
    '#type' => 'textfield',
    '#title' => t('Other Colleges Accepted At'),
    '#required' => FALSE,
    '#maxlength' => 255,
    '#size' => '255',
  );
  $form['account']['fb_uname'] = array(
    '#type' => 'textfield',
    '#title' => t('Facebook Profile Username'),
    '#required' => FALSE,
    '#maxlength' => 255,
    '#size' => '255',
  );
  /*
  $form['account']['motivation'] = array(
    '#type' => 'textarea',
    '#title' => t('What motivates you to be a mentor?'),
  	//'#name' => 'What motivates you to be a mentor? ',
    //'#default_value' => isset($values['motivation']) ? $values['motivation'] : NULL,
  );
  */
  $form['account']['response_time'] = array(
    '#title' => t('Expected response time'),
    '#type' => 'select',
    //'#default_value' => (isset($values['motivation']) ? $values['response_time'] : ''),
    '#options' => array(t('Everyday'), t('Once in a week'),t('2 times in a week'), t('3 times in a week'), t('Once in two weeks'), t('Once in a month')),
  	'#empty_option' => '--Select--',
    //'#name' => 'Expected response time',
  );
  $form['account']['available_time'] = array(
    '#type' => 'textarea',
    '#title' => t(''),
  );
  $form['account']['engagement_model_with_mentee'] = array(
  		'#type' => 'radios',
  		'#title' => t('Engagement Model With Mentee'),
  		'#required' => TRUE,
  		'#options' => drupal_map_assoc(array(t('On Demand 30 minutes'), t('On Demand 1 hour'), t('3 Month'), t('All of the above'))),
      '#default_value' => t('All of the above'),
  );
  $value_mtype = isset($form_state['values']['m_type']) ? $form_state['values']['m_type'] : 'student';
  $value_volunteer = ($value_mtype =='professional')? '1' : '0' ;
  $form['account']['volunteer'] = array(
  		//'#title' => t('Want To Be A Volunteer Mentor'),
  		'#type' => 'select',
  		'#options' => array(0 => t('No'),
  				1 => t('Yes'),
  		),
  		//'#empty_option' => '--Want To Be A Volunteer--',
  		'#prefix' => '<div id="dropdown_volunteer_default">',
  		'#suffix' => '</div>',
  		'#default_value' => $value_volunteer,
  		//'#name' => 'Expected response time',
  );
  $form['account']['mentoring_terms'] = array(
  		'#type' => 'checkbox',
  		//'#required' => TRUE,
  		'#title' =>  t(''),
  		//'#default_value' => isset($values['m_type']) ? $values['m_type'] : NULL,
  		'#element_validate' => array('element_validate_checked'),
  );
}
function element_validate_checked($element, $form_state) {
	if (!$form_state['values']['mentoring_terms']) {
		form_error($element, t('Please accept mentoring agreement.'));
	}
}	

 function mentor_fields_ajax_callback($form, $form_state) {
    return $form['account']['fieldOfSpecialization'];
}

/*function country_ajax_callback($form, $form_state) {
	$form['account']['country_others']['#hidden'] = true;
	 return $form['account']['country_others'];
}*/
function state_ajax_callback($form, $form_state) {
	//$form['account']['country_others']['#hidden'] = true;
	return $form['account']['cityUSA'];
}
//Ajax for High School Country
function state_ajax_callback_school($form, $form_state) {
  //$form['account']['country_others']['#hidden'] = true;
  return $form['account']['cityUSASchool'];
}
function mtype_ajax_callback($form, $form_state) {
	//$form['account']['country_others']['#hidden'] = true;
	return $form['account']['volunteer'];
}

function mentor_fields_specialization_dropdown_options($key = '') {
	$entries = db_query("SELECT scid, name FROM {specialization_subcategory} WHERE specialization_category_id = $key");

  $options = array();
  foreach($entries as $record)
  {
    $options[$record->scid] =$record->name;
  }
  return $options;
}

function mentor_fields_form_submit($form_state, $uid) {
try {
	  
	  $selected_spec = array();
	  $selected_aom = array();
	  $specialization = NULL;
	  $entries = '';
	  $fos = NULL;
	  /*$fos = $form_state['values']['fieldOfStudy'];
	   if(isset($form_state['values']['fieldOfSpecialization'])) {
	   $selected_spec = array_filter($form_state['values']['fieldOfSpecialization']);
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
	   $entries = db_query("SELECT name FROM {specialization_subcategory} WHERE specialization_category_id = $fos");
	   }
	   foreach($entries as $record) {
	   $specialization .= $record->name . ', ';
	   }
	   $specialization = substr($specialization, 0, (strlen($specialization) - 2));
	   }*/
	  $mentoring_area = '';
	  if(isset($form_state['values']['areaofmentoring'])) {
	  	$selected_aom = array_filter($form_state['values']['areaofmentoring']);
	  	if(!empty($selected_aom)) {
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
	  	//drupal_set_message('<pre>'.print_r($selected_aom,true).'</pre>');
	  	if(!empty($selected_aom) && isset($selected_aom[1]) && $selected_aom[1] == 1){
	  		$fos = $form_state['values']['fieldOfStudy'];
	  		//drupal_set_message('<pre>'.print_r($fos,true).'</pre>');
	  		if(isset($form_state['values']['fieldOfSpecialization'])) {
          $selected_spec = array_filter($form_state['values']['fieldOfSpecialization']);
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
	  				$entries = db_query("SELECT name FROM {specialization_subcategory} WHERE specialization_category_id = $fos");
	  			}
	  			foreach($entries as $record) {
	  				$specialization .= $record->name . ', ';
	  			}
	  			$specialization = substr($specialization, 0, (strlen($specialization) - 2));
	  		}
	  	}
	  }
		
		$birthDate = $form_state['values']['bday'];		
		
    $year_of_school;
    if($form_state['values']['m_type'] == 'professional'){
      if(isset($form_state['values']['yearOfSchool']) ) {
        $year_of_school = /*1980*/date('Y', strtotime("-35 years", time())) + $form_state['values']['yearOfSchool'];
      }
    }
    else{
      if(isset($form_state['values']['expectedYearOfSchool'])) {
        $year_of_school = date('Y', time()) + $form_state['values']['expectedYearOfSchool'];
      }
    }
    $years_of_exp = 0;
    if($form_state['values']['m_type'] == 'professional') {
      $years_of_exp = $form_state['values']['yearsOfExp'];
    }
    $year_of_highschool = 0;
    if(isset($form_state['values']['yearOfHighSchool']) ) {
        $year_of_highschool = /*1980*/date('Y', strtotime("-35 years", time())) + $form_state['values']['yearOfHighSchool'];
    }
		
		$nid = db_insert('mentor')
		->fields(array(
			'mid' => $uid,
			'first_name' => $form_state['values']['fname'],
			'last_name' => ($form_state['values']['lname'] != 'Last name ')?$form_state['values']['lname']:'',
			'birthday' => $birthDate['day'],
			'birthmonth' => $birthDate['month'],
			'birthyear' => $birthDate['year'],
			'gender' => $form_state['values']['gender'],
			'country' => $form_state['values']['country'],
			'state' => $form_state['values']['state'],
			'city' => $form_state['values']['city'],
			'zipcode' => $form_state['values']['zcode'],
			'mobile' => ($form_state['values']['mobile'] != 'Mobile ')?$form_state['values']['mobile']:NULL,
			'skype_id' => ($form_state['values']['skype_id'] != 'Skype Id ')?$form_state['values']['skype_id']:'',
			'userid' => $uid,
			'employer' => ($form_state['values']['employer'] != 'Employer *')?$form_state['values']['employer']:'',
			'title' => ($form_state['values']['title'] != 'Job Title *')?$form_state['values']['title']:'',
			'years_of_exp' => $years_of_exp,
			'linked_in_profile' => ($form_state['values']['linkedInProfile'] !='Linkedin Profile ')?$form_state['values']['linkedInProfile']:'',
			'last_school_attended' => ($form_state['values']['lastSchoolAttended'] != 'Last School Attended *')?$form_state['values']['lastSchoolAttended']:'',
			'school_attending' => ($form_state['values']['schoolAttending'] != 'School Attending *')?$form_state['values']['schoolAttending']:'',
			'year_of_school' => $year_of_school,
			'mentoring_motivation' => $form_state['values']['motivation'],
      'transfer_or_highschool' => $form_state['values']['transfer_highschool'],
      'highschool' => ($form_state['values']['highSchoolName'] != 'High School Name')?$form_state['values']['highSchoolName']:'',
      'year_of_highschool' => (isset($year_of_highschool))?$year_of_highschool:NULL,
      'country_highschool' => $form_state['values']['countrySchool'],
      'state_highschool' => $form_state['values']['stateSchool'],
      'city_highschool' => $form_state['values']['citySchool'],
			'about_me' => ($form_state['values']['about_me'] != 'About myself & What motivates you to be a mentor? ')?$form_state['values']['about_me']:'',
      'other_colleges_accepted_at' => $form_state['values']['other_colleges_accepted_at'],
      'fb_uname' => $form_state['values']['fb_uname'],
      'available_time' => $form_state['values']['available_time'],
			'response_time' => ($form_state['values']['response_time'] != "--Select--")?$form_state['values']['response_time']:'',
			//'hobbies' => $general_details['hobby'],
			'currently_accept_mentee' => 'N',
			'fos_id' => $fos,
			//'fos_sub_id' => $academic_details['fieldOfSpecialization'],
			'degree_id' => $form_state['values']['degree'],
			'mentor_type' => $form_state['values']['m_type'],
			'specialization'=> $specialization,
			'area_of_mentoring'=>$mentoring_area,
			'college_email' => ($form_state['values']['collegeemail'] != 'College E-mail Address *')?$form_state['values']['collegeemail']:'',
			'work_email' => ($form_state['values']['workemail'] !='Work E-mail Address *')?$form_state['values']['workemail']:'',
			'engagement_model_with_mentee' => $form_state['values']['engagement_model_with_mentee'],
			'volunteer' => $form_state['values']['volunteer'],
		))
		->execute();
		
    	foreach($selected_aom as $key => $value) {
			db_insert('mentor_aom')
				->fields(array(
					'mentor_id' => $uid,
					'aom_id' => $key,
			))
			->execute();			
		}
		
		foreach($selected_spec as $key => $value) {
			db_insert('mentor_specialization')
				->fields(array(
					'mentor_id' => $uid,
					'type' => $key,
			))
			->execute();
		}

    //Change roles based on Mentor type - Professional or Student
    $queryRole = db_select('users_roles', 'ur');
    $queryRole->condition('ur.uid', $uid, '=');
    $queryRole->fields('ur');
    $resultRole = $queryRole->execute();
    if($form_state['values']['m_type'] == 'professional'){
      $rid = '9';
    } else if($form_state['values']['m_type'] == 'student'){
      $rid = '10';
    } else{
      $rid = '4';
    }
    //Updating roles in table
    $role_updation = db_update('users_roles')
      ->fields(array(
        'rid' => $rid,
      ))
      ->condition('uid', $uid, '=')
      ->execute();
		$query = db_select('users', 'u'); 
		$query->condition('u.uid', $uid, '=');
		$query->fields('u', array('picture'));
		$result = $query->execute();
		$picture = 0;
		if($record = $result->fetchAssoc()) {
			$picture = $record['picture'];
		}
		
		$account = array();
		$account['uid'] = $uid;
		$account['status'] = 1;
		if($picture == 0) {
			if($form_state['values']['gender'] == 0) {
				$account['picture'] = 46;
			} else {
				$account['picture'] = 44;
			}
		}
		$success = drupal_write_record('users', $account, 'uid');
		
		$query = db_select('user_activation', 'ua'); 
		$query->condition('ua.uid', $uid, '=');
		$query->fields('ua', array('uid', 'activated'));
		$result = $query->execute();	
		
		$activated = 'N';
		if(	$record = $result->fetchAssoc()) {
			$activated = $record['activated'];
		}
				
    if($activated == 'N'){
      drupal_set_message(t("<p style='color:green; margin:0px !important;'>!activation_text</p>",
      array(
        '!activation_text' => '<strong>The user, '.$form_state['values']['fname'] . (($form_state['values']['lname'] != 'Last name ') ? ' ' . $form_state['values']['lname'] : '' ) .', has been registered successfully, but your account has not yet been verified. Please click on the link in the email sent to your email address from SkoolMentor to activate your account. Without account activation, mentors and mentees cannot connect with each other.</strong>',
      )), 'success');
      //drupal_set_message('The user, '.$form_state['values']['fname'] . (($form_state['values']['lname'] != 'Last name ') ? ' ' . $form_state['values']['lname'] : '' ) .', has been registered successfully, but your account has not yet been verified. Please click on the link sent to your e-mail Address to activate your account');
      //drupal_goto('node/1');
    } else {
      drupal_set_message('The user, '.$form_state['values']['fname'] . ' ' . (($form_state['values']['lname'] != 'Last name ') ? ' ' . $form_state['values']['lname'] : '' ) .', has been registered successfully.');
      //mentoringcommon_login_submit($form, $form_state);
    }
		//drupal_goto('mentoring/login');
	} catch (Exception $e) {
	    watchdog_exception('user', $e);
	    throw $e;
	}
}

function _get_user_notification_count($uid) {
	if(!isset($uid))
		return;
	$user = user_load($uid);
 	$roles = $user->roles;
 	$role = '';
 	$count = 0;
 	if(!empty($roles)){	 		
	 	foreach($roles as $element) {
	 		if(substr( $element, 0, 6 )  === 'mentee') {
	 			$role = 'mentee';
	 			break;
	 		} else if(substr( $element, 0, 6 ) === 'mentor') {
	 			$role = 'mentor';
	 			break;
	 		}
	 	}
	 	
	 	$query = db_select('connections', 'c');   
		$query->join('mentor', 'mr', 'mr.mid = c.mentor_id');
	    $query->join('mentee', 'm', 'm.mid = c.mentee_id');
		if($role === 'mentee') {
			$query->join('users', 'u', 'u.uid = mr.mid');
			$query->condition('m.mid', $uid,'=');
			$query->fields('mr');
		} else {
			$query->join('users', 'u', 'u.uid = m.mid');
			$query->condition('mr.mid', $uid,'=');
			$query->fields('m');
		}
		
		$query->fields('c')
			->fields('u', array('picture'));
		$query->addField('c', 'status', 'connection_status');
		$result = $query->execute();
		foreach($result as $record) {
			if($role == 'mentee' && $record->connection_status == 'Payment Pending')
				$count++;
			else if($role == 'mentor' && $record->connection_status == 'Pending') {
				$count++;
			}
			else if($role == 'mentee' && $record->connection_status == 'Decline') {
				$count++;
			}
		}
		
 	}	
	return $count;
}
