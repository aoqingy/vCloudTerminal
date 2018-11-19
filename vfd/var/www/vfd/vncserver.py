#!/usr/bin/python
#-*-coding:utf-8 -*-
import sys, os 
from const   import *
from utility import *

def main():
    """ A demo daemon main routine """
    try:
        rv = query_db('select passwd from vfpswd where id="1"')
        password = rv[0]['passwd']
        os.popen('/var/www/vfd/script/vnc_server.sh -rfbauth /etc/x11vnc.pass &') 
    except:
        os.popen('/var/www/vfd/script/vnc_server.sh &')


if __name__ == "__main__":
    # do the UNIX double-fork magic, see Stevens' "Advanced 
    # Programming in the UNIX Environment" for details (ISBN 0201563177)
    try: 
        pid = os.fork() 
        if pid > 0:
            # exit first parent
            sys.exit(0) 
    except OSError, e: 
        print >>sys.stderr, "fork #1 failed: %d (%s)" % (e.errno, e.strerror) 
        sys.exit(1)

    # decouple from parent environment
    os.chdir("/") 
    os.setsid() 
    os.umask(0) 

    # do second fork
    try: 
        pid = os.fork() 
        if pid > 0:
            # exit from second parent, print eventual PID before
            print "Daemon PID %d" % pid 
            sys.exit(0) 
    except OSError, e: 
        print >>sys.stderr, "fork #2 failed: %d (%s)" % (e.errno, e.strerror) 
        sys.exit(1) 

    # start the daemon main loop
    main()
