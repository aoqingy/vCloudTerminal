'''
A Simple Utility for Boot Configuration Data (BCD) of Windows Vista.
Usage:
    - To list the entries of BCD
    % python bcd.py -l -s <BCD file>
    - To change the default boot loader specified by GUID
    % python bcd.py -d <GUID> -s <BCD file>
This utility is EXPERIMENTAL without ANY WARRANTY.
Sse also:
    - hivex from libguestfs <http://libguestfs.org/>
    - MSDN Documentation about BCD
        <http://msdn.microsoft.com/en-us/windows/hardware/gg463059.aspx>
        <http://msdn.microsoft.com/en-us/library/cc441427(v=vs.85).aspx>
'''

from hivex import Hivex
import optparse


GUID_WINDOWS_BOOTMGR = '{9dea862c-5cdd-4e70-acc1-f32b344d4795}'
ELM_LIBRARY_DESC = '12000004'
ELM_BOOTMGR_DEFAULT = '23000003'
ELM_BOOTMGR_DISPORDER = '24000001'


class BCDObject:
    def __init__(self, hive, handle):
        self.hive = hive
        self.handle = handle

        ch = dict(map(
                lambda h:(hive.node_name(h), h),
                hive.node_children(handle)))
        
        desc_h = ch['Description']
        (type_h,) = hive.node_values(desc_h)
        self.type = hive.value_dword(type_h)

        self.elms = dict(map(
                lambda h:(hive.node_name(h), h),
                hive.node_children(ch['Elements'])))

    def uuid(self):
        return self.hive.node_name(self.handle)

    def value_string(self, key):
        h = self.elms[key]
        (elm_h,) = self.hive.node_values(h)
        return self.hive.value_string(elm_h)

    def value_dword(self, key):
        h = self.elms[key]
        (elm_h,) = self.hive.node_values(h)
        return self.hive.value_dword(elm_h)

    def value_multstring(self, key):
        h = self.elms[key]
        (elm_h,) = self.hive.node_values(h)
        return self.hive.value_multiple_strings(elm_h)

    def set_value_string(self, key, value):
        h = self.elms[key]
        (elm_h,) = self.hive.node_values(h)
        data = dict(
            t = self.hive.value_type(elm_h)[0],
            key = self.hive.value_key(elm_h),
            value = value.decode('utf-8').encode('utf-16le')
            )
        self.hive.node_set_value(h, data)


class BCDRoot:
    def __init__(self, filename):
        self.hive = Hivex(filename, write=True)
        
        r = self.hive.root()
        meta = dict(map(
                lambda h:(self.hive.node_name(h), h),
                self.hive.node_children(r)))
        self.objects = dict(map(
                lambda h: (self.hive.node_name(h), BCDObject(self.hive, h)),
                self.hive.node_children(meta['Objects'])))


    def objects(self):
        return self.objects.values()

    def object(self, uuid):
        return self.objects[uuid]

    def commit(self, filename):
        self.hive.commit(filename)


def list_loader(filename):
    root = BCDRoot(filename)
    mgr = root.object(GUID_WINDOWS_BOOTMGR)
    uuids = mgr.value_multstring(ELM_BOOTMGR_DISPORDER)
    try:
        u_def = mgr.value_string(ELM_BOOTMGR_DEFAULT)
    except:
        u_def = ''
    rloader = ''
    for uuid in uuids:
        if not uuid:
            continue
        loader = root.object(uuid)
        desc = loader.value_string(ELM_LIBRARY_DESC)
        isdef = ''
        if uuid == u_def:
            isdef = '(DEF)'
        if rloader != '':
            rloader += '\n'
        rloader += "%s  \"%s\"  %s" % (uuid, desc, isdef)

    rloaders = []
    for loader in rloader.split('\n'):
        loader = loader.split('  ')
        rloader = {}
        rloader['uuid']    = loader[0][1:-1]
        rloader['name']    = loader[1][1:-1]
        try:
            rloader['def'] = loader[2][1:-1]
        except:
            rloader['def'] = ''
        rloaders.append(rloader)

    return rloaders


def change_default(filename, uuid):
    #root = BCDRoot(filename)
    #mgr = root.object(GUID_WINDOWS_BOOTMGR)
    #mgr.set_value_string(ELM_BOOTMGR_DEFAULT, uuid)
    #root.commit(None)
    pass


def main():
    parser = optparse.OptionParser()
    parser.add_option('--default', '-d', default=None)
    parser.add_option('--list', '-l', action='store_true', default=False)
    parser.add_option('--store', '-s', default=None)
    (opt, args) = parser.parse_args()

    if opt.list:
        print list_loader(opt.store);
    elif opt.default:
        change_default(opt.store, opt.default)

if __name__ == '__main__':
    main()
