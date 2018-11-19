#!/usr/bin/python
#-*-coding:utf-8 -*-
import os
import re
import json
import glob
import shutil
import struct
import socket
import hashlib
import tarfile
import tempfile
import subprocess
from datetime import datetime
from werkzeug import secure_filename
from flask import request, send_file, make_response
#from flask.ext.babel import gettext as _
from const   import *
from utility import *


#@app.route('/api/identify', methods=['POST'])
def identify():
    logger.info("Entering identify...")

    try:
        uuid = info_uuid()
        mac  = info_mac()
        rv   = {'uuid':uuid, 'mac':mac}

        who = request.headers.get('X-Real-Ip', request.remote_addr)
        f = open('%s/manager_ip' % COUNTER_DIR, 'w')     #记录管理者IP以便后续通信（例如举手）
        f.write(who)
        f.close()

        logger.info(rv)
        return json.dumps({'code':'True', 'message':rv})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/system/info', methods=['GET'])
def system_info():
    logger.info("Entering system_info...")

    try:
        cpu_model, cpu_core = info_cpu()
        mem_total, mem_free = info_memory()

        uptime      = info_uptime()
        uuid        = info_uuid()
        mac         = info_mac()
        usb         = info_usb()
        kernel      = info_kernel()
        disk        = info_disk()
        vfd_ver     = info_vvfd()
        #viewer_ver = info_vviewer()
        iso_ver     = info_viso()
        media       = info_media()

        lstatus     = lic_status()
        #ldays       = lic_days()
        dbstatus    = info_db()

        rv = {'kernel':kernel, 'disk':disk, 'cpu_model':cpu_model, 'cpu_core':cpu_core, 'mem_total':mem_total, 'mem_free':mem_free, 'uuid':uuid, 'mac': mac, 'usb':usb, 'uptime':uptime, 'vfd_ver':vfd_ver, 'iso_ver':iso_ver, 'media':media, 'lic_status':lstatus, 'db_status':dbstatus}

        logger.info(rv)
        return json.dumps({'code':'True', 'message':rv})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


##########################################################
#
# Shutdown & Reboot
#
##########################################################
#@app.route('/api/shutdown', methods=['POST'])
def shutdown():
    logger.info("Entering shutdown...")

    try:
        subprocess.Popen('poweroff -d -f -i', shell=True)
        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/reboot', methods=['POST'])
def reboot():
    logger.info("Entering reboot...")

    try:
        subprocess.Popen('reboot -d -f -i', shell=True)
        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


##########################################################
#
# Time Related Logic
#
##########################################################
#@app.route('/api/time/get', methods=['GET'])
def get_time():
    logger.info("Entering get_time...")

    try:
        date   = datetime.now()
        year   = date.year
        month  = date.month
        day    = date.day
        hour   = date.hour
        minute = date.minute
        second = date.second
        tinfo = {"year":year, "month":month, "day":day, "hour":hour, "minute":minute, "second":second}

        logger.info(tinfo)
        return json.dumps({'code':'True', 'message':tinfo})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/time/set', methods=['POST'])
def set_time():
    logger.info("Entering set_time...")
    year   = request.form.get('year')
    month  = request.form.get('month')
    day    = request.form.get('day')
    hour   = request.form.get('hour')
    minute = request.form.get('minute')
    second = request.form.get('second')
    logger.info("year:%s, month:%s, day:%s, hour:%s, minute:%s, second:%s" % (year, month, day, hour, minute, second))

    try :
        command = 'date -s "%s-%s-%s %s:%s:%s"' % (year, month, day, hour, minute, second)
        p = subprocess.Popen(command, shell=True)	#这里如何查看命令执行结果(aoqingy)
        p.communicate()

        command = 'hwclock -w'
        p = subprocess.Popen(command, shell=True)
        p.communicate()

        command = 'date +%%s | tee %s/LAST_TIME' % COUNTER_DIR
        p = subprocess.Popen(command, shell=True)
        p.communicate()

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/password/set', methods=['POST'])
def set_password():
    logger.info("Entering set_password...")
    password = request.form.get('password1', '')

    try:
        clearPassword()
        if password:
            setPassword(password)
            os.popen('x11vnc -storepasswd %s /etc/x11vnc.pass' % password)
            os.popen('/var/www/vfd/script/vnc_server.sh -rfbauth /etc/x11vnc.pass &')
        else:
            os.popen('/var/www/vfd/script/vnc_server.sh &')

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


##########################################################
#
# Wakeup Logic (To wakup another terminal, not self)
#
##########################################################
def wakeupAnotherTerminal(mac, rvs):
    try:
        command = 'wakeonlan %s' % mac
        p = subprocess.Popen(command, shell=True)
        p.communicate()
    except Exception, e:
        rv = {}
        rv['mac']    = mac
        rv['reason'] = str(e)
        rvs.append(rv)

#@app.route('/api/wakeup', methods=['POST'])
def wakeup():
    logger.info("Entering wakeup...")
    macs = request.form.get('macs')
    logger.info("macs: %s" % macs)

    try:
        rvs = []
        threads = []
        for mac in macs.split(','):
            thread = Thread(target=wakeupAnotherTerminal, args=(mac, rvs))
            threads.append(thread)

        for thread in threads:
            thread.setDaemon(True)
            thread.start()

        for thread in threads:
            thread.join()

        logger.info(rvs)
        return json.dumps({'code':'True', 'message':rvs})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


##########################################################
#
# Picture Related Logic
#
##########################################################
#@app.route('/bootpng/change', methods=['POST'])
def change_bootpng():
    logger.info("Entering change_bootpng...")
    try:
        f = request.files['filename']
        f.save(UBUNTU_LOGO_FILE)
        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/lockjpg/change', methods=['POST'])
def change_lockjpg():
    logger.info("Entering change_lockjpg...")
    try:
        f = request.files['filename']
        f.save("%s/static/img/bg-class-lock.jpg" % BASE_DIR)
        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


##########################################################
#
# Upgrade System
#
##########################################################
def do_upgrade(ufile):
    os.popen('mkdir -p /tmp/update')
    os.popen('rm -rf /tmp/update/*')

    #解压
    os.popen('tar xf %s -C /tmp/update/' % ufile)
    logger.info("Update file uncompressed!")

    #检查哈希值文件
    if not os.path.exists("/tmp/update/MD5SUM"):
        return 1

    #读取MD5，与计算的MD5进行比较
    ufiles = []
    with open("/tmp/update/MD5SUM") as f:
        line = f.readline().split(' ')
        if not os.path.exists("/tmp/update/%s" % line[2].strip()):
            return 1
        #计算哈希值
        md5 = hashlib.md5()
        f2 = open("/tmp/update/" + line[2].strip())
        for line2 in f2:
            md5.update(line2)
        f2.close()
        #比较
        if not line[0].strip() == md5.hexdigest():
            return 2
        ufiles.append(line[2].strip())
    logger.info("MD5 verified!")

    #比较升级版本号
    for item in os.listdir('/tmp/update'):
        rv = re.search('(?P<update_file>update_[0-9\.]*)', os.path.join('/tmp/update', item))
        if rv:
            uversion = rv.group('update_file').split('_')[1]

    command = "apt-cache show vfd | awk '/Version/{print $2}'"
    p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE)
    out, err = p.communicate()
    cversion = out.strip('\n')

    uvsegs = uversion.split('.')
    cvsegs = cversion.split('.')

    umajor = int(uvsegs[0])
    uminor = int(uvsegs[1])
    ubuild = int(uvsegs[2])
    cmajor = int(cvsegs[0])
    cminor = int(cvsegs[1])
    cbuild = int(cvsegs[2])

    if (umajor < cmajor) or (umajor == cmajor and uminor < cminor) or (umajor == cmajor and uminor == cminor and ubuild < cbuild):
        return 3
    logger.info("Version confirmed!")

    #执行升级
    os.chdir('/tmp/update')
    command = 'dd if=%s | tar zxf -' % ufiles[0]
    p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE)
    out, err = p.communicate()
    if not p.returncode == 0 :
        return 4

    command = 'bash /tmp/update/update/update.sh'
    p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE)
    out, err = p.communicate()
    if not p.returncode == 0 :
        return 4

    return 0


#@app.route('/api/upgrade/network', methods=['POST'])
def upgrade_via_network():
    logger.info("Entering upgrade_via_network...")

    try:
        f = request.files['filename']
        if not re.match('update_[0-9\.]*.tgz', f.filename):
            raise Exception("Upload filename incorrect!")
        f.save("/tmp/%s" % f.filename)

        rv = do_upgrade("/tmp/%s" % f.filename)

        if rv == 1:
            raise Exception("Upload file is incompletable!")
        elif rv == 2:
            raise Exception("Upload file is incorrect!")
        elif rv == 3:
            raise Exception("Upload file is out of date!")
        elif rv == 4:
            raise Exception("Update error!")

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#在指定目录下查找update_[0-9\.]*.tgz类型的文件，返回版本号最大的那个文件
def findUpdateFile(dpath):
    rmajor = None
    rminor = None
    rbuild = None
    rufile = None

    for ufile in glob.glob('%s/update_[0-9\.]*.tgz' % dpath):
        version = os.path.basename(ufile)[7:-4].split('.')

        try:
            major = int(version[0])
            minor = int(version[1])
            build = int(version[2])
        except:
            continue

        if not rufile or major > rmajor or (major == rmajor and minor > rminor) or (major == rmajor and minor > rminor and build > rbuild):
            rmajor = major
            rminor = minor
            rbuild = build
            rufile = ufile

    return rufile


#@app.route('/api/upgrade/usb')
def upgrade_via_usb():
    logger.info("Entering upgrade_via_usb...")
    try:
        devices = find_usb_devices()
        if len(devices) == 0:
            raise Exception("No USB device found!")

        dpath = tempfile.mkdtemp(dir='/mnt')

        for device in devices:
            command = 'mount /dev/%s %s' % (device, dpath)
            p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            p.communicate()
            if p.returncode != 0:
                continue

            ufile = findUpdateFile(dpath)
            if not ufile:
                command = 'umount %s' % dpath
                p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                p.communicate()
                continue

            rv = do_upgrade(ufile)

            command = 'umount %s' % dpath
            p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            p.communicate()

            if not rv:
                break

        shutil.rmtree(dpath)

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


##########################################################
#
# Upload License
#
##########################################################
#@app.route('/api/license/network', methods=['POST'])
def license_via_network():
    logger.info("Entering license_via_network...")
    module = request.form.get('module')
    logger.info("module: %s" % module)

    try:
        if module:
            fname = "license-%s.txt" % module
        else:
            fname = "license.txt"

        f = request.files['filename']
        f.save('/tmp/%s' % fname)

        verify_license('/tmp/%s' % fname, module)

        command = 'cp -f /tmp/%s %s/.' % (fname, COUNTER_DIR)
        p = subprocess.Popen(command, shell=True)
        p.communicate()

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/license/usb', methods=['POST'])
def license_via_usb():
    logger.info("Entering license_via_usb...")
    module = request.form.get('module')
    logger.info("module: %s" % module)

    try:
        devices = find_usb_devices()
        if len(devices) == 0:
            raise Exception("No USB device found!")

        if module:
            fname = "license-%s.txt" % module
        else:
            fname = "license.txt"

        dpath = tempfile.mkdtemp(dir='/mnt')

        flag = 0
        for device in devices:
            command = 'mount /dev/%s %s' % (device, dpath)
            p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            p.communicate()
            if p.returncode != 0:
                continue

            if not glob.glob('%s/%s' % (dpath, fname)):
                command = 'umount %s' % dpath
                p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                p.communicate()
                continue

            try:
                verify_license('%s/%s' % (dpath, fname), module)
            except Exception, e2:
                logger.warning(str(e2))
                command = 'umount %s' % dpath
                p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                p.communicate()
                continue

            command = 'cp -f %s/%s %s/.' % (dpath, fname, COUNTER_DIR)
            p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            p.communicate()

            command = 'umount %s' % dpath
            p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            p.communicate()

            flag = 1
            break

        shutil.rmtree(dpath)

        if flag == 0:
            raise Exception("No license found!")

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


##########################################################
#
# Download Log
#
##########################################################
def collect_log(filename):
    tar = tarfile.open(filename, "w:tar")
    if os.path.isdir(LOG_DIR):
        tar.add(LOG_DIR)
    tar.close()


def log_via_network():
    logger.info("Entering log_via_network...")

    try:
        logfile = "/tmp/vflog.tar"
        collect_log(logfile)
        logger.info('Done!')
        return send_file(logfile, mimetype=None, as_attachment=True)
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


def log_via_usb():
    logger.info("Entering log_via_usb...")

    try:
        devices = find_usb_devices()
        if len(devices) == 0:
            raise Exception("No USB device found!")

        dpath = tempfile.mkdtemp(dir='/mnt')

        for device in devices:
            command = 'mount /dev/%s %s' % (device, dpath)
            p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            p.communicate()
            if p.returncode != 0:
                continue

            collect_log("%s/vflog.tar" % dpath)

            command = 'umount %s' % dpath
            p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            p.communicate()
            break

        shutil.rmtree(dpath)

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


def isZipType(filename):
    src_file = open(filename,'rb')
    src_file.seek(0)
    decimal_number = struct.unpack_from("B"*2, src_file.read(2))
    src_file.close()
    magic_number = u"%x%x" % (decimal_number[0], decimal_number[1])
    if magic_number == "504b" or magic_number == "504B":
        return 1
    else:
        return 0


#@app.route('/api/certificate/upload/', methods=['POST'])
def certificate_upload():
    logger.info("Entering certificate_upload...")
    try:
        f = request.files['filename']
        f.save("/tmp/%s" % f.filename)
        if not isZipType('/tmp/%s' % f.filename):
            raise Exception("Upload file is incorrect!")
        os.popen('unzip -o /tmp/%s -d /opt/Citrix/ICAClient/keystore/cacerts/' % f.filename)
        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})

