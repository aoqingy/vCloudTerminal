#!/usr/bin/env python
# -*- coding : utf-8 -*-

try:
    import xml.etree.cElementTree as ET
except:
    import xml.etree.ElementTree as ET

def _parse_node(node, coding='UTF-8'):
    tree = {}
    if node.attrib:
        for k, v in node.attrib.items():
            tree['@'+k] = v

    for child in node.getchildren():
        ctag = child.tag
        cattr = child.attrib
        ctext = child.text.strip().encode(coding) if child.text is not None else ''
        ctree = _parse_node(child)

        cdict = {ctag: ctree if ctree  else ctext}

        if ctag not in tree:
            tree.update(cdict)
            continue

        curtree = tree[ctag]
        if not isinstance(curtree, list):
            if not isinstance(curtree, dict):
                curtree = {}
            tree[ctag] = [curtree]

        tree[ctag].append(ctree)

    return tree

def parse(xml):
    EL = ET.fromstring(xml)

    return {EL.tag: _parse_node(EL)}



if __name__ == '__main__':

    vm = '''
<vm href="/ovirt-engine/api/vms/7724f03f-3aa2-4b6b-8916-8f528f99e074" id="7724f03f-3aa2-4b6b-8916-8f528f99e074">
    <actions>
        <link href="/ovirt-engine/api/vms/7724f03f-3aa2-4b6b-8916-8f528f99e074/previewsnapshot" rel="previewsnapshot"/>
        <link href="/ovirt-engine/api/vms/7724f03f-3aa2-4b6b-8916-8f528f99e074/migrate" rel="migrate"/>
        <link href="/ovirt-engine/api/vms/7724f03f-3aa2-4b6b-8916-8f528f99e074/logon" rel="logon"/>
        <link href="/ovirt-engine/api/vms/7724f03f-3aa2-4b6b-8916-8f528f99e074/maintenance" rel="maintenance"/>
        <link href="/ovirt-engine/api/vms/7724f03f-3aa2-4b6b-8916-8f528f99e074/clone" rel="clone"/>
        <link href="/ovirt-engine/api/vms/7724f03f-3aa2-4b6b-8916-8f528f99e074/thawfilesystems" rel="thawfilesystems"/>
        <link href="/ovirt-engine/api/vms/7724f03f-3aa2-4b6b-8916-8f528f99e074/commitsnapshot" rel="commitsnapshot"/>
        <link href="/ovirt-engine/api/vms/7724f03f-3aa2-4b6b-8916-8f528f99e074/undosnapshot" rel="undosnapshot"/>
        <link href="/ovirt-engine/api/vms/7724f03f-3aa2-4b6b-8916-8f528f99e074/cancelmigration" rel="cancelmigration"/>
        <link href="/ovirt-engine/api/vms/7724f03f-3aa2-4b6b-8916-8f528f99e074/reboot" rel="reboot"/>
        <link href="/ovirt-engine/api/vms/7724f03f-3aa2-4b6b-8916-8f528f99e074/freezefilesystems" rel="freezefilesystems"/>
        <link href="/ovirt-engine/api/vms/7724f03f-3aa2-4b6b-8916-8f528f99e074/reordermacaddresses" rel="reordermacaddresses"/>
        <link href="/ovirt-engine/api/vms/7724f03f-3aa2-4b6b-8916-8f528f99e074/ticket" rel="ticket"/>
        <link href="/ovirt-engine/api/vms/7724f03f-3aa2-4b6b-8916-8f528f99e074/detach" rel="detach"/>
        <link href="/ovirt-engine/api/vms/7724f03f-3aa2-4b6b-8916-8f528f99e074/export" rel="export"/>
        <link href="/ovirt-engine/api/vms/7724f03f-3aa2-4b6b-8916-8f528f99e074/shutdown" rel="shutdown"/>
        <link href="/ovirt-engine/api/vms/7724f03f-3aa2-4b6b-8916-8f528f99e074/start" rel="start"/>
        <link href="/ovirt-engine/api/vms/7724f03f-3aa2-4b6b-8916-8f528f99e074/stop" rel="stop"/>
        <link href="/ovirt-engine/api/vms/7724f03f-3aa2-4b6b-8916-8f528f99e074/suspend" rel="suspend"/>
    </actions>
    <name>aaa</name>
    <link href="/ovirt-engine/api/vms/7724f03f-3aa2-4b6b-8916-8f528f99e074/affinitylabels" rel="affinitylabels"/>
    <link href="/ovirt-engine/api/vms/7724f03f-3aa2-4b6b-8916-8f528f99e074/katelloerrata" rel="katelloerrata"/>
    <link href="/ovirt-engine/api/vms/7724f03f-3aa2-4b6b-8916-8f528f99e074/permissions" rel="permissions"/>
    <link href="/ovirt-engine/api/vms/7724f03f-3aa2-4b6b-8916-8f528f99e074/tags" rel="tags"/>
    <link href="/ovirt-engine/api/vms/7724f03f-3aa2-4b6b-8916-8f528f99e074/snapshots" rel="snapshots"/>
    <link href="/ovirt-engine/api/vms/7724f03f-3aa2-4b6b-8916-8f528f99e074/applications" rel="applications"/>
    <link href="/ovirt-engine/api/vms/7724f03f-3aa2-4b6b-8916-8f528f99e074/hostdevices" rel="hostdevices"/>
    <link href="/ovirt-engine/api/vms/7724f03f-3aa2-4b6b-8916-8f528f99e074/numanodes" rel="numanodes"/>
    <link href="/ovirt-engine/api/vms/7724f03f-3aa2-4b6b-8916-8f528f99e074/reporteddevices" rel="reporteddevices"/>
    <link href="/ovirt-engine/api/vms/7724f03f-3aa2-4b6b-8916-8f528f99e074/diskattachments" rel="diskattachments"/>
    <link href="/ovirt-engine/api/vms/7724f03f-3aa2-4b6b-8916-8f528f99e074/nics" rel="nics"/>
    <link href="/ovirt-engine/api/vms/7724f03f-3aa2-4b6b-8916-8f528f99e074/sessions" rel="sessions"/>
    <link href="/ovirt-engine/api/vms/7724f03f-3aa2-4b6b-8916-8f528f99e074/graphicsconsoles" rel="graphicsconsoles"/>
    <link href="/ovirt-engine/api/vms/7724f03f-3aa2-4b6b-8916-8f528f99e074/cdroms" rel="cdroms"/>
    <link href="/ovirt-engine/api/vms/7724f03f-3aa2-4b6b-8916-8f528f99e074/watchdogs" rel="watchdogs"/>
    <link href="/ovirt-engine/api/vms/7724f03f-3aa2-4b6b-8916-8f528f99e074/statistics" rel="statistics"/>
    <bios>
        <boot_menu>
            <enabled>false</enabled>
        </boot_menu>
    </bios>
    <cpu>
        <architecture>x86_64</architecture>
        <topology>
            <cores>1</cores>
            <sockets>1</sockets>
            <threads>1</threads>
        </topology>
    </cpu>
    <cpu_shares>0</cpu_shares>
    <creation_time>2017-06-12T17:18:48.144-04:00</creation_time>
    <delete_protected>false</delete_protected>
    <display>
        <allow_override>false</allow_override>
        <copy_paste_enabled>true</copy_paste_enabled>
        <disconnect_action>LOCK_SCREEN</disconnect_action>
        <file_transfer_enabled>true</file_transfer_enabled>
        <monitors>1</monitors>
        <single_qxl_pci>false</single_qxl_pci>
        <smartcard_enabled>false</smartcard_enabled>
        <type>spice</type>
    </display>
    <high_availability>
        <enabled>false</enabled>
        <priority>0</priority>
    </high_availability>
    <io>
        <threads>0</threads>
    </io>
    <large_icon href="/ovirt-engine/api/icons/df384361-3adf-447b-9537-efa384116339" id="df384361-3adf-447b-9537-efa384116339"/>
    <memory>1073741824</memory>
    <memory_policy>
        <guaranteed>1073741824</guaranteed>
        <max>4294967296</max>
    </memory_policy>
    <migration>
        <auto_converge>inherit</auto_converge>
        <compressed>inherit</compressed>
    </migration>
    <migration_downtime>-1</migration_downtime>
    <origin>ovirt</origin>
    <os>
        <boot>
            <devices>
                <device>hd</device>
            </devices>
        </boot>
        <type>other</type>
    </os>
    <small_icon href="/ovirt-engine/api/icons/634c4ab8-0b05-4a5e-9375-85ae4f8ecfb4" id="634c4ab8-0b05-4a5e-9375-85ae4f8ecfb4"/>
    <sso>
        <methods>
            <method id="guest_agent"/>
        </methods>
    </sso>
    <start_paused>false</start_paused>
    <stateless>false</stateless>
    <time_zone>
        <name>Etc/GMT</name>
    </time_zone>
    <type>desktop</type>
    <usb>
        <enabled>false</enabled>
    </usb>
    <cluster href="/ovirt-engine/api/clusters/00000002-0002-0002-0002-00000000017a" id="00000002-0002-0002-0002-00000000017a"/>
    <cpu_profile href="/ovirt-engine/api/cpuprofiles/5902b463-028d-0072-0174-0000000000b5" id="5902b463-028d-0072-0174-0000000000b5"/>
    <quota id="5902b479-01e9-02e0-0332-00000000029d"/>
    <next_run_configuration_exists>false</next_run_configuration_exists>
    <numa_tune_mode>interleave</numa_tune_mode>
    <placement_policy>
        <affinity>migratable</affinity>
    </placement_policy>
    <status>down</status>
    <stop_time>2017-06-12T17:18:48.149-04:00</stop_time>
    <original_template href="/ovirt-engine/api/templates/00000000-0000-0000-0000-000000000000" id="00000000-0000-0000-0000-000000000000"/>
    <template href="/ovirt-engine/api/templates/00000000-0000-0000-0000-000000000000" id="00000000-0000-0000-0000-000000000000"/>
</vm>
'''
    test = '<vms>' + vm * 2000 + '</vms>'
    result = parse(test)
    print(result)
    print
