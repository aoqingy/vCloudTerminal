import os
import stat
import paramiko
 
class SSHConnection(object):
    #----------------------------------------------------------------------
    def __init__(self, host, username, password, port=22):
        """Initialize and setup connection"""
        self.sftp = None
        self.sftp_open = False
 
        # open SSH Transport stream
        #self.transport = paramiko.Transport((host, port))
 
        #self.transport.connect(username=username, password=password)
        self.ssh = paramiko.SSHClient()
        self.ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        self.ssh.connect(host, port, username, password)

    #----------------------------------------------------------------------
    def run(self, command):
        stdin, stdout, stderr = self.ssh.exec_command(command)
        return {'stdout':stdout.read(), 'stderr':stderr.read()}
        #return stdout
 
    #----------------------------------------------------------------------
    def _openSFTPConnection(self):
        """
        Opens an SFTP connection if not already open
        """
        if not self.sftp_open:
            self.sftp = self.ssh.open_sftp()
            self.sftp_open = True

    #----------------------------------------------------------------------
    def stat(self, remote_path):
        """
        """
        self._openSFTPConnection()
        return self.sftp.stat(remote_path)
 
    #----------------------------------------------------------------------
    def get(self, remote_path, local_path=None):
        """
        Copies a file from the remote host to the local host.
        """
        self._openSFTPConnection()        
        self.sftp.get(remote_path, local_path)        
 
    #----------------------------------------------------------------------
    def put(self, local_path, remote_path=None):
        """
        Copies a file from the local host to the remote host
        """
        self._openSFTPConnection()
        self.sftp.put(local_path, remote_path)

    #----------------------------------------------------------------------
    def listdir_attr(self, remote_path):
        self._openSFTPConnection()
        return self.sftp.listdir_attr(remote_path)

    #----------------------------------------------------------------------
    def open(self, filename, mode):
        self._openSFTPConnection()
        return self.sftp.open(filename, mode)
 
    #----------------------------------------------------------------------
    def close(self):
        """
        Close SFTP connection and ssh connection
        """
        if self.sftp_open:
            self.sftp.close()
            self.sftp_open = False
        self.ssh.close()

    #----------------------------------------------------------------------
    def __get_local_files(self, local_path):
        files = list()

        for x in os.listdir(local_path):
            filename = os.path.join(local_path, x)
            if os.path.isdir(filename):
                files.extend(self.__get_local_files(filename))
            else:
                files.append(filename)

        return files

    def __get_remote_files(self, remote_path):
        files = list()

        for x in self.listdir_attr(remote_path):
            filename = remote_path + x.filename
            if stat.S_ISDIR(x.st_mode):
                files.extend(self.__get_remote_files(filename+'/'))
            else:
                files.append(filename)
        return files

    #----------------------------------------------------------------------
    def put_dir(self, local_path, remote_path=None):
        if local_path[-1] != '/':
            local_path = local_path + '/'

        if remote_path and remote_path[-1] != '/':
            remote_path = remote_path + '/'

        if not remote_path:
            remote_path = local_path

        for x in self.__get_local_files(local_path):
            remote_filename = remote_path + x[len(local_path):]
            print "Transfering %s to %s..." % (x, remote_filename)
            self.run('mkdir -p %s' % os.path.dirname(remote_filename))
            self.put(x, remote_filename)

    #----------------------------------------------------------------------
    def get_dir(self, remote_path, local_path=None):
        if remote_path[-1] != '/':
            remote_path = remote_path + '/'

        if local_path and local_path[-1] != '/':
            local_path = local_path + '/'

        if not local_path:
            local_path = remote_path

        for x in self.__get_remote_files(remote_path):
            local_filename = local_path + x[len(remote_path):]
            print "Transfering %s to %s..." % (x, local_filename)
            os.system('mkdir -p %s' % os.path.dirname(local_filename))
            self.get(x, local_filename)


def __start(host, username, password):
    print host
    print username
    print password
    command  = "/root/bittorrent/bttrack --port 6969 --dfile /tmp/dstate --logfile /tmp/tracker.log &"
    print command
    try:
        ssh = SSHConnection(host, username, password)
        print ssh
        rs = ssh.run(command)
        print rs
        ssh.close()
    except Exception, e:
        print str(e)
    
 
if __name__ == "__main__":
    host     = "192.168.0.51"
    username = "root"
    password = "123456"
 
    ssh = SSHConnection(host, username, password)
    rs = ssh.stat('/var/www/vfd/image.py').st_size
    #rs = ssh.run('chroot /mnt/temp /bin/bash -c "touch /etc/iscsi/iscsi.initramfs"')
    #rs = ssh.run('chroot /mnt/temp /bin/bash -c \'echo "InitiatorName=%s%s" > /etc/iscsi/initiatorname.iscsi\'' % ('aaa', '106'))
    #rs = ssh.run('chroot /mnt/temp /bin/bash -c \'echo "iscsi" >> /etc/initramfs-tools/modules\'')
    #rs = ssh.run('chroot /mnt/temp /bin/bash -c \'/bin/hostname ubuntu%s\'' % '106')
    #rs = ssh.run('chroot /mnt/temp /bin/bash -c \'/bin/mount -t proc none /proc\'')
    #rs = ssh.run('chroot /mnt/temp /bin/bash -c \'echo "nameserver 114.114.114.115" >> /etc/resolv.conf\'')
    ssh.close()
    print rs

    #ssh = SSHConnection(host, username, password)

    #print str(ssh.run("ls -l /root/*.py"))
    #ssh.get("/var/log/ovirt-engine/engine.log-20151020.gz", "/root/a.gz")
#    a = ssh.run("qemu-img info c.vmdk")
#    found = 'False'
#    size = None
#    for x in a['stdout'].strip().split('\n'):
#        y = x.split(': ')
#        if y[0] == 'file format' and y[1] == 'vmdk':
#            found = 'True'
#        if y[0] == 'virtual size':
#            size = y[1].split(' (')[1].split(' bytes)')[0]
#
#    if found == 'False' or size is None:
#        print 'error'
#
#    print size
#    print ssh.run("ls -l /tmp/")
    #ssh.put_dir("/tmp/bcd/", "/tmp/bcd/")
#    from threading import Thread
#    thread = Thread(target=__start, args=(host, username, password))
#    thread.setDaemon(True)
#    thread.start()
#    thread.join()
    #command  = "/root/bittorrent/bttrack --port 6969 --dfile /tmp/dstate --logfile /tmp/tracker.log &"
    #print command
    #rs = ssh.run(command)
    #print rs

    #ssh.close()
