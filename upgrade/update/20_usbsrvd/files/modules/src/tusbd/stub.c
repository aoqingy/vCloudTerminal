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
#if KERNEL_LT_EQ((0x2457+647-0x26dc),(0x6b8+1057-0xad3),(0xfeb+561-0x11f6))
#include <linux/smp_lock.h>
#endif
#if KERNEL_GT_EQ((0xf78+5223-0x23dd),(0xc8b+1234-0x1157),(0x11f6+1762-0x18b9))
#if KERNEL_LT_EQ((0x1008+303-0x1135),(0xec4+489-0x10a7),(0x788+1972-0xf1c))



#include "vhci_hcd.h"
#endif
#endif
static struct list_head lllllll;static spinlock_t lIIIII;extern struct IllllI*
IIllIlI;extern struct list_head lllIlIIl;extern struct mutex IIIIllll;
#if KERNEL_LT_EQ((0x73d+3818-0x1625),(0x1c94+199-0x1d55),(0x534+4665-0x175a))
extern struct notifier_block lIlIIIlI;
#else 
extern struct notifier_block IIIIIIll;
#endif
#ifdef _USBD_DEBUG_MEMORY_
extern atomic_t lllIlllll;extern atomic_t llIllllI;extern atomic_t llIIIlIIl;
#endif 


static struct usb_device_id lllIlIlII[]={{.driver_info=(0x1134+1894-0x1899)},{}}
;MODULE_DEVICE_TABLE(usb,lllIlIlII);static int IIIIIIlII(struct usb_interface*
IIllI,const struct usb_device_id*id);static void IlIIllIlI(struct usb_interface*
IIllI);
#if KERNEL_GT_EQ((0x757+264-0x85d),(0x9bc+1621-0x100b),(0x75a+1341-0xc80))
static int IllIlIlI(struct usb_interface*lIllII);static int llllIlIl(struct 
usb_interface*lIllII);
#elif KERNEL_GT_EQ((0x1ac1+2892-0x260b),(0xfab+36-0xfc9),(0x5e4+3976-0x155a))
static void IllIlIlI(struct usb_interface*lIllII);static void llllIlIl(struct 
usb_interface*lIllII);
#endif
void lIIlIlII(struct IllIl*lIlII);void IllIlIll(struct IllIl*lIlII);void 
IllIIIIl(struct IllIl*lIlII,Illlll lIIIl);struct IlIII*IlllIlIl(struct IllIl*
lIlII,Illlll lIIIl);struct usb_driver lllllII={.name=llIlIIII,.id_table=
lllIlIlII,.probe=IIIIIIlII,.disconnect=IlIIllIlI,
#if KERNEL_GT_EQ((0xb11+1813-0x1224),(0x1178+1444-0x1716),(0xecb+103-0xf20))
.pre_reset=IllIlIlI,.post_reset=llllIlIl,
#endif
};


static int IIIIIIlII(struct usb_interface*IIllI,const struct usb_device_id*id){
int IlIlI=-ENODEV;int lllllIlIl=(0x29f+6103-0x1a76);struct usb_device*IlIIl=
interface_to_usbdev(IIllI);char*IIIlllI=IlIIlIlI(&IlIIl->dev.kobj,GFP_KERNEL);
llIll(
"\x76\x69\x64\x3d\x30\x78\x25\x30\x34\x58\x20\x70\x69\x64\x3d\x30\x78\x25\x30\x34\x58\x20\x72\x65\x76\x3d\x30\x78\x25\x30\x34\x58\x20\x62\x75\x73\x5f\x69\x64\x3d" "\"" "\x25\x73" "\"" "\x20\x68\x75\x62\x3d" "\"" "\x25\x73" "\"" "\x20\x70\x61\x74\x68\x3d" "\"" "\x25\x73" "\"" "\x20\x69\x6e\x74\x65\x72\x66\x61\x63\x65\x3d\x25\x75\x20\x74\x6f\x74\x61\x6c\x5f\x69\x6e\x74\x65\x72\x66\x61\x63\x65\x73\x3d\x25\x75" "\n"
,le16_to_cpu(IlIIl->descriptor.idVendor),le16_to_cpu(IlIIl->descriptor.idProduct
),le16_to_cpu(IlIIl->descriptor.bcdDevice),IlIIlI(&IlIIl->dev),IlIIl->bus->
controller->driver->name,IIIlllI,IIllI->cur_altsetting->desc.bInterfaceNumber,
IlIIl->actconfig->desc.bNumInterfaces);if(IIIlllI)kfree(IIIlllI);if(IlIllIIl(
IlIIl)){lllllIlIl=(0x75c+7566-0x24e9);}else if(llllllll(IlIIl)){IlIlI=llIllIII(
IlIIl);if(IlIlI<(0xacb+4359-0x1bd2)){IIIIll(
"\x63\x61\x6e\x20\x6e\x6f\x74\x20\x61\x74\x74\x61\x63\x68\x20\x75\x73\x62\x20\x64\x65\x76\x69\x63\x65\x20\x25\x73\x2c\x20\x65\x72\x72\x6f\x72\x20\x25\x64" "\n"
,IlIIlI(&IlIIl->dev),IlIlI);}else{lllllIlIl=(0xd4+3214-0xd61);}}if(lllllIlIl){
IlIlI=IIIllllIl(IIllI,(0xde0+2694-0x1866));if(IlIlI<(0xe0a+3051-0x19f5)){IIIIll(
"\x63\x61\x6e\x20\x6e\x6f\x74\x20\x61\x74\x74\x61\x63\x68\x20\x75\x73\x62\x20\x69\x6e\x74\x65\x72\x66\x61\x63\x65\x20\x25\x73\x2c\x20\x65\x72\x72\x6f\x72\x20\x25\x64" "\n"
,IlIIlI(&IIllI->dev),IlIlI);}}return IlIlI;}
static void IlIIllIlI(struct usb_interface*IIllI){llIll("\x2b\x2b" "\n");if(
usb_get_intfdata(IIllI)!=(void*)-(0xff3+1183-0x1491)){lIlIIlIll(IIllI);}llIll(
"\x2d\x2d" "\n");}
#if KERNEL_GT_EQ((0xa23+4404-0x1b55),(0x1db+4315-0x12b0),(0xdfb+5341-0x22c1))
static int IllIlIlI(struct usb_interface*lIllII){return(0x617+6087-0x1dde);}
static int llllIlIl(struct usb_interface*lIllII){return(0x14d7+672-0x1777);}
#elif KERNEL_GT_EQ((0x1396+1287-0x189b),(0xe7f+5496-0x23f1),(0x12bc+1691-0x1945)\
)
static void IllIlIlI(struct usb_interface*lIllII){return;}static void llllIlIl(
struct usb_interface*lIllII){return;}
#endif


int IlIllIIl(struct usb_device*IlIIl){int lllIIllIl=(0x1c56+1686-0x22ec);struct 
IllIl*lIlII;spin_lock(&lIIIII);list_for_each_entry(lIlII,&lllllll,llllII){if(
lIlII->llIII==IlIIl){lllIIllIl=(0x77a+1539-0xd7c);break;}}spin_unlock(&lIIIII);
return lllIIllIl;}
int llIllIII(struct usb_device*IlIIl){llIll("\x2b\x2b\x20\x25\x73" "\n",IlIIlI(&
IlIIl->dev));if(lIllIIIll(IlIIl)==NULL){llIll(
"\x63\x61\x6e\x20\x6e\x6f\x74\x20\x63\x72\x65\x61\x74\x65\x20\x73\x74\x75\x62" "\n"
);return-ENOMEM;}llIll("\x2d\x2d" "\n");return(0xe2d+5199-0x227c);}
int lIIIlllI(struct usb_device*IlIIl){struct IllIl*lIlII;llIll(
"\x2b\x2b\x20\x25\x73" "\n",IlIIlI(&IlIIl->dev));lIlII=llIlIllI(IlIIl);if(lIlII)
{IlIlIlII(lIlII,NULL,(0xcc8+5431-0x21ff),(0x218+9258-0x2641));IlIIllII(lIlII);
lIlIIlIl(lIlII);}else{llIll(
"\x64\x65\x76\x69\x63\x65\x20\x6e\x6f\x74\x20\x66\x6f\x75\x6e\x64" "\n");}llIll(
"\x2d\x2d" "\n");return(0x44d+894-0x7cb);}int IIIllllIl(struct usb_interface*
IIllI,int IIIllIIII){int IlIlI=-ENODEV;struct usb_device*IlIIl=
interface_to_usbdev(IIllI);struct IllIl*lIlII;llIll("\x2b\x2b" "\n");lIlII=
llIlIllI(IlIIl);if(lIlII){


lIlII->IIIllIIl+=IIIllIIII;lIlII->IIIlllIl=IlIIl->actconfig?IlIIl->actconfig->
desc.bNumInterfaces:(0x6bf+3009-0x1280);if(++lIlII->IIlllIlI==lIlII->IIIlllIl){
lllllIlII(lIlII);}llIll(
"\x69\x6e\x69\x74\x5f\x69\x6e\x74\x65\x72\x66\x61\x63\x65\x73\x3d\x25\x64\x20\x74\x6f\x74\x61\x6c\x5f\x69\x6e\x74\x65\x72\x66\x61\x63\x65\x73\x3d\x25\x64" "\n"
,lIlII->IIlllIlI,lIlII->IIIlllIl);usb_set_intfdata(IIllI,lIlII);
IlIlI=(0x1482+4550-0x2648);}llIll(
"\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x3d\x25\x64" "\n",IlIlI);return IlIlI;}
void lIlIIlIll(struct usb_interface*IIllI){struct IllIl*lIlII;llIll(
"\x2b\x2b" "\n");
lIlII=usb_get_intfdata(IIllI);usb_set_intfdata(IIllI,NULL);lIlII->IIlllIlI--;
lIIlllllI(lIlII);
IIIIIllll(lIlII,IIllI,NULL,(0x5d8+2958-0x1165));llIll(
"\x69\x6e\x69\x74\x5f\x69\x6e\x74\x65\x72\x66\x61\x63\x65\x73\x3d\x25\x64\x20\x74\x6f\x74\x61\x6c\x5f\x69\x6e\x74\x65\x72\x66\x61\x63\x65\x73\x3d\x25\x64" "\n"
,lIlII->IIlllIlI,lIlII->IIIlllIl);lIlIIlIl(lIlII);
llIll("\x2d\x2d" "\n");}

int IlIIIIlll(void){int lIIIllIII=(0x1d4f+2306-0x2651);int IIlIlIlIl=
(0x69f+3535-0x146e);int IlIlI=(0xe8a+1527-0x1481);do{INIT_LIST_HEAD(&lllllll);
spin_lock_init(&lIIIII);INIT_LIST_HEAD(&lllIlIIl);mutex_init(&IIIIllll);IIllIlI=
lllIlllII();if(IIllIlI==NULL){IlIlI=-ENOMEM;IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x69\x6e\x69\x74\x5f\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x75\x73\x62\x64\x5f\x6c\x6f\x61\x64\x65\x72\x5f\x61\x6c\x6c\x6f\x63\x5f\x6d\x69\x6e\x6f\x72\x2e\x20\x45\x72\x72\x6f\x72\x20\x6e\x75\x6d\x62\x65\x72\x20\x25\x64" "\n"
,IlIlI);break;}


IlIlI=usb_register(&lllllII);if(IlIlI!=(0x1960+748-0x1c4c)){IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x69\x6e\x69\x74\x5f\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x75\x73\x62\x5f\x72\x65\x67\x69\x73\x74\x65\x72\x20\x66\x61\x69\x6c\x65\x64\x2e\x20\x45\x72\x72\x6f\x72\x20\x6e\x75\x6d\x62\x65\x72\x20\x25\x64" "\n"
,IlIlI);break;}lIIIllIII=(0x151+1510-0x736);
#if KERNEL_LT_EQ((0x1197+4040-0x215d),(0x1568+1039-0x1971),(0x51b+4599-0x16ff))
usb_register_notify(&lIlIIIlI);
#else 
IlIlI=bus_register_notifier(lllllII.drvwrap.driver.bus,&IIIIIIll);if(IlIlI!=
(0x14e8+1186-0x198a)){IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x69\x6e\x69\x74\x5f\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x62\x75\x73\x5f\x72\x65\x67\x69\x73\x74\x65\x72\x5f\x6e\x6f\x74\x69\x66\x69\x65\x72\x20\x66\x61\x69\x6c\x65\x64\x2e\x20\x45\x72\x72\x6f\x72\x20\x6e\x75\x6d\x62\x65\x72\x20\x25\x64" "\n"
,IlIlI);break;}
#endif
IIlIlIlIl=(0xd80+2345-0x16a8);}while((0x631+1355-0xb7c));if(IlIlI!=
(0x650+1069-0xa7d)){if(IIlIlIlIl)
#if KERNEL_LT_EQ((0xc37+582-0xe7b),(0x638+7619-0x23f5),(0x794+5263-0x1c10))
usb_unregister_notify(&lIlIIIlI);
#else 
bus_unregister_notifier(lllllII.drvwrap.driver.bus,&IIIIIIll);
#endif
if(lIIIllIII)usb_deregister(&lllllII);if(IIllIlI){IlIlIlIl(IIllIlI);IIllIlI=NULL
;}}return IlIlI;}void IIIIlIIlI(void){struct list_head llIlIll;IlIlIIIl();
#if KERNEL_LT_EQ((0xc41+766-0xf3d),(0x541+4588-0x1727),(0x1fd6+450-0x2185))
usb_unregister_notify(&lIlIIIlI);
#else 
bus_unregister_notifier(lllllII.drvwrap.driver.bus,&IIIIIIll);
#endif
usb_deregister(&lllllII);if(IIllIlI){IlIlIlIl(IIllIlI);IIllIlI=NULL;}
INIT_LIST_HEAD(&llIlIll);spin_lock(&lIIIII);list_splice_init(&lllllll,&llIlIll);
spin_unlock(&lIIIII);while(!list_empty(&llIlIll)){struct IllIl*lIlII=list_entry(
llIlIll.next,struct IllIl,llllII);IlIIllII(lIlII);}}struct IllIl*lIllIIIll(
struct usb_device*IlIIl){char*IIIlllI;struct IllIl*lIlII;IIIlllI=IlIIlIlI(&IlIIl
->dev.kobj,GFP_KERNEL);if(IIIlllI==NULL){return NULL;}lIlII=IlIIllI(sizeof(*
lIlII),GFP_KERNEL);if(lIlII){INIT_LIST_HEAD(&lIlII->llllII);init_waitqueue_head(
&lIlII->lllIll);INIT_LIST_HEAD(&lIlII->IIlIllll);spin_lock_init(&lIlII->lIIllll)
;INIT_LIST_HEAD(&lIlII->lIlIIlI);spin_lock_init(&lIlII->IlIIIl);INIT_LIST_HEAD(&
lIlII->lIlIIlII);kref_init(&lIlII->lllllIl);lIlII->vid=le16_to_cpu(IlIIl->
descriptor.idVendor);lIlII->IllIIII=le16_to_cpu(IlIIl->descriptor.idProduct);
lIlII->IlIllIl=le16_to_cpu(IlIIl->descriptor.bcdDevice);strncpy(lIlII->bus_id,
IlIIlI(&IlIIl->dev),BUS_ID_SIZE-(0x67a+4455-0x17e0));lIlII->lIIIllII=
(0x4f9+5428-0x1a2d);lIlII->IIIllIIl=(0x3d3+2537-0xdbc);lIlII->IIIlIIII=IIlllIIlI
;lIlII->llIII=usb_get_dev(IlIIl);lIlII->IIIlllIl=(0x89c+6060-0x2048);lIlII->
IIlllIlI=(0xd8a+69-0xdcf);lIlII->llIlllI=(0x1a78+1125-0x1edd);lIlII->llIIlIlI=
IIIlllI;lIlII->lllIIlI=(0x10b2+988-0x148e);lIlII->IIlIIlll=(0x22a1+200-0x2369);
lIlII->llllIllI=-(0xb8c+4236-0x1c17);lIlII->lIlllIlI=-(0x969+6656-0x2368);lIlII
->llIIIII=NULL;lIlII->IlllIlI[(0x93b+4568-0x1b13)].name="\x74\x79\x70\x65";lIlII
->IlllIlI[(0x4af+556-0x6db)].IIllllIl="\x73\x74\x75\x62";lIlII->IlllIlI[
(0x1db8+2119-0x25fe)].name="\x64\x65\x76";lIlII->IlllIlI[(0x449+6552-0x1de0)].
IIllllIl=IIIlllI;lIlII->IlllIlI[(0xf71+2328-0x1887)].name=NULL;lIlII->IlllIlI[
(0xa7+80-0xf5)].IIllllIl=NULL;lIlII->lIIIIll=(strcmp(IlIIl->bus->controller->
driver->name,"\x65\x68\x63\x69\x5f\x68\x63\x64")==(0x1805+600-0x1a5d));







if(strcmp(IlIIl->bus->controller->driver->name,"\x64\x77\x63\x5f\x6f\x74\x67")==
(0x3ed+7733-0x2222)){


lIlII->IIlIllI=llIIlIl;lIlII->IIIIIlll=llIIlIl;lIlII->IllIllII=llIIlIl;}else{
#if KERNEL_LT_EQ((0x780+5699-0x1dc1),(0x502+4190-0x155a),(0x85a+6093-0x2009))


lIlII->IIlIllI=lIlllll;lIlII->IIIIIlll=llIIlIl;lIlII->IllIllII=lIlllll;IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x63\x72\x65\x61\x74\x65\x3a\x20\x62\x75\x66\x66\x65\x72\x20\x74\x79\x70\x65\x73\x20\x62\x75\x6c\x6b\x3d\x70\x74\x20\x69\x6e\x74\x3d\x73\x6c\x20\x69\x73\x6f\x3d\x70\x74" "\n"
);
#elif KERNEL_EQ((0x19b8+641-0x1c37),(0x365+6286-0x1bed),(0x1bf8+319-0x1d18))



if(bus_to_hcd(IlIIl->bus)->driver->flags&HCD_USB3){lIlII->IIlIllI=lIlIllI;IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x63\x72\x65\x61\x74\x65\x3a\x20\x62\x75\x66\x66\x65\x72\x20\x74\x79\x70\x65\x73\x20\x62\x75\x6c\x6b\x3d\x73\x67\x20\x69\x6e\x74\x3d\x73\x6c\x20\x69\x73\x6f\x3d\x70\x74" "\n"
);}else{lIlII->IIlIllI=lIlllll;IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x63\x72\x65\x61\x74\x65\x3a\x20\x62\x75\x66\x66\x65\x72\x20\x74\x79\x70\x65\x73\x20\x62\x75\x6c\x6b\x3d\x70\x74\x20\x69\x6e\x74\x3d\x73\x6c\x20\x69\x73\x6f\x3d\x70\x74" "\n"
);}lIlII->IIIIIlll=llIIlIl;lIlII->IllIllII=lIlllll;
#elif KERNEL_EQ((0x6c+3268-0xd2e),(0x19d5+1989-0x2194),(0x117+4951-0x144e))



if(bus_to_hcd(IlIIl->bus)->driver->flags&HCD_USB3){lIlII->IIlIllI=lIlIllI;lIlII
->IIIIIlll=lIlIllI;IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x63\x72\x65\x61\x74\x65\x3a\x20\x62\x75\x66\x66\x65\x72\x20\x74\x79\x70\x65\x73\x20\x62\x75\x6c\x6b\x3d\x73\x67\x20\x69\x6e\x74\x3d\x73\x67\x20\x69\x73\x6f\x3d\x70\x74" "\n"
);}else{lIlII->IIlIllI=lIlllll;lIlII->IIIIIlll=llIIlIl;IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x63\x72\x65\x61\x74\x65\x3a\x20\x62\x75\x66\x66\x65\x72\x20\x74\x79\x70\x65\x73\x20\x62\x75\x6c\x6b\x3d\x70\x74\x20\x69\x6e\x74\x3d\x73\x6c\x20\x69\x73\x6f\x3d\x70\x74" "\n"
);}lIlII->IllIllII=lIlllll;
#elif KERNEL_GT_EQ((0x446+10-0x44e),(0x1bd5+909-0x1f5c),(0x228b+854-0x25c0))





if(IlIIl->bus->sg_tablesize>(0x52b+5890-0x1c2d)){lIlII->IIlIllI=lIlIllI;lIlII->
IIIIIlll=lIlIllI;IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x63\x72\x65\x61\x74\x65\x3a\x20\x62\x75\x66\x66\x65\x72\x20\x74\x79\x70\x65\x73\x20\x62\x75\x6c\x6b\x3d\x73\x67\x20\x69\x6e\x74\x3d\x73\x67\x20\x69\x73\x6f\x3d\x70\x74" "\n"
);}else{lIlII->IIlIllI=lIlllll;lIlII->IIIIIlll=llIIlIl;IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x63\x72\x65\x61\x74\x65\x3a\x20\x62\x75\x66\x66\x65\x72\x20\x74\x79\x70\x65\x73\x20\x62\x75\x6c\x6b\x3d\x70\x74\x20\x69\x6e\x74\x3d\x73\x6c\x20\x69\x73\x6f\x3d\x70\x74" "\n"
);}lIlII->IllIllII=lIlllll;
#endif
}
#ifdef _USBD_DEBUG_MEMORY_
atomic_inc(&lllIlllll);
#endif
if(llIlIIIll(lIlII)<(0x54b+3908-0x148f)){
#ifdef _USBD_DEBUG_MEMORY_
atomic_inc(&llIllllI);
#endif
IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x63\x72\x65\x61\x74\x65\x3a\x20\x61\x6c\x6c\x6f\x63\x20\x6d\x69\x6e\x6f\x72\x20\x66\x61\x69\x6c\x65\x64" "\n"
);lIlIIlIl(lIlII);return NULL;}spin_lock(&lIIIII);list_add(&lIlII->llllII,&
lllllll);spin_unlock(&lIIIII);if(lIIIlIIll(lIlII)<(0x4da+2980-0x107e)){IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x63\x72\x65\x61\x74\x65\x3a\x20\x72\x65\x67\x69\x73\x74\x65\x72\x20\x6d\x69\x6e\x6f\x72\x20\x66\x61\x69\x6c\x65\x64" "\n"
);IlIIllII(lIlII);return NULL;}return lIlII;}llIIlIIIl(IIIlllI);return NULL;}
void IlIIllII(struct IllIl*lIlII){
#ifdef _USBD_DEBUG_MEMORY_
atomic_inc(&llIllllI);
#endif
spin_lock(&lIIIII);list_del_init(&lIlII->llllII);spin_unlock(&lIIIII);lIIllllI(
lIlII);lIlIIlIl(lIlII);}
void IlIlIlIIl(struct kref*llllIlII){struct IllIl*lIlII=container_of(llllIlII,
struct IllIl,lllllIl);IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x64\x65\x73\x74\x72\x6f\x79\x2b\x2b" "\n"
);
#ifdef _USBD_DEBUG_MEMORY_
atomic_inc(&llIIIlIIl);
#endif
spin_lock(&lIIIII);list_del_init(&lIlII->llllII);spin_unlock(&lIIIII);IIllllIlI(
lIlII);while(!list_empty(&lIlII->IIlIllll)){struct IlIII*IIIll=list_entry(lIlII
->IIlIllll.next,struct IlIII,IlIlIl);list_del(&IIIll->IlIlIl);lllIllI(IIIll);}
while(!list_empty(&lIlII->lIlIIlI)){struct IlIII*IIIll=list_entry(lIlII->lIlIIlI
.next,struct IlIII,IlIlIl);list_del(&IIIll->IlIlIl);lllIllI(IIIll);}if(lIlII->
llIII){usb_put_dev(lIlII->llIII);lIlII->llIII=NULL;}if(lIlII->llIIlIlI){
llIIlIIIl(lIlII->llIIlIlI);lIlII->llIIlIlI=NULL;}lllIII(lIlII);IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x64\x65\x73\x74\x72\x6f\x79\x2d\x2d" "\n"
);}struct IllIl*llIlIllI(struct usb_device*IlIIl){struct IllIl*lIlII;spin_lock(&
lIIIII);list_for_each_entry(lIlII,&lllllll,llllII){if(lIlII->llIII==IlIIl){
IlllIIlI(lIlII);spin_unlock(&lIIIII);return lIlII;}}spin_unlock(&lIIIII);return 
NULL;}void lllllIlII(struct IllIl*lIlII){if(!lIlII->llIlllI){lIlII->llIlllI=
(0x1607+4017-0x25b7);lllIlllI(lIlII);lIllllIl(lIlII->lIllI);llIll(
"\x69\x6e\x69\x74\x5f\x69\x6e\x74\x65\x72\x66\x61\x63\x65\x73\x3d\x25\x64\x20\x74\x6f\x74\x61\x6c\x5f\x69\x6e\x74\x65\x72\x66\x61\x63\x65\x73\x3d\x25\x64\x20\x6f\x6e\x6c\x69\x6e\x65\x3d\x25\x64" "\n"
,lIlII->IIlllIlI,lIlII->IIIlllIl,lIlII->llIlllI);}}void lIIlllllI(struct IllIl*
lIlII){if(lIlII->llIlllI){lIlII->llIlllI=(0x114+2253-0x9e1);lIIlIlII(lIlII);
lIIllIll(lIlII->lIllI);llIll(
"\x69\x6e\x69\x74\x5f\x69\x6e\x74\x65\x72\x66\x61\x63\x65\x73\x3d\x25\x64\x20\x74\x6f\x74\x61\x6c\x5f\x69\x6e\x74\x65\x72\x66\x61\x63\x65\x73\x3d\x25\x64\x20\x6f\x6e\x6c\x69\x6e\x65\x3d\x25\x64" "\n"
,lIlII->IIlllIlI,lIlII->IIIlllIl,lIlII->llIlllI);}}void llllIIlIl(struct IllIl*
lIlII){if(lIlII->llIlllI){lIllllIl(lIlII->lIllI);}else{lIIllIll(lIlII->lIllI);}}
int IIlllIllI(struct IllIl*lIlII){llIll(
"\x69\x6e\x69\x74\x5f\x69\x6e\x74\x65\x72\x66\x61\x63\x65\x73\x3d\x25\x64\x20\x74\x6f\x74\x61\x6c\x5f\x69\x6e\x74\x65\x72\x66\x61\x63\x65\x73\x3d\x25\x64\x20\x6f\x6e\x6c\x69\x6e\x65\x3d\x25\x64" "\n"
,lIlII->IIlllIlI,lIlII->IIIlllIl,lIlII->llIlllI);return(lIlII->llIlllI==
(0x806+1684-0xe9a));}


void IlIIIIlII(struct IllIl*lIlII,int lIllllI){int i,lllIIllI;IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x72\x65\x73\x65\x74\x2b\x2b" "\n");
lIlII->IIIllIIl=(0x5eb+4045-0x15b8);if(lIlII->llIII->actconfig){



for(i=(0xa55+5608-0x203d);i<lIlII->llIII->actconfig->desc.bNumInterfaces;i++){
struct usb_interface*IIllI=lIlII->llIII->actconfig->interface[i];if(IIllI&&IIllI
->num_altsetting>(0x13a2+382-0x151f)){struct usb_host_interface*llllllI=
usb_altnum_to_altsetting(IIllI,(0x130+3227-0xdcb));if(llllllI){lllIIllI=
usb_set_interface(lIlII->llIII,llllllI->desc.bInterfaceNumber,llllllI->desc.
bAlternateSetting);}}}}if(lIllllI==IlIIIIIIl){
if((lIlII->lIIIllII&llIlIllIl)==(0x1c6f+1600-0x22af)){IIIIll(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x72\x65\x73\x65\x74\x3a\x20\x74\x72\x79\x69\x6e\x67\x20\x74\x6f\x20\x72\x65\x73\x65\x74\x20\x64\x65\x76\x69\x63\x65\x20\x76\x69\x64\x20\x25\x30\x34\x78\x20\x70\x69\x64\x20\x25\x30\x34\x78" "\n"
,lIlII->vid,lIlII->IllIIII);lllIIllI=usb_reset_device(lIlII->llIII);IIIIll(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x72\x65\x73\x65\x74\x3a\x20\x75\x73\x62\x5f\x72\x65\x73\x65\x74\x5f\x64\x65\x76\x69\x63\x65\x20\x72\x65\x74\x75\x72\x6e\x65\x64\x20\x25\x64" "\n"
,lllIIllI);}}memset(lIlII->IIllIIIl,(0x465+386-0x5e7),sizeof(lIlII->IIllIIIl));
memset(lIlII->lIlllIIl,(0xed1+5428-0x2405),sizeof(lIlII->lIlllIIl));IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x72\x65\x73\x65\x74\x2d\x2d" "\n");}
void lIlIIIlll(struct IllIl*lIlII,int lIllllI){if(usb_lock_device_for_reset(
lIlII->llIII,NULL)>=(0x14ad+3732-0x2341)){IlIIIIlII(lIlII,lIllllI);
usb_unlock_device(lIlII->llIII);}else{memset(lIlII->IIllIIIl,(0x21c5+542-0x23e3)
,sizeof(lIlII->IIllIIIl));memset(lIlII->lIlllIIl,(0x1036+4949-0x238b),sizeof(
lIlII->lIlllIIl));}}int IIIIIIII(struct IllIl*lIlII,int pipe){if(!usb_pipeisoc(
pipe))return(0xad+5384-0x15b5);if(usb_pipein(pipe))return(++lIlII->IIllIIlI[
usb_pipeendpoint(pipe)]);else return(++lIlII->llllIIll[usb_pipeendpoint(pipe)]);
}int IIlIlIIl(struct IllIl*lIlII,int pipe){if(!usb_pipeisoc(pipe))return
(0x961+3247-0x1610);if(usb_pipein(pipe))return(--lIlII->IIllIIlI[
usb_pipeendpoint(pipe)]);else return(--lIlII->llllIIll[usb_pipeendpoint(pipe)]);
}void llllIlIII(struct IllIl*lIlII,int pipe){if(!usb_pipeisoc(pipe))return;if(
usb_pipein(pipe))lIlII->IIllIIlI[usb_pipeendpoint(pipe)]=(0xc50+1010-0x1042);
else lIlII->llllIIll[usb_pipeendpoint(pipe)]=(0xfd6+3325-0x1cd3);}int lIIllIII(
struct IllIl*lIlII,int pipe){if(!usb_pipeisoc(pipe))return(0x84+1992-0x84c);if(
usb_pipein(pipe))return lIlII->IIllIIIl[usb_pipeendpoint(pipe)];else return 
lIlII->lIlllIIl[usb_pipeendpoint(pipe)];}void lIlIlIII(struct IllIl*lIlII,int 
pipe,int IlIIIll){if(!usb_pipeisoc(pipe))return;if(usb_pipein(pipe))lIlII->
IIllIIIl[usb_pipeendpoint(pipe)]=IlIIIll;else lIlII->lIlllIIl[usb_pipeendpoint(
pipe)]=IlIIIll;}static void lIIIIlllI(struct IlIII*IIIll){if(IIIll->lIllll==
llIIlIl){if(IIIll->IlIlII.lIlll){llIll(
"\x3a\x20\x75\x6e\x6c\x69\x6e\x6b\x69\x6e\x67\x20\x75\x72\x62\x20\x30\x78\x25\x70\x20\x75\x6e\x69\x71\x75\x65\x5f\x69\x64\x3d\x30\x78\x25\x6c\x6c\x78" "\n"
,IIIll->IlIlII.lIlll,IIIll->lIIIl);


usb_unlink_urb(IIIll->IlIlII.lIlll);}}else if(IIIll->lIllll==lIlllll){llIll(
"\x3a\x20\x75\x6e\x6c\x69\x6e\x6b\x69\x6e\x67\x20\x75\x63\x20\x75\x6e\x69\x71\x75\x65\x5f\x69\x64\x3d\x30\x78\x25\x6c\x6c\x78" "\n"
,IIIll->lIIIl);IIlIIIlIl(&IIIll->IIllIl.IlIIIII);}
#if KERNEL_GT_EQ((0x963+2561-0x1362),(0xef1+960-0x12ab),(0x7e5+5886-0x1ec4))
else if(IIIll->lIllll==lIlIllI){if(IIIll->lIllIll.lIlll){llIll(
"\x3a\x20\x75\x6e\x6c\x69\x6e\x6b\x69\x6e\x67\x20\x73\x67\x20\x30\x78\x25\x70\x20\x75\x6e\x69\x71\x75\x65\x5f\x69\x64\x3d\x30\x78\x25\x6c\x6c\x78" "\n"
,IIIll->lIllIll.lIlll,IIIll->lIIIl);


usb_unlink_urb(IIIll->lIllIll.lIlll);}}
#endif
else{
IIIIll(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x75\x6e\x6c\x69\x6e\x6b\x5f\x72\x65\x71\x75\x65\x73\x74\x3a\x20\x69\x6e\x74\x65\x72\x6e\x61\x6c\x20\x65\x72\x72\x6f\x72\x21" "\n"
);}}static void llIlIlIIl(struct IlIII*IIIll){if(IIIll->lIllll==llIIlIl){if(
IIIll->IlIlII.lIlll){llIll(
"\x3a\x20\x6b\x69\x6c\x69\x6e\x67\x20\x75\x72\x62\x20\x30\x78\x25\x70\x20\x75\x6e\x69\x71\x75\x65\x5f\x69\x64\x3d\x30\x78\x25\x6c\x6c\x78" "\n"
,IIIll->IlIlII.lIlll,IIIll->lIIIl);usb_kill_urb(IIIll->IlIlII.lIlll);}}else if(
IIIll->lIllll==lIlllll){llIll(
"\x3a\x20\x6b\x69\x6c\x6c\x69\x6e\x67\x20\x75\x63\x20\x75\x6e\x69\x71\x75\x65\x5f\x69\x64\x3d\x30\x78\x25\x6c\x6c\x78" "\n"
,IIIll->lIIIl);lIllIIIII(&IIIll->IIllIl.IlIIIII);}
#if KERNEL_GT_EQ((0x1edf+1393-0x244e),(0x201d+1491-0x25ea),(0xed+219-0x1a9))
else if(IIIll->lIllll==lIlIllI){if(IIIll->lIllIll.lIlll){llIll(
"\x3a\x20\x6b\x69\x6c\x6c\x69\x6e\x67\x20\x73\x67\x20\x30\x78\x25\x70\x20\x75\x6e\x69\x71\x75\x65\x5f\x69\x64\x3d\x30\x78\x25\x6c\x6c\x78" "\n"
,IIIll->lIllIll.lIlll,IIIll->lIIIl);usb_kill_urb(IIIll->lIllIll.lIlll);}}
#endif
else{
IIIIll(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x6b\x69\x6c\x6c\x5f\x72\x65\x71\x75\x65\x73\x74\x3a\x20\x69\x6e\x74\x65\x72\x6e\x61\x6c\x20\x65\x72\x72\x6f\x72\x21" "\n"
);}}
void IIIIIllll(struct IllIl*lIlII,struct usb_interface*lIllII,struct IlIII*
lIlIlll,int lllIIII){int i;unsigned long flags;struct IlIII*IIIlll,*IIlIlIl;
llIll("\x2b\x2b" "\n");
if(lIlII->lllIIlI&&lIlII->IIlIIlll==lIllII->cur_altsetting->desc.
bInterfaceNumber)
{lIIlIlII(lIlII);}for(i=(0xcb4+4265-0x1d5d);i<lIllII->cur_altsetting->desc.
bNumEndpoints;i++){do{IIlIlIl=NULL;spin_lock_irqsave(&lIlII->IlIIIl,flags);
list_for_each_entry(IIIlll,&lIlII->lIlIIlI,IlIlIl){
if(IIIlll==lIlIlll)continue;
if(IIIlll->endpoint==(IIIII)-(0x2118+1075-0x254a))continue;
if(IIIlll->endpoint!=lIllII->cur_altsetting->endpoint[i].desc.bEndpointAddress)
continue;
IIIlll->endpoint=(IIIII)-(0x13c4+858-0x171d);IIIlll->lllIIII=lllIIII;
if(IIIlll->lIlIll.IIIIIIIl){


IIIlll=IlllIlIl(lIlII,IIIlll->lIIIl);}if(atomic_xchg(&IIIlll->state,IIllIIl)==
IIIIlIl){



kref_get(&IIIlll->lllllIl);

IIlIlIl=IIIlll;break;}}spin_unlock_irqrestore(&lIlII->IlIIIl,flags);if(IIlIlIl){
llIlIlIIl(IIlIlIl);kref_put(&IIlIlIl->lllllIl,lllllIlI);}}while(IIlIlIl);}llIll(
"\x2d\x2d" "\n");}void lIlIllIlI(struct IllIl*lIlII,int endpoint,struct IlIII*
lIlIlll){unsigned long flags;struct IlIII*IIIlll,*IIIlIII;llIll("\x2b\x2b" "\n")
;if(lIlII->lllIIlI)
{if(endpoint==lIlII->llllIllI||endpoint==lIlII->lIlllIlI){IllIlIll(lIlII);}}




do{IIIlIII=NULL;spin_lock_irqsave(&lIlII->IlIIIl,flags);list_for_each_entry(
IIIlll,&lIlII->lIlIIlI,IlIlIl){
if(IIIlll==lIlIlll)continue;
if(IIIlll->endpoint==(IIIII)-(0xe26+1706-0x14cf))continue;
if(IIIlll->endpoint!=endpoint)continue;
IIIlll->endpoint=(IIIII)-(0x1621+1076-0x1a54);
if(IIIlll->lIlIll.IIIIIIIl){


IIIlll=IlllIlIl(lIlII,IIIlll->lIIIl);}if(atomic_xchg(&IIIlll->state,IIllIIl)==
IIIIlIl){



kref_get(&IIIlll->lllllIl);

IIIlIII=IIIlll;break;}}spin_unlock_irqrestore(&lIlII->IlIIIl,flags);if(IIIlIII){
lIIIIlllI(IIIlIII);kref_put(&IIIlIII->lllllIl,lllllIlI);}}while(IIIlIII);llIll(
"\x2d\x2d" "\n");}void IIlllIIIl(struct IllIl*lIlII,Illlll lIIIl,struct IlIII*
lIlIlll){int lIlIIII;unsigned long flags;struct IlIII*IIIlll,*IIIlIII;llIll(
"\x2b\x2b" "\n");spin_lock_irqsave(&lIlII->IlIIIl,flags);if(lIlII->lllIIlI){if(
lIlII->llIIIII&&lIlII->llIIIII->lIIIl==lIIIl){spin_unlock_irqrestore(&lIlII->
IlIIIl,flags);IllIlIll(lIlII);return;}}



lIlIIII=(0x8a0+943-0xc4f);IIIlIII=NULL;list_for_each_entry(IIIlll,&lIlII->
lIlIIlI,IlIlIl){
if(IIIlll==lIlIlll)continue;if(IIIlll->lIIIl==lIIIl){if(atomic_xchg(&IIIlll->
state,IIllIIl)==IIIIlIl){



kref_get(&IIIlll->lllllIl);

IIIlIII=IIIlll;}lIlIIII=(0x7f1+2929-0x1361);break;}}if(!lIlIIII){IllIIIIl(lIlII,
lIIIl);}spin_unlock_irqrestore(&lIlII->IlIIIl,flags);if(IIIlIII){lIIIIlllI(
IIIlIII);kref_put(&IIIlIII->lllllIl,lllllIlI);}else{llIll(
"\x6e\x6f\x74\x20\x66\x6f\x75\x6e\x64" "\n");}llIll("\x2d\x2d" "\n");}void 
IlIlIlII(struct IllIl*lIlII,struct IlIII*lIlIlll,int IIIllIIlI,int lllIIII){
struct IlIII*IIlIlIl,*IIIlll;unsigned long flags;IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x6b\x69\x6c\x6c\x5f\x61\x6c\x6c\x5f\x72\x65\x71\x75\x65\x73\x74\x73\x3a\x20\x2b\x2b" "\n"
);

lIIlIlII(lIlII);

spin_lock_irqsave(&lIlII->IlIIIl,flags);while(!list_empty(&lIlII->lIlIIlII)){
struct lIIIlIlI*IlIIll=list_entry(lIlII->lIlIIlII.next,struct lIIIlIlI,llllII);
list_del(&IlIIll->llllII);lllIII(IlIIll);}

do{


IIlIlIl=NULL;list_for_each_entry(IIIlll,&lIlII->lIlIIlI,IlIlIl){if(IIIllIIlI){
IIIlll->lIlllIl=(0xf9d+4350-0x209a);}if(lllIIII){
IIIlll->lllIIII=(0x15ff+2044-0x1dfa);}
if(IIIlll!=lIlIlll&&atomic_xchg(&IIIlll->state,IIllIIl)==IIIIlIl){



kref_get(&IIIlll->lllllIl);

IIlIlIl=IIIlll;break;}}spin_unlock_irqrestore(&lIlII->IlIIIl,flags);if(IIlIlIl){
llIlIlIIl(IIlIlIl);kref_put(&IIlIlIl->lllllIl,lllllIlI);}spin_lock_irqsave(&
lIlII->IlIIIl,flags);}while(IIlIlIl);spin_unlock_irqrestore(&lIlII->IlIIIl,flags
);IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x6b\x69\x6c\x6c\x5f\x61\x6c\x6c\x5f\x72\x65\x71\x75\x65\x73\x74\x73\x3a\x20\x2d\x2d" "\n"
);}
int IIIlIlII(struct usb_device*llIII,IIIII endpoint){int IIIIllI;struct 
usb_host_endpoint*ep;ep=(endpoint&(0x10ed+2962-0x1bff))?llIII->ep_in[endpoint&
(0x136d+4587-0x2549)]:llIII->ep_out[endpoint&(0xbe8+4001-0x1b7a)];if(!ep){IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x67\x65\x74\x5f\x65\x6e\x64\x70\x6f\x69\x6e\x74\x5f\x6d\x61\x78\x70\x61\x63\x6b\x65\x74\x3a\x20\x65\x6e\x64\x70\x6f\x69\x6e\x74\x20\x69\x73\x20\x4e\x55\x4c\x4c" "\n"
);return-ENODEV;}IIIIllI=le16_to_cpu(ep->desc.wMaxPacketSize);if((ep->desc.
bmAttributes&USB_ENDPOINT_XFERTYPE_MASK)!=USB_ENDPOINT_XFER_ISOC){IIIIllI=
IIIIllI&(0xf44+7509-0x249a);}else if(llIII->speed==USB_SPEED_HIGH)
{IIIIllI=(IIIIllI&(0x213b+83-0x198f))*((0x19d2+746-0x1cbb)+((IIIIllI>>
(0x659+4739-0x18d1))&(0x2a5+2897-0xdf3)));}
#if KERNEL_GT_EQ((0xc15+5824-0x22d3),(0x1840+1739-0x1f05),(0x243+564-0x458))
else if(llIII->speed==USB_SPEED_SUPER)
{
#if KERNEL_LT_EQ((0xe8c+5915-0x25a5),(0x163a+377-0x17ad),(0x1275+3905-0x2194))
IIIIllI=(IIIIllI&(0xf19+3443-0x148d))*(ep->ss_ep_comp?(((0x973+2636-0x13be)+ep->
ss_ep_comp->desc.bMaxBurst)*((0xc10+5316-0x20d3)+(ep->ss_ep_comp->desc.
bmAttributes&(0x135+7182-0x1d40)))):(0x463+6284-0x1cee));
#else
IIIIllI=(IIIIllI&(0x2637+303-0x1f67))*((0x6ba+4772-0x195d)+ep->ss_ep_comp.
bMaxBurst)*((0x3cd+6439-0x1cf3)+(ep->ss_ep_comp.bmAttributes&
(0x123f+4889-0x2555)));
#endif 
}
#endif 
else
{IIIIllI=IIIIllI&(0xb02+6147-0x1b06);}IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x67\x65\x74\x5f\x65\x6e\x64\x70\x6f\x69\x6e\x74\x5f\x6d\x61\x78\x70\x61\x63\x6b\x65\x74\x3a\x20\x65\x6e\x64\x70\x6f\x69\x6e\x74\x3d\x30\x78\x25\x30\x32\x78\x20\x6d\x61\x78\x70\x61\x63\x6b\x65\x74\x3d\x25\x64" "\n"
,endpoint,IIIIllI);return IIIIllI;}
#endif 

