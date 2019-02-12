<?php

function menteeprofile_recommendation_form($form, &$form_state, $account) {
	$uid;
	if(isset($_SESSION['user']) && $_SESSION['user']->uid == $account->uid) {
		$uid = $_SESSION['user']->uid;
	} else {
		drupal_goto();
	}	
	
	$query = db_select('mentee', 'm');
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
	    $account->school_name = $record['school_name'];
	    $account->yearOfSchool = $record['year_of_school'];
	    $account->college_name = $record['college_name'];
	    $account->year_of_intended_transfer = $record['year_of_intended_transfer'];
	    $account->mentee_type = $record['mentee_type'];
	    $account->state = $record['state'];
	    $account->city = $record['city'];
	    $account->mentoring_request = $record['mentoring_request'];
	    $account->mentoring_request_title = $record['mentoring_request_title'];
	    $account->hobbies = $record['hobbies'];
	    $account->area_of_mentoring = $record['area_of_mentoring'];
	    $account->fos_id = $record['fos_id'];
	}
	
	$area_mentee = $account->area_of_mentoring;
	$array_area_mentee = 0;
	$array_area_mentee = explode(', ',$area_mentee);
	//To fill zero in Null values
	$index = 0;
	for($index=0; $index<8; $index++) {
		if($array_area_mentee[$index] == NULL){
			$array_area_mentee[$index] = 0;
		}
	}

	if($account->fos_id != NULL && $account->fos_id != 9 && $account->fos_id != 10){
		$query = db_select('mentor', 'm');
	    $query->leftJoin('specialization_category', 'sc', 'sc.cid = m.fos_id');
	    //$query->join('mentor_specialization', 'ms', 'ms.mentor_id = m.mid');
		//$query->join('specialization_subcategory', 'ssc', 'ssc.scid = ms.type');
		$query->join('education_qualification', 'e', 'e.eid = m.degree_id');   
		$query->join('users', 'u', 'u.uid = m.mid');

		$or = db_or();
		
		$query1 = db_select('mentee_specialization', 'ms');
		$query1->condition('ms.mentee_id', $uid,'=');	   
		$query1->fields('ms');	   
		$result1 = $query1->execute();

		$specialization = array();
		$query_sc = "SELECT name FROM {specialization_subcategory} WHERE scid =";
		$max = $result1->rowCount();
		
		$isSpecFound = FALSE;
		foreach ($result1 as $fos) {
			$isSpecFound = TRUE;
			$query_sc .= $fos->spec_id;
			
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
						  ':area_0' => '%'.db_like($array_area_mentee[0]).'%',
						  ':area_1' => '%'.db_like($array_area_mentee[1]).'%',
						  ':area_2' => '%'.db_like($array_area_mentee[2]).'%',
						  ':area_3' => '%'.db_like($array_area_mentee[3]).'%',
						  ':area_4' => '%'.db_like($array_area_mentee[4]).'%',
						  ':area_5' => '%'.db_like($array_area_mentee[5]).'%',
						  ':area_6' => '%'.db_like($array_area_mentee[6]).'%',
						  ':area_7' => '%'.db_like($array_area_mentee[7]).'%',
						));
		$query->condition($or);

		$query->leftJoin('connections', 'c', 'c.mentor_id = m.mid AND c.mentee_id ='.$uid);
		//$query = $query->extend('PagerDefault')->limit(2);              //10 results per page
		//$query->extend('TableSort')        //Sorting Extender
		//->orderByHeader($header);	   
		$query->fields('m')
			//->fields('c', array('cid'))
			->fields('u', array('picture'))
			->fields('c', array('cid', 'status'))
			//->fields('ssc', array('name'))
			->fields('e', array('name'));
		//$query->addField('ssc', 'name', 'subcategory_name');
		$query->addField('e', 'name', 'edu_qualification');
		$results = $query->execute();

		$rows = array();   
		foreach ($results as $mentor) {	
			$query = db_select('user_activation', 'ua'); 
			$query->condition('ua.uid', $mentor->mid, '=');
			$query->fields('ua', array('uid', 'activated', 'activation_code'));
			$result = $query->execute();	

			$activated = '';
			if(	$record = $result->fetchAssoc()) {
				$activated = $record['activated'];
			} 
			if($activated != 'Y')
				continue;     

		    $rows[$mentor->mid] = array(
		    	'last_name' => ($mentor->last_name != '') ? $mentor->last_name[0].'.' : '',
		    	'mid' => $mentor->mid,
		    	'picture' => $mentor->picture,
		    	'first_name' => $mentor->first_name,
		    	'edu_qualification' => $mentor->edu_qualification,
		    	'area_mentoring' => $mentor->area_of_mentoring,
		    	'subcategory_name' => $mentor->specialization,
		    	'state' => $mentor->state,
		    	'city'=> $mentor->city,
		    	'connection_id' => isset($mentor->cid) ? $mentor->cid : 0,
		    	'last_school_attended' => $mentor->last_school_attended,
		    	'mentor_type' => $mentor->mentor_type,
		    	'school_attending' => $mentor->school_attending,
		    	'connection_status' => isset($mentor->status) ? $mentor->status : '',
		    	'accept_mentee' => $mentor->accept_mentee,	
		    	'volunteer' => $mentor->volunteer,
		    	'engagement_model_with_mentee' => $mentor->engagement_model_with_mentee,
		    );
		}
	}
	
	//$or->condition(db_or()->condition('m.last_school_attended', '%' . db_like($account->school_name) . '%', 'LIKE')->condition('m.school_attending', '%' . db_like($account->school_name) . '%', 'LIKE'));
	//$or->condition('m.state', '%' . db_like($account->state) . '%', 'LIKE');
	//$or->condition('m.city', '%' . db_like($account->city) . '%', 'LIKE');

	$queryOthers = db_select('mentor','mOthers');
	$queryOthers->leftJoin('specialization_category', 'scOthers', 'scOthers.cid = mOthers.fos_id');
    $queryOthers->join('education_qualification', 'eOthers', 'eOthers.eid = mOthers.degree_id');   
	$queryOthers->join('users', 'uOthers', 'uOthers.uid = mOthers.mid');
	
	if($array_area_mentee[0] != 'College major and activities advising'){
		
		$queryOthers->where(('(mOthers.area_of_mentoring LIKE :area_0) OR 
						  (mOthers.area_of_mentoring LIKE :area_1) OR 
						  (mOthers.area_of_mentoring LIKE :area_2) OR 
						  (mOthers.area_of_mentoring LIKE :area_3) OR 
						  (mOthers.area_of_mentoring LIKE :area_4) OR 
						  (mOthers.area_of_mentoring LIKE :area_5) OR
						  (mOthers.area_of_mentoring LIKE :area_6) OR
						  (mOthers.area_of_mentoring LIKE :area_7)'
						),array(
						  ':area_0' => '%'.db_like($array_area_mentee[0]).'%',
						  ':area_1' => '%'.db_like($array_area_mentee[1]).'%',
						  ':area_2' => '%'.db_like($array_area_mentee[2]).'%',
						  ':area_3' => '%'.db_like($array_area_mentee[3]).'%',
						  ':area_4' => '%'.db_like($array_area_mentee[4]).'%',
						  ':area_5' => '%'.db_like($array_area_mentee[5]).'%',
						  ':area_6' => '%'.db_like($array_area_mentee[6]).'%',
						  ':area_7' => '%'.db_like($array_area_mentee[7]).'%',
						));
	} else if($array_area_mentee[0] == 'College major and activities advising'){

		$queryOthers->where(('(mOthers.area_of_mentoring LIKE :area_1) OR 
						  (mOthers.area_of_mentoring LIKE :area_2) OR 
						  (mOthers.area_of_mentoring LIKE :area_3) OR 
						  (mOthers.area_of_mentoring LIKE :area_4) OR 
						  (mOthers.area_of_mentoring LIKE :area_5) OR
						  (mOthers.area_of_mentoring LIKE :area_6) OR
						  (mOthers.area_of_mentoring LIKE :area_7)'
						),array(
						  ':area_1' => '%'.db_like($array_area_mentee[1]).'%',
						  ':area_2' => '%'.db_like($array_area_mentee[2]).'%',
						  ':area_3' => '%'.db_like($array_area_mentee[3]).'%',
						  ':area_4' => '%'.db_like($array_area_mentee[4]).'%',
						  ':area_5' => '%'.db_like($array_area_mentee[5]).'%',
						  ':area_6' => '%'.db_like($array_area_mentee[6]).'%',
						  ':area_7' => '%'.db_like($array_area_mentee[7]).'%',
						));
	}

	$queryOthers->leftJoin('connections', 'cOthers', 'cOthers.mentor_id = mOthers.mid AND cOthers.mentee_id ='.$uid);
	
	$queryOthers->fields('mOthers')
	//$query = $query->extend('PagerDefault')->limit(2);              //10 results per page
	//$query->extend('TableSort')        //Sorting Extender
	//->orderByHeader($header);	   
		//->fields('c', array('cid'))
		->fields('uOthers', array('picture'))
		->fields('cOthers', array('cid', 'status'))
		//->fields('ssc', array('name'))
		->fields('eOthers', array('name'));
	//$query->addField('ssc', 'name', 'subcategory_name');
	$queryOthers->addField('eOthers', 'name', 'edu_qualification');
	$resultOthers = $queryOthers->execute();

	foreach ($resultOthers as $mentorOthers) {	
		$query = db_select('user_activation', 'ua'); 
		$query->condition('ua.uid', $mentorOthers->mid, '=');
		$query->fields('ua', array('uid', 'activated', 'activation_code'));
		$result = $query->execute();	

		$activated = '';
		if(	$record = $result->fetchAssoc()) {
			$activated = $record['activated'];
		} 
		if($activated != 'Y' || $mentor->mid == '2519')
			continue;     
	    $rows[$mentorOthers->mid] = array(
	    	'last_name' => ($mentorOthers->last_name != '') ? $mentorOthers->last_name[0].'.' : '',
	    	'mid' => $mentorOthers->mid,
	    	'picture' => $mentorOthers->picture,
	    	'first_name' => $mentorOthers->first_name,
	    	'edu_qualification' => $mentorOthers->edu_qualification,
	    	'area_mentoring' => $mentorOthers->area_of_mentoring,
	    	'subcategory_name' => $mentorOthers->specialization,
	    	'state' => $mentorOthers->state,
	    	'city'=> $mentorOthers->city,
	    	'connection_id' => isset($mentorOthers->cid) ? $mentorOthers->cid : 0,
	    	'last_school_attended' => $mentorOthers->last_school_attended,
	    	'mentor_type' => $mentorOthers->mentor_type,
	    	'school_attending' => $mentorOthers->school_attending,
	    	'connection_status' => isset($mentorOthers->status) ? $mentorOthers->status : '',
	    	'accept_mentee' => $mentorOthers->accept_mentee,	
	    	'volunteer' => $mentorOthers->volunteer,
	    	'engagement_model_with_mentee' => $mentorOthers->engagement_model_with_mentee,
	    );
	}
	
	$queryAlumni = db_select('mentor', 'm');
	$queryAlumni->leftJoin('specialization_category', 'sc', 'sc.cid = m.fos_id');
	$queryAlumni->join('education_qualification', 'e', 'e.eid = m.degree_id');   
	$queryAlumni->join('users', 'u', 'u.uid = m.mid');
	$queryAlumni->leftJoin('connections', 'c', 'c.mentor_id = m.mid AND c.mentee_id ='.$uid);
	if($account->mentee_type == 'highschool'){
		$queryAlumni->where('(m.highschool LIKE :school_name) AND 
							(m.state_highschool = :state_school) AND 
							(m.city_highschool = :city_school) AND 
							(m.transfer_or_highschool = 2)',
							array(
								':school_name' => '%'.db_like($account->school_name).'%',
								':state_school' => $account->state,
								':city_school' => $account->city)
							);
	}else if($account->mentee_type == 'transfer'){
		$queryAlumni->where('(m.highschool LIKE :college_name) AND 
							(m.state_highschool = :state_college) AND 
							(m.city_highschool = :city_college) AND 
							(m.transfer_or_highschool = 1)',
							array(
								':college_name' => '%'.db_like($account->college_name).'%',
								':state_college' => $account->state,
								':city_college' => $account->city)
							);
	}
	$queryAlumni->fields('m')
		->fields('u', array('picture'))
		->fields('c', array('cid', 'status'))
		->fields('e', array('name'));
	$queryAlumni->addField('e', 'name', 'edu_qualification');

	$resultAlumni = $queryAlumni->execute();

	foreach ($resultAlumni as $mentorAlumni) {
		$query = db_select('user_activation', 'ua');
		$query->condition('ua.uid', $mentorAlumni->mid, '=');
		$query->fields('ua', array('uid', 'activated', 'activation_code'));
		$result = $query->execute();

		$activated = '';
		if($record = $result->fetchAssoc()) {
			$activated = $record['activated'];
		}
		if($activated != 'Y' || $mentor->mid == '2519')
			continue;
	    $rowsAlumni[$mentorAlumni->mid] = array(
	    	'last_name' => ($mentorAlumni->last_name != '') ? $mentorAlumni->last_name[0].'.' : '',
	    	'mid' => $mentorAlumni->mid,
	    	'picture' => $mentorAlumni->picture,
	    	'first_name' => $mentorAlumni->first_name,
	    	'edu_qualification' => $mentorAlumni->edu_qualification,
	    	'area_mentoring' => $mentorAlumni->area_of_mentoring,
	    	'subcategory_name' => $mentorAlumni->specialization,
	    	'state' => $mentorAlumni->state,
	    	'city'=> $mentorAlumni->city,
	    	'connection_id' => isset($mentorAlumni->cid) ? $mentorAlumni->cid : 0,
	    	'last_school_attended' => $mentorAlumni->last_school_attended,
	    	'mentor_type' => $mentorAlumni->mentor_type,
	    	'school_attending' => $mentorAlumni->school_attending,
	    	'transfer_or_highschool' => $mentorAlumni->transfer_or_highschool,
	    	'highschool' => $mentorAlumni->highschool,
	    	'state_highschool' => $mentorAlumni->state_highschool,
	    	'city_highschool' => $mentorAlumni->city_highschool,
	    	'connection_status' => isset($mentorAlumni->status) ? $mentorAlumni->status : '',
	    	'accept_mentee' => $mentorAlumni->accept_mentee,
	    	'volunteer' => $mentorAlumni->volunteer,
	    	'engagement_model_with_mentee' => $mentorAlumni->engagement_model_with_mentee,
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
		'#type' => 'container',
		//'#attributes' => array('class' => array('container-inline')),
		'#weight' => -10,
		'#theme' => 'mentee_recommendation_list',
	);

	$form['recommendation']['mentor'] = array(
		'#type' => 'item',
		'#title' => t('Recommendation based on Area'),
		'#markup' => $rows,
	);
	$form['recommendation']['mentor_alumni'] = array(
		'#type' => 'item',
		'#title' => t('Recommendation of Alumni'),
		'#markup' => $rowsAlumni,
	);
	return $form;
}

