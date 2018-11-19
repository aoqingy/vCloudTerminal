#!/usr/bin/python
#-*-coding:utf-8 -*-
import os
import re
import json
import glob
import struct
import socket
import shutil
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
from blutils import *


#@app.route('/api/terminal/bflist', methods=['GET'])
def list_bcdfile():
    logger.info("Entering list_bcdfile...")
    partition = request.args.get('partition', '')
    logger.info('partition:%s' % partition)

    try:
        dpath = tempfile.mkdtemp(dir='/mnt')

        command = "mount /dev/%s %s" % (partition, dpath)
        p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        p.communicate()
        if p.returncode != 0:
            raise Exception('Mount failed!') 

        bcdfile = [f for f in os.listdir('%s/Boot/' % dpath) if f.startswith('BCD.') and len(f)==40]

        command = "umount %s" % dpath
        p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        p.communicate()

        shutil.rmtree(dpath)

        logger.info(bcdfile)
        return json.dumps({'code':'True', 'message':bcdfile})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/terminal/bfupload', methods=['POST'])
#上传的文件名为BCD.########-####-####-####-############，直接保存在指定分区下
def upload_bcdfile():
    logger.info("Entering upload_bcdfile...")
    partition = request.form.get('partition', '')
    logger.info('partition:%s' % partition)

    try:
        f = request.files['filename']
        filename = secure_filename(f.filename)
        f.save("/tmp/%s" % filename)

        dpath = tempfile.mkdtemp(dir='/mnt')

        command = "mount /dev/%s %s" % (partition, dpath)
        p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        p.communicate()
        if p.returncode != 0:
            raise Exception('Mount failed!')

        found = False
        for loader in list_loader('%s/Boot/BCD' % dpath):
            if filename == 'BCD.%s' % loader['uuid']:
                found = True
                break

        if found == True:
            command = "mv /tmp/%s %s/Boot/%s" % (filename, dpath, filename)
            p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            p.communicate()

        command = "umount %s" % dpath
        p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        p.communicate()

        shutil.rmtree(dpath)

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/terminal/blist', methods=['GET'])
def list_bootloader():
    logger.info("Entering list_bootloader...")
    partition = request.args.get('partition',  '')
    logger.info('partition: %s' % partition)

    try:
        dpath = tempfile.mkdtemp(dir='/mnt')

        command = "mount /dev/%s %s" % (partition, dpath)
        p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        p.communicate()
        if p.returncode != 0:
            raise Exception('Mount failed!')

        rloader = list_loader('%s/Boot/BCD' % dpath)

        command = "umount %s" % dpath
        p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        p.communicate()

        shutil.rmtree(dpath)

        logger.info(rloader)
        return json.dumps({'code':'True', 'message':rloader})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/terminal/bchange', methods=['POST'])
def change_bootloader():
    logger.info("Entering change_bootloader...")
    partition = request.form.get('partition')
    uuid = request.form.get('uuid')
    logger.info('partition: %s, uuid: %s' % (partition, uuid))
    try:
        #引导切换入口(aoqingy)
        if not check_useable('terminal'):
            raise Exception('Terminal license not activiated!')

        dpath = tempfile.mkdtemp(dir='/mnt')

        #挂载分区并备份BCD文件
        command = "mount /dev/%s %s" % (partition, dpath)
        p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        p.communicate()
        if p.returncode != 0:
            raise Exception('Mount failed!')

        #修改BCD文件
        if os.path.exists("%s/Boot/BCD.%s" % (dpath, uuid)):
            command = "cp -f %s/Boot/BCD %s/Boot/BCD.virtfan" % (dpath, dpath)
            p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            p.communicate()

            command = "cp -f %s/Boot/BCD.%s %s/Boot/BCD" % (dpath, uuid, dpath)
            p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            p.communicate()
        #else:
        #    change_default('%s/Boot/BCD' % dpath, '{%s}' % uuid)

        #卸载分区
        command = "umount %s" % dpath
        p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        p.communicate()

        shutil.rmtree(dpath)

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})
