#!/usr/bin/python
# -*- coding: utf-8 -*-
import os
import sys
import ssl
import time
import urllib
import urllib2
from xml2dict import parse
#from xmltodict import parse
from threading import Thread


def request2virtengine(url, username, password, method, data, headers):
    try:
        if hasattr(ssl, '_create_unverified_context'):
            ssl._create_default_https_context = ssl._create_unverified_context

        passman = urllib2.HTTPPasswordMgrWithDefaultRealm()
        passman.add_password(None, url, username, password)
        authhandler = urllib2.HTTPBasicAuthHandler(passman)
        opener = urllib2.build_opener(authhandler)
        urllib2.install_opener(opener)

        request = urllib2.Request(url, data, headers)
        request.get_method = lambda: method

        response = urllib2.urlopen(request).read()
        return parse(response)
    except Exception, e:
        error_message = e.read()
        raise Exception(error_message)


#################################################################
#
# Verify Engine API
#
#################################################################
#ca = fetchCA(ENGINE_IP)
#ca = ca.replace("\n", "\\n")
def fetchCA(engine):
    try:
        url = "https://" + engine + "/services/pki-resource?resource=ca-certificate&format=X509-PEM-CA"
        req = urllib2.Request(url)
        res = urllib2.urlopen(req).read()
        return res
    except Exception, e:
        try:
            url = "https://" + engine + "/ca.crt"
            req = urllib2.Request(url)
            res = urllib2.urlopen(req).read()
            return res
        except Exception, e:
            return None
    #ca = open(cafile, "w" )
    #ca.write(res)
    #ca.close()


def verifyAPI(engine, username, password):
    url = "https://" + engine + "/api/"
    return request2virtengine(url, username, password, 'GET', '', {})


#这个函数检查给定地址是否为有效的管理引擎。若是，返回访问入口点（后缀）；否则抛出例外
def locateAPI(rvs, engine, postfix, username, password):
    try:
        url = "https://" + engine + '/' + postfix + "/api/"
        response = request2virtengine(url, username, password, 'GET', '', {})
        rvs.append(postfix)
    except Exception, e:
        pass


def getAccessPostfix(engine, username, password):
    postfixes = ['', 'virtfan-engine', 'ovirt-engine']
    rvs = []
    threads = []
    for postfix in postfixes:
        thread = Thread(target=locateAPI, args=(rvs, engine, postfix, username, password))
        threads.append(thread)

    for thread in threads:
        thread.setDaemon(True)
        thread.start()

    for thread in threads:
        thread.join()

    if len(rvs) == 0:
        raise Exception("API access failed!")

    return rvs[0]


ENGINE_VERSION = None
def getVersion(engine, username, password, cache=True):
    global ENGINE_VERSION
    if cache == True and ENGINE_VERSION != None:
        return ENGINE_VERSION
    #print "#################################################################"
    #print "#                                                                "
    #print "# Initializing...                                                "
    #print "#                                                                "
    #print "#################################################################"
    url = "https://" + engine + "/api/"
    response = request2virtengine(url, username, password, 'GET', '', {})
    try:
        major = response['api']['product_info']['version']['major']
        minor = response['api']['product_info']['version']['minor']
    except Exception, e:
        major = response['api']['product_info']['version']['@major']
        minor = response['api']['product_info']['version']['@minor']
    ENGINE_VERSION = {'major': major, 'minor': minor}
    return ENGINE_VERSION


#################################################################
#
# Common functions
#
#################################################################
def requestResources(engine, username, password, resources):
    url = "https://%s/api/%s/" % (engine, resources)
    return request2virtengine(url, username, password, 'GET', '', {'filter':'true', 'All-Content': 'true'})


def requestResource(engine, username, password, resources, resource_id):
    url = "https://%s/api/%s/%s" % (engine, resources, resource_id)
    return request2virtengine(url, username, password, 'GET', '', {})


def requestResourceChildren(engine, username, password, resources, resource_id, children):
    url = "https://%s/api/%s/%s/%s" % (engine, resources, resource_id, children)
    return request2virtengine(url, username, password, 'GET', '', {})


def requestResourceChild(engine, username, password, resources, resource_id, children, child_id):
    url = "https://%s/api/%s/%s/%s/%s" % (engine, resources, resource_id, children, child_id)
    return request2virtengine(url, username, password, 'GET', '', {})


def queryResources(engine, username, password, resources, query):
    url = "https://%s/api/%s?%s" % (engine, resources, urllib.urlencode({'search':query}))
    return request2virtengine(url, username, password, 'GET', '', {})


def queryResourceChildren(engine, username, password, resources, resource_id, children, query):
    url = "https://%s/api/%s/%s/%s?%s" % (engine, resources, resource_id, children, urllib.urlencode({'search':query}))
    return request2virtengine(url, username, password, 'GET', '', {})


def parseResponse(response, version, rnames, rname, parseResource):
    rresources = []
    try:
        resources = response[rnames][rname]
        try:
            rresources.append(parseResource(resources, version))	#只有一个资源
        except Exception, e2:
            for resource in resources:					#有多个资源
                rresources.append(parseResource(resource, version))
    except Exception, e:						#没有资源
        pass
    return rresources


def getResources(engine, username, password, resources, rnames, rname, parseCallback):
    version = getVersion(engine, username, password)
    response = requestResources(engine, username, password, resources)
    return parseResponse(response, version, rnames, rname, parseCallback)


def getResource(engine, username, password, resources, resource_id, rname, parseCallback):
    version = getVersion(engine, username, password)
    response = requestResource(engine, username, password, resources, resource_id)
    return parseCallback(response[rname], version)


def getResourceChildren(engine, username, password, resources, resource_id, children, rnames, rname, parseCallback):
    version = getVersion(engine, username, password)
    response = requestResourceChildren(engine, username, password, resources, resource_id, children)
    return parseResponse(response, version, rnames, rname, parseCallback)


def searchResources(engine, username, password, resources, query, rnames, rname, parseCallback):
    version = getVersion(engine, username, password)
    response = queryResources(engine, username, password, resources, query)
    return parseResponse(response, version, rnames, rname, parseCallback)


def searchResourceChildren(engine, username, password, resources, resource_id, children, query, rnames, rname, parseCallback):
    version = getVersion(engine, username, password)
    response =  queryResourceChildren(engine, username, password, resources, resource_id, children, query)
    return parseResponse(response, version, rnames, rname, parseCallback)


#################################################################
#
# List Resources
#
#################################################################
#<link href="/ovirt-engine/api/events" rel="events"/>
#<link href="/ovirt-engine/api/icons" rel="icons"/>
#<link href="/ovirt-engine/api/instancetypes" rel="instancetypes"/>
#<link href="/ovirt-engine/api/storageconnections" rel="storageconnections"/>
#<link href="/ovirt-engine/api/vnicprofiles" rel="vnicprofiles"/>
#<link href="/ovirt-engine/api/diskprofiles" rel="diskprofiles"/>
#<link href="/ovirt-engine/api/cpuprofiles" rel="cpuprofiles"/>
#<link href="/ovirt-engine/api/schedulingpolicyunits" rel="schedulingpolicyunits"/>
#<link href="/ovirt-engine/api/schedulingpolicies" rel="schedulingpolicies"/>
#<link href="/ovirt-engine/api/macpools" rel="macpools"/>
#<link href="/ovirt-engine/api/networkfilters" rel="networkfilters"/>
#<link href="/ovirt-engine/api/operatingsystems" rel="operatingsystems"/>
#<link href="/ovirt-engine/api/externalhostproviders" rel="externalhostproviders"/>
#<link href="/ovirt-engine/api/openstackimageproviders" rel="openstackimageproviders"/>
#<link href="/ovirt-engine/api/openstackvolumeproviders" rel="openstackvolumeproviders"/>
#<link href="/ovirt-engine/api/openstacknetworkproviders" rel="openstacknetworkproviders"/>
#<link href="/ovirt-engine/api/katelloerrata" rel="katelloerrata"/>
#<link href="/ovirt-engine/api/affinitylabels" rel="affinitylabels"/>
#<link href="/ovirt-engine/api/clusterlevels" rel="clusterlevels"/>
#<link href="/ovirt-engine/api/imagetransfers" rel="imagetransfers"/>
#<link href="/ovirt-engine/api/externalvmimports" rel="externalvmimports"/>
def getAllDataCenters(engine, username, password):
    return getResources(engine, username, password, 'datacenters', 'data_centers', 'data_center', parseDataCenter)


def getAllClusters(engine, username, password):
    return getResources(engine, username, password, 'clusters', 'clusters', 'cluster', parseCluster)


def getAllHosts(engine, username, password):
    return getResources(engine, username, password, 'hosts', 'hosts', 'host', parseHost)


def getAllNetworks(engine, username, password):
    return getResources(engine, username, password, 'networks', 'networks', 'network', parseNetwork)


def getAllStorageDomains(engine, username, password):
    return getResources(engine, username, password, 'storagedomains', 'storage_domains', 'storage_domain', parseStorageDomain)


def getAllDisks(engine, username, password):
    return getResources(engine, username, password, 'disks', 'disks', 'disk', parseDisk)


def getAllVms(engine, username, password):
    return getResources(engine, username, password, 'vms', 'vms', 'vm', parseVm)


def getAllVmPools(engine, username, password):
    return getResources(engine, username, password, 'vmpools', 'vm_pools', 'vm_pool', parseVmPool)


def getAllTemplates(engine, username, password):
    return getResources(engine, username, password, 'templates', 'templates', 'template', parseTemplate)


def getAllDomains(engine, username, password):
    return getResources(engine, username, password, 'domains', 'domains', 'domain', parseDomain)


def getAllUsers(engine, username, password):
    return getResources(engine, username, password, 'users', 'users', 'user', parseUser)


def getAllGroups(engine, username, password):
    return getResources(engine, username, password, 'groups', 'groups', 'group', parseGroup)


def getAllTags(engine, username, password):
    return getResources(engine, username, password, 'tags', 'tags', 'tag', parseTag)


def getAllBookmarks(engine, username, password):
    return getResources(engine, username, password, 'bookmarks', 'bookmarks', 'bookmark', parseBookmark)


def getAllRoles(engine, username, password):
    return getResources(engine, username, password, 'roles', 'roles', 'role', parseRole)


def getAllPermissions(engine, username, password):
    return getResources(engine, username, password, 'permissions', 'permissions', 'permission', parsePermission)


def getAllJobs(engine, username, password):
    return getResources(engine, username, password, 'jobs', 'jobs', 'job', parseJob)


#def getStorageConnections(engine, username, password):
#    response = requestResources(engine, username, password, 'storageconnections')
#    version = getVersion(engine, username, password)
#    return requestResourceIds(response, version, 'storageconnections', 'storageconnection')


#def getVnicProfiles(engine, username, password):
#    response = requestResources(engine, username, password, 'vnicprofiles')
#    version = getVersion(engine, username, password)
#    return requestResourceIds(response, version, 'vnicprofiles', 'vnicprofile')


#def getDiskProfiles(engine, username, password):
#    response = requestResources(engine, username, password, 'diskprofiles')
#    version = getVersion(engine, username, password)
#    return requestResourceIds(response, version, 'diskprofiles', 'diskprofile')


#def getCpuProfiles(engine, username, password):
#    response = requestResources(engine, username, password, 'cpuprofiles')
#    version = getVersion(engine, username, password)
#    return requestResourceIds(response, version, 'cpuprofiles', 'cpuprofile')


#def getSchedulingPolicyUnits(engine, username, password):
#    response = requestResources(engine, username, password, '')                        #aoqingy
#    version = getVersion(engine, username, password)
#    return requestResourceIds(response, version, 'schedulingpolicyunits', 'schedulingpolicyunit')


#def getSchedulingPolicies(engine, username, password):
#    response = requestResources(engine, username, password, '')                        #aoqingy
#    version = getVersion(engine, username, password)
#    return requestResourceIds(response, version, 'schedulingpolicies', 'schedulingpolicy')


#################################################################
#
# List Resource IDs
#
#################################################################
def getDataCenterIds(engine, username, password):
    return getResources(engine, username, password, 'datacenters', 'data_centers', 'data_center', parseResourceId)


def getClusterIds(engine, username, password):
    return getResources(engine, username, password, 'clusters', 'clusters', 'cluster', parseResourceId)


def getHostIds(engine, username, password):
    return getResources(engine, username, password, 'hosts', 'hosts', 'host', parseResourceId)


def getNetworkIds(engine, username, password):
    return getResources(engine, username, password, 'networks', 'networks', 'network', parseResourceId)


def getStorageDomainIds(engine, username, password):
    return getResources(engine, username, password, 'storagedomains', 'storage_domains', 'storage_domain', parseResourceId)


def getDiskIds(engine, username, password):
    return getResources(engine, username, password, 'disks', 'disks', 'disk', parseResourceId)


def getVmIds(engine, username, password):
    return getResources(engine, username, password, 'vms', 'vms', 'vm', parseResourceId)


def getVmPoolIds(engine, username, password):
    return getResources(engine, username, password, 'vmpools', 'vm_pools', 'vm_pool', parseResourceId)


def getTemplateIds(engine, username, password):
    return getResources(engine, username, password, 'templates', 'templates', 'template', parseResourceId)


def getDomainIds(engine, username, password):
    return getResources(engine, username, password, 'domains', 'domains', 'domain', parseResourceId)


def getUserIds(engine, username, password):
    return getResources(engine, username, password, 'users', 'users', 'user', parseResourceId)


def getGroupIds(engine, username, password):
    return getResources(engine, username, password, 'groups', 'groups', 'group', parseResourceId)


def getTagIds(engine, username, password):
    return getResources(engine, username, password, 'tags', 'tags', 'tag', parseResourceId)


def getBookmarkIds(engine, username, password):
    return getResources(engine, username, password, 'bookmarks', 'bookmarks', 'bookmark', parseResourceId)


def getRoleIds(engine, username, password):
    return getResources(engine, username, password, 'roles', 'roles', 'role', parseResourceId)


def getPermissionIds(engine, username, password):
    return getResources(engine, username, password, 'permissions', 'permissions', 'permission', parseResourceId)


def getJobIds(engine, username, password):
    return getResources(engine, username, password, 'jobs', 'jobs', 'job', parseResourceId)


#def getCapabilityIds(engine, username, password):
#    response = requestResources(engine, username, password, 'capabilities')
#    version = getVersion(engine, username, password)
#    return requestResourceIds(response, version, 'capabilitiess', 'capability')


#def getEventIds(engine, username, password):
#    return getResources(engine, username, password, 'events', 'events', 'event', parseResourceId)


#def getInstanceTypeIds(engine, username, password):
#    return getResources(engine, username, password, 'instancetypes', 'instancetypes', 'instancetype', parseResourceId)


#################################################################
#
# Search Resources Logic
#
#################################################################
#<link href="/ovirt-engine/api/events;from={event_id}?search={query}" rel="events/search"/>
#<link href="/ovirt-engine/api/instancetypes?search={query}" rel="instancetypes/search"/>
#支持搜索属性：Clusters、Storage、Network、name、description、local、status、comment、compability_version
def searchDataCenters(engine, username, password, query):
    return searchResources(engine, username, password, 'datacenters', query, 'data_centers', 'data_center', parseDataCenter)


#支持搜索属性：Datacenter、Storage、Cluster_network、name、description、comment、architecture
def searchClusters(engine, username, password, query):
    return searchResources(engine, username, password, 'clusters', query, 'clusters', 'cluster', parseCluster)


#支持搜索属性：Vms、Templates、Events、Users、Storage、Nic、name、comment、status、external_status、cluster、address、cpu_usage、mem_usage、network_usage、load、version、cpus、memory、cpu_speed、cpu_modal、active_vms、migrating_vms、commited_mem、tag、type、datacenter、architecture、update_available、ha_score、spm_id
def searchHosts(engine, username, password, query):
    return searchResources(engine, username, password, 'hosts', query, 'hosts', 'host', parseHost)


#支持搜索属性：Cluster_network、Host_network、Provider、name、description、comment、vlanid、stp、mtu、vmnetwork、datacenter、label、provider_name、qos_name
def searchNetworks(engine, username, password, query):
    return searchResources(engine, username, password, 'networks', query, 'networks', 'network', parseNetwork)


#支持搜索属性：Hosts、Clusters、name、status、shared_status、external_status、datacenter、type、size、used、commited、comment、description、wipe_after_delete、low_space_threshold、critical_space_threshold
def searchStorageDomains(engine, username, password, query):
    return searchResources(engine, username, password, 'storagedomains', query, 'storage_domains', 'storage_domain', parseStorageDomain)


#支持搜索属性：Datacenter、Storage、alias、name、description、provisioned_size、size、actual_size、creation_date、bootable、sharable、status、disk_type、number_of_vms、vm_names、quota、id、wipe_after_delete
def searchDisks(engine, username, password, query):
    return searchResources(engine, username, password, 'disks', query, 'disks', 'disk', parseDisk)


#支持搜索属性：Hosts、Templates、Events、Users、Storage、Vnic、name、comment、status、ip、host、fqdn、uptime、os、creationdate、address、cpu_usage、mem_usage、network_usage、memory、migration_progress_percent、apps、cluster、pool、loggedinuser、tag、datacenter、type、quota、id、description、architecture、custom_emulated_machine、custom_cpu_type、compability_level、created_by_user_id
def searchVms(engine, username, password, query):
    return searchResources(engine, username, password, 'vms', query, 'vms', 'vm', parseVm)


#支持搜索属性：name、description、type、cluster、datacenter、architecture、assigned_vm_count、running_vm_count
def searchVmPools(engine, username, password, query):
    return searchResources(engine, username, password, 'vmpools', query, 'vm_pools', 'vm_pool', parseVmPool)


#支持搜索属性：Vms、Hosts、Events、Users、Storage、Vnic、name、comment、os、creationdate、childcount、mem、description、status、cluster、datacenter、quota、architecture、version_name
def searchTemplates(engine, username, password, query):
    return searchResources(engine, username, password, 'templates', query, 'templates', 'template', parseTemplate)


#支持搜索属性：Vms、Hosts、Templates、Events、name、lastname、username、login、directory、department、tag、pool、type
def searchUsers(engine, username, password, query):
    return searchResources(engine, username, password, 'users', query, 'users', 'user', parseUser)


#支持搜索属性：grpname、name
def searchGroups(engine, username, password, query):
    return searchResources(engine, username, password, 'groups', query, 'groups', 'group', parseGroup)


def searchDomainUsers(engine, username, password, domain_id, query):
    return searchResourceChildren(engine, username, password, 'domains', domain_id, 'users', query, 'users', 'user', parseDomainUser)


def searchDomainGroups(engine, username, password, domain_id, query):
    return searchResourceChildren(engine, username, password, 'domains', domain_id, 'groups', query, 'groups', 'group', parseDomainGroup)


#################################################################
#
# Search Resource IDs Logic
#
#################################################################
def searchDataCenterIds(engine, username, password, query):
    return searchResources(engine, username, password, 'datacenters', query, 'data_centers', 'data_center', parseResourceId)


def searchClusterIds(engine, username, password, query):
    return searchResources(engine, username, password, 'clusters', query, 'clusters', 'cluster', parseResourceId)


def searchHostIds(engine, username, password, query):
    return searchResources(engine, username, password, 'hosts', query, 'hosts', 'host', parseResourceId)


def searchNetworkIds(engine, username, password, query):
    return searchResources(engine, username, password, 'networks', query, 'networks', 'network', parseResourceId)


def searchStorageDomainIds(engine, username, password, query):
    return searchResources(engine, username, password, 'storagedomains', query, 'storage_domains', 'storage_domain', parseResourceId)


def searchDiskIds(engine, username, password, query):
    return searchResources(engine, username, password, 'disks', query, 'disks', 'disk', parseResourceId)


def searchVmIds(engine, username, password, query):
    return searchResources(engine, username, password, 'vms', query, 'vms', 'vm', parseResourceId)


def searchVmPoolIds(engine, username, password, query):
    return searchResources(engine, username, password, 'vmpools', query, 'vm_pools', 'vm_pool', parseResourceId)


def searchTemplateIds(engine, username, password, query):
    return searchResources(engine, username, password, 'templates', query, 'templates', 'template', parseResourceId)


def searchUserIds(engine, username, password, query):
    return searchResources(engine, username, password, 'users', query, 'users', 'user', parseResourceId)


def searchGroupIds(engine, username, password, query):
    return searchResources(engine, username, password, 'groups', query, 'groups', 'group', parseResourceId)


def searchDomainUserIds(engine, username, password, domain_id, query):
    return searchResourceChildren(engine, username, password, 'domains', domain_id, 'users', query, 'users', 'user', parseResourceId)


def searchDomainGroupIds(engine, username, password, domain_id, query):
    return searchResourceChildren(engine, username, password, 'domains', domain_id, 'groups', query, 'groups', 'group', parseResourceId)


#################################################################
#
# Parse Resurce
#
#################################################################
def parseResourceId(resource, version):
    return resource['@id']


def parseDataCenter(datacenter, version):
    rdatacenter = {}
    rdatacenter['id']             = datacenter['@id']
    rdatacenter['name']           = datacenter['name']
    rdatacenter['description']    = datacenter['description']
    if version['major'] == '4':
        rdatacenter['status']     = datacenter['status']
    else:
        rdatacenter['status']     = datacenter['status']['state']
    rdatacenter['local']          = datacenter['local']
    rdatacenter['storage_format'] = datacenter['storage_format']
    if version['major'] == '4':
        rdatacenter['quota_mode'] = datacenter['quota_mode']
        rdatacenter['version']    = datacenter['version']['major'] + '.' + datacenter['version']['minor']
    else:
        rdatacenter['quota_mode'] = ''
        rdatacenter['version']    = datacenter['version']['@major'] + '.' + datacenter['version']['@minor']
    return rdatacenter


def parseCluster(cluster, version):
    rcluster = {}
    rcluster['id']                 = cluster['@id']
    rcluster['name']               = cluster['name']
    rcluster['description']        = cluster['description']
    rcluster['ballooning_enabled'] = cluster['ballooning_enabled']
    rcluster['datacenter_id']      = cluster['data_center']['@id']
    return rcluster


def parseHost(host, version):
    rhost = {}
    rhost['id']                       = host['@id']
    rhost['name']                     = host['name']
    rhost['address']                  = host['address']
    if version['major'] == '4':
        rhost['status']               = host['status']
    else:
        rhost['status']               = host['status']['state']
    rhost['hardware_uuid']            = host['hardware_information']['uuid']
    rhost['certificate_organization'] = host['certificate']['organization']
    rhost['certificate_subject']      = host['certificate']['subject']
    rhost['memory']                   = str(int(host['memory'])/1024/1024/1024)
    rhost['ssh_port']                 = host['ssh']['port']
    rhost['ssh_fingerprint']          = host['ssh']['fingerprint']
    if version['major'] == '4':
        rhost['cpu_sockets']          = host['cpu']['topology']['sockets']
    else:
        rhost['cpu_sockets']          = host['cpu']['topology']['@sockets']
    if version['major'] == '4':
        rhost['cpu_cores']            = host['cpu']['topology']['cores']
    else:
        rhost['cpu_cores']            = host['cpu']['topology']['@cores']
    if version['major'] == '4':
        rhost['cpu_threads']          = host['cpu']['topology']['threads']
    else:
        rhost['cpu_threads']          = host['cpu']['topology']['@threads']
    return rhost


def parseNetwork(network, version):
    rnetwork = {}
    rnetwork['id']              = network['@id']
    rnetwork['name']            = network['name']
    rnetwork['description']     = network['description']
    rnetwork['datacenter_id']   = network['data_center']['@id']
    return rnetwork


def parseStorageDomain(storagedomain, version):
    rstoragedomain = {}
    rstoragedomain['id']                  = storagedomain['@id']
    rstoragedomain['name']                = storagedomain['name']
    rstoragedomain['type']                = storagedomain['type']
    rstoragedomain['master']              = storagedomain['master']
    rstoragedomain['storage_type']        = storagedomain['storage']['type']
    try:
        rstoragedomain['storage_path']    = storagedomain['storage']['path']
    except:
        rstoragedomain['storage_path']    = ''		#GLANCE存储域没有路径
    try:
        rstoragedomain['storage_address'] = storagedomain['storage']['address']
    except:
        rstoragedomain['storage_address'] = ''		#本地存储等没有地址
    try:
        rstoragedomain['available']       = str(int(storagedomain['available'])/1024/1024/1024)
        rstoragedomain['used']            = str(int(storagedomain['used'])/1024/1024/1024)
    except:
        rstoragedomain['available']       = ''		#GLANCE存储域没有
        rstoragedomain['used']            = ''
    return rstoragedomain


def parseDisk(disk, version):
    rdisk = {}
    rdisk['id']               = disk['@id']
    rdisk['name']             = disk['name']
    if version['major'] == '4':
        rdisk['status']       = disk['status']
    else:
        rdisk['status']       = disk['status']['state']
    rdisk['format']           = disk['format']
    rdisk['image_id']         = disk['image_id']
    rdisk['actual_size']      = disk['actual_size']
    rdisk['provisioned_size'] = disk['provisioned_size']
    return rdisk


def parseVm(vm, version):
    rvm = {}
    rvm['id']                   = vm['@id']
    rvm['name']                 = vm['name']
    rvm['type']                 = vm['type']
    rvm['cluster_id']           = vm['cluster']['@id']
    rvm['template_id']          = vm['template']['@id']
    try:
        rvm['description']      = vm['description']
    except:
        rvm['description']      = ''
    if version['major'] == '4':
        rvm['status']           = vm['status']
        cpu_sockets             = vm['cpu']['topology']['sockets']
        cpu_cores               = vm['cpu']['topology']['cores']
        rvm['cpu']              = str(int(cpu_sockets)*int(cpu_cores))
        rvm['timezone']         = vm['time_zone']['name']
        rvm['os_type']          = vm['os']['type']
    else:
        rvm['status']           = vm['status']['state']
        cpu_sockets             = vm['cpu']['topology']['@sockets']
        cpu_cores               = vm['cpu']['topology']['@cores']
        rvm['cpu']              = str(int(cpu_sockets)*int(cpu_cores))
        rvm['timezone']         = vm['timezone']
        rvm['os_type']          = vm['os']['@type']
    rvm['memory']               = str(int(vm['memory'])/1024/1024)
    try:
        rvm['display_address']  = vm['display']['address']
    except:
        rvm['display_address']  = ''
    try:
        rvm['port']             = vm['display']['port']
    except:
        rvm['port']             = '-1'
    try:
        rvm['sport']            = vm['display']['secure_port']
    except:
        rvm['sport']            = '-1'
    rvm['stateless']            = vm['stateless']
    rvm['delete_protected']     = vm['delete_protected']
    rvm['usb_policy']           = vm['usb']['enabled']
    rvm['display_type']         = vm['display']['type']
    try:
        rvm['host_id']          = vm['host']['@id']
    except:
        rvm['host_id']          = ''
    try:
        t = time.strptime(vm['creation_time'], "%Y-%m-%dT%H:%M:%S.%f+08:00")
    except:
        t = time.strptime(vm['creation_time'], "%Y-%m-%dT%H:%M:%S.%f-04:00")
    rvm['creation_time']        = time.strftime("%Y-%m-%d %H:%M", t)
    try:
        rvm['data']                 = vm['initialization']['configuration']['data']
    except Exception, e:
        rvm['data']             = ''
    return rvm


def parseVmPool(vmpool, version):
    rvmpool = {}
    rvmpool['id']               = vmpool['@id']
    rvmpool['name']             = vmpool['name']
    rvmpool['description']      = vmpool['description']
    rvmpool['size']             = vmpool['size']
    rvmpool['type']             = vmpool['type']
    return rvmpool


def parseTemplate(template, version):
    rtemplate = {}
    rtemplate['id']               = template['@id']
    rtemplate['name']             = template['name']
    try:
        rtemplate['description']  = template['description']
    except:
        rtemplate['description']  = ''
    rtemplate['type']             = template['type']
    if version['major'] == '4':
        rtemplate['status']       = template['status']
        cpu_sockets               = template['cpu']['topology']['sockets']
        cpu_cores                 = template['cpu']['topology']['cores']
        rtemplate['cpu']          = str(int(cpu_sockets)*int(cpu_cores))
        try:
            rtemplate['timezone'] = template['time_zone']['name']
        except:
            rtemplate['timezone'] = ''
        rtemplate['os_type']      = template['os']['type']
    else:
        rtemplate['status']       = template['status']['state']
        cpu_sockets               = template['cpu']['topology']['@sockets']
        cpu_cores                 = template['cpu']['topology']['@cores']
        rtemplate['cpu']          = str(int(cpu_sockets)*int(cpu_cores))
        try:
            rtemplate['timezone'] = template['timezone']
        except:
            rtemplate['timezone'] = ''
        rtemplate['os_type']      = template['os']['@type']
    rtemplate['memory']           = str(int(template['memory'])/1024/1024)
    rtemplate['display_type']     = template['display']['type']
    rtemplate['stateless']        = template['stateless']
    rtemplate['delete_protected'] = template['delete_protected']
    rtemplate['usb_policy']       = template['usb']['enabled']
    try:
        t = time.strptime(template['creation_time'], "%Y-%m-%dT%H:%M:%S.%f+08:00")
    except:
        t = time.strptime(template['creation_time'], "%Y-%m-%dT%H:%M:%S.%f-04:00")
    rtemplate['creation_time']    = time.strftime("%Y-%m-%d %H:%M", t)
    try:
        rtemplate['cluster_id']   = template['cluster']['@id']
    except:
        rtemplate['cluster_id']   = ''
    return rtemplate


def parseDomain(domain, version):
    rdomain = {}
    rdomain['id']              = domain['@id']
    rdomain['name']            = domain['name']
    return rdomain


def parseUser(user, version):
    ruser = {}
    ruser['id']              = user['@id']
    ruser['name']            = user['name']
    ruser['namespace']       = user['namespace']
    ruser['user_name']       = user['user_name']
    try:
        ruser['last_name']   = user['last_name']
    except:
        ruser['last_name']   = ''
    try:
        ruser['email']       = user['email']
    except:
        ruser['email']       = ''
    ruser['domain_id']       = user['domain']['@id']
    ruser['domain_name']     = user['domain']['name']
    ruser['domain_entry_id'] = user['domain_entry_id']
    return ruser


def parseGroup(group, version):
    rgroup = {}
    rgroup['id']              = group['@id']
    rgroup['name']            = group['name']
    rgroup['namespace']       = group['namespace']
    rgroup['domain_entry_id'] = group['domain_entry_id']
    try:
        rgroup['domain_id']   = group['domain']['@id']
    except:
        rgroup['domain_id']   = ''
    try:
        rgroup['domain_name'] = group['domain']['name']
    except:
        rgroup['domain_name'] = ''
    return rgroup


def parseTag(tag, version):
    rtag = {}
    rtag['id']              = tag['@id']
    rtag['name']            = tag['name']
    try:
        rtag['description'] = tag['description']
    except:
        rtag['description'] = ''
    try:
        rtag['parent_id']   = tag['parent']['@id']
    except:
        rtag['parent_id']   = ''
    return rtag


def parseBookmark(bookmark, version):
    rbookmark = {}
    rbookmark['id']             = bookmark['@id']
    return rbookmark


def parseRole(role, version):
    rrole = {}
    rrole['id']                 = role['@id']
    rrole['name']               = role['name']
    try:
        rrole['description']    = role['description']
    except:
        rrole['description']    = ''            #用户角色没有这个域
    try:
        rrole['administrative'] = role['administrative']
    except:
        rrole['administrative'] = ''
    try:
        rrole['mutable']        = role['mutable']
    except:
        rrole['mutable']        = ''
    return rrole


def parseDomainUser(user, version):
    ruser = {}
    ruser['id']              = user['@id']
    ruser['name']            = user['name']
    ruser['namespace']       = user['namespace']
    ruser['user_name']       = user['user_name']
    try:
        ruser['last_name']   = user['last_name']
    except:
        ruser['last_name']   = ''
    try:
        ruser['email']       = user['email']
    except:
        ruser['email']       = ''
    ruser['domain_id']       = user['domain']['@id']
    return ruser


def parseDomainGroup(group, version):
    rgroup = {}
    rgroup['id']              = group['@id']
    rgroup['name']            = group['name']
    rgroup['namespace']       = group['namespace']
    return rgroup


def parseQuota(quota, version):
    rquota = {}
    rquota['id']             = quota['@id']
    return rquota


def parseQos(qos, version):
    rqos = {}
    rqos['id']             = qos['@id']
    return rqos


def parseIscsiBond(iscsibond, version):
    riscsibond = {}
    riscsibond['id']             = iscsibond['@id']
    return riscsibond


def parsePermit(permit, version):
    rpermit = {}
    rpermit['id']             = permit['@id']
    rpermit['name']           = permit['name']
    rpermit['administrative'] = permit['administrative']
    return rpermit


def parsePermission(permission, version):
    rpermission = {}
    rpermission['id']                 = permission['@id']
    rpermission['role']               = permission['role']['@id']
    try:
        rpermission['user']           = permission['user']['@id']
    except:
        rpermission['user']           = ''
    try:
        rpermission['group']          = permission['group']['@id']
    except:
        rpermission['group']          = ''
    try:
        rpermission['data_center']    = permission['data_center']['@id']
    except:
        rpermission['data_center']    = ''
    try:
        rpermission['cluster']        = permission['cluster']['@id']
    except:
        rpermission['cluster']        = ''
    try:
        rpermission['vm']             = permission['vm']['@id']
    except:
        rpermission['vm']             = ''
    try:
        rpermission['template']       = permission['template']['@id']
    except:
        rpermission['template']       = ''
    try:
        rpermission['storage_domain'] = permission['disk']['@id']
    except:
        rpermission['storage_domain'] = ''
    try:
        rpermission['disk']           = permission['disk']['@id']
    except:
        rpermission['disk']           = ''
    return rpermission


def parseDiskAttachment(disk, version):
    rdisk = {}
    rdisk['id']               = disk['@id']
    rdisk['active']           = disk['active']
    rdisk['bootable']         = disk['bootable']
    rdisk['interface']        = disk['interface']
    return rdisk


def parseHostNic(nic, version):
    rnic = {}
    rnic['id']            = nic['@id']
    rnic['name']          = nic['name']
    rnic['status']        = nic['status']
    rnic['boot_protocol'] = nic['boot_protocol']
    rnic['bridged']       = nic['bridged']
    rnic['ip_address']    = nic['ip']['address']
    rnic['ip_network']    = nic['ip']['netmask']
    rnic['mac_address']   = nic['mac']['address']
    return rnic


def parseVmNic(nic, version):
    rnic = {}
    rnic['id']               = nic['@id']
    rnic['name']             = nic['name']
    rnic['interface']        = nic['interface']
    rnic['linked']           = nic['linked']
    rnic['plugged']          = nic['plugged']
    rnic['mac_address']      = nic['mac']['address']
    rnic['reported_devices'] = parseResponse(nic, version, 'reported_devices', 'reported_device', parseNicReportedDevice)
    return rnic


def parseTemplateNic(nic, version):
    rnic = {}
    rnic['id']               = nic['@id']
    rnic['name']             = nic['name']
    rnic['interface']        = nic['interface']
    rnic['linked']           = nic['linked']
    rnic['plugged']          = nic['plugged']
    return rnic


def parseNicReportedDevice(reported_device, version):
    rreported_device = {}
    rreported_device['id']          = reported_device['@id']
    rreported_device['name']        = reported_device['name']
    rreported_device['description'] = reported_device['description']
    rreported_device['mac_address'] = reported_device['mac']['address']
    rreported_device['ips']         = parseResponse(reported_device, version, 'ips', 'ip', parseReportedDeviceIp)
    return rreported_device


def parseReportedDeviceIp(ip, version):
    rip = {}
    rip['version'] = ip['version']
    rip['address'] = ip['address']
    return rip


def parseJob(job, version):
    rjob = {}
    rjob['id']            = job['@id']
    rjob['name']          = job['name']
    return rjob


def parseDiskStorageDomainId(storagedomain, version):
    rstoragedomainid = {}
    rstoragedomainid['id'] = storagedomain['@id']
    return storagedomain['@id']


#################################################################
#
# Data Center Related
#
#################################################################
def getDataCenterInfo(engine, username, password, datacenter_id):
    return getResource(engine, username, password, 'datacenters', datacenter_id, 'data_center', parseDataCenter)


def getDataCenterName(engine, username, password, datacenter_id):
    def parseDataCenterName(resource, version):
        return resource['name']
    return getResource(engine, username, password, 'datacenters', datacenter_id, 'data_center', parseDataCenterName)


def getDataCenterDescription(engine, username, password, datacenter_id):
    def parseDataCenterDescription(resource, version):
        return resource['description']
    return getResource(engine, username, password, 'datacenters', datacenter_id, 'data_center', parseDataCenterDescription)


def getDataCenterLocal(engine, username, password, datacenter_id):
    def parseDataCenterLocal(resource, version):
        return resource['local']
    return getResource(engine, username, password, 'datacenters', datacenter_id, 'data_center', parseDataCenterLocal)


def getDataCenterStorageFormat(engine, username, password, datacenter_id):
    def parseDataCenterStorageFormat(resource, version):
        return resource['storage_format']
    return getResource(engine, username, password, 'datacenters', datacenter_id, 'data_center', parseDataCenterStorageFormat)


def getDataCenterStatus(engine, username, password, datacenter_id):
    def parseDataCenterStatus(resource, version):
        if version['major'] == '4':
            return resource['status']
        else:
            return resource['status']['state']
    return getResource(engine, username, password, 'datacenters', datacenter_id, 'data_center', parseDataCenterStatus)


def getDataCenterQuotaMode(engine, username, password, datacenter_id):
    def parseDataCenterQuotaMode(resource, version):
        return resource['quota_mode']
    return getResource(engine, username, password, 'datacenters', datacenter_id, 'data_center', parseDataCenterQuotaMode)


def getDataCenterVersion(engine, username, password, datacenter_id):
    def parseDataCenterVersion(resource, version):
        if version['major'] == '4':
            return resource['version']['major'] + '.' + resource['version']['minor']
        else:
            return resource['version']['@major'] + '.' + resource['version']['@minor']
    return getResource(engine, username, password, 'datacenters', datacenter_id, 'data_center', parseDataCenterVersion)


def getDataCenterClusters(engine, username, password, datacenter_id):
    return getResourceChildren(engine, username, password, 'datacenters', datacenter_id, 'clusters', 'clusters', 'cluster', parseCluster)


def getDataCenterNetworks(engine, username, password, datacenter_id):
    return getResourceChildren(engine, username, password, 'datacenters', datacenter_id, 'networks', 'networks', 'network', parseNetwork)


def getDataCenterStorageDomains(engine, username, password, datacenter_id):
    return getResourceChildren(engine, username, password, 'datacenters', datacenter_id, 'storagedomains', 'storage_domains', 'storage_domain', parseStorageDomain)


def getDataCenterDataStorageDomains(engine, username, password, datacenter_id):
    rstoragedomains = []
    for storagedomain in getDataCenterStorageDomains(engine, username, password, datacenter_id):
        if storagedomain['type'] == 'data':
            rstoragedomains.append(storagedomain)
    return rstoragedomains


def getDataCenterMasterStorageDomain(engine, username, password, datacenter_id):
    for storagedomain in getDataCenterStorageDomains(engine, username, password, datacenter_id):
        if storagedomain['master'] == 'true':
            return storagedomain


def getDataCenterIsoStorageDomain(engine, username, password, datacenter_id):
    for storagedomain in getDataCenterStorageDomains(engine, username, password, datacenter_id):
        if storagedomain['type'] == 'iso':
            return storagedomain


def getDataCenterExportStorageDomain(engine, username, password, datacenter_id):
    for storagedomain in getDataCenterStorageDomains(engine, username, password, datacenter_id):
        if storagedomain['type'] == 'export':
            return storagedomain


def getDataCenterDataStorageDomainIds(engine, username, password, datacenter_id):
    rstoragedomains = []
    for storagedomain in getDataCenterStorageDomains(engine, username, password, datacenter_id):
        if storagedomain['type'] == 'data':
            rstoragedomains.append(storagedomain['id'])
    return rstoragedomains


def getDataCenterMasterStorageDomainId(engine, username, password, datacenter_id):
    for storagedomain in getDataCenterStorageDomains(engine, username, password, datacenter_id):
        if storagedomain['master'] == 'true':
            return storagedomain['id']


def getDataCenterIsoStorageDomainId(engine, username, password, datacenter_id):
    for storagedomain in getDataCenterStorageDomains(engine, username, password, datacenter_id):
        if storagedomain['type'] == 'iso':
            return storagedomain['id']


def getDataCenterExportStorageDomainId(engine, username, password, datacenter_id):
    for storagedomain in getDataCenterStorageDomains(engine, username, password, datacenter_id):
        if storagedomain['type'] == 'export':
            return storagedomain['id']


def getDataCenterPermissions(engine, username, password, datacenter_id):
    return getResourceChildren(engine, username, password, 'datacenters', datacenter_id, 'permissions', 'permissions', 'permission', parsePermission)


def getDataCenterQuotas(engine, username, password, datacenter_id):
    return getResourceChildren(engine, username, password, 'datacenters', datacenter_id, 'quotas', 'quotas', 'quota', parseQuota)


def getDataCenterQoss(engine, username, password, datacenter_id):
    return getResourceChildren(engine, username, password, 'datacenters', datacenter_id, 'qoss', 'qoss', 'qos', parseQos)


def getDataCenterIscsiBonds(engine, username, password, datacenter_id):
    return getResourceChildren(engine, username, password, 'datacenters', datacenter_id, 'iscsibonds', 'iscsibonds', 'iscsibond', parseIscsiBond)


def getDataCenterClusterIds(engine, username, password, datacenter_id):
    return getResourceChildren(engine, username, password, 'datacenters', datacenter_id, 'clusters', 'clusters', 'cluster', parseResourceId)


def getDataCenterNetworkIds(engine, username, password, datacenter_id):
    return getResourceChildren(engine, username, password, 'datacenters', datacenter_id, 'networks', 'networks', 'network', parseResourceId)


def getDataCenterStorageDomainIds(engine, username, password, datacenter_id):
    return getResourceChildren(engine, username, password, 'datacenters', datacenter_id, 'storagedomains', 'storage_domains', 'storage_domain', parseResourceId)


def getDataCenterPermissionIds(engine, username, password, datacenter_id):
    return getResourceChildren(engine, username, password, 'datacenters', datacenter_id, 'permissions', 'permissions', 'permission', parseResourceId)


def getDataCenterQuotaIds(engine, username, password, datacenter_id):
    return getResourceChildren(engine, username, password, 'datacenters', datacenter_id, 'quotas', 'quotas', 'quota', parseResourceId)


def getDataCenterQosIds(engine, username, password, datacenter_id):
    return getResourceChildren(engine, username, password, 'datacenters', datacenter_id, 'qoss', 'qoss', 'qos', parseResourceId)


def getDataCenterIscsiBondIds(engine, username, password, datacenter_id):
    return getResourceChildren(engine, username, password, 'datacenters', datacenter_id, 'iscsibonds', 'iscsibonds', 'iscsibond', parseResourceId)


#################################################################
#
# Cluster Related
#
#################################################################
def getClusterInfo(engine, username, password, cluster_id):
    return getResource(engine, username, password, 'clusters', cluster_id, 'cluster', parseCluster)


def getClusterName(engine, username, password, cluster_id):
    def parseClusterName(resource, version):
        return resource['name']
    return getResource(engine, username, password, 'clusters', cluster_id, 'cluster', parseClusterName)


def getClusterDescription(engine, username, password, cluster_id):
    def parseClusterDescription(resource, version):
        return resource['description']
    return getResource(engine, username, password, 'clusters', cluster_id, 'cluster', parseClusterDescription)


def getClusterDataCenterId(engine, username, password, cluster_id):
    def parseClusterDataCenterId(resource, version):
        return resource['data_center']['@id']
    return getResource(engine, username, password, 'clusters', cluster_id, 'cluster', parseClusterDataCenterId)


def getClusterNetworks(engine, username, password, cluster_id):
    return getResourceChildren(engine, username, password, 'clusters', cluster_id, 'networks', 'networks', 'network', parseNetwork)


def getClusterPermissions(engine, username, password, cluster_id):
    return getResourceChildren(engine, username, password, 'clusters', cluster_id, 'permissions', 'permissions', 'permission', parsePermission)


def getClusterNetworkIds(engine, username, password, cluster_id):
    return getResourceChildren(engine, username, password, 'clusters', cluster_id, 'networks', 'networks', 'network', parseResourceId)


def getClusterPermissionIds(engine, username, password, cluster_id):
    return getResourceChildren(engine, username, password, 'clusters', cluster_id, 'permissions', 'permissions', 'permission', parseResourceId)


def getClusterGlusterVolumeIds(engine, username, password, cluster_id):
    return getResourceChildren(engine, username, password, 'clusters', cluster_id, 'glustervolumes', 'glustervolumes', 'glustervolume', parseResourceId)


def getClusterGlusterHookIds(engine, username, password, cluster_id):
    return getResourceChildren(engine, username, password, 'clusters', cluster_id, 'glusterhooks', 'glusterhooks', 'glusterhook', parseResourceId)


def getClusterAffinityGroupIds(engine, username, password, cluster_id):
    return getResourceChildren(engine, username, password, 'clusters', cluster_id, 'affinitygroups', 'affinitygroups', 'affinitygroup', parseResourceId)


def getClusterCpuProfileIds(engine, username, password, cluster_id):
    return getResourceChildren(engine, username, password, 'clusters', cluster_id, 'cpuprofiles', 'cpuprofiles', 'cpuprofile', parseResourceId)


def getClusterNetworkFilterIds(engine, username, password, cluster_id):
    return getResourceChildren(engine, username, password, 'clusters', cluster_id, 'networkfilters', 'networkfilters', 'networkfilter', parseResourceId)


#################################################################
#
# Host Related
#
#################################################################
def getHostInfo(engine, username, password, host_id):
    return getResource(engine, username, password, 'hosts', host_id, 'host', parseHost)


def getHostName(engine, username, password, host_id):
    def parseHostName(resource, version):
        return resource['name']
    return getResource(engine, username, password, 'hosts', host_id, 'host', parseHostName)


def getHostAddress(engine, username, password, host_id):
    def parseHostAddress(resource, version):
        return resource['address']
    return getResource(engine, username, password, 'hosts', host_id, 'host', parseHostAddress)


def getHostCertificateOrganization(engine, username, password, host_id):
    def parseHostCertificateOrganization(resource, version):
        return resource['certificate']['organization']
    return getResource(engine, username, password, 'hosts', host_id, 'host', parseHostCertificateOrganization)


def getHostCertificateSubject(engine, username, password, host_id):
    def parseHostCertificateSubject(resource, version):
        return resource['certificate']['subject']
    return getResource(engine, username, password, 'hosts', host_id, 'host', parseHostCertificateSubject)


def getHostStatus(engine, username, password, host_id):
    def parseHostStatus(resource, version):
        if version['major'] == '4':
            return resource['status']
        else:
            return resource['status']['state']
    return getResource(engine, username, password, 'hosts', host_id, 'host', parseHostStatus)


def getHostType(engine, username, password, host_id):
    def parseHostType(resource, version):
        return resource['type']
    return getResource(engine, username, password, 'hosts', host_id, 'host', parseHostType)


def getHostUuid(engine, username, password, host_id):
    def parseHostUuid(resource, version):
        return resource['hardware_information']['uuid']
    return getResource(engine, username, password, 'hosts', host_id, 'host', parseHostUuid)


def getHostSshPort(engine, username, password, host_id):
    def parseHostSshPort(resource, version):
        return resource['ssh']['port']
    return getResource(engine, username, password, 'hosts', host_id, 'host', parseHostSshPort)


def getHostSshFingerPrint(engine, username, password, host_id):
    def parseHostSshFingerPrint(resource, version):
        return resource['ssh']['fingerprint']
    return getResource(engine, username, password, 'hosts', host_id, 'host', parseHostSshFingerPrint)


def getHostCpuSockets(engine, username, password, host_id):
    def parseHostCpuSockets(resource, version):
        if version['major'] == '4':
            return resource['cpu']['topology']['sockets']
        else:
            return resource['cpu']['topology']['@sockets']
    return getResource(engine, username, password, 'hosts', host_id, 'host', parseHostCpuSockets)


def getHostCpuCores(engine, username, password, host_id):
    def parseHostCpuCores(resource, version):
        if version['major'] == '4':
            return resource['cpu']['topology']['cores']
        else:
            return resource['cpu']['topology']['@cores']
    return getResource(engine, username, password, 'hosts', host_id, 'host', parseHostCpuCores)


def getHostCpuThreads(engine, username, password, host_id):
    def parseHostCpuThreads(resource, version):
        if version['major'] == '4':
            return resource['cpu']['topology']['threads']
        else:
            return resource['cpu']['topology']['@threads']
    return getResource(engine, username, password, 'hosts', host_id, 'host', parseHostCpuThreads)


def getHostMemory(engine, username, password, host_id):
    def parseHostMemory(resource, version):
        return resource['memory']
    return getResource(engine, username, password, 'hosts', host_id, 'host', parseHostMemory)


def getHostOsType(engine, username, password, host_id):
    def parseHostOsType(resource, version):
        if version['major'] == '4':
            return resource['os']['type']
        else:
            return resource['os']['@type']
    return getResource(engine, username, password, 'hosts', host_id, 'host', parseHostOsType)


def getHostOsVersion(engine, username, password, host_id):
    def parseHostOsVersion(resource, version):
        if version['major'] == '4':
            return resource['os']['version']['full_version']
        else:
            return resource['os']['version']['@full_version']
    return getResource(engine, username, password, 'hosts', host_id, 'host', parseHostOsVersion)


def getHostDisplayAddress(engine, username, password, host_id):
    def parseHostDisplayAddress(resource, version):
        try:
            return resource['display']['address']
        except:
            return ''    #如果没有勾选覆盖显示地址，这个域不存在
    return getResource(engine, username, password, 'hosts', host_id, 'host', parseHostDisplayAddress)


def getHostClusterId(engine, username, password, host_id):
    def parseHostClusterId(resource, version):
        return resource['cluster']['@id']
    return getResource(engine, username, password, 'hosts', host_id, 'host', parseHostClusterId)


def getHostTags(engine, username, password, host_id):
    return getResourceChildren(engine, username, password, 'hosts', host_id, 'tags', 'tags', 'tag', parseTag)


def getHostNics(engine, username, password, host_id):
    return getResourceChildren(engine, username, password, 'hosts', host_id, 'nics', 'host_nics', 'host_nic', parseHostNic)


def getHostPermissions(engine, username, password, host_id):
    return getResourceChildren(engine, username, password, 'hosts', host_id, 'permissions', 'permissions', 'permission', parsePermission)


def getHostStorageIds(engine, username, password, host_id):
    return getResourceChildren(engine, username, password, 'hosts', host_id, 'storages', 'storages', 'storage', parseResourceId)


def getHostNicIds(engine, username, password, host_id):
    return getResourceChildren(engine, username, password, 'hosts', host_id, 'nics', 'nics', 'nic', parseResourceId)


def getHostNumanodeIds(engine, username, password, host_id):
    return getResourceChildren(engine, username, password, 'hosts', host_id, 'numanodes', 'numanodes', 'numanode', parseResourceId)


def getHostTagIds(engine, username, password, host_id):
    return getResourceChildren(engine, username, password, 'hosts', host_id, 'tags', 'tags', 'tag', parseResourceId)


def getHostPermissionIds(engine, username, password, host_id):
    return getResourceChildren(engine, username, password, 'hosts', host_id, 'permissions', 'permissions', 'permission', parseResourceId)


def getHostHookIds(engine, username, password, host_id):
    return getResourceChildren(engine, username, password, 'hosts', host_id, 'hooks', 'hooks', 'hook', parseResourceId)


def getHostDeviceIds(engine, username, password, host_id):
    return getResourceChildren(engine, username, password, 'hosts', host_id, 'devices', 'devices', 'device', parseResourceId)


def getHostAffinityLabelIds(engine, username, password, host_id):
    return getResourceChildren(engine, username, password, 'hosts', host_id, 'affinitylabels', 'affinitylabels', 'affinitylabel', parseResourceId)


#<link href="/ovirt-engine/api/hosts/589c50bb-f940-4862-9c85-5729d699616e/katelloerrata" rel="katelloerrata"/>
#<link href="/ovirt-engine/api/hosts/589c50bb-f940-4862-9c85-5729d699616e/fenceagents" rel="fenceagents"/>
#<link href="/ovirt-engine/api/hosts/589c50bb-f940-4862-9c85-5729d699616e/networkattachments" rel="networkattachments"/>
#<link href="/ovirt-engine/api/hosts/589c50bb-f940-4862-9c85-5729d699616e/storageconnectionextensions" rel="storageconnectionextensions"/>
#<link href="/ovirt-engine/api/hosts/589c50bb-f940-4862-9c85-5729d699616e/unmanagednetworks" rel="unmanagednetworks"/>


#################################################################
#
# Network Related
#
#################################################################
def getNetworkInfo(engine, username, password, network_id):
    return getResource(engine, username, password, 'networks', network_id, 'network', parseNetwork)


def getNetworkName(engine, username, password, network_id):
    def parseNetworkName(resource, version):
        return resource['name']
    return getResource(engine, username, password, 'networks', network_id, 'network', parseNetworkName)


def getNetworkDescription(engine, username, password, network_id):
    def parseNetworkDescription(resource, version):
        return resource['description']
    return getResource(engine, username, password, 'networks', network_id, 'network', parseNetworkDescription)


def getNetworkDataCenterId(engine, username, password, network_id):
    def parseNetworkDataCenterId(resource, version):
        return resource['data_center']['@id']
    return getResource(engine, username, password, 'networks', network_id, 'network', parseNetworkDataCenterId)


def getNetworkPermissions(engine, username, password, network_id):
    return getResourceChildren(engine, username, password, 'networks', network_id, 'permissions', 'permissions', 'permission', parsePermission)


def getNetworkPermissionIds(engine, username, password, network_id):
    return getResourceChildren(engine, username, password, 'networks', network_id, 'permissions', 'permissions', 'permission', parseResourceId)


def getNetworkVnicProfileIds(engine, username, password, network_id):
    return getResourceChildren(engine, username, password, 'networks', network_id, 'vnicprofiles', 'vnicprofiles', 'vnicprofile', parseResourceId)


def getNetworkNetworkLabelIds(engine, username, password, network_id):
    return getResourceChildren(engine, username, password, 'networks', network_id, 'networklabels', 'networklabels', 'networklabel', parseResourceId)


#################################################################
#
# Storage Domain Related
#
#################################################################
def getStorageDomainInfo(engine, username, password, storagedomain_id):
    return getResource(engine, username, password, 'storagedomains', storagedomain_id, 'storage_domain', parseStorageDomain)


def getStorageDomainName(engine, username, password, storagedomain_id):
    def parseStorageDomainName(resource, version):
        return resource['name']
    return getResource(engine, username, password, 'storagedomains', storagedomain_id, 'storage_domain', parseStorageDomainName)


def getStorageDomainType(engine, username, password, storagedomain_id):
    def parseStorageDomainType(resource, version):
        return resource['type']
    return getResource(engine, username, password, 'storagedomains', storagedomain_id, 'storage_domain', parseStorageDomainType)


#def getStorageDomainStatus(engine, username, password, storagedomain_id):
#    def parseStorageDomainStatus(resource, version):
#        print '*********************************'
#        print resource
#        if version['major'] == '4':
#            return resource['status']
#        else:
#            return resource['status']['state']
#    return getResource(engine, username, password, 'storagedomains', storagedomain_id, 'storage_domain', parseStorageDomainStatus)


def getStorageDomainStorageAddress(engine, username, password, storagedomain_id):
    def parseStorageDomainStorageAddress(resource, version):
        try:
            return resource['storage']['address']
        except:
            return ''
    return getResource(engine, username, password, 'storagedomains', storagedomain_id, 'storage_domain', parseStorageDomainStorageAddress)	#本地存储域地址为空


def getStorageDomainStorageType(engine, username, password, storagedomain_id):
    def parseStorageDomainStorageType(resource, version):
        return resource['storage']['type']
    return getResource(engine, username, password, 'storagedomains', storagedomain_id, 'storage_domain', parseStorageDomainStorageType)


def getStorageDomainStoragePath(engine, username, password, storagedomain_id):
    def parseStorageDomainStoragePath(resource, version):
        try:
            return resource['storage']['path']
        except:
            return ''
    return getResource(engine, username, password, 'storagedomains', storagedomain_id, 'storage_domain', parseStorageDomainStoragePath)


def getStorageDomainStorageAvailable(engine, username, password, storagedomain_id):
    def parseStorageDomainStorageAvailable(resource, version):
        try:
            return resource['available']
        except:
            return ''
    return getResource(engine, username, password, 'storagedomains', storagedomain_id, 'storage_domain', parseStorageDomainStorageAvailable)


def getStorageDomainStorageUsed(engine, username, password, storagedomain_id):
    def parseStorageDomainStorageUsed(resource, version):
        try:
            return resource['used']
        except:
            return ''
    return getResource(engine, username, password, 'storagedomains', storagedomain_id, 'storage_domain', parseStorageDomainStorageUsed)


def getStorageDomainPermissions(engine, username, password, storagedomain_id):
    return getResourceChildren(engine, username, password, 'storagedomains', storagedomain_id, 'permissions', 'permissions', 'permission', parsePermission)


#以下对数据、ISO、导出和外部存储域均有效
def getStorageDomainPermissionIds(engine, username, password, storagedomain_id):
    return getResourceChildren(engine, username, password, 'storagedomains', storagedomain_id, 'permissions', 'permissions', 'permission', parseResourceId)


def getStorageDomainDiskSnapshotIds(engine, username, password, storagedomain_id):
    return getResourceChildren(engine, username, password, 'storagedomains', storagedomain_id, 'disksnapshots', 'disksnapshots', 'disksnapshot', parseResourceId)


def getStorageDomainDiskProfileIds(engine, username, password, storagedomain_id):
    return getResourceChildren(engine, username, password, 'storagedomains', storagedomain_id, 'diskprofiles', 'diskprofiles', 'diskprofile', parseResourceId)


#以下对数据、ISO、导出存储域有效
def getStorageDomainStorageConnectionIds(engine, username, password, storagedomain_id):
    return getResourceChildren(engine, username, password, 'storagedomains', storagedomain_id, 'storageconnections', 'storageconnections', 'storageconnection', parseResourceId)


#以下对数据、导出存储域有效
def getStorageDomainDiskIds(engine, username, password, storagedomain_id):
    return getResourceChildren(engine, username, password, 'storagedomains', storagedomain_id, 'disks', 'disks', 'disk', parseResourceId)


def getStorageDomainVmIds(engine, username, password, storagedomain_id):
    return getResourceChildren(engine, username, password, 'storagedomains', storagedomain_id, 'vms', 'vms', 'vm', parseResourceId)


def getStorageDomainTemplateIds(engine, username, password, storagedomain_id):
    return getResourceChildren(engine, username, password, 'storagedomains', storagedomain_id, 'templates', 'templates', 'template', parseResourceId)


#以下对ISO存储域有效
def getStorageDomainFileIds(engine, username, password, storagedomain_id):
    return getResourceChildren(engine, username, password, 'storagedomains', storagedomain_id, 'files', 'files', 'file', parseResourceId)


#以下对外部存储域有效
def getStorageDomainImageIds(engine, username, password, storagedomain_id):
    return getResourceChildren(engine, username, password, 'storagedomains', storagedomain_id, 'images', 'images', 'image', parseResourceId)


#################################################################
#
# Disk Related
#
#################################################################
def getDiskInfo(engine, username, password, disk_id):
    return getResource(engine, username, password, 'disks', disk_id, 'disk', parseDisk)


def getDiskName(engine, username, password, disk_id):
    def parseDiskName(resource, version):
        return resource['name']
    return getResource(engine, username, password, 'disks', disk_id, 'disk', parseDiskName)


def getDiskAlias(engine, username, password, disk_id):
    def parseDiskAlias(resource, version):
        return resource['alias']
    return getResource(engine, username, password, 'disks', disk_id, 'disk', parseDiskAlias)


def getDiskImageId(engine, username, password, disk_id):
    def parseDiskImageId(resource, version):
        return resource['image_id']
    return getResource(engine, username, password, 'disks', disk_id, 'disk', parseDiskImageId)


def getDiskStorageDomainIds(engine, username, password, disk_id):
    def parseDiskStorageDomainIds(resource, version):
        return parseResponse(resource, version, 'storage_domains', 'storage_domain', parseDiskStorageDomainId)
    return getResource(engine, username, password, 'disks', disk_id, 'disk', parseDiskStorageDomainIds)


#def getDiskSize(engine, username, password, disk_id):
#    disk = requestResource(engine, username, password, 'disks', disk_id)
#    return disk['disk']['size']


def getDiskProvisionedSize(engine, username, password, disk_id):
    def parseDiskProvisionedSize(resource, version):
        return resource['provisioned_size']
    return getResource(engine, username, password, 'disks', disk_id, 'disk', parseDiskProvisionedSize)


def getDiskActualSize(engine, username, password, disk_id):
    def parseDiskActualSize(resource, version):
        return resource['actual_size']
    return getResource(engine, username, password, 'disks', disk_id, 'disk', parseDiskActualSize)


def getDiskStatus(engine, username, password, disk_id):
    def parseDiskStatus(resource, version):
        if version['major'] == '4':
            return resource['status']
        else:
            return resource['status']['state']
    return getResource(engine, username, password, 'disks', disk_id, 'disk', parseDiskStatus)


#def getDiskInterface(engine, username, password, disk_id):
#    disk = requestResource(engine, username, password, 'disks', disk_id)
#    return disk['disk']['interface']


def getDiskFormat(engine, username, password, disk_id):
    def parseDiskFormat(resource, version):
        return resource['format']
    return getResource(engine, username, password, 'disks', disk_id, 'disk', parseDiskFormat)


def getDiskSparse(engine, username, password, disk_id):
    def parseDiskSparse(resource, version):
        return resource['sparse']
    return getResource(engine, username, password, 'disks', disk_id, 'disk', parseDiskSparse)


def getDiskBootable(engine, username, password, disk_id):
    def parseDiskBootable(resource, version):
        return resource['bootable']
    return getResource(engine, username, password, 'disks', disk_id, 'disk', parseDiskBootable)


def getDiskShareable(engine, username, password, disk_id):
    def parseDiskShareable(resource, version):
        return resource['shareable']
    return getResource(engine, username, password, 'disks', disk_id, 'disk', parseDiskShareable)


def getDiskWipeAfterDelete(engine, username, password, disk_id):
    def parseDiskWipeAfterDelete(resource, version):
        return resource['wipe_after_delete']
    return getResource(engine, username, password, 'disks', disk_id, 'disk', parseDiskWipeAfterDelete)


def getDiskPropagateErrors(engine, username, password, disk_id):
    def parseDiskPropagateErrors(resource, version):
        return resource['propagate_errors']
    return getResource(engine, username, password, 'disks', disk_id, 'disk', parseDiskPropagateErrors)


def getDiskDiskProfileId(engine, username, password, disk_id):
    def parseDiskProfileId(resource, version):
        return resource['disk_profile']['@id']
    return getResource(engine, username, password, 'disks', disk_id, 'disk', parseDiskProfileId)


def getDiskPermissions(engine, username, password, disk_id):
    return getResourceChildren(engine, username, password, 'disks', disk_id, 'permissions', 'permissions', 'permission', parsePermission)


def getDiskPermissionIds(engine, username, password, disk_id):
    return getResourceChildren(engine, username, password, 'disks', disk_id, 'permissions', 'permissions', 'permission', parseResourceId)


#################################################################
#
# Vm Related
#
#################################################################
def getVmInfo(engine, username, password, vm_id):
    return getResource(engine, username, password, 'vms', vm_id, 'vm', parseVm)


def getVmName(engine, username, password, vm_id):
    def parseVmName(resource, version):
        return resource['name']
    return getResource(engine, username, password, 'vms', vm_id, 'vm', parseVmName)


def getVmType(engine, username, password, vm_id):
    def parseVmType(resource, version):
        return resource['type']
    return getResource(engine, username, password, 'vms', vm_id, 'vm', parseVmType)


def getVmStatus(engine, username, password, vm_id):
    def parseVmStatus(resource, version):
        if version['major'] == '4':
            return resource['status']
        else:
            return resource['status']['state']
    return getResource(engine, username, password, 'vms', vm_id, 'vm', parseVmStatus)


def getVmMemory(engine, username, password, vm_id):
    def parseVmMemory(resource, version):
        return resource['memory']
    return getResource(engine, username, password, 'vms', vm_id, 'vm', parseVmMemory)


def getVmCpuSockets(engine, username, password, vm_id):
    def parseVmCpuSockets(resource, version):
        if version['major'] == '4':
            return resource['cpu']['topology']['sockets']
        else:
            return resource['cpu']['topology']['@sockets']
    return getResource(engine, username, password, 'vms', vm_id, 'vm', parseVmCpuSockets)


def getVmCpuCores(engine, username, password, vm_id):
    def parseVmCpuCores(resource, version):
        if version['major'] == '4':
            return resource['cpu']['topology']['cores']
        else:
            return resource['cpu']['topology']['@cores']
    return getResource(engine, username, password, 'vms', vm_id, 'vm', parseVmCpuCores)


def getVmCpuThreads(engine, username, password, vm_id):
    def parseVmCpuThreads(resource, version):
        if version['major'] == '4':
            return resource['cpu']['topology']['threads']
        else:
            return resource['cpu']['topology']['@threads']
    return getResource(engine, username, password, 'vms', vm_id, 'vm', parseVmCpuThreads)


def getVmOsType(engine, username, password, vm_id):
    def parseVmOsType(resource, version):
        if version['major'] == '4':
            return resource['os']['type']
        else:
            return resource['os']['@type']
    return getResource(engine, username, password, 'vms', vm_id, 'vm', parseVmOsType)


def getVmBootDev(engine, username, password, vm_id):
    def parseVmBootDev(resource, version):
        return resource['os']['boot']['@dev']
    return getResource(engine, username, password, 'vms', vm_id, 'vm', parseVmBootDev)


def getVmDisplayType(engine, username, password, vm_id):
    def parseVmDisplayType(resource, version):
        return resource['display']['type']
    return getResource(engine, username, password, 'vms', vm_id, 'vm', parseVmDisplayType)


def getVmDisplayAddress(engine, username, password, vm_id):
    def parseVmDisplayAddress(resource, version):
        try:
            return resource['display']['address']
        except:
            return ''
    return getResource(engine, username, password, 'vms', vm_id, 'vm', parseVmDisplayAddress)


def getVmDisplayPort(engine, username, password, vm_id):
    def parseVmDisplayPort(resource, version):
        try:
            return resource['display']['port']
        except:
            return ''
    return getResource(engine, username, password, 'vms', vm_id, 'vm', parseVmDisplayPort)


def getVmDisplaySecurePort(engine, username, password, vm_id):
    def parseVmDisplaySecurePort(resource, version):
        try:
            return resource['display']['secure_port']
        except:
            return ''
    return getResource(engine, username, password, 'vms', vm_id, 'vm', parseVmDisplaySecurePort)


def getVmDisplayMonitors(engine, username, password, vm_id):
    def parseVmDisplayMonitors(resource, version):
        return resource['display']['monitors']
    return getResource(engine, username, password, 'vms', vm_id, 'vm', parseVmDisplayMonitors)


def getVmDisplaySmartCardEnabled(engine, username, password, vm_id):
    def parseVmDisplaySmartCardEnabled(resource, version):
        return resource['display']['smartcard_enabled']
    return getResource(engine, username, password, 'vms', vm_id, 'vm', parseVmDisplaySmartCardEnabled)


def getVmDisplayFileTransferEnabled(engine, username, password, vm_id):
    def parseVmDisplayFileTransferEnabled(resource, version):
        return resource['display']['file_transfer_enabled']
    return getResource(engine, username, password, 'vms', vm_id, 'vm', parseVmDisplayFileTransferEnabled)


def getVmDisplayCopyPasteEnabled(engine, username, password, vm_id):
    def parseVmDisplayCopyPasteEnabled(resource, version):
        return resource['display']['copy_paste_enabled']
    return getResource(engine, username, password, 'vms', vm_id, 'vm', parseVmDisplayCopyPasteEnabled)


def getVmDisplayCertificateSubject(engine, username, password, vm_id):
    def parseVmDisplayCertificateSubject(resource, version):
        try:
            return resource['display']['certificate']['subject']
        except:
            return ''
    return getResource(engine, username, password, 'vms', vm_id, 'vm', parseVmDisplayCertificateSubject)
#    vm      = requestResource(engine, username, password, 'vms', vm_id)
#    version = getVersion(engine, username, password)
#    if version['major'] == '4':
#        try:
#            host_id = vm['vm']['host']['@id']
#            host    = requestResource(engine, username, password, 'hosts', host_id)
#            return host['host']['certificate']['subject']
#        except:
#            return ''
#    else:
#        #旧版本可以使用如下方法获取，但版本4.0以上不行
#        try:
#            return vm['vm']['display']['certificate']['subject']
#        except:
#            return ''


def getVmHostId(engine, username, password, vm_id):
    def parseVmHostId(resource, version):
        try:
            return resource['host']['@id']
        except:
            return ''
    return getResource(engine, username, password, 'vms', vm_id, 'vm', parseVmHostId)


def getVmCreationTime(engine, username, password, vm_id):
    def parseVmCreationTime(resource, version):
        return resource['creation_time']
    return getResource(engine, username, password, 'vms', vm_id, 'vm', parseVmCreationTime)


def getVmStopTime(engine, username, password, vm_id):
    def parseVmStopTime(resource, version):
        return resource['stop_time']
    return getResource(engine, username, password, 'vms', vm_id, 'vm', parseVmStopTime)


def getVmTimeZone(engine, username, password, vm_id):
    def parseVmTimeZone(resource, version):
        if version['major'] == '4':
            try:
                return resource['time_zone']['name']
            except Exception, e:
                return ''
        else:
            try:
                return resource['timezone']
            except Exception, e:
                return ''
    return getResource(engine, username, password, 'vms', vm_id, 'vm', parseVmTimeZone)


def getVmUsbEnabled(engine, username, password, vm_id):
    def parseVmUsbEnabled(resource, version):
        return resource['usb']['enabled']
    return getResource(engine, username, password, 'vms', vm_id, 'vm', parseVmUsbEnabled)


#def getVmIp(engine, username, password, vm_id):
#    #旧版本可以使用如下方法获取，但版本4.0以上不行
#    vm = requestResource(engine, username, password, 'vms', vm_id)
#    rips = []
#    try:
#        ips = vm['vm']['guest_info']['ips']['ip']
#        try:
#            rips.append(ips['@address'])
#        except Exception, e2:
#            for ip in ips:
#                rips.append(ip['@address'])
#    except Exception, e:
#        pass
#    return rips


def getVmClusterId(engine, username, password, vm_id):
    def parseVmClusterId(resource, version):
        return resource['cluster']['@id']
    return getResource(engine, username, password, 'vms', vm_id, 'vm', parseVmClusterId)


def getVmTemplateId(engine, username, password, vm_id):
    def parseVmTemplateId(resource, version):
        return resource['template']['@id']
    return getResource(engine, username, password, 'vms', vm_id, 'vm', parseVmTemplateId)


def getVmTags(engine, username, password, vm_id):
    #由于oVirt RestClient API的BUG，直接提取description获得空字符串
    return getResourceChildren(engine, username, password, 'vms', vm_id, 'tags', 'tags', 'tag', parseTag)


def getVmPermissions(engine, username, password, vm_id):
    return getResourceChildren(engine, username, password, 'vms', vm_id, 'permissions', 'permissions', 'permission', parsePermission)


def getVmPermissionUserIds(engine, username, password, vm_id):
    rusers = []
    for permission in getVmPermissions(engine, username, password, vm_id):
        user = permission['user']
        if user != '' and not user in rusers:
            rusers.append(user)
    return rusers


def getVmDiskAttachments(engine, username, password, vm_id):
    version = getVersion(engine, username, password)
    if version['major'] == '4':
        return getResourceChildren(engine, username, password, 'vms', vm_id, 'diskattachments', 'disk_attachments', 'disk_attachment', parseResourceId)
    else:
        return getResourceChildren(engine, username, password, 'vms', vm_id, 'disks', 'disks', 'disk', parseResourceId)


def getVmNics(engine, username, password, vm_id):
    return getResourceChildren(engine, username, password, 'vms', vm_id, 'nics', 'nics', 'nic', parseVmNic)


def getVmIps(engine, username, password, vm_id):
    rips = []
    for nic in getVmNics(engine, username, password, vm_id):
        for reported_device in nic['reported_devices']:
            for ip in reported_device['ips']:
                if ip['version'] == 'v4':
                    rips.append(ip['address'])
    return rips


def getVmApplicationIds(engine, username, password, vm_id):
    return getResourceChildren(engine, username, password, 'vms', vm_id, 'applications', 'applications', 'application', parseResourceId)


def getVmDiskAttachmentIds(engine, username, password, vm_id):
    version = getVersion(engine, username, password)
    if version['major'] == '4':
        return getResourceChildren(engine, username, password, 'vms', vm_id, 'diskattachments', 'disk_attachments', 'disk_attachment', parseResourceId)
    else:
        return getResourceChildren(engine, username, password, 'vms', vm_id, 'disks', 'disks', 'disk', parseResourceId)


def getVmNicIds(engine, username, password, vm_id):
    return getResourceChildren(engine, username, password, 'vms', vm_id, 'nics', 'nics', 'nic', parseResourceId)


def getVmNumanodeIds(engine, username, password, vm_id):
    return getResourceChildren(engine, username, password, 'vms', vm_id, 'numanodes', 'numanodes', 'numanode', parseResourceId)


def getVmCdromIds(engine, username, password, vm_id):
    return getResourceChildren(engine, username, password, 'vms', vm_id, 'cdroms', 'cdroms', 'cdrom', parseResourceId)


def getVmSnapshotIds(engine, username, password, vm_id):
    return getResourceChildren(engine, username, password, 'vms', vm_id, 'snapshots', 'snapshots', 'snapshot', parseResourceId)


def getVmTagIds(engine, username, password, vm_id):
    return getResourceChildren(engine, username, password, 'vms', vm_id, 'tags', 'tags', 'tag', parseResourceId)


def getVmPermissionIds(engine, username, password, vm_id):
    return getResourceChildren(engine, username, password, 'vms', vm_id, 'permissions', 'permissions', 'permission', parseResourceId)


def getVmReportedDeviceIds(engine, username, password, vm_id):
    return getResourceChildren(engine, username, password, 'vms', vm_id, 'reporteddevices', 'reporteddevices', 'reporteddevice', parseResourceId)


def getVmHostDeviceIds(engine, username, password, vm_id):
    return getResourceChildren(engine, username, password, 'vms', vm_id, 'hostdevices', 'hostdevices', 'hostdevice', parseResourceId)


def getVmWatchDogIds(engine, username, password, vm_id):
    return getResourceChildren(engine, username, password, 'vms', vm_id, 'watchdogs', 'watchdogs', 'watchdog', parseResourceId)


def getVmSessionIds(engine, username, password, vm_id):
    try:
        return getResourceChildren(engine, username, password, 'vms', vm_id, 'sessions', 'sessions', 'session', parseResourceId)
    except:
        return []		#旧版本不支持


def getVmGraphicsConsoleIds(engine, username, password, vm_id):
    return getResourceChildren(engine, username, password, 'vms', vm_id, 'graphicsconsoles', 'graphicsconsoles', 'graphicsconsole', parseResourceId)


def getVmAffinityLabelIds(engine, username, password, vm_id):
    return getResourceChildren(engine, username, password, 'vms', vm_id, 'affinitylabels', 'affnitylabels', 'affnitylabel', parseResourceId)


#<link href="/ovirt-engine/api/vms/ed61a4f5-9b7e-4e9b-88db-bcbfd7aa2e5f/katelloerrata" rel="katelloerrata"/>


#################################################################
#
# Vm Pool Related
#
#################################################################
def getVmPoolInfo(engine, username, password, vmpool_id):
    return getResource(engine, username, password, 'vmpools', vmpool_id, 'vm_pool', parseVmPool)


def getVmPoolName(engine, username, password, vmpool_id):
    def parseVmPoolName(resource, version):
        return resource['name']
    return getResource(engine, username, password, 'vmpools', vmpool_id, 'vm_pool', parseVmPoolName)


def getVmPoolDescription(engine, username, password, vmpool_id):
    def parseVmPoolDescription(resource, version):
        return resource['description']
    return getResource(engine, username, password, 'vmpools', vmpool_id, 'vm_pool', parseVmPoolDescription)


def getVmPoolSize(engine, username, password, vmpool_id):
    def parseVmPoolSize(resource, version):
        return resource['size']
    return getResource(engine, username, password, 'vmpools', vmpool_id, 'vm_pool', parseVmPoolSize)


def getVmPoolType(engine, username, password, vmpool_id):
    def parseVmPoolType(resource, version):
        return resource['type']
    return getResource(engine, username, password, 'vmpools', vmpool_id, 'vm_pool', parseVmPoolType)


def getVmPoolPermissions(engine, username, password, vmpool_id):
    return getResourceChildren(engine, username, password, 'vmpools', vmpool_id, 'permissions', 'permissions', 'permission', parsePermission)


def getVmPoolPermissionIds(engine, username, password, vmpool_id):
    return getResourceChildren(engine, username, password, 'vmpools', vmpool_id, 'permissions', 'permissions', 'permission', parseResourceId)


#################################################################
#
# Template Related
#
#################################################################
def getTemplateInfo(engine, username, password, template_id):
    return getResource(engine, username, password, 'templates', template_id, 'template', parseTemplate)


def getTemplateName(engine, username, password, template_id):
    def parseTemplateName(resource, version):
        return resource['name']
    return getResource(engine, username, password, 'templates', template_id, 'template', parseTemplateName)


def getTemplateType(engine, username, password, template_id):
    def parseTemplateType(resource, version):
        return resource['type']
    return getResource(engine, username, password, 'templates', template_id, 'template', parseTemplateType)


def getTemplateStatus(engine, username, password, template_id):
    def parseTemplateStatus(resource, version):
        if version['major'] == '4':
            return resource['status']
        else:
            return resource['status']['state']
    return getResource(engine, username, password, 'templates', template_id, 'template', parseTemplateStatus)


def getTemplateMemory(engine, username, password, template_id):
    def parseTemplateMemory(resource, version):
        return str(int(resource['memory'])/1024/1024/1024)
    return getResource(engine, username, password, 'templates', template_id, 'template', parseTemplateMemory)


def getTemplateCpuSockets(engine, username, password, template_id):
    def parseTemplateCpuSockets(resource, version):
        if version['major'] == '4':
            return resource['cpu']['topology']['sockets']
        else:
            return resource['cpu']['topology']['@sockets']
    return getResource(engine, username, password, 'templates', template_id, 'template', parseTemplateCpuSockets)


def getTemplateCpuCores(engine, username, password, template_id):
    def parseTemplateCpuCores(resource, version):
        if version['major'] == '4':
            return resource['cpu']['topology']['cores']
        else:
            return resource['cpu']['topology']['@cores']
    return getResource(engine, username, password, 'templates', template_id, 'template', parseTemplateCpuCores)


def getTemplateCpuThreads(engine, username, password, template_id):
    def parseTemplateCpuThreads(resource, version):
        if version['major'] == '4':
            return resource['cpu']['topology']['threads']
        else:
            return resource['cpu']['topology']['@threads']
    return getResource(engine, username, password, 'templates', template_id, 'template', parseTemplateCpuThreads)


def getTemplateOsType(engine, username, password, template_id):
    def parseTemplateOsType(resource, version):
        if version['major'] == '4':
            return resource['os']['type']
        else:
            return resource['os']['@type']
    return getResource(engine, username, password, 'templates', template_id, 'template', parseTemplateOsType)


def getTemplateCreationTime(engine, username, password, template_id):
    def parseTemplateCreationTime(resource, version):
        return resource['creation_time']
    return getResource(engine, username, password, 'templates', template_id, 'template', parseTemplateCreationTime)


def getTemplateDisplayType(engine, username, password, template_id):
    def parseTemplateDisplayType(resource, version):
        return resource['display']['type']
    return getResource(engine, username, password, 'templates', template_id, 'template', parseTemplateDisplayType)


def getTemplateDisplayMonitors(engine, username, password, template_id):
    def parseTemplateDisplayMonitors(resource, version):
        return resource['display']['monitors']
    return getResource(engine, username, password, 'templates', template_id, 'template', parseTemplateDisplayMonitors)


def getTemplateDisplaySmartCardEnabled(engine, username, password, template_id):
    def parseTemplateDisplaySmartCardEnabled(resource, version):
        return resource['display']['smartcard_enabled']
    return getResource(engine, username, password, 'templates', template_id, 'template', parseTemplateDisplaySmartCardEnabled)


def getTemplateDisplayFileTransferEnabled(engine, username, password, template_id):
    def parseTemplateDisplayFileTransferEnabled(resource, version):
        return resource['display']['file_transfer_enabled']
    return getResource(engine, username, password, 'templates', template_id, 'template', parseTemplateDisplayFileTransferEnabled)


def getTemplateDisplayCopyPasteEnabled(engine, username, password, template_id):
    def parseTemplateDisplayCopyPasteEnabled(resource, version):
        return resource['display']['copy_paste_enabled']
    return getResource(engine, username, password, 'templates', template_id, 'template', parseTemplateDisplayCopyPasteEnabled)


def getTemplateUsbEnabled(engine, username, password, template_id):
    def parseTemplateUsbEnabled(resource, version):
        return resource['usb']['enabled']
    return getResource(engine, username, password, 'templates', template_id, 'template', parseTemplateUsbEnabled)


def getTemplateDiskSize(engine, username, password, template_id):
    def parseTemplateDiskSize(resource, version):
        return resource['size']
    return getResource(engine, username, password, 'templates', template_id, 'template', parseTemplateDiskSize)


def getTemplateDiskActualSize(engine, username, password, template_id):
    def parseTemplateDiskActualSize(resource, version):
        return resource['actual_size']
    return getResource(engine, username, password, 'templates', template_id, 'template', parseTemplateDiskActualSize)


def getTemplateClusterId(engine, username, password, template_id):
    def parseTemplateClusterId(resource, version):
        try:
            return resource['cluster']['@id']
        except:
            return ''
    return getResource(engine, username, password, 'templates', template_id, 'template', parseTemplateClusterId)


def getTemplateDiskAttachments(engine, username, password, template_id):
    version = getVersion(engine, username, password)
    if version['major'] == '4':
        return getResourceChildren(engine, username, password, 'templates', template_id, 'diskattachments', 'disk_attachments', 'disk_attachment', parseResourceId)
    else:
        return getResourceChildren(engine, username, password, 'templates', template_id, 'disks', 'disks', 'disk', parseResourceId)


def getTemplateNics(engine, username, password, template_id):
    return getResourceChildren(engine, username, password, 'templates', template_id, 'nics', 'nics', 'nic', parseTemplateNic)


def getTemplateTags(engine, username, password, template_id):
    return getResourceChildren(engine, username, password, 'templates', template_id, 'tags', 'tags', 'tag', parseTag)


def getTemplatePermissions(engine, username, password, template_id):
    return getResourceChildren(engine, username, password, 'templates', template_id, 'permissions', 'permissions', 'permission', parsePermission)



def getTemplateDiskAttachmentIds(engine, username, password, template_id):
    version = getVersion(engine, username, password)
    if version['major'] == '4':
        return getResourceChildren(engine, username, password, 'templates', template_id, 'diskattachments', 'disk_attachments', 'disk_attachment', parseResourceId)
    else:
        return getResourceChildren(engine, username, password, 'templates', template_id, 'disks', 'disks', 'disk', parseResourceId)


def getTemplateNicIds(engine, username, password, template_id):
    return getResourceChildren(engine, username, password, 'templates', template_id, 'nics', 'nics', 'nic', parseResourceId)


def getTemplateCdromIds(engine, username, password, template_id):
    return getResourceChildren(engine, username, password, 'templates', template_id, 'cdroms', 'cdroms', 'cdrom', parseResourceId)


def getTemplateTagIds(engine, username, password, template_id):
    return getResourceChildren(engine, username, password, 'templates', template_id, 'tags', 'tags', 'tag', parseResourceId)


def getTemplatePermissionIds(engine, username, password, template_id):
    return getResourceChildren(engine, username, password, 'templates', template_id, 'permissions', 'permissions', 'permission', parseResourceId)


def getTemplateWatchDogIds(engine, username, password, template_id):
    return getResourceChildren(engine, username, password, 'templates', template_id, 'watchdogs', 'watchdogs', 'watchdog', parseResourceId)


def getTemplateGraphicsConsoleIds(engine, username, password, template_id):
    return getResourceChildren(engine, username, password, 'templates', template_id, 'graphicsconsoles', 'graphicsconsoles', 'graphicsconsole', parseResourceId)



#################################################################
#
# Domain Related
#
#################################################################
def getDomainInfo(engine, username, password, domain_id):
    return getResource(engine, username, password, 'domains', domain_id, 'domain', parseDomain)


def getDomainName(engine, username, password, domain_id):
    def parseDomainName(resource, version):
        return resource['name']
    return getResource(engine, username, password, 'domains', domain_id, 'domain', parseDomainName)


def getDomainUsers(engine, username, password, domain_id):
    return getResourceChildren(engine, username, password, 'domains', domain_id, 'users', 'users', 'user', parseDomainUser)


def getDomainGroups(engine, username, password, domain_id):
    return getResourceChildren(engine, username, password, 'domains', domain_id, 'groups', 'groups', 'group', parseDomainGroup)


def getDomainUserIds(engine, username, password, domain_id):
    return getResourceChildren(engine, username, password, 'domains', domain_id, 'users', 'users', 'user', parseResourceId)


#################################################################
#
# User Related
#
#################################################################
def getUserInfo(engine, username, password, user_id):
    return getResource(engine, username, password, 'users', user_id, 'user', parseUser)


def getUserName(engine, username, password, user_id):
    def parseUserName(resource, version):
        return resource['name']
    return getResource(engine, username, password, 'users', user_id, 'user', parseUserName)


def getUserUserName(engine, username, password, user_id):
    def parseUserUserName(resource, version):
        return resource['user_name']
    return getResource(engine, username, password, 'users', user_id, 'user', parseUserUserName)


def getUserLastName(engine, username, password, user_id):
    def parseUserLastName(resource, version):
        try:
            return resource['last_name']
        except:
            return ''               #admin@internal没有这个域
    return getResource(engine, username, password, 'users', user_id, 'user', parseUserLastName)


def getUserNameSpace(engine, username, password, user_id):
    def parseUserNameSpace(resource, version):
        return resource['namespace']
    return getResource(engine, username, password, 'users', user_id, 'user', parseUserNameSpace)


def getUserEmail(engine, username, password, user_id):
    def parseUserEmail(resource, version):
        try:
            return resource['email']
        except:
            return ''               #有些用户没有邮箱
    return getResource(engine, username, password, 'users', user_id, 'user', parseUserEmail)


#def getUserGroups(engine, username, password, user_id):
#    user = requestResource(engine, username, password, 'users', user_id)
#    return user['user']['groups']


def getUserDomainEntryId(engine, username, password, user_id):
    def parseUserDomainEntryId(resource, version):
        return resource['domain_entry_id']
    return getResource(engine, username, password, 'users', user_id, 'user', parseUserDomainEntryId)


def getUserDomainId(engine, username, password, user_id):
    def parseUserDomainId(resource, version):
        return resource['domain']['@id']
    return getResource(engine, username, password, 'users', user_id, 'user', parseUserDomainId)


def getUserDomainName(engine, username, password, user_id):
    def parseUserDomainName(resource, version):
        return resource['domain']['name']
    return getResource(engine, username, password, 'users', user_id, 'user', parseUserDomainName)


def getUserTags(engine, username, password, user_id):
    #由于oVirt RestClient API的BUG，直接提取description获得空字符串
    return getResourceChildren(engine, username, password, 'users', user_id, 'tags', 'tags', 'tag', parseTag)


def getUserRoles(engine, username, password, user_id):
    return getResourceChildren(engine, username, password, 'users', user_id, 'roles', 'roles', 'role', parseRole)


def getUserPermissions(engine, username, password, user_id):
    return getResourceChildren(engine, username, password, 'users', user_id, 'permissions', 'permissions', 'permission', parsePermission)


def getUserPermissionVmIds(engine, username, password, user_id):
    rvms = []
    for permission in getUserPermissions(engine, username, password, user_id):
        vm = permission['vm']
        if vm != '' and not vm in rvms:
            rvms.append(vm)
    return rvms


def getUserTagIds(engine, username, password, user_id):
    return getResourceChildren(engine, username, password, 'users', user_id, 'tags', 'tags', 'tag', parseResourceId)


def getUserRoleIds(engine, username, password, user_id):
    return getResourceChildren(engine, username, password, 'users', user_id, 'roles', 'roles', 'role', parseResourceId)


def getUserPermissionIds(engine, username, password, user_id):
    return getResourceChildren(engine, username, password, 'users', user_id, 'permissions', 'permissions', 'permission', parseResourceId)


def getUserSshPublicKeyIds(engine, username, password, user_id):
    return getResourceChildren(engine, username, password, 'users', user_id, 'sshpublickeys', 'sshpublickeys', 'sshpublickey', parseResourceId)


#################################################################
#
# Group Related
#
#################################################################
def getGroupInfo(engine, username, password, group_id):
    return getResource(engine, username, password, 'groups', group_id, 'group', parseGroup)


def getGroupName(engine, username, password, group_id):
    def parseGroupName(resource, version):
        return resource['name']
    return getResource(engine, username, password, 'groups', group_id, 'group', parseGroupName)


def getGroupNameSpace(engine, username, password, group_id):
    def parseGroupNameSpace(resource, version):
        return resource['namespace']
    return getResource(engine, username, password, 'groups', group_id, 'group', parseGroupNameSpace)


def getGroupDomainEntryId(engine, username, password, group_id):
    def parseGroupDomainEntryId(resource, version):
        return resource['namespace']
    return getResource(engine, username, password, 'groups', group_id, 'group', parseGroupDomainEntryId)


def getGroupDomainId(engine, username, password, group_id):
    def parseGroupDomainId(resource, version):
        try:
            return resource['domain']['@id']
        except:
            return ''       #有些组（例如Everyone）是没有任何域的
    return getResource(engine, username, password, 'groups', group_id, 'group', parseGroupDomainId)


def getGroupDomainName(engine, username, password, group_id):
    def parseGroupDomainName(resource, version):
        try:
            return resource['domain']['name']
        except:
            return ''       #有些组（例如Everyone）是没有任何域的
    return getResource(engine, username, password, 'groups', group_id, 'group', parseGroupDomainName)


def getGroupTags(engine, username, password, group_id):
   return getResourceChildren(engine, username, password, 'groups', group_id, 'tags', 'tags', 'tag', parseTag)


def getGroupRoles(engine, username, password, group_id):
   return getResourceChildren(engine, username, password, 'groups', group_id, 'roles', 'roles', 'role', parseRole)


def getGroupPermissions(engine, username, password, group_id):
   return getResourceChildren(engine, username, password, 'groups', group_id, 'permissions', 'permissions', 'permission', parseRole)


def getDomainGroupIds(engine, username, password, domain_id):
    return getResourceChildren(engine, username, password, 'domains', domain_id, 'groups', 'groups', 'group', parseResourceId)


def getGroupTagIds(engine, username, password, group_id):
    return getResourceChildren(engine, username, password, 'groups', group_id, 'tags', 'tags', 'tag', parseResourceId)


def getGroupRoleIds(engine, username, password, group_id):
    return getResourceChildren(engine, username, password, 'groups', group_id, 'roles', 'roles', 'role', parseResourceId)


def getGroupPermissionIds(engine, username, password, group_id):
    return getResourceChildren(engine, username, password, 'groups', group_id, 'permissions', 'permissions', 'permission', parseResourceId)


#################################################################
#
# Tag Related
#
#################################################################
def getTagInfo(engine, username, password, tag_id):
    return getResource(engine, username, password, 'tags', tag_id, 'tag', parseTag)


def getTagName(engine, username, password, tag_id):
    def parseTagName(resource, version):
        return resource['name']
    return getResource(engine, username, password, 'tags', tag_id, 'tag', parseTagName)


def getTagDescription(engine, username, password, tag_id):
    def parseTagDescription(resource, version):
        try:
            return resource['description']
        except Exception, e:
            return ''
    return getResource(engine, username, password, 'tags', tag_id, 'tag', parseTagDescription)


def getTagParentId(engine, username, password, tag_id):
    def parseTagParentId(resource, version):
        try:
            return resource['parent']['@id']
        except Exception, e:
            return ''                       #root标签没有parent
    return getResource(engine, username, password, 'tags', tag_id, 'tag', parseTagParentId)


#################################################################
#
# Bookmark Related
#
#################################################################
def getBookmarkInfo(engine, username, password, bookmark_id):
    return getResource(engine, username, password, 'bookmarks', bookmark_id, 'bookmark', parseBookmark)


def getBookmarkName(engine, username, password, bookmark_id):
    def parseBookmarkName(resource, version):
        return resource['name']
    return getResource(engine, username, password, 'bookmarks', bookmark_id, 'bookmark', parseBookmarkName)


#################################################################
#
# Role Related
#
#################################################################
def getRoleInfo(engine, username, password, role_id):
    return getResource(engine, username, password, 'roles', role_id, 'role', parseRole)


def getRoleName(engine, username, password, role_id):
    def parseRoleName(resource, version):
        return resource['name']
    return getResource(engine, username, password, 'roles', role_id, 'role', parseRoleName)


def getRoleDescription(engine, username, password, role_id):
    def parseRoleDescription(resource, version):
        try:
            return resource['description']
        except:
            return ''
    return getResource(engine, username, password, 'roles', role_id, 'role', parseRoleDescription)


def getRoleMutable(engine, username, password, role_id):
    def parseRoleMutable(resource, version):
        return resource['mutable']
    return getResource(engine, username, password, 'roles', role_id, 'role', parseRoleMutable)


def getRoleAdministrative(engine, username, password, role_id):
    def parseRoleAdministrative(resource, version):
        return resource['administrative']
    return getResource(engine, username, password, 'roles', role_id, 'role', parseRoleAdministrative)


def getRolePermits(engine, username, password, role_id):
    return getResourceChildren(engine, username, password, 'roles', role_id, 'permits', 'permits', 'permit', parsePermit)


def getRolePermitIds(engine, username, password, role_id):
    return getResourceChildren(engine, username, password, 'roles', role_id, 'permits', 'permits', 'permit', parseResourceId)


#################################################################
#
# Permission Related
#
#################################################################
def getPermissionInfo(engine, username, password, permission_id):
    return getResource(engine, username, password, 'permissions', permission_id, 'permission', parsePermission)


def getPermissionRoleId(engine, username, password, permission_id):
    def parsePermissionRoleId(resource, version):
        return resource['role']['@id']
    return getResource(engine, username, password, 'permissions', permission_id, 'permission', parsePermissionRoleId)


def getPermissionUserId(engine, username, password, permission_id):
    def parsePermissionUserId(resource, version):
        try:
            return resource['user']['@id']
        except:
            return ''
    return getResource(engine, username, password, 'permissions', permission_id, 'permission', parsePermissionUserId)


def getPermissionGroupId(engine, username, password, permission_id):
    def parsePermissionGroupId(resource, version):
        try:
            return resource['group']['@id']
        except:
            return ''
    return getResource(engine, username, password, 'permissions', permission_id, 'permission', parsePermissionGroupId)


#def getUserPermissionRoleId(engine, username, password, user_id, permission_id):
#    permission = requestResourceChild(engine, username, password, 'users', user_id, 'permissions', permission_id)
#    return permission['permission']['role']['@id']


#def getUserPermissionVmId(engine, username, password, user_id, permission_id):
#    permission = requestResourceChild(engine, username, password, 'users', user_id, 'permissions', permission_id)
#    return permission['permission']['vm']['@id']



#################################################################
#
# Job Related
#
#################################################################
def getJobStatus(engine, username, password, job_id):
    def parseJobStatus(resource, version):
        if version['major'] == '4':
            return resource['status']
        else:
            return resource['status']['state']
    return getResource(engine, username, password, 'jobs', job_id, 'job', parseJobStatus)


#################################################################
#
# Data Center Update Logic
#
#################################################################
def createDataCenter(engine, username, password, name, storage_type, version):
    url = "https://" + engine + "/api/datacenters/"
    data = "<data_center><name>%s</name><storage_type>%s</storage_type><version minor='%s' major='%s'/></data_center>" % (name, storage_type, version['minor'], version['major'])
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'POST', data, headers)


def updateDataCenterName(engine, username, password, datacenter_id, name):
    url = "https://" + engine + "/api/datacenters/" + datacenter_id
    data = "<data_center><name>%s</name></data_center>" % name
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'PUT', data, headers)

    
def updateDataCenterDescription(engine, username, password, datacenter_id, description):
    url = "https://" + engine + "/api/datacenters/" + datacenter_id
    data = "<data_center><description>%s</description></data_center>" % description
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'PUT', data, headers)


def updateDataCenterLocal(engine, username, password, datacenter_id, local):
    url = "https://" + engine + "/api/datacenters/" + datacenter_id
    data = "<data_center><local>%s</local></data_center>" % local
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'PUT', data, headers)


def removeDataCenter(engine, username, password, datacenter_id):
    url = "https://" + engine + "/api/datacenters/" + datacenter_id
    return request2virtengine(url, username, password, 'DELETE', '', {})


def attachDataCenterStorageDomain(engine, username, password, datacenter_id, storagedomain_id):
    url = "https://" + engine + "/api/datacenters/" + datacenter_id + "/storagedomains/"
    data = "<storage_domain id='%s' />" % storagedomain_id
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'POST', data, headers)


def activateDataCenterStorageDomain(engine, username, password, datacenter_id, storagedomain_id):
    url = "https://" + engine + "/api/datacenters/" + datacenter_id + "/storagedomains/" + storagedomain_id + "/activate/"
    data = "<action />"
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'POST', data, headers)


def deactivateDataCenterStorageDomain(engine, username, password, datacenter_id, storagedomain_id):
    url = "https://" + engine + "/api/datacenters/" + datacenter_id + "/storagedomains/" + storagedomain_id + "/deactivate/"
    data = "<action />"
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'POST', data, headers)


def addDataCenterPermission(datacenter_id):
    pass


def removeDataCenterPermission(datacenter_id):
    pass


#################################################################
#
# Cluster Update Logic
#
#################################################################
def createCluster(engine, username, password, name, cpu_id, datacenter_id):
    url = "https://" + engine + "/api/clusters/"
    data = "<cluster><name>%s</name><cpu id='%s' /><data_center id='%s' /></cluster>" % (name, cpu_id, datacenter_id)
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'POST', data, headers)


def updateClusterName(engine, username, password, cluster_id, name):
    url = "https://" + engine + "/api/clusters/" + cluster_id
    data = "<cluster><name>%s</name></cluster>" % name
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'PUT', data, headers)


def updateClusterDescription(engine, username, password, cluster_id, description):
    url = "https://" + engine + "/api/clusters/" + cluster_id
    data = "<cluster><description>%s</description></cluster>" % description
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'PUT', data, headers)


def removeCluster(engine, username, password, cluster_id):
    url = "https://" + engine + "/api/clusters/" + cluster_id
    return request2virtengine(url, username, password, 'DELETE', '', {})


def associateClusterNetwork(engine, username, password, cluster_id, network_name):
    url = "https://" + engine + "/api/clusters/" + cluster_id + "/networks/"
    data = "<network><name>%s</name></network>" % network_name
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'POST', data, headers)


def removeClusterNetwork(engine, username, password, cluster_id, network_id):
    url = "https://" + engine + "/api/clusters/" + cluster_id + "/networks/" + network_id
    return request2virtengine(url, username, password, 'DELETE', '', {})


def addClusterPermission(cluster_id):
    pass


def removeClusterPermission(cluster_id):
    pass


#################################################################
#
# Host Update Logic
#
#################################################################
def createHost(engine, username, password, name, address, rpassword):
    url = "https://" + engine + "/api/hosts/"
    data = "<host><name>%s</name><address>%s</address><root_password>%s</root_password></host>" % (name, address, rpassword)
    headers = {'Content-Type': 'application/xml'}
    response = request2virtengine(url, username, password, 'POST', data, headers)
    hid = None
    try:
        hid = response['host']['@id']
    except Exception, e:
        pass
    return hid


def InstallHost(engine, username, password, hostname, ipaddress, root_password):
    url = "https://" + engine + "/api/hosts"
    data = "<host><name>%s</name><address>%s</address><root_password>%s</root_password></host>" % (hostname, ipaddress, root_password)
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'POST', data, headers)


def updateHostName(engine, username, password, host_id, name):
    url = "https://" + engine + "/api/hosts/" + host_id
    data = "<host><name>%s</name></host>" % name
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'PUT', data, headers)


def removeHost(engine, username, password, host_id):
    url = "https://" + engine + "/api/hosts/" + host_id
    return request2virtengine(url, username, password, 'DELETE', '', {})


def activateHost(engine, username, password, host_id):
    url = "https://" + engine + "/api/hosts/" + host_id + "/activate/"
    data = "<action />"
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'POST', data, headers)


def deactivateHost(engine, username, password, host_id):
    url = "https://" + engine + "/api/hosts/" + host_id + "/deactivate/"
    data = "<action />"
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'POST', data, headers)


def approveHost(engine, username, password, host_id):
    url = "https://" + engine + "/api/hosts/" + host_id + "/approve/"
    data = "<action />"
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'POST', data, headers)


def commitHostNetworkConfig(engine, username, password, host_id):
    url = "https://" + engine + "/api/hosts/" + host_id + "/commitnetconfig/"
    data = "<action />"
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'POST', data, headers)


def fenceHost(engine, username, password, host_id, fence_type):
    url = "https://" + engine + "/api/hosts/" + host_id + "/fence/"
    data = "<action><fence_type>%s</fence_type></action>" % fence_type
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'POST', data, headers)


def attachHostNics(engine, username, password, host_id, network_id):  #nics_id or network_id (aoqingy)
    url = "https://" + engine + "/api/hosts/" + host_id + "/nics/" + network_id + "/attach/"
    data = "<action><network id='%s'></action>" % network_id
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'POST', data, headers)


def detachHostNics(engine, username, password, host_id, network_id):  #nics_id or network_id (aoqingy)
    url = "https://" + engine + "/api/hosts/" + host_id + "/nics/" + network_id + "/detach/"
    data = "<action><network id='%s'></action>" % network_id
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'POST', data, headers)


#Storage
#NumaNode
#Permissions
#Hooks


def addHostTag(engine, username, password, host_id, tag_name):
    url = "https://" + engine + "/api/hosts/" + host_id + "/tags/"
    data = "<tag><name>%s</name></tag>" % tag_name
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'POST', data, headers)


def removeHostTag(engine, username, password, host_id, tag_id):
    url = "https://" + engine + "/api/hosts/" + host_id + "/tags/" + tag_id
    return request2virtengine(url, username, password, 'DELETE', '', {})


#################################################################
#
# Network Update Logic
#
#################################################################
def createNetwork(engine, username, password, name, datacenter_id):
    url = "https://" + engine + "/api/networks/"
    data = "<network><name>%s</name><data_center id=%s /></network>" % (name, datacenter_id)
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'POST', data, headers)


def updateNetworkName(engine, username, password, network_id, name):
    url = "https://" + engine + "/api/networks/" + network_id
    data = "<network><name>%s</name></network>" % name
    headers = {'Content-Type': 'application/xml'}
    response = request2virtengine(url, username, password, 'PUT', data, headers)
    return response['network']['@id']


def updateNetworkDescription(engine, username, password, network_id, description):
    url = "https://" + engine + "/api/networks/" + network_id
    data = "<network><description>%s</description></network>" % description
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'PUT', data, headers)


def removeNetwork(engine, username, password, network_id):
    url = "https://" + engine + "/api/networks/" + network_id
    return request2virtengine(url, username, password, 'DELETE', '', {})


def createNetworkNicProfile(engine, username, password, network_id, nicprofile_name):
    url = "https://" + engine + "/api/networks/" + network_id + "/nicprofiles/"
    data = '<vnic_profile><name>%s</name></vnic_profile>' % nicprofile_name
    headers = {'Content-Type': 'application/xml'}
    response = request2virtengine(url, username, password, 'POST', data, headers)
    return response['vnic_profile']['@id']


def updateNicProfileCustomProperty(engine, username, password, nicprofile_id, property_name, property_value):
    url = "https://" + engine + "/api/nicprofiles/"
    data = '<vnic_profile><custom_properties><custom_property name="%s" value="%s"/></custom_properties></vnic_profile>' % (property_name, property_value)
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'PUT', data, headers)


def removeNetworkNicProfile(engine, username, password, nicprofile_id):
    url = "https://" + engine + "/api/nicprofiles/" + nicprofile_id
    return request2virtengine(url, username, password, 'DELETE', '', {})


def addNetworkPermission(network_id):
    pass


def removeNetworkPermission(network_id):
    pass


#Label
#createNetworkNicProfile
#updateNicProfileCustomProperty (extnet)
#addVmNic


#################################################################
#
# Storage Domain Update Logic
#
#################################################################
def createStorageDomain(engine, username, password, storagedomain_name, storagedomain_type, host_id, storage_type, storage_params):
    url     = "https://" + engine + "/api/storagedomains/"
    headers = {'Content-Type': 'application/xml'}
    if storage_type == 'nfs':
        data = "<storage_domain><name>%s</name><type>%s</type><host id='%s' /><storage><type>%s</type><address>%s</address><path>%s</path></storage></storage_domain>" % (storagedomain_name, storagedomain_type, host_id, storage_type, storage_params['address'], storage_params['path'])
    elif storage_type == 'localfs':
        data = "<storage_domain><name>%s</name><type>%s</type><host id='%s' /><storage><type>%s</type><path>%s</path></storage></storage_domain>" % (storagedomain_name, storagedomain_type, host_id, storage_type, storage_params['path'])
    elif storage_type == 'glusterfs':
        data = ""                       #To handle (aoqingy)
    else:
        raise Exception('Invalid storage type!')

    response = request2virtengine(url, username, password, 'POST', data, headers)
    sdid = None
    try:
        sdid = response['storage_domain']['@id']
    except Exception, e:
        pass
    return sdid


def updateStorageDomainName(engine, username, password, storagedomain_id, storagedomain_name):
    url = "https://" + engine + "/api/storagedomains/" + storagedomain_id
    data = "<storage_domain><name>%s</name></storage_domain>" % storagedomain_name
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'PUT', data, headers)


def removeStorageDomain(engine, username, password, storagedomain_id):
    url = "https://" + engine + "/api/storagedomains/" + storagedomain_id
    return request2virtengine(url, username, password, 'DELETE', '', {})


def importExportStorageDomainVm(engine, username, password, storagedomain_id):
    pass


def importExportStorageDomainTemplate(engine, username, password, storagedomain_id):
    pass


def removeExportStorageDomainVm(engine, username, password, storagedomain_id, vm_id):
    url = "https://" + engine + "/api/storagedomains/" + storagedomain_id + "/vms/" + vm_id
    return request2virtengine(url, username, password, 'DELETE', '', {})


def removeExportStorageDomainTemplate(engine, username, password, storagedomain_id, template_id):
    url = "https://" + engine + "/api/storagedomains/" + storagedomain_id + "/templates/" + template_id
    return request2virtengine(url, username, password, 'DELETE', '', {})


def CreateISODomain(engine, username, password, domain_name, nfs_ip, nfs_path, mount_host):
    url = "https://" + engine + "/api/storagedomains"
    data = "<storage_domain><name>%s</name><type>iso</type><storage><type>nfs</type><address>%s</address><path>%s</path></storage><host><name>%s</name></host></storage_domain>" % (domain_name, nfs_ip, nfs_path, mount_host)
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'POST', data, headers)


def CreateExportDomain(engine, username, password, domain_name, nfs_ip, nfs_path, mount_host):  #aoqingy
    url = "https://" + engine + "/api/storagedomains"
    data = "<storage_domain><name>%s</name><type>export</type><storage><type>nfs</type><address>%s</address><path>%s</path></storage><host><name>%s</name></host></storage_domain>" % (domain_name, nfs_ip, nfs_path, mount_host)
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'POST', data, headers)


#def AttachDomain(dc_uuid, domain_name):
#    url = "https://" + engine + "/api/" + dc_uuid + "/storagedomains"
#    data = "<storage_domain><name>%s</name></storage_domain>" % domain_name
#    return request2virtengine(url, data, headers={'Content-Type': 'application/xml'})


#def ActivateDomain(dc_uuid, domain_uuid):
#    url = "https://" + engine + "/api/" + dc_uuid + "/storagedomains/" + domain_uuid + "/activate"
#    data = "<action/>"
#    return request2virtengine(url, data, headers={'Content-Type': 'application/xml'})


def CreateNFSDataDomain(engine, username, password, domain_name, nfs_ip, nfs_path, mount_host):
    url = "https://" + engine + "/api/storagedomains"
    data = "<storage_domain><name>%s</name><type>data</type><storage><type>nfs</type><address>%s</address><path>%s</path></storage><host><name>%s</name></host></storage_domain>" % (domain_name, nfs_ip, nfs_path, mount_host)
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'POST', data, headers)


def addStorageDomainPermission(storagedomain_id):
    pass


def removeStorageDomainPermission(storagedomain_id):
    pass


#Disks
#StorageConnections
#DiskSnapshots
#DiskProfiles


#################################################################
#
# Vm Update Logic
#
#################################################################
def createVm(engine, username, password, name, template_id, cluster_id):
    url     = "https://" + engine + "/api/vms/"
    headers = {'Content-Type': 'application/xml'}
    data    = "<vm><name>%s</name><cluster id=\"%s\"></cluster><template id=\"%s\"></template></vm>" % (name, cluster_id, template_id)
    response = request2virtengine(url, username, password, 'POST', data, headers)
    rid = None
    try:
        rid = response['vm']['@id']
    except Exception, e:
        pass
    return rid


def createVm2(engine, username, password, name, template_id, cluster_id, disk_storagedomain_ids):
    url     = "https://" + engine + "/api/vms/"
    headers = {'Content-Type': 'application/xml'}
    #data = "<vm><name>%s</name><cluster id=\"%s\"></cluster><template id=\"%s\"></template></vm>" % (name, cluster_id, template_id)
    data    = "<vm><name>%s</name><cluster id=\"%s\"></cluster><template id=\"%s\"></template>" % (name, cluster_id, template_id)
    data += "<disks><clone>True</clone>"
    for dsdid in disk_storagedomain_ids:
        data += "<disk id=\"%s\"><storage_domains><storage_domain id=\"%s\"/></storage_domains></disk>" % (dsdid['did'], dsdid['sdid'])
    data += "</disks>"
    data += "</vm>"
    response = request2virtengine(url, username, password, 'POST', data, headers)
    rid = None
    try:
        rid = response['vm']['@id']
    except Exception, e:
        pass
    return rid


def updateVmName(engine, username, password, vm_id, name):
    url     = "https://" + engine + "/api/vms/" + vm_id
    headers = {'Content-Type': 'application/xml'}
    data    = "<vm><name>%s</name></vm>" % name
    request2virtengine(url, username, password, 'PUT', data, headers)


def updateVmDescription(engine, username, password, vm_id, description):
    url     = "https://" + engine + "/api/vms/" + vm_id
    headers = {'Content-Type': 'application/xml'}
    data    = "<vm><description>%s</description></vm>" % description
    request2virtengine(url, username, password, 'PUT', data, headers)


def updateVmTimeZone(engine, username, password, vm_id, timezone='Asia/Shanghai'):#Chinese Startd Time
    url     = "https://" + engine + "/api/vms/" + vm_id
    headers = {'Content-Type': 'application/xml'}
    version = getVersion(engine, username, password)
    if version['major'] == '4':
        data    = "<vm><time_zone><name>%s</name></time_zone></vm>" % timezone
    else:
        data    = "<vm><timezone>%s</timezone></vm>" % timezone
    request2virtengine(url, username, password, 'PUT', data, headers)


def updateVmOsType(engine, username, password, vm_id, ostype):
    url     = "https://" + engine + "/api/vms/" + vm_id
    headers = {'Content-Type': 'application/xml'}
    version = getVersion(engine, username, password)
    if version['major'] == '4':
        data = "<vm><os><type>%s</type></os></vm>" % ostype
    else:
        data = "<vm><os type=\"%s\"></os></vm>" % ostype
    request2virtengine(url, username, password, 'PUT', data, headers)


def updateVmMemory(engine, username, password, vm_id, memory):
    url     = "https://" + engine + "/api/vms/" + vm_id
    headers = {'Content-Type': 'application/xml'}
    data    = "<vm><memory>%s</memory></vm>" % str(int(memory)*1024*1024)		#<vm><memory>2147483648</memory></vm>
    request2virtengine(url, username, password, 'PUT', data, headers)


def updateVmCpu(engine, username, password, vm_id, cpu):
    url     = "https://" + engine + "/api/vms/" + vm_id
    headers = {'Content-Type': 'application/xml'}
    version = getVersion(engine, username, password)
    if version['major'] == '4':
        data    = "<vm><cpu><topology><cores>%s</cores><sockets>1</sockets><threads>1</threads></topology></cpu></vm>" % cpu
    else:
        data    = "<vm><cpu><topology sockets=\"1\" cores=\"%s\"/></cpu></vm>" % cpu	#<vm><cpu><topology sockets="1" cores="4"/></cpu></vm>
    request2virtengine(url, username, password, 'PUT', data, headers)


def updateVmStateless(engine, username, password, vm_id, stateless):
    url     = "https://" + engine + "/api/vms/" + vm_id
    headers = {'Content-Type': 'application/xml'}
    data    = "<vm><stateless>%s</stateless></vm>" % stateless			#<vm><stateless>true</stateless></vm>
    request2virtengine(url, username, password, 'PUT', data, headers)


def updateVmDeleteProtected(engine, username, password, vm_id, dprotected):
    url     = "https://" + engine + "/api/vms/" + vm_id
    headers = {'Content-Type': 'application/xml'}
    data    = "<vm><delete_protected>%s</delete_protected></vm>" % dprotected	#<vm><delete_protected>true</delete_protected></vm>
    request2virtengine(url, username, password, 'PUT', data, headers)


def updateVmUsbPolicy(engine, username, password, vm_id, usbpolicy):
    url     = "https://" + engine + "/api/vms/" + vm_id
    headers = {'Content-Type': 'application/xml'}
    if usbpolicy == 'true':
        data = "<vm><usb><enabled>true</enabled><type>native</type></usb></vm>"	#<vm><usb><enabled>true</enabled></usb></vm>
    else:
        data = "<vm><usb><enabled>false</enabled></usb></vm>"
    request2virtengine(url, username, password, 'PUT', data, headers)


def updateVmProtocol(engine, username, password, vm_id, protocol):
    url     = "https://" + engine + "/api/vms/" + vm_id
    headers = {'Content-Type': 'application/xml'}
    data    = "<vm><memory>%s</memory></vm>" % protocol
    request2virtengine(url, username, password, 'PUT', data, headers)


def updateVmMonitor(engine, username, password, vm_id, monitor):
    url     = "https://" + engine + "/api/vms/" + vm_id
    headers = {'Content-Type': 'application/xml'}
    data    = "<vm><memory>%s</memory></vm>" % monitor
    request2virtengine(url, username, password, 'PUT', data, headers)


def activateVmNic(engine, username, password, vm_id, nic_id):
    url     = "https://" + engine + "/api/vms/" + vm_id + "/nics/" + nic_id + "/activate"
    headers = {'Content-Type': 'application/xml'}
    data    = "<action />"
    request2virtengine(url, username, password, 'POST', data, headers)


def deactivateVmNic(engine, username, password, vm_id, nic_id):
    #对旧版本不可用？(aoqingy)
    url     = "https://" + engine + "/api/vms/" + vm_id + "/nics/" + nic_id + "/deactivate"
    headers = {'Content-Type': 'application/xml'}
    data    = "<action />"
    request2virtengine(url, username, password, 'POST', data, headers)


def removeVm(engine, username, password, vm_id):
    url = "https://" + engine + "/api/vms/" + vm_id
    return request2virtengine(url, username, password, 'DELETE', '', {})


def runonceVm(engine, username, password, vm_id, iso_file_id, vfd_file_id):
    url     = "https://" + engine + "/api/vms/" + vm_id + "/start/"
    headers = {'Content-Type': 'application/xml'}

    version = getVersion(engine, username, password)
    if version['major'] == '4':
        data    = "<action><vm><floppies><floppy><file id='%s'/></floppy></floppies><cdroms><cdrom><file id='%s'/></cdrom></cdroms><os><boot><devices><device>cdrom</device></devices></boot></os></vm></action>" % (vfd_file_id, iso_file_id)
    else:
        data    = "<action><vm><floppies><floppy><file id='%s'/></floppy></floppies><cdroms><cdrom><file id='%s'/></cdrom></cdroms><os><boot dev='cdrom'/></os></vm></action>" % (vfd_file_id, iso_file_id)
    request2virtengine(url, username, password, 'POST', data, headers)


def startVm(engine, username, password, vm_id):
    url = "https://" + engine + "/api/vms/" + vm_id + "/start/"
    data = "<action />"
    headers = {'Content-Type': 'application/xml'}
    response = request2virtengine(url, username, password, 'POST', data, headers)
    return response['action']['job']['@id']


def rebootVm(engine, username, password, vm_id):
    url = "https://" + engine + "/api/vms/" + vm_id + "/reboot/"
    data = "<action />"
    headers = {'Content-Type': 'application/xml'}
    response = request2virtengine(url, username, password, 'POST', data, headers)
    return response['action']['job']['@id']


def stopVm(engine, username, password, vm_id):
    url = "https://" + engine + "/api/vms/" + vm_id + "/stop/"
    data = "<action />"
    headers = {'Content-Type': 'application/xml'}
    response = request2virtengine(url, username, password, 'POST', data, headers)
    return response['action']['job']['@id']


def shutdownVm(engine, username, password, vm_id):
    url = "https://" + engine + "/api/vms/" + vm_id + "/shutdown/"
    data = "<action />"
    headers = {'Content-Type': 'application/xml'}
    response = request2virtengine(url, username, password, 'POST', data, headers)
    return response['action']['job']['@id']


def suspendVm(engine, username, password, vm_id):
    url = "https://" + engine + "/api/vms/" + vm_id + "/suspend/"
    data = "<action />"
    headers = {'Content-Type': 'application/xml'}
    response = request2virtengine(url, username, password, 'POST', data, headers)
    return response['action']['job']['@id']


def migrateVm(engine, username, password, vm_id, host_id):
    url = "https://" + engine + "/api/vms/" + vm_id + "/migrate/"
    if host_id:
        data = "<action><host id='%s'/></action>" % host_id
    else:
        data = "<action />"
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'POST', data, headers)


def setVmTicket(engine, username, password, vm_id, timeout):
    url = "https://" + engine + "/api/vms/" + vm_id + "/ticket/"
    data = "<action><ticket><expiry>%s</expiry></ticket></action>" % str(timeout)
    headers = {'Content-Type': 'application/xml'}
    response = request2virtengine(url, username, password, 'POST', data, headers)
    rticket = None
    try:
        rticket = response['action']['ticket']['value']
    except Exception, e:
        pass
    return rticket


def exportVm(vm_id):
    pass


def addVmDisk(engine, username, password, vm_id, storagedomain_id, size, interface = 'virtio', format='cow', sparse='true', bootable='true', shareable='false'):
    headers = {'Content-Type': 'application/xml'}
    version = getVersion(engine, username, password)
    if version['major'] == '4':
        storagedomain_name = getStorageDomainName(engine, username, password, storagedomain_id)
        url  = "https://" + engine + "/api/vms/" + vm_id + "/diskattachments/"
        data = "<disk_attachment><bootable>%s</bootable><interface>%s</interface><active>true</active><disk><format>%s</format><provisioned_size>%s</provisioned_size><storage_domains><storage_domain><name>%s</name></storage_domain></storage_domains></disk></disk_attachment>" % (bootable, interface, format, size, storagedomain_name)
        response = request2virtengine(url, username, password, 'POST', data, headers)
        return response['disk_attachment']['@id']
    else:
        #data = "<disk><storage_domains><storage_domain id='%s'/></storage_domains><size>%s</size><type>system</type><interface>virtio</interface><format>cow</format><bootable>true</bootable></disk>"
        url  = "https://" + engine + "/api/vms/" + vm_id + "/disks/"
        data = "<disk><storage_domains><storage_domain id='%s'/></storage_domains><size>%s</size><interface>%s</interface><format>%s</format><sparse>%s</sparse><bootable>%s</bootable><shareable>%s</shareable></disk>" % (storagedomain_id, size, interface, format, sparse, bootable, shareable)
        response = request2virtengine(url, username, password, 'POST', data, headers)
        return response['disk']['@id']


def addVmNic(engine, username, password, vm_id, nic_name, network_id):	#network_id? (aoqingy)
    url = "https://" + engine + "/api/vms/" + vm_id + "/nics/"
    data = "<nic><name>%s</name><network id='%s'/><interface>virtio</interface></nic>" % (nic_name, network_id)
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'POST', data, headers)


def updateVmNic():
    pass


def removeVmNic():
    pass


#changeVmCdrom(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, "7ec489e2-3c24-4a14-9230-e3cb7dcf84ad", "00000000-0000-0000-0000-000000000000", "cn_windows_7_professional_with_sp1_x64_dvd_621744.iso", True)
#changeVmFloppy(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, "71260db6-de4b-4a33-83d6-881412227ca7", "00000000-0000-0000-0000-000000000000", "virtio-win-1.6.4_amd64.vfd", True)
def changeVmCdrom(engine, username, password, vm_id, cdrom_id, file_id, online='True'):
    url = "https://" + engine + "/api/vms/" + vm_id + "/cdroms/" + cdrom_id
    if online == 'True':
        url += "?current"
    data = "<cdrom><file id='%s' /></cdrom>" % file_id
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, "PUT", data, headers)


def changeVmBootDev(engine, username, password, vm_id, boot_dev):
    url = "https://" + engine + "/api/vms/" + vm_id
    data = "<vm><os><boot dev='%s'/></os></vm>" % boot_dev
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, "PUT", data, headers)


def addVmSnapshot(engine, username, password, vm_id, description):
    url = "https://" + engine + "/api/vms/" + vm_id + "/snapshots/"
    data = "<snapshot><description>%s</description></snapshot>" % description
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'POST', data, headers)


def previewVmSnapshot(engine, username, password, vm_id, snapshot_id):
    url = "https://" + engine + "/api/vms/" + vm_id + "/snapshots/" + snapshot_id #+ "/prev/"? (aoqingy)
    data = "<action />"
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'POST', data, headers)


def restoreVmSnapshot(engine, username, password, vm_id, snapshot_id):
    url = "https://" + engine + "/api/vms/" + vm_id + "/snapshots/" + snapshot_id + "/restore/"
    data = "<action />"
    headers={'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'POST', data, headers)


def addVmTag(engine, username, password, vm_id, tag_id):
    url = "https://" + engine + "/api/vms/" + vm_id + "/tags/"
    #data = "<tag><name>%s</name></tag>" % tag_name
    data = "<tag id='%s'></tag>" % tag_id
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'POST', data, headers)


def removeVmTag(engine, username, password, vm_id, tag_id):
    url = "https://" + engine + "/api/vms/" + vm_id + "/tags/" + tag_id
    return request2virtengine(url, username, password, 'DELETE', '', {})


#################################################################
#
# Vm Pool Update Logic
#
#################################################################
def createVmPool(engine, username, password, name, template_id, cluster_id):
    url = "https://" + engine + "/api/vmpools/"
    data = "<vmpool><name>%s</name><cluster id='%s' href='/api/clusters/%s'/><template id='%s' href='/api/templates/%s'/></vmpool>" % (name, cluster_id, cluster_id, template_id, template_id)
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'POST', data, headers)		#Do we need href? (aoqingy)


def updateVmPoolSize(engine, username, password, vmpool_id, size):
    url = "https://" + engine + "/api/vmpools/" + vmpool_id
    data = "<vmpool><size>%s</size></vmpool>" % size
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'PUT', data, headers)


def removeVmPool(engine, username, password, vmpool_id):
    url = "https://" + engine + "/api/vmpools/" + vmpool_id
    return request2virtengine(url, username, password, 'DELETE', '', {})


def allocateVm(engine, username, password, vmpool_id):
    url = "https://" + engine + "/api/vmpools/" + vmpool_id + "/allocatevm/"
    data = "<action />"
    headers = {'Content-Type': 'application/xml'}
    response = request2virtengine(url, username, password, 'POST', data, headers)
    return response['action']['vm']['@id']


#################################################################
#
# Template Update Logic
#
#################################################################
def createTemplate(engine, username, password, name, vm_id):
    url = "https://" + engine + "/api/templates/"
    data = "<template><name>%s</name><vm id='%s' /></template>" % (name, vm_id)
    headers = {'Content-Type': 'application/xml'}
    response = request2virtengine(url, username, password, 'POST', data, headers)
    rid = None
    try:
        rid = response['template']['@id']
    except Exception, e:
        print str(e)
        pass
    return rid


def updateTemplateName(engine, username, password, template_id, name):
    url     = "https://" + engine + "/api/templates/" + template_id
    headers = {'Content-Type': 'application/xml'}
    data    = "<template><name>%s</name></template>" % name
    request2virtengine(url, username, password, 'PUT', data, headers)


def updateTemplateDescription(engine, username, password, template_id, description):
    url     = "https://" + engine + "/api/templates/" + template_id
    headers = {'Content-Type': 'application/xml'}
    data    = "<template><description>%s</description></template>" % description
    request2virtengine(url, username, password, 'PUT', data, headers)


def updateTemplateTimeZone(engine, username, password, template_id, timezone='Asia/Shanghai'):#Chinese Startd Time
    url     = "https://" + engine + "/api/templates/" + template_id
    headers = {'Content-Type': 'application/xml'}
    version = getVersion(engine, username, password)
    if version['major'] == '4':
        data    = "<template><time_zone><name>%s</name></time_zone></template>" % timezone
    else:
        data    = "<template><timezone>%s</timezone></template>" % timezone
    request2virtengine(url, username, password, 'PUT', data, headers)


def updateTemplateOsType(engine, username, password, template_id, ostype):
    url     = "https://" + engine + "/api/templates/" + template_id
    headers = {'Content-Type': 'application/xml'}
    data    = "<template><os type=\"%s\"></os></template>" % ostype
    request2virtengine(url, username, password, 'PUT', data, headers)


def updateTemplateMemory(engine, username, password, template_id, memory):
    url = "https://" + engine + "/api/templates/" + template_id
    data = "<template><memory>%s</memory></template>" % str(int(memory)*1024*1024)
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'PUT', data, headers)


def updateTemplateCpu(engine, username, password, template_id, cpu):
    url     = "https://" + engine + "/api/templates/" + template_id
    headers = {'Content-Type': 'application/xml'}
    data    = "<template><cpu><topology sockets=\"1\" cores=\"%s\"/></cpu></template>" % cpu
    request2virtengine(url, username, password, 'PUT', data, headers)


def updateTemplateStateless(engine, username, password, template_id, stateless):
    url     = "https://" + engine + "/api/templates/" + template_id
    headers = {'Content-Type': 'application/xml'}
    data    = "<template><stateless>%s</stateless></template>" % stateless
    request2virtengine(url, username, password, 'PUT', data, headers)


def updateTemplateDeleteProtected(engine, username, password, template_id, dprotected):
    url     = "https://" + engine + "/api/templates/" + template_id
    headers = {'Content-Type': 'application/xml'}
    data    = "<template><delete_protected>%s</delete_protected></template>" % dprotected
    request2virtengine(url, username, password, 'PUT', data, headers)


def updateTemplateUsbPolicy(engine, username, password, template_id, usbpolicy):
    url     = "https://" + engine + "/api/templates/" + template_id
    headers = {'Content-Type': 'application/xml'}
    if usbpolicy == 'true':
        data = "<template><usb><enabled>true</enabled><type>native</type></usb></template>"
    else:
        data = "<template><usb><enabled>false</enabled></usb></template>"
    request2virtengine(url, username, password, 'PUT', data, headers)


def removeTemplate(engine, username, password, template_id):
    url = "https://" + engine + "/api/templates/" + template_id
    return request2virtengine(url, username, password, 'DELETE', '', {})


def exportTemplate(engine, username, password, template_id):
    pass


def addTemplateTag(engine, username, password, template_id, tag_name):
    url = "https://" + engine + "/api/templates/" + template_id + "/tags/"
    data = "<tag><name>%s</name></tag>" % tag_name
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'POST', data, headers)


def removeTemplateTag(engine, username, password, template_id, tag_id):
    url = "https://" + engine + "/api/templates/" + template_id + "/tags/" + tag_id
    return request2virtengine(url, username, password, 'DELETE', '', {})


#################################################################
#
# Domain Update Logic
#
#################################################################
#Domain is not updatable?


#################################################################
#
# User Update Logic
#
#################################################################
def addUser(engine, username, password, uname, dname):	#domain_id or domain_etry_id not supported (aoqingy)
    url = "https://" + engine + "/api/users"
    data = '<user><domain><name>%s</name></domain><user_name>%s</user_name></user>' % (dname, uname)
    headers = {'Content-Type':'application/xml'}
    response = request2virtengine(url, username, password, 'POST', data, headers)
    return response['user']['@id']


def removeUser(engine, username, password, user_id):
    url = "https://" + engine + "/api/users/" + user_id
    return request2virtengine(url, username, password, 'DELETE', '', {})


def addUserTag(engine, username, password, user_id, tag_id):
    url = "https://" + engine + "/api/users/" + user_id + "/tags/"
    #data = "<tag><name>%s</name></tag>" % tag_name
    data = "<tag id='%s'></tag>" % tag_id
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'POST', data, headers)


def removeUserTag(engine, username, password, user_id, tag_id):
    url = "https://" + engine + "/api/users/" + user_id + "/tags/" + tag_id
    return request2virtengine(url, username, password, 'DELETE', '', {})


#################################################################
#
# Group Update Logic
#
#################################################################
def addGroup(engine, username, password, gname, dname):    #aoqingy
    url     = "https://" + engine + "/api/groups"
    headers = {'Content-Type':'application/xml'}
    data    = '<user><domain><name>%s</name></domain><user_name>%s@%s</user_name></user>' % (dname, username, dname)
    try:
        request2virtengine(url, username, password, 'POST', data, headers)
    except Exception, e:
        pass


def removeGroup(engine, username, password, group_id):
    url = "https://" + engine + "/api/groups/" + group_id
    return request2virtengine(url, username, password, 'DELETE', '', {})


def addGroupTag(engine, username, password, group_id, tag_name):
    url = "https://" + engine + "/api/groups/" + group_id + "/tags/"
    data = "<tag><name>%s</name></tag>" % tag_name
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'POST', data, headers)


def removeGroupTag(engine, username, password, group_id, tag_id):
    url = "https://" + engine + "/api/groups/" + group_id + "/tags/" + tag_id
    return request2virtengine(url, username, password, 'DELETE', '', {})


#################################################################
#
# Tag Update Logic
#
#################################################################
ROOT_TAG_ID = "00000000-0000-0000-0000-000000000000"
def createTag(engine, username, password, tag_name, tag_description, parent_id=ROOT_TAG_ID):
    url = "https://" + engine + "/api/tags/"
    data = "<tag><name>%s</name><description>%s</description><parent id='%s'></parent></tag>" % (tag_name, tag_description, parent_id)
    headers = {'Content-Type': 'application/xml'}
    response = request2virtengine(url, username, password, 'POST', data, headers)
    rid = None
    try:
        rid = response['tag']['@id']
    except Exception, e:
        pass
    return rid


def removeTag(engine, username, password, tag_id):
    url = "https://" + engine + "/api/tags/" + tag_id
    return request2virtengine(url, username, password, 'DELETE', '', {})


#################################################################
#
# Role Update Logic
#
#################################################################
#{'administrative': 'false', 'id': '1',    'name': 'create_vm'}
#{'administrative': 'false', 'id': '2',    'name': 'delete_vm'}
#{'administrative': 'false', 'id': '3',    'name': 'edit_vm_properties'}
#{'administrative': 'false', 'id': '5',    'name': 'change_vm_cd'}
#{'administrative': 'false', 'id': '6',    'name': 'migrate_vm'}
#{'administrative': 'false', 'id': '7',    'name': 'connect_to_vm'}
#{'administrative': 'true',  'id': '8',    'name': 'import_export_vm'}
#{'administrative': 'false', 'id': '9',    'name': 'configure_vm_network'}
#{'administrative': 'false', 'id': '10',   'name': 'configure_vm_storage'}
#{'administrative': 'false', 'id': '11',   'name': 'move_vm'}
#{'administrative': 'false', 'id': '12',   'name': 'manipulate_vm_snapshots'}
#{'administrative': 'false', 'id': '13',   'name': 'reconnect_to_vm'}
#{'administrative': 'true',  'id': '14',   'name': 'change_vm_custom_properties'}
#{'administrative': 'true',  'id': '15',   'name': 'edit_admin_vm_properties'}
#{'administrative': 'false', 'id': '17',   'name': 'reboot_vm'}
#{'administrative': 'false', 'id': '18',   'name': 'stop_vm'}
#{'administrative': 'false', 'id': '19',   'name': 'shut_down_vm'}
#{'administrative': 'false', 'id': '21',   'name': 'hibernate_vm'}
#{'administrative': 'false', 'id': '22',   'name': 'run_vm'}
#{'administrative': 'true',  'id': '100',  'name': 'create_host'}
#{'administrative': 'true',  'id': '101',  'name': 'edit_host_configuration'}
#{'administrative': 'true',  'id': '102',  'name': 'delete_host'}
#{'administrative': 'true',  'id': '103',  'name': 'manipulate_host'}
#{'administrative': 'true',  'id': '104',  'name': 'configure_host_network'}
#{'administrative': 'false', 'id': '200',  'name': 'create_template'}
#{'administrative': 'false', 'id': '201',  'name': 'edit_template_properties'}
#{'administrative': 'false', 'id': '202',  'name': 'delete_template'}
#{'administrative': 'false', 'id': '203',  'name': 'copy_template'}
#{'administrative': 'false', 'id': '204',  'name': 'configure_template_network'}
#{'administrative': 'true',  'id': '205',  'name': 'edit_admin_template_properties'}
#{'administrative': 'false', 'id': '300',  'name': 'create_vm_pool'}
#{'administrative': 'false', 'id': '301',  'name': 'edit_vm_pool_configuration'}
#{'administrative': 'false', 'id': '302',  'name': 'delete_vm_pool'}
#{'administrative': 'false', 'id': '303',  'name': 'vm_pool_basic_operations'}
#{'administrative': 'true',  'id': '400',  'name': 'create_cluster'}
#{'administrative': 'true',  'id': '401',  'name': 'edit_cluster_configuration'}
#{'administrative': 'true',  'id': '402',  'name': 'delete_cluster'}
#{'administrative': 'true',  'id': '403',  'name': 'configure_cluster_network'}
#{'administrative': 'true',  'id': '404',  'name': 'assign_cluster_network'}
#{'administrative': 'true',  'id': '500',  'name': 'manipulate_users'}
#{'administrative': 'true',  'id': '501',  'name': 'manipulate_roles'}
#{'administrative': 'false', 'id': '502',  'name': 'manipulate_permissions'}
#{'administrative': 'false', 'id': '503',  'name': 'add_users_and_groups_from_directory'}
#{'administrative': 'true',  'id': '600',  'name': 'create_storage_domain'}
#{'administrative': 'true',  'id': '601',  'name': 'edit_storage_domain_configuration'}
#{'administrative': 'true',  'id': '602',  'name': 'delete_storage_domain'}
#{'administrative': 'true',  'id': '603',  'name': 'manipulate_storage_domain'}
#{'administrative': 'true',  'id': '700',  'name': 'create_storage_pool'}
#{'administrative': 'true',  'id': '701',  'name': 'delete_storage_pool'}
#{'administrative': 'true',  'id': '702',  'name': 'edit_storage_pool_configuration'}
#{'administrative': 'true',  'id': '703',  'name': 'configure_storage_pool_network'}
#{'administrative': 'true',  'id': '704',  'name': 'create_storage_pool_network'}
#{'administrative': 'true',  'id': '705',  'name': 'delete_storage_pool_network'}
#{'administrative': 'true',  'id': '800',  'name': 'configure_engine'}
#{'administrative': 'true',  'id': '900',  'name': 'configure_quota'}
#{'administrative': 'false', 'id': '901',  'name': 'consume_quota'}
#{'administrative': 'true',  'id': '1000', 'name': 'create_gluster_volume'}
#{'administrative': 'true',  'id': '1001', 'name': 'manipulate_gluster_volume'}
#{'administrative': 'true',  'id': '1002', 'name': 'delete_gluster_volume'}
#{'administrative': 'true',  'id': '1003', 'name': 'manipulate_gluster_hook'}
#{'administrative': 'true',  'id': '1004', 'name': 'manipulate_gluster_service'}
#{'administrative': 'false', 'id': '1100', 'name': 'create_disk'}
#{'administrative': 'false', 'id': '1101', 'name': 'attach_disk'}
#{'administrative': 'false', 'id': '1102', 'name': 'edit_disk_properties'}
#{'administrative': 'false', 'id': '1103', 'name': 'configure_disk_storage'}
#{'administrative': 'false', 'id': '1104', 'name': 'delete_disk'}
#{'administrative': 'true',  'id': '1105', 'name': 'configure_scsi_generic_io'}
#{'administrative': 'false', 'id': '1106', 'name': 'access_image_storage'}
#{'administrative': 'false', 'id': '1107', 'name': 'disk_live_storage_migration'}
#{'administrative': 'false', 'id': '1108', 'name': 'sparsify_disk'}]
#{'administrative': 'true',  'id': '1203', 'name': 'configure_network_vnic_profile'}
#{'administrative': 'true',  'id': '1204', 'name': 'create_network_vnic_profile'}
#{'administrative': 'true',  'id': '1205', 'name': 'delete_network_vnic_profile'}
#{'administrative': 'false', 'id': '1300', 'name': 'login'}
#{'administrative': 'true',  'id': '1301', 'name': 'tag_management'}
#{'administrative': 'true',  'id': '1302', 'name': 'bookmark_management'}
#{'administrative': 'true',  'id': '1303', 'name': 'event_notification_management'}
#{'administrative': 'true',  'id': '1304', 'name': 'audit_log_management'}
#{'administrative': 'true',  'id': '1400', 'name': 'inject_external_events'}
#{'administrative': 'true',  'id': '1500', 'name': 'inject_external_tasks'}
#{'administrative': 'true',  'id': '1550', 'name': 'manipulate_affinity_groups'}
#{'administrative': 'true',  'id': '1560', 'name': 'configure_storage_disk_profile'}
#{'administrative': 'true',  'id': '1561', 'name': 'create_storage_disk_profile'}
#{'administrative': 'true',  'id': '1562', 'name': 'delete_storage_disk_profile'}
#{'administrative': 'false', 'id': '1563', 'name': 'attach_disk_profile'}
#{'administrative': 'true',  'id': '1660', 'name': 'create_mac_pool'}
#{'administrative': 'true',  'id': '1661', 'name': 'edit_mac_pool'}
#{'administrative': 'true',  'id': '1662', 'name': 'delete_mac_pool'}
#{'administrative': 'true',  'id': '1663', 'name': 'configure_mac_pool'}
#{'administrative': 'false', 'id': '1664', 'name': 'connect_to_serial_console'}
#{'administrative': 'true',  'id': '1665', 'name': 'delete_cpu_profile'}
#{'administrative': 'true',  'id': '1666', 'name': 'update_cpu_profile'}
#{'administrative': 'true',  'id': '1667', 'name': 'create_cpu_profile'}
#{'administrative': 'true',  'id': '1668', 'name': 'assign_cpu_profile'}
#APIUser权限包括：5、7、17、18、19、21、22、1300和/或4（vm_basic_operations）
def createRole(engine, username, password, name, description, administrative, permit_ids):
    url = "https://" + engine + "/api/roles/"
    data = "<role><name>%s</name><description>%s</description><administrative>%s</administrative><permits>" % (name, description, administrative)
    for permit in permit_ids:
        data += "<permit id='%s' />" % permit
    data += "</permits></role>"
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'POST', data, headers)


def updateRoleDescription(engine, username, password, role_id, description):
    url = "https://" + engine + "/api/roles/" + role_id
    data = "<role><description>%s</description></role>" % description
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'PUT', data, headers)


def removeRole(engine, username, password, role_id):
    url = "https://" + engine + "/api/roles/%s" % role_id
    return request2virtengine(url, username, password, 'DELETE', '', {})


def assignRolePermit(engine, username, password, role_id, permit_id):
    url = "https://" + engine + "/api/roles/" + role_id + "/permits/"
    data = "<permit id='%s' />" % permit_id
    headers={'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'POST', data, headers)


def reclaimRolePermit(engine, username, password, role_id, permit_id):
    url = "https://" + engine + "/api/roles/" + role_id + "/permits/" + permit_id
    return request2virtengine(url, username, password, 'DELETE', '', {})


#################################################################
#
# Permission Update Logic
#
#################################################################
def addPermission(engine, username, password, uname, dname, role_id):
    url = "https://" + engine + "/api/permissions/"
    data = "<permission><user_name>%s@</user_name><roles><role id='%s' /></roles></permission>" % (uname, dname, role_id)
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, "POST", data, headers)


def addVmPermission(engine, username, password, vm_id, user_id, role_id):
    url = "https://" + engine + "/api/vms/%s/permissions/" % vm_id
    data = "<permission><user id='%s' /><role id='%s' /></permission>" % (user_id, role_id)
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, "POST", data, headers)


def removeVmPermission(engine, username, password, vm_id, permission_id):
    url = "https://" + engine + "/api/vms/%s/permissions/%s" % (vm_id, permission_id)
    return request2virtengine(url, username, password, 'DELETE', '', {})


def addUserPermission(engine, username, password, user_id, vm_id, role_id):
    url = "https://" + engine + "/api/users/%s/permissions/" % user_id
    data = "<permission><vm id='%s' /><role id='%s' /></permission>" % (vm_id, role_id)
    headers = {'Content-Type': 'application/xml'}
    return request2virtengine(url, username, password, 'POST', data, headers)


def removeUserPermission(engine, username, password, user_id, permission_id):
    url = "https://" + engine + "/api/users/%s/permissions/%s" % (user_id, permission_id)
    return request2virtengine(url, username, password, 'DELETE', '', {})


#################################################################
#
# ???
#
#################################################################
#def getCapabilities(engine, username, password, version):
#    response = requestResources(engine, username, password, 'capabilities')
#    major, minor = version.split('.', 1)
#    for x in response['capabilities']['version']:
#        if x['@major'] == major and x['@minor'] == minor:
#            return x
#    return None


#def getCapabilityOsTypes(engine, username, password, version):
#    capabilities = getCapabilities(engine, username, password, version)
#    return capabilities['os_types']['os_type']


#def getCapabilityDiskFormats(engine, username, password, version):
#    capabilities = getCapabilities(engine, username, password, version)
#    return capabilities['disk_formats']['disk_format']


#def getCapabilityDiskInterfaces(engine, username, password, version):
#    capabilities = getCapabilities(engine, username, password, version)
#    return capabilities['disk_interfaces']['disk_interface']


#def getCapabilityVmAffinities(engine, username, password, version):
#    capabilities = getCapabilities(engine, username, password, version)
#    return capabilities['vm_affinities']['vm_affinity']


#def getCapabilityCustomProperties(engine, username, password, version):
#    capabilities = getCapabilities(engine, username, password, version)
#    return capabilities['custom_properties']['custom_property']


#def getCapabilityBootProtocols(engine, username, password, version):
#    capabilities = getCapabilities(engine, username, password, version)
#    return capabilities['boot_protocols']['boot_protocol']


#def getCapabilityErrorHandlings(engine, username, password, version):
#    capabilities = getCapabilities(engine, username, password, version)
#    return capabilities['error_handling']['on_error']


#def getCapabilityStorageFormats(engine, username, password, version):
#    capabilities = getCapabilities(engine, username, password, version)
#    return capabilities['storage_formats']['format']


#def getCapabilityCreationStates(engine, username, password, version):
#    capabilities = getCapabilities(engine, username, password, version)
#    return capabilities['creation_states']['create_state']


#def getCapabilityPowerManagementStates(engine, username, password, version):
#    capabilities = getCapabilities(engine, username, password, version)
#    return capabilities['power_management_states']['power_management_state']


#def getCapabilityHostStates(engine, username, password, version):
#    capabilities = getCapabilities(engine, username, password, version)
#    return capabilities['host_states']['host_state']


#def getCapabilityPermitIds(engine, username, password, version):
#    capabilities = getCapabilities(engine, username, password, version)
#    return capabilities['permits']['permit']['@id']


#def getCapabilityPermitName(engine, username, password, version, permit_id):
#    capabilities = getCapabilities(engine, username, password, version)
#    for capability in capabilities['permits']['permit']:
#        if capability['@id'] == permit_id:
#            return capability['name']
#    return None


#################################################################
#
# Misc
#
#################################################################
def SetupNetwork():
    pass


def ChangeDisplayProtocol():
    pass


ENGINE_IP       = "192.168.0.97/ovirt-engine"
#ENGINE_IP       = "192.168.0.240/virtfan-engine"
#ENGINE_IP       = "192.168.0.131/ovirt-engine"
ENGINE_USERNAME = "admin@internal"
ENGINE_PASSWORD = "123456"


def show_resources():
    print "****************************************************"
    print "*                                                  *"
    print "*               Listing Resources                  *"
    print "*                                                  *"
    print "****************************************************"
    print getAllDataCenters(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    print getAllClusters(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    print getAllHosts(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    print getAllStorageDomains(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    print getAllNetworks(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    print getAllDisks(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    print getAllVms(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    print getAllVmPools(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    print getAllTemplates(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    print getAllTags(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    print getAllRoles(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    print getAllDomains(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    print getAllUsers(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    print getAllGroups(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    print getAllJobs(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    print


def show_resource_ids():
    print "****************************************************"
    print "*                                                  *"
    print "*             Listing Resource IDs                 *"
    print "*                                                  *"
    print "****************************************************"
    print getDataCenterIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    print getClusterIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    print getHostIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    print getNetworkIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    print getStorageDomainIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    print getDiskIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    print getVmIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    print getVmPoolIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    print getTemplateIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    print getDomainIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    print getUserIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    print getGroupIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    print getTagIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    #print getBookmarkIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    print getRoleIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    print getPermissionIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    print getJobIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    #print getCapabilityIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    #print getEventIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    #print getInstanceTypeIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    #print getStorageConnections(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    #print getVnicProfiles(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    #print getDiskProfiles(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    #print getCpuProfiles(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    #print getSchedulingPolicyUnits(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    #print getSchedulingPolicies(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    print


def search_resources():
    print "****************************************************"
    print "*                                                  *"
    print "*            Searching Resource Logic              *"
    print "*                                                  *"
    print "****************************************************"
    print searchDataCenters(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, "")
    print searchClusters(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, "")
    print searchHosts(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, "")
    print searchNetworks(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, "")
    print searchStorageDomains(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, "vms.status=up")
    print searchDisks(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, "")
    print searchVms(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, "")
    print searchVmPools(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, "")
    print searchTemplates(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, "")
    print searchUsers(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, "")
    print searchGroups(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, "")
    for x in getDomainIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD):
        print x
        print searchDomainGroups(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x, "")
        print searchDomainUsers(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x, "")
        print


def search_resource_ids():
    print "****************************************************"
    print "*                                                  *"
    print "*                 Searching Logic                  *"
    print "*                                                  *"
    print "****************************************************"
    print searchDataCenterIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, "")
    print searchClusterIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, "")
    print searchHostIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, "")
    print searchNetworkIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, "")
    print searchStorageDomainIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, "vms.status=up")
    print searchDiskIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, "")
    print searchVmIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, "")
    print searchVmPoolIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, "")
    print searchTemplateIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, "")
    print searchUserIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, "")
    print searchGroupIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, "")
    for x in getDomainIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD):
        print x
        print searchDomainGroupIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x, "")
        print searchDomainUserIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x, "")
        print


def show_datacenters():
    print "****************************************************"
    print "*                                                  *"
    print "*             Listing Data Centers                 *"
    print "*                                                  *"
    print "****************************************************"
    for x in getDataCenterIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD):
        print x
        print getDataCenterInfo(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getDataCenterName(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getDataCenterDescription(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getDataCenterStatus(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getDataCenterClusters(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getDataCenterNetworks(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getDataCenterStorageDomains(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getDataCenterDataStorageDomains(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getDataCenterMasterStorageDomain(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getDataCenterIsoStorageDomain(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getDataCenterExportStorageDomain(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getDataCenterPermissions(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getDataCenterClusterIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getDataCenterNetworkIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getDataCenterStorageDomainIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getDataCenterPermissionIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        #print getDataCenterQuotaIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        #print getDataCenterIscsiBondIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        #print getDataCenterQosIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print


def show_clusters():
    print "****************************************************"
    print "*                                                  *"
    print "*                Listing Clusters                  *"
    print "*                                                  *"
    print "****************************************************"
    for x in getClusterIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD):
        print x
        print getClusterInfo(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getClusterName(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getClusterDataCenterId(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getClusterNetworks(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getClusterPermissions(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getClusterNetworkIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getClusterPermissionIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        #print getClusterGlusterVolumeIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        #print getClusterGlusterHookIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        #print getClusterAffinityGroupIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        #print getClusterCpuProfileIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print


def show_hosts():
    print "****************************************************"
    print "*                                                  *"
    print "*                  Listing Hosts                   *"
    print "*                                                  *"
    print "****************************************************"
    for x in getHostIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD):
        print x
        print getHostInfo(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getHostName(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getHostAddress(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getHostCertificateOrganization(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getHostCertificateSubject(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getHostStatus(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getHostType(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getHostSshPort(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getHostSshFingerPrint(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getHostMemory(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getHostCpuSockets(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getHostCpuCores(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getHostCpuThreads(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getHostOsType(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getHostOsVersion(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        #print getHostDisplayAddress(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getHostClusterId(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getHostNics(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getHostTags(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getHostPermissions(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        #print getHostStorageIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getHostNicIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getHostTagIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getHostPermissionIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getHostNumanodeIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getHostHookIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print


def show_networks():
    print "****************************************************"
    print "*                                                  *"
    print "*                Listing Networks                  *"
    print "*                                                  *"
    print "****************************************************"
    for x in getNetworkIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD):
        print x
        print getNetworkInfo(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getNetworkName(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getNetworkDescription(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getNetworkDataCenterId(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getNetworkPermissions(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getNetworkPermissionIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getNetworkVnicProfileIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        #print getNetworkLabelIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print


def show_storagedomains():
    print "****************************************************"
    print "*                                                  *"
    print "*            Listing Storage Domains               *"
    print "*                                                  *"
    print "****************************************************"
    for x in getStorageDomainIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD):
        print x
        print getStorageDomainInfo(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getStorageDomainName(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getStorageDomainType(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        #print getStorageDomainStatus(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getStorageDomainStorageAddress(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getStorageDomainStorageType(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getStorageDomainStoragePath(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getStorageDomainStorageAvailable(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getStorageDomainStorageUsed(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getStorageDomainPermissions(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getStorageDomainPermissionIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getStorageDomainDiskIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getStorageDomainStorageConnectionIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getStorageDomainDiskSnapshotIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getStorageDomainDiskProfileIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        #print getStorageDomainFileIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        #t = getStorageDomainType(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        #print t
        #if t == "iso":
        #    print "Files in the ISO storage domain:"
        #    for y in getStorageDomainFileIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x):
        #        print y
        print


def show_disks():
    print "****************************************************"
    print "*                                                  *"
    print "*                  Listing Disks                   *"
    print "*                                                  *"
    print "****************************************************"
    for x in getDiskIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD):
        print x
        print getDiskInfo(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getDiskName(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getDiskAlias(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        #print getDiskSize(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getDiskProvisionedSize(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getDiskActualSize(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getDiskStatus(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        #print getDiskInterface(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getDiskFormat(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getDiskSparse(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        #print getDiskBootable(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getDiskShareable(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getDiskWipeAfterDelete(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getDiskPropagateErrors(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        #print getDiskDiskProfileId(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getDiskImageId(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getDiskStorageDomainIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getDiskPermissions(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getDiskPermissionIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        #print getDiskStatisticIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print


def show_vms():
    print "****************************************************"
    print "*                                                  *"
    print "*                   Listing Vms                    *"
    print "*                                                  *"
    print "****************************************************"

    for x in getVmIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD):
        print x
        print getVmInfo(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmName(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmType(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmStatus(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmMemory(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmCpuSockets(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmCpuCores(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmCpuThreads(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmOsType(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        #print getVmBootDev(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmCreationTime(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmStopTime(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmTimeZone(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmUsbEnabled(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmDisplayType(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmDisplayAddress(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmDisplayPort(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmDisplaySecurePort(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmDisplayMonitors(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmDisplaySmartCardEnabled(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmDisplayFileTransferEnabled(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmDisplayCopyPasteEnabled(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmDisplayCertificateSubject(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmClusterId(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmTemplateId(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmDiskAttachments(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmNics(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmTags(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmPermissions(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmIps(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmApplicationIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmDiskAttachmentIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmNicIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmNumanodeIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmCdromIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmSnapshotIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmTagIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmPermissionIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmReportedDeviceIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmWatchDogIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmSessionIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print

def show_vmpools():
    print "****************************************************"
    print "*                                                  *"
    print "*                Listing Templates                 *"
    print "*                                                  *"
    print "****************************************************"
    for x in getVmPoolIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD):
        print x
        print getVmPoolInfo(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmPoolName(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmPoolDescription(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmPoolSize(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmPoolType(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmPoolPermissions(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getVmPoolPermissionIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print


def show_templates():
    print "****************************************************"
    print "*                                                  *"
    print "*                Listing Templates                 *"
    print "*                                                  *"
    print "****************************************************"
    for x in getTemplateIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD):
        print x
        print getTemplateInfo(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getTemplateName(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x).encode('utf-8')
        print getTemplateType(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getTemplateStatus(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getTemplateMemory(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getTemplateCpuSockets(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getTemplateCpuCores(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getTemplateCpuThreads(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getTemplateOsType(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getTemplateClusterId(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getTemplateCreationTime(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getTemplateDisplayType(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getTemplateDisplayMonitors(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getTemplateDisplaySmartCardEnabled(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getTemplateDisplayFileTransferEnabled(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getTemplateDisplayCopyPasteEnabled(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getTemplateDiskAttachments(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getTemplateNics(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getTemplateTags(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getTemplatePermissions(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getTemplateDiskAttachmentIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getTemplateNicIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getTemplateCdromIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getTemplateTagIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getTemplatePermissionIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getTemplateWatchDogIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print


def show_domains():
    print "****************************************************"
    print "*                                                  *"
    print "*                 Listing Domains                  *"
    print "*                                                  *"
    print "****************************************************"
    for x in getDomainIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD):
        print x
        print getDomainInfo(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getDomainName(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getDomainUsers(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getDomainGroups(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getDomainUserIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getDomainGroupIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)        
        print


def show_users():
    print "****************************************************"
    print "*                                                  *"
    print "*                  Listing Users                   *"
    print "*                                                  *"
    print "****************************************************"
    for x in getUserIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD):
        print x
        print getUserInfo(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getUserName(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getUserUserName(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getUserLastName(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getUserEmail(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getUserNameSpace(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getUserDomainEntryId(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getUserDomainId(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getUserDomainName(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getUserTags(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getUserRoles(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getUserPermissions(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getUserPermissionIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getUserRoleIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getUserTagIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print


def show_groups():
    print "****************************************************"
    print "*                                                  *"
    print "*                 Listing Groups                   *"
    print "*                                                  *"
    print "****************************************************"
    for x in getGroupIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD):
        print x
        print getGroupInfo(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getGroupName(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getGroupNameSpace(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getGroupDomainEntryId(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getGroupDomainId(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getGroupDomainName(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getGroupTags(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getGroupRoles(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getGroupPermissions(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getGroupPermissionIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getGroupRoleIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getGroupTagIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)        
        print


def show_tags():
    print "****************************************************"
    print "*                                                  *"
    print "*                  Listing Tags                    *"
    print "*                                                  *"
    print "****************************************************"
    for x in getTagIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD):
        print x
        print getTagName(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getTagDescription(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getTagParentId(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print


def show_bookmarks():
    print "****************************************************"
    print "*                                                  *"
    print "*                Listing Bookmarks                 *"
    print "*                                                  *"
    print "****************************************************"
    for x in getBookmarkIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD):
        print x
        print getBookmarkName(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print


def show_roles():
    print "****************************************************"
    print "*                                                  *"
    print "*                   Listing Roles                  *"
    print "*                                                  *"
    print "****************************************************"
    
    for x in getRoleIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD):
        print x
        print getRoleName(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getRoleDescription(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getRolePermits(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getRolePermitIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print


def show_permissions():
    print "****************************************************"
    print "*                                                  *"
    print "*                Listing Permissions               *"
    print "*                                                  *"
    print "****************************************************"
    for x in getPermissionIds(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD):
        print x
        print getPermissionInfo(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getPermissionRoleId(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getPermissionUserId(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print getPermissionGroupId(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, x)
        print


def todo():
    #print createDataCenter('test', 'nfs', {'major':'3', 'minor':'0'})
    #print addVmDisk(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, "6eaecdb1-8357-4d0b-9c50-68fc56c65c26", "271a4b74-3fa8-40f1-be3c-baf7c2f011bf", "8589934592")
    #addVmNic(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, "5854d6b2-ea51-4802-a3d1-5f4f5b5a24b0", "nic1", "00000000-0000-0000-0000-000000000009")
    #createVm(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, "s-192-168-000-107-01-05", 'f534ae08-dabc-4a07-8bd0-58e5dc16d0ee', '00000001-0001-0001-0001-000000000295')
    #print createVm2(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, "axax", "94709a3c-3dae-42d9-a420-70cefeccb16b", "19baf837-4484-4792-a953-5cbaf1b23e7a", [{"key":"6feb30d2-df06-47b7-8700-d0da24d2d46c","value":"8ca79d97-e707-40b5-9135-80ad61fa6020"},{"key":"c0adfc3f-e478-4a04-87ec-eadedb82f6ea","value":"8ca79d97-e707-40b5-9135-80ad61fa6020"},{"key":"635c72a5-cb59-4576-a7b4-03aa062df2c3","value":"23907ca7-568c-4e64-a8c6-8652ae2fe8f3"}]);
    #runonceVm(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, "179cc59b-c67a-42a9-9939-21ab24d4becb", "cn_windows_7_ultimate_with_sp1_x64_dvd_u_677408.iso", "virtio-win-0.1.118_amd64.vfd")
    #print addUser(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, '65613037336561362D666239392D313033342D396434382D346434373463363335333361', '617574687A2D7669727466616E2E636F6D')
    pass


if __name__ == "__main__":
    import datetime
    start = datetime.datetime.now()

    #print getAccessPostfix(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)
    print getAllVms(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD)

    #startVm(ENGINE_IP, ENGINE_USERNAME, ENGINE_PASSWORD, "759e2669-0183-4565-b9bd-c822f62fc052") 
    sys.exit(1)

    show_resources()
    show_resource_ids()
    search_resources()
    search_resource_ids()
    show_datacenters()
    show_clusters()
    show_hosts()
    show_networks()
    show_storagedomains()
    show_disks()
    show_vms()
    show_vmpools()
    show_templates()
    show_domains()
    show_users()
    show_groups()
    show_tags()
    show_bookmarks()
    show_roles()
    show_permissions()

    print "****************************************************"
    end = datetime.datetime.now()
    print "Totol: " + str(end - start)
