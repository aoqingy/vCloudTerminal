#!/usr/bin/python
#-*-coding:utf-8 -*-
#from flask import Flask
#from flask.ext.babel import Babel, gettext as _
import subprocess
import tempfile
import logging
import sqlite3
import urllib
import urllib2
import hashlib
import glob
import json
import uuid
import time
import sys
import re
import os
from datetime import datetime
from M2Crypto.EVP import Cipher
from base64 import b64encode, b64decode
from virtapi import *
from const   import *

#app = Flask(__name__)


##########################################################
#
# Encryption/Decryption Related
#
##########################################################
def __cipher(msg, op):
    iv = "0123456789abcdeffedcba9876543210"
    passKey = "password4virtfannaftriv4drowssap"
    cipher = Cipher(alg='aes_128_cbc', key=passKey, iv=iv, op=op)
    v = cipher.update(msg)
    v = v + cipher.final()
    del cipher
    return v


def encrypt(msg):
    return b64encode(__cipher(msg, 1))


def decrypt(msg):
    return __cipher(b64decode(msg), 0)


def encrypt_to_file(msg, f):
    file(f, 'w').write(encrypt(msg))


def decrypt_from_file(f):
    return decrypt(file(f).read().strip())


##########################################################
#
# Utilities
#
##########################################################
def check_ip(ip):
    if re.match(r'^((\d{1,2}|1\d{2}|2[0-4]\d|25[0-5])\.){3}(\d{1,2}|1\d{2}|2[0-4]\d|25[0-5])$', ip):
        return True
    else:
        return False


def bin_convert(field):
    nm = bin(int(field))[2:]
    length = len(nm)
    lack = 8-length
    for i in range(lack):
        nm = "0"+nm
    return nm


def check_netmask(mask):
    ipseg = mask.split('.')
    if len(ipseg) != 4:
        return False
    netmask = bin_convert(ipseg[0]) + bin_convert(ipseg[1]) + bin_convert(ipseg[2]) + bin_convert(ipseg[3])
    if re.search('^1*0*$', netmask):
        return True
    else:
        return False


def find_usb_devices():
    # find all block
    blk = [x for x in os.listdir('/sys/class/block/') if re.search('sd[a-z]\d', x)]
    # find root block
    for line in os.popen('df /', 'r'):
        tmp = re.search('(?P<root>\S+)\s', line)
        if tmp:
            root = tmp.group('root')
    root = root.split('/')[2]
    root = filter(str.isalpha, root)
    # all block - root block
    usb = [x for x in blk if not re.search(root, x)]

    return usb


def get_installation_date():
    command = "passwd -S root | awk '{print $3}'"
    p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    itime = ''.join(p.stdout.readlines()).strip()
    return int(time.mktime(time.strptime(itime, '%m/%d/%Y')))


def get_current_date():
    return int(time.mktime(datetime.now().timetuple()))


##########################################################
#
# System Information Logic
#
##########################################################
#因为Windows下，MAC地址不能唯一标识云终端，所以采用BIOS标识符和硬盘系列号的哈希值
#此外，唤醒云终端需要真正的MAC地址，所以提供另外一个函数来获取并返回云终端MAC地址
#由于历史原因，前面一个函数命名为info_mac，后面一个函数命名为info_mac_real(aoqingy)
#将info_mac改名为info_uuid，将info_mac_real改名为info_mac(aoqingy)

#所有试用模式的安装日期都为当日，因此不可用于控制许可证。标识符只取BIOS UUID
#正常模式只能出现在U盘或者磁盘
#如果介质为U盘，则只取U盘的系列号为标识符；
#否则为和Windows保持一致，取BIOS标识符和引导磁盘系列号计算标识符。

def info_uuid():
    command = "dmidecode -t 1 | grep UUID: | awk '{ print $2 }'"
    p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    biosuuid = ''.join(p.stdout.readlines()).strip()

    command = "mount | grep \"on \/cdrom type nfs\" | wc -l"
    p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE)
    output, dummy = p.communicate()
    if output.strip() != '0':
        #网络启动取主板UUID和MAC地址
        node = uuid.getnode()
        macaddr = uuid.UUID(int = node).hex[-12:]
        macaddr = macaddr[0:2]+":"+macaddr[2:4]+":"+macaddr[4:6]+":"+macaddr[6:8]+":"+macaddr[8:10]+":"+macaddr[10:12]
        macaddr = macaddr.upper()

        m = hashlib.md5()
        m.update(biosuuid)
        m.update(macaddr)
        return m.hexdigest().upper()

    devname = ""
    command = "mount | grep \"on \/cdrom type vfat\""
    p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE)
    output, dummy = p.communicate()
    if output != "":
        devname = output.strip()[0:8]

    command = "mount | grep \"on \/ type ext4\""
    p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE)
    output, dummy = p.communicate()
    if output != "":
        devname = output.strip()[0:8]

    if devname:
        command = "udevadm info %s | grep \"ID_BUS=\"" % devname
        p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE)
        output, dummy = p.communicate()
        devtype = output.strip().split("=")[1]

        #硬盘也可以使用下面的方式获取序列号，而不需要使用以下命令：
        #hdparm -I %s 2>/dev/null | grep 'Serial Number:' | awk '{ print $3 }'
        devsn = ""
        command = "udevadm info %s | grep \"ID_SERIAL_SHORT=\"" % devname
        p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE)
        output, dummy = p.communicate()
        if output != "":
            devsn = output.strip().split("=")[1]

        if devtype == "usb":
            #U盘只取系列号，不取主板UUID，以便插在任何设备上都能识别（aoqingy）
            m = hashlib.md5()
            if devsn:
                m.update(devsn)
            else:
                m.update(biosuuid)
            return m.hexdigest().upper()
        else:                       #scsi or ata
            m = hashlib.md5()
            m.update(biosuuid)
            if devsn:
                m.update(devsn)
            return m.hexdigest().upper()

    #其他情况（例如光驱启动）都只取主板UUID
    #mount | grep \"on \/cdrom type iso9660\"
    m = hashlib.md5()
    m.update(biosuuid)
    return m.hexdigest().upper()


def info_mac():
    node = uuid.getnode()
    macaddr = uuid.UUID(int = node).hex[-12:]
    macaddr = macaddr[0:2]+":"+macaddr[2:4]+":"+macaddr[4:6]+":"+macaddr[6:8]+":"+macaddr[8:10]+":"+macaddr[10:12]
    macaddr = macaddr.upper()
    #for card in os.listdir('/sys/class/net'):
    #    if re.search('^(?=e)', card):
    #        f = open('/sys/class/net/%s/address' % card, 'r')
    #        mac = f.read().strip().upper()
    #        f.close()
    #        break
    return macaddr


def info_cpu():
    cpu_model = ''
    cpu_core  = ''
    f = open('/proc/cpuinfo', 'r')
    for ln in f.readlines():
        model = re.search('(?<=model name[\s]: ).+', ln)
        if model:
            cpu_model = model.group(0)
        model2 = re.search('(?<=Processor[\s]:).+', ln)
        if model2:
            cpu_model = model2.group(0).strip()
        core = re.search('(?<=processor[\s]: ).+', ln)
        if core:
            cpu_core = core.group(0)
    f.close()
    cpu_core = int(cpu_core)+1
    return cpu_model, cpu_core


def info_memory():
    mem_total = ''
    mem_free  = ''
    f = open('/proc/meminfo', 'r')
    for ln in f.readlines():
        total = re.search('(?<=MemTotal:).+(?<=\s)', ln)
        if total:
            mem_total = total.group(0).strip()
            mem_total = int(mem_total) / 1024
            mem_total = str(mem_total)+" MB"
        free = re.search('(?<=MemFree:).+(?<=\s)', ln)
        if free:
            mem_free = free.group(0).strip()
            mem_free = int(mem_free) / 1024
            mem_free = str(mem_free)+" MB"
    f.close()
    return mem_total, mem_free


def info_disk():
    disk = ''
    for ln in os.popen('df -ah /', 'r'):
        status = re.search('^/dev\S+\s+(?P<disk_size>\S+)\s', ln)
        if status:
            disk = status.group('disk_size')
            break
    return disk


def info_usb():
    temp = tempfile.NamedTemporaryFile()
    command = subprocess.Popen('lsusb -v >%s' % temp.name, shell=True, stdout=subprocess.PIPE)
    output, dummy = command.communicate()

    sns = []
    sn = ''
    sr = ''
    with open(temp.name, 'r') as f:
        for line in f.readlines():
            line = line.strip()
            if line.startswith('Device Descriptor:'):
                if sn != '' and sr == 'Mass Storage':
                    sns.append(sn)
                sn = ''
                sr = ''
            if line.startswith('iSerial'):
                sn = ' '.join(line.split()[2:])
            if line.startswith('bInterfaceClass'):
                sr = ' '.join(line.split()[2:])

    if sn != '' and sr == 'Mass Storage':
        sns.append(sn)

    return ','.join(sns)


def info_kernel():
    kernel = ''
    for ln in os.popen('uname -r', 'r'):
        status = re.search('.+', ln)
        if status:
            kernel = status.group(0)
            break
    return kernel


def info_vvfd():
    vfd_ver = open('%s/version' % COUNTER_DIR).read().strip('\n')
    #for ln in os.popen('dpkg -s vfd', 'r'):		#aoqingy
    #    status = re.search('(?<=Version: ).+', ln)
    #    if status:
    #        vfd_ver = status.group(0)
    #        break
    return vfd_ver


def info_viso():
    iso_ver = ''
    for ln in os.popen('cat /etc/os-release', 'r'):
        status = re.search('^VERSION="(?P<ver>.+)"', ln)
        if status:
            iso_ver = status.group('ver')
            break
    return iso_ver


#def info_vviewer():
#    viewer_ver = ''
#    for ln in os.popen('dpkg -s virt-viewer', 'r'):
#        status = re.search('(?<=Version: ).+', ln)
#        if status:
#            viewer_ver = status.group(0)
#            break
#    return viewer_ver


def info_uptime():
    uptime = {}
    f = open('/proc/uptime')
    con = f.read().split()
    f.close()
    all_sec = float(con[0])
    MINUTE,HOUR,DAY = 60,3600,86400
    uptime['day']    = int(all_sec / DAY)
    uptime['hour']   = int((all_sec % DAY) / HOUR)
    uptime['minute'] = int((all_sec % HOUR) / MINUTE)
    uptime['second'] = int(all_sec % MINUTE)
    return uptime


def info_db():
    action = subprocess.Popen("lsattr %s | grep '\-i\-'" % DB_FILE, shell=True, stdout=subprocess.PIPE)
    p = action.communicate()[0]
    rc = action.returncode
    if rc == 0:
        return "disabled"
    else:
        return "enabled"


def _media1():
    command = "cat /proc/cpuinfo | grep -i hypervisor | wc -l"
    p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE)
    output, dummy = p.communicate()
    if output.strip() == '0':
        return "Physical"
    else:
        return "Virtual"


def _media2():
    command = "mount | grep \"aufs on \/ type\" | wc -l"
    p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE)
    output, dummy = p.communicate()
    if output.strip() != '0':
        return "Trial"
    else:
        return "Installation"


def _media3():
    command = "mount | grep \"on \/cdrom type nfs\" | wc -l"
    p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE)
    output, dummy = p.communicate()
    if output.strip() != '0':
        return "Network"

    command = "mount | grep \"on \/cdrom type iso9660\" | wc -l"
    p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE)
    output, dummy = p.communicate()
    if output.strip() != '0':
        return "Cdrom"

    command = "mount | grep \"on \/cdrom type vfat\" | wc -l"
    p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE)
    output, dummy = p.communicate()
    if output.strip() != '0':
        return 'Usb'

    command = "mount | grep \"on \/ type ext4\""
    p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE)
    output, dummy = p.communicate()
    devname = output.strip()[0:8]
    command = "udevadm info %s | grep \"ID_BUS=\"" % devname
    p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE)
    output, dummy = p.communicate()
    devtype = output.strip().split("=")[1]
    if devtype == "usb":
        return "Usb"
    else:			#scsi or ata
        return "Disk"


def info_media():
    return _media1() + ',' + _media2() + ',' + _media3()


##########################################################
#
# License Related Logic
#
##########################################################
TRIAL_DAYS = 90

def lic_status():
    cdate = get_current_date()
    idate = get_installation_date()
    udays = (cdate - idate) / 86400

    rv = []
    for ufile in sorted(glob.glob('%s/license*.txt' % COUNTER_DIR)):
        module = os.path.basename(ufile)[7:-4]
        if module.startswith('-'):
            module = module[1:]

        lstatus, ldays = check_license(module)

        if lstatus == 'activated':
           vflag = 'activated'
        elif lstatus == 'invalid':
           vflag = 'invalid'
        else:
            if udays >= 0 and ldays > 0 and ldays >= udays:
                vflag = str(ldays - udays) + " day(s) left"
            else:
                vflag = str(udays - ldays) + " day(s) expired"

        rv.append(module + ": " + vflag if module else vflag)

    if rv:
        return '; '.join(sorted(rv))

    if udays <= TRIAL_DAYS:
        return "Trial: %s day(s) left" % str(TRIAL_DAYS - udays)
    else:
        return "Trial: %s day(s) expired" % str(udays - TRIAL_DAYS)


#在上传许可证时进行校验
def verify_license(fname, module=""):
    uuid = info_uuid()
    with open(fname, 'r') as f:
        for line in f.readlines():
            try:
                decrypted = decrypt(line.strip()).split(',')
                decrypted_uuid = decrypted[0]
                decrypted_days = decrypted[1]
                try:
                    decrypted_name = decrypted[2]
                except:
                    decrypted_name = ""
                if decrypted_uuid == uuid and decrypted_name == module:
                    if decrypted_days == "0":    #如果为0，表示已激活，返回最大整数值
                        return ('activated', sys.maxint)
                    else:
                        return ('valid', int(decrypted_days))
            except Exception, e2:
                logger.warning(str(e2))
    raise Exception("License invalid!")


#在使用时对许可证进行检查
def check_license(module=""):
    try:
        uuid = info_uuid()
        fname = 'license-%s.txt' % module if module else 'license.txt' 
        with open('%s/%s' % (COUNTER_DIR, fname), 'r') as f:
            for line in f.readlines():
                try:
                    decrypted = decrypt(line.strip()).split(',')
                    decrypted_uuid = decrypted[0]
                    decrypted_days = decrypted[1]
                    try:
                        decrypted_name = decrypted[2]
                    except:
                        decrypted_name = ""
                    if decrypted_uuid == uuid and decrypted_name == module:
                        if decrypted_days == "0":	#如果为0，表示已激活，返回最大整数值
                            return ('activated', sys.maxint) 
                        else:
                            return ('valid', int(decrypted_days))
                except Exception, e2:
                    logger.warning(str(e2))
        return ('valid', TRIAL_DAYS)
    except Exception, e:
        return ('valid', TRIAL_DAYS)


#许可证逻辑
def check_useable(module):
    cdate = get_current_date()
    idate = get_installation_date()

    udays = (cdate - idate) / 86400
    logger.info("Used days from installation: %s" % udays)

    lstatus, ldays = check_license()
    if lstatus == 'activated':
        logger.info("Software activated!")
        return 1

    if module:
        mstatus, mdays = check_license(module)
        if mstatus == 'activated':
            logger.info("Module %s activated!" % module.toupper())
            return 1
        ldays = max(ldays, mdays)

    if udays >= 0 and ldays > 0 and ldays >= udays:
        rv = 1
    else:
        rv = 0

    logger.info("License " + ("activated" if rv == 1 else "invalid") + "!")
    return rv


##########################################################
#
# Database Related Logic
#
##########################################################
def connect_db():
    rv = sqlite3.connect(DB_FILE)
    rv.row_factory = sqlite3.Row
    return rv


def init_db():
   db = connect_db()
   with app.open_resource(DB_SCRIPT, mode='r') as f:
       db.cursor().executescript(f.read())
   db.commit()


def query_db(query, args=(), one=False):
    db = connect_db()
    cur = db.execute(query, args)
    rv = [dict((cur.description[idx][0], value) for idx, value in enumerate(row)) for row in cur.fetchall()]
    cur.close()
    db.close()
    return (rv[0] if rv else None) if one else rv


def insertResource(product, nickname, serverip, username, password, domain, autolink):
    sentense = 'insert into vftb(product, nickname, serverip, username, password, domain, autolink) values("%s", "%s", "%s", "%s", "%s", "%s", "%s")' % (product, nickname, serverip, username, password, domain, autolink)
    db = connect_db()
    cur = db.cursor()
    cur.execute(sentense)
    cur.close()
    db.commit()
    db.close()


def deleteResource(rid):
    sentense = 'delete from vftb where id="%s"' % (rid)
    db = connect_db()
    cur = db.cursor()
    cur.execute(sentense)
    cur.close()
    db.commit()
    db.close()


def clearResource():
    sentense = 'delete from vftb'
    db = connect_db()
    cur = db.cursor()
    cur.execute(sentense)
    cur.close()
    db.commit()
    db.close()


def updateResource(rid, product, nickname, serverip, username, password, domain, autolink):
    sentense = 'update vftb set product="%s", nickname="%s", serverip="%s", username="%s", password="%s", domain="%s", autolink="%s" where id="%s"' % (product, nickname, serverip, username, password, domain, autolink, rid)
    db = connect_db()
    cur = db.cursor()
    cur.execute(sentense)
    cur.close()
    db.commit()
    db.close()


def updateLink():
    sentense = 'update vftb set autolink="0" '
    db = connect_db()
    cur = db.cursor()
    cur.execute(sentense)
    cur.close()
    db.commit()
    db.close()


def createIdv(name, autostart, cpu, memory, sdisk, ddisk, cdrom, floppy, nettype, ipaddr, netmask, gateway, dns, pci, port):
    sentense = 'insert into vfidv(name, autostart, cpu, memory, sdisk, sdisk_restore, ddisk, ddisk_restore, cdrom, floppy, boot, nettype, ipaddr, netmask, gateway, dns, pci, port) values("%s", "%s", "%s", "%s", "%s", "%s", "%s", "%s", "%s", "%s", "%s", "%s", "%s", "%s", "%s", "%s", "%s", "%s")' % (name, autostart, cpu, memory, sdisk, '', ddisk, '', cdrom, floppy, 'iso', nettype, ipaddr, netmask, gateway, dns, pci, port)
    db = connect_db()
    cur = db.cursor()
    cur.execute(sentense)
    cur.close()
    db.commit()
    db.close()


def deleteIdv(name):
    sentense = 'delete from vfidv where name="%s"' % (name)
    db = connect_db()
    cur = db.cursor()
    cur.execute(sentense)
    cur.close()
    db.commit()
    db.close()


def clearIdv():
    sentense = 'delete from vfidv'
    db = connect_db()
    cur = db.cursor()
    cur.execute(sentense)
    cur.close()
    db.commit()
    db.close()


def updateIdv(name, autostart, cpu, memory, sdisk, sdisk_restore, ddisk, ddisk_restore, cdrom, floppy, boot, nettype, ipaddr, netmask, gateway, dns, pci, port):
    sentense = 'update vfidv set autostart="%s", cpu="%s", memory="%s", sdisk="%s", sdisk_restore="%s", ddisk="%s", ddisk_restore="%s", cdrom="%s", floppy="%s", boot="%s", nettype="%s", ipaddr="%s", netmask="%s", gateway="%s", dns="%s", pci="%s", port="%s" where name="%s"' % (autostart, cpu, memory, sdisk, sdisk_restore, ddisk, ddisk_restore, cdrom, floppy, boot, nettype, ipaddr, netmask, gateway, dns, pci, port, name)
    db = connect_db()
    cur = db.cursor()
    cur.execute(sentense)
    cur.close()
    db.commit()
    db.close()


def clearPassword():
    sentense = 'delete from vfpswd'
    db = connect_db()
    cur = db.cursor()
    cur.execute(sentense)
    cur.close()
    db.commit()
    db.close()


def setPassword(password):
    sentense = 'insert into vfpswd(passwd) values("%s")' % password
    db = connect_db()
    cur = db.cursor()
    cur.execute(sentense)
    cur.close()
    db.commit()
    db.close()


##########################################################
#
# Request Related Logic, TOUPDATE (aoqingy)
#
##########################################################
#一般会有以下错误：连接被重置、连接被拒绝、网页不存在、连接超时、服务不可用、找不到主机
#192.168.0.1: ''
#192.168.0.16: <urlopen error [Errno 111] Connection refused>
#192.168.0.23: HTTP Error 404: Not Found
#192.168.0.28: <urlopen error timed out>
#192.168.0.88: HTTP Error 503: Service Temporarily Unavailable
#192.168.0.184: <urlopen error [Errno 113] No route to host>
RETRY_COUNT = 1
def sendRequest(url=None, method=None, data=None, headers=None, timeout=3):
    count = 0
    while (count < RETRY_COUNT):
        logger.info("Sending request (%s) to: %s..." % (str(count), url))
        try:
            if data:
                if headers:
                    request = urllib2.Request(url=url, data=urllib.urlencode(data), headers=headers)
                else:
                    request = urllib2.Request(url=url, data=urllib.urlencode(data))
            else:
                if headers:
                    request = urllib2.Request(url=url, headers=headers)
                else:
                    request = urllib2.Request(url=url)

            if method:
                request.get_method = lambda: method

            response = json.loads(urllib2.urlopen(request, timeout=timeout).read())
            return response
        except Exception, e:
            count = count + 1
            if count == RETRY_COUNT:
                raise
        time.sleep(1)

