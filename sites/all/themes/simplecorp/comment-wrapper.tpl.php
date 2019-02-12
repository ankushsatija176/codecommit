
<section id="comments" class="<?php print $classes; ?>"<?php print $attributes; ?>>


	<?php $mentor = user_load($variables['node']->uid);
	
	foreach ($mentor->roles as $value) {
		if(strpos($value,'mentee') !== false){
			print_r('its coming here');
			drupal_goto('mentee/'.$mentor->uid.'/profile');
		}		
	};
	
	?>
	
	<div>
  		<div class="mentor-profile-usr-pic2">
  		<div class=" mentor-profile-usr-pic3 ">
  		<div class=" mentor-profile-usr-pic4">
  		 <?php 	
  		 if($mentor->picture){
                print theme_image_style(
                array(
                    'style_name' => 'thumbnail',
                    'path' => $mentor->picture->uri,
                    'attributes' => array(
                                        'class' => 'avatar user-pic-div-fit',
                    					'style'=> 'object-fit:fill; height: 150px;'
                                    )            
                    )
                ); 
                }else{
                    echo '<img src="/sites/default/files/styles/thumbnail/public/pictures/picture-571-1395975666.png" />';
                }
       ?>
       </div>
  		<div class="mentor-profile-usr-pic9 ">
  		<?php 			
		   		$rating = mentoringcommon_mentor_rating($variables['node']->uid);  	
		   			
		   		$mentor_details = mentoringcommon_mentor_details($variables['node']->uid);
		   		if($mentor_details->last_school_attended == '')
		   			$school = $mentor_details->school_attending;
		   		else
		   			$school = $mentor_details->last_school_attended;
		  		//drupal_set_message("<pre>".print_r($mentor_details ,true)."</pre>",error);
			$path = drupal_get_path('module', 'fivestar');	
		   	drupal_add_css($path . '/css/fivestar.css');		   	
		   	print render(theme('fivestar_static', array('rating' => $rating['average'], 'stars' => 5, 'tag' => 'userrating',
		   	'widget' => array( 'name' => 'oxygen', 'css' => $path . '/widgets/oxygen/oxygen.css' )))); 
		   		   	
		  	$settings = array(
		   	    'theme' => 'fivestar_rating',
			    'stars' => 5,
			    'autosubmit' => FALSE,
			    'allow_clear' => FALSE,
			    'langcode' => 'und',
			    'text' => 'average', // options are none, average, smart, user, and dual
			    'tag' => 'userrating',
			    'style' => 'average', // options are average, dual, smart, user
			    'widget' => array( 'name' => 'oxygen', 'css' => drupal_get_path('module', 'fivestar') . '/widgets/oxygen/oxygen.css' )
			  );
		   ?>  
		   </div>
		   <div class="mentor-profile-usr-pic7 ">
		   </div>
		   </div> 
		   <?php 
				if(isset($mentor_details->last_name) && user_is_logged_in()){
					$last_name = $mentor_details->last_name;
				} else if(isset($mentor_details->last_name)){
					$last_name = $mentor_details->last_name[0].'.';
				} else{
					$last_name = '';
				}
			?>
		   <div  class="mentor-profile-user-details1"><a href = "/mentor/<?php print $mentor->uid;?>/profile"><?php print $mentor_details->first_name;?> <?php print $last_name; ?></a>
		   <div class="wordwrap mentor-profile-user-details2"><?php print $school?> , Class of <?php print $mentor_details->year_of_school?></div>
		   <div class="wordwrap mentor-profile-user-details2"> Specialization: <?php print $mentor_details->specialization?></div>
		   </div>
		   </div>
		   
  			</div>
	
	
    <?php if ($content['comments'] && $node->type != 'forum'): ?>
    <?php print render($title_prefix); ?>
    
    <!-- <h2 class="title"><?php print t('Comments'); ?></h2>-->
    <?php print render($title_suffix); ?>
    <?php endif; ?>

    <div class="commentlist">
    <?php print render($content['comments']); ?>
    </div>

    <?php 
    if ($content['comment_form']){ 
    	if(isset($_SESSION['user'])) {
	    	$user_id = $_SESSION['user']->uid;
	    	$user = user_load($user_id);
		 	$roles = $user->roles;
		 	if(!empty($roles)){	 		
			 	foreach($roles as $element) {
			 		//drupal_set_message($element);
			 		if(substr( $element, 0, 6 )  === 'mentee') {
			 			$query = db_select('connections', 'c');
						$query->condition('c.mentor_id', $variables['node']->uid,'=');
						$query->condition('c.mentee_id', $user_id,'=');
						//$query->condition('c.status', 'Pending','=');
						$query->fields('c');
						$query->addField('c', 'status', 'connection_status');
						$result = $query->execute();
						
						$notification_array = array();
						foreach($result as $record) {
							if($record->connection_status == 'Confirmed') {
								$rating = mentoringcommon_mentor_rating_by_mentee($variables['node']->uid, $user_id);
								if (empty($rating)) {
								?>
									<h2 class="title comment-form"><?php print t('Add new review'); ?></h2>
		    						<?php print render($content['comment_form']); ?>
		    						
		    					<?php
								}
							}
						}
						$queryPP = db_select('pendingpayment', 'pp');
						$queryPP->condition('pp.mentor_id', $variables['node']->uid, '=');
						$queryPP->condition('pp.mentee_id', $user_id, '=');
						$queryPP->fields('pp');
						$queryPP->addField('pp', 'status', 'connection_status');
						$queryPP->addField('pp', 'last_update_time', 'lastUpdateTime');
						$resultPP = $queryPP->execute();
						$notification_array = array();
						foreach($resultPP as $record) {
							/*$lastUpdateTime = $record->lastUpdateTime;
							$currentDate = date_create(date("Y-m-d H:i:s"));
							$diff = date_diff($lastUpdateTime,$currentDate);*/
							if(isset($record->connection_status)) {
								$rating = mentoringcommon_mentor_rating_by_mentee($variables['node']->uid, $user_id);
								if (empty($rating)) {
								?>
									<h2 class="title comment-form"><?php print t('Add new review'); ?></h2>
		    						<?php print render($content['comment_form']); ?>
		    						
		    					<?php
								}
							}
						}
			 		}
			 	}
		 	}
    	}
    }    	
    ?>  
    
    <script type="text/javascript">
            (function ($) {
                	$('.filter-wrapper').hide();
               		$('div.profile').children(".user-picture").hide();
               		$('div.profile').children("h3").hide();
               		$('div.profile').children(".field-name-field-user-reply").hide();
               		$('#comments').children("h2").each(function(){
						$text = $(this).text();
							if($text == "Add new comment"){
								//$(this).html("Add New Review");
							}
                   		});
					})(jQuery);
				</script>   
</section>