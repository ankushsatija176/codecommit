<?php


 function mentor_profile($form, &$form_state, $account, $category) {
 	
    $uid = $_SESSION['user']->uid;
    $query = db_select('mentor', 'm');   
	//$query->join('specialization_subcategory', 'ssc', 'ssc.id = m.fos_id'); //JOIN node with users
	$query->condition('m.userid', $uid,'=');	   
	$query->fields('m');
	$result = $query->execute();
	
	$mentor = array();
	if(	$record = $result->fetchAssoc()) {
		$account->mid = $record['mid'];
	    $account->first_name = $record['first_name'];
	    $account->last_name = $record['last_name'];
	    $account->gender = $record['gender'];
	    $account->zipcode = $record['zipcode'];
	    $account->mentor_type = $record['mentor_type'];
	    $account->title = $record['title'];
	    $account->years_of_exp = $record['years_of_exp'];
	    $account->linkedInProfile = $record['linked_in_profile'];
	    $account->last_school_attended = $record['last_school_attended'];
	    //$account->hobbies = $record['hobbies'];
	    $account->mentoring_motivation = $record['mentoring_motivation'];
	    $account->fos_id = $record['fos_id'];
		//$account->fos_sub_id = $record['fos_sub_id'];
		$account->degree_id = $record['degree_id'];
	    $account->school_attending = $record['school_attending'];
	}
	
	// During initial form build, add the entity to the form state for use during
	  // form building and processing. During a rebuild, use what is in the form
	  // state.
	  if (!isset($form_state['user'])) {
	    $form_state['user'] = $account;
	  }
	  else {
	    $account = $form_state['user'];
	  }
	  $form['#user'] = $account;
	  
	  if($category == 'edit') {
	  	mentor_update_skill_form($form, $form_state);
	  } else if($category == 'view') {
	  	mentor_view_profile_form($form, $form_state);
	  }
	  $form['actions'] = array('#type' => 'actions');
	  $form['actions']['submit'] = array(
	    '#type' => 'submit',
	    '#value' => t('Update'),
	  );
	  
	  $form['#submit'][] = 'mentor_update_sill_form_submit';

  	return $form;
 }
 
 function mentor_update_skill_form(&$form, &$form_state) {

  // @todo Legacy support. Modules are encouraged to access the entity using
  //   $form_state. Remove in Drupal 8.
  global $user;
  $account = $form['#user'];  
  
  // Account information.
  $form['academic_details'] = array(
    '#type'   => 'container',
    '#weight' => -10,
  );
  $form['academic_details']['details'] = array(
    '#type' => 'fieldset',
    '#title' => t('Academic Details'),
  );
  
  $entries = db_query("SELECT cid, name FROM {specialization_category}");

  $options = array();
  foreach($entries as $record)
  {
    $options[$record->cid] =$record->name;
  }
  
  
  $value_field_of_study = $account->fos_id;  
  
  $form['academic_details']['details']['fieldOfStudy'] = array(
    '#type' => 'select',
    '#title' => t('Field of Study'),
    '#description' => t('Field of study.'),
    '#required' => FALSE,
    '#options' => $options,
    '#default_value' => $value_field_of_study,
    '#ajax' => array(
   'event' => 'change',
        'callback' => 'mentor_ajax_callback',
        'progress' => array(
        'message' => '',
      ),
        'wrapper' => 'dropdown_specialization_replace',
      ),
  );
  
  $spec_options = mentor_specialization_dropdown_options($value_field_of_study);
  
  $spec_ids = db_query("SELECT mentor_id, type FROM {mentor_specialization} where mentor_id = " . $account->mid);

  $mentor_specs = array();
  foreach($spec_ids as $record)
  {
    $mentor_specs[$record->type] =$record->type;
  }
  $form['academic_details']['details']['fieldOfSpecialization'] = array(
    '#type' => 'select',
    '#title' => t('Field of Specialization'),
    '#description' => t('Field of study you are specialized in.'),
    '#required' => FALSE,
    //'#options' => $options,
    '#multiple' => true,
    '#prefix' => '<div id="dropdown_specialization_replace">',
    '#suffix' => '</div>',
    '#options' => $spec_options,
    '#default_value' => $mentor_specs,//isset($form_state['values']['fieldOfSpecialization']) ? $form_state['values']['fieldOfSpecialization'] : '',
  );
  
  $entries = db_query("SELECT eid, name FROM {education_qualification}");

  $options = array();
  foreach($entries as $record)
  {
    $options[$record->eid] =$record->name;
  }
  
  $form['academic_details']['details']['degree'] = array(
    '#title' => t('Degree'),
    '#type' => 'select',
    '#description' => 'Your Qualification',
    '#required' => TRUE,
    '#options' =>  $options ,
    '#default_value' => isset($account->degree_id) ? $account->degree_id : NULL,
  );
     
  return $form;	
  
 }
 
function mentor_update_sill_form_submit($form, &$form_state) {
  $account = $form['#user'];
    $account->mid = $form['#user']->mid;
    $account->userid = $account->uid;
    $account->fos_id = $form_state['values']['fieldOfStudy'];
    $mentor_specs = $form_state['values']['fieldOfSpecialization'];
    $account->degree_id = $form_state['values']['degree'];
    
    $success = drupal_write_record('mentor', $account, 'mid');   
    
      if ($success === FALSE) {      	
        // The query failed - better to abort the save than risk further
        // data loss.
        return FALSE;
      } else {
        $num_deleted = db_delete('mentor_specialization')
		  ->condition('mentor_id', $account->mid)
		  ->execute();
		foreach ($mentor_specs as $key=>$element) {
			$data = array(
			  'mentor_id' => $account->mid,
			  'type' => $element,
			);
			$success = drupal_write_record('mentor_specialization', $data);
			if ($success === FALSE) {      	
		        // The query failed - better to abort the save than risk further
		        // data loss.
		        return FALSE;
			}
		}
      }
  // Clear the page cache because pages can contain usernames and/or profile information:
  cache_clear_all();

  drupal_set_message(t('The changes have been saved.'));
}

