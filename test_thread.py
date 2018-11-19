import threading
from threading import Thread
import subprocess
import time

def __copy(sfile, dfile):
    for i in range(0, 5):
        print "Sleeping"
        time.sleep(3)


if __name__ == '__main__':
    thread = Thread(target=__copy, name="__copy", args=('/home/vClassTerminal/make-iso.sh', '/tmp/'))
    thread.setDaemon(True)
    thread.start()
    #print thread.ident

    while True:
        quit = True
        for thread in threading.enumerate():
            time.sleep(1)
            print "Checking"
            print thread.name
            if thread.name == "__copy":
                quit = False
        if quit:
            break

    print "Exiting"
    #thread.join()
    #while True:
    #    print "Checking"
    #    time.sleep(1)
    #    if not thread.is_alive():
    #        print "Exiting"
    #        break
