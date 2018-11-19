#!/usr/bin/python
#-*-coding:utf-8 -*-
import os
import re
import json
import time
import shutil
import subprocess
from flask import Flask, request
#from flask.ext.babel import gettext as _
from werkzeug import secure_filename
from threading import Thread
from const   import *
from virtapi import *
from sshapi  import *
from utility import *

from task    import CheckFileSize
import celery


#@app.route('/api/file/list', methods=['GET'])
def list_files():
    logger.info("Entering list_files...")
    path = request.args.get('path',  '')
    logger.info('path: %s' % path)

    try:
        rfiles = []
        for _file in os.listdir(path):
            rfile = {}
            rfile['name']  = os.path.basename(_file)
            rfile['path']  = os.path.join(path, _file)
            rfile['size']  = os.path.getsize(os.path.join(path, _file))
            rfile['ctime'] = os.path.getctime(os.path.join(path, _file))
            rfiles.append(rfile)
        logger.info(rfiles)
        return json.dumps({'code':'True', 'message':rfiles})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/file/mremove', methods=['POST'])
def remove_files():
    logger.info("Entering remove_files...")
    files = request.form.get('files',  '')
    logger.info('files: %s' % files)

    try:
        for _file in files.split(','):
            try:
                if os.path.exists(_file):
                    os.popen('rm -f %s' % _file)
            except:
                pass

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/file/rename', methods=['POST'])
def rename_file():
    logger.info("Entering rename_file...")
    _file = request.form.get('file',  '')
    fname = request.form.get('fname', '')
    logger.info('file: %s, fname: %s' % (_file, fname))

    try:
        if os.path.exists(_file):
            dname = os.path.dirname(_file)
            os.rename(_file, os.path(dname, fname))

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#####################################################################
#
# 获取文件下载状态
#
#####################################################################
#@app.route('/api/file/status', methods=['GET'])
def status_file():
    logger.info("Entering status_file...")
    tid = request.args.get('task_id')
    logger.info('tid: %s' % tid)

    try:
        if tid:
            task = CheckFileSize.AsyncResult(tid)
            data = task.result or task.state
        else:
            raise Exception('No task id given!')

        logger.info(data)
        return json.dumps({'code':'True', 'message':data})
    except Exception, e:
        print str(e)
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/file/check/stop', methods=['POST'])
def stop_check_file():
    logger.info("Entering stop_check_file...")
    tid = request.form.get('task_id')
    logger.info('tid: %s' % tid)

    try:
        task = CheckFileSize.AsyncResult(tid)
        task.revoke(terminate=True, signal='SIGKILL')
        logger.info("Done!")
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#####################################################################
#
# 直接拷贝文件
#
#####################################################################
#@app.route('/api/file/copy', methods=['POST'])
def __copyFile(sfile, dfile):
    if os.path.exists(dfile):
        os.popen('rm -f %s' % dfile)
    command = "cp %s %s" % (sfile, dfile)
    subprocess.Popen(command, shell=True)


def copy_file():
    logger.info("Entering copy_file...")
    sfile = request.form.get('sfile', '')
    dpath = request.form.get('dpath', '')
    logger.info('sfile: %s, dpath: %s' % (sfile, dpath))

    try:
        dfile = os.path.join(dpath, os.path.basename(sfile))
        thread = Thread(target=__copyFile, args=(sfile, dfile))
        thread.setDaemon(True)
        thread.start()

        dsize = os.stat(sfile).st_size
        job = CheckFileSize.delay(dfile, dsize)
        data = job.id

        logger.info(data)
        return json.dumps({'code':'True', 'message':data})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#####################################################################
#
# 通过SSH下载文件
#
#####################################################################
def __downloadFile(sipaddr, spassword, sshport, sfile, dfile):
    try:
        if os.path.exists(dfile):
            os.popen('rm -f %s' % dfile)
        ssh = SSHConnection(sipaddr, 'root', spassword, int(sshport))
        sf = ssh.open(sfile, 'rb')	#如果直接调用ssh.get无法下载超大文件
        with open(dfile, 'wb') as df:
            shutil.copyfileobj(sf, df)
        ssh.close()
    except Exception, e:
        logger.error(str(e))


#@app.route('/api/file/download/start', methods=['POST'])
def download_file():
    logger.info("Entering download_file...")
    sipaddr   = request.form.get('sipaddr',   '')
    spassword = request.form.get('spassword', '')
    sshport   = request.form.get('sshport',   '')
    sfile     = request.form.get('sfile',     '')
    logger.info('sipaddr: %s, sshport: %s, sfile: %s' % (sipaddr, sshport, sfile))

    try:
        if not sshport:
            sshport = '22'

        dfile = os.path.join('/home/image', os.path.basename(sfile))
        thread = Thread(target=__downloadFile, args=(sipaddr, spassword, sshport, sfile, dfile))
        thread.setDaemon(True)
        thread.start()

        ssh = SSHConnection(sipaddr, 'root', spassword, int(sshport))
        dsize = ssh.stat(sfile).st_size
        ssh.close()

        job = CheckFileSize.delay(dfile, dsize)
        data = job.id

        logger.info(data)
        return json.dumps({'code':'True', 'message':data})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#####################################################################
#
# 通过BT下载文件
# 有两种方式获取TORRENT文件
# 1. 通过SSH下载
# 2. 通过CURL发送
#
#####################################################################
def __downloadWithBT(sipaddr, spassword, sshport, sfile, tfile, dfile):
    try:
        if os.path.exists(dfile):
            os.popen('rm -f %s' % dfile)
        ssh = SSHConnection(sipaddr, 'root', spassword, int(sshport))
        ssh.get(tfile, '/tmp/%s.torrent' % os.path.basename(sfile))
        ssh.close()

        os.popen('%s/btdownload.sh "/tmp/%s.torrent" "%s"' % (SCRIPT_DIR, os.path.basename(sfile), dfile))
    except Exception, e:
        logger.error(str(e))


#@app.route('/api/file/download/btstart', methods=['POST'])
def download_file_with_bt():
    logger.info("Entering download_file_with_bt...")
    sipaddr   = request.form.get('sipaddr',   '')
    spassword = request.form.get('spassword', '')
    sshport   = request.form.get('sshport',   '')
    sfile     = request.form.get('sfile',     '')
    tfile     = request.form.get('tfile',     '')
    logger.info('sipaddr: %s, sshport: %s, sfile: %s, tfile: %s' % (sipaddr, sshport, sfile, tfile))

    try:
        if not sshport:
            sshport = '22'

        dfile = os.path.join('/home/image', os.path.basename(sfile))
        thread = Thread(target=__downloadWithBT, args=(sipaddr, spassword, sshport, sfile, tfile, dfile))
        thread.setDaemon(True)
        thread.start()

        ssh = SSHConnection(sipaddr, 'root', spassword, int(sshport))
        dsize = ssh.stat(sfile).st_size
        ssh.close()

        job = CheckFileSize.delay(dfile, dsize)
        data = job.id

        logger.info(data)
        return json.dumps({'code':'True', 'message':data})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


def __downloadWithBTByCurl(sfile, tfile, dfile):
    try:
        if os.path.exists(dfile):
            os.popen('rm -f %s' % dfile)

        command = '%s/btdownload.sh "%s" "%s"' % (SCRIPT_DIR, tfile, dfile)
        logger.info(command)
        p = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
        out, err = p.communicate()
        logger.info(out)
        logger.info(err)
    except Exception, e:
        logger.error(str(e))


#@app.route('/api/file/download/bcstart', methods=['POST'])
def download_file_with_bt_by_curl():
    logger.info("Entering download_file_with_bt_by_curl...")

    try:
        tfile = request.files['filename']
        if not re.match('.*\.torrent', secure_filename(tfile.filename)):
            raise Exception("Invalid image file!")

        tfile.save("/tmp/" + secure_filename(tfile.filename))
        logger.info('Download torrent: %s ' % tfile.filename)

        sfile = '.'.join(tfile.filename.split('.')[0:-2])
        logger.info(sfile)
        dsize = tfile.filename.split('.')[-2]
        logger.info(dsize)
        #dsize = 0		#磁盘大小
        #for ln in os.popen('df -a /', 'r'):
        #    rv = re.search('^/dev\S+\s+\S+\s+\S+\s+(?P<disk_size>\S+)\s', ln)
        #    if rv:
        #        dsize = rv.group('disk_size')
        #        break

        #if (int(dsize)/1000-500) < (int(isize)/1024/1024):
        #    raise Exception("No enough capacity.")

        dfile = os.path.join('/home/image', sfile)
        thread = Thread(target=__downloadWithBTByCurl, args=(sfile, "/tmp/" + secure_filename(tfile.filename), dfile))
        thread.setDaemon(True)
        thread.start()

        job = CheckFileSize.delay(dfile, dsize)
        data = job.id

        logger.info(data)
        return json.dumps({'code':'True', 'message':data})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#####################################################################
#
# USB挂载与卸载
#
#####################################################################
def mount_usb():
    logger.info("Entering mount_usb...")
    dpath = request.form.get('dpath', '')
    logger.info('dpath: %s' % dpath)

    try:
        if not dpath:
            dpath = '/mnt/usb'

        devices = find_usb_devices()
        if len(devices) != 1:
            raise Exception("Only one USB device allowed!")

        #如果目录不存在，创建
        if not os.path.exists(dpath):
            command = 'mkdir -p %s' % dpath
            p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            out, err = p.communicate()
            if err:
                raise Exception("Fail to make directory %s" % dpath)

        #如果目录已挂载，卸载
        if os.path.ismount(dpath):
            command = 'umount %s' % dpath
            p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            out, err = p.communicate()
            if err:
                raise Exception("Fail to unmount directory %s" % dpath)

        command = 'mount /dev/%s %s' % (devices[0], dpath)
        p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        out, err = p.communicate()
        if err:
            raise Exception("Fail to mount directory %s" % dpath)

        time.sleep(3)

        logger.info("Done!")
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


def unmount_usb():
    logger.info("Entering unmount_usb...")
    dpath = request.form.get('dpath', '')
    logger.info('dpath: %s' % dpath)

    try:
        if not dpath:
            dpath = '/mnt/usb'

        if os.path.ismount(dpath):
            command = 'umount /mnt/usb'
            p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            out, err = p.communicate()
            if err:
                raise Exception("Fail to unmount directory %s" % dpath)

        logger.info("Done!")
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})

