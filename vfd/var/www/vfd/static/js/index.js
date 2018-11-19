/**
 * Demo script to handle the theme demo
 * **/
var IndexObj = function () {
    //检查系统保护
    var scb_pi_checkPermit = function(response) {
        //系统已保护
        if (response.message == "true") {
            $("#dialog-verify-password").modal("show");
        } else {
            location.href = "/setting";
        }
    }

    var ecb_pi_checkPermit = function(response) {
    }

    var scb_pi_verifyPermit = function(response) {
        if (response.message == "true") {
            $("#dialog-verify-password").modal("hide");
            location.href = "/setting";
        } else {
            PageUtil.error("密码错误！");
        }
    }

    var ecb_pi_verifyPermit = function(response) {
        PageUtil.error("密码校验失败！");
    }

    //重启系统
    var scb_pi_reboot = function(response) {
        $('#reboot').modal('hide');
        PageUtil.alert(response.message);
    }
    
    var ecb_pi_reboot = function(response) {
    }

    //关闭系统
    var scb_pi_shutdown = function(response) {
        $('#shutdown').modal('hide');
        PageUtil.alert(response.message);
    }
    
    var ecb_pi_shutdown = function(response) {
    }

    var scb_pi_getResources = function(response) {
        var data = response.message;
        var phtml = '';
        phtml += '<table class="table table-hover" align="center" id="pi-resource">';
        phtml += '<thead>';
        phtml += '<tr>';
        phtml += '  <th width="8%" ></th>';
        phtml += '  <th width="15%"><span>名称</span></th>';
        phtml += '  <th width="15%"><span>类型</span></th>';
        phtml += '  <th width="20%"><span>服务器地址</span></th>';
        phtml += '  <th width="15%"><span>用户名</span></th>';
        phtml += '  <th width="15%"><span>自动连接</span></th>';
        phtml += '  <th width="5%" ><span>操作</span></th>';
        phtml += '  <th width="7%" ></th>';
        phtml += '</tr>';
        phtml += '</thead>';
        phtml += '<tbody>';
        for (var i=0; i<data.length; i++){
            phtml += '<tr>';
            phtml += '  <td width="8%"></td>';
            phtml += '  <td width="15%"><span>'+data[i].nickname+'</span></td>';
            phtml += '  <td width="15%"><span>';
            if(data[i].product=="spice-desktop") {
                phtml += 'SPICE桌面';
            } else if(data[i].product=="rdp-desktop") {
                phtml += 'RDP桌面';
            } else if(data[i].product=="vmware-desktop") {
                phtml += 'VMware桌面';
            } else if(data[i].product=="citrix-desktop") {
                phtml += 'CITRIX桌面';
            } else if(data[i].product=="idv-desktop") {
                phtml += 'IDV桌面';
            } else {
                phtml += '';
            }
            phtml += '</span></td>';
            phtml += '  <td width="20%"><span>'+data[i].serverip+'</span></td>';
            phtml += '  <td width="15%"><span>'+data[i].username+'</span></td>';
            if (data[i].autolink == 1) {
                phtml += '  <td width="15%"><div class="pi-autolink">是</div></td>';
            } else {
                phtml += '  <td width="15%"><div class="pi-autolink">否</div></td>';
            }
            phtml += '  <td width="5%">';
            phtml += '    <a href="javascript:;" class="btn default btn-xs green-stripe pi-connect" data-nickname="'+data[i].nickname+'" data-serverip="'+data[i].serverip+'" data-username="'+data[i].username+'" data-password="'+data[i].password+'" data-domain="'+data[i].domain+'" data-product="'+data[i].product+'"> 连接 </a>';
            phtml += '  </td>';
            phtml += '  <td width="7%"></td>';
            phtml += '</tr>';
        }
        phtml += '</tbody>';
        phtml += '</table>';
        $("#pi-connection-area").html(phtml);
        autoConnect();
    }

    var ecb_pi_getResources = function(response) {
        var phtml = "";
        //phtml += '<tr>';
        //phtml += '  <td colspan="6" style="text-align:center">对不起没有记录</td>';
        //phtml += '</tr>';
        $("#pi-connection-area").html(phtml);
    }

    //添加这段代码是为了在连接云桌面之前自动共享本地USB设备(aoqingy)
    var scb_ps_startUsbdService = function(response) {
    }

    var ecb_ps_startUsbdService = function(response) {
        PageUtil.error("启动USB共享服务失败！")
    }

    var scb_connectTest = function(response) {
        var product  = $("#pi-product").val();
        var username = $("#pi-username").val();
        var password = $("#pi-password").val();
        if (product != "citrix-desktop" && product != "idv-desktop" && (username == '' || password == '')) {
            $("#dca-username").val(username);
            $("#dca-password").val(password);
            if (username != '') {
                $("#dca-username").attr("readonly", "readonly");
            } else {
                $("#dca-username").removeAttr("readonly");
            }
            $("#dialog-connect-account").modal('show');
            setTimeout(function () {
                $("#dialog-connect-account input:eq(0)").focus();
            }, 800);
        } else {
            doConnect();
        }
    }

    var ecb_connectTest = function(response) {
        var product  = $("#pi-product").val();
        var username = $("#pi-username").val();
        var password = $("#pi-password").val();
        if (product != "citrix-desktop" && product != "idv-desktop" && (username == '' || password == '')) {
            $("#dca-username").val(username);
            $("#dca-password").val(password);
            if (username != '') {
                $("#dca-username").attr("readonly", "readonly");
            } else {
                $("#dca-username").removeAttr("readonly");
            }
            $("#dialog-connect-account").modal('show');
            setTimeout(function () {
                $("#dialog-connect-account input:eq(0)").focus();
            }, 800);
        } else {
            doConnect();
        }
        //PageUtil.error("连接测试失败！");
    }

    var doConnect = function(response) {
        var nickname = $("#pi-nickname").val();
        var product  = $("#pi-product" ).val();
        var serverip = $("#pi-serverip").val();
        var username = $("#pi-username").val();
        var password = $("#pi-password").val();
        var domain   = $("#pi-domain"  ).val();

        if (product == "spice-desktop"){
            getDesktops(scb_getDesktops4Spice, ecb_getDesktops4Spice, serverip, username, password, domain);
        } else if (product == "rdp-desktop"){
            if (domain == "") {
                //如果未填入域名，接入常规RDP桌面
                connectRegularRdp(scb_connectRegularRdp, ecb_connectRegularRdp, serverip, username, password);
            } else {
                //否则，以RDP协议接入虚拟化平台云桌面（首先获取云桌面列表）
                getDesktops(scb_getDesktops4Rdp, ecb_getDesktops4Rdp, serverip, username, password, domain);
            }
        } else if (product == "vmware-desktop"){
            connectVMware(scb_connectVMware, ecb_connectVMware, serverip, username, password);
        } else if (product == "citrix-desktop") {
            if (serverip.match(/:\/\//)) {    //可以直接输入各种协议的URL（例如http、rtmp等）
                connectCitrix(scb_connectCitrix, ecb_connectCitrix, serverip);
            } else {
                connectCitrix(scb_connectCitrix, ecb_connectCitrix, "http:\/\/" + serverip);
            }
        } else if (product == "idv-desktop"){
            connectIdv(scb_connectIdv, ecb_connectIdv, nickname); 
        }
    }

    /*
    ** IDV桌面相关
    */
    var scb_connectIdv = function(response) {
    }

    var ecb_connectIdv = function(response) {
        alert('连接IDV桌面失败!');
    }

    /*
    ** VMware桌面相关
    */
    var scb_connectVMware = function(response) {
    }

    var ecb_connectVMware = function(response) {
        alert("连接VMware桌面失败!");
    }

    /*
    ** Citrix桌面相关
    */
    var scb_connectCitrix = function(response) {
        location.href = response.message;
    }

    var ecb_connectCitrix = function(response) {
        alert("连接Citrix桌面失败!");
    }

    /*
    ** RDP桌面相关
    */
    var scb_connectRegularRdp = function(response) {
    }

    var ecb_connectRegularRdp = function(response) {
        alert("连接常规RDP桌面失败!");
    }

    //获取系统信息
    var scb_pi_getSystemInfo = function(response) {
        $("#pi-uuid").html(response.message.uuid);
    }

    var ecb_pi_getSystemInfo = function(response) {
        $("#pi-uuid").html('');
    }

    var handleActions = function(){
        $('body')
        .on('click', '#pi-setting', function(e) {
            e.preventDefault();
            checkPermit(scb_pi_checkPermit, ecb_pi_checkPermit);
        })
        .on('click', '#pi-verify-password', function(e) {
            e.preventDefault();
            var password = $('#dvp-password').val();
            verifyPermit(scb_pi_verifyPermit, ecb_pi_verifyPermit, password);
        })
        .on('click', '#pi-reboot', function(e) {
            e.preventDefault();
            reboot(scb_pi_reboot, ecb_pi_reboot);
        })
        .on('click', '#pi-shutdown', function(e) {
            e.preventDefault();
            shutdown(scb_pi_shutdown, ecb_pi_shutdown);
        })
        .on('click', 'a.pi-connect', function(e) {
            e.preventDefault();
            var $el = $(this);
            var nickname = $el.data("nickname");
            var product  = $el.data("product");
            var serverip = $el.data('serverip');
            var username = $el.data("username");
            var password = $el.data("password");
            var domain   = $el.data("domain");
            $("#pi-nickname").val(nickname);
            $("#pi-product" ).val(product);
            $("#pi-serverip").val(serverip);
            $("#pi-username").val(username);
            $("#pi-password").val(password);
            $("#pi-domain"  ).val(domain);
            if (product != "idv-desktop") {
                //添加这段代码是为了在连接云桌面之前自动共享本地USB设备(aoqingy)
                startUsbdService(scb_ps_startUsbdService, ecb_ps_startUsbdService);
                connectTest(scb_connectTest, ecb_connectTest, serverip);
            } else {
                doConnect();
            }
        })
        .on('click', '#dca-username-keyboard', function(e) {
            e.preventDefault();
            $("#dca-username").keyboard({
                openOn : null,
                stayOpen : true,
                layout : 'qwerty'
            })
            .addTyping();
            var kb = $("#dca-username").getkeyboard();
            if ( kb.isOpen ) {
                kb.close();
            } else {
                kb.reveal();
            }
        })
        .on('click', '#dca-password-keyboard', function(e) {
            e.preventDefault();
            $("#dca-password").keyboard({
                openOn : null,
                stayOpen : true,
                layout : 'qwerty'
            })
            .addTyping();
            var kb = $("#dca-password").getkeyboard();
            if ( kb.isOpen ) {
                kb.close();
            } else {
                kb.reveal();
            }
        })
        .on('click', '#pi-cancel-connect', function(e) {
            e.preventDefault();
            clearInterval(ctimer);
            $("#dialog-message-box").modal("hide");
        })
        .on('click', '#pi-connect-account', function(e) {
            e.preventDefault();
            var username = $("#dca-username").val();
            var password = $("#dca-password").val();
            if (username == '' || password == '') {
                return;
            }
            $("#pi-username").val(username);
            $("#pi-password").val(password);
            $("#dialog-connect-account").modal("hide");
            doConnect();
        });
    };

    var initGrid = function() {
        getResources(scb_pi_getResources, ecb_pi_getResources);
        getSystemInfo(scb_pi_getSystemInfo, ecb_pi_getSystemInfo);
    }

    return {
        init: function() {
            initGrid();
            handleActions();
        }
    };
}();

var ctimer = null;
var autoConnectObj = null;
function autoConnect(){
    if (whereFrom == "api") {
        whenFromApi();
    }
    $('#pi-resource tbody tr').each(function() {
        var chkObj = $(this).find(".pi-autolink");
        if (chkObj.text() == '是') {
            $("#pi-message").html("将在 <span id='pi-countdown'>1</span> 秒后自动连接");
            $("#dialog-message-box").modal("show");
            autoConnectObj = $(this).find(".pi-connect");
            //ctimer = setInterval("countDown()", 1000)		#倒计时
            autoConnectObj.trigger("click");
        }
    });
};

$(document).ready(function () {
    /** Coding Here */
}).keydown(function (e) {
    if (e.which === 27) {
        clearInterval(ctimer);
    }
});

function countDown(){
    var s = $("#pi-countdown");
    s.text(s.text() * 1 - 1);
    if (s.text()*1 == 0) {
        $("#dialog-message-box").modal("hide");
        autoConnectObj.trigger("click");
        clearInterval(ctimer);
    }
};

function whenFromApi(){
    $('#pi-resource tr').each(function() {
        $(this).find(".pi-connect").trigger("click");
    });
}
