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


#@app.route('/api/vncviewer/connect', methods=['POST'])
def connect_vncviewer():
    logger.info("Entering connect_vncviewer...")
    serverip = request.form.get('serverip', '')
    logger.info("serverip:%s" % serverip)

    try:
        command = '/bin/bash %s/vnc_viewer_start.sh %s &' % (SCRIPT_DIR, serverip)
        p = subprocess.Popen(command, shell=True)
        p.communicate()

        command = '/bin/bash %s/control_grab.sh &' % SCRIPT_DIR
        p = subprocess.Popen(command, shell=True)
        p.communicate()

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/vncviewer/disconnect', methods=['POST'])
def disconnect_vncviewer():
    logger.info("Entering disconnect_vncviewer...")

    try:
        command = '/bin/bash %s/control_release.sh' % SCRIPT_DIR
        p = subprocess.Popen(command, shell=True)
        p.communicate()

        command = '/bin/bash %s/vnc_viewer_stop.sh' % SCRIPT_DIR 
        p = subprocess.Popen(command, shell=True)
        p.communicate()

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/screen/snapshot', methods=['POST'])
def snapshot_screen():
    logger.info("Entering snapshot_screen...")

    try:
        #课堂监控入口(aoqingy)
        if not check_useable('terminal'):
            raise Exception('Terminal license not activiated.')

        sfile = "/tmp/screen.jpg"
        os.popen('/bin/bash %s/screen_snapshot.sh %s &' % (SCRIPT_DIR, sfile))

        logger.info('Done!')
        return send_file(sfile, mimetype=None, as_attachment=True)
    except Exception, e:
        logger.error(str(e))
        return make_response(jsonify({'error': str(e)}), 404)	#需要是字典吗(aoqingy)


#@app.route('/api/screen/lock', methods=['POST'])
def lock_screen():
    logger.info("Entering lock_screen...")

    try:
        command = '/bin/bash %s/screen_lock.sh %s/static/img/screen-default.jpg &' % (SCRIPT_DIR, BASE_DIR)
        p = subprocess.Popen(command, shell=True)
        p.communicate()

        command = '/bin/bash %s/control_grab.sh &' % SCRIPT_DIR
        p = subprocess.Popen(command, shell=True)
        p.communicate()

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/screen/unlock', methods=['POST'])
def unlock_screen():
    logger.info("Entering unlock_screen...")

    try:
        command = '/bin/bash %s/control_release.sh' % SCRIPT_DIR
        p = subprocess.Popen(command, shell=True)
        p.communicate()

        command = '/bin/bash %s/screen_unlock.sh' % SCRIPT_DIR
        p = subprocess.Popen(command, shell=True)
        p.communicate()

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


def lock_input():
    logger.info("Entering lock_input...")

    try:
        os.popen('/bin/bash %s/control_grab.sh &' % SCRIPT_DIR)
        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/input/unlock', methods=['POST'])
def unlock_input():
    logger.info("Entering unlock_input...")
    try:
        os.popen('%s/control_release.sh' % SCRIPT_DIR)
        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/camera/push', methods=['POST'])
def push_camera():
    logger.info("Entering push_camera...")
    url = request.form.get('url', '')
    sdp = request.form.get('sdp', '')
    logger.info("url: %s" % url)

    try:
        command = '/bin/bash %s/camera_push.sh "%s" "%s" &' % (SCRIPT_DIR, url, sdp)
        p = subprocess.Popen(command, shell=True)
        p.communicate()

        command = '/bin/bash %s/control_grab.sh &' % SCRIPT_DIR
        p = subprocess.Popen(command, shell=True)
        p.communicate()

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/camera/stop', methods=['POST'])
def stop_camera():
    logger.info("Entering stop_camera...")

    try:
        command = '/bin/bash %s/control_release.sh' % SCRIPT_DIR
        p = subprocess.Popen(command, shell=True)
        p.communicate()

        command = "/bin/bash %s/camera_stop.sh" % SCRIPT_DIR
        p = subprocess.Popen(command, shell=True)
        p.communicate()

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/media/play', methods=['POST'])
def play_media():
    logger.info("Entering play_media...")
    url = request.form.get('url', '')
    offset = request.form.get('offset', '')
    logger.info("url: %s" % url)

    try:
        command = '/bin/bash %s/media_play.sh "%s" "%s" &' % (SCRIPT_DIR, url, offset)
        p = subprocess.Popen(command, shell=True)
        p.communicate()

        command = '/bin/bash %s/control_grab.sh &' % SCRIPT_DIR
        p = subprocess.Popen(command, shell=True)
        p.communicate()

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/media/stop', methods=['POST'])
def stop_media():
    logger.info("Entering stop_media...")

    try:
        command = '/bin/bash %s/control_release.sh' % SCRIPT_DIR
        p = subprocess.Popen(command, shell=True)
        p.communicate()

        command = '/bin/bash %s/media_stop.sh' % SCRIPT_DIR
        p = subprocess.Popen(command, shell=True)
        p.communicate()

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


def pause_media():
    logger.info("Entering pause_media...")
    try:
        command = '/bin/bash %s/media_pause.sh' % SCRIPT_DIR
        p = subprocess.Popen(command, shell=True)
        p.communicate()

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


def resume_media():
    logger.info("Entering resume_media...")
    try:
        command = '/bin/bash %s/media_resume.sh' % SCRIPT_DIR
        p = subprocess.Popen(command, shell=True)
        p.communicate()

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


def start_record():
    logger.info("Entering start_record...")
    try:
        command = '/bin/bash %s/record_start.sh &' % SCRIPT_DIR
        p = subprocess.Popen(command, shell=True)
        p.communicate()

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


def stop_record():
    logger.info("Entering stop_record...")
    try:
        command = '/bin/bash %s/stop_record.sh' % SCRIPT_DIR
        p = subprocess.Popen(command, shell=True)
        p.communicate()

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/file', methods=['POST'])
def file_():
    logger.info("Entering file_...")

    try:
        f = request.files['filename']
        f.save("/root/%s" % f.filename)
        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/message/start', methods=['POST'])
def start_message():
    logger.info("Entering start_message...")

    try:
        f = request.files['filename']
        f.save("/tmp/%s" % f.filename)

        command = '/bin/bash %s/screen_lock.sh /tmp/%s &' % (SCRIPT_DIR, f.filename)
        p = subprocess.Popen(command, shell=True)
        p.communicate()

        command = '/bin/bash %s/control_grab.sh &' % SCRIPT_DIR
        p = subprocess.Popen(command, shell=True)
        p.communicate()

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/message/stop', methods=['POST'])
def stop_message():
    logger.info("Entering stop_message...")
    try:
        command = '/bin/bash %s/control_release.sh' % SCRIPT_DIR
        p = subprocess.Popen(command, shell=True)
        p.communicate()

        command = '/bin/bash %s/screen_unlock.sh' % SCRIPT_DIR
        p = subprocess.Popen(command, shell=True)
        p.communicate()

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


