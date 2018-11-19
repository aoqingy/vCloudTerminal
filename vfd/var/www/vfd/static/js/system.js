var SystemObj = function () {
        var $addSPICEDesktopForm = $('#form-add-sdesktop'), $addSPICEDesktopError = $('.alert-danger', $addSPICEDesktopForm), $addSPICEDesktopWarning = $('.alert-warning', $addSPICEDesktopForm),
        addSPICEDesktopSubmitFormOptions = {
            dataType: 'json',
            url     : '/api/resource/add',
            type    : 'POST',
            success: function(response){
                if (response.code == "True") {
                    $("#dialog-add-sdesktop").modal('hide');
                    getResources(scb_pi_getResources, ecb_pi_getResources);
                } else {
                    PageUtil.error("添加SPICE桌面失败！");
                    $addSPICEDesktopError.hide();
                    $addSPICEDesktopError.show();
                }
            }
        }

        $addRDPDesktopForm = $('#form-add-rdesktop'), $addRDPDesktopError = $('.alert-danger', $addRDPDesktopForm), $addRDPDesktopWarning = $('.alert-warning', $addRDPDesktopForm),
        addRDPDesktopSubmitFormOptions = {
            dataType: 'json',
            url     : '/api/resource/add',
            type    : 'POST',
            success: function(response){
                if (response.code == "True") {
                    $("#dialog-add-rdesktop").modal('hide');
                    getResources(scb_pi_getResources, ecb_pi_getResources);
                } else {
                    PageUtil.error("添加RDP桌面失败！");
                    $addRDPDesktopError.hide();
                    $addRDPDesktopError.show();
                }
            }
        }

        $addVMWAREDesktopForm = $('#form-add-vdesktop'), $addVMWAREDesktopError = $('.alert-danger', $addVMWAREDesktopForm), $addVMWAREDesktopWarning = $('.alert-warning', $addVMWAREDesktopForm),
        addVMWAREDesktopSubmitFormOptions = {
            dataType: 'json',
            url     : '/api/resource/add',
            type    : 'POST',
            success: function(response){
                if (response.code == "True") {
                    $("#dialog-add-vdesktop").modal('hide');
                    getResources(scb_pi_getResources, ecb_pi_getResources);
                } else {
                    PageUtil.error("添加VMware桌面失败！");
                    $addVMWAREDesktopError.hide();
                    $addVMWAREDesktopError.show();
                }
            }
        }

        $addCITRIXDesktopForm = $('#form-add-cdesktop'), $addCITRIXDesktopError = $('.alert-danger', $addCITRIXDesktopForm), $addCITRIXDesktopWarning = $('.alert-warning', $addCITRIXDesktopForm),
        addCITRIXDesktopSubmitFormOptions = {
            dataType: 'json',
            url     : '/api/resource/add',
            type    : 'POST',
            success: function(response){
                if (response.code == "True") {
                    $("#dialog-add-cdesktop").modal('hide');
                    getResources(scb_pi_getResources, ecb_pi_getResources);
                } else {
                    PageUtil.error("添加CITRIX桌面失败");
                    $addCITRIXDesktopError.hide();
                    $addCITRIXDesktopError.show();
                }
            }
        }

        $addIDVDesktopForm = $('#form-add-idesktop'), $addIDVDesktopError = $('.alert-danger', $addIDVDesktopForm), $addIDVDesktopWarning = $('.alert-warning', $addIDVDesktopForm),
        addIDVDesktopSubmitFormOptions = {
            dataType: 'json',
            url     : '/api/resource/add',
            type    : 'POST',
            success: function(response){
                if (response.code == "True") {
                    $("#dialog-add-idesktop").modal('hide');
                    getResources(scb_pi_getResources, ecb_pi_getResources);
                } else {
                    PageUtil.error("添加IDV桌面失败！");
                    $addIDVDesktopError.hide();
                    $addIDVDesktopError.show();
                }
            }
        }

        $setPasswordForm = $('#form-set-password'), $setPasswordFormError = $('.alert-danger', $setPasswordForm), $setPasswordFormWarning = $('.alert-warning', $setPasswordForm),
        setPasswordFormSubmitFormOptions = {
            dataType: 'json',
            url     : '/api/password/set',
            type    : 'POST',
            success: function(response){
                if (response.code == "True") {
                    PageUtil.alert(response.message);
                    $("#dialog-set-password").modal('hide');
                } else {
                    PageUtil.error(response.message);
                    $("#dialog-set-password").modal('hide');
                    $setPasswordFormError.hide();
                    $setPasswordFormWarning.show();
                }
            }
        };

    var handleFormValidation = function(){

        jQuery.validator.addMethod("name_regex", function(value, element) {
            return this.optional(element) || /^[\w-_.\u4e00-\u9fa5]+$/i.test(value);
        }, "only special word");

        jQuery.validator.addMethod("http_regex", function(value, element) {
            return this.optional(element) || /^[\w-_.:\/]+$/i.test(value);
        }, "only special word");

        $addSPICEDesktopForm.validate({
            errorElement: 'span',
            errorClass:   'help-block',
            focusInvalid: false,
            rules: {
                nickname:      { required: true, maxlength: 20, name_regex: true },
                serverip:      { required: true, http_regex: true },
                domain:        { maxlength: 20, name_regex: true },
            },
            messages: {
                nickname:      { required: "名称不能为空", maxlength: "名称长度不能超过20个字符", name_regex: "名称只能包含中文、英文、数字、-、_、." },
                serverip:      { required: "服务器地址不能为空", http_regex: "服务器地址中含有特殊字符" },
            },
            invalidHandler: function (event, validator) {
                $addSPICEDesktopWarning.hide();
                $addSPICEDesktopError.show();
            },
            highlight: function (element) {
                $(element).closest('.form-group').addClass('has-error');
            },
            success: function (label) {
                label.closest('.form-group').removeClass('has-error');
                label.remove();
            },
            errorPlacement: function (error, element) {
                error.insertAfter(element.closest('.form-control'));
            },
            submitHandler: function (form) {
                $(form).ajaxSubmit(addSPICEDesktopSubmitFormOptions);
            }
        });

        $("#pi-cancel-add-sdesktop").click(function() {
            $addSPICEDesktopForm.validate().resetForm();
            $("label", $addSPICEDesktopForm).closest('.form-group').removeClass('has-error');
        });

        $('#form-add-sdesktop input').keypress(function (e) {
            if (e.which == 13) {
                $(form).ajaxSubmit(addSPICEDesktopSubmitFormOptions);
            }
        });


        $addRDPDesktopForm.validate({
            errorElement: 'span',
            errorClass:   'help-block',
            focusInvalid: false,
            rules: {
                nickname:      { required: true, maxlength: 20, name_regex: true },
                serverip:      { required: true, http_regex: true },
                domain:        { maxlength: 20, name_regex: true },
            },
            messages: {
                nickname:      { required: "名称不能为空", maxlength: "名称长度不能超过20个字符", name_regex: "名称只能包含中文、英文、数字、-、_、." },
                serverip:      { required: "服务器地址不能为空", http_regex: "服务器地址中含有特殊字符" },
            },
            invalidHandler: function (event, validator) {
                $addRDPDesktopWarning.hide();
                $addRDPDesktopError.show();
            },
            highlight: function (element) {
                $(element).closest('.form-group').addClass('has-error');
            },
            success: function (label) {
                label.closest('.form-group').removeClass('has-error');
                label.remove();
            },
            errorPlacement: function (error, element) {
                error.insertAfter(element.closest('.form-control'));
            },
            submitHandler: function (form) {
                $(form).ajaxSubmit(addRDPDesktopSubmitFormOptions);
            }
        });

        $("#pi-cancel-add-rdesktop").click(function() {
            $addRDPDesktopForm.validate().resetForm();
            $("label", $addRDPDesktopForm).closest('.form-group').removeClass('has-error');
        });

        $('#form-add-rdesktop input').keypress(function (e) {
            if (e.which == 13) {
                $(form).ajaxSubmit(addRDPDesktopSubmitFormOptions);
            }
        });

        $addVMWAREDesktopForm.validate({
            errorElement: 'span',
            errorClass:   'help-block',
            focusInvalid: false,
            rules: {
                nickname:      { required: true, maxlength: 20, name_regex: true },
                serverip:      { required: true, http_regex: true },
                domain:        { maxlength: 20, name_regex: true },
            },
            messages: {
                nickname:      { required: "名称不能为空", maxlength: "名称长度不能超过20个字符", name_regex: "名称只能包含中文、英文、数字、-、_、." },
                serverip:      { required: "服务器地址不能为空", http_regex: "服务器地址中含有特>殊字符" },
            },
            invalidHandler: function (event, validator) {
                $addVMWAREDesktopWarning.hide();
                $addVMWAREDesktopError.show();
            },
            highlight: function (element) {
                $(element).closest('.form-group').addClass('has-error');
            },
            success: function (label) {
                label.closest('.form-group').removeClass('has-error');
                label.remove();
            },
            errorPlacement: function (error, element) {
                error.insertAfter(element.closest('.form-control'));
            },
            submitHandler: function (form) {
                $(form).ajaxSubmit(addVMWAREDesktopSubmitFormOptions);
            }
        });

        $("#pi-cancel-add-vdesktop").click(function() {
            $addVMWAREDesktopForm.validate().resetForm();
            $("label", $addVMWAREDesktopForm).closest('.form-group').removeClass('has-error');
        });

        $('#form-add-vdesktop input').keypress(function (e) {
            if (e.which == 13) {
                $(form).ajaxSubmit(addVMWAREDesktopSubmitFormOptions);
            }
        });


        $addCITRIXDesktopForm.validate({
            errorElement: 'span',
            errorClass:   'help-block',
            focusInvalid: false,
            rules: {
                nickname:      { required: true, maxlength: 20, name_regex: true },
                serverip:      { required: true, http_regex: true },
            },
            messages: {
                nickname:      { required: "名称不能为空", maxlength: "名称长度不能超过20个字符", name_regex: "名称只能包含中文、英文、数字、-、_、." },
                serverip:      { required: "服务器地址不能为空", http_regex: "服务器地址中含有特殊字符" },
            },
            invalidHandler: function (event, validator) {
                $addCITRIXDesktopWarning.hide();
                $addCITRIXDesktopError.show();
            },
            highlight: function (element) {
                $(element).closest('.form-group').addClass('has-error');
            },
            success: function (label) {
                label.closest('.form-group').removeClass('has-error');
                label.remove();
            },
            errorPlacement: function (error, element) {
                error.insertAfter(element.closest('.form-control'));
            },
            submitHandler: function (form) {
                $(form).ajaxSubmit(addCITRIXDesktopSubmitFormOptions);
            }
        });

        $("#pi-cancel-add-cdesktop").click(function() {
            $addCITRIXDesktopForm.validate().resetForm();
            $("label", $addCITRIXDesktopForm).closest('.form-group').removeClass('has-error');
        });

        $('#form-add-cdesktop input').keypress(function (e) {
            if (e.which == 13) {
                $(form).ajaxSubmit(addCITRIXDesktopSubmitFormOptions);
            }
        });

        $addIDVDesktopForm.validate({
            errorElement: 'span',
            errorClass:   'help-block',
            focusInvalid: false,
            rules: {
                nickname:      { required: true, maxlength: 20, name_regex: true },
            },
            messages: {
                nickname:      { required: "名称不能为空", maxlength: "名称长度不能超过20个字符", name_regex: "名称只能包含中文、英文、数字、-、_、." },
            },
            invalidHandler: function (event, validator) {
                $addIDVDesktopWarning.hide();
                $addIDVDesktopError.show();
            },
            highlight: function (element) {
                $(element).closest('.form-group').addClass('has-error');
            },
            success: function (label) {
                label.closest('.form-group').removeClass('has-error');
                label.remove();
            },
            errorPlacement: function (error, element) {
                error.insertAfter(element.closest('.form-control'));
            },
            submitHandler: function (form) {
                $(form).ajaxSubmit(addIDVDesktopSubmitFormOptions);
            }
        });

        $("#pi-cancel-add-idesktop").click(function() {
            $addIDVDesktopForm.validate().resetForm();
            $("label", $addIDVDesktopForm).closest('.form-group').removeClass('has-error');
        });

        $('#form-add-idesktop input').keypress(function (e) {
            if (e.which == 13) {
                $(form).ajaxSubmit(addIDVDesktopSubmitFormOptions);
            }
        });

        $('#dialog-connect-account input').keypress(function (e) {
            if (e.which == 13) {
                $('#pi-connect-account').trigger('click');
            }
        });

        $('#form-set-password').validate({
            errorElement: 'span',
            errorClass  : 'help-block',
            focusInvalid: false,
            rules: {
                password2: {
                    equalTo: "#dsp-password"
                }
            },
            messages: {
                password2: {
                    equalTo: "两次输入密码不一致"
                }
            },
            invalidHandler: function (event, validator) {
                $setPasswordFormWarning.hide();
                $setPasswordFormError.show();
            },
            highlight: function (element) {
                $(element).closest('.form-group').addClass('has-error');
            },
            success: function (label) {
                label.closest('.form-group').removeClass('has-error');
                label.remove();
            },
            errorPlacement: function (error, element) {
                error.insertAfter(element.closest('.form-control'));
            },
            submitHandler: function (form) {
                $(form).ajaxSubmit(setPasswordFormSubmitFormOptions);
            }
        });
    }

    //重启终端
    var scb_ps_reboot = function(response) {
        $('#reboot').modal('hide');
        PageUtil.alert(response.message);
    }

    var ecb_ps_reboot = function(response) {
    }

    //关闭终端
    var scb_ps_shutdown = function(response) {
        $('#shutdown').modal('hide');
        PageUtil.alert(response.message);
    }

    var ecb_ps_shutdown = function(response) {
    }

    //网络
    var scb_ps_getNetwork = function(response) {
        var data = response.message;
        $("select[name='iptype']").val(data.iptype);
        $("input[name='ipaddr']" ).val(data.ipaddr);
        $("input[name='netmask']").val(data.netmask);
        $("input[name='gateway']").val(data.gateway);
        $("input[name='dns1']"   ).val(data.dns1);
        $("input[name='dns2']"   ).val(data.dns2);
        if (data.iptype == "dhcp"){
            $("input[name='ipaddr']" ).attr("readonly", "readonly");
            $("input[name='netmask']").attr("readonly", "readonly");
            $("input[name='gateway']").attr("readonly", "readonly");
        } else {
            $("input[name='ipaddr']" ).removeAttr("readonly");
            $("input[name='netmask']").removeAttr("readonly");
            $("input[name='gateway']").removeAttr("readonly");
        }
        //如果不是dhcp和static，我们需要禁用保存和应用按钮
        if (data.iptype != 'dhcp' && data.iptype != 'static') {
            $("#ps-save-network").attr("disabled", "disabled");
            $("#ps-restart-network").attr("disabled", "disabled");
        }
    }

    var ecb_ps_getNetwork = function(response) {
    }

    //保存网络
    var scb_ps_saveNetwork = function(response) {
        PageUtil.alert("网络配置已保存，但目前仍然使用的是保存之前的网络配置，新的网络配置在重启终端之后才能生效。");
    }

    var ecb_ps_saveNetwork = function(response) {
        PageUtil.error(response.message);
    }

    //应用网络
    var scb_ps_restartNetwork = function(response) {
        getNetwork(scb_ps_getNetwork4Restart, ecb_ps_getNetwork4Restart);
        PageUtil.alert("网络配置已应用，但如果您需要在该网络配置在终端重启之后仍然生效，请执行保存操作！");
    }
    
    var ecb_ps_restartNetwork= function(response) {
    }

    var scb_ps_getNetwork4Restart = function(response) {
        var iptype = $("select[name='iptype']" ).val();
        var data = response.message;
        $("input[name='ipaddr']" ).val(data.ipaddr);
        $("input[name='netmask']").val(data.netmask);
        $("input[name='gateway']").val(data.gateway);
        $("input[name='dns1']"   ).val(data.dns1);
        $("input[name='dns2']"   ).val(data.dns2);
        if (iptype == "dhcp"){
            $("input[name='ipaddr']" ).attr("readonly", "readonly");
            $("input[name='netmask']").attr("readonly", "readonly");
            $("input[name='gateway']").attr("readonly", "readonly");
        } else {
            $("input[name='ipaddr']" ).removeAttr("readonly");
            $("input[name='netmask']").removeAttr("readonly");
            $("input[name='gateway']").removeAttr("readonly");
        }
    }

    var ecb_ps_getNetwork4Restart = function(response) {
    }

    //获取WIFI
    var scb_ps_getWifi = function(response) {
        var whtml = '';
        for (var i = 0; i < response.message.length; i++) {
            whtml += '<option value="' + response.message[i] + '">' + response.message[i] + '</option>';
        }
        $("#ps-wifi-name").html(whtml);
        $("#ps-wifi-password").val('');
    }

    var ecb_ps_getWifi = function(response) {
        $("#ps-wifi-name").html('');
        $("#ps-wifi-password").val('');
    }

    var scb_ps_getConnectedWifi = function(response) {
        if (response.message.length) {
            $("#ps-connected-wifi").html('<div class="col-md-6"><input type="text" readonly class="form-control" value="' + response.message[0] + '" id="ps-connected-wifi-name" /></div><div class="col-md-3"><button type="button" class="btn blue-madison" style="width:84px; height:34px;" id="ps-disconnect-wifi">断开</button></div>');
        } else {
            $("#ps-connected-wifi").html('当前没有无线连接！');
        }
        $("#ps-wifi-password").val('');
    }

    var ecb_ps_getConnectedWifi = function(response) {
        $("#ps-connected-wifi").html('当前没有无线连接！');
        $("#ps-wifi-password").val('');
    }

    //连接WIFI
    var scb_ps_connectWifi = function(response) {
        getConnectedWifi(scb_ps_getConnectedWifi, ecb_ps_getConnectedWifi);
    }

    var ecb_ps_connectWifi = function(response) {
        PageUtil.error(response.message);
        $("#ps-wifi-password").val('');
    }

    //断开WIFI
    var scb_ps_disconnectWifi = function(response) {
        getConnectedWifi(scb_ps_getConnectedWifi, ecb_ps_getConnectedWifi);
    }

    var ecb_ps_disconnectWifi = function(response) {
        PageUtil.error(response.message);
        $("#ps-wifi-password").val('');
    }

    var scb_pi_getResources = function(response) {
        var data = response.message;
        var phtml = '';
        phtml += '<table class="table table-hover" align="center" id="pi-resource">';
        phtml += '<thead>';
        phtml += '<tr>';
        phtml += '  <th width="4%" ></th>';
        phtml += '  <th width="15%">名称</th>';
        phtml += '  <th width="15%">类型</th>';
        phtml += '  <th width="21%">服务器地址</th>';
        phtml += '  <th width="15%">用户名</th>';
        phtml += '  <th width="12%">自动连接</th>';
        phtml += '  <th width="18%">操作</th>';
        phtml += '</tr>';
        phtml += '</thead>';
        phtml += '<tbody>';
        for (var i=0; i<data.length; i++){
            phtml += '<tr>';
            phtml += '  <th width="4%" ></th>';
            phtml += '  <td width="15%">'+data[i].nickname+'</td>';
            phtml += '  <td width="15%">';
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
            phtml += '</td>';
            phtml += '  <td width="21%">'+data[i].serverip+'</td>';
            phtml += '  <td width="15%">'+data[i].username+'</td>';
            if (data[i].autolink == 1) {
                phtml += '  <td width="12%">是</td>';
            } else {
                phtml += '  <td width="12%">否</td>';
            }
            phtml += '  <td width="18%">';
            if (data[i].product == "spice-desktop") {
                phtml += '    <a href="javascript:;" class="btn default btn-xs green-stripe pi-edit-sdesktop" data-id="'+data[i].id+'" data-nickname="'+data[i].nickname+'" data-product="'+data[i].product+'" data-serverip="'+data[i].serverip+'" data-username="'+data[i].username+'" data-password="'+data[i].password+'" data-domain="'+data[i].domain+'" data-autolink="'+data[i].autolink+'" > 编辑 </a>';
            } else if (data[i].product == "rdp-desktop") {
                phtml += '    <a href="javascript:;" class="btn default btn-xs green-stripe pi-edit-rdesktop" data-id="'+data[i].id+'" data-nickname="'+data[i].nickname+'" data-product="'+data[i].product+'" data-serverip="'+data[i].serverip+'" data-username="'+data[i].username+'" data-password="'+data[i].password+'" data-domain="'+data[i].domain+'" data-autolink="'+data[i].autolink+'" > 编辑 </a>';
            } else if (data[i].product == "vmware-desktop") {
                phtml += '    <a href="javascript:;" class="btn default btn-xs green-stripe pi-edit-vdesktop" data-id="'+data[i].id+'" data-nickname="'+data[i].nickname+'" data-product="'+data[i].product+'" data-serverip="'+data[i].serverip+'" data-username="'+data[i].username+'" data-password="'+data[i].password+'" data-autolink="'+data[i].autolink+'" > 编辑 </a>';
            } else if (data[i].product == "citrix-desktop") {
                phtml += '    <a href="javascript:;" class="btn default btn-xs green-stripe pi-edit-cdesktop" data-id="'+data[i].id+'" data-nickname="'+data[i].nickname+'" data-product="'+data[i].product+'" data-serverip="'+data[i].serverip+'" data-username="'+data[i].username+'" data-password="'+data[i].password+'" data-domain="'+data[i].domain+'" data-autolink="'+data[i].autolink+'" > 编辑 </a>';
            } else if (data[i].product == "idv-desktop") {
                phtml += '    <a href="javascript:;" class="btn default btn-xs green-stripe pi-edit-idesktop" data-id="'+data[i].id+'" data-nickname="'+data[i].nickname+'" data-product="'+data[i].product+'" data-serverip="'+data[i].serverip+'" data-username="'+data[i].username+'" data-password="'+data[i].password+'" data-domain="'+data[i].domain+'" data-autolink="'+data[i].autolink+'" > 编辑 </a>';
            }
            phtml += '    <a href="javascript:;" class="btn default btn-xs green-stripe pi-remove" data-id="'+data[i].id+'"> 删除 </a>';
            phtml += '  </td>';
            phtml += '</tr>';
        }
        phtml += '</tbody>';
        phtml += '</table>';
        $("#pi-connection-area").html(phtml);
    }

    var ecb_pi_getResources = function(response) {
        var phtml = "";
        //phtml += '<tr>';
        //phtml += '  <td colspan="6" style="text-align:center">对不起没有记录</td>';
        //phtml += '</tr>';
        $("#pi-connection-area").html(phtml);
    }

    var scb_removeResource = function(response) {
        getResources(scb_pi_getResources, ecb_pi_getResources);
    }
    var ecb_removeResource = function(response) {
    }

    //时间
    var scb_ps_getSystemTime = function(response) {
        var data = response.message;
        $('#ps-datepicker').datepicker("update", new Date(data.year, data.month-1, data.day));
        var hour   = data.hour;
        var minute = data.minute;
        if (data.minute < 10){
             minute.toString();
             minute = "0" + minute;
        }
        $("#ps-timepicker").val(hour+":"+minute);
    }

    var ecb_ps_getSystemTime = function(response) {
    }

    var scb_ps_setSystemTime = function(response) {
        PageUtil.alert(response.message);
    }

    var ecb_ps_setSystemTime = function(response) {
        PageUtil.error(response.message);
    }

    //切换系统
    function scb_ps_listBootLoader(response) {
        var shtml = '';
        for (var i = 0; i < response.message.length; i++) {
            var data = response.message[i];
            shtml += '<div class="form-group">';
            shtml += '<div class="col-md-1">';
            if (data['def'] != '') {
                shtml += '<input type="checkbox" class="form-control ps-dtb-checkbox" data-uuid=\'' + data['uuid'] + '\' id=\'ps-dtb-' + data['uuid'] + '\' checked="checked" />';
            } else {
                shtml += '<input type="checkbox" class="form-control ps-dtb-checkbox" data-uuid=\'' + data['uuid'] + '\' id=\'ps-dtb-' + data['uuid'] + '\' />';
            }
            shtml += '</div>';
            shtml += '<div class="col-md-10 ps-dtb-label" style="text-align:right" data-uuid=\'' + data['uuid'] + '\' data-name=\'' + data['name'] + '\'>';
            shtml += '<label class="control-label">' + data['name'] + '(' + data['uuid'] + ')' + '</label>';
            shtml += '</div>';
            shtml += '</div>';
        }
        $("#ps-dtb-bootloader").html(shtml);
    }

    function ecb_ps_listBootLoader(response) {
        $("#ps-dtb-bootloader").html('');
    }

    function scb_ps_changeBootLoader(response) {
        $("#dialog-terminal-bootloader").modal('hide');
        PageUtil.alert("设置默认引导成功！");
        reboot(scb_ps_reboot, ecb_ps_reboot);
    }

    function ecb_ps_changeBootLoader(response) {
        PageUtil.error("设置默认引导失败！");
    }

    //保存系统
    var scb_ps_querySystem4Save = function(response) {
        var shtml = '';
        if ($("#ps-dss-type").val() == 'disk') {
            data = response.message['disk'];
        } else {
            data = response.message['parts'];
        }
        for (var i = 0; i < data.length; i++) {
            shtml += '<option value=\'' + data[i] + '\'>' + data[i] + '</option>';
        }
        $("#ps-dss-all-diskparts").html(shtml);
        $("#ps-dss-diskparts").html('');
    }
    var ecb_ps_querySystem4Save = function(response) {
        $("#ps-dss-all-diskparts").html('');
        $("#ps-dss-diskparts").html('');
    }

    var scb_ps_saveSystem = function(response) {
        $("#dialog-save-system").modal('hide');
        PageUtil.alert("系统保存成功！")
    }

    var ecb_ps_saveSystem = function(response) {
        PageUtil.error("系统保存失败！")
    }

    //恢复系统
    var scb_ps_querySystem4Restore = function(response) {
        var shtml = '';
        if ($("#ps-drs-type").val() == 'disk') {
            data = response.message['disk'];
        } else {
            data = response.message['parts'];
        }
        for (var i = 0; i < data.length; i++) {
            shtml += '<option value=\'' + data[i] + '\'>' + data[i] + '</option>';
        }
        $("#ps-drs-all-diskparts").html(shtml);
        $("#ps-drs-diskparts").html('');
    }
    var ecb_ps_querySystem4Restore = function(response) {
        $("#ps-drs-all-diskparts").html('');
        $("#ps-drs-diskparts").html('');
    }

    var scb_ps_restoreSystem = function(response) {
        $("#dialog-restore-system").modal('hide');
        PageUtil.alert("系统恢复成功！")
    }

    var ecb_ps_restoreSystem = function(response) {
        PageUtil.error("系统恢复失败！")
    }

    //系统上传
    var scb_ps_uploadSystem = function(response) {
        $("#dialog-upload-system").modal('hide');
        PageUtil.alert("系统上传成功！")
    }

    var ecb_ps_uploadSystem = function(response) {
        PageUtil.error("系统上传失败！")
    }

    //系统下载
    var scb_ps_downloadSystem = function(response) {
        $("#dialog-download-system").modal('hide');
        PageUtil.alert("系统下载成功！")
    }

    var ecb_ps_downloadSystem = function(response) {
        PageUtil.error("系统下载失败！")
    }

    //USB共享
    var scb_ps_getUsbdStatus = function(response) {
        var shtml = '';
        if (response.message == 'started') {
            shtml += '<div class="form-group">';
            shtml += '  <label class="col-md-2 control-label">USB服务状态：</label>';
            shtml += '  <div class="col-md-8">';
            shtml += '    <input class="form-control" type="text" readonly="readonly" value="已启动"></input>';
            shtml += '  </div>';
            shtml += '  <div class="col-md-2">';
            shtml += '    <a class="btn btn-default btn-sm" id="ps-stop-usbd"><span class="hidden-480">停止</span></a>';
            shtml += '  </div>';
            shtml += '</div>';
            shtml += '<div class="form-group">';
            shtml += '  <label class="col-md-2 control-label">服务监听地址：</label>';
            shtml += '  <div class="col-md-3">';
            shtml += '    <input class="form-control" type="text" id="ps-usbd-ipaddr"></input>';
            shtml += '  </div>';
            shtml += '  <label class="col-md-2 control-label">服务监听端口：</label>';
            shtml += '  <div class="col-md-3">';
            shtml += '    <input class="form-control" type="text" id="ps-usbd-port"></input>';
            shtml += '  </div>';
            shtml += '</div>';
            shtml += '<div class="form-group">';
            shtml += '  <label class="col-md-2 control-label">云端桌面地址：</label>';
            shtml += '  <div class="col-md-3">';
            shtml += '    <input class="form-control" type="text" id="ps-desk-ipaddr"></input>';
            shtml += '  </div>';
            shtml += '  <label class="col-md-2 control-label">云端桌面端口：</label>';
            shtml += '  <div class="col-md-3">';
            shtml += '    <input class="form-control" type="text" id="ps-desk-port"></input>';
            shtml += '  </div>';
            shtml += '  <div class="col-md-2">';
            shtml += '    <a class="btn btn-default btn-sm" id="ps-create-callback"><span class="hidden-480">连接</span></a>';
            shtml += '  </div>';
            shtml += '</div>';
            shtml += '<div class="form-group">';
            shtml += '  <div class="table-scrollable" id="ps-usb-list">';
            shtml += '  </div>';
            shtml += '</div>';
            $("#ps-usbd-content").html(shtml);
            getNetwork(scb_ps_getNetwork4Usbd, ecb_ps_getNetwork4Usbd);
            getUsbdPort(scb_ps_getUsbdPort, ecb_ps_getUsbdPort);
            listUsbDevices(scb_ps_listUsbDevices, ecb_ps_listUsbDevices);
            getUsbdCallback(scb_ps_getUsbdCallback, ecb_ps_getUsbdCallback);
        } else {
            shtml += '<div class="form-group">';
            shtml += '  <label class="col-md-3 control-label">USB服务状态：</label>';
            shtml += '  <div class="col-md-6">';
            shtml += '    <input class="form-control" type="text" readonly="readonly" value="已停止"></input>';
            shtml += '  </div>';
            shtml += '  <div class="col-md-2">';
            shtml += '    <a class="btn btn-default btn-sm" id="ps-start-usbd"><span class="hidden-480">启动</span></a>';
            shtml += '  </div>';
            shtml += '</div>';
            $("#ps-usbd-content").html(shtml);
        }
    }

    var ecb_ps_getUsbdStatus = function(response) {
        var shtml = '';
        shtml += '<div class="form-group">';
        shtml += '  <label class="col-md-3 control-label">USB服务状态：</label>';
        shtml += '  <div class="col-md-6">';
        shtml += '    <input class="form-control" type="text" readonly="readonly" value="未知"></input>';
        shtml += '  </div>';
        shtml += '</div>';
        $("#ps-usbd-content").html('');
    }

    var scb_ps_startUsbdService = function(response) {
        getUsbdStatus(scb_ps_getUsbdStatus, ecb_ps_getUsbdStatus);
    }

    var ecb_ps_startUsbdService = function(response) {
        PageUtil.error("启动USB共享服务失败！")
    }

    var scb_ps_stopUsbdService = function(response) {
        getUsbdStatus(scb_ps_getUsbdStatus, ecb_ps_getUsbdStatus);
    }

    var ecb_ps_stopUsbdService = function(response) {
        PageUtil.error("停止USB共享服务失败！")
    }

    var scb_ps_getNetwork4Usbd = function(response) {
        $("#ps-usbd-ipaddr").val(response.message.ipaddr);
    }

    var ecb_ps_getNetwork4Usbd = function(response) {
        $("#ps-usbd-ipaddr").val('');
    }

    var scb_ps_getUsbdPort = function(response) {
        $("#ps-usbd-port").val(response.message);
    }

    var ecb_ps_getUsbdPort = function(response) {
        $("#ps-usbd-port").val('');
    }

    var scb_ps_getUsbdCallback = function(response) {
        $("#ps-desk-ipaddr").val(response.message.ip);
        $("#ps-desk-port").val(response.message.port);
    }

    var ecb_ps_getUsbdCallback = function(response) {
        $("#ps-desk-ipaddr").val('');
        $("#ps-desk-port").val('');
    }

    var scb_ps_createUsbdCallback = function(response) {
        getUsbdStatus(scb_ps_getUsbdStatus, ecb_ps_getUsbdStatus);
    }

    var ecb_ps_createUsbdCallback = function(response) {
        PageUtil.error("连接USB桌面失败！")
    }

    var scb_ps_closeUsbdCallback = function(response) {
        getUsbdStatus(scb_ps_getUsbdStatus, ecb_ps_getUsbdStatus);
    }

    var ecb_ps_closeUsbdCallback = function(response) {
        PageUtil.error("断开USB桌面失败！")
    }

    var redrawUsbDevices = function(devices) {
        shtml = '';
        shtml += '<div class="table-scrollable">';
        shtml += '<table class="table table-striped table-bordered table-advance table-hover">';
        shtml += '<thead>';
        shtml += '<tr>';
        shtml += '<th>序号</th>';
        shtml += '<th>名称</th>';
        shtml += '<th>状态</th>';
        shtml += '<th></th>';
        shtml += '</tr>';
        shtml += '</thead>';
        shtml += '<tbody>';
        for (var i = 0; i < devices.length; i++) {
            var uid = devices[i]['uid'];
            var uname = devices[i]['name'];
            var ustatus = devices[i]['status'];
            shtml += '<tr>';
            shtml += '<td>'+uid+'</td>';
            shtml += '<td>'+uname+'</td>';
            shtml += '<td>'+ustatus+'</td>';
            if (ustatus.indexOf('shared') >= 0 || ustatus.indexOf('in use by') >= 0) {
                shtml += '<td><a class="btn default btn-xs black ps-unshare-usb" href="javascript:;" data-uid="'+uid+'"> 取消共享 </a></td>';
            } else {
                shtml += '<td><a class="btn default btn-xs black ps-share-usb" href="javascript:;" data-uid="'+uid+'"> 共享 </a></td>';
            }
            shtml += '</tr>';
        }
        shtml += '</tbody>';
        shtml += '</table>';
        shtml += '</div>';
        $('#ps-usb-list').html(shtml);
    }

    var scb_ps_listUsbDevices = function(response) {
        redrawUsbDevices(response.message);
    }

    var ecb_ps_listUsbDevices = function(response) {
        redrawUsbDevices([]);
    }

    var scb_ps_shareUsbDevice = function(response) {
        listUsbDevices(scb_ps_listUsbDevices, ecb_ps_listUsbDevices);
    }

    var ecb_ps_shareUsbDevice = function(response) {
        listUsbDevices(scb_ps_listUsbDevices, ecb_ps_listUsbDevices);
    }

    var scb_ps_unshareUsbDevice = function(response) {
        listUsbDevices(scb_ps_listUsbDevices, ecb_ps_listUsbDevices);
    }

    var ecb_ps_unshareUsbDevice = function(response) {
        listUsbDevices(scb_ps_listUsbDevices, ecb_ps_listUsbDevices);
    }

    //系统升级
    var scb_ps_upgradeSystem = function(response) {
        PageUtil.alert("系统升级成功！")
        $("#dialog-upgrade").modal('hide');
    }

    var ecb_ps_upgradeSystem = function(response) {
        PageUtil.error("系统升级失败！")
        $("#dialog-upgrade").modal('hide');
    }

    //系统日志
    var scb_ps_getSystemLog = function(response) {
        PageUtil.alert(response.message)
        $("#dialog-log").modal('hide');
    }

    var ecb_ps_getSystemLog = function(response) {
        PageUtil.error(response.message)
        $("#dialog-log").modal('hide');
    }

    //上传许可证
    var scb_ps_uploadLicense = function(response) {
        PageUtil.alert(response.message)
        $("#dialog-license").modal('hide');
    }

    var ecb_ps_uploadLicense = function(response) {
        PageUtil.error(response.message)
        $("#dialog-license").modal('hide');
    }

    var scb_ps_resetSystem = function(response) {
        PageUtil.alert(response.message)
        $("#reset").modal('hide');
    }

    var ecb_ps_resetSystem = function(response) {
        PageUtil.error(response.message)
        $("#reset").modal('hide');
    }

    //系统信息
    var scb_ps_getSystemInfo = function(response) {
        var data = response.message;
        var syhtml = '';
        syhtml += '<div class="col-md-4 margin-bottom-5" align="right">内核版本：</div>';
        syhtml += '<div class="col-md-7 margin-bottom-5">'+data.kernel+'</div>';
        syhtml += '<div class="col-md-4 margin-bottom-5" align="right">物理地址：</div>';
        syhtml += '<div class="col-md-7 margin-bottom-5">'+data.mac+'</div>';
        syhtml += '<div class="col-md-4 margin-bottom-5" align="right">USB标识：</div>';
        if (data.usb != '') {
            syhtml += '<div class="col-md-7 margin-bottom-5">'+data.usb+'</div>';
        } else {
            syhtml += '<div class="col-md-7 margin-bottom-5">-</div>';
        }
        syhtml += '<div class="col-md-4 margin-bottom-5" align="right">处理器：</div>';
        syhtml += '<div class="col-md-7 margin-bottom-5">'+data.cpu_model+'</div>';
        syhtml += '<div class="col-md-4 margin-bottom-5" align="right">内核数：</div>';
        syhtml += '<div class="col-md-7 margin-bottom-5">'+data.cpu_core+'</div>';
        syhtml += '<div class="col-md-4 margin-bottom-5" align="right">内存大小：</div>';
        syhtml += '<div class="col-md-7 margin-bottom-5">'+data.mem_total+'</div>';
        syhtml += '<div class="col-md-4 margin-bottom-5" align="right">可用内存：</div>';
        syhtml += '<div class="col-md-7 margin-bottom-5">'+data.mem_free+'</div>';
        syhtml += '<div class="col-md-4 margin-bottom-5" align="right">空间大小：</div>';
        syhtml += '<div class="col-md-7 margin-bottom-5">'+data.disk+'</div>';
        syhtml += '<div class="col-md-4 margin-bottom-5" align="right">运行时间：</div>';
        syhtml += '<div class="col-md-7 margin-bottom-5">'+data.uptime.day+'天 '+data.uptime.hour+'小时 '+data.uptime.minute+'分钟'+'</div>';
        $("#div-system-info").html(syhtml);
        var sohtml = "";
        sohtml += '<div class="col-md-4 margin-bottom-5" align="right">软件：</div>';
        sohtml += '<div class="col-md-7 margin-bottom-5">云终端软件</div>';
        sohtml += '<div class="col-md-4 margin-bottom-5" align="right">版本：</div>';
        sohtml += '<div class="col-md-7 margin-bottom-5">'+data.vfd_ver+'</div>';
        sohtml += '<div class="col-md-4 margin-bottom-5" align="right">模式：</div>';
        sohtml += '<div class="col-md-7 margin-bottom-5">'+data.media+'</div>';
        $("#div-software-info").html(sohtml);
        var slhtml = "";
        slhtml += '<div class="col-md-4 margin-bottom-5" align="right">许可证：</div>';
        slhtml += '<div class="col-md-7 margin-bottom-5">'+data.lic_status+'</div>';
        $("#div-license-info").html(slhtml);
    }

    var ecb_ps_getSystemInfo = function(response) {
    }

    var diskparts_save_selected = function() {
        var ids = document.getElementById("ps-dss-diskparts");
        var names = "";
        for (var i = 0; i < ids.length; i++) {
            names += ids.options[i].value + ",";
        }
        names = names.length > 0 ? names.substr(0, names.length - 1) : names;

        return names;
    }

    var diskparts_restore_selected = function() {
        var ids = document.getElementById("ps-drs-diskparts");
        var names = "";
        for (var i = 0; i < ids.length; i++) {
            names += ids.options[i].value + ",";
        }
        names = names.length > 0 ? names.substr(0, names.length - 1) : names;

        return names;
    }

   var scb_pi_getIdvs = function(response) {
        var ihtml = '<option></option>';
        for (var i = 0; i < response.message.length; i++) {
            var name = response.message[i]['name'];
            if (name == $('#pi-cur-idesktop').val()) {
                ihtml += '<option selected="selected">' + response.message[i]['name'] + '</option>';
            } else {
                ihtml += '<option>' + response.message[i]['name'] + '</option>';
            }
        }
        $("#pi-idvname").html(ihtml);
    }

    var ecb_pi_getIdvs = function(response) {
        $("#pi-idvname").html('');
    }

    var scb_mountUsb = function(response) {
        getFiles(scb_getFiles4Usb, ecb_getFiles4Usb, "/mnt/usb")
    }

    var ecb_mountUsb = function(response) {
        $("#pi-usb-file").html('');
    }

    var scb_unmountUsb = function(response) {
        $("#pi-usb-file").html('');
    }

    var ecb_unmountUsb = function(response) {
    }

    var scb_getFiles4Local = function(response) {
        var data = response.message;
        var phtml = '';
        phtml += '<table class="table table-hover" align="center">';
        phtml += '<thead>';
        phtml += '<tr>';
        phtml += '  <th width="85%"><span>文件</span></th>';
        phtml += '  <th width="15%"><span>操作</span></th>';
        phtml += '</tr>';
        phtml += '</thead>';
        phtml += '<tbody>';
        for (var i=0; i<data.length; i++){
            phtml += '<tr>';
            phtml += '  <td width="85%"><span>'+data[i].name+'</span></td>';
            phtml += '  <td width="15%">';
            phtml += '    <a href="javascript:;" class="btn default btn-xs green-stripe ps-clone-local" data-fullpath="'+data[i].path+'"> 复制到U盘 </a>';
            phtml += '  </td>';
            phtml += '</tr>';
        }
        phtml += '</tbody>';
        phtml += '</table>';
        $("#pi-local-file").html(phtml);
    }

    var ecb_getFiles4Local = function(response) {
        $("#pi-local-file").html('');
    }

    var scb_getFiles4Usb = function(response) {
        var data = response.message;
        var phtml = '';
        phtml += '<table class="table table-hover" align="center">';
        phtml += '<thead>';
        phtml += '<tr>';
        phtml += '  <th width="85%"><span>文件</span></th>';
        phtml += '  <th width="15%"><span>操作</span></th>';
        phtml += '</tr>';
        phtml += '</thead>';
        phtml += '<tbody>';
        for (var i=0; i<data.length; i++){
            phtml += '<tr>';
            phtml += '  <td width="85%"><span>'+data[i].name+'</span></td>';
            phtml += '  <td width="15%">';
            phtml += '    <a href="javascript:;" class="btn default btn-xs green-stripe ps-clone-usb" data-fullpath="'+data[i].path+'"> 复制到终端 </a>';
            phtml += '  </td>';
            phtml += '</tr>';
        }
        phtml += '</tbody>';
        phtml += '</table>';
        $("#pi-usb-file").html(phtml);
    }

    var ecb_getFiles4Usb = function(response) {
        $("#pi-usb-file").html('');
    }

    var dcf_progress;
    var checkFileProgress = function(response) {
        var task_id = $("#ps-task-id").val();
        getFileProgress(scb_getFileProgress, ecb_getFileProgress, task_id);
        dcf_progress = setTimeout(checkFileProgress, 3000);
    }

    var scb_copyFile = function(response) {
        var task_id = response.message;
        $("#dialog-copy-progress").modal('show');
        $("#ps-task-id").val(task_id);
        checkFileProgress();
    }

    var ecb_copyFile = function(response) {
        PageUtil.error("复制文件失败！");
    }

    var scb_getFileProgress = function(response) {
        var progress = response.message;
        if (progress == 'PENDING') {
            $("#ps-task-bar").css({ 'width': '0%' });
            $("#ps-task-bar").html('&nbsp;' + '0%&nbsp;');
        } else if (progress == 'SUCCESS') {
            $("#ps-task-bar").css({ 'width': '100%' });
            $("#ps-task-bar").html('&nbsp;' + '100%&nbsp;');
        } else {
            $("#ps-task-bar").css({ 'width': progress.percent + '%' });
            $("#ps-task-bar").html('&nbsp;' + progress.percent + '%&nbsp;');
        }
    }

    var ecb_getFileProgress = function(response) {
    }

    var exitFileProgress = function() {
        clearTimeout(dcf_progress);
        $("#dialog-copy-progress").modal('hide');
    }

    var handleActions = function(){
        $('body')
        //重启终端
        .on('click', '#ps-reboot', function(e) {
            e.preventDefault();
            reboot(scb_ps_reboot, ecb_ps_reboot);
        })

        //关闭终端
        .on('click', '#ps-shutdown', function(e) {
            e.preventDefault();
            shutdown(scb_ps_shutdown, ecb_ps_shutdown);
        })

        //网络标签
        .on('click', '#ps-tab-network', function(e) {
            e.preventDefault();
            getNetwork(scb_ps_getNetwork, ecb_ps_getNetwork);
            getWifi(scb_ps_getWifi, ecb_ps_getWifi);
            getConnectedWifi(scb_ps_getConnectedWifi, ecb_ps_getConnectedWifi);
        })

        //连接项标签
        .on('click', '#ps-tab-resource', function(e) {
            e.preventDefault();
            getResources(scb_pi_getResources, ecb_pi_getResources);
        })

        //时间标签
        .on('click', '#ps-tab-time', function(e) {
            e.preventDefault();
            getSystemTime(scb_ps_getSystemTime, ecb_ps_getSystemTime);
        })

        //操作标签
        .on('click', '#ps-tab-action', function(e) {
            e.preventDefault();
            //Do nothing
        })

        //关于标签
        .on('click', '#ps-tab-about', function(e) {
            e.preventDefault();
            getSystemInfo(scb_ps_getSystemInfo, ecb_ps_getSystemInfo);
        })

        //有线网络
        .on('change', '#ps-ip-type', function(e) {
            e.preventDefault();
            if ($("select[name='iptype']").val() == "dhcp") {
                $("input[name='ipaddr']" ).attr("readonly", "readonly");
                $("input[name='netmask']").attr("readonly", "readonly");
                $("input[name='gateway']").attr("readonly", "readonly");
            } else if ($("select[name='iptype']").val() == "static") {
                $("input[name='ipaddr']" ).removeAttr("readonly");
                $("input[name='netmask']").removeAttr("readonly");
                $("input[name='gateway']").removeAttr("readonly");
            }
        })

        //保存网络
        .on('click', '#ps-save-network', function(e) {
            e.preventDefault();
            var iptype  = $("select[name='iptype']", $('#form-network-config')).val();
            var ipaddr  = $("input[name='ipaddr']",  $('#form-network-config')).val();
            var netmask = $("input[name='netmask']", $('#form-network-config')).val();
            var gateway = $("input[name='gateway']", $('#form-network-config')).val();
            var dns1    = $("input[name='dns1']",    $('#form-network-config')).val();
            var dns2    = $("input[name='dns2']",    $('#form-network-config')).val();
            saveNetwork(scb_ps_saveNetwork, ecb_ps_saveNetwork, iptype, ipaddr, netmask, gateway, dns1, dns2);
        })

        //应用网络
        .on('click', '#ps-restart-network', function(e) {
            e.preventDefault();
            var iptype  = $("select[name='iptype']", $('#form-network-config')).val();
            var ipaddr  = $("input[name='ipaddr']",  $('#form-network-config')).val();
            var netmask = $("input[name='netmask']", $('#form-network-config')).val();
            var gateway = $("input[name='gateway']", $('#form-network-config')).val();
            var dns1    = $("input[name='dns1']",    $('#form-network-config')).val();
            var dns2    = $("input[name='dns2']",    $('#form-network-config')).val();
            restartNetwork(scb_ps_restartNetwork, ecb_ps_restartNetwork, iptype, ipaddr, netmask, gateway, dns1, dns2);
        })

        //WIFI网络
        .on('click', '#ps-refresh-wifi', function(e) {
            e.preventDefault();
            getWifi(scb_ps_getWifi, ecb_ps_getWifi);
        })

        .on('click', '#ps-connect-wifi', function(e) {
            e.preventDefault();
            var wifiname = $("#ps-wifi-name").val();
            var password = $("#ps-wifi-password").val();
            connectWifi(scb_ps_connectWifi, ecb_ps_connectWifi, wifiname, password);
        })

        .on('click', '#ps-disconnect-wifi', function(e) {
            e.preventDefault();
            var wifi = $("#ps-connected-wifi-name").val();
            disconnectWifi(scb_ps_disconnectWifi, ecb_ps_disconnectWifi, wifi);
        })

        //网络测试
        .on('click', '#ps-ping', function(e) {
            e.preventDefault();
            $('#ps-stop-ping').focus();
            ping('start');
        })

        .on('keydown', '#ps-ip', function(e) {
            if (e.which == 13) {
                e.preventDefault();
                $('#ps-stop-ping').focus();
                ping('start');
            }
        })

        .on('click', '#ps-stop-ping', function(e) {
            e.preventDefault();
            $('#ps-ping').focus();
            ping('stop');
        })

        .on('click', '#pi-add-sdesktop', function(e) {
            e.preventDefault();
            var $el = $(this);
            $("input[name='id']",       $addSPICEDesktopForm).val("");
            $("input[name='nickname']", $addSPICEDesktopForm).val("");
            $("input[name='serverip']", $addSPICEDesktopForm).val("");
            $("input[name='username']", $addSPICEDesktopForm).val("");
            $("input[name='password']", $addSPICEDesktopForm).val("");
            $("input[name='domain']",   $addSPICEDesktopForm).val("");
            $("input[name='autolink']", $addSPICEDesktopForm).prop("checked", false);
            $("#dialog-add-sdesktop").modal('show');
            $("#pi-cur-sdesktop").val('');
            setTimeout(function () {
                $("input[name='nickname']", $addSPICEDesktopForm).focus();
            }, 800);
        })
        .on('click', '#pi-add-rdesktop', function(e) {
            e.preventDefault();
            var $el = $(this);
            $("input[name='id']",       $addRDPDesktopForm).val("");
            $("input[name='nickname']", $addRDPDesktopForm).val("");
            $("input[name='serverip']", $addRDPDesktopForm).val("");
            $("input[name='username']", $addRDPDesktopForm).val("");
            $("input[name='password']", $addRDPDesktopForm).val("");
            $("input[name='domain']",   $addRDPDesktopForm).val("");
            $("input[name='autolink']", $addRDPDesktopForm).prop("checked", false);
            $("#dialog-add-rdesktop").modal('show');
            $("#pi-cur-rdesktop").val('');
            setTimeout(function () {
                $("input[name='nickname']", $addRDPDesktopForm).focus();
            }, 800);
        })
        .on('click', '#pi-add-vdesktop', function(e) {
            e.preventDefault();
            var $el = $(this);
            $("input[name='id']",       $addVMWAREDesktopForm).val("");
            $("input[name='nickname']", $addVMWAREDesktopForm).val("");
            $("input[name='serverip']", $addVMWAREDesktopForm).val("");
            $("input[name='username']", $addVMWAREDesktopForm).val("");
            $("input[name='password']", $addVMWAREDesktopForm).val("");
            $("input[name='autolink']", $addVMWAREDesktopForm).prop("checked", false);
            $("#dialog-add-vdesktop").modal('show');
            setTimeout(function () {
                $("input[name='nickname']", $addVMWAREDesktopForm).focus();
            }, 800);
        })
        .on('click', '#pi-add-cdesktop', function(e) {
            e.preventDefault();
            var $el = $(this);
            $("input[name='id']",       $addCITRIXDesktopForm).val("");
            $("input[name='nickname']", $addCITRIXDesktopForm).val("");
            $("input[name='serverip']", $addCITRIXDesktopForm).val("");
            $("input[name='autolink']", $addCITRIXDesktopForm).prop("checked", false);
            $("#dialog-add-cdesktop").modal('show');
            setTimeout(function () {
                $("input[name='nickname']", $addCITRIXDesktopForm).focus();
            }, 800);
        })
        .on('click', '#pi-add-idesktop', function(e) {
            e.preventDefault();
            var $el = $(this);
            $("input[name='id']",       $addIDVDesktopForm).val("");
            $("input[name='nickname']", $addIDVDesktopForm).val("");
            $("input[name='serverip']", $addIDVDesktopForm).val("localhost");
            $("input[name='username']", $addIDVDesktopForm).val("");
            $("input[name='autolink']", $addIDVDesktopForm).prop("checked", false);
            $("#dialog-add-idesktop").modal('show');
            $("#pi-cur-idesktop").val('');
            getIdvs(scb_pi_getIdvs, ecb_pi_getIdvs);
            setTimeout(function () {
                $("input[name='nickname']", $addIDVDesktopForm).focus();
            }, 800);
        })
        .on('click', 'a.pi-edit-sdesktop', function(e) {
            e.preventDefault();
            var $el = $(this);
            $("input[name='id']",       $addSPICEDesktopForm).val($el.data('id'));
            $("input[name='nickname']", $addSPICEDesktopForm).val($el.data('nickname'));
            $("input[name='product']",  $addSPICEDesktopForm).val($el.data('product'));
            $("input[name='serverip']", $addSPICEDesktopForm).val($el.data('serverip'));
            $("input[name='username']", $addSPICEDesktopForm).val($el.data('username'));
            $("input[name='password']", $addSPICEDesktopForm).val($el.data('password'));
            $("input[name='domain']",   $addSPICEDesktopForm).val($el.data('domain'));
            if ($el.data('autolink') == 1) {
                $("input[name='autolink']", $addSPICEDesktopForm).prop("checked", true);
            } else {
                $("input[name='autolink']", $addSPICEDesktopForm).prop("checked", false);
            }
            $("#dialog-add-sdesktop").modal('show');
            setTimeout(function () {
                $("input[name='nickname']", $addSPICEDesktopForm).focus();
            }, 800);
        })
        .on('click', 'a.pi-edit-rdesktop', function(e) {
            e.preventDefault();
            var $el = $(this);
            $("input[name='id']",       $addRDPDesktopForm).val($el.data('id'));
            $("input[name='nickname']", $addRDPDesktopForm).val($el.data('nickname'));
            $("input[name='product']",  $addRDPDesktopForm).val($el.data('product'));
            $("input[name='serverip']", $addRDPDesktopForm).val($el.data('serverip'));
            $("input[name='username']", $addRDPDesktopForm).val($el.data('username'));
            $("input[name='password']", $addRDPDesktopForm).val($el.data('password'));
            $("input[name='domain']",   $addRDPDesktopForm).val($el.data('domain'));
            if ($el.data('autolink') == 1) {
                $("input[name='autolink']", $addRDPDesktopForm).prop("checked", true);
            } else {
                $("input[name='autolink']", $addRDPDesktopForm).prop("checked", false);
            }
            $("#dialog-add-rdesktop").modal('show');
            $("#pi-cur-rdesktop").val($el.data('username'));
            setTimeout(function () {
                $("input[name='nickname']", $addRDPDesktopForm).focus();
            }, 800);
        })
        .on('click', 'a.pi-edit-vdesktop', function(e) {
            e.preventDefault();
            var $el = $(this);
            $("input[name='id']",       $addVMWAREDesktopForm).val($el.data('id'));
            $("input[name='nickname']", $addVMWAREDesktopForm).val($el.data('nickname'));
            $("input[name='product']",  $addVMWAREDesktopForm).val($el.data('product'));
            $("input[name='serverip']", $addVMWAREDesktopForm).val($el.data('serverip'));
            $("input[name='username']", $addVMWAREDesktopForm).val($el.data('username'));
            $("input[name='password']", $addVMWAREDesktopForm).val($el.data('password'));
            if ($el.data('autolink') == 1) {
                $("input[name='autolink']", $addVMWAREDesktopForm).prop("checked", true);
            } else {
                $("input[name='autolink']", $addVMWAREDesktopForm).prop("checked", false);
            }
            $("#dialog-add-vdesktop").modal('show');
            setTimeout(function () {
                $("input[name='nickname']", $addVMWAREDesktopForm).focus();
            }, 800);
        })
        .on('click', 'a.pi-edit-cdesktop', function(e) {
            e.preventDefault();
            var $el = $(this);
            $("input[name='id']",       $addCITRIXDesktopForm).val($el.data('id'));
            $("input[name='nickname']", $addCITRIXDesktopForm).val($el.data('nickname'));
            $("input[name='product']",  $addCITRIXDesktopForm).val($el.data('product'));
            $("input[name='serverip']", $addCITRIXDesktopForm).val($el.data('serverip'));
            if ($el.data('autolink') == 1) {
                $("input[name='autolink']", $addCITRIXDesktopForm).prop("checked", true);
            } else {
                $("input[name='autolink']", $addCITRIXDesktopForm).prop("checked", false);
            }
            $("#dialog-add-cdesktop").modal('show');
            setTimeout(function () {
                $("input[name='nickname']", $addCITRIXDesktopForm).focus();
            }, 800);
        })
        .on('click', 'a.pi-edit-idesktop', function(e) {
            e.preventDefault();
            var $el = $(this);
            $("input[name='id']",       $addIDVDesktopForm).val($el.data('id'));
            $("input[name='nickname']", $addIDVDesktopForm).val($el.data('nickname'));
            $("input[name='product']",  $addIDVDesktopForm).val($el.data('product'));
            $("input[name='serverip']", $addIDVDesktopForm).val($el.data('serverip'));
            if ($el.data('autolink') == 1) {
                $("input[name='autolink']", $addIDVDesktopForm).prop("checked", true);
            } else {
                $("input[name='autolink']", $addIDVDesktopForm).prop("checked", false);
            }
            $("#dialog-add-idesktop").modal('show');
            $("#pi-cur-idesktop").val($el.data('nickname'));
            getIdvs(scb_pi_getIdvs, ecb_pi_getIdvs);
            setTimeout(function () {
                $("input[name='nickname']", $addIDVDesktopForm).focus();
            }, 800);
        })

        .on('click', 'a.pi-remove', function(e) {
            e.preventDefault();
            var id = $(this).data('id');
            removeResource(scb_removeResource, ecb_removeResource, id);
        })

        //时间
        .on('click', '#ps-set-time', function(e) {
            e.preventDefault();
            year   = $("#ps-datepicker").datepicker('getDate').getFullYear();
            month  = $("#ps-datepicker").datepicker('getDate').getMonth() + 1;
            day    = $("#ps-datepicker").datepicker('getDate').getDate();
            hour   = $("#ps-timepicker").data('timepicker').hour;
            minute = $("#ps-timepicker").data('timepicker').minute;
            second = $("#ps-timepicker").data('timepicker').second;
            setSystemTime(scb_ps_setSystemTime, ecb_ps_setSystemTime, year, month, day, hour, minute, second);
        })

        //设置密码
        .on('click', '#ps-password', function(e) {
            e.preventDefault();
            $("input[name='password1']", $('#form-set-password')).val("");
            $("input[name='password2']", $('#form-set-password')).val("");
            $("#dialog-set-password").modal('show');
        })

        //切换系统
        .on('click', '#ps-bootloader', function(e) {
            e.preventDefault();
            $("#dialog-terminal-bootloader").modal({show:true, keyboard:false});
            listBootLoader(scb_ps_listBootLoader, ecb_ps_listBootLoader, 'sda1');
        })

        .on('change', '.ps-dtb-checkbox',
        function(e) {
            e.preventDefault();
            $(".ps-dtb-checkbox").each(function(){
                $(this).prop('checked', false);
            });
            var uuid = $(this).data("uuid");
            $('#ps-dtb-'+uuid).prop('checked', true);
        })

       .on('click', '#ps-change-bootloader',
        function(e) {
            e.preventDefault();
            var uuid = '';
            $(".ps-dtb-checkbox").each(function(){
                if ($(this).prop('checked') == true) {
                    uuid = $(this).data("uuid");
                }
            });
            if (uuid != '') {
                changeBootLoader(scb_ps_changeBootLoader, ecb_ps_changeBootLoader, 'sda1', uuid);
            }
        })

        //保存系统
        .on('click', '#ps-save', function(e) {
            e.preventDefault();
            $('#ps-dss-type').val('disk');
            $('#ps-dss-path').val('');
            $("#dialog-save-system").modal({show:true, keyboard:false});
            querySystem(scb_ps_querySystem4Save, ecb_ps_querySystem4Save);
        })

        .on('change', '#ps-dss-type',
        function(e) {
            e.preventDefault();
            querySystem(scb_ps_querySystem4Save, ecb_ps_querySystem4Save);
        })

        .on('click', '#ps-dss-all-diskparts',
        function(e) {
            e.preventDefault();
            var r = $('#ps-dss-all-diskparts').val();
            if (r) {
                $("#ps-dss-all-diskparts option[value='" + r + "']").remove();
                $('#ps-dss-diskparts').append('<option value=\'' + r + '\'>' + r + '</option>');
            }
        })

        .on('click', '#ps-dss-diskparts',
        function(e) {
            e.preventDefault();
            var r = $('#ps-dss-diskparts').val();
            if (r) {
                $("#ps-dss-diskparts option[value='" + r + "']").remove();
                $('#ps-dss-all-diskparts').append('<option value=\'' + r + '\'>' + r + '</option>');
            }
        })

        .on('click', '#ps-do-save',
        function(e) {
            e.preventDefault();
            var type = $("#ps-dss-type").val();
            var dps = diskparts_save_selected();
            if (dps == '') {
                $("#ps-dss-diskparts-checker").html('<span style="color: #A94442;" class="help-block">请选择至少一个磁盘或分区</span>');
                return;
            } else {
                $("#ps-dss-diskparts-checker").html('');
            }
            var path = $('#ps-dss-path').val();
            PageUtil.confirm("保存终端将终端本地磁盘中的系统保存到本地或远程导出的目录下。请注意：保存终端将破坏本地或远程导出目录下的镜像文件，如果有的话，请谨慎操作！！！根据终端磁盘大小和网络速度，保存可能需要20分钟以上的时间，并且，在保存结束之前，不能关闭此浏览器。您确定要保存吗？", function() {
                saveSystem(scb_ps_saveSystem, ecb_ps_saveSystem, type, dps, path);
            }, "Warning");
        })

        //恢复系统
        .on('click', '#ps-restore', function(e) {
            e.preventDefault();
            $('#ps-drs-type').val('disk');
            $('#ps-drs-path').val('');
            $("#dialog-restore-system").modal({show:true, keyboard:false});
            querySystem(scb_ps_querySystem4Restore, ecb_ps_querySystem4Restore);
        })

        .on('change', '#ps-drs-type',
        function(e) {
            e.preventDefault();
            querySystem(scb_ps_querySystem4Restore, ecb_ps_querySystem4Restore);
        })

        .on('click', '#ps-drs-all-diskparts',
        function(e) {
            e.preventDefault();
            var r = $('#ps-drs-all-diskparts').val();
            if (r) {
                $("#ps-drs-all-diskparts option[value='" + r + "']").remove();
                $('#ps-drs-diskparts').append('<option value=\'' + r + '\'>' + r + '</option>');
            }
        })

        .on('click', '#ps-drs-diskparts',
        function(e) {
            e.preventDefault();
            var r = $('#ps-drs-diskparts').val();
            if (r) {
                $("#ps-drs-diskparts option[value='" + r + "']").remove();
                $('#ps-drs-all-diskparts').append('<option value=\'' + r + '\'>' + r + '</option>');
            }
        })

        .on('click', '#ps-do-restore',
        function(e) {
            e.preventDefault();
            var type = $("#ps-drs-type").val();
            var dps = diskparts_restore_selected();
            if (dps == '') {
                $("#ps-drs-diskparts-checker").html('<span style="color: #A94442;" class="help-block">>请选择至少一个磁盘或分区</span>');
                return;
            } else {
                $("#ps-drs-diskparts-checker").html('');
            }
            var path = $('#ps-drs-path').val();
            PageUtil.confirm("恢复终端将保存在本地或远程导出的目录中的系统数据恢复到终端的本地磁盘中。请注意：恢复终端将破坏终端本地磁盘中的所有数据，请谨慎操作！！！根据终端磁盘大小和网络速度，恢复可能需要20分钟以上的时间，并且，在恢复结束之前，不能关闭此浏览器。您确定要恢复吗？", function() {
                restoreSystem(scb_ps_restoreSystem, ecb_ps_restoreSystem, type, dps, path);
            }, "Warning");
        })

        //系统上传
        .on('click', '#ps-upload', function(e) {
            e.preventDefault();
            $('#ps-dus-path').val('');
            $("#dialog-upload-system").modal({show:true, keyboard:false});
        })

        .on('click', '#ps-upload-system', function(e) {
            e.preventDefault();
            var path = $('#ps-dus-path').val();
            if (path == '') {
                return;
            }
            PageUtil.confirm("上传系统将保存在终端本地磁盘中的系统上传到远程导出的目录下。请注意：上传系统将破坏远程导出目录下的镜像文件，如果有的话，请谨慎操作！！！根据系统镜像大小和网络速度，上传可能需要20分钟以上的时间，并且，在上传结束之前，不能关闭此浏览器。您确定要上传吗？", function() {
                uploadSystem(scb_ps_uploadSystem, ecb_ps_uploadSystem, path);
            }, "Warning");
        })

        //系统下载
        .on('click', '#ps-download', function(e) {
            e.preventDefault();
            $('#ps-dds-path').val('');
            $("#dialog-download-system").modal({show:true, keyboard:false});
        })

        .on('click', '#ps-download-system', function(e) {
            e.preventDefault();
            var path = $('#ps-dds-path').val();
            if (path == '') {
                return;
            }
            PageUtil.confirm("下载系统将保存在远程导出目录下的系统下载到终端的本地磁盘中。请注意：下载系统将破坏终端本地磁盘中的镜像文件，如果有的话，请谨慎操作！！！根据系统镜像大小和网络速度，下载可能需要20分钟以上的时间，并且，在下载结束之前，不能关闭此浏览器。您确定要下载吗？", function() {
                downloadSystem(scb_ps_downloadSystem, ecb_ps_downloadSystem, path);
            }, "Warning");
        })

        //USB共享
        .on('click', '#ps-usbredir', function(e) {
            e.preventDefault();
            $("#dialog-redirect-usb").modal({show:true, keyboard:false});
            getUsbdStatus(scb_ps_getUsbdStatus, ecb_ps_getUsbdStatus);
        })

        .on('click', '#ps-start-usbd', function(e) {
            e.preventDefault();
            startUsbdService(scb_ps_startUsbdService, ecb_ps_startUsbdService);
        })

        .on('click', '#ps-stop-usbd', function(e) {
            e.preventDefault();
            stopUsbdService(scb_ps_stopUsbdService, ecb_ps_stopUsbdService);
        })

        .on('click', '#ps-create-callback', function(e) {
            e.preventDefault();
            var dip = $('#ps-desk-ipaddr').val();
            var dport = $('#ps-desk-port').val();
            if (dip == '' || dport == '') {
                return;
            }
            createUsbdCallback(scb_ps_createUsbdCallback, ecb_ps_createUsbdCallback, dip, dport);
        })

        .on('click', '#ps-close-callback', function(e) {
            e.preventDefault();
            closeUsbdCallback(scb_ps_closeUsbdCallback, ecb_ps_closeUsbdCallback);
        })

        .on('click', '.ps-share-usb', function(e) {
            e.preventDefault();
            var uid = $(this).data('uid');
            shareUsbDevice(scb_ps_shareUsbDevice, ecb_ps_shareUsbDevice, uid);
        })

        .on('click', '.ps-unshare-usb', function(e) {
            e.preventDefault();
            var uid = $(this).data('uid');
            unshareUsbDevice(scb_ps_unshareUsbDevice, ecb_ps_unshareUsbDevice, uid);
        })

        .on('click', '#ps-refresh-usbredir', function(e) {
            e.preventDefault();
            getUsbdStatus(scb_ps_getUsbdStatus, ecb_ps_getUsbdStatus);
        })

        //系统升级
        .on('click', '#ps-upgrade-system', function(e) {
            e.preventDefault();
            upgradeSystem(scb_ps_upgradeSystem, ecb_ps_upgradeSystem);
        })

        //许可证上传
        .on('click', '#ps-upload-license', function(e) {
            e.preventDefault();
            var module = $('#ps-license-module').val();
            uploadLicense(scb_ps_uploadLicense, ecb_ps_uploadLicense, module);
        })

        .on('click', '#ps-file', function(e) {
            e.preventDefault();
            $("#dialog-file").modal({show:true, keyboard:false});
        })

        .on('click', '#ps-df-mount', function(e) {
            e.preventDefault();
            mountUsb(scb_mountUsb, ecb_mountUsb);
        })

        .on('click', '#ps-df-unmount', function(e) {
            e.preventDefault();
            unmountUsb(scb_unmountUsb, ecb_unmountUsb);
        })

        .on('click', '#ps-df-refresh', function(e) {
            e.preventDefault();
            var path = $("#ps-df-path").val();
            if (path == '') {
                return;
            }
            getFiles(scb_getFiles4Local, ecb_getFiles4Local, path);
        })

        .on('click', '.ps-clone-local', function(e) {
            e.preventDefault();
            var $el = $(this);
            var sfile = $(this).data("fullpath");
            var dpath = '/mnt/usb';
            copyFile(scb_copyFile, ecb_copyFile, sfile, dpath);
        })

        .on('click', '.ps-clone-usb', function(e) {
            e.preventDefault();
            var $el = $(this);
            var sfile = $(this).data("fullpath");
            var dpath = $("#ps-df-path").val();
            if (dpath == '') {
                return;
            }
            copyFile(scb_copyFile, ecb_copyFile, sfile, dpath);
        })

        .on('click', '#ps-end-copy-progress', function(e) {
            e.preventDefault();
            exitFileProgress();
        })

        //下载日志
        .on('click', '#ps-export-log', function(e) {
            e.preventDefault();
            getSystemLog(scb_ps_getSystemLog, ecb_ps_getSystemLog);
        })

        //
        .on('click', '#ps-reset', function(e) {
            e.preventDefault();
            resetSystem(scb_ps_resetSystem, ecb_ps_resetSystem);
        })

    }

    return {
        init: function () {
            handleFormValidation();
            handleActions();
            getNetwork(scb_ps_getNetwork, ecb_ps_getNetwork);
            getWifi(scb_ps_getWifi, ecb_ps_getWifi);
            getConnectedWifi(scb_ps_getConnectedWifi, ecb_ps_getConnectedWifi);
        }
    };
}();


var scb_ps_ping2 = function(response) {
    $("#ps-ping-info").append(response.message + "<BR>");
}

var ecb_ps_ping2 = function(response) {
}

var pingi;

var scb_ps_ping1 = function(response) {
    $("#ps-ping-info").append(response.message + "<BR>");
    pingi = setInterval(function() {
        var ip = $("input[id='ps-ip']").val();
        ping2(scb_ps_ping2, ecb_ps_ping2, ip);
    }, 1200);
}

var ecb_ps_ping1 = function(response) {
    PageUtil.error(response.message);
}


function ping(action){
    if (action == 'stop') {
        clearInterval(pingi);
    } else if (action == 'start') {
        clearInterval(pingi);
        $("#ps-ping-info").html("");
        var ip = $("input[id='ps-ip']").val();
        ping1(scb_ps_ping1, ecb_ps_ping1, ip);
    }
};
