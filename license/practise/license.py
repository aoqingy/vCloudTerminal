from crypt import decrypt_from_file

LICENSE_FILE = 'a.txt'

def checkLicense(licensefile=LICENSE_FILE):
    try:
        decrypted = decrypt_from_file(licensefile)
        return decrypted
    except Exception, e:
        print('Fail to check : %s' % str(e))
        return 0

if __name__ == '__main__':
    print(checkLicense())
