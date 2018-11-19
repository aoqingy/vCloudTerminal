#!/usr/bin/python
#-*-coding:utf-8 -*-
import os
import re
import json
import math
import time
import hashlib
import subprocess
from threading import Thread
from werkzeug import secure_filename
from flask import request, make_response
#from flask.ext.babel import gettext as _
from const   import *
from virtapi import *
from utility import *


##########################################################
#
# Management DB Related Logic
#
##########################################################
def insert_mgmt(uuid, ip):
    sentense = 'insert into vfmgmt(uuid, ip) values("%s", "%s")' % (uuid, ip)
    db = connect_db()
    cur = db.cursor()
    cur.execute(sentense)
    cur.close()
    db.commit()
    db.close()


def remove_mgmt(uuid):
    sentense = 'delete from vfmgmt where uuid="%s"' % (uuid)
    db = connect_db()
    cur = db.cursor()
    cur.execute(sentense)
    cur.close()
    db.commit()
    db.close()


def update_mgmt(uuid, ip):
    sentense = 'update vfmgmt set ip="%s" where uuid="%s"' % (ip, uuid)
    db = connect_db()
    cur = db.cursor()
    cur.execute(sentense)
    cur.close()
    db.commit()
    db.close()


def clear_mgmt():
    sentense = 'delete from vfmgmt'
    db = connect_db()
    cur = db.cursor()
    cur.execute(sentense)
    cur.close()
    db.commit()
    db.close()


##########################################################
#
# Management Operation Related Logic
#
##########################################################
#
#终端扫描
#
def scanTerminal(ip, wtime):
    try:
        logger.info("%s: %s" % (ip, wtime))
        time.sleep(wtime)
        url = "http://%s/api/identify" % ip	#规范后的API
        response = sendRequest(url=url, method="POST")
        logger.info('Response from %s: %s' % (ip, response))
        uuid = response['message']['uuid']
        logger.info("Found: %s(%s)" % (uuid, ip))

        rv = query_db('select * from vfmgmt where uuid="%s"' % uuid)
        if not rv:
            insert_mgmt(uuid, ip)
        else:
            update_mgmt(uuid, ip)
    except Exception, e:
        logger.error("%s: %s" % (ip, str(e)))


#@app.route('/terminal/scan', methods=['POST'])
def scan_terminals():
    logger.info("Entering scan_terminal...")
    ipstart = request.form.get('ipstart', '')
    ipend   = request.form.get('ipend',   '')
    logger.info("ipstart:%s, ipend:%s" % (ipstart, ipend))

    try:
        if not ipstart or not check_ip(ipstart):
            raise Exception('IP address invalid!')
        if ipend and not check_ip(ipend):
            raise Exception('IP address invalid!')

        if not ipend:
            scanTerminal(ipstart, 0)
        else:
            ipsseg = ipstart.split('.')             #起始IP分段
            ipeseg = ipend.split('.')               #结束IP分段
            if ipsseg[0] != ipeseg[0] or ipsseg[1] != ipeseg[1]:
                raise Exception('IP range invlid!')
            if int(ipsseg[2]) > int(ipeseg[2]) or (int(ipsseg[2]) == int(ipeseg[2]) and int(ipsseg[3]) > int(ipeseg[3])):
                raise Exception('IP range invlid!')
            count = 0
            wtime = 0
            threads = []
            for ipseg0 in xrange(int(ipsseg[0]), int(ipeseg[0]) + 1):
                for ipseg1 in xrange(int(ipsseg[1]), int(ipeseg[1]) + 1):
                    for ipseg2 in xrange(int(ipsseg[2]), int(ipeseg[2]) + 1):
                        for ipseg3 in xrange(int(ipsseg[3]), int(ipeseg[3]) + 1):
                            ip = str(ipseg0)+'.'+str(ipseg1)+'.'+str(ipseg2)+'.'+str(ipseg3)
                            #以下算法确保至多64个请求同时执行
                            if count == 64:
                                count = 0
                                wtime += 0.1
                            count = count+1
                            thread = Thread(target=scanTerminal, args=(ip, wtime))
                            threads.append(thread)
            for thread in threads:
                thread.setDaemon(True)
                thread.start()
            for thread in threads:
                thread.join()                       #等待扫描完成之后才返回

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#
#列显终端
#
def listTerminal(ip, uuid, rterminals):
    rterminal = {}

    try:
        url = "http://%s/api/system/info" % ip		#规范后的API
        response = sendRequest(url=url)
        logger.info('Response from %s: %s' % (ip, response))

        rterminal['ip']   = ip
        rterminal['uuid'] = uuid
        if uuid != response['message']['uuid']:
            rterminal['uuid'] += '/' + response['message']['uuid']
        rterminal['status'] = 'online'
        try:
            rterminal['status'] += '/' + response['message']['db_status']
        except:
            pass
        rterminal['uptime'] = response['message']['uptime']
    except Exception, e:
        rterminal['ip'] = ip
        rterminal['uuid'] = uuid
        rterminal['status'] = 'offline'
        rterminal['uptime'] = ''

    logger.info(rterminal)
    rterminals.append(rterminal)


#@app.route('/terminal/list', methods=['GET'])
def list_terminals():
    logger.info("Entering list_terminals...")
    page = request.args.get('page', '1')
    rows = request.args.get('rows', '100')
    sord = request.args.get('sord', 'asc')
    sidx = request.args.get('sidx', 'ip')
    logger.info("page:%s, rows:%s, sord:%s, sidx:%s" % (page, rows, sord, sidx))

    if os.path.isfile('%s/management.txt' % COUNTER_DIR):   # check management.txt
        #terminals = query_db('select distinct uuid,ip from vfmgmt order by %s %s' % (sidx, sord))
        terminals = query_db('select distinct uuid,ip from vfmgmt')
    else:
        terminals = []
    rterminals = []
    threads = []
    for terminal in terminals:
        thread = Thread(target=listTerminal, args=(terminal['ip'], terminal['uuid'], rterminals))
        threads.append(thread)

    for thread in threads:
        thread.setDaemon(True)
        thread.start()

    for thread in threads:
        thread.join()

    if sidx == 'uuid':
        if sord == 'desc':
            rterminals.sort(lambda x,y : cmp(y['uuid'], x['uuid']))
        else:
            rterminals.sort(lambda x,y : cmp(x['uuid'], y['uuid']))
    else:
        if sord == 'desc':
            rterminals.sort(lambda x,y : cmp(y['ip'], x['ip']))
        else:
            rterminals.sort(lambda x,y : cmp(x['ip'], y['ip']))

    logger.info(rterminals)
    records = len(rterminals)
    total = int(math.ceil(float(records)/float(rows)))
    return json.dumps({'page':page, 'records':records, 'total':total, 'rows':rterminals[(int(page)-1)*int(rows):int(page)*int(rows)]})


#
#获取终端信息
#
#@app.route('/terminal/info', methods=['GET'])
def get_terminal_info():
    logger.info("Entering get_terminal_info...")
    uuid = request.args.get('uuid')
    logger.info("uuid: %s" % uuid)

    try:
        terminal = query_db('select * from vfmgmt where uuid="%s"' % uuid, one=True)
        ip = terminal['ip']
        url = "http://%s/api/system/info" % ip	#规范后的API
        response = sendRequest(url=url)
        logger.info('Response from %s: %s' % (ip, response))
        return json.dumps({'code':response['code'], 'message':response['message']})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#
#删除终端
#
#@app.route('/terminal/remove', methods=['POST'])
def remove_terminals():
    logger.info("Entering remove_terminal...")
    uuids = request.form.get('uuids')
    logger.info("uuids: %s" % uuids)

    try:
        for uuid in uuids.split(','):
            remove_mgmt(uuid)

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#
#清除终端数据库
#
#@app.route('/terminal/clear', methods=['POST'])
def clear_terminals():
    logger.info("Entering clear_terminals...")

    try:
        clear_mgmt()

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#
#唤醒终端
#
def wakeupTerminal(uuid, rvs):
    try:
        subprocess.Popen('wakeonlan %s' % uuid, shell=True)
    except Exception, e:
        rv = {}
        rv['uuid']   = uuid
        rv['reason'] = str(e)
        rvs.append(rv)


#@app.route('/terminal/wakeup', methods=['POST'])
def wakeup_terminals():
    logger.info("Entering wakeup_terminal...")
    uuids = request.form.get('uuids')
    logger.info("uuids: %s" % uuids)

    try:
        rvs = []
        threads = []
        for uuid in uuids.split(','):
            thread = Thread(target=wakeupTerminal, args=(uuid, rvs))
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


#
#关闭终端
#
def shutdownTerminal(ip, uuid, rvs):
    try:
        url = "http://%s/api/shutdown" % ip		#规范后的API
        response = sendRequest(url=url, method='POST')
        logger.info('Response from %s: %s' % (ip, response))
    except Exception, e:
        rv = {}
        rv['ip']     = ip
        rv['uuid']    = uuid
        rv['reason'] = str(e)
        rvs.append(rv)


#@app.route('/terminal/shutdown', methods=['POST'])
def shutdown_terminals():
    logger.info("Entering shutdown_terminals...")
    uuids = request.form.get('uuids')
    logger.info("uuids: %s" % uuids)

    try:
        rvs = []
        threads = []
        for uuid in uuids.split(','):
            terminal = query_db('select * from vfmgmt where uuid="%s"' % uuid, one=True)
            thread = Thread(target=shutdownTerminal, args=(terminal['ip'], uuid, rvs))
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


#
#重启终端
#
def rebootTerminal(ip, uuid, rvs):
    try:
        url = "http://%s/api/reboot" % ip		#规范后的API
        response = sendRequest(url=url, method='POST')
        logger.info('Response from %s: %s' % (ip, response))
    except Exception, e:
        rv = {}
        rv['ip']     = ip
        rv['uuid']    = uuid
        rv['reason'] = str(e)
        rvs.append(rv)


#@app.route('/terminal/reboot', methods=['POST'])
def reboot_terminals():
    logger.info("Entering reboot_terminals...")
    uuids = request.form.get('uuids')
    logger.info("uuids: %s" % uuids)

    try:
        rvs = []
        threads = []
        for uuid in uuids.split(','):
            terminal = query_db('select * from vfmgmt where uuid="%s"' % uuid, one=True)
            thread = Thread(target=rebootTerminal, args=(terminal['ip'], uuid, rvs))
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


#@app.route('/terminal/uuids')
def terminal_uuids():
    logger.info("Entering terminal_uuids...")
    uuids = request.args.get('uuids')
    logger.info("uuids: %s" % uuids)

    uuids = uuids.replace(',', '\r\n')
    response = make_response(uuids)
    response.headers['Content-Type'] = 'text/plain'
    response.headers['Content-Disposition'] = 'attachment; filename=uuids.txt'
    return response


def updateTerminalLicense(filename, ip, uuid, rvs):
    try:
        logger.info("Sending update request to %s..." % ip)
        os.popen("curl -F filename=@%s http://%s/license/upload" % (filename, ip))
    except Exception, e:
        rv = {}
        rv['ip']     = ip
        rv['uuid']    = uuid
        rv['reason'] = str(e)
        rvs.append(rv)


def updateTerminalPackage(filename, ip, uuid, rvs):
    try:
        logger.info("Sending update request to %s..." % ip)
        os.popen("curl -F filename=@%s http://%s/api/update/network" % (filename, ip))
    except Exception, e:
        rv = {}
        rv['ip']     = ip
        rv['uuid']    = uuid
        rv['reason'] = str(e)
        rvs.append(rv)


#@app.route('/terminal/update', methods=['POST'])		#要重点测试啊(aoqingy)
def update_terminals():
    logger.info("Entering update_terminals...")
    function = request.form.get('function')
    uuids     = request.form.get('uuids')
    f        = request.files['filename']
    logger.info("function: %s, uuids: %s" % (function, uuids))

    try:
        os.popen('rm -rf /tmp/management/*')
        f = request.files['filename']
        f.save('/tmp/management/' + secure_filename(f.filename))
        os.chdir('/tmp/management/')

        if function == 'license':
            if not f.filename == "license.txt":
                raise Exception("Upload file is incorrect!")
            rvs = []
            threads = []
            for uuid in uuids.split(','):
                terminal = query_db('select * from vfmgmt where uuid="%s"' % uuid, one=True)
                thread = Thread(target=updateTerminalLicense, args=(request.files['filename'].filename, terminal['ip'], uuid, rvs))
                threads.append(thread)

            for thread in threads:
                thread.setDaemon(True)
                thread.start()

            for thread in threads:
                thread.join()

        elif function == 'package':
            #升级包文件名必须为update_###.tgz的格式
            if not re.match('update_[0-9\.]*.tgz', request.files['filename'].filename):
                raise Exception("Upload file is incorrect!")

            #解压升级包
            os.popen('mkdir -p /tmp/management/update')
            os.popen('rm -rf /tmp/management/update/*')
            os.popen('tar xf /tmp/management/%s -C /tmp/management/update/' % request.files['filename'].filename)
            logger.info("Update pacage uncompressed!")

            #读取MD5值，并与计算的MD5进行比较
            if not os.path.exists("/tmp/management/update/md5"):
                raise Exception("Upload file is incomplete!")
            f = open("/tmp/management/update/md5")
            lines = f.readlines()
            f.close()
            for ln in lines:
                fl = ln.split(" ")
                if not os.path.exists("/tmp/management/update/%s" % fl[2].strip()):
                    raise Exception("Upload file is incomplete!")
                file_path="/tmp/management/update/"+fl[2].strip()
                md5 = hashlib.md5()
                f = open(file_path)
                for line in f:
                    md5.update(line)
                f.close()
                if not fl[0].strip() == md5.hexdigest():
                    raise Exception("Upload file is incorrect!")
            logger.info("MD5 verified!")

            rvs = []
            threads = []
            for uuid in uuids.split(','):
                terminal = query_db('select * from vfmgmt where uuid="%s"' % uuid, one=True)
                thread = Thread(target=updateTerminalPackage, args=(request.files['filename'].filename, terminal['ip'], uuid, rvs))
                threads.append(thread)
    
            for thread in threads:
                thread.setDaemon(True)
                thread.start()
    
            for thread in threads:
                thread.join()
    
            logger.info(rvs)
            return json.dumps({'code':'True', 'message':rvs})
        else:
            raise Exception("Upload file is incorrect!")

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#
#设置时间
#
#@app.route('/terminal/time/get', methods=['GET'])
def get_terminal_time():
    logger.info("Entering get_terminal_time...")
    uuid = request.args.get('uuid', '')
    logger.info("uuid: %s" % uuid)

    try:
        terminal = query_db('select * from vfmgmt where uuid="%s"' % uuid, one=True)
        url = "http://%s/api/time/get" % terminal['ip']		#规范后的API
        response = sendRequest(url=url)
        logger.info('Response from %s: %s' % (terminal['ip'], response))
        return json.dumps({'code':response['code'], 'message':response['message']})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#
#设置时间
#
def setTerminalTime(year, month, day, hour, minute, second, ip, uuid, rvs):
    try:
        url = "http://%s/time/set" % ip
        data = {'year':year, 'month':month, 'day':day, 'hour':hour, 'minute':minute, 'second':second}
        response = sendRequest(url=url, method='POST', data=data)
        logger.info('Response from %s: %s' % (ip, response))
    except Exception, e:
        rv = {}
        rv['ip']     = ip
        rv['uuid']    = uuid
        rv['reason'] = str(e)
        rvs.append(rv)


#@app.route('/terminal/time/set', methods=['POST'])
def set_terminal_time():
    logger.info("Entering set_terminal_time...")
    uuids   = request.form.get('uuids')
    year   = request.form.get('year')
    month  = request.form.get('month')
    day    = request.form.get('day')
    hour   = request.form.get('hour')
    minute = request.form.get('minute')
    second = request.form.get('second')
    logger.info("year:%s, month:%s, day:%s, hour:%s, minute:%s, second:%s" % (year, month, day, hour, minute, second))

    try:
        rvs = []
        threads = []
        for uuid in uuids.split(','):
            terminal = query_db('select * from vfmgmt where uuid="%s"' % uuid, one=True)
            thread = Thread(target=setTerminalTime, args=(year, month, day, hour, minute, second, terminal['ip'], uuid, rvs))
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


#
#定位终端
#
def locateTerminal(ip, uuid, rvs):
    try:
        url = "http://%s/api/screen/lock" % ip		#规范后的API
        response = sendRequest(url=url)
        logger.info('Response from %s: %s' % (ip, response))

        time.sleep(3)

        url = "http://%s/api/screen/unlock" % ip	#规范后的API
        response = sendRequest(url=url)
        logger.info('Response from %s: %s' % (ip, response))
    except Exception, e:
        rv = {}
        rv['ip']     = ip
        rv['uuid']    = uuid
        rv['reason'] = str(e)
        rvs.append(rv)


#@app.route('/terminal/time/locate', methods=['GET'])
def locate_terminals(request):
    logger.info("Entering locate_terminals...")
    uuids = request.form.get("uuids", '')
    logger.info("uuids: %s" % uuids)

    try:
        rvs = []
        threads = []
        for uuid in uuids.split(','):
            terminal = query_db('select * from vfmgmt where uuid="%s"' % uuid, one=True)
            thread = Thread(target=locateTerminal, args=(terminal['ip'], uuid, rvs))
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


#@app.route('/management/upload', methods=['POST'])
def upload_management():
    logger.info("Entering upload_management...")

    try:
        f = request.files['filename']
        if not f.filename == "management.txt":
            raise Exception("Filename incorrect!")
        f.save("%s/management.txt" % COUNTER_DIR)

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/management/remove')
def remove_management():
    logger.info("Entering remove_management...")

    try:
        if os.path.isfile('%s/management.txt' % COUNTER_DIR):
            subprocess.Popen('rm -f %s/management.txt' % COUNTER_DIR, shell=True)
        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})

