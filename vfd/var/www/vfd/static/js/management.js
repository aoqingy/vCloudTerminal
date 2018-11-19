var ManagementObj = function() {
    var initGrid = function() {
        $("#pm-ip-start").val('');
        $("#pm-ip-end").val('');
        jQuery("#grid-pm-terminal").jqGrid({
            url: '/terminal/list',
            width: 710,
            height: 250,
            multiselect: true,
            datatype:"json",
            colNames: ['id', 'MAC地址', 'IP地址', '状态', '上线时间'],
            colModel: [{
                name: 'id',
                index: 'id',
                hidden: true,
                search: false
            },
            {
                name: 'mac',
                index: 'mac',
                width: 120
            },
            {
                name: 'ip',
                index: 'ip',
                width: 90,
                formatter: function(v) {
                    return '<a href="http://' + v + '">' + v + '</a>';
                }
            },
            {
                name: 'status',
                index: 'status',
                width: 60,
                sortable: false
            },
            {
                name: 'uptime',
                index: 'uptime',
                width: 90,
                sortable: false,
                formatter: function(v) {
                    if (v) {
                        return v['day'] + '天' + v['hour'] + '小时' + v['minute'] + '分' + v['second'] + '秒';
                    } else {
                        return '';
                    }
                }
            }],
            rowNum: 100,
            rowList: [100],
            rownumbers: false,
            //gridview: true,
            jsonReader: {
                repeatitems: false
            },
            pager: '#pager-pm-terminal',
            viewrecords: true,
            sortorder: "asc",
        });
    }

    var $updateForm = $('#form-update-terminal'), $updateFormError = $('.alert-danger', $updateForm), $updateFormWarning = $('.alert-warning', $updateForm),
        updateFormSubmitFormOptions = {
            dataType: 'json',
            url: '/terminal/update',
            type: 'POST',
            beforeSend: function(){
                PageUtil.showMaskLayer();
            },
            success: function(response){
                PageUtil.hideMaskLayer();
                if (response.code == "True") {
                    PageUtil.alert(response.message);
                } else {
                    PageUtil.error(response.message);
                }
            },
            error: function(){
                PageUtil.hideMaskLayer();
                PageUtil.error('请选择正确的文件');
            }
        };

    var $uploadLicForm = $('#form-upload-mgmt-lic'), $uploadLicFormError = $('.alert-danger', $uploadLicForm), $uploadLicFormWarning = $('.alert-warning', $uploadLicForm),
        uploadLicFormSubmitFormOptions = {
            dataType: 'json',
            url: '/management/upload',
            type: 'POST',
            beforeSend: function(){
                PageUtil.showMaskLayer();
            },
            success: function(response){
                PageUtil.hideMaskLayer();
                if (response.code == "True") {
                    $("#dialog-upload-mgmt-lic").modal("hide");
                    PageUtil.alert("上传管理许可证成功！");
                    $("#grid-pm-terminal").trigger("reloadGrid");   //管理许可证删除后，要重新加载终端列表(aoqingy)
                } else {
                    PageUtil.error("上传管理许可证失败！");
                }
            },
            error: function(){
                PageUtil.hideMaskLayer();
                PageUtil.error('请选择正确的文件');
            }
        };

    var $addConnectionForm = $('#form-add-connection'), $addConnectionFormError = $('.alert-danger', $addConnectionForm), $addConnectionFormWarning = $('.alert-warning', $addConnectionForm),
        addConnectionFormSubmitFormOptions = {
            dataType: 'json',
            url: '/terminal/connection/add',
            type: 'POST',
            beforeSend: function(){
                PageUtil.showMaskLayer();
            },
            success: function(response){
                $("#dialog-add-connection").modal("hide");
                PageUtil.hideMaskLayer();
                if (response.code == "True") {
                    PageUtil.alert("添加终端连接成功！");
                } else {
                    PageUtil.error("添加终端连接失败！");
                }
            },
            error: function(){
                PageUtil.hideMaskLayer();
                PageUtil.error('请选择正确的文件');
            }
        };

    var handleFormValidation = function(){
        jQuery.validator.addMethod("name_regex", function(value, element) {
            return this.optional(element) || /^[\w-_.\u4e00-\u9fa5]+$/i.test(value);
        }, "only special word");

        jQuery.validator.addMethod("http_regex", function(value, element) {
            return this.optional(element) || /^[\w-_.:\/]+$/i.test(value);
        }, "only special word");

        $('#form-update-terminal').validate({
            errorElement: 'span',
            errorClass: 'help-block',
            focusInvalid: false,
            rules: {
            },
            messages: {
            },
            invalidHandler: function (event, validator) {
                $updateFormWarning.hide();
                $updateFormError.show();
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
                $(form).ajaxSubmit(updateFormSubmitFormOptions);
            }
        });

        $('#form-upload-mgmt-lic').validate({
            errorElement: 'span',
            errorClass: 'help-block',
            focusInvalid: false,
            rules: {
            },
            messages: {
            },
            invalidHandler: function (event, validator) {
                $uploadLicFormWarning.hide();
                $uploadLicFormError.show();
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
                $(form).ajaxSubmit(uploadLicFormSubmitFormOptions);
            }
        });

        $('#form-add-connection').validate({
            errorElement: 'span',
            errorClass: 'help-block',
            focusInvalid: false,
            rules: {
                cname:      { required: true, maxlength: 20, name_regex: true },
                caddress:   { required: true, http_regex: true },
                //uprefix:    { required: true, maxlength: 20, name_regex: true },
                domain:     { maxlength: 20, name_regex: true },
            },
            messages: {
                cname:      { required: "名称不能为空", maxlength: "名称长度不能超过20个字符", name_regex: "名称只能包含中文、英文、数字、-、_、." },
                caddress:   { required: "服务器地址不能为空", http_regex: "服务器地址中含有特殊字符" },
                //uprefix:    { required: "名称不能为空", maxlength: "名称长度不能超过20个字符", name_regex: "名称只能包含中文、英文、数字、-、_、." },
                domain:     { maxlength: "名称长度不能超过20个字符", name_regex: "名称只能包含中文、英文、数字、-、_、." },
            },
            invalidHandler: function (event, validator) {
                $addConnectionFormWarning.hide();
                $addConnectionFormError.show();
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
                $(form).ajaxSubmit(addConnectionFormSubmitFormOptions);
            }
        });

        $("#dac-cancel-add-connection").click(function() {
            $addConnectionForm.validate().resetForm();
            $("label", $addConnectionForm).closest('.form-group').removeClass('has-error');
        });
    }

    var scb_pm_scanTerminals = function(response) {
        $("#grid-pm-terminal").trigger("reloadGrid");
    }

    var ecb_pm_scanTerminals = function(response) {
        PageUtil.error("扫描终端失败！");
    }

    var scb_pm_refreshTerminals = function(response) {
        $("#grid-pm-terminal").trigger("reloadGrid");
    }

    var ecb_pm_refreshTerminals = function(response) {
        PageUtil.error("刷新数据库失败！");
    }

    var scb_pm_clearTerminals = function(response) {
        $("#grid-pm-terminal").trigger("reloadGrid");
    }

    var ecb_pm_clearTerminals = function(response) {
        PageUtil.error("清空数据库失败！");
    }

    var scb_pm_removeManagementLic = function(response) {
        PageUtil.alert("删除管理许可证成功！");
        $("#grid-pm-terminal").trigger("reloadGrid");	//管理许可证删除后，要重新加载终端列表(aoqingy)
    }

    var ecb_pm_removeManagementLic = function(response) {
        PageUtil.error("删除管理许可证失败！");
    }

    var scb_pm_clearResourceDb = function(response) {
        PageUtil.alert("清空连接项成功！");
    }

    var ecb_pm_clearResourceDb = function(response) {
        PageUtil.error("清空连接项失败！");
    }

    var scb_pm_wakeupTerminals = function(response) {
        $("#grid-pm-terminal").trigger("reloadGrid");
    }

    var ecb_pm_wakeupTerminals = function(response) {
        PageUtil.error("唤醒终端失败！");
    }

    var scb_pm_shutdownTerminals = function(response) {
        $("#grid-pm-terminal").trigger("reloadGrid");
    }

    var ecb_pm_shutdownTerminals = function(response) {
        PageUtil.error("关闭终端失败！");
    }

    var scb_pm_rebootTerminals = function(response) {
        $("#grid-pm-terminal").trigger("reloadGrid");
    }

    var ecb_pm_rebootTerminals = function(response) {
        PageUtil.error("重启终端失败！");
    }

    var scb_pm_enableTerminals = function(response) {
        $("#grid-pm-terminal").trigger("reloadGrid");
    }

    var ecb_pm_enableTerminals = function(response) {
        PageUtil.error("启用终端失败！");
    }

    var scb_pm_disableTerminals = function(response) {
        $("#grid-pm-terminal").trigger("reloadGrid");
    }

    var ecb_pm_disableTerminals = function(response) {
        PageUtil.error("禁用终端失败！");
    }

    var scb_pm_getTerminalInfo = function(response) {
        //PageUtil.alert(JSON.stringify(response.message));
        $("#kernel").html(response.message.kernel);
        $("#vfd_ver").html(response.message.vfd_ver);
        $("#mem_free").html(response.message.mem_free);
        $("#lic_days").html(response.message.lic_days);
        $("#uptime").html(response.message.uptime.day+"天 "+response.message.uptime.hour+"小时 "+response.message.uptime.minute+"钟 ");
        $("#mac").html(response.message.mac);
        $("#lic_status").html(response.message.lic_status);
        $("#cpu_core").html(response.message.cpu_core);
        $("#mem_total").html(response.message.mem_total);
        $("#disk").html(response.message.disk);
        $("#cpu_model").html(response.message.cpu_model);
        $("#dialog-info").modal("show");
    }

    var ecb_pm_getTerminalInfo = function(response) {
        PageUtil.error("获取终端信息失败！");
    }

    var scb_pm_getTerminalTime = function(response) {
        var data = response.message;
        $('#dst-datepicker').datepicker("update", new Date(data.year, data.month-1, data.day));
        var hour   = data.hour;
        var minute = data.minute;
        if (data.minute < 10){
             minute.toString();
             minute = "0" + minute;
        }
        $("#dst-timepicker").val(hour+":"+minute);
    }

    var ecb_pm_getTerminalTime = function(response) {
        PageUtil.error("获取终端时间失败！");
        //这里要清除日期和时间(aoqingy)
    }

    var scb_pm_setTerminalTime = function(response) {
        PageUtil.alert("设置终端时间成功！");
    }

    var ecb_pm_setTerminalTime = function(response) {
        PageUtil.error("设置终端时间失败！");
    }
/*
    var scb_pm_addTerminalConnectionByFile = function(response) {
        PageUtil.alert("添加终端连接成功！");
    }

    var ecb_pm_addTerminalConnectionByFile = function(response) {
        PageUtil.error("添加终端连接失败！");
    }

    var scb_pm_addTerminalConnection = function(response) {
        PageUtil.alert("添加终端连接成功！");
    }

    var ecb_pm_addTerminalConnection = function(response) {
        PageUtil.error("添加终端连接失败！");
    }
*/

    var scb_pi_reboot = function(response) {
        PageUtil.alert(response.message);
    }
    var ecb_pi_reboot = function(response) {
    }
    var scb_pi_shutdown = function(response) {
        PageUtil.alert(response.message);
    }
    var ecb_pi_shutdown = function(response) {
    }

    var scb_pm_removeTerminals = function(response) {
        $("#grid-pm-terminal").trigger("reloadGrid");
    }

    var ecb_pm_removeTerminals = function(response) {
        PageUtil.error("删除终端失败！");
    }

    var handleActions = function() {
        $('body')
        .on('click', '#pi-reboot', function(e) {
            e.preventDefault();
            reboot(scb_pi_reboot, ecb_pi_reboot);
        })
        .on('click', '#pi-shutdown', function(e) {
            e.preventDefault();
            shutdown(scb_pi_shutdown, ecb_pi_shutdown);
        })
        .on('click', '#pm-ip-search',
        function(e) {
            e.preventDefault();
            var ipstart = $('#pm-ip-start').val();
            var ipend   = $('#pm-ip-end').val();
            if (ipstart == '') {
                //$("#pm-ip-checker").html('<span style="color: #A94442;" class="help-block">请至少输入起始IP地址！</span>');
                return;
                //$("#pm-ip-checker").html('');
            }
            scanTerminals(scb_pm_scanTerminals, ecb_pm_scanTerminals, ipstart, ipend);
        })

        .on('click', '#pm-refresh',
        function(e) {
            e.preventDefault();
            refreshTerminals(scb_pm_refreshTerminals, ecb_pm_refreshTerminals);
        })

        .on('click', '#pm-clear',
        function(e) {
            e.preventDefault();
            PageUtil.confirm("确定需要清空终端列表吗？",
            function() {
                clearTerminals(scb_pm_clearTerminals, ecb_pm_clearTerminals);
            },
            "Warning");
        })

        .on('click', '#mgmt-lic-remove',
        function(e) {
            e.preventDefault();
            PageUtil.confirm("确定删除管理许可证吗？",
            function() {
                removeManagementLic(scb_pm_removeManagementLic, ecb_pm_removeManagementLic);
            },
            "Warning");
        })

        .on('click', '#pm-wakeup',
        function(e) {
            e.preventDefault();
            var macs = terminal_macs_selected();
            if (macs.length > 0) {
                wakeupTerminals(scb_pm_wakeupTerminals, ecb_pm_wakeupTerminals, macs);
            } else {
                PageUtil.error("请选择至少一个终端！");
            }
        })

        .on('click', '#pm-shutdown',
        function(e) {
            e.preventDefault();
            var macs = terminal_macs_selected();
            if (macs.length > 0) {
                shutdownTerminals(scb_pm_shutdownTerminals, ecb_pm_shutdownTerminals, macs);
            } else {
                PageUtil.error("请选择至少一个终端！");
            }
        })

        .on('click', '#pm-reboot',
        function(e) {
            e.preventDefault();
            var macs = terminal_macs_selected();
            if (macs.length > 0) {
                rebootTerminals(scb_pm_rebootTerminals, ecb_pm_rebootTerminals, macs);
            } else {
                PageUtil.error("请选择至少一个终端！");
            }
        })

        .on('click', '#pm-enable',
        function(e) {
            e.preventDefault();
            var macs = terminal_macs_selected();
            if (macs.length > 0) {
                enableTerminals(scb_pm_enableTerminals, ecb_pm_enableTerminals, macs);
            } else {
                PageUtil.error("请选择至少一个终端！");
            }
        })

        .on('click', '#pm-disable',
        function(e) {
            e.preventDefault();
            var macs = terminal_macs_selected();
            if (macs.length > 0) {
                disableTerminals(scb_pm_disableTerminals, ecb_pm_disableTerminals, macs);
            } else {
                PageUtil.error("请选择至少一个终端！");
            }
        })

        .on('click', '#pm-info',
        function(e) {
            e.preventDefault();
            var ids = $("#grid-pm-terminal").jqGrid("getGridParam", "selarrrow");
            if (ids.length == 1) {
                var rowData = $("#grid-pm-terminal").jqGrid('getRowData', ids[0]);
                getTerminalInfo(scb_pm_getTerminalInfo, ecb_pm_getTerminalInfo, rowData.mac);
            } else {
                PageUtil.error("请选择一个终端！");
            }
        })

        .on('click', '#pm-update',
        function(e) {
            e.preventDefault();
            var macs = terminal_macs_selected();
            if (macs.length > 0) {
                $("#pm-update-macs").val(macs);
                $("#dialog-update-terminal").modal("show");
            } else {
                PageUtil.error("请选择至少一个终端！");
            }
        })

        .on('click', '#mgmt-lic-upload',
        function(e) {
            e.preventDefault();
            $("#dialog-upload-mgmt-lic").modal("show");
        })

        .on('click', '#pm-set-time',
        function(e) {
            e.preventDefault();
            var macs = terminal_macs_selected();
            if (macs.length > 0) {
                $("#dst-macs").val(macs);
                $("#dialog-set-time").modal("show");
                //只选中一个终端时，我们需要显示其当前时间
                var ids = $("#grid-pm-terminal").jqGrid("getGridParam", "selarrrow");
                if (ids.length == 1) {
                    getTerminalTime(scb_pm_getTerminalTime, ecb_pm_getTerminalTime, macs);
                } else {
                    //用当前时间填充
                    var cdate = new Date();
                    var year   = cdate.getFullYear();
                    var month  = cdate.getMonth() + 1; //months from 1-12
                    var day    = cdate.getDate();
                    var hour   = parseInt(cdate.getHours());
                    var minute = parseInt(cdate.getMinutes());
                    $('#dst-datepicker').datepicker("update", new Date(year, month-1, day));
                    if (minute < 10){
                       minute.toString();
                       minute = "0" + minute;
                    }
                    $("#dst-timepicker").val(hour+":"+minute);
                }
            } else {
                PageUtil.error("请选择至少一个终端！");
            }
        })

        .on('click', '#dst-set-time',
        function(e) {
            e.preventDefault();
            $("#dialog-set-time").modal("hide");
            var macs   = $("#dst-macs").val();
            var year   = $("#dst-datepicker").datepicker('getDate').getFullYear();
            var month  = $("#dst-datepicker").datepicker('getDate').getMonth() + 1;
            var day    = $("#dst-datepicker").datepicker('getDate').getDate();
            var hour   = $("#dst-timepicker").data('timepicker').hour;
            var minute = $("#dst-timepicker").data('timepicker').minute;
            var second = $("#dst-timepicker").data('timepicker').second;
            setTerminalTime(scb_pm_setTerminalTime, ecb_pm_setTerminalTime, macs, year, month, day, hour, minute, second);
        })

        .on('click', '#pm-connection',
        function(e) {
            e.preventDefault();
            var macs = terminal_macs_selected();
            var ips  = terminal_ips_selected();
            if (macs.length > 0) {
                //PageUtil.alert("此功能未开放！");
                $("#dac-macs").val(macs);
                $("#dac-connection-in-file").prop('checked', false);
                $("#dac-connection-file").val('');
                $("#dac-connection-file").prop('disabled', true);
                $("#dac-connection-name").val('');
                $("#dac-connection-name").prop('disabled', false);
                $("#dac-url-address").val('');
                $("#dac-url-address").prop('disabled', false);
                $("#dac-username-prefix").val('');
                $("#dac-username-prefix").prop('disabled', false);
                $("#dac-start-sequence").val('');
                $("#dac-start-sequence").prop('disabled', false);
                $("#dac-order-type").prop('disabled', false);
                $("#dac-password").val('');
                $("#dac-password").prop('disabled', true);
                $("#dac-password-as-user").prop('checked', true);
                $("#dac-password-as-user").prop('disabled', false);
                $("#dac-domain").val('');
                $("#dac-domain").prop('disabled', false);
                $("#dac-auto-connect").prop('checked', false);
                $("#dac-auto-connect").prop('disabled', false);
                $("#dialog-add-connection").modal("show");
            } else {
                PageUtil.error("请选择至少一个终端！");
            }
        })

        .on('change', '#dac-connection-in-file',
        function(e) {
            e.preventDefault();
            if ($('#dac-connection-in-file').prop('checked') == true) {
                $("#dac-connection-file" ).prop('disabled', false);
                $("#dac-connection-name" ).prop('disabled', true);
                $("#dac-url-address"     ).prop('disabled', true);
                $("#dac-username-prefix" ).prop('disabled', true);
                $("#dac-start-sequence"  ).prop('disabled', true);
                $("#dac-order-type"      ).prop('disabled', true);
                $("#dac-password"        ).prop('disabled', true);
                $("#dac-password-as-user").prop('disabled', true);
                $("#dac-domain"          ).prop('disabled', true);
                $("#dac-auto-connect"    ).prop('disabled', true);
            } else {
                $("#dac-connection-file" ).prop('disabled', true);
                $("#dac-connection-name" ).prop('disabled', false);
                $("#dac-url-address"     ).prop('disabled', false);
                $("#dac-username-prefix" ).prop('disabled', false);
                $("#dac-start-sequence"  ).prop('disabled', false);
                $("#dac-order-type"      ).prop('disabled', false);
                $("#dac-password-as-user").prop('disabled', false);
                $("#dac-domain"          ).prop('disabled', false);
                $("#dac-auto-connect"    ).prop('disabled', false);
                if ($('#dac-password-as-user').prop('checked') == true) {
                    $("#dac-password").val('');
                    $("#dac-password").prop('disabled', true);
                } else {
                    $("#dac-password").prop('disabled', false);
                }
            }
        })

        .on('change', '#dac-password-as-user',
        function(e) {
            e.preventDefault();
            if ($('#dac-password-as-user').prop('checked') == true) {
                $("#dac-password").val('');
                $("#dac-password").prop('disabled', true);
            } else {
                $("#dac-password").prop('disabled', false);
            }
        })

        .on('click', '#dac-clear-connection',
        function(e) {
            e.preventDefault();
            PageUtil.confirm("确定清空所有连接项吗？",
            function() {
                var macs = $('#dac-macs').val();
                clearResourceDb(scb_pm_clearResourceDb, ecb_pm_clearResourceDb, macs);
            },
            "Warning");
        })
/*
        .on('click', '#dac-add-connection',
        function(e) {
            e.preventDefault();
            var macs       = $('#dac-macs').val();
            var file       = $('#dac-connection-file').val();
            var connection = $('#dac-connection-type').val();
            var nickname   = $('#dac-connection-name').val();
            var serverip   = $('#dac-url-address').val();
            var prefix     = $('#dac-username-prefix').val();
            var snumber    = $('#dac-start-sequence').val();
            var order      = $('#dac-number-order').val();
            var password   = $('#dac-password').val();
            var domain     = $('#dac-domain').val();
            var autolink   = $('#dac-autolink').val();
            if (snumber != '' && isNaN(snumber)) {
                $('#dac-start-sequence-checker').html('<span style="color: #A94442;" class="help-block">请输入起始编号！</span>');
                return;
            } else {
                $('#dac-start-sequence-checker').html('');
            }
            if (password == '' && $('#dac-password-as-user').prop('checked') == false) {
                $('#dac-password-checker').html('<span style="color: #A94442;" class="help-block">请输入密码！</span>');
                return;
            } else {
                $('#dac-password-checker').html('');
            }
            alert('add connect');
            if ($('#dac-connection-in-file').prop('checked') == true) {
                alert(file);
                addTerminalConnectionByFile(scb_pm_addTerminalConnectionByFile, ecb_pm_addTerminalConnectionByFile, macs, file)
            } else {
                alert('value');
                addTerminalConnection(scb_pm_addTerminalConnection, ecb_pm_addTerminalConnection, macs, connection, nickname, serverip, prefix, snumber, order, password, domain, autolink); 
            }
        })
*/
        .on('click', '#pm-export-macs',
        function(e) {
            e.preventDefault();
            var macs = terminal_macs_selected();
            if (macs.length > 0) {
                exportTerminalMacs(macs);
            } else {
                PageUtil.error("请选择至少一个终端！");
            }
        })

        .on('click', '#pm-remove',
        function(e) {
            e.preventDefault();
            var macs = terminal_macs_selected();
            if (macs.length == 0) {
                return;
            }
            PageUtil.confirm("确定要删除终端吗？",
            function() {
                removeTerminals(scb_pm_removeTerminals, ecb_pm_removeTerminals, macs);
            },
            "Warning");
        })
    };

    var terminal_ips_selected = function() {
        var ids = $("#grid-pm-terminal").jqGrid("getGridParam", "selarrrow");

        var terminal_ips = "";
        for (var i = 0; i < ids.length; i++) {
            var id = ids[i];
            var rowData = $("#grid-pm-terminal").jqGrid('getRowData', id);
            terminal_ips += rowData.ip + ",";
        }
        terminal_ips = terminal_ips.length > 0 ? terminal_ips.substr(0, terminal_ips.length - 1) : terminal_ips;

        return terminal_ips;
    }

    var terminal_macs_selected = function() {
        var ids = $("#grid-pm-terminal").jqGrid("getGridParam", "selarrrow");

        var terminal_macs = "";
        for (var i = 0; i < ids.length; i++) {
            var id = ids[i];
            var rowData = $("#grid-pm-terminal").jqGrid('getRowData', id);
            terminal_macs += rowData.mac + ",";
        }
        terminal_macs = terminal_macs.length > 0 ? terminal_macs.substr(0, terminal_macs.length - 1) : terminal_macs;

        return terminal_macs;
    }

    return {
        init: function() {
            initGrid();
            handleActions();
            handleFormValidation();
        }
    };

} ();
