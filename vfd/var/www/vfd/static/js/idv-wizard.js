var IdvWizard = function() {
    return {
        //main function to initiate the module
        init: function() {
            if (!jQuery().bootstrapWizard) {
                return;
            }

            var form = $('#form-create-idv');
            var error = $('.alert-danger', form);
            var success = $('.alert-success', form);
            //$('#ps-dci-next').removeAttr("disabled");

            form.validate({
                doNotHideMessage: true,
                errorElement    : 'span',
                errorClass      : 'help-block help-block-error',
                focusInvalid    : false,
                rules           : {},
                messages        : {},
                errorPlacement: function(error, element) {},

                invalidHandler: function(event, validator) {
                    success.hide();
                    error.show();
                    Metronic.scrollTo(error, -200);
                },

                highlight: function(element) {},
                unhighlight: function(element) {},

                success: function(label) {},

                submitHandler: function(form) {
                    success.show();
                    error.hide();
                }

            });

            var handleTitle = function(tab, navigation, index) {
                var total = navigation.find('li').length;
                var current = index + 1;
                jQuery('li', $('#wizard-create-idv')).removeClass("done");
                var li_list = navigation.find('li');
                for (var i = 0; i < index; i++) {
                    jQuery(li_list[i]).addClass("done");
                }

                if (current >= total) {
                    $('#wizard-create-idv').find('.button-next').hide();
                    $('#wizard-create-idv').find('.button-finish').show();
                    $('#wizard-create-idv').find('.button-close').show();
                } else {
                    $('#wizard-create-idv').find('.button-next').show();
                    $('#wizard-create-idv').find('.button-finish').hide();
                    $('#wizard-create-idv').find('.button-close').show();
                }
                Metronic.scrollTo($('.page-title'));
            }

            $('#wizard-create-idv').bootstrapWizard({
                'nextSelector': '.button-next',
                onNext: function(tab, navigation, index) {
                    success.hide();
                    error.hide();
                    if (index == 1) {
                        var name = $("#ps-dci-name").val();
                        if (name == "") {
                            $("#ps-dci-name-checker").html('<span style="color: #A94442;" class="help-block">名称不能为空！</span>');
                            return false;
                        } else {
                            $("#ps-dci-name-checker").html('');
                        }
                        getMemory(scb_pi_getMemory, ecb_pi_getMemory);
                        getCpu(scb_pi_getCpu, ecb_pi_getCpu);
                    }

                    if (index == 2) {
                        var memory  = $("#ps-dci-memory").val();
                        var cpu     = $("#ps-dci-cpu"   ).val();
                        if (!/^[0-9]*[1-9][0-9]*$/.test(memory) || parseInt(memory) < 512 || parseInt(memory) > 4096) {
                            $("#ps-dci-memory-checker").html('<span style="color: #A94442;" class="help-block">内存容量必须为正整数，且在512和4096之间！</span>');
                            return false;
                        } else {
                            $("#ps-dci-memory-checker").html('');
                        }
                        if (!/^[0-9]*[1-9][0-9]*$/.test(cpu) || parseInt(cpu) > 8) {
                            $("#ps-dci-cpu-checker").html('<span style="color: #A94442;" class="help-block">CPU数量必须为正整数，且不能超过8！</span>');
                            return false;
                        } else {
                            $("#ps-dci-cpu-checker").html('');
                        }
                        getDisks(scb_pi_getSystemDisks, ecb_pi_getSystemDisks);
                        getDisks(scb_pi_getDataDisks, ecb_pi_getDataDisks);
                        getIsos(scb_pi_getIsos, ecb_pi_getIsos);
                        getVfds(scb_pi_getVfds, ecb_pi_getVfds);
                    }

                    if (index == 3) {
                        var sdisk = $('#ps-dci-sdisk').val();
                        if (sdisk == '') {
                            $("#ps-dci-sdisk-checker").html('<span style="color: #A94442;" class="help-block">必须选择系统磁盘！</span>');
                            return false;
                        } else {
                            $("#ps-dci-sdisk-checker").html('');
                        }
                    }

                    if (index == 4) {
                        getPcis(scb_pi_getPcis, ecb_pi_getPcis);
                    }

                    if (form.valid() == false) {
                        return false;
                    }

                    handleTitle(tab, navigation, index);
                },
                onPrevious: function(tab, navigation, index) {
                    success.hide();
                    error.hide();

                    handleTitle(tab, navigation, index);
                },
                onTabShow: function(tab, navigation, index) {
                    var total = navigation.find('li').length;
                    var current = index + 1;
                    var $percent = (current / total) * 100;
                    $('#wizard-create-idv').find('.progress-bar').css({
                        width: $percent + '%'
                    });
                }
            });

            $('#wizard-create-idv').find('.button-finish').hide();
            $('#wizard-create-idv .button-close').click(function() {
            }).show();
        }

    };

} ();
