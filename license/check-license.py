# -*- encoding: utf-8 -*-
import os
import sys
from M2Crypto.EVP import Cipher
from base64 import b64encode, b64decode

iv = "0123456789abcdeffedcba9876543210"
passKey = "password4virtfannaftriv4drowssap"

def __cipher(msg, op):
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


if __name__ == '__main__':
    if not os.path.isfile('macs.txt'):
        exit()
    #else:
    #    os.popen('sudo apt -y install dos2unix')
    #    os.popen('sudo dos2unix ./macs.txt')

    f = open(sys.argv[1], 'r')
    for line in f.readlines():
        print decrypt(line.strip())
    f.close()

