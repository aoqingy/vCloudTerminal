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

#ifdef _USBD_ENABLE_VHCI_
#include "usbd.h"
ssize_t llllIIIlI(void*,const char __user*,size_t);ssize_t lIIIIllII(void*,char 
__user*,size_t);long IIIllllll(void*,unsigned int,unsigned long);
#ifdef CONFIG_COMPAT
long llIlIllll(void*,unsigned int,unsigned long);
#endif
int lIlllllII(void*,int);int lIllllIlI(void*,int);unsigned int lIIlIlllI(void*,
struct file*,poll_table*lllIll);int lIIlIllll(struct IllllI*lIllI,struct 
llIlIlIlI __user*ioctl);int IIlIlIlII(struct IllllI*lIllI,struct IIllllIII 
__user*ioctl);int llllIIlII(struct IllllI*lIllI,struct llIIIIIll __user*ioctl);
static struct IllIIlIl IlIIIllIl[]={{"\x74\x79\x70\x65","\x76\x62\x75\x73"},{
NULL,NULL}};struct IllllI*llIlIIllI(void){struct IllllI*lIllI;lIllI=IlIIllI(
sizeof(*lIllI),GFP_KERNEL);if(lIllI){mutex_init(&lIllI->mutex);lIllI->context=
lIllI;lIllI->lIIIll=-(0x605+5785-0x1c9d);lIllI->ops.open=lIlllllII;lIllI->ops.
release=lIllllIlI;lIllI->ops.unlocked_ioctl=IIIllllll;
#ifdef CONFIG_COMPAT
lIllI->ops.compat_ioctl=llIlIllll;
#endif
lIllI->ops.read=lIIIIllII;lIllI->ops.write=llllIIIlI;lIllI->ops.poll=lIIlIlllI;
lIllI->IlllIlI=IlIIIllIl;if(lllIIIIl(lIllI,(0x191+4579-0x1373),
(0x1a69+2787-0x254b))<(0x2265+1065-0x268e)){lllIII(lIllI);lIllI=NULL;}}return 
lIllI;}void lIllIIII(struct IllllI*lIllI){if(lIllI){llIlIIIl(lIllI);lllIII(lIllI
);}}ssize_t lIIIIllII(void*context,char __user*llIlI,size_t IIlII){
ssize_t IlIlI=(0x6ed+2882-0x122f);IlllI(
"\x75\x73\x62\x64\x5f\x76\x62\x75\x73\x5f\x72\x65\x61\x64\x3a\x20\x62\x75\x66\x20\x69\x73\x20\x30\x78\x25\x70\x2c\x20\x72\x65\x71\x75\x65\x73\x74\x65\x64\x20\x25\x6c\x75\x20\x62\x79\x74\x65\x73" "\n"
,llIlI,(unsigned long)IIlII);return IlIlI;}ssize_t llllIIIlI(void*context,const 
char __user*llIlI,size_t IIlII){
ssize_t IlIlI=IIlII;IlllI(
"\x75\x73\x62\x64\x5f\x76\x62\x75\x73\x5f\x77\x72\x69\x74\x65\x3a\x20\x62\x75\x66\x20\x69\x73\x20\x30\x78\x25\x70\x2c\x20\x72\x65\x71\x75\x65\x73\x74\x65\x64\x20\x25\x6c\x75\x20\x62\x79\x74\x65\x73" "\n"
,llIlI,(unsigned long)IIlII);return IlIlI;}long IllIlIIIl(void*context,unsigned 
int llIIII,void __user*llIIlI){struct IllllI*lIllI=context;ssize_t IlIlI=
(0xa4d+888-0xdc5);IlllI(
"\x75\x73\x62\x64\x5f\x76\x62\x75\x73\x5f\x64\x6f\x5f\x69\x6f\x63\x74\x6c\x3a\x20\x2b\x2b\x20\x63\x6d\x64\x3d\x25\x64\x20\x61\x72\x67\x3d\x30\x78\x25\x70" "\n"
,llIIII,llIIlI);switch(llIIII){case lIlIllIIl:IlIlI=lIIlIllll(lIllI,llIIlI);
break;case IIIllIIIl:IlIlI=IIlIlIlII(lIllI,llIIlI);break;case llllllIlI:IlIlI=
llllIIlII(lIllI,llIIlI);break;default:IlllI(
"\x75\x73\x62\x64\x5f\x76\x62\x75\x73\x5f\x64\x6f\x5f\x69\x6f\x63\x74\x6c\x3a\x20\x75\x6e\x6b\x6e\x6f\x77\x6e\x20\x69\x6f\x63\x74\x6c" "\n"
);IlIlI=-EINVAL;break;}IlllI(
"\x75\x73\x62\x64\x5f\x76\x62\x75\x73\x5f\x64\x6f\x5f\x69\x6f\x63\x74\x6c\x3a\x20\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x3d\x25\x6c\x75" "\n"
,(unsigned long)IlIlI);return IlIlI;}long IIIllllll(void*context,unsigned int 
llIIII,unsigned long llIIlI){IlllI(
"\x75\x73\x62\x64\x5f\x76\x62\x75\x73\x5f\x69\x6f\x63\x74\x6c" "\n");return 
IllIlIIIl(context,llIIII,(void __user*)llIIlI);}
#ifdef CONFIG_COMPAT
long llIlIllll(void*context,unsigned int llIIII,unsigned long llIIlI){IlllI(
"\x75\x73\x62\x64\x5f\x76\x62\x75\x73\x5f\x63\x6f\x6d\x70\x61\x74\x5f\x69\x6f\x63\x74\x6c" "\n"
);return IllIlIIIl(context,llIIII,compat_ptr(llIIlI));}
#endif


int lIlllllII(void*context,int IlIllI){
IlllI(
"\x75\x73\x62\x64\x5f\x76\x62\x75\x73\x5f\x6f\x70\x65\x6e\x20\x25\x64" "\n",
IlIllI);return(0x17fa+167-0x18a1);}

int lIllllIlI(void*context,int IlIllI){
IlllI(
"\x75\x73\x62\x64\x5f\x76\x62\x75\x73\x5f\x72\x65\x6c\x65\x61\x73\x65\x20\x25\x64" "\n"
,IlIllI);if(IlIllI==(0x21e0+580-0x2424)){
IllllIlII();}return(0x2cc+4087-0x12c3);}unsigned int lIIlIlllI(void*context,
struct file*lIIIlI,poll_table*lllIll){
return(POLLOUT|POLLWRNORM);}int lIIlIllll(struct IllllI*lIllI,struct llIlIlIlI 
__user*ioctl){int IlIlI=(0xa53+2502-0x1419);struct lIlIl*lllll=NULL;lllIl lllllI
;llIIIl vid;llIIIl IllIIII;llIIIl IlIllIl;llIIIl llllIIIIl;IIIII speed;IlllI(
"\x75\x73\x62\x64\x5f\x76\x62\x75\x73\x5f\x69\x6f\x63\x74\x6c\x5f\x70\x6c\x75\x67\x5f\x64\x65\x76\x69\x63\x65\x3a\x20\x2b\x2b" "\n"
);do
{if(get_user(lllllI,&ioctl->IIIlIl.lIIIIII)<(0x1050+1763-0x1733)){IlIlI=-EFAULT;
break;}if(lllllI!=sizeof(struct llIlIlIlI)){IlIlI=-EINVAL;break;}if(get_user(vid
,&ioctl->lIIIIlIl)<(0x197+5638-0x179d)){IlIlI=-EFAULT;break;}if(get_user(IllIIII
,&ioctl->IlllIlII)<(0xcec+661-0xf81)){IlIlI=-EFAULT;break;}if(get_user(IlIllIl,&
ioctl->llIllIll)<(0x1b16+2131-0x2369)){IlIlI=-EFAULT;break;}if(get_user(
llllIIIIl,&ioctl->IIIlIlIII)<(0xca4+3731-0x1b37)){IlIlI=-EFAULT;break;}if(
get_user(speed,&ioctl->lIIllIlII)<(0x390+3332-0x1094)){IlIlI=-EFAULT;break;}
switch(speed){case lIlIIlIII:speed=USB_SPEED_LOW;break;case llIIllIIl:speed=
USB_SPEED_FULL;break;case lIlIlIllI:speed=USB_SPEED_HIGH;break;case lIIIIIlIl:
#if KERNEL_GT_EQ((0xadc+967-0xea1),(0x138f+4645-0x25ae),(0x14a6+1109-0x18d4)) ||\
 RHEL_RELEASE_GT_EQ((0xbbf+6070-0x236f),(0x1f23+1367-0x2477)) 
speed=USB_SPEED_SUPER;
#else
IIIIll(
"\x55\x53\x42\x20\x33\x2e\x30\x20\x69\x73\x20\x6e\x6f\x74\x20\x73\x75\x70\x70\x6f\x72\x74\x65\x64\x20\x6f\x6e\x20\x74\x68\x69\x73\x20\x6b\x65\x72\x6e\x65\x6c\x2c\x20\x75\x73\x65\x20\x6b\x65\x72\x6e\x65\x6c\x20\x32\x2e\x36\x2e\x33\x39\x20\x6f\x72\x20\x6e\x65\x77\x65\x72" "\n"
);IlIlI=-EINVAL;
#endif
break;default:IlllI(
"\x75\x73\x62\x64\x5f\x76\x62\x75\x73\x5f\x69\x6f\x63\x74\x6c\x5f\x70\x6c\x75\x67\x5f\x64\x65\x76\x69\x63\x65\x3a\x20\x69\x6e\x76\x61\x6c\x69\x64\x20\x64\x65\x76\x69\x63\x65\x20\x73\x70\x65\x65\x64" "\n"
);IlIlI=-EINVAL;break;}if(IlIlI<(0x1d39+657-0x1fca))break;lllll=IlIlIIIIl(vid,
IllIIII,IlIllIl,speed);if(lllll==(0x2c5+9106-0x2657)){IlIlI=-ENOMEM;break;}IlIlI
=lllIllIIl(lllll);if(IlIlI<(0xa16+884-0xd8a)){IlllllII(lllll);break;}llIll(
"\x64\x65\x76\x69\x63\x65\x69\x64\x3d\x25\x64" "\n",IlIIIIIl(lllll->lIllI));if(
put_user((lllIl)IlIIIIIl(lllll->lIllI),&ioctl->llIIlIIlI)<(0x442+3759-0x12f1)){
IlllllII(lllll);IlIlI=-EFAULT;break;}}while((0xa4+5934-0x17d2));if(IlIlI<
(0xa89+1890-0x11eb)){if(lllll)IlllllII(lllll);}IlllI(
"\x75\x73\x62\x64\x5f\x76\x62\x75\x73\x5f\x69\x6f\x63\x74\x6c\x5f\x70\x6c\x75\x67\x5f\x64\x65\x76\x69\x63\x65\x3a\x20\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x3d\x25\x64" "\n"
,IlIlI);return IlIlI;}int IIlIlIlII(struct IllllI*lIllI,struct IIllllIII __user*
ioctl){int IlIlI=(0xe96+437-0x104b);struct lIlIl*lllll;lllIl lllllI;lllIl 
lllIIlIl;IlllI(
"\x75\x73\x62\x64\x5f\x76\x62\x75\x73\x5f\x69\x6f\x63\x74\x6c\x5f\x75\x6e\x70\x6c\x75\x67\x5f\x64\x65\x76\x69\x63\x65\x3a\x20\x2b\x2b" "\n"
);do
{if(get_user(lllllI,&ioctl->IIIlIl.lIIIIII)<(0xb32+5836-0x21fe)){IlIlI=-EFAULT;
break;}if(lllllI!=sizeof(struct IIllllIII)){IlIlI=-EINVAL;break;}if(get_user(
lllIIlIl,&ioctl->llIIlIIlI)<(0x190a+1475-0x1ecd)){IlIlI=-EFAULT;break;}lllll=
IIlllIlll(lllIIlIl);if(lllll==NULL){IlllI(
"\x75\x73\x62\x64\x5f\x76\x62\x75\x73\x5f\x69\x6f\x63\x74\x6c\x5f\x75\x6e\x70\x6c\x75\x67\x5f\x64\x65\x76\x69\x63\x65\x3a\x20\x64\x65\x76\x69\x63\x65\x20\x25\x75\x20\x69\x73\x20\x6e\x6f\x74\x20\x66\x6f\x75\x6e\x64" "\n"
,lllIIlIl);IlIlI=-ENODEV;break;}

IlllllII(lllll);
lllllIll(lllll);}while((0xfdf+996-0x13c3));IlllI(
"\x75\x73\x62\x64\x5f\x76\x62\x75\x73\x5f\x69\x6f\x63\x74\x6c\x5f\x75\x6e\x70\x6c\x75\x67\x5f\x64\x65\x76\x69\x63\x65\x3a\x20\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x3d\x25\x64" "\n"
,IlIlI);return IlIlI;}int llllIIlII(struct IllllI*lIllI,struct llIIIIIll __user*
ioctl){int IlIlI=(0x1b69+163-0x1c0c);lllIl lllllI;IlllI(
"\x75\x73\x62\x64\x5f\x76\x62\x75\x73\x5f\x69\x6f\x63\x74\x6c\x5f\x75\x73\x62\x33\x5f\x73\x75\x70\x70\x6f\x72\x74\x3a\x20\x2b\x2b" "\n"
);do
{if(get_user(lllllI,&ioctl->IIIlIl.lIIIIII)<(0x3b8+8341-0x244d)){IlIlI=-EFAULT;
break;}if(lllllI!=sizeof(struct llIIIIIll)){IlIlI=-EINVAL;break;}
#if KERNEL_GT_EQ((0xf98+1432-0x152e),(0x5c3+7309-0x224a),(0x173b+315-0x184f)) ||\
 RHEL_RELEASE_GT_EQ((0x61d+2477-0xfc4),(0x243f+458-0x2606))
IlIlI=(0x16d2+1800-0x1dda);
#else
IlIlI=-EPIPE;
#endif
}while((0x7fc+1489-0xdcd));IlllI(
"\x75\x73\x62\x64\x5f\x76\x62\x75\x73\x5f\x69\x6f\x63\x74\x6c\x5f\x75\x73\x62\x33\x5f\x73\x75\x70\x70\x6f\x72\x74\x3a\x20\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x3d\x25\x64" "\n"
,IlIlI);return IlIlI;}
#endif 

