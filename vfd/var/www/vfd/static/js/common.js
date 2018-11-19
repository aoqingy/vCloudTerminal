jQuery.extend({'vfModal':(function(){
    var m = $("<div class='modal fade' tabindex='-1' data-backdrop='static' data-keyboard='false'></div>");
    var cnt = "", msg = "";
    return {'show':function(type,message){
            switch(type)
            {
                case 'success':
                    msg = message || 'Info';
                    cnt += "<div class='modal-dialog'><div class='modal-content'>";
                    cnt += "<div class='modal-header'><button type='button' class='close' data-dismiss='modal' aria-hidden='true'>×</button><h4 class='modal-title'>成功</h4></div>";
                    cnt += "<div class='modal-body'><div class='Metronic-alerts alert alert-success'><i class='glyphicon glyphicon-ok'></i>  "+msg+" </div></div>";
                    cnt += "<div class='modal-footer'><button type='button' class='btn default'  data-dismiss='modal' aria-hidden='true'>Close</button></div>";
                    cnt += "</div></div>";
                    break;

                case 'warning':
                    msg = message || 'Warning';
                    cnt += "<div class='modal-dialog'><div class='modal-content'>";
                    cnt += "<div class='modal-header'><button type='button' class='close' data-dismiss='modal' aria-hidden='true'>×</button><h4 class='modal-title'>警告</h4></div>";
                    cnt += "<div class='modal-body'><div class='Metronic-alerts alert alert-warning'><i class='glyphicon glyphicon-warning-sign'></i>  "+msg+" </div></div>";
                    cnt += "<div class='modal-footer'><button type='button' class='btn default' data-dismiss='modal' aria-hidden='true'>Close</button></div>";
                    cnt += "</div></div>";
                    break;

                case 'error':
                    msg = message || 'Error';
                    cnt += "<div class='modal-dialog'><div class='modal-content'>";
                    cnt += "<div class='modal-header'><button type='button' class='close' data-dismiss='modal' aria-hidden='true'>×</button><h4 class='modal-title'>错误</h4></div>";
                    cnt += "<div class='modal-body'><div class='Metronic-alerts alert alert-danger'><i class='glyphicon glyphicon-remove'></i>  "+msg+" </div></div>";
                    cnt += "<div class='modal-footer'><button type='button' class='btn default' data-dismiss='modal' aria-hidden='true'>Close</button></div>";
                    cnt += "</div></div>";
                    break;

                default:
                    cnt = "<div class=\"modal-header\" style=\"height:2em;overflow:hidden;\"><button type=\"button\" class=\"close\" data-dismiss=\"modal\" aria-hidden=\"true\">×</button><h5>消息</h5></div><div class=\"modal-body\"><p class=\"alert\">"+message+"</p></div>";
            }
            m.html(cnt);
            cnt = "";
            m.modal({show:true, keyboard:true});
        },
        'confirm':function(message, callback, style){
            //callback();
            msg = '您确定要删除吗？' || message;
            msg = message || 'Warning';
            cnt += "<div class='modal-dialog'><div class='modal-content'>";
            cnt += "<div class='modal-header'><button type='button' class='close' data-dismiss='modal' aria-hidden='true'>×</button><h4 class='modal-title'>提示</h4></div>";
            cnt += "<div class='modal-body'><div class='Metronic-alerts alert alert-"+style+"'><div style='float:left;margin-right:3px;'><i class='glyphicon glyphicon-warning-sign'></i></div><div style='float:left;'>"+msg+" </div><div style='clear:both'></div></div></div>";
            cnt += "<div class='modal-footer'><button type='button' class='btn btn-primary pageUtilConfirmOK'>确定</button><button type='button' class='btn default' data-dismiss='modal' aria-hidden='true'>取消</button></div>";
            cnt += "</div></div>";
            m.html(cnt);
            cnt = "";
            m.modal({show:true, keyboard:true});
            $(".pageUtilConfirmOK", m).click(function(){
                 $.vfModal.hide();
                 callback();
                 return false;
            });
        },
        'hide':function(){
            m.modal('hide');
        }
    };
})()});

function getQueryString(name){
     var reg = new RegExp("(^|&)"+ name +"=([^&]*)(&|$)");
     var r = window.location.search.substr(1).match(reg);
     if(r!=null)return  unescape(r[2]); return null;
}

Array.prototype.contains = function(b) {
    for (var a = 0; a < this.length; a++) {
        if (this[a] == b) {
            return true
        }
    }
    return false
};
Array.prototype.unique = function(){
    var data = this || [];
    var a = {};
    for (var i=0; i<data.length; i++) {
        var v = data[i];
        if (typeof(a[v]) == 'undefined'){
            a[v] = 1;
        }
    };
    data.length=0;
    for (var i in a){
        data[data.length] = i;
    }
    return data;
};

var PageUtil = {
    blockUIId   : "body",
    blockUIMsg  : "Processing...",
    showMaskLayer: function(param1) {
        var param = param1 || {}
        PageUtil.blockUIId = param.id || PageUtil.blockUIId;
        PageUtil.blockUIMsg = param.msg || PageUtil.blockUIMsg;
        $('html,body').animate({scrollTop: '0px'}, 500);
        Metronic.blockUI({
            target: PageUtil.blockUIId,
            boxed: true,
            message: PageUtil.blockUIMsg
        });
        if(PageUtil.blockUIId == "body"){
            $(".blockUI").css("position", "fixed");
            $(".blockUI").css("z-index", "99999");
            $(".blockUI").css("top", "0");
            $(".blockUI").css("padding-top", "20%");
        }
    },
    hideMaskLayer: function(id) {
        Metronic.unblockUI(PageUtil.blockUIId);
    },
    alert: function(msg1) {
        var msg = msg1 || "Success";
        //Metronic.alert({message: msg, type:"success", icon:"check", closeInSeconds: 5});
        $.vfModal.show('success',msg);
    },
    warning: function(msg1) {
        var msg = msg1 || "Warning";
        //Metronic.alert({message: msg, type:"warning", icon:"warning", closeInSeconds: 5});
        $.vfModal.show('warning',msg);
    },
    error: function(msg1) {
        var msg = msg1 || "Error";
        //Metronic.alert({message: msg, type:"danger", icon:"danger", closeInSeconds: 50});
        $.vfModal.show('error',msg);
    },
    confirm: function(msg1, callback) {
        var style= arguments[2] || "info";
        var msg = msg1 || "Error";
        //Metronic.alert({message: msg, type:"danger", icon:"danger", closeInSeconds: 50});
        $.vfModal.confirm(msg, callback, style);
    }
};
String.prototype.endsWith = function(suffix) {
    return this.indexOf(suffix, this.length - suffix.length) !== -1;
};

