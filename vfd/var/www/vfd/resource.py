#!/usr/bin/python
#-*-coding:utf-8 -*-
import json
import subprocess
from flask import request
#from flask.ext.babel import gettext as _
from const   import *
from utility import *


##########################################################
#
# Resource Related Logic
#
##########################################################
#@app.route('/api/resource/list', methods=['GET'])
def list_resources():
    logger.info("Entering list_resources...")

    try:
        rv = query_db('select * from vftb')
        logger.info(rv)
        return json.dumps({'code':'True', 'message':rv})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/resource/add', methods=['POST'])
def add_resource():
    logger.info("Entering add_resource...")
    rid      = request.form.get('id'      , '')
    product  = request.form.get('product' , '')
    nickname = request.form.get('nickname', '')
    serverip = request.form.get('serverip', '')
    username = request.form.get('username', '')
    password = request.form.get('password', '')
    domain   = request.form.get('domain'  , '')
    autolink = request.form.get('autolink', '')
    logger.info("rid:%s, product:%s, nickname:%s, serverip:%s, username:%s, password:%s, domain:%s, autolink:%s" % (rid, product, nickname, serverip, username, password, domain, autolink))

    try:
        if not product or not nickname or not serverip:
           raise Exception("Parameter invalid!")

        if rid:
            if autolink == '1':
                updateLink()
            updateResource(rid, product, nickname, serverip, username, password, domain, autolink)
        else:
            if autolink == '1':
                updateLink()
            rc = insertResource(product, nickname, serverip, username, password, domain, autolink)

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/resource/remove', methods=['POST'])
def remove_resource():
    logger.info("Entering remove_resource...")
    rid = request.form.get('id', '')
    logger.info("id: %s" % rid)

    try:
        #rv = query_db('select nickname from vftb where id = "%s"' % rid)
        deleteResource(rid)
        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/resource/clear', methods=['POST'])
def clear_resources():
    logger.info("Entering clear_resources...")

    try:
        clearResource()
        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/resource/refresh', methods=['POST'])
def refresh_resources():
    logger.info("Entering refresh_resources...")

    try:
        subprocess.Popen('%s/refresh.sh' % SCRIPT_DIR, shell=True)
        #os.popen('xdotool key F5')
        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/resource/enable', methods=['POST'])
def enable_resource():
    logger.info("Entering enable_resource...")

    try:
        subprocess.Popen('chattr -i %s' % DB_FILE, shell=True)
        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/resource/disable', methods=['POST'])
def disable_resource():
    logger.info("Entering disable_resource...")

    try:
        subprocess.Popen('chattr +i %s' % DB_FILE, shell=True)	#设置成只读也无法禁止写入数据？(aoqingy)
        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})
