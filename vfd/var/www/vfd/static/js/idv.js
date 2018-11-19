var IdvObj = function() {
    var pci_ids_selected = function() {
        var ids = document.getElementById("ps-dci-pci");
        var pci_ids="";
        for (var i = 0; i < ids.length; i++) {
            var pci = JSON.parse(ids.options[i].value);
            pci_ids += pci['id'] + ",";
        }
        pci_ids = pci_ids.length > 0 ? pci_ids.substr(0, pci_ids.length - 1) : pci_ids;

        return pci_ids;
    }

    var pci_ids_selected2 = function() {
        var ids = document.getElementById("ps-deip-pci");
        var pci_ids="";
        for (var i = 0; i < ids.length; i++) {
            var pci = JSON.parse(ids.options[i].value);
            pci_ids += pci['id'] + ",";
        }
        pci_ids = pci_ids.length > 0 ? pci_ids.substr(0, pci_ids.length - 1) : pci_ids;

        return pci_ids;
    }

    var scb_removeIdv = function(response) {
        getIdvs(scb_pi_getIdvs, ecb_pi_getIdvs);
    }


    var ecb_removeIdv = function(response) {
    }

    var scb_redrawPciDevices = function(response) {
        $('#ps-deip-device').val(response.message);
    }

    var ecb_redrawPciDevices = function(response) {
        $('#ps-deip-device').val('');
    }

    var redrawIdv = function(name) {
        $('#ps-cur-idv').val(name);
        var ihtml = '';
        if (name == '') {
            ihtml += '<a class="btn btn-default btn-sm" id="ps-create-idv">';
            ihtml += '<span class="hidden-480">创建</span>';
            ihtml += '</a>';
        } else {
            ihtml += '<a class="btn btn-default btn-sm" id="ps-remove-idv">';
            ihtml += '<span class="hidden-480">删除</span>';
            ihtml += '</a>';
        }
        $('#ps-idv-action').html(ihtml);
        if (name == '') {
            $('#ps-idv-info').html('');
        } else {
            getIdvInfo(scb_getIdvInfo, ecb_getIdvInfo, name);
        }
    }

    var handleActions = function() {
        $('body')
        .on('change', '#ps-idv-name', function(e) {
            e.preventDefault();
            var name = $('#ps-idv-name').val();
            redrawIdv(name);
        })

        .on('click', '#ps-remove-idv', function(e) {
            e.preventDefault();
            var name = $('#ps-idv-name').val();
            PageUtil.confirm("您确定要删除吗？", function() {
                $('#ps-cur-idv').val('');
                removeIdv(scb_removeIdv, ecb_removeIdv, name);
            }, "Warning");
        })

        .on('click', '#ps-create-idv', function(e) {
            e.preventDefault();
            $("#ps-dci-name"     ).val('');
            $('#ps-dci-autostart').prop('checked', false);
            $("#ps-dci-cpu"      ).val('');
            $("#ps-dci-memory"   ).val('');
            $("#ps-dci-sdisk"    ).val('');
            $("#ps-dci-ddisk"    ).val('');
            $("#ps-dci-iso"      ).val('');
            $("#ps-dci-vfd"      ).val('');
            $("#ps-dci-nettype"  ).val('');
            $("#ps-dci-ipaddr"   ).val('');
            $("#ps-dci-netmask"  ).val('');
            $("#ps-dci-gateway"  ).val('');
            $("#ps-dci-dns"      ).val('');
            $("#ps-dci-ipaddr"   ).attr("readonly", "readonly");
            $("#ps-dci-netmask"  ).attr("readonly", "readonly");
            $("#ps-dci-gateway"  ).attr("readonly", "readonly");
            $("#ps-dci-dns"      ).attr("readonly", "readonly");
            $('#wizard-create-idv a[href="#ps-dci-tab1"]').tab('show');
            jQuery('li', $('#wizard-create-idv')).removeClass("done");
            $('#wizard-create-idv').find('.button-next').show();
            $('#wizard-create-idv').find('.button-finish').hide();
            $('#wizard-create-idv').find('.button-close').show();
            $("#dialog-create-idv").modal('show');
        })

        .on('click', '#ps-create-sdisk', function(e) {
            e.preventDefault();
            $('#ps-dcd-diskname').val('');
            $('#ps-dcd-disksize').val('');
            $("#dialog-create-disk").modal('show');
            getAvailableDisk(scb_pi_getAvailableDisk, ecb_pi_getAvailableDisk);
        })

        .on('click', '#ps-create-ddisk', function(e) {
            e.preventDefault();
            $('#ps-dcd-diskname').val('');
            $('#ps-dcd-disksize').val('');
            $("#dialog-create-disk").modal('show');
            getAvailableDisk(scb_pi_getAvailableDisk, ecb_pi_getAvailableDisk);
        })

        .on('click', '#ps-upload-iso', function(e) {
            e.preventDefault();
            $("#dialog-upload-iso").modal('show');
        })

        .on('click', '#ps-upload-vfd', function(e) {
            e.preventDefault();
            $("#dialog-upload-iso").modal('show');
        })

        .on('click', '#ps-create-disk', function(e) {
            e.preventDefault();
            var name = $('#ps-dcd-diskname').val();
            if (name == '') {
                $("#ps-dcd-diskname-checker").html('<span style="color: #A94442;" class="help-block">名称不能为空！</span>');
                return false;
            } else {
                $("#ps-dcd-diskname-checker").html('');
            }
            var size = $('#ps-dcd-disksize').val();
            if (!/^[0-9]*[1-9][0-9]*$/.test(size)) {
                $("#ps-dcd-disksize-checker").html('<span style="color: #A94442;" class="help-block">容量不能为空！</span>');
                return false;
            } else {
                $("#ps-dcd-disksize-checker").html('');
            }
            createDisk(scb_pi_createDisk, ecb_pi_createDisk, name, size);
        })

        .on('click', '#ps-mount-usb', function(e) {
            e.preventDefault();
            PageUtil.alert("Mount USB");
        })

        .on('click', '#ps-umount-usb', function(e) {
            e.preventDefault();
            PageUtil.alert("Umount USB");
        })

        .on('change', '#ps-dci-nettype', function(e) {
            e.preventDefault();
            var nettype = $('#ps-dci-nettype').val();
            if (nettype == '' || nettype == 'user') {
                $("#ps-dci-ipaddr" ).val('');
                $("#ps-dci-netmask").val('');
                $("#ps-dci-gateway").val('');
                $("#ps-dci-dns"    ).val('');
                $("#ps-dci-ipaddr" ).attr("readonly", "readonly");
                $("#ps-dci-netmask").attr("readonly", "readonly");
                $("#ps-dci-gateway").attr("readonly", "readonly");
                $("#ps-dci-dns"    ).attr("readonly", "readonly");
            } else {
                $("#ps-dci-ipaddr" ).removeAttr("readonly");
                $("#ps-dci-netmask").removeAttr("readonly");
                $("#ps-dci-gateway").removeAttr("readonly");
                $("#ps-dci-dns"    ).removeAttr("readonly");
            }
        })

        .on('click', '#ps-dci-all-pci',
        function(e) {
            e.preventDefault();
            var p = $('#ps-dci-all-pci').val();
            if (p) {
                var pci = JSON.parse(p);
                $("#ps-dci-all-pci option[value='" + p + "']").remove();
                $('#ps-dci-pci').append('<option value=\'' + p + '\'>' + pci['name'] + '</option>');
            }
        })

        .on('click', '#ps-dci-pci',
        function(e) {
            e.preventDefault();
            var p = $('#ps-dci-pci').val();
            if (p) {
                var pci = JSON.parse(p);
                $("#ps-dci-pci option[value='" + p + "']").remove();
                $('#ps-dci-all-pci').append('<option value=\'' + p + '\'>' + pci['name'] + '</option>');
            }
        })

        .on('click', '#ps-dci-close',
        function(e) {
            e.preventDefault();
            $("#dialog-create-idv").modal("hide");
        })

        .on('click', '#ps-dci-finish',
        function(e) {
            e.preventDefault();
            $("#dialog-create-idv").modal("hide");
            var name      = $('#ps-dci-name'     ).val();
            var autostart = '';
            if ($('#ps-dci-autostart').prop('checked') == true) {
                autostart = 'startonboot';	//不知道为何，这里值也用autostart就会出问题(aoqingy)
            }
            var cpu       = $('#ps-dci-cpu'      ).val();
            var memory    = $('#ps-dci-memory'   ).val();
            var sdisk     = $('#ps-dci-sdisk'    ).val();
            var ddisk     = $('#ps-dci-ddisk'    ).val();
            var cdrom     = $('#ps-dci-iso'      ).val();
            var floppy    = $('#ps-dci-vfd'      ).val();
            var nettype   = $('#ps-dci-nettype'  ).val();
            var ipaddr    = $('#ps-dci-ipaddr'   ).val();
            var netmask   = $('#ps-dci-netmask'  ).val();
            var gateway   = $('#ps-dci-gateway'  ).val();
            var dns       = $('#ps-dci-dns'      ).val();
            var pci       = pci_ids_selected();
            createIdv(scb_createIdv, ecb_createIdv, name, autostart, cpu, memory, sdisk, ddisk, cdrom, floppy, nettype, ipaddr, netmask, gateway, dns, pci);
        })

        .on('click', '#ps-edit-cpu', function(e) {
            e.preventDefault();
            $('#dialog-edit-idv-cpu').modal('show');
            var name = $('#ps-idv-name').val();
            $('#ps-deic-name').val(name);
            $('#ps-deic-cpu' ).val('');
        })

        .on('click', '#ps-deic-edit-cpu', function(e) {
            e.preventDefault();
            var name = $('#ps-deic-name').val();
            var cpu  = $('#ps-deic-cpu' ).val();
            editIdvCpu(scb_editIdvCpu, ecb_editIdvCpu, name, cpu);
        })

        .on('click', '#ps-edit-memory', function(e) {
            e.preventDefault();
            $('#dialog-edit-idv-memory').modal('show');
            var name = $('#ps-idv-name').val();
            $('#ps-deim-name'  ).val(name);
            $('#ps-deim-memory').val('');
        })

        .on('click', '#ps-deim-edit-memory', function(e) {
            e.preventDefault();
            var name   = $('#ps-deim-name'  ).val();
            var memory = $('#ps-deim-memory').val();
            editIdvMemory(scb_editIdvMemory, ecb_editIdvMemory, name, memory);
        })

        .on('click', '#ps-edit-cdrom', function(e) {
            e.preventDefault();
            $('#dialog-edit-idv-iso').modal('show');
            var name = $('#ps-idv-name').val();
            $('#ps-deii-name').val(name);
            $('#ps-deii-boot').prop("checked", false);
            getIsos(scb_deii_getIsos, ecb_deii_getIsos);
        })

        .on('click', '#ps-deii-edit-cdrom', function(e) {
            e.preventDefault();
            var name  = $('#ps-deii-name' ).val();
            var cdrom = $('#ps-deii-cdrom').val();
            var boot  = '';
            if ($('#ps-deii-boot').prop('checked') == true) {
                boot = 'iso';
            }
            if (cdrom == '' && boot != '') {
                return false;
            }
            editIdvCdrom(scb_editIdvCdrom, ecb_editIdvCdrom, name, cdrom, boot);
        })

        .on('click', '#ps-edit-floppy', function(e) {
            e.preventDefault();
            $('#dialog-edit-idv-vfd').modal('show');
            var name = $('#ps-idv-name').val();
            $('#ps-deiv-name'  ).val(name);
            getVfds(scb_deiv_getVfds, ecb_deiv_getVfds);
        })

        .on('click', '#ps-deiv-edit-floppy', function(e) {
            e.preventDefault();
            var name   = $('#ps-deiv-name'  ).val();
            var floppy = $('#ps-deiv-floppy').val();
            editIdvFloppy(scb_editIdvFloppy, ecb_editIdvFloppy, name, floppy);
        })

        .on('click', '#ps-edit-sdisk', function(e) {
            e.preventDefault();
            $('#dialog-edit-idv-sdisk').modal('show');
            var name = $('#ps-idv-name').val();
            $('#ps-deis-name'   ).val(name);
            getDisks(scb_deis_getSystemDisks, ecb_deis_getSystemDisks);
            $('#ps-deis-restore').prop("checked", false);
            $('#ps-deis-boot'   ).prop("checked", false);
        })

        .on('click', '#ps-deis-edit-sdisk', function(e) {
            e.preventDefault();
            var name    = $('#ps-deis-name'  ).val();
            var sdisk   = $('#ps-deis-sdisk').val();
            if (sdisk == '') {
                $("#ps-deis-sdisk-checker").html('<span style="color: #A94442;" class="help-block">必须选择系统磁盘！</span>');
                return false;
            }
            $("#ps-deis-sdisk-checker").html('');
            var restore = '';
            if ($('#ps-deis-restore').prop('checked') == true) {
                restore = 'restore';
            }
            var boot  = '';
            if ($('#ps-deis-boot').prop('checked') == true) {
                boot = 'disk';
            }
            editIdvSdisk(scb_editIdvSdisk, ecb_editIdvSdisk, name, sdisk, restore, boot);
        })

        .on('click', '#ps-edit-ddisk', function(e) {
            e.preventDefault();
            $('#dialog-edit-idv-ddisk').modal('show');
            var name = $('#ps-idv-name').val();
            $('#ps-deid-name'   ).val(name);
            getDisks(scb_deid_getDataDisks, ecb_deid_getDataDisks);
            $('#ps-deid-restore').prop("checked", false);
        })

        .on('click', '#ps-deid-edit-ddisk', function(e) {
            e.preventDefault();
            var name    = $('#ps-deid-name'  ).val();
            var ddisk   = $('#ps-deid-ddisk').val();
            var restore = '';
            if ($('#ps-deid-restore').prop('checked') == true) {
                restore = 'restore';
            }
            if (ddisk == '' && restore != '') {
                return false;
            }
            editIdvDdisk(scb_editIdvDdisk, ecb_editIdvDdisk, name, ddisk, restore);
        })

        .on('click', '#ps-edit-network', function(e) {
            e.preventDefault();
            $('#dialog-edit-idv-network').modal('show');
            var name = $('#ps-idv-name').val();
            $('#ps-dein-name'   ).val(name);
            $('#ps-dein-nettype').val('');
            $('#ps-dein-ipaddr' ).val('');
            $('#ps-dein-netmask').val('');
            $('#ps-dein-gateway').val('');
            $('#ps-dein-dns'    ).val('');
            $("#ps-dein-ipaddr" ).attr("readonly", "readonly");
            $("#ps-dein-netmask").attr("readonly", "readonly");
            $("#ps-dein-gateway").attr("readonly", "readonly");
            $("#ps-dein-dns"    ).attr("readonly", "readonly");
        })

        .on('change', '#ps-dein-nettype', function(e) {
            e.preventDefault();
            var nettype = $('#ps-dein-nettype').val();
            if (nettype == '' || nettype == 'user') {
                $("#ps-dein-ipaddr" ).val('');
                $("#ps-dein-netmask").val('');
                $("#ps-dein-gateway").val('');
                $("#ps-dein-dns"    ).val('');
                $("#ps-dein-ipaddr" ).attr("readonly", "readonly");
                $("#ps-dein-netmask").attr("readonly", "readonly");
                $("#ps-dein-gateway").attr("readonly", "readonly");
                $("#ps-dein-dns"    ).attr("readonly", "readonly");
            } else {
                $("#ps-dein-ipaddr" ).removeAttr("readonly");
                $("#ps-dein-netmask").removeAttr("readonly");
                $("#ps-dein-gateway").removeAttr("readonly");
                $("#ps-dein-dns"    ).removeAttr("readonly");
            }
        })

        .on('click', '#ps-dein-edit-network', function(e) {
            e.preventDefault();
            var name    = $('#ps-dein-name'   ).val();
            var nettype = $('#ps-dein-nettype').val();
            var ipaddr  = $('#ps-dein-ipaddr' ).val();
            var netmask = $('#ps-dein-netmask').val();
            var gateway = $('#ps-dein-gateway').val();
            var dns     = $('#ps-dein-dns'    ).val();
            editIdvNetwork(scb_editIdvNetwork, ecb_editIdvNetwork, name, nettype, ipaddr, netmask, gateway, dns);
        })

        .on('click', '#ps-edit-pci', function(e) {
            e.preventDefault();
            $('#dialog-edit-idv-pci').modal('show');
            var name = $('#ps-idv-name').val();
            $('#ps-deip-name').val(name);
            $('#ps-deip-device').val('');
            getPcis(scb_deip_getPcis, ecb_deip_getPcis);
        })

        .on('click', '#ps-deip-edit-pci', function(e) {
            e.preventDefault();
            var name = $('#ps-deip-name').val();
            var pci  = pci_ids_selected2();
            editIdvPci(scb_editIdvPci, ecb_editIdvPci, name, pci);
        })

        .on('click', '#ps-deip-all-pci',
        function(e) {
            e.preventDefault();
            var p = $('#ps-deip-all-pci').val();
            if (p) {
                var pci = JSON.parse(p);
                $("#ps-deip-all-pci option[value='" + p + "']").remove();
                $('#ps-deip-pci').append('<option value=\'' + p + '\'>' + pci['name'] + '</option>');
                var pci  = pci_ids_selected2();
                redrawPciDevices(scb_redrawPciDevices, ecb_redrawPciDevices, pci);
            }
        })

        .on('click', '#ps-deip-pci',
        function(e) {
            e.preventDefault();
            var p = $('#ps-deip-pci').val();
            if (p) {
                var pci = JSON.parse(p);
                $("#ps-deip-pci option[value='" + p + "']").remove();
                $('#ps-deip-all-pci').append('<option value=\'' + p + '\'>' + pci['name'] + '</option>');
                var pci  = pci_ids_selected2();
                redrawPciDevices(scb_redrawPciDevices, ecb_redrawPciDevices, pci);
            }
        })

        .on('change', '#ps-edit-autostart',
        function(e) {
            e.preventDefault();
            var name = $('#ps-idv-name').val();
            var autostart = '';
            if ($('#ps-edit-autostart').prop('checked') == true) {
                autostart = 'startonboot';
            }
            editIdvAutoStart(scb_editIdvAutoStart, ecb_editIdvAutoStart, name, autostart);
        })

    };

    var scb_pi_getIdvs = function(response) {
        var name = $('#ps-cur-idv').val();
        var ihtml = '<option></option>';
        for (var i = 0; i < response.message.length; i++) {
            if (name == response.message[i]['name']) {
                ihtml += '<option selected="selected" value="' + response.message[i]['name'] + '">' + response.message[i]['name'] + '</option>';	//Note: we use name instead of id as value (aoqingy)
            } else {
                ihtml += '<option value="' + response.message[i]['name'] + '">' + response.message[i]['name'] + '</option>';
            }
        }
        $("#ps-idv-name").html(ihtml);
        redrawIdv(name);
    }

    var ecb_pi_getIdvs = function(response) {
        $("#ps-idv-name").html('');
    }

    var scb_createIdv = function(response) {
        getIdvs(scb_pi_getIdvs, ecb_pi_getIdvs);
    }

    var ecb_createIdv = function(response) {
    }

    var scb_getIdvInfo = function(response) {
        var data = response.message;
        var ihtml = '';
        ihtml += '<div class="form-group">';
        ihtml += '  <div class="col-md-12">';
        ihtml += '    <label class="col-md-3 control-label">CPU：</label>';
        ihtml += '    <label class="col-md-6 control-label" style="text-align:left">' + data.cpu + '</label>';
        ihtml += '    <div class="col-md-2">';
        ihtml += '      <a class="btn btn-default btn-sm" id="ps-edit-cpu">';
        ihtml += '        <img src="static/img/idv-cpu.png" width="16" />';
        ihtml += '      </a>';
        ihtml += '    </div>';
        ihtml += '  </div>';
        ihtml += '  <div class="col-md-12">';
        ihtml += '    <label class="col-md-3 control-label">内存：</label>';
        ihtml += '    <label class="col-md-6 control-label" style="text-align:left">' + data.memory + '</label>';
        ihtml += '    <div class="col-md-2">';
        ihtml += '      <a class="btn btn-default btn-sm" id="ps-edit-memory">';
        ihtml += '        <img src="static/img/idv-memory.png" width="16" />';
        ihtml += '      </a>';
        ihtml += '    </div>';
        ihtml += '  </div>';
        ihtml += '</div>';

        ihtml += '<div class="form-group">';
        ihtml += '  <div class="col-md-12">';
        ihtml += '    <label class="col-md-3 control-label">光盘：</label>';
        if (data['cdrom'] != '') {
            ihtml += '    <label class="col-md-6 control-label" style="text-align:left">' + data.cdrom + '</label>';
        } else {
            ihtml += '    <label class="col-md-6 control-label" style="text-align:left">-</label>';
        }
        ihtml += '    <div class="col-md-2">';
        ihtml += '      <a class="btn btn-default btn-sm" id="ps-edit-cdrom">';
        ihtml += '        <img src="static/img/idv-cdrom.png" width="16" />';
        ihtml += '      </a>';
        ihtml += '    </div>';
        ihtml += '  </div>';
        ihtml += '  <div class="col-md-12">';
        ihtml += '    <label class="col-md-3 control-label">软盘：</label>';
        if (data['floppy'] != '') {
            ihtml += '    <label class="col-md-6 control-label" style="text-align:left">' + data.floppy + '</label>';
        } else {
            ihtml += '    <label class="col-md-6 control-label" style="text-align:left">-</label>';
        }
        ihtml += '    <div class="col-md-2">';
        ihtml += '      <a class="btn btn-default btn-sm" id="ps-edit-floppy">';
        ihtml += '        <img src="static/img/idv-floppy.png" width="16" />';
        ihtml += '      </a>';
        ihtml += '    </div>';
        ihtml += '  </div>';
        ihtml += '  <div class="col-md-12">';
        ihtml += '    <label class="col-md-3 control-label">系统磁盘：</label>';
        if (data['sdisk_restore'] != '') {
            ihtml += '    <label class="col-md-6 control-label" style="text-align:left">' + data.sdisk + ' (restore)</label>';
        } else {
            ihtml += '    <label class="col-md-6 control-label" style="text-align:left">' + data.sdisk + '</label>';
        }
        ihtml += '    <div class="col-md-2">';
        ihtml += '      <a class="btn btn-default btn-sm" id="ps-edit-sdisk">';
        ihtml += '        <img src="static/img/idv-disk.png" width="16" />';
        ihtml += '      </a>';
        ihtml += '    </div>';
        ihtml += '  </div>';
        ihtml += '  <div class="col-md-12">';
        ihtml += '    <label class="col-md-3 control-label">数据磁盘：</label>';
        if (data['ddisk'] != '') {
            if (data['ddisk_restore'] != '') {
                ihtml += '    <label class="col-md-6 control-label" style="text-align:left">' + data.ddisk + ' (restore)</label>';
            } else {
                ihtml += '    <label class="col-md-6 control-label" style="text-align:left">' + data.ddisk + '</label>';
            }
        } else {
            ihtml += '    <label class="col-md-6 control-label" style="text-align:left">-</label>';
        }
        ihtml += '    <div class="col-md-2">';
        ihtml += '      <a class="btn btn-default btn-sm" id="ps-edit-ddisk">';
        ihtml += '        <img src="static/img/idv-disk.png" width="16" />';
        ihtml += '      </a>';
        ihtml += '    </div>';
        ihtml += '  </div>';
        ihtml += '  <div class="col-md-12">';
        ihtml += '    <label class="col-md-3 control-label">引导设备：</label>';
        ihtml += '    <label class="col-md-9 control-label" style="text-align:left">' + data.boot + '</label>';
        ihtml += '  </div>';
        ihtml += '</div>';

        ihtml += '<div class="col-md-12">';
        ihtml += '  <div class="form-group">';
        ihtml += '    <label class="col-md-3 control-label">网络类型：</label>';
        if (data['nettype'] != '') {
            ihtml += '    <label class="col-md-6 control-label" style="text-align:left">' + data.nettype + '</label>';
        } else {
            ihtml += '    <label class="col-md-6 control-label" style="text-align:left">-</label>';
        }
        ihtml += '    <div class="col-md-2">';
        ihtml += '      <a class="btn btn-default btn-sm" id="ps-edit-network">';
        ihtml += '        <img src="static/img/idv-network.png" width="16" />';
        ihtml += '      </a>';
        ihtml += '    </div>';
        ihtml += '  </div>';
        ihtml += '  <div class="col-md-12">';
        if (data['ipaddr'] != '') {
            ihtml += '    <label class="col-md-3 control-label">IP地址：</label>';
            ihtml += '    <label class="col-md-8 control-label" style="text-align:left">' + data.ipaddr + '</label>';
        }
        if (data['netmask'] != '') {
            ihtml += '    <label class="col-md-3 control-label">子网掩码：</label>';
            ihtml += '    <label class="col-md-8 control-label" style="text-align:left">' + data.netmask + '</label>';
        }
        if (data['gateway'] != '') {
            ihtml += '    <label class="col-md-3 control-label">网关地址：</label>';
            ihtml += '    <label class="col-md-8 control-label" style="text-align:left">' + data.gateway + '</label>';
        }
        if (data['dns'] != '') {
            ihtml += '    <label class="col-md-3 control-label">DNS地址：</label>';
            ihtml += '    <label class="col-md-8 control-label" style="text-align:left">' + data.dns + '</label>';
        }
        ihtml += '  </div>';
        ihtml += '</div>';

        ihtml += '<div class="form-group">';
        ihtml += '  <div class="col-md-12">';
        ihtml += '    <label class="col-md-3 control-label">PCI设备：</label>';
        if (data['pci'] != '') {
            ihtml += '    <label class="col-md-6 control-label" style="text-align:left">' + data.pci + '</label>';
        } else {
            ihtml += '    <label class="col-md-6 control-label" style="text-align:left">-</label>';
        }
        ihtml += '    <div class="col-md-2" id="ps-idv-action" align="bottom">';
        ihtml += '      <a class="btn btn-default btn-sm" id="ps-edit-pci">';
        ihtml += '        <img src="static/img/idv-pci.png" width="16" />';
        ihtml += '      </a>';
        ihtml += '    </div>';
        ihtml += '  </div>';
        ihtml += '</div>';

        ihtml += '<div class="form-group">';
        ihtml += '  <div class="col-md-12">';
        ihtml += '    <label class="col-md-3 control-label">自动启动：</label>';
        ihtml += '    <div class="col-md-2" id="ps-idv-action" align="bottom">';
        if (data.autostart) {
            ihtml += '      <input type="checkbox" checked="checked" value="1" id="ps-edit-autostart" style=" width: 19px; height: 25px; padding: 0 5px 0 0; display: block; clear: left; float: left;" >';
        } else {
            ihtml += '      <input type="checkbox" value="1" id="ps-edit-autostart" style=" width: 19px; height: 25px; padding: 0 5px 0 0; display: block; clear: left; float: left;" >';
        }
        ihtml += '    </div>';
        ihtml += '  </div>';
        ihtml += '</div>';
        $('#ps-idv-info').html(ihtml);
    }

    var ecb_getIdvInfo = function(response) {
        $('#ps-idv-info').html('');
    }

    var scb_editIdvCpu = function(response) {
        $('#dialog-edit-idv-cpu').modal('hide');
        getIdvs(scb_pi_getIdvs, ecb_pi_getIdvs);
    }

    var ecb_editIdvCpu = function(response) {
        PageUtil.error('编辑桌面CPU失败！');
    }

    var scb_editIdvMemory = function(response) {
        $('#dialog-edit-idv-memory').modal('hide');
        getIdvs(scb_pi_getIdvs, ecb_pi_getIdvs);
    }

    var ecb_editIdvMemory = function(response) {
        PageUtil.error('编辑桌面内存失败！');
    }

    var scb_editIdvCdrom = function(response) {
        $('#dialog-edit-idv-iso').modal('hide');
        getIdvs(scb_pi_getIdvs, ecb_pi_getIdvs);
    }

    var ecb_editIdvCdrom = function(response) {
        PageUtil.error('编辑桌面光盘失败！');
    }

    var scb_editIdvFloppy = function(response) {
        $('#dialog-edit-idv-vfd').modal('hide');
        getIdvs(scb_pi_getIdvs, ecb_pi_getIdvs);
    }

    var ecb_editIdvFloppy = function(response) {
        PageUtil.error('编辑桌面软盘失败！');
    }

    var scb_editIdvSdisk = function(response) {
        $('#dialog-edit-idv-sdisk').modal('hide');
        getIdvs(scb_pi_getIdvs, ecb_pi_getIdvs);
    }

    var ecb_editIdvSdisk = function(response) {
        PageUtil.error('编辑桌面系统磁盘失败！');
    }

    var scb_editIdvDdisk = function(response) {
        $('#dialog-edit-idv-ddisk').modal('hide');
        getIdvs(scb_pi_getIdvs, ecb_pi_getIdvs);
    }

    var ecb_editIdvDdisk = function(response) {
        PageUtil.error('编辑桌面数据磁盘失败！');
    }

    var scb_editIdvNetwork = function(response) {
        $('#dialog-edit-idv-network').modal('hide');
        getIdvs(scb_pi_getIdvs, ecb_pi_getIdvs);
    }

    var ecb_editIdvNetwork = function(response) {
        PageUtil.error('编辑桌面网络失败！');
    }

    var scb_editIdvPci = function(response) {
        $('#dialog-edit-idv-pci').modal('hide');
        getIdvs(scb_pi_getIdvs, ecb_pi_getIdvs);
    }

    var ecb_editIdvPci = function(response) {
        PageUtil.error('编辑桌面PCI失败！');
    }

    var scb_editIdvAutoStart = function(response) {
        getIdvs(scb_pi_getIdvs, ecb_pi_getIdvs);
    }

    var ecb_editIdvAutoStart = function(response) {
        PageUtil.error('编辑桌面自动启动失败！');
    }

    var scb_deii_getIsos = function(response) {
        var ihtml = '<option value=""></option>';
        for (var i = 0; i < response.message.length; i++) {
            ihtml += '<option>' + response.message[i] + '</option>';
        }
        $("#ps-deii-cdrom").html(ihtml);
    }

    var ecb_deii_getIsos = function(response) {
        $("#ps-dci-cdrom").html('');
    }

    var scb_deiv_getVfds = function(response) {
        var ihtml = '<option value=""></option>';
        for (var i = 0; i < response.message.length; i++) {
            ihtml += '<option>' + response.message[i] + '</option>';
        }
        $("#ps-deiv-floppy").html(ihtml);
    }

    var ecb_deiv_getVfds = function(response) {
        $("#ps-deiv-floppy").html('');
    }

    var scb_deis_getSystemDisks = function(response) {
        var shtml = '<option value=""></option>';
        for (var i = 0; i < response.message.length; i++) {
            shtml += '<option>' + response.message[i] + '</option>';
        }
        $("#ps-deis-sdisk").html(shtml);
    }

    var ecb_deis_getSystemDisks = function(response) {
        $("#ps-deis-sdisk").html('');
    }

    var scb_deid_getDataDisks = function(response) {
        var shtml = '<option value=""></option>';
        for (var i = 0; i < response.message.length; i++) {
            shtml += '<option>' + response.message[i] + '</option>';
        }
        $("#ps-deid-ddisk").html(shtml);
    }

    var ecb_deid_getDataDisks = function(response) {
        $("#ps-deid-ddisk").html('');
    }

    var scb_deip_getPcis = function(response) {
        var phtml = '';
        for (var i = 0; i < response.message.length; i++) {
            phtml += '<option value=\'' + JSON.stringify(response.message[i]) + '\'>' + response.message[i]['name'] + '</option>';
        }
        $("#ps-deip-all-pci").html(phtml);
        $("#ps-deip-pci").html('');
    }

    var ecb_deip_getPcis = function(response) {
        $("#ps-deip-all-pci").html('');
        $("#ps-deip-pci").html('');
    }

    return {
        init: function() {
            handleActions();
            $('#ps-cur-idv').val('');
            getIdvs(scb_pi_getIdvs, ecb_pi_getIdvs);
        }
    };
} ();


//////////////////////////////////////////////////
//
// Callbacks for Create IDV Desktop Wizard
//
//////////////////////////////////////////////////
var scb_pi_getMemory = function(response) {
    $('#ps-dci-rmemory').val(response.message);
}

var ecb_pi_getMemory = function(response) {
}

var scb_pi_getCpu = function(response) {
    $('#ps-dci-rcpu').val(response.message);
}

var ecb_pi_getCpu = function(response) {
}

var scb_pi_getSystemDisks = function(response) {
    var shtml = '<option value=""></option>';
    for (var i = 0; i < response.message.length; i++) {
        shtml += '<option>' + response.message[i] + '</option>';
    }
    $("#ps-dci-sdisk").html(shtml);
}

var ecb_pi_getSystemDisks = function(response) {
    $("#ps-dci-sdisk").html('');
}


var scb_pi_getDataDisks = function(response) {
    var dhtml = '<option value=""></option>';
    for (var i = 0; i < response.message.length; i++) {
        dhtml += '<option>' + response.message[i] + '</option>';
    }
    $("#ps-dci-ddisk").html(dhtml);
}

var ecb_pi_getDataDisks = function(response) {
    $("#ps-dci-ddisk").html('');
}


var scb_pi_getIsos = function(response) {
    var ihtml = '<option value=""></option>';
    for (var i = 0; i < response.message.length; i++) {
        ihtml += '<option>' + response.message[i] + '</option>';
    }
    $("#ps-dci-iso").html(ihtml);
}

var ecb_pi_getIsos = function(response) {
    $("#ps-dci-iso").html('');
}


var scb_pi_getVfds = function(response) {
    var ihtml = '<option value=""></option>';
    for (var i = 0; i < response.message.length; i++) {
        ihtml += '<option>' + response.message[i] + '</option>';
    }
    $("#ps-dci-vfd").html(ihtml);
}

var ecb_pi_getVfds = function(response) {
    $("#ps-dci-vfd").html('');
}


var scb_pi_getPcis = function(response) {
    var phtml = '';
    for (var i = 0; i < response.message.length; i++) {
        phtml += '<option value=\'' + JSON.stringify(response.message[i]) + '\'>' + response.message[i]['name'] + '</option>';
    }
    $("#ps-dci-all-pci").html(phtml);
    $("#ps-dci-pci").html('');
}

var ecb_pi_getPcis = function(response) {
    $("#ps-dci-all-pci").html('');
    $("#ps-dci-pci").html('');
}


var scb_pi_getAvailableDisk = function(response) {
    $("#ps-dcd-adisksize").val(response.message);
}

var ecb_pi_getAvailableDisk = function(response) {
    $("#ps-dcd-adisksize").val('');
}


var scb_pi_createDisk = function(response) {
    $('#dialog-create-disk').modal('hide');
    getDisks(scb_pi_getSystemDisks, ecb_pi_getSystemDisks);
    getDisks(scb_pi_getDataDisks, ecb_pi_getDataDisks);
}

var ecb_pi_createDisk = function(response) {
    PageUtil.error('创建磁盘失败!');
}

