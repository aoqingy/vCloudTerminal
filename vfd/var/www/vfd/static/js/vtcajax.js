//////////////////////////////////////////////////
//
// Resource Related
//
//////////////////////////////////////////////////
function getResources(scb, ecb) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/resource/list',
        type     : 'GET',
        dataType : 'json',
        success  : function(response) {
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


function removeResource(scb, ecb, id) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/resource/remove',
        type     : 'POST',
        dataType : 'json',
        data     : {'id':id},
        success  : function(response) {
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


//////////////////////////////////////////////////
//
// Network Related
//
//////////////////////////////////////////////////
function getNetwork(scb, ecb) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/network/get',
        type     : 'GET',
        dataType : 'json',
        success  : function(response) {
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


function saveNetwork(scb, ecb, iptype, ipaddr, netmask, gateway, dns1, dns2) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/network/set',
        type     : 'POST',
        dataType : 'json',
        data     : {"iptype":iptype, "ipaddr":ipaddr, "netmask":netmask, "gateway":gateway, "dns1":dns1, "dns2":dns2},
        success  : function(response) {
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


function restartNetwork(scb, ecb, iptype, ipaddr, netmask, gateway, dns1, dns2) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/network/restart',
        type     : 'POST',
        dataType : 'json',
        data     : {"iptype":iptype, "ipaddr":ipaddr, "netmask":netmask, "gateway":gateway, "dns1":dns1, "dns2":dns2},
        success  : function(response) {
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


function getWifi(scb, ecb) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/wifi/scan',
        type     : 'POST',
        dataType : 'json',
        success  : function(response) {
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


function getConnectedWifi(scb, ecb) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/wifi/status',
        type     : 'GET',
        dataType : 'json',
        success  : function(response) {
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


function connectWifi(scb, ecb, ssid, password) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/wifi/connect',
        type     : 'POST',
        dataType : 'json',
        data     : {'ssid':ssid, "password":password},
        success  : function(response) {
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

function disconnectWifi(scb, ecb, wifi) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/wifi/disconnect',
        type     : 'POST',
        dataType : 'json',
        data     : {'ssid':wifi},
        success  : function(response) {
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


function ping1(scb, ecb, ip) {
    $.ajax({
        url      : '/api/network/ping1',
        type     : 'POST',
        dataType : 'json',
        data     : {'ip':ip},
        success  : function (response) {
            if(response.code == "True"){
                scb(response);
            } else {
                ecb(response);
            }
        },
        error: function(){
        }
    });
}


function ping2(scb, ecb, ip) {
    $.ajax({
        url      : '/api/network/ping2',
        type     : 'POST',
        dataType : 'json',
        data     : {'ip':ip},
        success  : function (response) {
            if(response.code == "True"){
                scb(response);
            } else {
                ecb(response);
            }
        },
        error: function(){
        }
    });
}


//////////////////////////////////////////////////
//
// Information Related
//
//////////////////////////////////////////////////
function getSystemInfo(scb, ecb) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/system/info',
        type     : 'GET',
        dataType : 'json',
        success  : function(response) {
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


//////////////////////////////////////////////////
//
// Time Related
//
//////////////////////////////////////////////////
function getSystemTime(scb, ecb) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/time/get',
        type     : 'GET',
        dataType : 'json',
        success  : function(response) {
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


function setSystemTime(scb, ecb, year, month, day, hour, minute, second) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/time/set',
        type     : 'POST',
        dataType : 'json',
        data     : {"year":year, "month":month, "day":day, "hour":hour, "minute":minute, "second":second},
        success: function (response) {
            PageUtil.hideMaskLayer();
            if(response.code == "True"){
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


//////////////////////////////////////////////////
//
// Shutdown & Reboot
//
//////////////////////////////////////////////////
function shutdown(scb, ecb) {
    $.ajax({
        url      : '/api/shutdown',
        type     : 'POST',
        dataType : 'json',
        success  : function(response) {
            if (response.code == "True") {
                scb(response);
            } else {
                ecb(response);
            }
        },
        error: function(){
        }
    });
}


function reboot(scb, ecb) {
    $.ajax({
        url      : '/api/reboot',
        type     : 'POST',
        dataType : 'json',
        success  : function(response) {
            if (response.code == "True") {
                scb(response);
            } else {
                ecb(response);
            }
        },
        error: function(){
        }
    });
}


//////////////////////////////////////////////////
//
// Boot Loader Related
//
//////////////////////////////////////////////////
function listBootLoader(scb, ecb, partition) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/terminal/blist',
        type     : 'GET',
        dataType : 'json',
        data     : {"partition":partition},
        success  : function(response) {
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


function changeBootLoader(scb, ecb, partition, uuid) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/terminal/bchange',
        type     : 'POST',
        dataType : 'json',
        data     : {"partition":partition, 'uuid':uuid},
        success  : function(response) {
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


//////////////////////////////////////////////////
//
// Save & Restore Related
//
//////////////////////////////////////////////////
function querySystem(scb, ecb) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/partition/cquery',
        type     : 'GET',
        dataType : 'json',
        success  : function(response) {
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


function saveSystem(scb, ecb, type, dps, path) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/partition/csave',
        type     : 'POST',
        dataType : 'json',
        data     : {"type":type, "dps":dps, "path": path},
        success  : function(response) {
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


function restoreSystem(scb, ecb, type, dps, path) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/partition/crestore',
        type     : 'POST',
        dataType : 'json',
        data     : {"type":type, "dps":dps, "path": path},
        success  : function(response) {
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


function uploadSystem(scb, ecb, path) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/partition/upload',
        type     : 'POST',
        dataType : 'json',
        data     : {"path": path},
        success  : function(response) {
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


function downloadSystem(scb, ecb, path) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/partition/download',
        type     : 'POST',
        dataType : 'json',
        data     : {"path": path},
        success  : function(response) {
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


//////////////////////////////////////////////////
//
// USB Sharing Related
//
//////////////////////////////////////////////////
function getUsbdStatus(scb, ecb) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/usbredir/status',
        type     : 'GET',
        dataType : 'json',
        data     : {},
        success  : function(response) {
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


function startUsbdService(scb, ecb) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/usbredir/start',
        type     : 'POST',
        dataType : 'json',
        data     : {},
        success  : function(response) {
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


function stopUsbdService(scb, ecb) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/usbredir/stop',
        type     : 'POST',
        dataType : 'json',
        data     : {},
        success  : function(response) {
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


function getUsbdPort(scb, ecb) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/usbredir/port',
        type     : 'GET',
        dataType : 'json',
        data     : {},
        success  : function(response) {
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


function getUsbdCallback(scb, ecb) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/usbredir/getcb',
        type     : 'GET',
        dataType : 'json',
        data     : {},
        success  : function(response) {
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


function createUsbdCallback(scb, ecb, ip, port) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/usbredir/createcb',
        type     : 'POST',
        dataType : 'json',
        data     : {'ip':ip , 'port':port},
        success  : function(response) {
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


function closeUsbdCallback(scb, ecb) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/usbredir/closecb',
        type     : 'POST',
        dataType : 'json',
        data     : {},
        success  : function(response) {
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


function listUsbDevices(scb, ecb) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/usbredir/list',
        type     : 'GET',
        dataType : 'json',
        data     : {},
        success  : function(response) {
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


function shareUsbDevice(scb, ecb, uid) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/usbredir/share',
        type     : 'POST',
        dataType : 'json',
        data     : {'uid': uid},
        success  : function(response) {
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


function unshareUsbDevice(scb, ecb, uid) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/usbredir/unshare',
        type     : 'POST',
        dataType : 'json',
        data     : {'uid': uid},
        success  : function(response) {
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


//////////////////////////////////////////////////
//
// Upgrade, License and Log
//
//////////////////////////////////////////////////
function upgradeSystem(scb, ecb) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/upgrade/usb',
        type     : 'POST',
        dataType : 'json',
        success  : function(response) {
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


function uploadLicense(scb, ecb, module) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/license/usb',
        type     : 'POST',
        dataType : 'json',
        data     : {'module': module},
        success  : function(response) {
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


function getSystemLog(scb, ecb) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/log/usb',
        type     : 'POST',
        dataType : 'json',
        success  : function(response) {
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


//////////////////////////////////////////////////
//
// Desktop Related
//
//////////////////////////////////////////////////
function connectTest(scb, ecb, serverip) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/connect_test',
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


function getDesktops(scb, ecb, serverip, username, password, domain) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/desktop/list',
        type     : 'POST',
        dataType : 'json',
        data     : {'serverip': serverip, 'username': username, 'password': password, 'domain': domain},
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


function startAndConnectSpice(scb, ecb, serverip, username, password, domain, vmid) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/spice/connect',
        type     : 'POST',
        dataType : 'json',
        data     : {'serverip': serverip, 'username': username, 'password': password, 'domain': domain, 'vmid': vmid},
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


function startAndConnectRdp(scb, ecb, serverip, username, password, domain, vmid, rusername, rpassword) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/rdp/connect',
        type     : 'POST',
        dataType : 'json',
        data     : {'serverip': serverip, 'username': username, 'password': password, 'domain': domain, 'vmid': vmid, 'rusername': rusername, 'rpassword': rpassword},
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


function connectRegularRdp(scb, ecb, serverip, username, password) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/rdp/rconnect',
        type     : 'POST',
        dataType : 'json',
        data     : {'serverip': serverip, 'username': username, 'password':password},
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


function connectVMware(scb, ecb, serverip, username, password) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/vmware/connect',
        type     : 'POST',
        dataType : 'json',
        data     : {'serverip': serverip, 'username': username, 'password': password},
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


function connectCitrix(scb, ecb, serverip) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/citrix/connect',
        type     : 'POST',
        dataType : 'json',
        data     : {'serverip': serverip},
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


function getFiles(scb, ecb, path) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/file/list',
        type     : 'GET',
        dataType : 'json',
        data     : {'path': path},
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


function getMemory(scb, ecb) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/idv/memory',
        type     : 'GET',
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


function getCpu(scb, ecb) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/idv/cpu',
        type     : 'GET',
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


function getDisks(scb, ecb) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/idv/disk',
        type     : 'GET',
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


function getIsos(scb, ecb) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/idv/iso',
        type     : 'GET',
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


function getVfds(scb, ecb) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/idv/vfd',
        type     : 'GET',
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


function getPcis(scb, ecb) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/idv/pci',
        type     : 'GET',
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


function getAvailableDisk(scb, ecb) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/idv/adisk',
        type     : 'GET',
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


function createDisk(scb, ecb, name, size) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/idv/cdisk',
        type     : 'POST',
        dataType : 'json',
        data     : {'name': name, 'size': size},
        success  : function(response) {
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


function connectIdv(scb, ecb, name) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/idv/connect',
        type     : 'POST',
        dataType : 'json',
        data     : {'name': name},
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


function createIdv(scb, ecb, name, autostart, cpu, memory, sdisk, ddisk, cdrom, floppy, nettype, ipaddr, netmask, gateway, dns, pci) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/idv/create',
        type     : 'POST',
        dataType : 'json',
        data     : {'name': name, 'autostart': autostart, 'cpu': cpu, 'memory': memory, 'sdisk': sdisk, 'ddisk': ddisk, 'cdrom': cdrom, 'floppy': floppy, 'nettype': nettype, 'ipaddr': ipaddr, 'netmask': netmask, 'gateway': gateway, 'dns': dns, 'pci': pci},
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


function removeIdv(scb, ecb, name) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/idv/remove',
        type     : 'POST',
        dataType : 'json',
        data     : {'name': name},
        success  : function(response) {
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


function getIdvs(scb, ecb) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/idv/list',
        type     : 'GET',
        dataType : 'json',
        success  : function(response) {
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


function getIdvInfo(scb, ecb, name) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/idv/info',
        type     : 'GET',
        dataType : 'json',
        data     : {'name': name},
        success  : function(response) {
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


function editIdvCpu(scb, ecb, name, cpu) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/idv/ecpu',
        type     : 'POST',
        dataType : 'json',
        data     : {'name': name, 'cpu': cpu},
        success  : function(response) {
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


function editIdvMemory(scb, ecb, name, memory) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/idv/ememory',
        type     : 'POST',
        dataType : 'json',
        data     : {'name': name, 'memory': memory},
        success  : function(response) {
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


function editIdvCdrom(scb, ecb, name, cdrom, boot) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/idv/ecdrom',
        type     : 'POST',
        dataType : 'json',
        data     : {'name': name, 'cdrom': cdrom, 'boot': boot},
        success  : function(response) {
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


function editIdvFloppy(scb, ecb, name, floppy) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/idv/efloppy',
        type     : 'POST',
        dataType : 'json',
        data     : {'name': name, 'floppy': floppy},
        success  : function(response) {
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


function editIdvSdisk(scb, ecb, name, sdisk, sdisk_restore, boot) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/idv/esdisk',
        type     : 'POST',
        dataType : 'json',
        data     : {'name': name, 'sdisk': sdisk, 'sdisk_restore': sdisk_restore, 'boot': boot},
        success  : function(response) {
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


function editIdvDdisk(scb, ecb, name, ddisk, ddisk_restore) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/idv/eddisk',
        type     : 'POST',
        dataType : 'json',
        data     : {'name': name, 'ddisk': ddisk, 'ddisk_restore': ddisk_restore},
        success  : function(response) {
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


function editIdvNetwork(scb, ecb, name, nettype, ipaddr, netmask, gateway, dns) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/idv/enetwork',
        type     : 'POST',
        dataType : 'json',
        data     : {'name': name, 'nettype': nettype, 'ipaddr': ipaddr, 'netmask': netmask, 'gateway': gateway, 'dns': dns},
        success  : function(response) {
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


function editIdvPci(scb, ecb, name, pci) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/idv/epci',
        type     : 'POST',
        dataType : 'json',
        data     : {'name': name, 'pci': pci},
        success  : function(response) {
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


function editIdvAutoStart(scb, ecb, name, autostart) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/idv/eautostart',
        type     : 'POST',
        dataType : 'json',
        data     : {'name': name, 'autostart': autostart},
        success  : function(response) {
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


function redrawPciDevices(scb, ecb, pci) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/idv/pdevice',
        type     : 'GET',
        dataType : 'json',
        data     : {'pci': pci},
        success  : function(response) {
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


function checkPermit(scb, ecb) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/permit/check',
        type     : 'GET',
        dataType : 'json',
        data     : {},
        success  : function(response) {
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


function verifyPermit(scb, ecb, password) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/permit/verify',
        type     : 'POST',
        dataType : 'json',
        data     : {'password': password},
        success  : function(response) {
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


function mountUsb(scb, ecb, path) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/usb/mount',
        type     : 'POST',
        dataType : 'json',
        data     : {'path':path},
        success  : function(response) {
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


function unmountUsb(scb, ecb, path) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/usb/unmount',
        type     : 'POST',
        dataType : 'json',
        data     : {'path': path},
        success  : function(response) {
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


function copyFile(scb, ecb, sfile, dpath) {
    PageUtil.showMaskLayer();
    $.ajax({
        url      : '/api/file/copy/start',
        type     : 'POST',
        dataType : 'json',
        data     : {'sfile': sfile, 'dpath': dpath},
        success  : function(response) {
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


function getFileProgress(scb, ecb, task_id) {
    $.ajax({
        url      : '/api/file/status',
        type     : 'GET',
        dataType : 'json',
        data     : {'task_id': task_id},
        success  : function(response) {
            if (response.code == "True") {
                scb(response);
            } else {
                ecb(response);
            }
        },
        error: function(){
        }
    });
}

