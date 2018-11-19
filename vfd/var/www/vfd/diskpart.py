#!/usr/bin/python
#-*-coding:utf-8 -*-
import os
import re
import json
import time
import fcntl
import array
import shutil
import socket
import struct
import tempfile
import subprocess
from flask import Flask, request, send_file, make_response
#from flask.ext.babel import gettext as _
from werkzeug import secure_filename
from const   import *
from virtapi import *
from utility import *


##########################################################
#
# PXE Related Utilities
#
##########################################################
#查询非忙的磁盘或分区（通过/proc/partitions和/proc/mounts）
#返回JSON格式的{'code': 'True', 'message': {'disk': ['sda'], 'parts':['sda1', 'sda2']}}
def is_supported(device):
    if re.match(r'x?[hsv]d[a-z]+[0-9]*', device):
        return True
    return False


def is_partition(device):
    if re.match(r'x?[hsv]d[a-z]+[0-9]+', device):
        return True
    return False


def get_disk_name(device):
    command = "echo %s | sed -r -e 's/^([^0-9]*)[0-9]*$/\\1/g'" % device
    p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    return ''.join(p.stdout.readlines()).strip()


def get_partition_number(device):
    command = "echo %s | sed -r -e 's/^[^0-9]*-?([0-9]*)$/\\1/g'" % device
    p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    return ''.join(p.stdout.readlines()).strip()


#root@vclassterminal:~# parted /dev/sda print
#Model: ATA Hoodisk SSD (scsi)
#Disk /dev/sda: 32.0GB
#Sector size (logical/physical): 512B/512B
#Partition Table: msdos
#Disk Flags: 
#
#Number  Start   End     Size    Type      File system  Flags
# 1      1049kB  106MB   105MB   primary   ntfs         boot
# 2      106MB   17.5GB  17.4GB  primary   ntfs
# 3      17.5GB  32.0GB  14.5GB  extended
# 5      17.5GB  32.0GB  14.5GB  logical   ext4
def get_partition_size(device):
    command = 'parted /dev/%s print | grep -E "^[[:space:]]*%s\>" | awk -F" " "{print \$4}"' % (get_disk_name(device), get_partition_number(device))
    p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    return ''.join(p.stdout.readlines()).strip()


def get_partition_type(device):
    command = 'parted /dev/%s print | grep -E "^[[:space:]]*%s\>" | awk -F" " "{print \$5}"' % (get_disk_name(device), get_partition_number(device))
    p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    return ''.join(p.stdout.readlines()).strip()


def get_partition_filesystem(device):
    command = 'parted /dev/%s print | grep -E "^[[:space:]]*%s\>" | awk -F" " "{print \$6}"' % (get_disk_name(device), get_partition_number(device))
    p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    return ''.join(p.stdout.readlines()).strip()


def all_interfaces():
    max_possible = 128  # arbitrary. raise if needed.
    bytes = max_possible * 32
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    names = array.array('B', '\0' * bytes)
    outbytes = struct.unpack('iL', fcntl.ioctl(
        s.fileno(),
        0x8912,  # SIOCGIFCONF
        struct.pack('iL', bytes, names.buffer_info()[0])
    ))[0]
    namestr = names.tostring()
    lst = []
    for i in range(0, outbytes, 40):
        name = namestr[i:i+16].split('\0', 1)[0]
        lst.append(name)
    return lst


def get_ip_address(ifname):
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    return socket.inet_ntoa(fcntl.ioctl(
        s.fileno(),
        0x8915,  # SIOCGIFADDR
        struct.pack('256s', ifname[:15])
    )[20:24])


##########################################################
#
# PXE Related Logic
#
##########################################################
#@app.route('/api/diskpart/cquery', methods=['GET'])
def query_diskpart():
    logger.info("Entering query_diskpart...")

    try:
        command = "cat /proc/partitions | egrep '[0-9]+[[:blank:]]+[0-9]+[[:blank:]]+[0-9]+[[:blank:]]+.*' | awk '{ print $4 }' | sort -V"
        p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        devices = ''.join(p.stdout.readlines())

        command = "cat /proc/mounts"
        p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        mounts = ''.join(p.stdout.readlines())

        rdevices = {}
        disks = []
        partitions = []
        for device in devices.split('\n'):
            if not is_supported(device) or device in mounts:
                continue
            if is_partition(device):
                ptype       = get_partition_type(device).lower()
                pfilesystem = get_partition_filesystem(device).lower()
                if ptype != 'extended' and not 'swap' in pfilesystem:
                    partitions.append(device)
            else:
                disks.append(device)
        rdevices['disk']  = disks
        rdevices['parts'] = partitions

        logger.info(rdevices)
        return json.dumps({'code':'True', 'message':rdevices})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


def save_restore_common(command, path):
    if not os.path.isdir('/home/partimag'):
        p = subprocess.Popen('mkdir /home/partimag', shell=True)
        p.communicate()

    if path:
        p = subprocess.Popen('mount -t nfs -o retry=0 %s /home/partimag' % path, shell=True)
        p.communicate()
        if p.returncode != 0:
            raise Exception('Fail to mount %s!' % path)

    logger.info(command)
    p = subprocess.Popen(command, shell=True)
    p.communicate()

    if path:
        p = subprocess.Popen('umount /home/partimag', shell=True)
        p.communicate()


def check_clonezilla_log():
    CLONEZILLA_LOGFILE = '/var/log/clonezilla.log'
    command = "cat %s | grep 'The data partition to be saved:'" % CLONEZILLA_LOGFILE
    p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    out, err = p.communicate()
    devnames = out[34:].strip()

    for devname in devnames.split(' '):
        command = "cat %s | grep 'Finished saving /dev/%s'" % (CLONEZILLA_LOGFILE, devname)
        p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        out, err = p.communicate()
        if out.strip():			#The partition is finished successfully
            continue

        message = ""
        command = "cat %s | grep 'Please boot Windows or fix it by fsck.'" % CLONEZILLA_LOGFILE
        p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        out, err = p.communicate()
        if out.strip():
            message += "Windows OS is unclean and needs fsck!\n"

        command = "cat %s | grep 'No space left on device!'" % CLONEZILLA_LOGFILE
        p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        out, err = p.communicate()
        if out.strip():
            message += "No enough space to save partitions!\n"

        raise Exception(message)

    return "Done!"


#@app.route('/api/diskpart/csave', methods=['POST'])
def save_diskpart():
    logger.info("Entering save_diskpart...")
    type_ = request.form.get('type', '')
    dps   = request.form.get('dps',  '')
    path  = request.form.get('path', '')
    logger.info("type: %s, dps: %s, path: %s" % (type_, dps, path))
    try:
        #判断是否从USB磁盘启动。若是，适用USB许可逻辑；否则适用PXE许可逻辑
        command = 'udevadm info --query=all `awk \'$2=="/"{print $1}\' /proc/mounts` | grep ID_BUS'
        p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        if 'usb' in ''.join(p.stdout.readlines()).strip():
            #USB系统还原入口(aoqingy)
            if not check_useable('usb'):
                raise Exception('USB license not activiated!')
        else:
            #系统还原入口(aoqingy)
            if not check_useable('pxe'):
                raise Exception('PXE license not activiated.')

        diskparts = ' '.join(dps.split(','))
        if type_ == 'disk':
            command = '/usr/sbin/ocs-sr -q2 -j2 -nogui -fsck-src-part-y -z1p -i 4000 -sc -p true savedisk image "%s"' % diskparts
        else:                                   #parts
            command = '/usr/sbin/ocs-sr -q2 -j2 -nogui -fsck-src-part-y -z1p -i 4000 -sc -p true saveparts image "%s"' % diskparts
        save_restore_common(command, path)

        #检查日志，判断保存是否成功
        check_clonezilla_log()

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/diskpart/crestore', methods=['POST'])
def restore_diskpart():
    logger.info("Entering restore_diskpart...")
    type_ = request.form.get('type',  '')
    dps   = request.form.get('dps', '')
    path  = request.form.get('path', '')
    logger.info("type: %s, dps: %s, path: %s" % (type_, dps, path))

    try:
        #判断是否从USB磁盘启动。若是，适用USB许可逻辑；否则适用PXE许可逻辑
        command = 'udevadm info --query=all `awk \'$2=="/"{print $1}\' /proc/mounts` | grep ID_BUS'
        p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        if 'usb' in ''.join(p.stdout.readlines()).strip():
            #USB系统还原入口(aoqingy)
            if not check_useable('usb'):
                raise Exception('USB license not activiated!')
        else:
            #系统还原入口(aoqingy)
            if not check_useable('pxe'):
                raise Exception('PXE license not activiated.')

        diskparts = ' '.join(dps.split(','))
        if type_ == 'disk':
            command = '/usr/sbin/ocs-sr -e1 auto -e2 -nogui -j1 -j2 -p true restoredisk image "%s"' % diskparts
        else:                                   #parts
            command = '/usr/sbin/ocs-sr -e1 auto -e2 -nogui -j1 -j2 -k -p true restoreparts image "%s"' % diskparts
        save_restore_common(command, path)

        #检查日志，判断恢复是否成功

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/diskpart/cmrestore', methods=['POST'])
def mrestore_diskpart():
    logger.info("Entering mrestore_diskpart...")
    type_ = request.form.get('type',  '')
    dps   = request.form.get('dps', '')
    path  = request.form.get('path', '')
    logger.info("type: %s, dps: %s, path: %s" % (type_, dps, path))

    try:
        #判断是否从USB磁盘启动。若是，适用USB许可逻辑；否则适用PXE许可逻辑
        command = 'udevadm info --query=all `awk \'$2=="/"{print $1}\' /proc/mounts` | grep ID_BUS'
        p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        if 'usb' in ''.join(p.stdout.readlines()).strip():
            #USB系统还原入口(aoqingy)
            if not check_useable('usb'):
                raise Exception('USB license not activiated!')
        else:
            #系统还原入口(aoqingy)
            if not check_useable('pxe'):
                raise Exception('PXE license not activiated.')

        diskparts = ' '.join(dps.split(','))
        if type_ == 'disk':
            command = '/usr/sbin/ocs-sr -e1 auto -e2 -nogui -j1 -j2 -p true --mcast-port 2232 multicast_restoredisk image "%s"' % diskparts
        else:					#parts
            command = '/usr/sbin/ocs-sr -e1 auto -e2 -nogui -j1 -j2 -k -p true --mcast-port 2232 multicast_restoreparts image "%s"' % diskparts
        save_restore_common(command, path)

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/diskpart/cmudpsend', methods=['POST'])
def mudpsend_diskpart():
    logger.info("Entering mudpsend_diskpart...")
    type_  = request.form.get('type',   '')
    dps    = request.form.get('dps',    '')
    path   = request.form.get('path',   '')
    ipaddr = request.form.get('ipaddr', '')
    rnum   = request.form.get('rnum',   '')
    logger.info("type: %s, dps: %s, path: %s, ipaddr: %s, rnum: %s" % (type_, dps, path, ipaddr, rnum))

    try:
        for interface in all_interfaces():
            if ipaddr in get_ip_address(interface):
                break

        diskparts = ' '.join(dps.split(','))
        if type_ == 'disk':
            command = '/bin/bash %s/multicast_restore.sh -n %s --max-wait 30 --mcast-port 2232 --interface %s -t multicast_restoredisk -o image "%s"' % (SCRIPT_DIR, rnum, interface, diskparts)
        else:
            command = '/bin/bash %s/multicast_restore.sh -n %s --max-wait 30 --mcast-port 2232 --interface %s -t multicast_restoreparts -o image "%s"' % (SCRIPT_DIR, rnum, interface, diskparts)
        save_restore_common(command, path)

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/winparam/update', methods=['POST'])
#def update_winparam():
#    logger.info("Entering update_winparam...")
#    mac     = request.form.get('mac',     '')
#    ipaddr  = request.form.get('ipaddr',  '')
#    netmask = request.form.get('netmask', '')
#    gateway = request.form.get('gateway', '')
#    dns1    = request.form.get('dns1',    '')
#    logger.info("mac: %s, ipaddr: %s, netmask: %s, gateway: %s, dsn1: %s" % (mac, ipaddr, netmask, gateway, dns1))
#
#    try:
#        hostname = mac.replace(':', '-')
#        bat = '@echo off\r\nset hostname=%s\r\nreg add "HKEY_LOCAL_MACHINE\System\CurrentControlSet\Control\ComputerName\ActiveComputerName" /v ComputerName /t reg_sz /d %%hostname%% /f >nul 2>nul\r\nreg add "HKEY_LOCAL_MACHINE\System\CurrentControlSet\Services\Tcpip\Parameters" /v "NV Hostname" /t reg_sz /d %%hostname%% /f >nul 2>nul\r\nreg add "HKEY_LOCAL_MACHINE\System\CurrentControlSet\Services\Tcpip\Parameters" /v Hostname /t reg_sz /d %%hostname%% /f >nul 2>nul\r\nnetsh interface ip set address name="%%1" source=static addr=%s mask=%s gateway=%s 1\r\nnetsh interface ip set dns name="%%1" source=static addr=%s\r\nshutdown /r\r\nstart /b "" cmd /c del "c:\\virtfan.bat" && exit'.encode('utf8') % (hostname, ipaddr, netmask, gateway, dns1)
#
#        f = open('/tmp/virtfan.bat', 'w')
#        f.write(bat)
#        f.close()
#
#        #将上述文件放在所有分区下
#        command = "cat /proc/partitions | egrep '[0-9]+[[:blank:]]+[0-9]+[[:blank:]]+[0-9]+[[:blank:]]+.*' | awk '{ print $4 }' | sort -V"
#        p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
#        devices = ''.join(p.stdout.readlines())
#
#        command = "cat /proc/mounts"
#        p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
#        mounts = ''.join(p.stdout.readlines())
#
#        partitions = []
#        for device in devices.split('\n'):
#            if not is_supported(device) or device in mounts:
#                continue
#            if not is_partition(device):
#                continue
#
#            try:
#                psize       = get_partition_size(device).lower()
#            except:
#                psize       = ''
#            try:
#                ptype       = get_partition_type(device).lower()
#            except:
#                ptype       = ''
#            try:
#                pfilesystem = get_partition_filesystem(device).lower()
#            except:
#                pfilesystem = ''
#
#            if not psize or 'mb' in psize:			#Skip Boot Partition
#                continue
#            if not pfilesystem or not 'ntfs' in pfilesystem:
#                continue
#            partitions.append(device)
#
#        for partition in partitions:
#            command = '%s/update_winparam.sh %s %s' % (SCRIPT_DIR, partition, '/tmp/virtfan.bat')
#            logger.info(command)
#            p = subprocess.Popen(command, shell=True)
#            p.communicate()
#
#        logger.info('Done!')
#        return json.dumps({'code':'True', 'message':'Done!'})
#    except Exception, e:
#        logger.error(str(e))
#        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/diskpart/upload', methods=['POST'])
def upload_diskpart():
    logger.info("Entering upload_diskpart...")
    path  = request.form.get('path', '')
    logger.info("path: %s" % path)
    try:
        #判断是否从USB磁盘启动。若是，适用USB许可逻辑；否则适用PXE许可逻辑
        command = 'udevadm info --query=all `awk \'$2=="/"{print $1}\' /proc/mounts` | grep ID_BUS'
        p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        if 'usb' in ''.join(p.stdout.readlines()).strip():
            #USB系统还原入口(aoqingy)
            if not check_useable('usb'):
                raise Exception('USB license not activiated!')
        else:
            #系统还原入口(aoqingy)
            if not check_useable('pxe'):
                raise Exception('PXE license not activiated.')

        #防止/home/partimag是远程路径
        command = 'umount /home/partimag'
        p = subprocess.Popen(command, shell=True)
        p.communicate()

        if not os.path.isdir('/home/partimag/image'):
            raise Exception('No image on local system!')

        dpath = tempfile.mkdtemp(dir="/mnt")
        command = 'mount -t nfs -o retry=0 %s %s' % (path, dpath)
        p = subprocess.Popen(command, shell=True)
        p.communicate()
        if p.returncode != 0:
            raise Exception('Fail to mount %s!' % path)

        command = 'rm -rf %s/image' % dpath
        p = subprocess.Popen(command, shell=True)
        p.communicate()

        command = 'cp -r /home/partimag/image %s/image' % dpath
        p = subprocess.Popen(command, shell=True)
        p.communicate()

        command = 'umount %s' % dpath
        p = subprocess.Popen(command, shell=True)
        p.communicate()

        shutil.rmtree(dpath)

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/diskpart/download', methods=['POST'])
def download_diskpart():
    logger.info("Entering download_diskpart...")
    path  = request.form.get('path', '')
    logger.info("path: %s" % path)
    try:
        #判断是否从USB磁盘启动。若是，适用USB许可逻辑；否则适用PXE许可逻辑
        command = 'udevadm info --query=all `awk \'$2=="/"{print $1}\' /proc/mounts` | grep ID_BUS'
        p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        if 'usb' in ''.join(p.stdout.readlines()).strip():
            #USB系统还原入口(aoqingy)
            if not check_useable('usb'):
                raise Exception('USB license not activiated!')
        else:
            #系统还原入口(aoqingy)
            if not check_useable('pxe'):
                raise Exception('PXE license not activiated.')

        #防止/home/partimag是远程路径
        command = 'umount /home/partimag'
        p = subprocess.Popen(command, shell=True)
        p.communicate()

        dpath = tempfile.mkdtemp(dir="/mnt")
        command = 'mount -t nfs -o retry=0 %s %s' % (path, dpath)
        p = subprocess.Popen(command, shell=True)
        p.communicate()
        if p.returncode != 0:
            raise Exception('Fail to mount %s!' % path)

        if not os.path.isdir('%s/image' % dpath):
            raise Exception('No image on remote system!')

        command = 'mkdir -p /home/partimag'
        p = subprocess.Popen(command, shell=True)
        p.communicate()

        command = 'rm -rf /home/partimag/image'
        p = subprocess.Popen(command, shell=True)
        p.communicate()

        command = 'cp -r %s/image /home/partimag/image' % dpath
        p = subprocess.Popen(command, shell=True)
        p.communicate()

        command = 'umount %s' % dpath
        p = subprocess.Popen(command, shell=True)
        p.communicate()

        shutil.rmtree(dpath)

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})

