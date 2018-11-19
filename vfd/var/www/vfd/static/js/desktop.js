var DesktopObj = function () {

    var handleActions = function(){
        $('body')
        .on('click', '.rdesktop', function(e) {
            e.preventDefault();
            vmid = $(this).data('vmid');			//记录所点击的虚拟机标识符
            startAndConnectRdp(scb_startAndConnectRdp, ecb_startAndConnectRdp, serverip, username, password, domain, vmid, rusername, rpassword);
        })

        .on('click', '.sdesktop', function(e) {
            e.preventDefault();
            vmid = $(this).data('vmid');			//记录所点击的虚拟机标识符
            startAndConnectSpice(scb_startAndConnectSpice, ecb_startAndConnectSpice, serverip, username, password, domain, vmid);
        })
        
        .on('click', '.refresh', function(e) {
            e.preventDefault();
            getDesktops(scb_getDesktops, ecb_getDesktops, serverip, username, password, domain);
        })
        
        .on('click', '#pd-reconnect', function(e) {
            e.preventDefault();
            //alert('vmid: '+vmid+', rusername: '+rusername+', rpassword: '+rpassword);
            $("#dialog-reconnect-desktop").modal('hide');
            if (conntype == "rdp") {
                startAndConnectRdp(scb_startAndConnectRdp, ecb_startAndConnectRdp, serverip, username, password, domain, vmid, rusername, rpassword);
            } else {
                startAndConnectSpice(scb_startAndConnectSpice, ecb_startAndConnectSpice, serverip, username, password, domain, vmid);
            }
        })

        .on('click', '#pd-connect-with-another', function(e) {
            e.preventDefault();
            //alert('vmid: '+vmid+', rusername: '+rusername+', rpassword: '+rpassword);
            if (conntype == "rdp") {
                $("#dialog-reconnect-desktop").modal('hide');
                $("#dcoa-username").val('');
                $("#dcoa-password").val('');
                $("#dialog-connect-other-account").modal('show');
            }
        })

        .on('click', '#pd-connect-other-account', function(e) {
            e.preventDefault();
            rusername = $("#dcoa-username").val();			//记录新的连接用户名
            rpassword = $("#dcoa-password").val();
            //alert('vmid: '+vmid+', rusername: '+rusername+', rpassword: '+rpassword);
            $("#dialog-connect-other-account").modal('hide');
            if (conntype == "rdp") {
                startAndConnectRdp(scb_startAndConnectRdp, ecb_startAndConnectRdp, serverip, username, password, domain, vmid, rusername, rpassword);
            }
        })

    }
    
    return {
        init: function () {
            handleActions();
        }
    };
}();

var serverip;
var username;
var password;
var domain;
var conntype;
var vmid;
var rusername = 'administrator';
var rpassword = '123456';
var ctimer;


var scb_startAndConnectRdp = function(response) {
}

var ecb_startAndConnectRdp = function(response) {
    getDesktops(scb_getDesktops, ecb_getDesktops, serverip, username, password, domain);
    $("#prd-message").html("无法连接桌面!");
    $("#dialog-reconnect-desktop").modal('show');
}


var scb_startAndConnectSpice = function(response) {
}

var ecb_startAndConnectSpice = function(response) {
    getDesktops(scb_getDesktops, ecb_getDesktops, serverip, username, password, domain);
    $("#prd-message").html("无法连接桌面!");
    $("#dialog-reconnect-desktop").modal('show');
}


var scb_getDesktops4Rdp = function(response) {
    serverip = $("#pi-serverip").val();
    username = $("#pi-username").val();
    password = $("#pi-password").val();
    domain   = $("#pi-domain").val();
    conntype = 'rdp';
    var data = response.message;
    if (data.length == 1) {
        //如果只有一个桌面的情况下，直接去连
        vmid = data[0].id;
        startAndConnectRdp(scb_startAndConnectRdp, ecb_startAndConnectRdp, serverip, username, password, domain, vmid, rusername, rpassword);
    } else {
        //呈现云桌面列表
        location.href = "/desktop?serverip="+serverip+"&username="+username+"&password="+password+"&domain="+domain+"&conntype=rdp";
        ctimer = setInterval("reloadDesktopsList()", 3000)
    }
}

var ecb_getDesktops4Rdp = function(response) {
    PageUtil.error("获取云桌面失败!");
}


var scb_getDesktops4Spice = function(response) {
    serverip = $("#pi-serverip").val();
    username = $("#pi-username").val();
    password = $("#pi-password").val();
    domain   = $("#pi-domain").val();
    conntype = 'spice';
    var data = response.message;
    if (data.length == 1) {
        //如果只有一个桌面的情况下，直接去连
        vmid = data[0].id;
        startAndConnectSpice(scb_startAndConnectSpice, ecb_startAndConnectSpice, serverip, username, password, domain, vmid);
    } else {
        //呈现云桌面列表
        location.href = "/desktop?serverip="+serverip+"&username="+username+"&password="+password+"&domain="+domain+"&conntype=spice";
        ctimer = setInterval("reloadDesktopsList()", 3000)
    }
}

var ecb_getDesktops4Spice = function(response) {
    PageUtil.error("获取云桌面失败!");
}


var scb_getDesktops = function(response) {
    redrawDesktopList(response.message);
}

var ecb_getDesktops = function(response) {
}


var redrawDesktopList = function(data) {
    var rhtml = '';
    if (data instanceof Array) {
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
            rhtml += '<div';
            if (conntype == "rdp") {
                rhtml += ' class="rdesktop vdesk"';
            } else {
                rhtml += ' class="sdesktop vdesk"';
            }
            rhtml += ' data-vmid="'+data[i].id+'" data-serverip="'+serverip+'" data-username="'+username+'" data-password="'+password+'" data-domain="'+domain+'">';
            rhtml += '  <a class="vdesk-img"><img src="'+image+'" width="200px" alt="云桌面"/></a>';
            rhtml += '  <div class="vdesk-name">'+data[i].name+'</div>';
            rhtml += '</div>';
        }
        if (data.length == 0) {
            rhtml = '<div class="no_vm">没有授权的云桌面</div>';
        }
    }
    $("#vdesks-area").html(rhtml);
    rhtml = '';
    if (conntype == 'rdp') {
        rhtml += '<div class="col-md-6" style="text-align:left">';
        rhtml += '  <button type="button" class="btn green" id="pd-connect-with-another">换用户名连接</button>';
        rhtml += '</div>';
        rhtml += '<div class="col-md-6" style="text-align:right">';
        rhtml += '  <button type="button" class="btn" data-dismiss="modal">取消</button>';
        rhtml += '  <button type="button" class="btn blue" id="pd-reconnect">重连</button>';
        rhtml += '</div>';
    } else {
        rhtml += '  <button type="button" class="btn" data-dismiss="modal">取消</button>';
        rhtml += '  <button type="button" class="btn blue" id="pd-reconnect">重连</button>';
    }
    $("#pd-reconnect-footer").html(rhtml);
}


var reloadDesktopsList = function() {
    clearInterval(ctimer);
    getDesktops(scb_getDesktops, ecb_getDesktops, serverip, username, password, domain);
}
