<!-- #page-wrapper -->
<div id="page-wrapper">

    <!-- #page -->
    <div id="page">
        
        <!-- header -->
        <header role="header" class="container clearfix"> 
        	 <?php
	            	drupal_add_css(drupal_get_path('module', 'mentoringcommon') . '/css/common.css', array('group' => CSS_DEFAULT, 'every_page' => TRUE));
	         ?>            
            <!-- #pre-header -->
            <div id="pre-header" style="min-height:40px" class="clearfix">
				
            	<div id="header-left" class="one-third" style="padding-top:0px; margin-bottom:0px"> 
                    
                    <?php if ($logo): ?>
                    <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"> <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" /></a>
                    <?php endif; ?>
             	</div>
             	 <?php
             	 
	                	//drupal_add_css(drupal_get_path('module', 'mentoringcommon') . '/css/login_popup.css', array('group' => CSS_DEFAULT, 'every_page' => TRUE));
						drupal_add_css(drupal_get_path('module', 'mentoringcommon') . '/css/style.css', array('group' => CSS_DEFAULT, 'every_page' => TRUE));
					    //drupal_add_js('http://ajax.googleapis.com/ajax/libs/jquery/1.4.2/jquery.min.js?ver=1.4.2');
					    //drupal_add_js(drupal_get_path('module', 'mentoringcommon') . '/js/login.js'); 
	                ?>  
				<?php if(user_is_logged_in()) :?>

				<?php 
					$uid = $_SESSION['user']->uid;
					$notificationCount= _get_user_notification_count($uid);
					$profileString = '';
					$role2='';
					if(user_is_logged_in()) {
						$role = get_user_role();
						if(substr( $role, 0, 6 ) === 'mentor') {
							$role2="mentee";
							$profileString = 'mentorprofile';
							$userFirstName = db_query('SELECT m.first_name FROM {mentor} m WHERE m.mid = :uid', array(':uid' => $uid))->fetchField();
						} else {
							$role2="mentor";
							$profileString = 'menteeprofile';
							$userFirstName = db_query('SELECT m.first_name FROM {mentee} m WHERE m.mid = :uid', array(':uid' => $uid))->fetchField();
						}
					}
				?>

            	<div>	
            	  <div id = "subscriptionWindow" class="subscription-popup" style = "margin-bottom:8px">
			    			
			     		 	<div class="view view-product-list view-id-product_list view-display-id-block">
			     		 	    <div class="view-content">
			     		 	       <table class="views-table cols-3">
        							 <thead>
     									 <tr>
							                  <th class="views-field views-field-title">
							                  		Engagement Model
							                      </th>
							                  <th class="views-field views-field-display-price">
							            			Price          </th>
							                  <th class="views-field views-field-buyitnowbutton">
							            			Action          </th>
							              </tr>
							    	</thead>
    								<tbody>
								          <tr class="odd views-row-first" style="display: table-row;">
								                  <td class="views-field views-field-title">
								            <span>On Demand Mentoring - 30 Minutes<div class="tooltip" style="display: inline;font-weight: normal;"><img  style="max-width: 20px; vertical-align: middle;" src="/sites/all/themes/simplecorp/images/question.png" alt="Hint" />
							<span><b>On demand 30 minutes mentoring</b> is a mentoring session for 30 minutes only. It requires no commitment beyond the 30 minutes of mentoring by the mentor or the mentee.				
								</span></div></span>          </td>
								                  <td class="views-field views-field-display-price">
								            <span class="uc-price">$25.00</span>          </td>
								                  <td class="views-field views-field-buyitnowbutton">
								                  <a id="ondemand30minsBuyButton" class="accept_button one_click" target="_self" href="/mentee/connection?mentor_id=663,subscription=30mins" onclick="return acceptButton();">Connect</a>
								            </td>
								          </tr>
								          <tr class="odd views-row-mid" style="display: table-row;">
								                  <td class="views-field views-field-title">
								            <span>On Demand Mentoring - 1 Hour <div class="tooltip" style="display: inline;font-weight: normal;"><img  style="max-width: 20px; vertical-align: middle;" src="/sites/all/themes/simplecorp/images/question.png" alt="Hint" />
							<span><b>On demand 1 hour mentoring</b> is a mentoring session for 1 hour only. It requires no commitment beyond the 1 hour of mentoring by the mentor or the mentee.				
								</span></div></span>          </td>
								                  <td class="views-field views-field-display-price">
								            <span class="uc-price">$50.00</span>          </td>
								                  <td class="views-field views-field-buyitnowbutton">
								                  <a id= "ondemandBuyButton" class="accept_button one_click" target="_self" href="/mentee/connection?mentor_id=663,subscription=ondemand" onclick="return acceptButton();">Connect</a>
								            </td>
								          </tr>
								          <tr class="even views-row-last" style="display: table-row;">
								                  <td class="views-field views-field-title">
								            <span>3 Months <div class="tooltip" style="display: inline;font-weight: normal;"><img  style="max-width: 20px; vertical-align: middle;" src="/sites/all/themes/simplecorp/images/question.png" alt="Hint" />
							<span><b>3 months</b> - specifies a total mentoring duration of 3 months with the mentee. Within the 3 month period mentors and mentees  meet for approx 1-2 hours per month on a mutually agreed upon frequency and meeting duration to add up to approx 1-2 hours/month. Eg: mentors and mentees can choose to meet once a week for 25-30 minutes for upto 3 months.</span></div></span></td>
								                  <td class="views-field views-field-display-price">
								            <span class="uc-price">$225.00</span>          </td>
								                  <td class="views-field views-field-buyitnowbutton">
								                  <a id= "threemonthBuyButton" class="accept_button one_click" target="_self" href="/mentee/connection?mentor_id=663,subscription=3month" onclick="return acceptButton();">Connect</a>
								            </td>
								              </tr>
								      </tbody>
					</table>
	   			</div>
	   			<script type="text/javascript">
	   				(function($) {
	   					$(document).ready(function acceptButton() {
		   					$(".one_click").click(function(event){
							    var href=$(this).attr('href');
							    if(typeof href != 'undefined'){
								    var r=confirm('Are you sure? Please choose the model of engagement carefully. Once your connection request is sent to the mentor, you will not be able to change the model of engagement.\nPress OK : to confirm.\nPress CANCEL: to select different engagement model.');
								    if(r==true){
								       window.location = $(this).attr('href');
								       $(this).css("background-color","#B3B8BD");
								       $(this).removeAttr('href');
								       return true;
								    } else{
								    	return false;
								    }
								}
			   				});
		   				});
		   			})(jQuery);
		   			/*}*/
	   			</script>
	   		</div>
			<div id="subscriptionWindowClose" class="form-submit button small round steel_blue" style=" text-align: center; width: 10%; margin-left: 44%; margin-top: 2%;">Close</div>
		</div>	
			       
			<div class="action-tab-div">
				<div id="menu-bar" class="content">
					<ul style="list-style: none;">
						<li style="float:right;">
							<a id="welcomeToSkoolMentor" class="signup_button big fill sign-button-style welcomebutton" style="min-width: 130px;" href="#login-box" >Hi <?php print $userFirstName; ?>
							  	<?php if($notificationCount > 0 ) :?><span class="welcomebuttonbell"><img src="/sites/all/modules/custom/faqs/bell.png.png">
								<div style="position: absolute; width: 40%; top: -20%; right: 10%;">
									<span style="background-color: red; width: 100%; color: rgb(252, 247, 247);text-align: center;padding: 10%;border-radius: 30%;font-size: 10px;"><?php print $notificationCount; ?></span>
								</div>
								</span>
								<?php endif; ?>
							</a>
						</li>
						<li style="float:right;">
							<a id = "resourcesButton" class="button790 signup_button big fill" style="float:right; min-width: 104px;" href="#">Resources</a>
							<ul id="resourcesDropdownContent" class="dropdown-content" >
								<li>
									<a id = "mentorResourcesButton" class="button790 signup_button big fill" style="color:#120A2A; float:right; min-width: 104px;" href="/mentor-resources" >For Mentors</a>
								</li>
								<li>
									<a id = "menteeResourcesButton" class="button790 signup_button big fill" style="color:#120A2A; float:right; min-width: 104px;" href="/mentee-resources" >For Mentees</a>
								</li>
								<li>
									<a id = "faqsButton" class="button790 signup_button big fill" style="color:#120A2A; float:right; min-width: 104px;" href="/faqs" >FAQ</a>
								</li>
							</ul>
						</li>
						<li style="float:right;">
							<a class="button790 signup_button big fill" style="color:#120A2A; float:right; min-width: 104px;" href="/referfriend" >Invite Friends</a>
						</li>
						<li style="float:right;">
							<a id="companyButton" class="button790 signup_button big fill" style="float:right; min-width: 100px;" href="#">Company</a>
							<ul id="companyDropdownContent" class="dropdown-content">
								<li style="">
									<a id="aboutUsButton" class="button790 signup_button big fill" style="color:#120A2A; float:right; min-width: 100px;/* left: 14px; */" href="/about_us">About Us</a>
								</li>
								<li style="">
									<a id="advisorsButton" class="button790 signup_button big fill" style="color:#120A2A; float:right; min-width: 100px;" href="/advisors">Advisors</a>
								</li>
								<li>
									<a id="partnersButton" class="button790 signup_button big fill" style="color:#120A2A; float:right; min-width: 100px;" href="/partners">Partners</a>
								</li>
								<li>
									<a id = "blogsButton" class="button790 signup_button big fill" style="color:#120A2A; float:right; min-width: 100px;" href="/blog" style="" >Blogs</a>
								</li>
							</ul>
						</li>
						<li style="padding-top: 4px; padding-left: 0px; padding-right: 0px;">
							<div class="keyword-search-style"><input class="keyword-search-input-style" id="keywordSearchTextBox" type="text" name="keywordSearch" myattr='/<?php print $role2;?>/searchResult?keyword='>
								<img id="keywordSearchImage" style=" margin: 5px;position: absolute;"  src="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/search-bg.png">
							</div>
						</li>
					</ul>
				</div>
			</div>
		    </div>
		    <div id="w-menu" class="welcome-menu" style="display: block ; padding-left: 10px; border-radius: 15px;">
               	      <a class="signup_button normal fill"  href="/<?php print $profileString;?>/<?php print $_SESSION['user']->uid; ?>/edit" style="color:#120A2A" >View Profile</a> 
                          <a class="signup_button normal fill" href="/<?php print $profileString;?>/<?php print $_SESSION['user']->uid; ?>/connections" style="color:#120A2A" >Connections</a> 
                          <a class="signup_button normal fill" href="/<?php print $profileString;?>/<?php print $_SESSION['user']->uid; ?>/messages"  style="color:#120A2A" >Messages</a> 
                           <a class="signup_button normal fill" href="/<?php print $profileString;?>/<?php print $_SESSION['user']->uid; ?>/notifications"  style="color:#120A2A" >Notifications
                  <?php if($notificationCount > 0 ) :?>        <span class="welcomebuttonbellnoti">
				  			<div style="position: absolute; right: 25%;">
				  			<span style="background-color: red; width: 100%; color: rgb(252, 247, 247);text-align: center;padding: 30%;border-radius: 30%;font-size: 15px;"><?php print $notificationCount;?></span>
				  			</div>
				  		  </span>
				  	<?php endif; ?>	  </a> 
				  	<a class="signup_button normal fill" href="/<?php print $profileString;?>/<?php print $_SESSION['user']->uid; ?>/recommendations"  style="color:#120A2A" >Recommendations</a> 
                           <a class="signup_button normal fill" href="/<?php print $role2;?>/search"  style="color:#120A2A" >Search <?php print $role2;?></a> 
                    <?php if($_SESSION['user']->uid == '2519') :?> <a class="signup_button normal fill" href="/pending_payment"  style="color:#120A2A" >Pending Payment</a> 
                    	<a class="signup_button normal fill" href="/mentor/search"  style="color:#120A2A" >Search Mentor</a> 
                    <?php endif; ?>       
                          <a class="signup_button normal fill" href="/user/logout"><font style="color:#120A2A">Logout</font></a>
			</div>
               	<script type="text/javascript">
               	var queryString = location.search;
               	if( queryString.indexOf("keyword=") >= 0) {
                   	document.getElementById("keywordSearchTextBox").value =  queryString.substring(queryString.indexOf("keyword=")+8).replace("%20", " ");
  					document.getElementById("keywordSearchTextBox").style.color = "black";
				}
               	(function ($) {
                   	$("#subscriptionWindow").hide();
                   	//$("#subscriptionWindow").fadeIn(5000);
                   	$("#subscriptionWindow").find(".even").hide();
                   	$("#subscriptionWindow").find(".odd").hide();
                   	$("#subscriptionWindow").find(".views-row-first").show();
                   	$("#subscriptionWindow").find(".views-row-mid").show();
                   	$("#subscriptionWindow").find(".views-row-last").show();
                   	$("#subscriptionWindowClose").click(function(){
                   		$("#subscriptionWindow").fadeOut(1000);
                       	});
               		$('a.signup_button').click(function(){
						  $(this).toggleClass("bbg");
					});
						$("#keywordSearchTextBox").each(function(){
							if(!this.value){
							this.value = "Keyword Search";
							$(this).css("color","#ABA6A6");
						    }
							var valueText = "Keyword Search";
							$(this).css("font-weight","bold");
							$(this).css("border","1px solid #514B4B");
							$(this).css("border-style","solid");
							$(this).keydown(function(){
						        if(this.value == "Keyword Search") {
						            this.value = "";
						            $(this).css("color","black");
								    $(this).css("font-weight","normal");
								}
						    });

						    $(this).blur(function(){
						        if(this.value == "") {
						            this.value = "Keyword Search";
						            $(this).css("color","#ABA6A6");
								    $(this).css("font-weight","bold");
								}
						    });
						    $(this).keydown(function(event){
							     if(event.which == 13){
										window.location.href = ""+$(this).attr('myattr')+""+$(this).val();
						    	}
						     });
						});
						$("#keywordSearchImage").each(function(){

							$(this).click(function(){
							window.location.href = ""+$("#keywordSearchTextBox").attr('myattr')+""+$("#keywordSearchTextBox").attr('value');
							});
							$(this).mouseover(function(){
								$(this).css('cursor','pointer');
							});
						});
						$('div.welcome-menu').hide();
							$('#welcomeToSkoolMentor').click(function() {
								$('div.welcome-menu').slideToggle(50);
							return false;
						});
						$(document).click(function(event) {
    						if(!$(event.target).closest('#w-menu').length &&
    							!$(event.target).is('#w-menu')) {
        							if($('#w-menu').is(":visible")) {
            							$('#w-menu').hide();
        							}
    						}
						});
					})(jQuery);
				</script>   
            	<?php endif; ?>
                <?php if ($page['header']) :?> 
				<div id="menu-bar" class="action-tab-div container-inline">
					<ul>
						<li style="float: right;">
							<a id = "signInForSkoolMentor" class="signup_button big fill sign-button-style"  href="#login-box" style="color:#120A2A; float: right; min-width: 70px;" >Sign In</a>
						</li>
						<li style="float:right;">
							<a id = "resourcesButton" class="button790 signup_button big fill" style="float:right; min-width: 104px;" href="#">Resources</a>
							<ul id="resourcesDropdownContent" class="dropdown-content" >
								<li>
									<a id = "mentorResourcesButton" class="button790 signup_button big fill" style="color:#120A2A; float:right; min-width: 104px;" href="/mentor-resources" >For Mentors</a>
								</li>
								<li>
									<a id = "menteeResourcesButton" class="button790 signup_button big fill" style="color:#120A2A; float:right; min-width: 104px;" href="/mentee-resources" >For Mentees</a>
								</li>
								<li>
									<a id = "faqsButton" class="button790 signup_button big fill" style="color:#120A2A; float:right; min-width: 104px;" href="/faqs" >FAQ</a>
								</li>
							</ul>
						</li>
						<li style="float: right;">
							<a id = "howItWorksButton" class="button790 signup_button big fill" style="color:#120A2A; float:right; min-width: 107px;" href="#login-box" >How It Works</a>
						</li>
						<li style="float: right;">
							<a id = "tesimonialsButton" class="button790 signup_button big fill" style="color:#120A2A; float:right; min-width: 100px;" href="/testimonials" >Testimonials</a>
						</li>
						<li style="float:right;">
							<a id="companyButton" class="button790 signup_button big fill" style="float:right; min-width: 100px;" href="#">Company</a>
							<ul id="companyDropdownContent" class="dropdown-content">
								<li style="">
									<a id="aboutUsButton" class="button790 signup_button big fill" style="color:#120A2A; float:right; min-width: 100px;/* left: 14px; */" href="/about_us">About Us</a>
								</li>
								<li style="">
									<a id="advisorsButton" class="button790 signup_button big fill" style="color:#120A2A; float:right; min-width: 100px;" href="/advisors">Advisors</a>
								</li>
								<li>
									<a id="partnersButton" class="button790 signup_button big fill" style="color:#120A2A; float:right; min-width: 100px;" href="/partners">Partners</a>
								</li>
								<li>
									<a id = "blogsButton" class="button790 signup_button big fill" style="color:#120A2A; float:right; min-width: 100px;" href="/blog" style="" >Blogs</a>
								</li>
							</ul>
						</li>
                   <!--  <div class="keyword-search-style"><input class="keyword-search-input-style" id="keywordSearchTextBox" type="text" name="keywordSearch" myattr='/mentee/searchResult?keyword='>
                  	 <img id="keywordSearchImage" style=" margin: 5px;position: absolute;" src="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/search-bg.png">
                  	 </div>
                     -->
                    </ul>
						<div id="content">
					    					        
					        <div id="login-box" class="signin-menu" style="display: none; padding-left: 10px; border-radius: 15px">
					        	<!-- <a href="#" class="close"><img src="sites/all/themes/simplecorp/images/close_pop.png" class="btn_close" title="Close Window" alt="Close" /></a> 
					        	-->
					        	<h3 style="display:block;text-align:center; margin-botton: 15px;font-size: 16px; border-bottom: 1px solid #EDEEEF;">Login to SkoolMentor</h3>
					        	<div style="/*display:inline-block; margin-left:30px*/">
					          		<?php print $login_form; ?>
					          	      <a href="/usr/password" style = "padding-left: 20%; font-size: 15px;">Forgot Password ?</a>		                        
					            </div>
					          
					            <div  style="display:inline-block; margin-left: 25px;min-width: 95%;">
					            	<div class="separator" style="text-align: center; color: black; font-weight: bold; margin-left: 20%;">OR</div>
					            </div>
					            <div style="display:inline-block; min-width: 100%;">	            
						            <div>
										<a href="/fb/login?type=login"><img style="max-height: 30px; margin-left: 8%; width: 81%; image-rendering: -webkit-optimize-contrast !important;" src="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/icons/fb_signin.png" alt="Log in with Facebook"/></a>
						            </div>
								    <div style="/*position: absolute;margin-top: 40px*/">
				                        <a href="/linkedin/login/0?type=login"><img style="max-height: 30px; margin-left: 8%; margin-top: 10px;width: 81%;" src="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/icons/linkedin-button-signin.png" alt="Log in with Linkedin"/></a>
					                </div>
								</div>
								<div  style="text-align:center;">
									<h6 style="margin-top: 10px;line-height: 25px;font-size: 14px;color: black;font-weight: bold;">
										Don't have an account?
										<!-- <a title="Create a SkoolMentor account now!" class="register-window button round" id="register_form" href="#register-box">Register Now!</a> -->
										<br><a style="padding: 7px 10px;background-color: rgb(224, 218, 206);color: black;border-radius: 25px;width: 70%;border-color: black;border-width: medium;"
										 class="button round" id="register_form" >Register Now!</a>
										 <!-- href="/signup"<a style="padding: 7px 35px;background-color: rgb(224, 218, 206);color: black;border-radius: 25px;width: 70%;border-color: black;border-width: medium;"
										 class="button round"  href="/mentee/register">Register Now!</a> -->
									</h6>
							    </div>
						   	</div>

						   	<div id="register-box" class="register-popup" >
					        	<a href="#" class="close"><img src="/sites/all/themes/simplecorp/images/close_pop.png" class="btn_close" title="Close Window" alt="Close" /></a>
					        	<?php print drupal_render(drupal_get_form('mentoringcommon_sign_up_form')); ?>
					        </div>
						</div>



                    <script type="text/javascript">
					//$(document).ready(function() {
					(function ($) {
						var queryString = location.search;
	               		if( queryString.indexOf("keyword=") >= 0) {
							$('#keywordSearchTextBox').val(queryString.substring(queryString.indexOf("keyword=")+8).replace("%20", " "));
	               			$('#keywordSearchTextBox').css("color","black");
	               		}
	               	 	$('#howItWorksButton').bind('contextmenu', function (e) {
	                     e.preventDefault();
	                     alert('Right Click is not allowed');
	                   });
						$('a.signup_button').click(function(){
							  $(this).toggleClass("bbg");
						});

						$('#mentoringcommon-login').submit(function(){
								$(this).find(".form-submit").val("Loading....");
								$(this).prop("disable",true);
							});
						$('div.register-popup').hide();
						$('div.signin-menu').hide();
						$('#faqsButton').click(function() {
							if($('#howItWorksDiv').is(':visible')){
								$('#howItWorksDiv').slideToggle(50);
								$('#howItWorksButton').toggleClass('bbg');
							}
							if($('#login-box').is(':visible')){
								$('#login-box').slideToggle(50);
								$('#signInForSkoolMentor').toggleClass('bbg');
							}
						});
						$('#signInForSkoolMentor').click(function() {
							
							// Getting the variable's value from a link 
							var position =$(this).position();
							var loginBox = $(this).attr('href');
							
							if($('#howItWorksDiv').is(':visible')){
								$('#howItWorksDiv').slideToggle(50);
								$('#howItWorksButton').toggleClass('bbg');
							}
							if($('#faqsButton').hasClass('bbg')){
								$('#faqsButton').toggleClass('bbg');
							}else if(window.location.href.indexOf("faqs") > -1 && !$('#signInForSkoolMentor').hasClass('bbg')){
								$('#faqsButton').toggleClass('bbg');	
							}
						    $(loginBox).slideToggle(50);
						    $(loginBox+'> div > form > div > div > input').each(function(){
						    	if($(this).attr("value") ==  "Log In"){
									 $(this).attr('style','background-color: rgb(255, 150, 14); background-image: none ! important; margin-left: 10%; width: 78%; padding: 7px 12px; font-size: medium; font-weight: bolder;');
									}else{
										if(this.name == "name"){
											$(this).val("Username");
										}else if(this.name == "pass"){
											$(this).val("Password");
										}
										$(this).css("width",'73%');							 
										$(this).css("border-radius",'5px');							 
										$(this).css("margin",'2% 10%');							 
										var valueText = this.value;
										var typeText = this.type;
									    $(this).css('color','#cdcdcd');
									    $(this).css('font-weight','bold');
									    if(typeText == "password" && this.value == "Password")
									    	this.type ='text';
										   								
										$(this).focus(function(){
											if(typeText == "password")
										    	this.type ='password';
											
									        if(this.value == valueText) {
									            this.value = '';
									            $(this).css('color','black');
											    $(this).css('font-weight','normal');
											    if(this.name == "name"){
												    var password = $(this).parent().siblings(".form-type-password").children("input");
												    focused = setInterval(function() {
															if (password.val() !== "Password") {
																	password.triggerHandler( "focus" );
												    		   		clearInterval(focused);
												            }
												    }, 50);
											    }
											    
											}
									    });
									 
									    $(this).blur(function(){
									        if(this.value == '') {
									            this.value = valueText;
									            $(this).css('color','#cdcdcd');
											    $(this).css('font-weight','bold');
											    if(typeText == "password")
											    	this.type ='text';
												
											}
									    });
									}
							    });
						    
							return false;
						});
						
						$('#register_form').click(function() {
							
							$('#login-box').hide();
							$('#signInForSkoolMentor').toggleClass("bbg");
							var registerBox = $('#register-box');
							
							//Fade in the Popup and add close button
							$(registerBox).fadeIn(300);
							
							//Set the center alignment padding + border
							//var popMargTop = ($(registerBox).height() + 24) / 2; 
							//var popMargLeft = ($(registerBox).width() + 24) / 2; 
							
							//$(registerBox).css({ 
								//'margin-top' : -popMargTop,
								//'margin-left' : -popMargLeft
							//});
							
							// Add the mask to body
							$('body').append('<div id="mask"></div>');
							$('#mask').fadeIn(300);
							$("label[for^=edit-usertype]").show();
							return false;
						});
						
						// When clicking on the button close or the mask layer the popup closed
						$('a.close').click(function() {
							$('#mask , .signin-menu').fadeOut(300 , function() {
								$('#mask').remove();  
							});
							$('#mask , .register-popup').fadeOut(300 , function() {
								$('#mask').remove();  
							}); 
							return false;
						});

						$("#keywordSearchTextBox").each(function(){
							if(!this.value){
								this.value = "Keyword Search";
								$(this).css("color","#ABA6A6");
							    }
						    var valueText = "Keyword Search";
							$(this).css("font-weight","bold");
							$(this).css("border","1px solid #514B4B");
							$(this).css("border-style","solid");
							$(this).keydown(function(){
						        if(this.value == valueText) {
						            this.value = "";
						            $(this).css("color","black");
								    $(this).css("font-weight","normal");
								}
						    });

						    $(this).blur(function(){
						        if(this.value == "") {
						            this.value = valueText;
						            $(this).css("color","#ABA6A6");
								    $(this).css("font-weight","bold");
								}
						    });
						    $(this).keydown(function(event){
						    	 if(event.which == 13){
								    	window.location.href = ""+$(this).attr('myattr')+""+$(this).val();
						    	}
						     });
						});
						$("#keywordSearchImage").each(function(){

							$(this).click(function(){
							window.location.href = ""+$("#keywordSearchTextBox").attr('myattr')+""+$("#keywordSearchTextBox").attr('value');
							});
							$(this).mouseover(function(){
								$(this).css('cursor','pointer');
							});
						});
						$(document).click(function(event) {
    						if(!$(event.target).closest('#login-box').length &&
    							!$(event.target).is('#login-box')) {
        							if($('#login-box').is(":visible")) {
            							$('#login-box').hide();
        							}
    						}
						});
						$(document).ready(function () {
							$("ul#resourcesDropdownContent").hide();
							$('div.action-tab-div li').mouseenter(function() {
								$('ul#resourcesDropdownContent', this).animate({opacity: 'show'}, 'slow');
							});
							$('div.action-tab-div li').mouseleave(function() {
								$('ul#resourcesDropdownContent', this).animate({opacity: 'hide'}, 'fast');
							});
						});
					//});
						//$(h1).hide();
					})(jQuery);
				</script>
		    		<!-- <div style="float:right; margin:10px 6px 0 6px; padding: 5px 5px 5px 5px; width: 200px; border: 1px solid #111111; border-radius: 5px">	                    	
		                    	
		                    	Sign Up <a class="register-button" href="/mentee/register">Mentee</a> | <a class="register-button" href="/mentor/register">Mentor</a>
		                    	
		    		</div>
		                  -->     	              
	                                                		            
	        </div>        
                <?php endif; ?>

                <?php if (theme_get_setting('social_icons_display','simplecorp')): ?>   
                    <!-- #social-icons
                    <div id="social-icons" class="clearfix">
                        <ul id="social-links">
                            <li class="facebook-link"><a href="https://www.facebook.com/morethan.just.themes" class="facebook" id="social-01" title="Join Us on Facebook!">Facebook</a></li>
                            <li class="twitter-link"><a href="https://twitter.com/morethanthemes" class="twitter" id="social-02" title="Follow Us on Twitter">Twitter</a></li>
                            <li class="google-link"><a href="#" id="social-03" title="Google" class="google">Google</a></li>
                            <li class="dribbble-link"><a href="#" id="social-04" title="Dribble" class="dribbble">Dribble</a></li>
                            <li class="vimeo-link"><a href="#" id="social-05" title="Vimeo" class="vimeo">Vimeo</a></li>
                            <li class="skype-link"><a href="#" id="social-06" title="Skype" class="skype">Skype</a></li>
                            <li class="linkedin-link"><a href="#" id="social-07" title="Linkedin" class="linkedin">Linkedin</a></li>
                            <li class="pinterest-link"><a href="#" id="social-09" title="Pinterest" class="pinterest">Pinterest</a></li>
                            <li class="rss-link"><a href="#" id="social-08" title="RSS" class="rss">RSS Feeds</a></li>
                        </ul>
                    </div>
                    <!-- EOF: #social-icons -->
                <?php endif; ?>    
                
            </div>
            <!-- EOF: #pre-header -->
      
      <div id = "howItWorksDiv"  style = "margin-bottom:8px">
     	 <?php $module = 'block';
				$delta = '4';

				//Load the block object.
				$block = block_load($module, $delta);

				// Get a renderable array.
				$render_array = _block_get_renderable_array(_block_render_blocks(array($block)));

				// 	Render the block element.
				$output = render($render_array);

				print $output;
				$block = module_invoke('views', 'block_view', 'product_list-block');
				print render($block['content']);
					?>
      </div>
                   
      	    <!-- #postheader  -->
      	    <?php if ($page['post_header']): ?>
		  <div style = "margin-bottom:8px">
		    <?php print render($page['post_header']); ?>
		  </div>
	    <?php endif; ?>
	    <!-- EOF: #post-header -->
      <script type="text/javascript">
					(function ($) {
						$('#howItWorksDiv').hide();
						$('#howItWorksButton').click(function() {
							
							//Fade in the Popup and add close button
							$('#howItWorksDiv').slideToggle(100);
							if($('#login-box').is(':visible')){
								$('#login-box').slideToggle(50);
								$('#signInForSkoolMentor').toggleClass('bbg');
							}
							if($('#faqsButton').hasClass('bbg')){
								$('#faqsButton').toggleClass('bbg');
							}else if(window.location.href.indexOf("faqs") > -1 && !$('#howItWorksButton').hasClass('bbg')){
								$('#faqsButton').toggleClass('bbg');	
							}
							return false;
						});
						$("[id^='edit-submit']").each(function(){
							if($(this).attr("value") ==  "Log In"){
							 $(this).attr('style','background-color: rgb(255, 150, 14); background-image: none ! important; margin-left: 10%; width: 78%; padding: 7px 12px; font-size: medium; font-weight: bolder;');
							}
						});
					
					})(jQuery);
				</script>  
            <!-- #header -->
            <div id="header" class="clearfix" style="display:none; margin-top: 10px; margin-bottom: 10px">
                
                <!-- #header-left -->
                <div id="header-left" class="one-fifth"> 
                    
                    <?php if ($site_name || $site_slogan): ?>
                        <!-- #name-and-slogan -->
                        <!--<hgroup id="name-and-slogan">
							<?php if ($site_name):?>
                            <h1 id="site-name"><a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>"><?php print $site_name; ?></a></h1>
                            <?php endif; ?>
    
                            <?php if ($site_slogan):?>
                            <h2 id="site-slogan"><?php print $site_slogan; ?></h2>
                            <?php endif; ?>
                        </hgroup>--> 
                        <!-- EOF:#name-and-slogan -->
                    <?php endif; ?>

                </div>
                <!--EOF: #header-left -->     

                <!-- #header-right -->
                <div id="header-right" class="three-fifth last" style="padding-top:20px">   

                    <!-- #navigation-wrapper -->
                    <div id="navigation-wrapper" class="clearfix">
                        <!-- #main-navigation -->                        
                        <nav id="main-navigation" class="main-menu clearfix" role="navigation">
                        <?php if ($page['navigation']) :?>
                        <?php print drupal_render($page['navigation']); ?>
                        <?php else : ?>

                        <?php if (module_exists('i18n_menu')) {
                        $main_menu_tree = i18n_menu_translated_tree(variable_get('menu_main_links_source', 'main-menu'));                        
                        } else {
                        	if(user_is_logged_in()) {
                        		$role = get_user_role();
                        		if(substr( $role, 0, 6 ) === 'mentor') {
                        			$main_menu_tree = menu_tree('menu-mentor-menu');
                        		} else {
                        			$main_menu_tree = menu_tree('menu-mentee-menu');
                        		}
                        	} else {
                        		$main_menu_tree = menu_tree(variable_get('menu_main_links_source', 'main-menu'));
                        	} 
                        }
                        if(user_is_logged_in()) {
                       		print drupal_render($main_menu_tree);
                       	}
                         ?>

                        <?php endif; ?>
                        </nav>
                        <!-- EOF: #main-navigation -->
                    </div>
                    <!-- EOF: #navigation-wrapper -->

                </div>
                <!--EOF: #header-right -->

            </div> 
            <!-- EOF: #header -->

        </header>   
        <!-- EOF: header -->

        <div id="content" class="clearfix" style="min-height:600px">

            <?php if ($page['top_content']): ?>
            <!-- #top-content -->
            <div id="top-content" class="container clearfix">
              <!-- intro-page -->
              <div class="intro-page">
              <?php print render($page['top_content']); ?>
              </div>
              <!-- EOF: intro-page -->            
            </div>  
            <!--EOF: #top-content -->
            <?php endif; ?>
            
            <!-- #banner -->
            <div id="banner" class="container">

                <?php if ($page['banner']) : ?>
                <!-- #banner-inside -->
                <div id="banner-inside">
                <?php print render($page['banner']); ?>
                </div>
                <!-- EOF: #banner-inside -->        
                <?php endif; ?>

                <?php if (theme_get_setting('slideshow_display','simplecorp')): ?>

					<?php if ($is_front): ?>
                    <!-- #slider-container -->
                    <div id="slider-container">
                        <div class="flexslider loading">
                            <ul class="slides">

                                <!-- first-slide -->
                                <li class="slider-item">
                                    <div class="slider-image">             
                                        <a href="<?php print base_path();?>"><img src="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/slider01v2.jpg" alt="" /></a>
                                    </div>
                                    <!--<div class="flex-caption">
                                        <h3>Quisque eu nibh enim, ac aliquam nunc.</h3>
                                    </div>-->
                                </li>
    			
    							<!-- second-slide -->
                                <li class="slider-item">
                                    <div class="slider-image">                        
                                        <img src="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/sliderp4.jpg" alt="" />
                                    </div>                        
                                    <!--<div class="flex-caption">
                                        <h3>Quisque eu nibh enim, ac aliquam nunc.</h3>
                                    </div>-->
                                </li>

                                <!-- third-slide -->
                                <li class="slider-item">
                                    <div class="slider-image">
                                        <a href="/mentor/register"><img src="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/img1.jpg" alt="" /></a>
                                    </div>
                                    <!--<div class="flex-caption">
                                        <h3>Quisque eu nibh enim, ac aliquam nunc.</h3>
                                    </div>-->
                                </li>

    							<!-- fourth-slide -->
                                <li class="slider-item">
                                    <div class="slider-image">                        
                                        <img src="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/sliderp4.jpg" alt="" />
                                    </div>                        
                                    <!--<div class="flex-caption">
                                        <h3>Quisque eu nibh enim, ac aliquam nunc.</h3>
                                    </div>-->
                                </li>
    
                                <!-- fifth-slide -->
                                <li class="slider-item">
                                    <div class="slider-image">                        
                                        <a href="/mentee/register"><img src="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/img2.jpg" alt="" /></a>
                                    </div>                        
                                    <!--<div class="flex-caption">
                                        <h3>Quisque eu nibh enim, ac aliquam nunc.</h3>
                                    </div>-->
                                </li>


                            </ul>
                        </div>
                    </div>
                    <!-- EOF: #slider-container -->
                    <?php endif; ?>

                <?php endif; ?>
            
            </div>
            <!-- EOF: #banner -->

            <?php if (theme_get_setting('breadcrumb_display','simplecorp') || $messages): ?>
            <!--breadrumb & messages -->
            <div class="container clearfix">
            <!--<?php print $breadcrumb; ?>-->
            <?php print $messages; ?>
            </div>
            <!--EOF: breadrumb & messages -->
            <?php endif; ?>

            <!--#featured -->
            <div id="featured"> 

                <?php if ($page['highlighted']): ?>
                <div class="container clearfix"><?php print render($page['highlighted']); ?></div>
                <?php endif; ?>

                <?php if (theme_get_setting('highlighted_display','simplecorp')): ?>
                        
					<?php if ($is_front): ?>  
    
                    <div class="container clearfix">
                          
                        <!--featured-item -->
                        <div class="one-half">
                            <img src="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/featured-img-01.png" class="img-align-left" alt="" />
                            <h3>Awesome Features</h3>
                            <p>Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore.</p>
                            <div class="readmore">
                                <a href="#">Read More</a>
                            </div>
                        </div>
                        <!--EOF: featured-item -->
    
                        <!--featured-item -->
                        <div class="one-half last">
                            <img src="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/featured-img-02.png" class="img-align-left" alt="" />
                            <h3>Browser Compatibility</h3>
                            <p>Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore.</p>
                            <div class="readmore">
                                <a href="#">Read More</a>
                            </div>
                        </div>
                        <!--EOF: featured-item -->              
    
                    </div> 
                  
                    <div class="container clearfix">
    
                        <!--featured-item -->
                        <div class="one-half">
                            <img src="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/featured-img-03.png" class="img-align-left" alt="" />
                            <h3>Works on Mobile Devices</h3>
                            <p>Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore.</p>
                            <div class="readmore">
                                <a href="#">Read More</a>
                            </div>
                        </div>
                        <!--EOF: featured-item -->              
    
                        <!--featured-item -->
                        <div class="one-half last">
                            <img src="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/featured-img-04.png" class="img-align-left" alt="" />
                            <h3>Full Documentation</h3>
                            <p>Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore.</p>
                            <div class="readmore">
                                <a href="#">Read More</a>
                            </div>
                        </div>
                        <!--EOF: featured-item -->   
                    
                    <div class="horizontal-line"> </div>
    
                    </div>
                       
                    <?php endif; ?>

                <?php endif; ?>  

            </div>
            <!-- EOF: #featured -->
            
            <!--#main-content -->
            <div id="main-content" class="container clearfix" style="height:auto">
                <?php if ($page['sidebar_first']) :?>
                    <!--.sidebar first-->
                    <div class="one-fourth">
                    <aside class="sidebar">
                    <?php print render($page['sidebar_first']); ?>
                    </aside>
                    </div>
                    <!--EOF:.sidebar first-->
                <?php endif; ?>

				
                <?php if ($page['sidebar_first'] && $page['sidebar_second']) { ?>
                <div class="one-half"> 
                <?php } elseif ($page['sidebar_first']) { ?>
                <div class="three-fourth last"> 
                <?php } elseif ($page['sidebar_second']) { ?>
                <div class="three-fourth"> 
                <?php } else { ?>
                <div class="clearfix">    
                <?php } ?>
                    <!--#main-content-inside-->
                    <div id="main-content-inside">
                    <?php print render($title_prefix); ?>
                    <?php print render($title_suffix); ?>
                    <?php print render($page['help']); ?>
                    <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
                    <?php print render($page['content']); ?>
                    </div>
                    <!--EOF:#main-content-inside-->
                </div>


                <?php if ($page['sidebar_second']) :?>
                    <!--.sidebar second-->
                    <div class="one-fourth last">
                    <aside class="sidebar">
                    <?php print render($page['sidebar_second']); ?>
                    </aside>
                    </div>
                    <!--EOF:.sidebar second-->
                <?php endif; ?>  

            </div>
            <!--EOF: #main-content -->

            <!-- #bottom-content -->
            <div id="bottom-content" class="container clearfix">

                <?php if ($page['bottom_content']): ?>
                <?php print render($page['bottom_content']); ?>
                <?php endif; ?>

                <?php if (theme_get_setting('carousel_display','simplecorp')): ?>
                        
					<?php if ($is_front): ?>  
                    
                    <h3>Some of Our Featured Projects</h3>
                    
                    <ul id="projects-carousel" class="loading">
    
                        <!-- PROJECT ITEM STARTS -->
                        <li>
                            <div class="item-content">
                                <div class="link-holder">
                                    <div class="portfolio-item-holder">
                                        <div class="portfolio-item-hover-content">
    
                                            <a href="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/portfolio-img-1.jpg" title="title" data-rel="prettyPhoto" class="zoom">View Image</a>
                                            
                                           <img src="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/pt-img1.jpg" alt="" width="220"  class="portfolio-img" />  
                                            
                                            <div class="hover-options"></div>
                                        </div>
                                    </div>
                                    <div class="description">
                                        <p>
                                            <a href="#" title="title"> BlackBerry Website Project</a>
                                        </p>
                                        <span>Web</span>
                                    </div>
                                </div>
                            </div>
                        </li>
                        <!-- PROJECT ITEM ENDS -->
    
                        <!-- PROJECT ITEM STARTS -->
                        <li>
                            <div class="item-content">
                                <div class="link-holder">
                                    <div class="portfolio-item-holder">
                                        <div class="portfolio-item-hover-content">
    
                                            <a href="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/portfolio-img-2.jpg" title="title" data-rel="prettyPhoto" class="zoom">View Image</a>
                                            
                                            <img src="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/pt-img2.jpg" alt="" width="220" class="portfolio-img" />
    
                                            <div class="hover-options"></div>
                                        </div>
                                    </div>
                                    <div class="description">
                                        <p>
                                            <a href="#" title="title"> Vestibulum ante ipsum primis</a>
                                        </p>
                                        <span>Illustration</span>
                                    </div>
                                </div>
                            </div>
                        </li>
                        <!-- PROJECT ITEM ENDS -->
    
                        <!-- PROJECT ITEM STARTS -->
                        <li>
                            <div class="item-content">
                                <div class="link-holder">
                                    <div class="portfolio-item-holder">
                                        <div class="portfolio-item-hover-content">
    
                                            <a href="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/portfolio-img-3.jpg" title="title" data-rel="prettyPhoto" class="zoom">View Image</a>
                                            
                                            <img src="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/pt-img3.jpg" alt="" width="220" class="portfolio-img" />
    
                                            <div class="hover-options"></div>
                                        </div>
                                    </div>
                                    <div class="description">
                                        <p>
                                            <a href="#" title="title"> Nulla mollis fermentum nunc</a>
                                        </p>
                                        <span>Illustration</span>
                                    </div>
                                </div>
                            </div>
                        </li>
                        <!-- PROJECT ITEM ENDS -->
    
                        <!-- PROJECT ITEM STARTS -->
                        <li>
                            <div class="item-content">
                                <div class="link-holder">
                                    <div class="portfolio-item-holder">
                                        <div class="portfolio-item-hover-content">
    
                                            <a href="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/portfolio-img-4.jpg" title="title" data-rel="prettyPhoto" class="zoom">View Image</a>
                                            
                                            <img src="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/pt-img4.jpg" alt="" width="220" class="portfolio-img" />
                                            
                                            <div class="hover-options"></div>
                                        </div>
                                    </div>
                                    <div class="description">
                                        <p>
                                            <a href="#" title="title"> Cras vel orci sapien</a>
                                        </p>
                                        <span>Illustration / Web</span>
                                    </div>
                                </div>
                            </div>
                        </li>
                        <!-- PROJECT ITEM ENDS -->
    
                         <!-- PROJECT ITEM STARTS -->
                        <li>
                            <div class="item-content">
                                <div class="link-holder">
                                    <div class="portfolio-item-holder">
                                        <div class="portfolio-item-hover-content">
    
                                            <a href="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/portfolio-img-5.jpg" title="title" data-rel="prettyPhoto" class="zoom">View Image</a>
                                            
                                            <img src="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/pt-img5.jpg" alt="" width="220" class="portfolio-img" />
                                            
                                            <div class="hover-options"></div>
                                        </div>
                                    </div>
                                    <div class="description">
                                        <p>
                                            <a href="#" title="title">Curabitur nisl libero</a>
                                        </p>
                                        <span>Illustration / Web</span>
                                    </div>
                                </div>
                            </div>
                        </li>
                        <!-- PROJECT ITEM ENDS -->
    
                        <!-- PROJECT ITEM STARTS -->
                        <li>
                            <div class="item-content">
                                <div class="link-holder">
                                    <div class="portfolio-item-holder">
                                        <div class="portfolio-item-hover-content">
    
                                            <a href="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/portfolio-img-1.jpg" title="title" data-rel="prettyPhoto" class="zoom">View Image</a>
                                            
                                            <img src="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/pt-img1.jpg" alt="" width="220" class="portfolio-img" />
                                            
                                            <div class="hover-options"></div>
                                        </div>
                                    </div>
                                    <div class="description">
                                        <p>
                                            <a href="#" title="title"> BlackBerry Website Project</a>
                                        </p>
                                        <span>Web</span>
                                    </div>
                                </div>
                            </div>
                        </li>
                        <!-- PROJECT ITEM ENDS -->
    
                        <!-- PROJECT ITEM STARTS -->
                        <li>
                            <div class="item-content">
                                <div class="link-holder">
                                    <div class="portfolio-item-holder">
                                        <div class="portfolio-item-hover-content">
    
                                            <a href="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/portfolio-img-2.jpg" title="title" data-rel="prettyPhoto" class="zoom">View Image</a>
                                            
                                            <img src="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/pt-img2.jpg" alt="" width="220" class="portfolio-img" />
                                            
                                            <div class="hover-options"></div>
                                        </div>
                                    </div>
                                    <div class="description">
                                        <p>
                                            <a href="#" title="title"> Vestibulum ante ipsum primis</a>
                                        </p>
                                        <span>Illustration</span>
                                    </div>
                                </div>
                            </div>
                        </li>
                        <!-- PROJECT ITEM ENDS -->
    
                        <!-- PROJECT ITEM STARTS -->
                        <li>
                            <div class="item-content">
                                <div class="link-holder">
                                    <div class="portfolio-item-holder">
                                        <div class="portfolio-item-hover-content">
    
                                            <a href="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/portfolio-img-3.jpg" title="title" data-rel="prettyPhoto" class="zoom">View Image</a>
                                            
                                            <img src="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/pt-img3.jpg" alt="" width="220" class="portfolio-img" />
                                            
                                            <div class="hover-options"></div>
                                        </div>
                                    </div>
                                    <div class="description">
                                        <p>
                                            <a href="#" title="title"> Nulla mollis fermentum nunc</a>
                                        </p>
                                        <span>Illustration</span>
                                    </div>
                                </div>
                            </div>
                        </li>
                        <!-- PROJECT ITEM ENDS -->
    
                    </ul>
    
                    <!-- // optional "view full portfolio" button on homepage featured projects -->
                    <a href="#" class="colored" title="portofolio">View full portofolio</a> 
               
                <?php endif; ?>

            <?php endif; ?>  
            
            </div>
            <!-- EOF: #bottom-content -->


        </div> <!-- EOF: #content -->

        <!-- #footer -->
        <footer id="footer">
            
            <?php if ($page['footer_first'] || $page['footer_second'] || $page['footer_third'] || $page['footer_fourth']) :?>
            <div class="container clearfix">

                <div class="first one-fourth footer-area">
                <?php if ($page['footer_first']) :?>
                <?php print render($page['footer_first']); ?>
                <?php endif; ?>
                </div>

                <div class="one-fourth footer-area">
                <?php if ($page['footer_second']) :?>
                <?php print render($page['footer_second']); ?>
                <?php endif; ?>
                </div>

                <div class="one-fourth footer-area">
                <?php if ($page['footer_third']) :?>
                <?php print render($page['footer_third']); ?>
                <?php endif; ?> 
                </div>

                <div class="one-fourth footer-area last">
                <?php if ($page['footer_fourth']) :?>
                <?php print render($page['footer_fourth']); ?>
                <?php endif; ?> 
                </div>

            </div>
            <?php endif; ?>

            <!-- #footer-bottom -->
            <div id="footer-bottom" >
                <div class="container clearfix" >
                    <span class="right"><a class="backtotop" href="#">↑</a></span>
                    <?php print theme('links__system_secondary_menu', array('links' => $secondary_menu, 'attributes' => array('class' => array('menu', 'secondary-menu', 'links', 'clearfix')))); ?>
                    
                    <?php if ($page['footer']) :?>
                    <?php print render($page['footer']); ?>
                    <?php endif; ?>
                    
                    <!--  <div class="credits">
                    Ported to Drupal by <a href="http://www.drupalizing.com">Drupalizing</a> a Project of <a href="http://www.morethanthemes.com">More than Themes</a>. Designed by <a href="http://www.s5themes.com/">Site5 WordPress Themes</a>. 
                    </div>-->

                </div>
            </div>
            <!-- EOF: #footer-bottom -->
            
        </footer> 
        <!-- EOF #footer -->
     
    </div>
    <!-- EOF: #page -->

</div> 
<!-- EOF: #page-wrapper -->