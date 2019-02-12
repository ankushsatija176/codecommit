jQuery(document).ready(function(){
	var mainPanel = $("#mainPanel");
	var subPanel = mainPanel.find("#subPanel");
	var leftDiv = $("<div>").css("width", "60px").css("height", mainPanel.height()+"px")
							.css("position", "relative").css("left", "0px").attr("id", "leftDiv");
	mainPanel.append(leftDiv);
	var rightDiv = $("<div>").css("width", "60px").attr("id", "rightDiv")
					.css("height", mainPanel.height()+"px").css("position", "absolute")
					.css("right","0px")
					.css("top", parseInt(mainPanel.css("top"))+"px");				
					
	mainPanel.append(rightDiv);
	leftDiv.hover(function(){mouIn(leftDiv, false);}, function(){mouOut(leftDiv);});
	rightDiv.hover(function(){mouIn(rightDiv, true);}, function(){mouOut(rightDiv);});
	
	function mouIn(ele, incr){
		ele.data("imgScrl", true);								
		if(ele.data("imgScrl")){
			_mouIn(ele, incr);
		}
	}
	function _mouIn(ele, incr){					
		var mLeft;
		if(ele.data("imgScrl")){
			mLeft = parseInt(subPanel.css("margin-left"));						
			if(incr){
				mLeft+=8;
			}else{
				mLeft-=8;
			}
			subPanel.css("margin-left", mLeft+"px");
			//_mouIn(ele, incr);
			setTimeout(function(){_mouIn(ele, incr);}, 1);
		}
	}
	function mouOut(ele){
		ele.data("imgScrl", false);				
	}
});