#!/usr/bin/python
#-*-coding:utf-8 -*-
import os
import time
import json
import subprocess
from flask import request
#from flask.ext.babel import gettext as _
from const   import *
from virtapi import *
from utility import *


#@app.route('/api/usbredir/status', methods=['GET'])
def get_usbd_status():
    logger.info("Entering get_usbd_status...")

    try:
        pidfile = "/var/run/usbsrvd.pid"
        if os.path.exists(pidfile) and os.path.isfile(pidfile):
            rstatus = "started"
        else:
            rstatus = "stopped"
        logger.info(rstatus)
        return json.dumps({'code':'True', 'message':rstatus})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/usbredir/start', methods=['POST'])
def start_usbd_service():
    logger.info("Entering start_usbd_service...")

    try:
        #USB共享入口(aoqingy)
        if not check_useable('usbredir'):
            raise Exception('USB Redir license not activiated!')

        command = "/etc/init.d/rc.usbsrvd start"
        p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        p.communicate()

        time.sleep(2)		#确保后续调用能获取到服务状态和端口(aoqingy)

        command = "usbsrv -settcpport 32032"
        p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

        rdevices = []

        command = "usbsrv -list devices"
        p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

        for line in p.stdout.readlines():
            try:
                segments = line.strip().split(':', 1)
                key   = segments[0].strip()
                value = segments[1].strip()
                if key == 'Status':
                    rdevices.append({'uid': uid, 'name': name, 'status': value})
                try:
                    uid = int(key)
                    name = value
                except:
                    pass
            except:
                pass

        for device in rdevices:
            command = 'usbsrv -remexclude %s' % device['uid']
            p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

        for device in rdevices:
            #应该改成文件方式(aoqingy)
            if 'Logitech' in device['name'] or 'Mouse' in device['name'] or 'Keyboard' in device['name']:
                command = 'usbsrv -addexclude %s' % device['uid']
                p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

        command = 'usbsrv -autoshare on'
        p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

        logger.info("Done!")
        return json.dumps({'code':'True', 'message':"Done!"})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/usbredir/stop', methods=['POST'])
def stop_usbd_service():
    logger.info("Entering stop_usbd_service...")

    try:
        command = "/etc/init.d/rc.usbsrvd stop"
        p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        p.communicate()

        logger.info("Done!")
        return json.dumps({'code':'True', 'message':"Done!"})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/usbredir/port', methods=['GET'])
def get_usbd_port():
    logger.info("Entering get_usbd_port...")

    try:
        rport = ''

        command = "lsof -i -P -n | grep usbsrvd | awk '{print $9}'"
        p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        for line in p.stdout.readlines():
            line = line.strip()
            if line.startswith('*:'):
                rport = line[2:]
                break

        logger.info(rport)
        return json.dumps({'code':'True', 'message':rport})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/usbredir/getcb', methods=['GET'])
def get_usbd_callback():
    logger.info("Entering get_usbd_callback...")

    try:
        rcallback = {}
        rcallback['ip'] = ''
        rcallback['port'] = ''

        command = "lsof -i -P -n | grep usbsrvd | awk '{print $9}'"
        p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        for line in p.stdout.readlines():
            line = line.strip()
            try:
                mapping = line.split('->')
                desktop = mapping[1].split(':')
                rcallback['ip'] = desktop[0]
                rcallback['port'] = desktop[1]
                break
            except Exception, e2:
                pass

        logger.info(rcallback)
        return json.dumps({'code':'True', 'message':rcallback})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/usbredir/createcb', methods=['POST'])
def create_usbd_callback():
    logger.info("Entering create_usbd_callback...")
    ip = request.form.get('ip', '')
    port = request.form.get('port', '')
    logger.info("ip: %s, port: %s" % (ip, port))

    try:
        command = "usbsrv -closecallback *"
        p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        p.communicate()

        command = "usbsrv -createcallback %s:%s" % (ip, port)
        p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        p.communicate()

        time.sleep(2)

        logger.info("Done!")
        return json.dumps({'code':'True', 'message':"Done!"})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/usbredir/closecb', methods=['POST'])
def close_usbd_callback():
    logger.info("Entering close_usbd_callback...")

    try:
        command = "usbsrv -closecallback *"
        p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        p.communicate()

        logger.info("Done!")
        return json.dumps({'code':'True', 'message':"Done!"})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/usbredir/list', methods=['GET'])
def list_usb_devices():
    logger.info("Entering list_usb_devices...")

    try:
        rdevices = []

        command = "usbsrv -list devices"
        p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

        for line in p.stdout.readlines():
            try:
                segments = line.strip().split(':', 1)
                key   = segments[0].strip()
                value = segments[1].strip()
                if key == 'Status':
                    rdevices.append({'uid': uid, 'name': name, 'status': value})
                try:
                    uid = int(key)
                    name = value
                except:
                    pass
            except:
                pass

        logger.info(rdevices)
        return json.dumps({'code':'True', 'message':rdevices})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/usbredir/share', methods=['POST'])
def share_usb_device():
    logger.info("Entering share_usb_device...")
    uid = request.form.get('uid', '')
    logger.info("uid: %s" % uid)

    try:
        command = 'usbsrv -share %s' % uid
        p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        p.communicate()
        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/usbredir/unshare', methods=['POST'])
def unshare_usb_device():
    logger.info("Entering unshare_usb_device...")
    uid = request.form.get('uid', '')
    logger.info("uid: %s" % uid)

    try:
        command = 'usbsrv -unshare %s' % uid
        p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        p.communicate()
        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})

