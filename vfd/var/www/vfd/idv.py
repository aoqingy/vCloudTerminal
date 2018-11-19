#!/usr/bin/python
#-*-coding:utf-8 -*-
import os
import re
import glob
import json
import time
import uuid
import fcntl
import array
import shutil
import socket
import struct
import tempfile
import subprocess
import multiprocessing
from flask import Flask, request, send_file, make_response
#from flask.ext.babel import gettext as _
from werkzeug import secure_filename
from const   import *
from virtapi import *
from utility import *


##########################################################
#
# PXE Related Logic
#
##########################################################
#@app.route('/api/idv/memory', methods=['GET'])
def get_memory():
    logger.info("Entering get_memory...")

    try:
        command = "cat /proc/meminfo | grep MemTotal | awk '{ print $2 }'"
        p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        rmemory = str(int(''.join(p.stdout.readlines()).strip()) / 1024) + ' MB'

        logger.info(rmemory)
        return json.dumps({'code':'True', 'message':rmemory})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/idv/cpu', methods=['GET'])
def get_cpu():
    logger.info("Entering get_cpu...")

    try:
        rcpu = str(multiprocessing.cpu_count())

        logger.info(rcpu)
        return json.dumps({'code':'True', 'message':rcpu})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/idv/disk', methods=['GET'])
def get_disks():
    logger.info("Entering get_disks...")

    try:
        rdisks = []
        for i in glob.glob('/home/image/*.img'):
            rdisks.append(os.path.basename(i)[:-4])
        rdisks = sorted(rdisks)

        logger.info(rdisks)
        return json.dumps({'code':'True', 'message':rdisks})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/idv/iso', methods=['GET'])
def get_isos():
    logger.info("Entering get_isos...")

    try:
        risos = []
        for i in glob.glob('/home/image/*.iso'):
            risos.append(os.path.basename(i)[:-4])
        risos = sorted(risos)

        logger.info(risos)
        return json.dumps({'code':'True', 'message':risos})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/idv/vfd', methods=['GET'])
def get_vfds():
    logger.info("Entering get_vfds...")

    try:
        rvfds = []
        for i in glob.glob('/home/image/*.vfd'):
            rvfds.append(os.path.basename(i)[:-4])
        rvfds = sorted(rvfds)

        logger.info(rvfds)
        return json.dumps({'code':'True', 'message':rvfds})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/idv/pci', methods=['GET'])
def get_pcis():
    logger.info("Entering get_pcis...")

    try:
        rpcis = []
        command = 'lspci'
        p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        for line in p.stdout.readlines():
            line = line.strip()
            pcid = line.split()[0]
            pcin = line[len(pcid)+1:]
            if not pcin.startswith('USB controller') and not pcin.startswith('Audio device') and not pcin.startswith('VGA compatible controller'):
                continue
            rpcis.append({'id': pcid, 'name': pcin})

        logger.info(rpcis)
        return json.dumps({'code':'True', 'message':rpcis})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#@app.route('/api/idv/adisk', methods=['GET'])
def get_adisk():
    logger.info("Entering get_adisk...")

    try:
        s = os.statvfs('/var')
        radisk = str(int(s.f_bsize * s.f_bavail)/1024/1024/1024) + ' GB'

        logger.info(radisk)
        return json.dumps({'code':'True', 'message':radisk})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


def create_disk():
    logger.info("Entering create_disk...")
    name = request.form.get('name',  '')
    size = request.form.get('size', '')
    logger.info("name: %s, size: %s" % (name, size))

    try:
        command = 'mkdir -p /home/image'
        p = subprocess.Popen(command, shell=True)
        p.communicate()

        command = 'qemu-img create -f qcow2 /home/image/%s.img %sG' % (name, size)
        p = subprocess.Popen(command, shell=True)
        p.communicate()

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


def list_idvs():
    logger.info("Entering list_idvs...")

    try:
        rv = query_db('select * from vfidv')
        logger.info(rv)
        return json.dumps({'code':'True', 'message':rv})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


#在创建IDV桌面时，将桌面参数保存在数据库中
#对应SPICE端口，从5901开始到查找一个空闲的，条件是没有在数据库中，并且没有被进程使用(lsof -i :5901)
#如果“开机启动”状态为True，则创建一条脚本添加到/etc/rc.local中

#在编辑IDV桌面时，修改桌面参数
#如果“开机启动”状态为True，则创建一条脚本添加到/etc/rc.local中

#在连接时
#从数据库读取桌面参数
#判断进程是否在运行，如果没有则运行
#调用remote-viewer连接
def prepareCommand(idv):
    logger.info('Preparing qemu-kvm command...')
    qcommand = ''
    if idv['sdisk'] and idv['sdisk_restore']:
        qcommand += 'rm /home/image/%s.snap\n' % idv['sdisk']
        qcommand += 'qemu-img create -f qcow2 -o backing_file=/home/image/%s.img /home/image/%s.snap 10G\n' % (idv['sdisk'], idv['sdisk'])

    if idv['ddisk'] and idv['ddisk_restore']:
        qcommand += 'rm /home/image/%s.snap\n' % idv['ddisk']
        qcommand += 'qemu-img create -f qcow2 -o backing_file=/home/image/%s.img /home/image/%s.snap 10G\n' % (idv['ddisk'], idv['ddisk'])

    if idv['pci']:
        qcommand += 'modprobe vfio\n'
        qcommand += 'modprobe vfio-pci\n'

    if idv['pci']:
        for i in idv['pci'].split(','):
            qcommand += '/bin/bash /var/www/vfd/script/passthrough.sh 0000:%s\n' % i

    qcommand += '/usr/bin/qemu-system-x86_64'
    qcommand += ' -enable-kvm'
    qcommand += ' -name %s' % idv['name']
    qcommand += ' -m %s' % idv['memory']
    qcommand += ' -smp %s,sockets=1,cores=%s,threads=1' % (idv['cpu'], idv['cpu'])
    qcommand += ' -no-user-config'
    qcommand += ' -nodefaults'
    qcommand += ' -no-hpet'
    #qcommand += ' -no-shutdown'
    qcommand += ' -realtime mlock=off'
    qcommand += ' -rtc base=localtime,driftfix=slew'
    qcommand += ' -global kvm-pit.lost_tick_policy=discard'
    qcommand += ' -uuid %s' % uuid.uuid1() 
    #监控
    qcommand += ' -chardev socket,id=charmonitor,path=/usr/sbin/virtfan/%s.sock,server,nowait' % idv['name']
    qcommand += ' -mon chardev=charmonitor,id=monitor,mode=control'
    #光盘
    if idv['cdrom']:
        qcommand += ' -drive file=/home/image/%s.iso,if=none,id=drive-ide0-1-0,readonly=on,format=raw' % idv['cdrom']
        if idv['boot'] == 'iso':
            qcommand += ' -device ide-cd,bus=ide.1,unit=0,drive=drive-ide0-1-0,id=ide0-1-0,bootindex=1'
        else:
            qcommand += ' -device ide-cd,bus=ide.1,unit=0,drive=drive-ide0-1-0,id=ide0-1-0,bootindex=2'
    #软盘
    if idv['floppy']:
        qcommand += ' -drive file=/home/image/%s.vfd,if=none,id=drive-fdc0-0-0,readonly=on,format=raw' % idv['floppy']
        qcommand += ' -global isa-fdc.driveA=drive-fdc0-0-0'
    #磁盘
    qcommand += ' -device virtio-scsi-pci,id=scsi0,bus=pci.0,addr=0x2'
    if idv['sdisk']:
        if idv['sdisk_restore']:
            qcommand += ' -drive file=/home/image/%s.snap,format=qcow2,if=none,id=drive-virtio-disk0' % idv['sdisk']
        else:
            command = "qemu-img info /home/image/%s.img | grep 'file format:' | awk '{print $3}'" % idv['sdisk']
            p = subprocess.Popen(command, stdout=subprocess.PIPE, shell=True)
            out, dummy = p.communicate()
            _format = out.strip()
            qcommand += ' -drive file=/home/image/%s.img,format=%s,if=none,id=drive-virtio-disk0' % (idv['sdisk'], _format)
        if idv['boot'] == 'disk':
            qcommand += ' -device scsi-hd,bus=scsi0.0,channel=0,scsi-id=0,lun=0,drive=drive-virtio-disk0,id=virtio-disk0,bootindex=1'
        else:
            qcommand += ' -device scsi-hd,bus=scsi0.0,channel=0,scsi-id=0,lun=0,drive=drive-virtio-disk0,id=virtio-disk0,bootindex=2'
    if idv['ddisk']:
        if idv['ddisk_restore']:
            qcommand += ' -drive file=/home/image/%s.snap,format=qcow2,if=none,id=drive-virtio-disk1' % idv['ddisk']
        else:
            command = "qemu-img info /home/image/%s.img | grep 'file format:' | awk '{print $3}'" % idv['ddisk']
            p = subprocess.Popen(command, stdout=subprocess.PIPE, shell=True)
            out, dummy = p.communicate()
            _format = out.strip()
            qcommand += ' -drive file=/home/image/%s.img,format=%s,if=none,id=drive-virtio-disk1' % (idv['ddisk'], _format)
        qcommand += ' -device scsi-hd,bus=scsi0.0,channel=0,scsi-id=0,lun=1,drive=drive-virtio-disk1,id=virtio-disk1'
    #启动
    qcommand += ' -boot menu=on,splash-time=10000,strict=on'

    #网络
    qcommand += ' -netdev user,id=usernet0'
    qcommand += ' -device rtl8139,netdev=usernet0,id=net0,bus=pci.0,addr=0x3'

    #显卡
    qcommand += ' -device qxl-vga,id=video0,ram_size=67108864,vram_size=67108864,vgamem_mb=16,bus=pci.0,addr=0x4'
    #声卡
    qcommand += ' -device intel-hda,id=sound0,bus=pci.0,addr=0x5'
    qcommand += ' -device hda-duplex,id=sound0-codec0,bus=sound0.0,cad=0'

    #USB设备
    qcommand += ' -device ich9-usb-ehci1,id=usb,bus=pci.0,addr=0x6.0x7'
    qcommand += ' -device ich9-usb-uhci1,masterbus=usb.0,firstport=0,bus=pci.0,multifunction=on,addr=0x6'
    qcommand += ' -device ich9-usb-uhci2,masterbus=usb.0,firstport=2,bus=pci.0,addr=0x6.0x1'
    qcommand += ' -device ich9-usb-uhci3,masterbus=usb.0,firstport=4,bus=pci.0,addr=0x6.0x2'
    qcommand += ' -device usb-tablet,id=input0'
    qcommand += ' -chardev spicevmc,id=charredir0,name=usbredir'
    qcommand += ' -device usb-redir,chardev=charredir0,id=redir0'
    qcommand += ' -chardev spicevmc,id=charredir1,name=usbredir'
    qcommand += ' -device usb-redir,chardev=charredir1,id=redir1'
    qcommand += ' -chardev spicevmc,id=charredir2,name=usbredir'
    qcommand += ' -device usb-redir,chardev=charredir2,id=redir2'
    qcommand += ' -chardev spicevmc,id=charredir3,name=usbredir'
    qcommand += ' -device usb-redir,chardev=charredir3,id=redir3'
    qcommand += ' -device nec-usb-xhci,id=usb2,bus=pci.0,addr=0x7'
    qcommand += ' -chardev spicevmc,id=charredir4,name=usbredir'
    qcommand += ' -device usb-redir,chardev=charredir4,id=redir4'
    qcommand += ' -chardev spicevmc,id=charredir5,name=usbredir'
    qcommand += ' -device usb-redir,chardev=charredir5,id=redir5'
    qcommand += ' -chardev spicevmc,id=charredir6,name=usbredir'
    qcommand += ' -device usb-redir,chardev=charredir6,id=redir6'
    qcommand += ' -chardev spicevmc,id=charredir7,name=usbredir'
    qcommand += ' -device usb-redir,chardev=charredir7,id=redir7'

    #串口设备
    qcommand += ' -device virtio-serial,id=virtio-serial0,bus=pci.0,addr=0x8'
    qcommand += ' -chardev spicevmc,id=charchannel0,name=vdagent'
    qcommand += ' -device virtserialport,bus=virtio-serial0.0,nr=1,chardev=charchannel0,id=channel0,name=com.redhat.spice.0'

    #内存胀缩设备
    qcommand += ' -device virtio-balloon-pci,id=balloon0,bus=pci.0,addr=0x9'

    #PCI透传设备
    if idv['pci']:
        count = 0
        for pci in idv['pci'].split(','):
            qcommand += ' -device vfio-pci,host=%s,id=hostdev%s,bus=pci.0,addr=0x%s' % (pci, str(count), str(10+count))
            count += 1

    #SPICE协议
    qcommand += ' -spice port=%s,addr=127.0.0.1,disable-ticketing,image-compression=off,seamless-migration=on' % idv['port']

    qcommand += ' &\n'

    command = 'mkdir -p /usr/sbin/virtfan/'
    p = subprocess.Popen(command, shell=True)
    p.communicate()

    if idv['autostart']:
        command = 'echo "%s" > /usr/sbin/virtfan/%s.sh' % (qcommand, idv['name'])
    else:
        command = 'rm /usr/sbin/virtfan/%s.sh' % idv['name']
    p = subprocess.Popen(command, shell=True)
    p.communicate()

    logger.info(qcommand)
    return qcommand


def queryIdvByName(name):
    idvs = query_db('select * from vfidv')
    for idv in idvs:
        if idv['name'] == name:
            return idv
    return None


def queryIdvByPort(port):
    idvs = query_db('select * from vfidv')
    for idv in idvs:
        if idv['port'] == port:
            return idv
    return None


def get_idv_info():
    logger.info("Entering get_idv_info...")
    name = request.args.get('name',      '')
    logger.info("name: %s" % name)

    try:
        ridv = queryIdvByName(name)

        logger.info(ridv)
        return json.dumps({'code':'True', 'message':ridv})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


def create_idv():
    logger.info("Entering create_idv...")
    name      = request.form.get('name',      '')
    autostart = request.form.get('autostart', '')
    cpu       = request.form.get('cpu',       '')
    memory    = request.form.get('memory',    '')
    sdisk     = request.form.get('sdisk',     '')
    ddisk     = request.form.get('ddisk',     '')
    cdrom     = request.form.get('cdrom',     '')
    floppy    = request.form.get('floppy',    '')
    nettype   = request.form.get('nettype',   '')
    ipaddr    = request.form.get('ipaddr',    '')
    netmask   = request.form.get('netmask',   '')
    gateway   = request.form.get('gateway',   '')
    dns       = request.form.get('dns',       '')
    pci       = request.form.get('pci',       '')
    logger.info("name: %s, autostart: %s, cpu: %s, memory: %s, sdisk: %s, ddisk: %s, cdrom: %s, floppy: %s, nettype: %s, ipaddr: %s, netmask: %s, gateway: %s, dns: %s, pci: %s" % (name, autostart, cpu, memory, sdisk, ddisk, cdrom, floppy, nettype, ipaddr, netmask, gateway, dns, pci))
    try:
        for port in range(5901, 6000):
            if queryIdvByPort(str(port)):
                continue

        createIdv(name, autostart, cpu, memory, sdisk, ddisk, cdrom, floppy, nettype, ipaddr, netmask, gateway, dns, pci, str(port))

        idv = queryIdvByName(name)
        command = prepareCommand(idv)

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


def remove_idv():
    logger.info("Entering remove_idv...")
    name = request.form.get('name', '')
    logger.info("name: %s" % name)

    try:
        deleteIdv(name)

        command = 'rm /usr/sbin/virtfan/%s.sh' % name
        p = subprocess.Popen(command, shell=True)
        p.communicate()

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


def edit_idv_cpu():
    logger.info("Entering edit_idv_cpu...")
    name = request.form.get('name', '')
    cpu  = request.form.get('cpu',  '')
    logger.info("name: %s, cpu: %s" % (name, cpu))

    try:
        idv = queryIdvByName(name)

        updateIdv(name, idv['autostart'], cpu, idv['memory'], idv['sdisk'], idv['sdisk_restore'], idv['ddisk'], idv['ddisk_restore'], idv['cdrom'], idv['floppy'], idv['boot'], idv['nettype'], idv['ipaddr'], idv['netmask'], idv['gateway'], idv['dns'], idv['pci'], idv['port'])

        idv = queryIdvByName(name)
        command = prepareCommand(idv)

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


def edit_idv_memory():
    logger.info("Entering edit_idv_memory...")
    name   = request.form.get('name', '')
    memory = request.form.get('memory',  '')
    logger.info("name: %s, memory: %s" % (name, memory))

    try:
        idv = queryIdvByName(name)

        updateIdv(name, idv['autostart'], idv['cpu'], memory, idv['sdisk'], idv['sdisk_restore'], idv['ddisk'], idv['ddisk_restore'], idv['cdrom'], idv['floppy'], idv['boot'], idv['nettype'], idv['ipaddr'], idv['netmask'], idv['gateway'], idv['dns'], idv['pci'], idv['port'])

        idv = queryIdvByName(name)
        command = prepareCommand(idv)

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


def edit_idv_cdrom():
    logger.info("Entering edit_idv_cdrom...")
    name  = request.form.get('name',  '')
    cdrom = request.form.get('cdrom', '')
    boot  = request.form.get('boot',  '')
    logger.info("name: %s, cdrom: %s, boot: %s" % (name, cdrom, boot))

    try:
        idv = queryIdvByName(name)

        if not boot:
            boot = idv['boot']

        updateIdv(name, idv['autostart'], idv['cpu'], idv['memory'], idv['sdisk'], idv['sdisk_restore'], idv['ddisk'], idv['ddisk_restore'], cdrom, idv['floppy'], boot, idv['nettype'], idv['ipaddr'], idv['netmask'], idv['gateway'], idv['dns'], idv['pci'], idv['port'])

        idv = queryIdvByName(name)
        command = prepareCommand(idv)

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


def edit_idv_floppy():
    logger.info("Entering edit_idv_floppy...")
    name   = request.form.get('name',   '')
    floppy = request.form.get('floppy', '')
    logger.info("name: %s, floppy: %s" % (name, floppy))

    try:
        idv = queryIdvByName(name)

        updateIdv(name, idv['autostart'], idv['cpu'], idv['memory'], idv['sdisk'], idv['sdisk_restore'], idv['ddisk'], idv['ddisk_restore'], idv['cdrom'], floppy, idv['boot'], idv['nettype'], idv['ipaddr'], idv['netmask'], idv['gateway'], idv['dns'], idv['pci'], idv['port'])

        idv = queryIdvByName(name)
        command = prepareCommand(idv)

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


def edit_idv_sdisk():
    logger.info("Entering edit_idv_sdisk...")
    name          = request.form.get('name',  '')
    sdisk         = request.form.get('sdisk', '')
    sdisk_restore = request.form.get('sdisk_restore', '')
    boot          = request.form.get('boot',  '')
    logger.info("name: %s, sdisk: %s, sdisk_restore: %s, boot: %s" % (name, sdisk, sdisk_restore, boot))

    try:
        idv = queryIdvByName(name)

        if not boot:
            boot = idv['boot']

        updateIdv(name, idv['autostart'], idv['cpu'], idv['memory'], sdisk, sdisk_restore, idv['ddisk'], idv['ddisk_restore'], idv['cdrom'], idv['floppy'], boot, idv['nettype'], idv['ipaddr'], idv['netmask'], idv['gateway'], idv['dns'], idv['pci'], idv['port'])

        idv = queryIdvByName(name)
        command = prepareCommand(idv)

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


def edit_idv_ddisk():
    logger.info("Entering edit_idv_ddisk...")
    name          = request.form.get('name', '')
    ddisk         = request.form.get('ddisk',  '')
    ddisk_restore = request.form.get('ddisk_restore', '')
    logger.info("name: %s, ddisk: %s" % (name, ddisk))

    try:
        idv = queryIdvByName(name)

        updateIdv(name, idv['autostart'], idv['cpu'], idv['memory'], idv['sdisk'], idv['sdisk_restore'], ddisk, ddisk_restore, idv['cdrom'], idv['floppy'], idv['boot'], idv['nettype'], idv['ipaddr'], idv['netmask'], idv['gateway'], idv['dns'], idv['pci'], idv['port'])

        idv = queryIdvByName(name)
        command = prepareCommand(idv)

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


def edit_idv_network():
    logger.info("Entering edit_idv_network...")
    name    = request.form.get('name',    '')
    nettype = request.form.get('nettype', '')
    ipaddr  = request.form.get('ipaddr',  '')
    netmask = request.form.get('netmask', '')
    gateway = request.form.get('gateway', '')
    dns     = request.form.get('dns',     '')
    logger.info("name: %s, nettype: %s, ipaddr: %s, netmask: %s, gateway: %s, dns: %s" % (name, nettype, ipaddr, netmask, gateway, dns))

    try:
        idv = queryIdvByName(name)

        updateIdv(name, idv['autostart'], idv['cpu'], idv['memory'], idv['sdisk'], idv['sdisk_restore'], idv['ddisk'], idv['ddisk_restore'], idv['cdrom'], idv['floppy'], idv['boot'], nettype, ipaddr, netmask, gateway, dns, idv['pci'], idv['port'])

        idv = queryIdvByName(name)
        command = prepareCommand(idv)

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


def edit_idv_pci():
    logger.info("Entering edit_idv_pci...")
    name = request.form.get('name', '')
    pci  = request.form.get('pci',  '')
    logger.info("name: %s, pci: %s" % (name, pci))

    try:
        idv = queryIdvByName(name)

        updateIdv(name, idv['autostart'], idv['cpu'], idv['memory'], idv['sdisk'], idv['sdisk_restore'], idv['ddisk'], idv['ddisk_restore'], idv['cdrom'], idv['floppy'], idv['boot'], idv['nettype'], idv['ipaddr'], idv['netmask'], idv['gateway'], idv['dns'], pci, idv['port'])

        idv = queryIdvByName(name)
        command = prepareCommand(idv)

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


def edit_idv_autostart():
    logger.info("Entering edit_idv_autostart...")
    name      = request.form.get('name',      '')
    autostart = request.form.get('autostart', '')
    logger.info("name: %s, autostart: %s" % (name, autostart))

    try:
        idv = queryIdvByName(name)

        updateIdv(name, autostart, idv['cpu'], idv['memory'], idv['sdisk'], idv['sdisk_restore'], idv['ddisk'], idv['ddisk_restore'], idv['cdrom'], idv['floppy'], idv['boot'], idv['nettype'], idv['ipaddr'], idv['netmask'], idv['gateway'], idv['dns'], idv['pci'], idv['port'])

        idv = queryIdvByName(name)
        command = prepareCommand(idv)

        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


def get_pci_devices():
    logger.info("Entering get_pci_devices...")
    pci = request.args.get('pci', '')
    logger.info("pci: %s" % pci)

    try:
        usbs = []
        for i in glob.glob('/sys/bus/usb/devices/usb*'):
            usbs.append(i)

        pumaps = {}
        for i in sorted(usbs):
            command = "readlink %s" % i
            p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            k = os.path.dirname(''.join(p.stdout.readlines()).strip())[-12:]
            if k not in pumaps.keys():
                pumaps[k] = []
            pumaps[k].append(os.path.basename(i))

        udmaps = {}
        command = "lsusb"
        p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        for i in p.stdout.readlines():
            i = i.strip()
            if not i:
                continue
            k = 'usb'+str(int(i[4:7]))
            if k not in udmaps.keys():
                udmaps[k] = []
            udmaps[k].append(i[33:])

        rdevices = ''
        #for i in sorted(pumaps.keys()):
        for i in pci.split(','):
            if not i.strip():
                continue
            try:
                rdevices += i + '\n'
                i = '0000:' + i
                for j in sorted(pumaps[i]):
                    rdevices += '    ' + j + '\n'
                    for k in sorted(udmaps[j]):
                        rdevices += '        ' + k + '\n'
            except Exception, e2:
                pass

        logger.info(rdevices)
        return json.dumps({'code':'True', 'message':rdevices})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})


def connect_idv():
    logger.info("Entering connect_idv...")
    name = request.form.get('name',  '')
    logger.info("name: %s" % name)

    try:
        #查找指定名称的IDV桌面
        idv = queryIdvByName(name)
        if not idv:
            raise Exception('IDV desktop not found!')

        #如果命令没有执行，则执行之
        command = 'ps -ef | grep qemu-system-x86_64 | grep %s' % idv['name']
        p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        if not ''.join(p.stdout.readlines()).strip():
            command = prepareCommand(idv)
            p = subprocess.Popen(command, shell=True)
            p.communicate()
            time.sleep(5)

        command = '%s/connect_via_idv.sh %s' % (SCRIPT_DIR, idv['port'])
        p = subprocess.Popen(command, shell=True)
        p.communicate()
 
        logger.info('Done!')
        return json.dumps({'code':'True', 'message':'Done!'})
    except Exception, e:
        logger.error(str(e))
        return json.dumps({'code':'False', 'message':str(e)})

