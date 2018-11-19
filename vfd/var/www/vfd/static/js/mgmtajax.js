//////////////////////////////////////////////////
//
// Interact with the backend
//
//////////////////////////////////////////////////
/*
 * 管理
 */
function scanTerminals(scb, ecb, ipstart, ipend) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/terminal/scan',
        type     : 'POST',
        dataType : 'json',
        data     : {"ipstart":ipstart, "ipend":ipend},
        success: function(response){
            PageUtil.hideMaskLayer();
            if (response.code == "True") {
                scb(response);
            } else {
                ecb(response);
            }
        },
        error: function(){
            PageUtil.hideMaskLayer();
        }
    });
}


function refreshTerminals(scb, ecb) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/terminal/refresh',
        type     : 'POST',
        dataType : 'json',
        data     : {},
        success: function(response){
            PageUtil.hideMaskLayer();
            if (response.code == "True") {
                scb(response);
            } else {
                ecb(response);
            }
        },
        error: function(){
            PageUtil.hideMaskLayer();
        }
    });
}


function clearTerminals(scb, ecb) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/terminal/clear',
        type     : 'POST',
        dataType : 'json',
        data     : {},
        success: function(response){
            PageUtil.hideMaskLayer();
            if (response.code == "True") {
                scb(response);
            } else {
                ecb(response);
            }
        },
        error: function(){
            PageUtil.hideMaskLayer();
        }
    });
}


function removeManagementLic(scb, ecb) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/management/remove',
        type     : 'POST',
        dataType : 'json',
        data     : {},
        success: function(response){
            PageUtil.hideMaskLayer();
            if (response.code == "True") {
                scb(response);
            } else {
                ecb(response);
            }
        },
        error: function(){
            PageUtil.hideMaskLayer();
        }
    });
}


function clearResourceDb(scb, ecb, macs) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/terminal/connection/clear',
        type     : 'POST',
        dataType : 'json',
        data     : {"macs":macs},
        success: function(response){
            PageUtil.hideMaskLayer();
            if (response.code == "True") {
                scb(response);
            } else {
                ecb(response);
            }
        },
        error: function(){
            PageUtil.hideMaskLayer();
        }
    });
}


function wakeupTerminals(scb, ecb, macs) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/terminal/wakeup',
        type     : 'POST',
        dataType : 'json',
        data     : {"macs":macs},
        success: function(response){
            PageUtil.hideMaskLayer();
            if (response.code == "True") {
                scb(response);
            } else {
                ecb(response);
            }
        },
        error: function(){
            PageUtil.hideMaskLayer();
        }
    });
}


function shutdownTerminals(scb, ecb, macs) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/terminal/shutdown',
        type     : 'POST',
        dataType : 'json',
        data     : {"macs":macs},
        success: function(response){
            PageUtil.hideMaskLayer();
            if (response.code == "True") {
                scb(response);
            } else {
                ecb(response);
            }
        },
        error: function(){
            PageUtil.hideMaskLayer();
        }
    });
}


function rebootTerminals(scb, ecb, macs) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/terminal/reboot',
        type     : 'POST',
        dataType : 'json',
        data     : {"macs":macs},
        success: function(response){
            PageUtil.hideMaskLayer();
            if (response.code == "True") {
                scb(response);
            } else {
                ecb(response);
            }
        },
        error: function(){
            PageUtil.hideMaskLayer();
        }
    });
}


function enableTerminals(scb, ecb, macs) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/terminal/enable',
        type     : 'POST',
        dataType : 'json',
        data     : {"macs":macs},
        success: function(response){
            PageUtil.hideMaskLayer();
            if (response.code == "True") {
                scb(response);
            } else {
                ecb(response);
            }
        },
        error: function(){
            PageUtil.hideMaskLayer();
        }
    });
}


function disableTerminals(scb, ecb, macs) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/terminal/disable',
        type     : 'POST',
        dataType : 'json',
        data     : {"macs":macs},
        success: function(response){
            PageUtil.hideMaskLayer();
            if (response.code == "True") {
                scb(response);
            } else {
                ecb(response);
            }
        },
        error: function(){
            PageUtil.hideMaskLayer();
        }
    });
}


function getTerminalInfo(scb, ecb, mac) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/terminal/info',
        type     : 'GET',
        dataType : 'json',
        data     : {"mac":mac},
        success: function(response){
            PageUtil.hideMaskLayer();
            if (response.code == "True") {
                scb(response);
            } else {
                ecb(response);
            }
        },
        error: function(){
            PageUtil.hideMaskLayer();
        }
    });
}


function getTerminalTime(scb, ecb, mac) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/terminal/time/get',
        type     : 'GET',
        dataType : 'json',
        data     : {"mac":mac},
        success: function(response){
            PageUtil.hideMaskLayer();
            if (response.code == "True") {
                scb(response);
            } else {
                ecb(response);
            }
        },
        error: function(){
            PageUtil.hideMaskLayer();
        }
    });
}


function setTerminalTime(scb, ecb, macs, year, month, day, hour, minute, second) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/terminal/time/set',
        type     : 'POST',
        dataType : 'json',
        data     : {"macs":macs, "year":year, 'month':month, 'day':day, 'hour':hour, 'minute':minute, 'second':second},
        success: function(response){
            PageUtil.hideMaskLayer();
            if (response.code == "True") {
                scb(response);
            } else {
                ecb(response);
            }
        },
        error: function(){
            PageUtil.hideMaskLayer();
        }
    });
}

/*
function addTerminalConnection(scb, ecb, macs, product, nickname, serverip, prefix, snumber, order, password, domain, autolink) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/terminal/connection/add',
        type     : 'POST',
        dataType : 'json',
        data     : {"macs":macs, "product":product, 'nickname':nickname, 'serverip':serverip, 'prefix':prefix, 'snumber':snumber, 'order':order, 'password':password, 'domain':domain, 'autolink':autolink},
        success: function(response){
            PageUtil.hideMaskLayer();
            if (response.code == "True") {
                scb(response);
            } else {
                ecb(response);
            }
        },
        error: function(){
            PageUtil.hideMaskLayer();
        }
    });
}

function updateTerminal(scb, ecb, macs, filename) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/terminal/update',
        type     : 'POST',
        dataType : 'json',
        data     : {"macs":macs},
        success: function(response){
            PageUtil.hideMaskLayer();
            if (response.code == "True") {
                scb(response);
            } else {
                ecb(response);
            }
        },
        error: function(){
            PageUtil.hideMaskLayer();
        }
    });
}
*/

function exportTerminalMacs(macs) {
    var form = $("<form>");
    form.attr('style',  'display:none');
    form.attr('target', 'pm-form-action');
    form.attr('method', 'get');
    form.attr('action', '/terminal/macs');

    var input1 = $('<input>');
    input1.attr('type', 'hidden');
    input1.attr('name', 'macs');
    input1.attr('value', macs);
    $('body').append(form);
    form.append(input1);
    form.submit();
}


function removeTerminals(scb, ecb, macs) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/terminal/remove',
        type     : 'POST',
        dataType : 'json',
        data     : {"macs":macs},
        success: function(response){
            PageUtil.hideMaskLayer();
            if (response.code == "True") {
                scb(response);
            } else {
                ecb(response);
            }
        },
        error: function(){
            PageUtil.hideMaskLayer();
        }
    });
}


function connectTest(scb, ecb, serverip) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/connect_test',
        type     : 'POST',
        dataType : 'json',
        data     : {'ip':serverip},
        success: function(response){
            PageUtil.hideMaskLayer();
            if (response.code == "True") {
                scb(response);
            } else {
                ecb(response);
            }
        },
        error: function(){
            PageUtil.hideMaskLayer();
        }
    });
}
