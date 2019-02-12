<?php

function mentorprofile_loadmentor($user_id) {
	$account = new stdClass();
	$uid;
	$role;
	$form['#user'] = mentoringcommon_anonymous_user();
	if(isset($_SESSION['user'])) {  		
  		if($_SESSION['user']->uid == $user_id) {
  			$role = 'full-profile';
  			$uid = $_SESSION['user']->uid;
  		} else {
  			$role = 'authenticated-user';
  			$uid = $user_id;
  		}
  	} else {
  		$uid = $user_id;
  		$role = 'anonymous-user';
  	}
    $connection_condition = 'c.mentor_id = m.mid';    
    $query = db_select('mentor', 'm'); 
    $query->join('users', 'u', 'u.uid = m.mid');
    $query->leftJoin('user_activation', 'ua', 'ua.uid = m.mid'); 
    $query->leftJoin('specialization_category', 'sc', 'sc.cid = m.fos_id');
	//$query->join('specialization_subcategory', 'ssc', 'ssc.scid = m.fos_sub_id');
	$query->leftJoin('education_qualification', 'eq', 'eq.eid = m.degree_id'); //JOIN node with users
	//$query->condition('ua.activated', 'Y', '=');
	//$query->condition('u.uid', '2519', '!=');
	if($role == 'authenticated-user') {		
		$connection_condition .= ' AND c.mentee_id ='.$_SESSION['user']->uid;
	}
	$query->leftJoin('connections', 'c', $connection_condition);
	$query->leftJoin('subscription', 'sub', 'c.subscription_id = sub.sid');
	
	$query->condition('m.userid', $uid,'=');	   
	$query->fields('m')
		->fields('sc', array('name'))
		//->fields('ssc', array('name'))
		->fields('eq', array('name'))
		->fields('u', array('mail'))
		->fields('sub')
		->fields('c', array('cid', 'status','subscription_id'));
	$query->addField('sc', 'name', 'category_name');
	//$query->addField('ssc', 'name', 'subcategory_name');
	$query->addField('eq', 'name', 'degree');
	$result = $query->execute();
	
	$mentor = array();
	if(	$record = $result->fetchAssoc()) {
		if(isset($_SESSION['user']->uid)) {
			$query1 = db_select('users_roles', 'ur');   
	    	$query1->join('role', 'r', 'r.rid = ur.rid');
	    	$query1->condition('ur.uid', $_SESSION['user']->uid,'=');	   
			$query1->fields('r', array('name'))
				->fields('ur', array('rid'))
				->orderBy('rid', 'DESC');
			$role_result = $query1->execute();
			if(	$role_record = $role_result->fetchAssoc()) {
				$account->membership = $role_record['name'];	
			}
		}
		
		$account->uid = $user_id;
		$account->role = $role;
		$account->mid = $record['mid'];
		$account->cid = $record['cid'];
		$account->connection_status = $record['status'];
	    $account->first_name = $record['first_name'];
	    if($record['last_name'] != '')
	    	$account->last_name = $record['last_name'][0].'.';

	    else
	    	$account->last_name = '';

	    $account->email = $record['mail'];
	    $account->birthday = $record['birthday'].'-'.$record['birthmonth'].'-'.$record['birthyear'];
	    $account->gender = $record['gender'];
	    $account->zipcode = $record['zipcode'];
	    $account->mentor_type = $record['mentor_type'];
	    $account->title = $record['title'];
	    $account->state = $record['state'];
	    $account->city = $record['city'];
	    $account->employer = $record['employer'];
	    $account->years_of_exp = $record['years_of_exp'];
	    $account->linkedInProfile = $record['linked_in_profile'];
	    $account->last_school_attended = $record['last_school_attended'];
	    $account->mentoring_motivation = $record['mentoring_motivation'];
	    $account->fos = $record['category_name'];
	    $account->specialization = $record['specialization'];
		//$account->fos_sub = $record['subcategory_name'];
		$account->degree = $record['degree'];
	    $account->school_attending = $record['school_attending'];
	    $account->response_time = ($record['response_time']!="--Select--")?$record['response_time']:'';
	    $account->available_time = $record['available_time'];
	    $account->year_of_school = $record['year_of_school'];
	    $account->highSchoolName = $record['highschool'];
	    $account->year_of_highschool = $record['year_of_highschool'];
	    $account->countrySchool = $record['country_highschool'];
	    $account->stateSchool = $record['state_highschool'];
	    $account->citySchool = $record['city_highschool'];
	    $account->transfer_or_highschool = $record['transfer_or_highschool'];
	    $account->about_me = $record['about_me'];
	    $account->other_colleges_accepted_at = $record['other_colleges_accepted_at'];
	    $account->fb_uname = $record['fb_uname'];
	    $account->mobile = $record['mobile'];
	    $account->skype_id = $record['skype_id'];
	    $account->engagement_model_with_mentee = $record['engagement_model_with_mentee'];
	    $account->alias = $record['alias'];
	    $account->volunteer = $record['volunteer'];
		$account->accept_mentee = $record['accept_mentee'];
	    if($record['volunteer'] == "1")
	    	$account->volunteer_text = "Yes";
	    else
	    	$account->volunteer_text = "No";
	    if($account->role == 'authenticated-user') {
	    	$account->mentee_id = $_SESSION['user']->uid;
	    }
	    if($role != 'anonymous-user' && isset($account->connection_status) && $account->connection_status == 'Confirmed') {
	    	$account->connected = TRUE;
	    } else {
	    	//$account->connection_status = '';
	    	$account->connected = FALSE;
	    }
	}
	
   $query = db_select('mentor_specialization', 'ms');
  	$query->join('specialization_subcategory', 'ssc', 'ssc.scid = ms.type'); //JOIN node with users 
	$query->condition('ms.mentor_id', $account->mid,'=');	   
	$query->fields('ms')//SELECT the fields from user	
	   ->fields('ssc');
	$result = $query->execute();
	
	$fieldOfStudy = '';
  foreach ($result as $fos) {
  	  $fieldOfStudy .= $fos->name . ', '; 
  }
  $account->fos_sub = $fieldOfStudy;
  
  $query = db_select('mentor_aom', 'ma');
  	$query->join('area_mentoring', 'am', 'am.aid = ma.aom_id'); //JOIN node with users 
	$query->condition('ma.mentor_id', $account->uid,'=');	   
	$query->fields('ma')//SELECT the fields from user	
	   ->fields('am');
	$result = $query->execute();	

  $areaOfMentoring = '';
  foreach ($result as $aom) {
  	  $areaOfMentoring .= $aom->name . ', '; 
  }
  $account->area_mentoring = $areaOfMentoring;
  
  return $account;

}


function mentorprofile_recommendation_form($form, &$form_state, $account) {
	$uid;
	if(isset($_SESSION['user']) && $_SESSION['user']->uid == $account->uid) {
		$uid = $_SESSION['user']->uid;
	} else {
		drupal_goto();
	}	
	
	$query = db_select('mentor', 'm');
    $query->join('users', 'u', 'u.uid = m.mid'); 
	$query->condition('m.mid', $uid,'=');	   
	$query->fields('m')
		->fields('u', array('mail'));
	$result = $query->execute();
	
	if(	$record = $result->fetchAssoc()) {
		$account->mid = $record['mid'];
		$account->email = $record['mail'];
	    $account->first_name = $record['first_name'];
	    if($record['last_name'] != '')
	    	$account->last_name = $record['last_name'][0].'.';
	    else
	    	$account->last_name = '';
	    $account->birthday = $record['birthday'].'-'.$record['birthmonth'].'-'.$record['birthyear'];
	    $account->gender = $record['gender'];
	    $account->zipcode = $record['zipcode'];
	    $account->mentor_type = $record['mentor_type'];
	    $account->title = $record['title'];
	    $account->country = $record['country'];
	    $account->state = $record['state'];
	    $account->city = $record['city'];
	    $account->employer = $record['employer'];
	    $account->years_of_exp = $record['years_of_exp'];
	    $account->linkedInProfile = $record['linked_in_profile'];
	    $account->last_school_attended = $record['last_school_attended'];
	    $account->hobbies = $record['hobbies'];
	    $account->mentoring_motivation = $record['mentoring_motivation'];
	    //$account->fos = $record['category_name'];
		//$account->degree = $record['degree'];
	    $account->school_attending = $record['school_attending'];
	    $account->fos_id = $record['fos_id'];
	    $account->area_of_mentoring = $record['area_of_mentoring'];
	    $account->highSchoolName = $record['highschool'];
	    $account->year_of_highschool = $record['year_of_highschool'];
	    $account->countrySchool = $record['country_highschool'];
	    $account->stateSchool = $record['state_highschool'];
	    $account->citySchool = $record['city_highschool'];
	    $account->transfer_or_highschool = $record['transfer_or_highschool'];
	}
	
	$area_mentor = $account->area_of_mentoring;
	$array_area_mentor = 0;
	$array_area_mentor = explode(', ',$area_mentor);
	// Filling zero for NULL values
	$index = 0;
	for($index=0; $index<8; $index++) {
		if($array_area_mentor[$index] == NULL){
			$array_area_mentor[$index] = 0;
		}
	}

	if($account->fos_id != NULL && $account->fos_id != 9 && $account->fos_id != 10){
		$query = db_select('mentee', 'm');   
		$query->join('users', 'u', 'u.uid = m.mid');
	    $query->leftJoin('specialization_category', 'sc', 'sc.cid = m.fos_id');
		//$query->join('mentor_specialization', 'ms', 'ms.mentor_id = m.mid');
		//$query->join('specialization_subcategory', 'ssc', 'ssc.scid = ms.type');
		$query->join('users', 'u', 'u.uid = m.mid');

		$or = db_or();
		
		$query1 = db_select('mentor_specialization', 'ms');
		$query1->condition('ms.mentor_id', $uid,'=');	   
		$query1->fields('ms');	   
		$result1 = $query1->execute();
				  
		$specialization = array();
		$query_sc = "SELECT name FROM {specialization_subcategory} WHERE scid =";
		$max = $result1->rowCount();

		$isSpecFound = FALSE;
		foreach ($result1 as $fos) {
			$isSpecFound = TRUE;
			$query_sc .= $fos->type;

			if($max > 1) {
				$query_sc .= " or scid = ";
				$max = $max - 1;  	
			}
		}
		if ($isSpecFound) {
			$entries = db_query($query_sc);

			$i = 0;
			foreach($entries as $record) {
				$specialization[$i] = $record->name;
				$i = $i + 1;  	
			}
			$max = count($specialization);

			if($max > 1) {
				$or_inner = db_or();
				for($i = 0; $i < $max; $i++) {
					$or_inner->condition('m.specialization', '%' . db_like($specialization[$i]) . '%', 'LIKE');
				}
				$or->condition($or_inner);		
			} else {
				$or->condition('m.specialization', '%' . db_like($specialization[0]) . '%', 'LIKE');	
			}
		}

		$query->where(('((m.area_of_mentoring LIKE :area_0) OR 
					  	(m.area_of_mentoring LIKE :area_1) OR 
						(m.area_of_mentoring LIKE :area_2) OR 
						(m.area_of_mentoring LIKE :area_3) OR 
						(m.area_of_mentoring LIKE :area_4) OR 
						(m.area_of_mentoring LIKE :area_5) OR
						(m.area_of_mentoring LIKE :area_6) OR
						(m.area_of_mentoring LIKE :area_7)) AND m.fos_id='.$account->fos_id
						),array(
						  ':area_0' => '%'.db_like($array_area_mentor[0]).'%',
						  ':area_1' => '%'.db_like($array_area_mentor[1]).'%',
						  ':area_2' => '%'.db_like($array_area_mentor[2]).'%',
						  ':area_3' => '%'.db_like($array_area_mentor[3]).'%',
						  ':area_4' => '%'.db_like($array_area_mentor[4]).'%',
						  ':area_5' => '%'.db_like($array_area_mentor[5]).'%',
						  ':area_6' => '%'.db_like($array_area_mentor[6]).'%',
						  ':area_7' => '%'.db_like($array_area_mentor[7]).'%',
						));
		$query->condition($or);

		$query->leftJoin('connections', 'c', 'c.mentee_id = m.mid AND c.mentor_id ='.$uid);    
	    //$query = $query->extend('PagerDefault')->limit(2);              //10 results per page
		//$query->extend('TableSort')        //Sorting Extender
		//->orderByHeader($header);	   
		$query->fields('m')
			//->fields('c', array('cid'))
			->fields('u', array('picture'))
			->fields('c', array('cid', 'status'));

		$results = $query->execute();
		
		$rows = array();   
		foreach ($results as $mentee) {	  
			$query = db_select('user_activation', 'ua'); 
			$query->condition('ua.uid', $mentee->mid, '=');
			$query->fields('ua', array('uid', 'activated', 'activation_code'));
			$result = $query->execute();	
			
			$activated = '';
			if(	$record = $result->fetchAssoc()) {
				$activated = $record['activated'];
			} 
			if($activated != 'Y')
				continue; 
		    $rows[$mentee->mid] = array(
		    	'last_name' => ($mentee->last_name != '') ? $mentee->last_name[0].'.' : '',
		    	'mid' => $mentee->mid,
		    	'picture' => $mentee->picture,
		    	'first_name' => $mentee->first_name,
		    	'area_mentoring' => $mentee->area_of_mentoring,
		    	'subcategory_name' => $mentee->specialization,
		    	'state' => $mentee->state,
		    	'city'=> $mentee->city,
		    	'connection_id'=>$mentee->cid
		    );
		}
	}

	//$or->condition('m.school_name', '%' . db_like($account->school_attending) . '%', 'LIKE');
	//$or->condition('m.school_name', '%' . db_like($account->last_school_attended) . '%', 'LIKE');
	//$or->condition('m.state', '%' . db_like($account->state) . '%', 'LIKE');
	//$or->condition('m.city', '%' . db_like($account->city) . '%', 'LIKE');

	//To add all other mentees for areas College Major and activities advising

	$queryOthers = db_select('mentee','mOthers');
	$queryOthers->leftJoin('specialization_category', 'scOthers', 'scOthers.cid = mOthers.fos_id');
    $queryOthers->join('users', 'uOthers', 'uOthers.uid = mOthers.mid');

	if($array_area_mentor[0] != 'College major and activities advising'){

		$queryOthers->where(('(mOthers.area_of_mentoring LIKE :area_0) OR 
						  (mOthers.area_of_mentoring LIKE :area_1) OR 
						  (mOthers.area_of_mentoring LIKE :area_2) OR 
						  (mOthers.area_of_mentoring LIKE :area_3) OR 
						  (mOthers.area_of_mentoring LIKE :area_4) OR 
						  (mOthers.area_of_mentoring LIKE :area_5) OR
						  (mOthers.area_of_mentoring LIKE :area_6) OR
						  (mOthers.area_of_mentoring LIKE :area_7)'
						),array(
						  ':area_0' => '%'.db_like($array_area_mentor[0]).'%',
						  ':area_1' => '%'.db_like($array_area_mentor[1]).'%',
						  ':area_2' => '%'.db_like($array_area_mentor[2]).'%',
						  ':area_3' => '%'.db_like($array_area_mentor[3]).'%',
						  ':area_4' => '%'.db_like($array_area_mentor[4]).'%',
						  ':area_5' => '%'.db_like($array_area_mentor[5]).'%',
						  ':area_6' => '%'.db_like($array_area_mentor[6]).'%',
						  ':area_7' => '%'.db_like($array_area_mentor[7]).'%',
						));
	} else if($array_area_mentor[0] == 'College major and activities advising'){

		$queryOthers->where(('(mOthers.area_of_mentoring LIKE :area_1) OR 
						  (mOthers.area_of_mentoring LIKE :area_2) OR 
						  (mOthers.area_of_mentoring LIKE :area_3) OR 
						  (mOthers.area_of_mentoring LIKE :area_4) OR 
						  (mOthers.area_of_mentoring LIKE :area_5) OR
						  (mOthers.area_of_mentoring LIKE :area_6) OR
						  (mOthers.area_of_mentoring LIKE :area_7)'
						),array(
						  ':area_1' => '%'.db_like($array_area_mentor[1]).'%',
						  ':area_2' => '%'.db_like($array_area_mentor[2]).'%',
						  ':area_3' => '%'.db_like($array_area_mentor[3]).'%',
						  ':area_4' => '%'.db_like($array_area_mentor[4]).'%',
						  ':area_5' => '%'.db_like($array_area_mentor[5]).'%',
						  ':area_6' => '%'.db_like($array_area_mentor[6]).'%',
						  ':area_7' => '%'.db_like($array_area_mentor[7]).'%',
						));
	}
	
	$queryOthers->leftJoin('connections', 'cOthers', 'cOthers.mentee_id = mOthers.mid AND cOthers.mentor_id ='.$uid);
	
	$queryOthers->fields('mOthers')
	//$query = $query->extend('PagerDefault')->limit(2);              //10 results per page
	//$query->extend('TableSort')        //Sorting Extender
	//->orderByHeader($header);	   
		//->fields('c', array('cid'))
		->fields('uOthers', array('picture'))
		->fields('cOthers', array('cid', 'status'));
		//->fields('ssc', array('name'))

	$resultOthers = $queryOthers->execute();

	foreach ($resultOthers as $menteeOthers) {	
		$query = db_select('user_activation', 'ua'); 
		$query->condition('ua.uid', $menteeOthers->mid, '=');
		$query->fields('ua', array('uid', 'activated', 'activation_code'));
		$result = $query->execute();	
		
		$activated = '';
		if(	$record = $result->fetchAssoc()) {
			$activated = $record['activated'];
		} 
		if($activated != 'Y')
			continue; 
	    $rows[$menteeOthers->mid] = array(
	    	'last_name' => ($menteeOthers->last_name != '') ? $menteeOthers->last_name[0].'.' : '',
	    	'mid' => $menteeOthers->mid,
	    	'picture' => $menteeOthers->picture,
	    	'first_name' => $menteeOthers->first_name,
	    	'area_mentoring' => $menteeOthers->area_of_mentoring,
	    	'subcategory_name' => $menteeOthers->specialization,
	    	'state' => $menteeOthers->state,
	    	'city'=> $menteeOthers->city,
	    	'connection_id'=>$menteeOthers->cid
	    );
	}

	$queryJunior = db_select('mentee', 'm');   
	$queryJunior->join('users', 'u', 'u.uid = m.mid');
	$queryJunior->leftJoin('specialization_category', 'sc', 'sc.cid = m.fos_id');
	$queryJunior->join('users', 'u', 'u.uid = m.mid');
	if(!empty($account->highSchoolName)){
		if(!empty($account->stateSchool) && !empty($account->citySchool)){
			if($account->transfer_or_highschool == 2){
				$queryJunior->where('(m.school_name LIKE :school_name) AND 
							(m.state = :state_school) AND 
							(m.city = :city_school) AND 
							(m.mentee_type = :type)',
							array(
								':school_name' => '%'.db_like($account->highSchoolName).'%',
								':state_school' => $account->stateSchool,
								':city_school' => $account->citySchool,
								':type' => "highschool")
							);
			}else if($account->transfer_or_highschool == 1){
				$queryJunior->where('(m.college_name LIKE :college_name) AND 
							(m.state = :state_college) AND 
							(m.city = :city_college) AND 
							(m.mentee_type = :type)',
							array(
								':college_name' => '%'.db_like($account->highSchoolName).'%',
								':state_college' => $account->stateSchool,
								':city_college' => $account->citySchool,
								':type' => "transfer")
							);
			}
		}
	}
	$queryJunior->leftJoin('connections', 'c', 'c.mentee_id = m.mid AND c.mentor_id ='.$uid);
	$queryJunior->fields('m')
		->fields('u', array('picture'))
		->fields('c', array('cid', 'status'));

	$resultJunior = $queryJunior->execute();

	foreach ($resultJunior as $menteeJunior) {	
		$query = db_select('user_activation', 'ua'); 
		$query->condition('ua.uid', $menteeJunior->mid, '=');
		$query->fields('ua', array('uid', 'activated', 'activation_code'));
		$result = $query->execute();	
		$activated = '';
		if(	$record = $result->fetchAssoc()) {
			$activated = $record['activated'];
		}
		if($activated != 'Y')
			continue; 
		$rowsJunior[$menteeJunior->mid] = array(
			'last_name' => ($menteeJunior->last_name != '') ? $menteeJunior->last_name[0].'.' : '',
			'mid' => $menteeJunior->mid,
			'picture' => $menteeJunior->picture,
			'first_name' => $menteeJunior->first_name,
			'area_mentoring' => $menteeJunior->area_of_mentoring,
			'subcategory_name' => $menteeJunior->specialization,
			'state' => $menteeJunior->state,
			'city'=> $menteeJunior->city,
			'connection_id'=>$menteeJunior->cid
		);
	}

	        
	/*$html = theme('mentee_recommendation_list', array('rows' => $rows));
	 
	//Append pager
	$html .= theme('pager',
	            array(
	                'tags' => array()
	            )
	        );
	         
	return ($html);*/

	$form['recommendation'] = array(
	    '#type'   => 'container',    
	    //'#attributes' => array('class' => array('container-inline')),
	    '#weight' => -10,
	    '#theme' => 'mentorprofile_recommendation_list',	    
  	);
  	
  	$form['recommendation']['mentee'] = array(
	    '#type' => 'item',
	    '#title' => t('Recommendation Based On Area'),
	    '#markup' => $rows,
	);
	$form['recommendation']['menteeJunior'] = array(
	    '#type' => 'item',
	    '#title' => t('Recommendation Based On School'),
	    '#markup' => $rowsJunior,
	);
	return $form;
}

