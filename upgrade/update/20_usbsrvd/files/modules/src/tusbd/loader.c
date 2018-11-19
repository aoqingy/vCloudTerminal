/*
 *
 *  Copyright (C) 2007-2016 SimplyCore, LLC
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 *
 */

#ifdef _USBD_ENABLE_STUB_
#include "usbd.h"
#include "loader.h"
struct IllllI*IIllIlI;struct list_head lllIlIIl;struct mutex IIIIllll;extern 
struct usb_driver lllllII;int llllllll(struct usb_device*IlIIl){llIIIl vid,
IllIIII,IlIllIl;IIIII class,IlllIllIl,IIIIlIIII;struct lIIllIl*lllII;int 
IIIIllII=(0x16c5+1114-0x1b1f);int lIIIIIlI=(0xde7+3053-0x19d4);llIll(
"\x2b\x2b" "\n");
if(strcmp(IlIIl->bus->controller->driver->name,llIIIll)==(0x1379+3462-0x20ff)){
llIll(
"\x2d\x2d\x20\x73\x6b\x69\x70\x20\x6f\x75\x72\x20\x76\x69\x72\x74\x75\x61\x6c\x20\x64\x65\x76\x69\x63\x65\x21" "\n"
);return(0x1837+3240-0x24df);}vid=le16_to_cpu(IlIIl->descriptor.idVendor);
IllIIII=le16_to_cpu(IlIIl->descriptor.idProduct);IlIllIl=le16_to_cpu(IlIIl->
descriptor.bcdDevice);lllIIIllI(IlIIl,&class,&IlllIllIl,&IIIIlIIII);if(class==
(0x9ca+717-0xc8e)){llIll(
"\x2d\x2d\x20\x73\x6b\x69\x70\x20\x75\x73\x62\x20\x68\x75\x62\x21" "\n");return
(0x6cc+6349-0x1f99);}llIll(
"\x56\x3d\x25\x30\x34\x58\x20\x50\x3d\x25\x30\x34\x58\x20\x52\x3d\x25\x30\x34\x58\x20\x43\x3d\x25\x30\x32\x58\x20\x53\x3d\x25\x30\x32\x58\x20\x50\x3d\x25\x30\x32\x58\x20\x49\x44\x3d\x25\x73\x20\x53\x4e\x3d\x25\x73" "\n"
,vid,IllIIII,IlIllIl,class,IlllIllIl,IIIIlIIII,IlIIlI(&IlIIl->dev),IlIIl->serial
?IlIIl->serial:"\x6e\x6f\x6e\x65");
mutex_lock(&IIIIllll);list_for_each_entry(lllII,&lllIlIIl,entry){if(lllII->lllII
.IlIIIlI&lIlIIlllI){if(lllII->lllII.lIIIIlIl!=vid)continue;}if(lllII->lllII.
IlIIIlI&IllIIIIll){if(lllII->lllII.IlllIlII!=IllIIII)continue;}if(lllII->lllII.
IlIIIlI&lIIIllIlI){if(lllII->lllII.llIllIll!=IlIllIl)continue;}if(lllII->lllII.
IlIIIlI&IIllIIIIl){if(lllII->lllII.llllIIIll!=class)continue;}if(lllII->lllII.
IlIIIlI&lIIlllIlI){if(lllII->lllII.lIIllIIll!=IlllIllIl)continue;}if(lllII->
lllII.IlIIIlI&lllllllII){if(lllII->lllII.IIIllIlIl!=IIIIlIIII)continue;}if(lllII
->lllII.IlIIIlI&llIllllII){if(strncmp((char*)(lllII+(0x1405+1257-0x18ed)),IlIIlI
(&IlIIl->dev),lllII->lllII.IlIIIlIl))continue;}if(lllII->lllII.IlIIIlI&IIlIllIl)
{if(IlIIl->serial==NULL)continue;if(strncmp((char*)(lllII+(0x8aa+3903-0x17e8))+
lllII->lllII.IlIIIlIl,IlIIl->serial,lllII->lllII.llIlllIl))continue;}if(lllII->
lllII.IlIIIlI&IlIllIIII){lIIIIIlI=(0x203a+1149-0x24b6);IIIIllII=
(0x13d7+669-0x1673);break;}if(lllII->lllII.IlIIIlI&lllIlIllI){lIIIIIlI=
(0x553+2018-0xd35);IIIIllII=(0x609+555-0x833);break;}}mutex_unlock(&IIIIllll);if
(IIIIllII==(0x11e8+3743-0x2087)){llIll(
"\x2d\x2d\x20\x6e\x6f\x20\x6d\x61\x74\x63\x68" "\n");}else if(lIIIIIlI){llIll(
"\x2d\x2d\x20\x61\x6c\x6c\x6f\x77\x65\x64" "\n");}else{llIll(
"\x2d\x2d\x20\x64\x65\x6e\x69\x65\x64" "\n");}return lIIIIIlI;}void llllIIIII(
struct list_head*llIIIlII){struct list_head llIlIll=LIST_HEAD_INIT(llIlIll);

mutex_lock(&IIIIllll);list_splice_init(&lllIlIIl,&llIlIll);list_splice_init(
llIIIlII,&lllIlIIl);mutex_unlock(&IIIIllll);
while(!list_empty(&llIlIll)){struct lIIllIl*llIIIlI;llIIIlI=list_entry(llIlIll.
next,struct lIIllIl,entry);list_del(&llIIIlI->entry);lllIII(llIIIlI);}



}void IlIlIIIl(){struct list_head llIlIll=LIST_HEAD_INIT(llIlIll);
mutex_lock(&IIIIllll);list_splice_init(&lllIlIIl,&llIlIll);mutex_unlock(&
IIIIllll);
while(!list_empty(&llIlIll)){struct lIIllIl*llIIIlI;llIIIlI=list_entry(llIlIll.
next,struct lIIllIl,entry);list_del(&llIIIlI->entry);lllIII(llIIIlI);}}











int IIIlllIll(struct usb_interface*IIllI){int IlIlI;int llIlIIIII=
(0x52b+6233-0x1d84);int llIIllll=(0x882+6414-0x2190);
if(IIllI->dev.driver&&to_usb_driver(IIllI->dev.driver)==&lllllII){return
(0x437+6350-0x1d05);}
llIIllll=(0xe57+1279-0x1355);
if(IIllI->dev.driver){usb_driver_release_interface(to_usb_driver(IIllI->dev.
driver),IIllI);llIlIIIII=(0x10fd+3571-0x1eef);}
IlIlI=usb_driver_claim_interface(&lllllII,IIllI,(void*)-(0x802+5135-0x1c10));if(
IlIlI<(0x1a2b+1658-0x20a5)){IIIIll(
"\x66\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x63\x6c\x61\x69\x6d\x20\x69\x6e\x74\x65\x72\x66\x61\x63\x65\x20\x25\x73\x2c\x20\x65\x72\x72\x6f\x72\x20\x25\x64" "\n"
,IlIIlI(&IIllI->dev),IlIlI);return IlIlI;}IlIlI=IIIllllIl(IIllI,llIlIIIII);if(
IlIlI<(0x60b+5952-0x1d4b)){IIIIll(
"\x66\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x61\x74\x74\x61\x63\x68\x20\x69\x6e\x74\x65\x72\x66\x61\x63\x65\x20\x25\x73\x2c\x20\x65\x72\x72\x6f\x72\x20\x25\x64" "\n"
,IlIIlI(&IIllI->dev),IlIlI);
usb_driver_release_interface(&lllllII,IIllI);return IlIlI;}return llIIllll;}
static int IIIlIIIIl(struct device*dev,void*llIllllIl){const char*llIIll=
llIllllIl;if(strcmp(llIIll,IlIIlI(dev))==(0x55f+6660-0x1f63))return
(0x461+2662-0xec6);return(0xfd9+739-0x12bc);}struct usb_device*IIlIIIII(const 
char*llIIll){struct device*dev;dev=bus_find_device(
#if KERNEL_LT_EQ((0x1547+4434-0x2697),(0x19d8+897-0x1d53),(0x2e6+3283-0xfa7))
lllllII.driver.bus,
#else
lllllII.drvwrap.driver.bus,
#endif
NULL,(void*)llIIll,IIIlIIIIl);if(dev){return to_usb_device(dev);}return NULL;}





int IIIlIllI(struct usb_device*IlIIl){int i;int llIIllIlI=(0x876+7619-0x2639);
int llIIllll=(0x1e79+1916-0x25f5);int IlIlI=-ENODEV;llIll(
"\x2b\x2b\x20\x25\x73" "\n",IlIIlI(&IlIIl->dev));if(!IlIllIIl(IlIIl)){IlIlI=
llIllIII(IlIIl);if(IlIlI<(0x754+6173-0x1f71)){IIIIll(
"\x66\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x61\x74\x74\x61\x63\x68\x20\x75\x73\x62\x20\x64\x65\x76\x69\x63\x65\x20\x25\x73\x2c\x20\x65\x72\x72\x6f\x72\x20\x25\x64" "\n"
,IlIIlI(&IlIIl->dev),IlIlI);llIll(
"\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x3d\x25\x64" "\n",IlIlI);return IlIlI;}}if
(IlIIl->actconfig){for(i=(0x1b76+2183-0x23fd);i<IlIIl->actconfig->desc.
bNumInterfaces;i++){struct usb_interface*IIllI=IlIIl->actconfig->interface[i];if
(IIllI==NULL)continue;
IlIlI=IIIlllIll(IIllI);if(IlIlI<(0xde1+3811-0x1cc4)){llIll(
"\x69\x6e\x74\x65\x72\x66\x61\x63\x65\x20\x25\x73\x20\x6e\x6f\x74\x20\x63\x6c\x61\x69\x6d\x65\x64\x2c\x20\x65\x72\x72\x6f\x72\x20\x25\x64" "\n"
,IlIIlI(&IIllI->dev),IlIlI);break;}llIIllIlI++;if(IlIlI>(0x388+4122-0x13a2)){
llIll(
"\x69\x6e\x74\x65\x72\x66\x61\x63\x65\x20\x25\x73\x2c\x20\x61\x63\x74\x75\x61\x6c\x6c\x79\x20\x63\x6c\x61\x69\x6d\x65\x64" "\n"
,IlIIlI(&IIllI->dev));llIIllll++;}else
{llIll(
"\x69\x6e\x74\x65\x72\x66\x61\x63\x65\x20\x25\x73\x2c\x20\x63\x6c\x61\x69\x6d\x65\x64" "\n"
,IlIIlI(&IIllI->dev));}}if(IlIlI>=(0x1160+3338-0x1e6a)&&llIIllIlI>
(0xff1+2978-0x1b93)&&llIIllll==(0x14f6+3487-0x2295)){



struct IllIl*lIlII=llIlIllI(IlIIl);if(lIlII){llIll(
"\x72\x65\x66\x72\x65\x73\x68\x20\x6f\x6e\x6c\x69\x6e\x65" "\n");llllIIlIl(lIlII
);lIlIIlIl(lIlII);}else{llIll(
"\x73\x74\x75\x62\x20\x6e\x6f\x74\x20\x66\x6f\x75\x6e\x64" "\n");}}}llIll(
"\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x3d\x25\x64" "\n",IlIlI);return IlIlI;}





void llllIIlI(struct usb_device*IlIIl,int IlllIIll){int i;llIll(
"\x2b\x2b\x20\x25\x73" "\n",IlIIlI(&IlIIl->dev));if(IlIIl->actconfig){for(i=
(0x11a+7909-0x1fff);i<IlIIl->actconfig->desc.bNumInterfaces;i++){struct 
usb_interface*IIllI=IlIIl->actconfig->interface[i];if(IIllI==NULL)continue;
if(IIllI->dev.driver==NULL)continue;if(to_usb_driver(IIllI->dev.driver)!=&
lllllII)continue;llIll(
"\x72\x65\x6c\x65\x61\x73\x65\x20\x69\x6e\x74\x65\x72\x66\x61\x63\x65\x20\x25\x73" "\n"
,IlIIlI(&IIllI->dev));
usb_driver_release_interface(&lllllII,IIllI);}}if(IlIllIIl(IlIIl)){lIIIlllI(
IlIIl);}
#if KERNEL_GT_EQ((0xb3+7381-0x1d86),(0x9e3+3818-0x18c7),(0xe0d+2730-0x18a1))
if(IlIIIlllI(&IlIIl->dev)){llIlIIll(&IlIIl->dev,(0x1646+2680-0x20be));llIll(
"\x73\x65\x6e\x64\x20\x4b\x4f\x42\x4a\x5f\x41\x44\x44\x20\x66\x6f\x72\x20\x64\x65\x76\x69\x63\x65\x20\x25\x73" "\n"
,IlIIlI(&IlIIl->dev));kobject_uevent(&IlIIl->dev.kobj,KOBJ_ADD);}
#endif
if(IlIIl->actconfig){for(i=(0x8f1+2751-0x13b0);i<IlIIl->actconfig->desc.
bNumInterfaces;i++){struct usb_interface*IIllI=IlIIl->actconfig->interface[i];if
(IIllI==NULL)continue;
#if KERNEL_GT_EQ((0x8f3+7160-0x24e9),(0x942+1929-0x10c5),(0x27f+2037-0xa5e))
if(IlIIIlllI(&IIllI->dev)){llIlIIll(&IIllI->dev,(0x9a3+6107-0x217e));llIll(
"\x73\x65\x6e\x64\x20\x4b\x4f\x42\x4a\x5f\x41\x44\x44\x20\x66\x6f\x72\x20\x69\x6e\x74\x65\x72\x66\x61\x63\x65\x20\x25\x73" "\n"
,IlIIlI(&IIllI->dev));kobject_uevent(&IIllI->dev.kobj,KOBJ_ADD);}
#endif
if(IlllIIll&&IIllI->dev.driver==NULL){int lllIIllI;llIll(
"\x6c\x6f\x61\x64\x20\x64\x65\x66\x61\x75\x6c\x74\x20\x64\x72\x69\x76\x65\x72\x20\x66\x6f\x72\x20\x69\x6e\x74\x65\x72\x66\x61\x63\x65\x20\x25\x73" "\n"
,IlIIlI(&IIllI->dev));


lllIIllI=device_attach(&IIllI->dev);}}}llIll("\x2d\x2d" "\n");}








#if KERNEL_LT_EQ((0x66b+5933-0x1d96),(0x1617+1404-0x1b8d),(0x1ccc+1447-0x2260))


int lIlIIllIl(struct notifier_block*self,unsigned long lIllIII,void*dev){struct 
usb_device*IlIIl=dev;llIll(
"\x2b\x2b\x20\x61\x63\x74\x69\x6f\x6e\x3d\x25\x73\x28\x25\x6c\x75\x29\x20\x64\x65\x76\x3d\x25\x73" "\n"
,lllIlIII(lIllIII),lIllIII,IlIIl?IlIIlI(&IlIIl->dev):"\x6e\x6f\x6e\x65");if(
lIllIII==USB_DEVICE_ADD){if(llllllll(IlIIl)){IIIlIllI(IlIIl);}}if(lIllIII==
USB_DEVICE_REMOVE){

llllIIlI(IlIIl,(0xa6b+5117-0x1e68));}llIll("\x2d\x2d");return NOTIFY_OK;}struct 
notifier_block lIlIIIlI={.notifier_call=lIlIIllIl,.priority=INT_MAX,
};
#else 




int lIIIlIIII(struct notifier_block*self,unsigned long lIllIII,void*dev){struct 
device*lIIIIl=dev;llIll(
"\x2b\x2b\x20\x61\x63\x74\x69\x6f\x6e\x3d\x25\x73\x28\x25\x6c\x75\x29\x20\x64\x65\x76\x3d\x25\x73" "\n"
,IIllIlll(lIllIII),lIllIII,lIIIIl?IlIIlI(lIIIIl):"\x6e\x6f\x6e\x65");if(lIllIII
==BUS_NOTIFY_ADD_DEVICE){if(IlIlIIlII(lIIIIl)){struct usb_device*IlIIl=
to_usb_device(lIIIIl);



if(llllllll(IlIIl)){

if(llIllIII(IlIIl)>=(0xcb6+3208-0x193e)){
#if KERNEL_GT_EQ((0x139c+1711-0x1a49),(0x63f+4836-0x191d),(0x7f5+4578-0x19c1))







llIlIIll(&IlIIl->dev,(0xc84+3505-0x1a34));
#endif
}}}else if(lIIIIIIlI(lIIIIl)){struct usb_interface*IIllI=to_usb_interface(dev);
struct usb_device*IlIIl=interface_to_usbdev(IIllI);
if(IlIllIIl(IlIIl)){int IlIlI;
#if KERNEL_GT_EQ((0x6a4+3372-0x13ce),(0x16a+1660-0x7e0),(0x208c+841-0x23bb)) && \
KERNEL_LT_EQ((0x768+7722-0x2590),(0xb60+5343-0x2039),(0x1160+2639-0x1b88))
int state_in_sysfs;
#endif
#if KERNEL_GT_EQ((0x307+1206-0x7bb),(0x8d8+1058-0xcf4),(0x500+4878-0x17f8))
llIlIIll(&IIllI->dev,(0x5f+4151-0x1095));
#endif
llIll(
"\x63\x6c\x61\x69\x6d\x69\x6e\x67\x20\x69\x6e\x74\x65\x72\x66\x61\x63\x65\x20\x25\x73" "\n"
,IlIIlI(&IIllI->dev));
#if KERNEL_GT_EQ((0x6fd+2924-0x1267),(0x11ad+5258-0x2631),(0x45a+1050-0x85a)) &&\
 KERNEL_LT_EQ((0x7a2+2944-0x1320),(0xb20+4630-0x1d30),(0x1a94+1797-0x2172))























state_in_sysfs=lIIIIl->kobj.state_in_sysfs;lIIIIl->kobj.state_in_sysfs=
(0x438+365-0x5a5);
#endif
IlIlI=IIIlllIll(IIllI);
#if KERNEL_GT_EQ((0x9d2+519-0xbd7),(0x1037+5204-0x2485),(0x1400+294-0x150c)) && \
KERNEL_LT_EQ((0x1e12+1996-0x25dc),(0x116c+3915-0x20b1),(0x1655+3879-0x2555))

lIIIIl->kobj.state_in_sysfs=state_in_sysfs;
#endif
if(IlIlI<(0x1938+1334-0x1e6e)){llIll(
"\x69\x6e\x74\x65\x72\x66\x61\x63\x65\x20\x25\x73\x20\x6e\x6f\x74\x20\x63\x6c\x61\x69\x6d\x65\x64\x2c\x20\x65\x72\x72\x6f\x72\x20\x25\x64" "\n"
,IlIIlI(&IIllI->dev),IlIlI);}else if(IlIlI>(0x4a8+1378-0xa0a)){llIll(
"\x69\x6e\x74\x65\x72\x66\x61\x63\x65\x20\x25\x73\x20\x61\x63\x74\x75\x61\x6c\x6c\x79\x20\x63\x6c\x61\x69\x6d\x65\x64" "\n"
,IlIIlI(&IIllI->dev));}else
{llIll(
"\x69\x6e\x74\x65\x72\x66\x61\x63\x65\x20\x25\x73\x20\x63\x6c\x61\x69\x6d\x65\x64" "\n"
,IlIIlI(&IIllI->dev));}}}}else if(lIllIII==BUS_NOTIFY_DEL_DEVICE){if(lIIIIIIlI(
lIIIIl)){struct usb_interface*IIllI=to_usb_interface(dev);struct usb_device*
IlIIl=interface_to_usbdev(IIllI);if(IlIllIIl(IlIIl)){



}}else if(IlIlIIlII(lIIIIl)){struct usb_device*IlIIl=to_usb_device(lIIIIl);if(
IlIllIIl(IlIIl)){


lIIIlllI(IlIIl);}}}llIll("\x2d\x2d" "\n");return NOTIFY_OK;}struct 
notifier_block IIIIIIll={.notifier_call=lIIIlIIII,.priority=INT_MAX,
};
#endif 
#endif 

