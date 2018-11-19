var RDPObj = function () {
    var serverip;
    var username;
    var password;
    var domain;
    
    var initParameter = function(data){
        serverip = getQueryString("serverip");
        username = getQueryString("username");
        password = getQueryString("password");
        domain = getQueryString("domain");
        loadDesktopList(data);
    }
    
    var loadDesktopList = function(data){
        var rhtml = "";
        if(data instanceof Array){
            for (var i = 0; i < data.length; i++) {
                var image = '';
                if (data[i].os_type.indexOf('Windows') >= 0) {
                    if (data[i].status == "up") {
                        image = windows_up_img;
                    } else {
                        image = windows_down_img;
                    }
                } else {
                    if (data[i].status == "up") {
                        image = other_up_img;
                    } else {
                        image = other_down_img;
                    }
                }
                rhtml += '<div class="vdesk" data-vmid="'+data[i].id+'" data-serverip="'+serverip+'" data-username="'+username+'" data-password="'+password+'" data-domain="'+domain+'">';
                rhtml += '  <a class="vdesk-img"><img src="'+image+'" width="200px" alt="云桌面"/></a>';
                rhtml += '  <div class="vdesk-name">'+data[i].name+'</div>';
                rhtml += '</div>';
            }
        }
        $("#vdesks-area").html(rhtml);
    }

    var scb_startAndConnectRdp = function(response) {
    }
    
    var ecb_startAndConnectRdp = function(response) {
        PageUtil.error("无法连接桌面!");
    }

    var scb_getDesktops = function(response) {
        loadDesktopList(response.message);
    }
    
    var ecb_getDesktops = function(response) {
        PageUtil.error("无法获取桌面!");
    }

    var handleActions = function(){
        $('body')
        .on('click', '.vdesk', function(e) {
            e.preventDefault();
            var vmid = $(this).data('vmid');
            var serverip = $(this).data('serverip');
            var username = $(this).data('username');
            var password = $(this).data('password');
            var domain = $(this).data('domain');
            startAndConnectRdp(scb_startAndConnectRdp, ecb_startAndConnectRdp, serverip, username, password, domain, vmid);
            getDesktops(scb_getDesktops, ecb_getDesktops, serverip, username, password, domain);
        })
        
        .on('click', '.refresh', function(e) {
            e.preventDefault();
            getDesktops(scb_getDesktops, ecb_getDesktops, serverip, username, password, domain);
        })
        
        
    }
    
    return {
        init: function () {
            initParameter(JSON.parse(getQueryString("desktops")));
            handleActions();
        }
    };
}();
