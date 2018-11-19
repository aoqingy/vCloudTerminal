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


#@app.route('/api/permit/check', methods=['GET'])
def check_permit():
    logger.info("Entering check_permit...")

    try:
        rv = query_db('select passwd from vfpswd where id="1"')
        if rv:
            rstatus = "true"
        else:
            rstatus = "false"
        logger.info(rstatus)
        return json.dumps({'code':'True', 'message':rstatus})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/permit/verify', methods=['POST'])
def verify_permit():
    logger.info("Entering verify_permit...")
    password = request.form.get('password', '')

    try:
        rv = query_db('select passwd from vfpswd where id="1"')
        if rv[0]['passwd'] == password:
            rstatus = "true"
        else:
            rstatus = "false"
        logger.info(rstatus)
        return json.dumps({'code':'True', 'message':rstatus})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})

