#!/usr/bin/python
#-*-coding:utf-8 -*-
from flask import Flask, request
#from flask.ext.babel import gettext as _
from werkzeug import secure_filename
import re
import os
import json
import urllib2
import subprocess
from const   import *
from virtapi import *
from utility import *


#@app.route('/api/connect_test', methods=['POST'])
#这个函数怎么理解(aoqingy)，是否可以在这个函数里面等待网络起来？
def connect_test():
    logger.info("connect_test...")
    ip = request.form.get('ip')
    logger.info("ip:%s" % ip)

    try:
        for card in os.listdir('/sys/class/net'):
            if re.search('^(?=e)', card):
                nic = card
                break

        nic_stat = 1
        for ln in os.popen('ifconfig %s' % nic, 'r'):
            status = re.search('RUNNING', ln)
            if status:
                nic_stat = 0
                break

        if nic_stat:
            raise Exception('Network not configured!')

        p = subprocess.Popen('%s/connect_test.sh "%s"' % (SCRIPT_DIR, ip), shell=True, stdout=subprocess.PIPE)
        out, err = p.communicate()
        if p.returncode != 0:
            raise Exception(err)

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/desktop/list', methods=['GET'])
def get_desktops():
    logger.info('Entering get_desktops...')
    serverip  = request.form.get('serverip', '')
    username  = request.form.get('username', '')
    password  = request.form.get('password', '')
    domain    = request.form.get('domain',   '')
    logger.info('serverip: %s, username: %s, domain: %s' % (serverip, username, domain))

    try:
        postfix = getAccessPostfix(serverip, username+'@'+domain, password)
        #重新获取并保存版本号，否则在IP地址切换时会有问题（aoqingy）
        getVersion(serverip+'/'+postfix, username+'@'+domain, password, cache=False)
        #考虑到虚拟机池
        for pool in getAllVmPools(serverip+'/'+postfix, username+'@'+domain, password):
            try:
                allocateVm(serverip+'/'+postfix, username+'@'+domain, password, pool['id'])
            except Exception, e2:
                logger.warning(str(e2))
        rvms = getAllVms(serverip+'/'+postfix, username+'@'+domain, password)
        logger.info(rvms)
        return json.dumps({'code':'True', 'message':rvms})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


RETRY_COUNT = 5
def safeStopVm(serverip, username, password, vmid):
    count = 0
    while (count < RETRY_COUNT):
        stopVm(serverip, username, password, vmid)
        while True:
            time.sleep(3)
            status = getVmStatus(serverip, username, password, vmid)
            logger.info(status)
            if status.lower() == "down":
                return
            count = count + 1
            if count == RETRY_COUNT:
                raise Exception("Stopping vm failed!")
            break


def safeStartVm(serverip, username, password, vmid):
    count = 0
    while (count < RETRY_COUNT):
        startVm(serverip, username, password, vmid)
        while True:
            time.sleep(3)
            status = getVmStatus(serverip, username, password, vmid)
            logger.info(status)
            if status.lower() == "powering_up" or status.lower() == "up":
                return
            if status.lower() == "down":
                count = count + 1
                if count == RETRY_COUNT:
                    raise Exception("Starting vm failed!")
                break


#@app.route('/api/spice/connect', methods=['POST'])
def connect_virtualized_spice():
    logger.info('Entering connect_virtualized_spice...')
    serverip = request.form.get('serverip', '')
    username = request.form.get('username', '')
    password = request.form.get('password', '')
    domain   = request.form.get('domain',   '')
    vmid     = request.form.get('vmid',     '')
    logger.info('serverip: %s, username: %s, domain: %s, vmid: %s' % (serverip, username, domain, vmid))

    try:
        #SPICE桌面接入入口(aoqingy)
        if not check_useable('vdi'):
            raise Exception('VDI license not activiated.')

        postfix = getAccessPostfix(serverip, username+'@'+domain, password)

        #如果虚拟机未启动，则启动之
        status = getVmStatus(serverip+'/'+postfix, username+'@'+domain, password, vmid)
        logger.info("Checkig vm status: %s" % status)

        if status == 'suspended' or status == 'paused':
            logger.info("Stopping vm...")
            safeStopVm(serverip+'/'+postfix, username+'@'+domain, password, vmid)
            logger.info("Stopped...")

        status = getVmStatus(serverip+'/'+postfix, username+'@'+domain, password, vmid)
        logger.info("Checkig vm status: %s" % status)
        if status == 'down' or status == 'powering_down':
            logger.info("Starting vm...")
            safeStartVm(serverip+'/'+postfix, username+'@'+domain, password, vmid)
            logger.info("Started...")

        #获取虚拟机所运行在的宿主机
        logger.info("Retrieving vm info...")
        info = getVmInfo(serverip+'/'+postfix, username+'@'+domain, password, vmid)
        logger.info(info)

        name        = info['name']
        type_       = info['display_type']
        address     = info['display_address']
        port        = info['port']
        secure_port = info['sport']
        host_id     = info['host_id']

        ca = fetchCA(serverip+'/'+postfix)
        ca = ca.replace("\n", "\\n")
        certificate_subject = getHostCertificateSubject(serverip+'/'+postfix, username+'@'+domain, password, host_id)
        #smartcard_enabled   = getVmDisplaySmartCardEnabled(serverip+'/'+postfix, username+'@'+domain, password, vmid)
        #smartcard_enabled   = '1' if smartcard_enabled=='true' else '0'
        ticket = setVmTicket(serverip+'/'+postfix, username+'@'+domain, password, vmid, 120)

        vv = """[virt-viewer]
type=%s
host=%s
port=%s
password=%s
# Password is valid for 120 seconds.
tls-port=%s
fullscreen=1
title=%s
enable-smartcard=0
enable-usb-autoshare=1
delete-this-file=1
usb-filter=-1,-1,-1,-1,0
tls-ciphers=DEFAULT
host-subject=%s
ca=%s
toggle-fullscreen=shift+f11
release-cursor=shift+f12
secure-attention=ctrl+alt+end
secure-channels=main;inputs;cursor;playback;record;display;usbredir;smartcard
""" % (type_, address, port, ticket, secure_port, name, certificate_subject, ca)
        logger.info(vv)

        f = open('/tmp/console.vv', 'w')
        f.write(vv)
        f.close()

        subprocess.Popen('%s/connect_via_spice.sh /tmp/console.vv' % SCRIPT_DIR, shell = True)

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/rdp/connect', methods=['POST'])
def connect_virtualized_rdp():
    logger.info('Entering connect_virtualized_rdp...')
    serverip  = request.form.get('serverip',  '')
    username  = request.form.get('username',  '')
    password  = request.form.get('password',  '')
    domain    = request.form.get('domain',    '')
    vmid      = request.form.get('vmid',      '')
    rusername = request.form.get('rusername', 'vdi')
    rpassword = request.form.get('rpassword', 'vdi123')
    logger.info('serverip: %s, username: %s, domain: %s, vmid: %s, rusername: %s' % (serverip, username, domain, vmid, rusername))

    try:
        postfix = getAccessPostfix(serverip, username+'@'+domain, password)

        #如果虚拟机未启动，则启动之
        status = getVmStatus(serverip+'/'+postfix, username+'@'+domain, password, vmid)
        logger.info("Checkig vm status: %s" % status)

        if status == 'down' or status == 'powering_down':
            logger.info("Starting vm...")
            safeStartVm(serverip+'/'+postfix, username+'@'+domain, password, vmid)
            logger.info("Started...")

        #获取虚拟机所运行在的宿主机
        logger.info("Retrieving vm info...")
        info = getVmInfo(serverip+'/'+postfix, username+'@'+domain, password, vmid)
        logger.info(info)

        #获取虚拟机的IP地址
        ipaddr = info['ips'][0]
        hostid = info['host_id']
        #检查端口映射
        #如果未映射（用默认的用户名和密码连接到虚拟机的IP地址和默认3389端口）
        #如果已映射（用默认的用户名和密码连接到宿主机的IP地址和映射RDP端口）
        try:
            try:
                dip = getHostAddress(serverip+'/'+postfix, username+'@'+domain, password, hostid)
                logger.info("Trying host ipaddr: %s" % dip)
                url = "http://%s/cgi-bin/terminal/get-map-conf.cgi?dstip=%s" % (dip, ipaddr)
                logger.info("Retrieving port mapping...")
                mrequest = urllib2.Request(url)
                mdata = eval(urllib2.urlopen(mrequest).read())
            except:
                dip = serverip
                logger.info("Trying engine ipaddr: %s" % dip)
                url = "http://%s/cgi-bin/terminal/get-map-conf.cgi?dstip=%s" % (dip, ipaddr)
                logger.info("Retrieving port mapping...")
                mrequest = urllib2.Request(url)
                mdata = eval(urllib2.urlopen(mrequest).read())

            logger.info(mdata)
            dport = mdata[0]['srcport']
        except:
            dip   = ipaddr
            dport = '3389'

        logger.info('%s %s %s %s' % (dip, dport, rusername, rpassword))
        action = subprocess.Popen('%s/connect_via_rdp.sh %s %s %s %s' % (SCRIPT_DIR, dip, dport, rusername, rpassword), shell = True, stdout=subprocess.PIPE)
        action.communicate()[0]
        if action.returncode >= 16:
            raise Exception('RDP error: %s' % str(action.returncode))

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/rdp/rconnect', methods=['POST'])
def connect_regular_rdp():
    logger.info('Entering connnect_regular_rdp...')
    serverip = request.form.get('serverip', '')
    username = request.form.get('username', '')
    password = request.form.get('password', '')
    logger.info('serverip: %s, username: %s' % (serverip, username))

    try:
        #RDP桌面接入入口(aoqingy)
        if not check_useable('vdi'):
            raise Exception('VDI license not activiated.')

        logger.info('%s %s %s %s' % (serverip, '3389', username, password))
        subprocess.Popen('%s/connect_via_rdp.sh %s %s %s %s' % (SCRIPT_DIR, serverip, '3389', username, password), shell = True)
        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/vmware/connect', methods=['POST'])
def connect_vmware():
    logger.info("Entering connect_vmware...")
    serverip = request.form.get('serverip', '')
    username = request.form.get('username', '')
    password = request.form.get('password', '')
    logger.info('serverip: %s, username: %s' % (serverip, username))

    try:
        #VMware桌面接入入口(aoqingy)
        if not check_useable('vdi'):
            raise Exception('VDI license not activiated.')

        subprocess.Popen('%s/connect_via_vmware.sh %s %s %s' % (SCRIPT_DIR, serverip, username, password), shell=True)
        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/citrix/connect', methods=['POST'])
def connect_citrix():
    logger.info("Entering connect_citrix...")
    serverip = request.form.get('serverip', '')
    logger.info('serverip: %s' % serverip)

    try:
        #Citrix桌面接入入口(aoqingy)
        if not check_useable('vdi'):
            raise Exception('VDI license not activiated.')

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':serverip})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})

