<?php if($comment->pid == 0){?>
<div style="display: inline-block; color: #848484;border-bottom: 1px solid #ccc;width: 100%;">
<div style="min-width: 15%; float: left; padding: 1%;">

<div style="padding: 2% 0%;"><?php print render($content['field_user_rating']); ?> </div>

<div style="padding: 2% 0%; color: #565656;"><?php  print drupal_ucfirst($comment->name) ?> </div>
<div>
<?php print $submitted_month_c; ?> 
<?php print $submitted_day_c; ?>,
<?php print $submitted_year_c; ?>
</div>
</div>
<div style="min-width: 75%; float: left; margin: 1% 1% 1% 0%;padding-left: 2%; max-width: 79%;">
<div style="font-size: 20px; color: black; font-weight: bold;" ><?php print filter_xss($comment->subject) ?></div>
<div style="min-height: 30px;"><?php 
        //drupal_set_message("<pre>".print_r($content,true)."</pre>",error);
		print render($content['comment_body']); ?>
        
</div>
<?php //if($comment->pid == 0){?>
<?php // print render($content['links']); } ?>
</div>
<?php }?>
</div>
<script type="text/javascript">
            (function ($) {
            	var count = 0;
            	var timerComment = setInterval(function(){
            		if(count < 60){
            			clearInterval(timerComment);
             		}
					if($('.filter-wrapper').length>0){
         				clearInterval(timerComment);
             			$('.filter-wrapper').hide();
             			if($('#comments').length <= 0){
                 			$('label[for^=edit-subject]').text("Title");
                 			$('.field-type-fivestar').hide();
                 		}	
					}
             			
            	}, 1000);
            		$('p').attr("style","margin: 1px 0px;");
               		$('div.field-label').hide();
               		})(jQuery);
				</script>   
	