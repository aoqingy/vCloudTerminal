#!/bin/sh  
   
if [ $# -ne 1 ]  
then  
   echo "usage: $(basename $0) pciaddr"  
   exit 1  
fi  

pciaddr=$1  
prefullpath="/sys/bus/pci/devices/"$pciaddr  
fullpath=$prefullpath"/iommu_group/devices"  
driverfullpath=$prefullpath"/driver/unbind"  

for i in `ls $fullpath`  
do  
   if [ $i != $pciaddr ]  
   then  
       # unbind  
       echo $i >>$driverfullpath  
    
       # new_id  
       prdmsg=`/usr/bin/lspci -n -s $pciaddr`  
       prdmsg=`echo $prdmsg | /bin/sed 's/:/ /g' | /usr/bin/awk -F' ' '{print $4 " " $5 }'`  
       echo $prdmsg >/sys/bus/pci/drivers/vfio-pci/new_id  
   fi  
done  
  
# unbind and new_id itself  
echo $pciaddr  >>$driverfullpath  
prdmsg=`/usr/bin/lspci -n -s $pciaddr`  
prdmsg=`echo $prdmsg | /bin/sed 's/:/ /g' | /usr/bin/awk -F' ' '{ print $4 " " $5 }'`  
echo $prdmsg>/sys/bus/pci/drivers/vfio-pci/new_id  
  
exit 0  
