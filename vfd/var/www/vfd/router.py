#!/usr/bin/python
#-*-coding:utf-8 -*-
import os
from flask import request, render_template, url_for, session, redirect
#from flask.ext.babel import gettext as _
from const   import *
from utility import *

##########################################################
#
# URL Related Logic - Login & Logout
#
##########################################################
#@app.route('/login', methods=['POST'])
def login():
    logger.info("Entering login...")

    rv = query_db('select * from vfpswd where passwd = "%s"' % request.form['password'])
    if rv:
        session['password'] = request.form['password']
        return render_template("system.html")
    else:
        return redirect(url_for('index'))


#@app.route('/logout', methods=['GET'])
def logout():
    logger.info("Entering logout...")

    session.pop('password', None)
    return redirect(url_for('index'))


#@app.route('/', methods=['GET'])
def index():
    logger.info("Entering index...")
    #wherefrom = request.args.get('wherefrom', '')

    #rv = query_db('select * from vfpswd')
    #if not rv or 'password' in session:
    #    return render_template('index.html', var1=wherefrom)
    #else:
    #    return render_template('login.html')
    return render_template('index.html')


#@app.route('/setting', methods=['GET'])
def setting():
    logger.info("Entering setting...")
    #rv = query_db('select passwd from vfpswd where id="1"')
    #if not rv or ('password' in session and rv[0]['passwd'] == session["password"]):
    #    return render_template('system.html')
    #else:
    #    return render_template('login.html')
    return render_template('system.html')


#@app.route('/p2p', methods=['GET'])
def p2p():
    logger.info("Entering p2p...")
    uuid = info_uuid()
    logger.info(uuid)
    return render_template('p2p.html', uuid=uuid)


#@app.route('/management', methods=['GET'])
def management():
    logger.info("Entering management...")
    return render_template('management.html')


#@app.route('/rdp', methods=['GET'])
def rdp():
    logger.info("Entering rdp...")
    serverip = request.args.get('serverip', '')
    username = request.args.get('username', '')
    password = request.args.get('password', '')
    domain   = request.args.get('domain',   '')
    return render_template('rdp.html', serverip=serverip, username=username, password=password)


#@app.route('/spice', methods=['GET'])
def spice():
    logger.info("Entering spice...")
    serverip = request.args.get('serverip', '')
    username = request.args.get('username', '')
    password = request.args.get('password', '')
    domain   = request.args.get('domain',   '')
    return render_template('spice.html', serverip=serverip, username=username, password=password)


#@app.route('/desktop', methods=['GET'])
def desktop():
    logger.info("Entering desktop...")
    serverip = request.args.get('serverip', '')
    username = request.args.get('username', '')
    password = request.args.get('password', '')
    domain   = request.args.get('domain',   '')
    conntype = request.args.get('conntype', '')
    return render_template('desktop.html', serverip=serverip, username=username, password=password, domain=domain, conntype=conntype)

