#!/usr/bin/python
#-*-coding:utf-8 -*-
import os
import time
from flask import Flask
from celery import Celery, platforms
platforms.C_FORCE_ROOT=True   #允许root权限运行celery

def make_celery(app):
    celery = Celery('hello',
        broker=app.config['CELERY_BROKER_URL'],
        backend=app.config['CELERY_RESULT_BACKEND']
    )
    celery.conf.update(app.config)
    TaskBase = celery.Task
    class ContextTask(TaskBase):
        abstract = True
        def __call__(self, *args, **kwargs):
            with app.app_context():
                return TaskBase.__call__(self, *args, **kwargs)
    celery.Task = ContextTask
    return celery

app = Flask(__name__)
app.config.from_object(__name__)
app.secret_key = 'A0Zr98j/3yX R~ZWJ!jmN]LWX/,?RT'
app.config['CELERY_BROKER_URL']     = 'redis://localhost:6379/0'
app.config['CELERY_RESULT_BACKEND'] = 'redis://localhost:6379/1'

celery = make_celery(app)

@celery.task(bind=True)
#这个函数检查目标文件拷贝状态，它传入目标文件的完整路径和目标大小，计算文件的实际大小百分比，直到两者相等
def CheckFileSize(self, dfile, dsize):
    while True:
        time.sleep(0.5)
        if not os.path.exists(dfile):
            continue
        rsize = os.stat(dfile).st_size
        percent = int(float(rsize) * 100 / float(dsize))
        self.update_state(state='PROGRESS', meta={'percent': percent})
        if int(rsize) == int(dsize):
            break


def __getDirSize(dpath):
    total_size = 0
    for dirpath, dirnames, filenames in os.walk(dpath):
        for f in filenames:
            fp = os.path.join(dirpath, f)
            total_size += os.path.getsize(fp)
    return total_size


@celery.task(bind=True)
def CheckDirSize(self, dpath, dsize):
    while True:
        time.sleep(0.5)
        if not os.path.exists(dpath):
            continue
        rsize = __getDirSize(dpath)
        percent = int(float(rsize) * 100 / float(dsize))
        self.update_state(state='PROGRESS', meta={'percent': percent})
        if int(rsize) == int(dsize):
            break

