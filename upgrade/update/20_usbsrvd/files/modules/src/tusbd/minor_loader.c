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
static ssize_t IIlIlIlll(void*,const char __user*,size_t);static ssize_t 
IlIlIlIll(void*,char __user*,size_t);static long lIlIlllII(void*,unsigned int,
unsigned long);
#ifdef CONFIG_COMPAT
static long lIllIIlII(void*,unsigned int,unsigned long);
#endif
static int IIllllllI(void*,int);static int lIlIlIlII(void*,int);static unsigned 
int IIIlllllI(void*,struct file*,poll_table*lllIll);static int llIlIIlII(struct 
IllllI*lIllI,const char __user*llIlI);static int IlIIIlIII(struct IllllI*lIllI,
const struct IIIIIIlIl __user*ioctl);static int IIlIIlIII(struct IllllI*lIllI,
struct llIIIIlII __user*ioctl);static int llIIlllll(struct IllllI*lIllI,const 
struct IIlIIllIl __user*ioctl);static int IIIIllIll(struct IllllI*lIllI,const 
struct IllIlllll __user*ioctl);struct IllIIlIl IlIIlIlII[]={{"\x74\x79\x70\x65",
"\x6c\x6f\x61\x64\x65\x72"},{NULL,NULL}};struct IllllI*lllIlllII(void){struct 
IllllI*lIllI;lIllI=IlIIllI(sizeof(*lIllI),GFP_KERNEL);if(lIllI){mutex_init(&
lIllI->mutex);lIllI->context=lIllI;lIllI->lIIIll=-(0x1e80+38-0x1ea5);lIllI->ops.
open=IIllllllI;lIllI->ops.release=lIlIlIlII;lIllI->ops.unlocked_ioctl=lIlIlllII;
#ifdef CONFIG_COMPAT
lIllI->ops.compat_ioctl=lIllIIlII;
#endif
lIllI->ops.read=IlIlIlIll;lIllI->ops.write=IIlIlIlll;lIllI->ops.poll=IIIlllllI;
lIllI->IlllIlI=IlIIlIlII;if(lllIIIIl(lIllI,(0xccf+2527-0x16ae),(0x1d5+883-0x548)
)<(0x1557+4164-0x259b)){lllIII(lIllI);lIllI=NULL;}}return lIllI;}void IlIlIlIl(
struct IllllI*lIllI){if(lIllI){llIlIIIl(lIllI);lllIII(lIllI);}}static ssize_t 
IlIlIlIll(void*context,char __user*llIlI,size_t IIlII){
ssize_t IlIlI=(0x14a7+847-0x17f6);IlllI(
"\x75\x73\x62\x64\x5f\x6c\x6f\x61\x64\x65\x72\x5f\x72\x65\x61\x64\x3a\x20\x62\x75\x66\x20\x69\x73\x20\x30\x78\x25\x70\x2c\x20\x72\x65\x71\x75\x65\x73\x74\x65\x64\x20\x25\x6c\x75\x20\x62\x79\x74\x65\x73" "\n"
,llIlI,(unsigned long)IIlII);return IlIlI;}static ssize_t IIlIlIlll(void*context
,const char __user*llIlI,size_t IIlII){
ssize_t IlIlI=IIlII;IlllI(
"\x75\x73\x62\x64\x5f\x6c\x6f\x61\x64\x65\x72\x5f\x77\x72\x69\x74\x65\x3a\x20\x62\x75\x66\x20\x69\x73\x20\x30\x78\x25\x70\x2c\x20\x72\x65\x71\x75\x65\x73\x74\x65\x64\x20\x25\x6c\x75\x20\x62\x79\x74\x65\x73" "\n"
,llIlI,(unsigned long)IIlII);return IlIlI;}static long IIIIIIIIl(void*context,
unsigned int llIIII,void __user*llIIlI){struct IllllI*lIllI=context;ssize_t 
IlIlI=(0x629+8198-0x262f);IlllI(
"\x75\x73\x62\x64\x5f\x6c\x6f\x61\x64\x65\x72\x5f\x64\x6f\x5f\x69\x6f\x63\x74\x6c\x3a\x20\x2b\x2b\x20\x63\x6d\x64\x3d\x25\x64\x20\x61\x72\x67\x3d\x30\x78\x25\x70" "\n"
,llIIII,llIIlI);switch(llIIII){case IIIIIIllI:IlIlI=llIlIIlII(lIllI,llIIlI);
break;case lIlIIIlIl:IlIlI=IlIIIlIII(lIllI,llIIlI);break;case lIIIIlIIl:IlIlI=
IIlIIlIII(lIllI,llIIlI);break;case IIIIlIlll:IlIlI=llIIlllll(lIllI,llIIlI);break
;case IlIIIIIll:IlIlI=IIIIllIll(lIllI,llIIlI);break;default:IlllI(
"\x75\x73\x62\x64\x5f\x6c\x6f\x61\x64\x65\x72\x5f\x64\x6f\x5f\x69\x6f\x63\x74\x6c\x3a\x20\x75\x6e\x6b\x6e\x6f\x77\x6e\x20\x69\x6f\x63\x74\x6c" "\n"
);IlIlI=-EINVAL;break;}IlllI(
"\x75\x73\x62\x64\x5f\x6c\x6f\x61\x64\x65\x72\x5f\x64\x6f\x5f\x69\x6f\x63\x74\x6c\x3a\x20\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x3d\x25\x6c\x75" "\n"
,(unsigned long)IlIlI);return IlIlI;}static long lIlIlllII(void*context,unsigned
 int llIIII,unsigned long llIIlI){IlllI(
"\x75\x73\x62\x64\x5f\x6c\x6f\x61\x64\x65\x72\x5f\x69\x6f\x63\x74\x6c" "\n");
return IIIIIIIIl(context,llIIII,(void __user*)llIIlI);}
#ifdef CONFIG_COMPAT
static long lIllIIlII(void*context,unsigned int llIIII,unsigned long llIIlI){
IlllI(
"\x75\x73\x62\x64\x5f\x6c\x6f\x61\x64\x65\x72\x5f\x63\x6f\x6d\x70\x61\x74\x5f\x69\x6f\x63\x74\x6c" "\n"
);return IIIIIIIIl(context,llIIII,compat_ptr(llIIlI));}
#endif


static int IIllllllI(void*context,int IlIllI){
IlllI(
"\x75\x73\x62\x64\x5f\x6c\x6f\x61\x64\x65\x72\x5f\x6f\x70\x65\x6e\x20\x25\x64" "\n"
,IlIllI);
return(0x804+917-0xb99);}

static int lIlIlIlII(void*context,int IlIllI){
IlllI(
"\x75\x73\x62\x64\x5f\x6c\x6f\x61\x64\x65\x72\x5f\x72\x65\x6c\x65\x61\x73\x65\x20\x25\x64" "\n"
,IlIllI);if(IlIllI==(0x1f5a+235-0x2045)){
IlIlIIIl();}return(0x3c7+6499-0x1d2a);}static unsigned int IIIlllllI(void*
context,struct file*lIIIlI,poll_table*lllIll){
return(POLLOUT|POLLWRNORM);}static int llIlIIlII(struct IllllI*lIllI,const char 
__user*llIlI){int IlIlI=(0x172c+905-0x1ab5);const char __user*IIlIllII;struct 
list_head llIIIlII;struct lIlllIlIl lIlIIIll;lllIl lIIlII;llIll("\x2b\x2b" "\n")
;INIT_LIST_HEAD(&llIIIlII);if(copy_from_user(&lIlIIIll,llIlI,sizeof(lIlIIIll)))
return-EFAULT;IIlIllII=llIlI+lIlIIIll.IIIlIl.lIIIIII;if(llIlI+sizeof(lIlIIIll)>
IIlIllII)return-EINVAL;llIlI+=sizeof(lIlIIIll);llIll(
"\x63\x6f\x75\x6e\x74\x3d\x25\x64" "\n",lIlIIIll.IllIIIlI);for(lIIlII=
(0x13f7+2034-0x1be9);lIIlII<lIlIIIll.IllIIIlI;lIIlII++){size_t llllIllll;size_t 
IlIIlIII;struct llIlIlII lllII;struct lIIllIl*lIIllII;if(llIlI+sizeof(lllII)>
IIlIllII){IlIlI=-EINVAL;break;}if(copy_from_user(&lllII,llIlI,sizeof(lllII))){
IlIlI=-EFAULT;break;}if((lllII.IlIIIlI&IlIllIIII)&&(lllII.IlIIIlI&lllIlIllI)){
IlIlI=-EINVAL;break;}if((lllII.IlIIIlI&llIllllII)&&lllII.IlIIIlIl<=
(0xb38+3141-0x177d)){
IlIlI=-EINVAL;break;}if((lllII.IlIIIlI&IIlIllIl)&&lllII.llIlllIl<=
(0x701+117-0x776)){
IlIlI=-EINVAL;break;}IlIIlIII=sizeof(struct llIlIlII)+lllII.IlIIIlIl+lllII.
llIlllIl;llllIllll=sizeof(struct lIIllIl)-sizeof(struct llIlIlII)+IlIIlIII;if(
llIlI+IlIIlIII>IIlIllII){IlIlI=-EINVAL;break;}lIIllII=IllllIl(llllIllll,
GFP_KERNEL);if(lIIllII==NULL){IlIlI=-ENOMEM;break;}if(copy_from_user(&lIIllII->
lllII,llIlI,IlIIlIII)){lllIII(lIIllII);IlIlI=-EFAULT;break;}if((lllII.IlIIIlI&
llIllllII)&&*((char*)(&lIIllII->lllII+(0x2593+198-0x2658))+lllII.IlIIIlIl-
(0x14e4+4414-0x2621))!='\0'){
lllIII(lIIllII);IlIlI=-EINVAL;break;}if((lllII.IlIIIlI&IIlIllIl)&&*((char*)(&
lIIllII->lllII+(0x616+4441-0x176e))+lllII.IlIIIlIl+lllII.llIlllIl-
(0x3bb+1601-0x9fb))!='\0'){
lllIII(lIIllII);IlIlI=-EINVAL;break;}llIll(
"\x56\x3d\x25\x30\x34\x58\x20\x50\x3d\x25\x30\x34\x58\x20\x52\x3d\x25\x30\x34\x58\x20\x43\x3d\x25\x30\x32\x58\x20\x53\x3d\x25\x30\x32\x58\x20\x50\x3d\x25\x30\x32\x58\x20\x49\x44\x3d\x25\x73\x20\x53\x4e\x3d\x25\x73\x20\x46\x3d\x25\x30\x38\x58" "\n"
,lIIllII->lllII.lIIIIlIl,lIIllII->lllII.IlllIlII,lIIllII->lllII.llIllIll,lIIllII
->lllII.llllIIIll,lIIllII->lllII.lIIllIIll,lIIllII->lllII.IIIllIlIl,lIIllII->
lllII.IlIIIlIl?(char*)(&lIIllII->lllII+(0x965+1020-0xd60)):"\x6e\x6f\x6e\x65",
lIIllII->lllII.llIlllIl?(char*)(&lIIllII->lllII+(0x4bf+3829-0x13b3))+lIIllII->
lllII.IlIIIlIl:"\x6e\x6f\x6e\x65",lIIllII->lllII.IlIIIlI);list_add_tail(&lIIllII
->entry,&llIIIlII);llIlI+=IlIIlIII;}
if(lIIlII!=lIlIIIll.IllIIIlI){IlIlI=-EINVAL;}
if(IlIlI>=(0x1614+1387-0x1b7f)){llIll("\x75\x70\x64\x61\x74\x65" "\n");llllIIIII
(&llIIIlII);}
if(IlIlI<(0xa51+3207-0x16d8)){while(!list_empty(&llIIIlII)){struct lIIllIl*
llIIIlI;llIIIlI=list_entry(llIIIlII.next,struct lIIllIl,entry);list_del(&llIIIlI
->entry);lllIII(llIIIlI);}}llIll(
"\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x3d\x25\x64" "\n",IlIlI);return IlIlI;}
static int IlIIIlIII(struct IllllI*lIllI,const struct IIIIIIlIl __user*ioctl){
int IlIlI;lllIl lllllI;llIll("\x2b\x2b" "\n");do
{if(get_user(lllllI,&ioctl->IIIlIl.lIIIIII)<(0x2d9+7937-0x21da)){IlIlI=-EFAULT;
break;}if(lllllI!=sizeof(*ioctl)){IlIlI=-EINVAL;break;}IlIlIIIl();IlIlI=
(0x436+3498-0x11e0);}while((0xba2+5495-0x2119));llIll(
"\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x3d\x25\x64" "\n",IlIlI);return IlIlI;}
static int IIlIIlIII(struct IllllI*lIllI,struct llIIIIlII __user*ioctl){int 
IlIlI=-ENODEV;lllIl lllllI;llIll("\x2b\x2b" "\n");do
{IIIII lIIIllIIl;char llIIll[sizeof(ioctl->llIIll)+(0xa86+1803-0x1190)];struct 
usb_device*IlIIl;if(get_user(lllllI,&ioctl->IIIlIl.lIIIIII)<(0x3cc+4111-0x13db))
{IlIlI=-EFAULT;break;}if(lllllI!=sizeof(*ioctl)){IlIlI=-EINVAL;break;}if(
get_user(lIIIllIIl,&ioctl->lIIIllIIl)<(0x2127+1065-0x2550)){IlIlI=-EFAULT;break;
}llIIll[sizeof(llIIll)-(0x57a+6844-0x2035)]='\0';if(copy_from_user(llIIll,&ioctl
->llIIll,sizeof(ioctl->llIIll))){IlIlI=-EFAULT;break;}IlIlI=-ENODEV;IlIIl=
IIlIIIII(llIIll);if(IlIIl){usb_lock_device(IlIIl);
#if KERNEL_LT_EQ((0x6ca+127-0x747),(0x2bf+5978-0x1a13),(0xe35+2526-0x17fe))
down_write(&IlIIl->dev.bus->subsys.rwsem);
#endif
if(llllllll(IlIIl)){IlIlI=IIIlIllI(IlIIl);}else{llIll(
"\x64\x65\x76\x69\x63\x65\x20\x25\x73\x20\x6e\x6f\x74\x20\x73\x68\x61\x72\x65\x64" "\n"
,llIIll);}
#if KERNEL_LT_EQ((0xb22+2886-0x1666),(0xa43+2221-0x12ea),(0x441+638-0x6aa))
up_write(&IlIIl->dev.bus->subsys.rwsem);
#endif
usb_unlock_device(IlIIl);usb_put_dev(IlIIl);}else{llIll(
"\x64\x65\x76\x69\x63\x65\x20\x25\x73\x20\x6e\x6f\x74\x20\x66\x6f\x75\x6e\x64" "\n"
,llIIll);}}while((0x1219+1858-0x195b));llIll(
"\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x3d\x25\x64" "\n",IlIlI);return IlIlI;}
static int llIIlllll(struct IllllI*lIllI,const struct IIlIIllIl __user*ioctl){
int IlIlI=-ENODEV;lllIl lllllI;llIll("\x2b\x2b" "\n");do
{char llIIll[sizeof(ioctl->llIIll)+(0xc5b+3996-0x1bf6)];IIIII IlllIIll;struct 
usb_device*IlIIl;if(get_user(lllllI,&ioctl->IIIlIl.lIIIIII)<(0x1031+1985-0x17f2)
){IlIlI=-EFAULT;break;}if(lllllI!=sizeof(*ioctl)){IlIlI=-EINVAL;break;}if(
get_user(IlllIIll,&ioctl->IlllIIll)<(0xb2+3491-0xe55)){IlIlI=-EFAULT;break;}
llIIll[sizeof(llIIll)-(0x1839+2060-0x2044)]='\0';if(copy_from_user(llIIll,&ioctl
->llIIll,sizeof(ioctl->llIIll))){IlIlI=-EFAULT;break;}IlIlI=-ENODEV;IlIIl=
IIlIIIII(llIIll);if(IlIIl){usb_lock_device(IlIIl);
#if KERNEL_LT_EQ((0x3c+6325-0x18ef),(0x253+6461-0x1b8a),(0x103+5476-0x1652))
down_write(&IlIIl->dev.bus->subsys.rwsem);
#endif
llllIIlI(IlIIl,IlllIIll);IlIlI=(0x253+1264-0x743);
#if KERNEL_LT_EQ((0xe86+4527-0x2033),(0x12b4+4639-0x24cd),(0x1d+9371-0x24a3))
up_write(&IlIIl->dev.bus->subsys.rwsem);
#endif
usb_unlock_device(IlIIl);usb_put_dev(IlIIl);}else{llIll(
"\x64\x65\x76\x69\x63\x65\x20\x25\x73\x20\x6e\x6f\x74\x20\x66\x6f\x75\x6e\x64" "\n"
,llIIll);}}while((0x67+384-0x1e7));llIll(
"\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x3d\x25\x64" "\n",IlIlI);return IlIlI;}
static int IIIIllIll(struct IllllI*lIllI,const struct IllIlllll __user*ioctl){
int IlIlI=-ENODEV;lllIl lllllI;llIll("\x2b\x2b" "\n");do
{char llIIll[sizeof(ioctl->llIIll)+(0xf6f+4725-0x21e3)];struct usb_device*IlIIl;
if(get_user(lllllI,&ioctl->IIIlIl.lIIIIII)<(0x17c+3265-0xe3d)){IlIlI=-EFAULT;
break;}if(lllllI!=sizeof(*ioctl)){IlIlI=-EINVAL;break;}llIIll[sizeof(llIIll)-
(0x25+3214-0xcb2)]='\0';if(copy_from_user(llIIll,&ioctl->llIIll,sizeof(ioctl->
llIIll))){IlIlI=-EFAULT;break;}IlIlI=-ENODEV;IlIIl=IIlIIIII(llIIll);if(IlIIl){
usb_lock_device(IlIIl);
#if KERNEL_LT_EQ((0x426+5403-0x193f),(0xd73+4493-0x1efa),(0x1dfc+1606-0x242d))
down_write(&IlIIl->dev.bus->subsys.rwsem);
#endif
if(llllllll(IlIIl)){IlIlI=IIIlIllI(IlIIl);}else{llllIIlI(IlIIl,(0x2ef+408-0x486)
);IlIlI=(0x913+5912-0x202b);}
#if KERNEL_LT_EQ((0x1ec6+1566-0x24e2),(0x408+3340-0x110e),(0xc73+710-0xf24))
up_write(&IlIIl->dev.bus->subsys.rwsem);
#endif
usb_unlock_device(IlIIl);usb_put_dev(IlIIl);}else{llIll(
"\x64\x65\x76\x69\x63\x65\x20\x25\x73\x20\x6e\x6f\x74\x20\x66\x6f\x75\x6e\x64" "\n"
,llIIll);}}while((0xf32+988-0x130e));llIll(
"\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x3d\x25\x64" "\n",IlIlI);return IlIlI;}
#endif 

