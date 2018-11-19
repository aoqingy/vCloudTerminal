#!/usr/bin/python
#-*-coding:utf-8 -*-
from flask import request
#from flask.ext.babel import gettext as _
import re
import os
import json
import subprocess
from const   import *
from virtapi import *
from utility import *

#app = Flask(__name__)


##########################################################
#
# Network Related Logic
#
##########################################################
def check_nic():
    nic = ''
    for card in os.listdir('/sys/class/net'):
        if re.search('^(?=e)', card):
            nic = card
            break
    if not nic:
        raise Exception('NIC not found.')
    return nic


def get_ip_info(nic):
    iptype  = 'dhcp'
    ipaddr  = ''
    netmask = ''
    gateway = ''

    with open("/etc/network/interfaces") as f:
        for i in f.readlines():
            rv = re.search('(?<=%s inet ).+' % nic,i)
            if rv:
                iptype = rv.group(0)

    command = subprocess.Popen('ifconfig "%s"' % nic, shell=True, stdout=subprocess.PIPE)
    output, dummy = command.communicate()
    for line in output.split('\n'):
        rv = re.search('(?<=inet addr:)\S+', line)
        if rv:
            ipaddr = rv.group(0)
        rv = re.search('(?<=inet 地址:)\S+', line)        #如果安装的操作系统为中文(aoqingy)
        if rv:
            ipaddr = rv.group(0)
        rv = re.search('(?<=Mask:)\S+', line)
        if rv:
            netmask = rv.group(0)
        rv = re.search('(?<=掩码:)\S+', line)             #如果安装的操作系统为中文(aoqingy)
        if rv:
            netmask = rv.group(0)

    command = subprocess.Popen('route -n', shell=True, stdout=subprocess.PIPE)
    output, dummy = command.communicate()
    for line in output.split('\n'):
        rv = re.search('^0.0.0.0\s+(?P<gateway>\S+)', line)
        if rv:
            gateway = rv.group('gateway')

    return iptype, ipaddr, netmask, gateway


def get_dns_info():
    dns1 = ''
    dns2 = ''
    dns  = ''
    with open("/etc/resolv.conf") as f:
        for line in f.readlines():
            rv = re.search('(?<=nameserver[\s+])\S+', line)
            if rv:
                if dns:
                    dns = dns + ' ' + rv.group(0)
                else:
                    dns = rv.group(0)

    dnss = dns.split(' ')
    dns1 = dnss[0]
    if len(dnss) >= 2:
        dns2 = dnss[1]

    return dns1, dns2


def save_ip(nic, iptype, ipaddr, netmask, gateway):
    f = open('/etc/network/interfaces', 'w')
    f.write('auto lo\n')
    f.write('iface lo inet loopback\n\n')
    f.write('auto %s\n' % nic)
    if iptype == 'static':
        f.write('iface %s inet static\n' % nic)
        f.write('    address %s\n' % ipaddr)
        f.write('    netmask %s\n' % netmask)
        if gateway != '':
            f.write('    gateway %s\n' % gateway)
        #else:
        #    os.popen('route del default')
    else:
        f.write('iface %s inet dhcp\n' % nic)
    f.close()


def apply_ip(nic, iptype, ipaddr, netmask, gateway):
    if iptype == 'static':
        os.popen('ifconfig %s down' % nic)
        os.popen('ifconfig %s %s network %s' % (nic, ipaddr, netmask))
        os.popen('ifconfig %s up' % nic)
        os.popen('route add default gw %s' % gateway)
    else:
        os.popen('dhclient -r %s' % nic)
        os.popen('rm -rf /var/lib/dhclient/*')
        os.popen('dhclient %s' % nic)


def save_dns(dns1, dns2):
    if dns1:
        f = open('/run/resolvconf/resolv.conf', 'w+')
        f.write('nameserver %s\n' % dns1)
        if dns2:
            f.write('nameserver %s\n' % dns2)
        f.close()
        if os.path.exists("/etc/resolvconf/resolv.conf.d/base"):
            f = open('/etc/resolvconf/resolv.conf.d/base', 'w+')
            f.write('nameserver %s\n' % dns1)
            if dns2:
                f.write('nameserver %s\n' % dns2)
            f.close()
    else:
        if dns2:
            f = open('/run/resolvconf/resolv.conf', 'w+')
            f.write('nameserver %s\n' % dns2)
            f.close()
            if os.path.exists("/etc/resolvconf/resolv.conf.d/base"):
                f = open('/etc/resolvconf/resolv.conf.d/base', 'w+')
                f.write('nameserver %s\n' % dns2)
                f.close()
        else:                       #如果既没指定DNS1，又没指定DNS2，为何要这样处理(aoqingy)
            f = open('/run/resolvconf/resolv.conf', 'w+')
            f.close()
            if os.path.exists("/etc/resolvconf/resolv.conf.d/base"):
                f = open('/etc/resolvconf/resolv.conf.d/base', 'w+')
                f.close()


#@app.route('/api/network/get', methods=['GET'])
def get_network():
    logger.info("Entering get_network...")
    try:
        nic = check_nic()
        iptype, ipaddr, netmask, gateway = get_ip_info(nic)
        dns1, dns2 = get_dns_info()
        rv = {'iptype':iptype, 'ipaddr':ipaddr, 'netmask':netmask, 'gateway':gateway, 'dns1':dns1, 'dns2':dns2}

        logger.info(rv)
        return json.dumps({'code':'True', 'message':rv})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/network/set', methods=['POST'])
def set_network():
    logger.info('Enter set_network ...')
    try:
        iptype   = request.form.get('iptype',  '')
        ipaddr   = request.form.get('ipaddr',  '')
        netmask  = request.form.get('netmask', '')
        gateway  = request.form.get('gateway', '')
        dns1     = request.form.get('dns1',    '')
        dns2     = request.form.get('dns2',    '')

        logger.info('iptype:%s, ipaddr:%s, netmask:%s, gateway:%s, dns1:%s, dns2:%s' % (iptype, ipaddr, netmask, gateway, dns1, dns2))

        if iptype != 'static' and iptype != 'dhcp':
            raise Exception('Invalid Network Type!')
        if iptype == 'static':
            if ipaddr == '' or not check_ip(ipaddr):
                raise Exception('Invalid IP Address!')
            if netmask == '' or not check_netmask(netmask):
                raise Exception('Invalid Netmask!')
            if gateway and not check_ip(gateway):
                raise Exception('Invalid Gateway!')
        if dns1 and not check_ip(dns1):
            raise Exception('Invalid DNS Address!')
        if dns2 and not check_ip(dns2):
            raise Exception('Invalid DNS Address!')

        nic = check_nic()
        save_ip(nic, iptype, ipaddr, netmask, gateway)
        save_dns(dns1, dns2)

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/network/restart', methods=['POST'])
def restart_network():
    logger.info("Entering restart_network...")
    try:
        iptype   = request.form.get('iptype',  '')
        ipaddr   = request.form.get('ipaddr',  '')
        netmask  = request.form.get('netmask', '')
        gateway  = request.form.get('gateway', '')
        dns1     = request.form.get('dns1',    '')
        dns2     = request.form.get('dns2',    '')

        logger.info('iptype:%s, ipaddr:%s, netmask:%s, gateway:%s, dns1:%s, dns2:%s' % (iptype, ipaddr, netmask, gateway, dns1, dns2))

        if iptype != 'static' and iptype != 'dhcp':
            raise Exception('Invalid Network Type!')
        if iptype == 'static':
            if ipaddr == '' or not check_ip(ipaddr):
                raise Exception('Invalid IP Address!')
            if netmask == '' or not check_netmask(netmask):
                raise Exception('Invalid Netmask!')
            if gateway and not check_ip(gateway):
                raise Exception('Invalid Gateway!')
        if dns1 and not check_ip(dns1):
            raise Exception('Invalid DNS Address!')
        if dns2 and not check_ip(dns2):
            raise Exception('Invalid DNS Address!')

        nic = check_nic()
        apply_ip(nic, iptype, ipaddr, netmask, gateway)
        save_dns(dns1, dns2)

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


##########################################################
#
# Wifi Related Logic
#
##########################################################
#@app.route('/api/wifi/scan', methods=['POST'])
def scan_wifi():
    logger.info("Entering scan_wifi...")

    try:
        wifilist = []
        os.popen('rfkill unblock all')
        wifi_nic = None
        for card in os.listdir('/sys/class/net'):
            if re.search('^(?=w)', card):
                wifi_nic = card
                break
        if not wifi_nic:
            raise Exception('Wifi nic not found!')

        os.popen('ifconfig %s up' % wifi_nic)
        for ln in os.popen("iwlist scan | grep ESSID", 'r'):
            wifilist.append(re.search('ESSID:\"(?P<wifi>.+)\"\s', ln).group('wifi'))
        wifilist = list(set(wifilist))
        wifilist = sorted(wifilist)
        wifi_list=[]
        for ls in wifilist:
            wifi_list.append(ls.decode('string_escape'))
        return json.dumps({'code':'True', 'message':wifi_list})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/wifi/status', methods=['GET'])
def status_wifi():
    logger.info("Entering status_wifi...")

    try:
        wifistat = []
        for ln in os.popen("iwgetid", 'r'):
            wifistat.append(re.search('ESSID:\"(?P<wifi>.+)\"\s', ln).group('wifi'))

        logger.info(wifistat)
        if wifistat != "":
            return json.dumps({'code':'True', 'message':wifistat})
        else:
            return json.dumps({'code':'False', 'message':wifistat})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/wifi/connect', methods=['POST'])
def connect_wifi():
    logger.info("Entering connect_wifi...")

    try:
        ssid     = request.form.get('ssid')
        password = request.form.get('password')
        if password:
            action = subprocess.Popen('nmcli d wifi connect %s password %s' % (ssid, password) , shell=True, stdout=subprocess.PIPE)
        else:
            action = subprocess.Popen('nmcli d wifi connect %s' % ssid, shell=True, stdout=subprocess.PIPE)
        p = action.communicate()[0]
        rc = action.returncode
        if rc != 0:
            raise Exception('Failed to connect Wifi.')
        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/wifi/disconnect', methods=['POST'])
def disconnect_wifi():
    logger.info("Entering disconnect_wifi...")
    try:
        ssid = request.form.get('ssid')
        for ln in os.popen("iwgetid", 'r'):
            wifi_iface = re.search('(?P<iface>^.+)\s.+"%s"' % ssid, ln).group('iface')
            if wifi_iface:
                break

        if wifi_iface == "":
            raise Exception("Wifi not connected!")

        p = subprocess.Popen('nmcli d disconnect %s' % wifi_iface , shell=True, stdout=subprocess.PIPE)
        if p.returncode != 0:
            raise Exception("Fail to disconnect wifi!")

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


##########################################################
#
# Network Test Related
#
##########################################################
#@app.route('/api/network/ping1', methods=['POST'])
def ping1():
    logger.info("Entering ping1...")
    ip = request.form.get('ip', '')
    logger.info("ip: %s" % ip)

    try:
        if not ip:
            raise Exception("IP address invalid!")

        pinfo = ''
        for ln in os.popen('ping %s -w 1 -c 1' % ip, 'r'):
            status = re.search('(?=PING).+', ln)
            if status:
                pinfo = status.group(0)
                break

        if pinfo == '':
            raise Exception('ping: unknown host ' + ip)

        logger.info(pinfo)
        return json.dumps({'code':'True', 'message':pinfo})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/network/ping2', methods=['POST'])
def ping2():
    logger.info("Entering ping2...")
    ip = request.form.get('ip', '')
    logger.info("ip: %s" % ip)

    try:
        if not ip:
            raise Exception('IP address invalid!')

        pinfo = ''
        for ln in os.popen('ping %s -w 1 -c 1' % ip, 'r'):
            status = re.search('.+(?=icmp_seq).+', ln)
            if status:
                pinfo = status.group(0)
                break

        if pinfo == '':
            raise Exception('1 packets transmitted, 0 received, 100% packet loss, time 0ms')

        logger.info(pinfo)
        return json.dumps({'code':'True', 'message':pinfo})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})

