#!/usr/bin/python
#-*-coding:utf-8 -*-
import os
import logging
import logging.handlers
from flask import Flask

app = Flask(__name__)

#BASE_DIR      = os.path.abspath(os.path.dirname(__file__))
BASE_DIR      = "/var/www/vfd"
SCRIPT_DIR    = BASE_DIR + "/script"
LOG_DIR       = BASE_DIR + "/log"
COUNTER_DIR   = BASE_DIR + "/counter"

LOG_FILE      = BASE_DIR + "/log/vfd.log"

DB_SCRIPT     = BASE_DIR + "/vfd.sql"
DB_FILE       = BASE_DIR + "/vfd.db"

USE_TIME      = BASE_DIR + "/counter/USE_TIME"
MGMT_UPDIR    = "/tmp/management"
IMAGE_DIR     = "/home/image/"               #BT文件保存路径
IMAGE_STAT    = BASE_DIR + "/log/image.stat"
#ITALC_KEYDIR = "/etc/italc/keys/public/teacher"

UBUNTU_LOGO_FILE = "/usr/share/plymouth/themes/ubuntu-logo/ubuntu-logo.png"

if not os.path.isdir(LOG_DIR):
    os.makedirs(LOG_DIR)
if not os.path.isdir(MGMT_UPDIR):
    os.makedirs(MGMT_UPDIR)
if not os.path.isdir(COUNTER_DIR):
    os.makedirs(COUNTER_DIR)
if not os.path.isfile(USE_TIME):
    f = open(USE_TIME, 'w')
    f.close()

formatter = logging.Formatter('[%(asctime)s] {%(filename)s:%(lineno)-4d} %(levelname)-5s - %(message)s','%m-%d %H:%M:%S')
logger = logging.getLogger()
fileTimeHandler = logging.handlers.TimedRotatingFileHandler(filename=LOG_FILE, when='midnight', backupCount=3)
fileTimeHandler.suffix = "%Y%m%d.log"  #设置 切分后日志文件名的时间格式 默认 filename+"." + suffix 如果需要更改 需要改logging 源码
fileTimeHandler.setFormatter(formatter)
logging.basicConfig(level = logging.INFO)
fileTimeHandler.setFormatter(formatter)
logger.addHandler(fileTimeHandler)

