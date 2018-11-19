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

#include "usbd.h"
#include <linux/mm.h>
#include <linux/highmem.h>
#include <asm/page.h>
int IIIIlIllI(const lIIll IIlIl,size_t*lllllI,size_t*llIlIl,IIIII*flags,IIIII*
endpoint){switch(IIlIl->IIIlI.IIlIlI){case lllllIIl:*lllllI=sizeof(IIlIl->IllIII
);*flags=IIIIIl;*llIlIl=IIlIl->IllIII.IlIll;*endpoint=(0xcad+4709-0x1e92);break;
case lIIlllll:*lllllI=sizeof(IIlIl->IllIII);*flags=(0x1285+5081-0x265e);*llIlIl=
IIlIl->IllIII.IlIll;*endpoint=(0x145f+2554-0x1e59);break;case IIllllII:*lllllI=
sizeof(IIlIl->IIIIlI)-sizeof(IIlIl->IIIIlI.lllIlII[(0x1143+2574-0x1b51)])+IIlIl
->IIIIlI.IllllIIl*sizeof(IIlIl->IIIIlI.lllIlII[(0x11e4+4009-0x218d)]);*flags=
(0xa5c+5839-0x212b);*llIlIl=(0xcc+2781-0xba9);*endpoint=(0x255+654-0x4e3);break;
case lIIlIIII:*lllllI=sizeof(IIlIl->IlllIIl);*flags=(0xd42+4901-0x2067);*llIlIl=
(0x64f+687-0x8fe);*endpoint=(0x266+4004-0x120a);break;case llIlIIlI:*lllllI=
sizeof(IIlIl->IIIllI);*flags=IIlIl->IIIllI.Flags;*llIlIl=IIlIl->IIIllI.IlIll;*
endpoint=IIlIl->IIIllI.Endpoint|((*flags&IIIIIl)?(0x121c+4622-0x23aa):
(0x2a+4006-0xfd0));break;case lllIlIlI:*lllllI=sizeof(IIlIl->lIllIl);*llIlIl=
IIlIl->lIllIl.IlIll;*flags=IIlIl->lIllIl.Flags;*endpoint=IIlIl->lIllIl.Endpoint|
((*flags&IIIIIl)?(0x4c0+739-0x723):(0xa82+2330-0x139c));break;case lIIlIIIl:*
lllllI=lllIIIlI(IIlIl);*flags=IIlIl->llIIl.Flags;*llIlIl=IIlIl->llIIl.IlIll;*
endpoint=IIlIl->llIIl.Endpoint|((*flags&IIIIIl)?(0x16fc+2204-0x1f18):
(0x14a+4281-0x1203));break;case lIIlllII:*lllllI=sizeof(IIlIl->IIIIII);*flags=
IIlIl->IIIIII.Flags;*llIlIl=IIlIl->IIIIII.IlIll;*endpoint=IIlIl->IIIIII.Endpoint
|((*flags&IIIIIl)?(0x1878+1466-0x1db2):(0x14bb+2660-0x1f1f));break;case lllIllll
:*lllllI=sizeof(IIlIl->llIlIlI);*flags=IIlIl->llIlIlI.Flags;*llIlIl=
(0x112a+5604-0x270e);*endpoint=IIlIl->llIlIlI.Endpoint|((*flags&IIIIIl)?
(0xe4+927-0x403):(0x1112+3830-0x2008));break;case llIlIlll:*lllllI=sizeof(IIlIl
->IIlIlIII);*flags=(0x975+6036-0x2109);*llIlIl=(0x578+238-0x666);*endpoint=
(0x29f+4642-0x13c2);break;case IIlIIlIll:return-EINVAL;case IIIIllIl:*lllllI=
sizeof(IIlIl->IlIllIll);*flags=(0x113a+4004-0x20de);*llIlIl=(0x12e8+3272-0x1fb0)
;*endpoint=(0x197+6688-0x1ab8);break;case IllIIIll:*lllllI=sizeof(IIlIl->
IIIlllIlI);*flags=(0x13b6+3187-0x2029);*llIlIl=(0x216+4060-0x11f2);*endpoint=
(0x486+53-0x3bc);break;case lIIIIlII:*lllllI=sizeof(IIlIl->lllIIIIII);*flags=
(0xbac+1987-0x136f);*llIlIl=(0x1a5c+606-0x1cba);*endpoint=(0x313+2428-0xb90);
break;case IIlIlIlI:*lllllI=sizeof(IIlIl->lIIIllll);*flags=IIlIl->lIIIllll.Flags
;*llIlIl=(0x2fd+410-0x497);*endpoint=IIlIl->lIIIllll.Endpoint|((*flags&IIIIIl)?
(0x275+65-0x236):(0x9da+3944-0x1942));break;default:return-EINVAL;}return
(0xc52+3717-0x1ad7);}
struct usb_host_config*IIIIIllIl(struct usb_device*IlIIl){if(IlIIl->actconfig)
return IlIIl->actconfig;if(IlIIl->descriptor.bNumConfigurations&&IlIIl->config)
return&IlIIl->config[(0x530+3959-0x14a7)];return NULL;}
struct usb_host_interface*IlIllllll(struct usb_host_config*config){if(config->
desc.bNumInterfaces>(0xe6b+269-0xf78)){if(config->interface[(0x38+807-0x35f)]){
if(config->interface[(0xfa8+3059-0x1b9b)]->cur_altsetting)return config->
interface[(0x1e91+666-0x212b)]->cur_altsetting;if(config->interface[
(0x1149+3145-0x1d92)]->num_altsetting&&config->interface[(0x17ba+3337-0x24c3)]->
altsetting)return&config->interface[(0x504+8553-0x266d)]->altsetting[
(0x676+1110-0xacc)];}if(config->intf_cache[(0x222b+1192-0x26d3)]&&config->
intf_cache[(0xa76+6610-0x2448)]->num_altsetting)return&config->intf_cache[
(0x1a22+1995-0x21ed)]->altsetting[(0x16bf+1618-0x1d11)];}return NULL;}
void lllIIIllI(struct usb_device*IlIIl,u8*lIlIlIl,u8*llIllll,u8*IllIlII){struct 
usb_host_config*config;struct usb_host_interface*IIllI;config=IIIIIllIl(IlIIl);
if(config==NULL){if(lIlIlIl)*lIlIlIl=(0x2306+134-0x238c);if(llIllll)*llIllll=
(0x6b6+2946-0x1238);if(IllIlII)*IllIlII=(0x1708+2962-0x229a);return;}IIllI=
IlIllllll(config);

















if((config->desc.bNumInterfaces>(0x1288+2112-0x1ac7))&&((IlIIl->descriptor.
bDeviceClass==(0xf81+5082-0x235b))||
((IlIIl->descriptor.bDeviceClass==(0xe73+5752-0x23fc))&&
(IlIIl->descriptor.bDeviceSubClass==(0x1e5d+895-0x21da))&&(IlIIl->descriptor.
bDeviceProtocol==(0xf37+1688-0x15ce))))){

if(lIlIlIl)*lIlIlIl=(0x1727+1423-0x1cb6);if(llIllll)*llIllll=(0x14ed+654-0x177b)
;if(IllIlII)*IllIlII=(0x952+7130-0x252c);}else if(config->desc.bNumInterfaces>
(0x998+5780-0x202c)&&IIllI){
if(lIlIlIl)*lIlIlIl=IIllI->desc.bInterfaceClass;if(llIllll)*llIllll=IIllI->desc.
bInterfaceSubClass;if(IllIlII)*IllIlII=IIllI->desc.bInterfaceProtocol;}else
{
if(lIlIlIl)*lIlIlIl=IlIIl->descriptor.bDeviceClass;if(llIllll)*llIllll=IlIIl->
descriptor.bDeviceSubClass;if(IllIlII)*IllIlII=IlIIl->descriptor.bDeviceProtocol
;}}
#ifdef _USBD_ENABLE_STUB_
#ifdef _USBD_DEBUG_MEMORY_
extern atomic_t lIllllll;extern atomic_t lIlIllIII;extern atomic_t lIllIIlIl;
#endif 

size_t IIlIlllll(struct IlIII*IIIll,void __user*llIlI,size_t IIlII){size_t IlIlI
=(0x5e1+4194-0x1643);IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x65\x78\x74\x72\x61\x63\x74\x5f\x72\x65\x71\x75\x65\x73\x74\x3a\x20\x2b\x2b" "\n"
);do{lIIll IIlIl=(lIIll)(IIIll+(0x41d+3655-0x1263));IIIII flags,endpoint;size_t 
IIIllll,llIlIl,lIIlII;if(IIIIlIllI(IIlIl,&IIIllll,&llIlIl,&flags,&endpoint)<
(0x9c0+7488-0x2700)){IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x65\x78\x74\x72\x61\x63\x74\x5f\x72\x65\x71\x75\x65\x73\x74\x3a\x20\x69\x6e\x76\x61\x6c\x69\x64\x20\x64\x61\x74\x61" "\n"
);break;}if(!access_ok(VERIFY_WRITE,llIlI,IIlIl->IIIlI.IIIlII)){IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x65\x78\x74\x72\x61\x63\x74\x5f\x72\x65\x71\x75\x65\x73\x74\x3a\x20\x6d\x65\x6d\x6f\x72\x79\x20\x61\x63\x63\x65\x73\x73\x20\x63\x68\x65\x63\x6b\x20\x66\x61\x69\x6c\x65\x64" "\n"
);break;}lIIlII=min(IIIllll,IIlII);if(__copy_to_user(llIlI,IIlIl,lIIlII)!=
(0x152c+1860-0x1c70)){IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x65\x78\x74\x72\x61\x63\x74\x5f\x72\x65\x71\x75\x65\x73\x74\x3a\x20\x63\x61\x6e\x6e\x6f\x74\x20\x63\x6f\x70\x79\x20\x74\x6f\x20\x75\x73\x65\x72\x20\x62\x75\x66\x66\x65\x72\x28\x31\x29" "\n"
);break;}IlIlI+=lIIlII;IIlII-=lIIlII;llIlI+=lIIlII;lIIlII=min(llIlIl,IIlII);
if((flags&IIIIIl)&&lIIlII){if(IIIll->lIllll==llIIlIl){


if(__copy_to_user(llIlI,IIIll->IlIlII.IIIIl,lIIlII)){IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x65\x78\x74\x72\x61\x63\x74\x5f\x72\x65\x71\x75\x65\x73\x74\x3a\x20\x63\x61\x6e\x6e\x6f\x74\x20\x63\x6f\x70\x79\x20\x74\x6f\x20\x75\x73\x65\x72\x20\x62\x75\x66\x66\x65\x72\x28\x32\x29" "\n"
);IlIlI=(0xc31+4868-0x1f35);break;}}else if(IIIll->lIllll==lIlllll){


if(IIIlIllIl(&IIIll->IIllIl.lIllIIl,llIlI,lIIlII)<lIIlII){IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x65\x78\x74\x72\x61\x63\x74\x5f\x72\x65\x71\x75\x65\x73\x74\x3a\x20\x63\x61\x6e\x6e\x6f\x74\x20\x63\x6f\x70\x79\x20\x74\x6f\x20\x75\x73\x65\x72\x20\x62\x75\x66\x66\x65\x72\x28\x33\x29" "\n"
);IlIlI=(0x109c+3900-0x1fd8);break;}}
#if KERNEL_GT_EQ((0x1048+5704-0x268e),(0x785+2194-0x1011),(0x865+3886-0x1774))
else if(IIIll->lIllll==lIlIllI){


if(lIIIIIIIl(&IIIll->lIllIll.sg,llIlI,lIIlII)<lIIlII){IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x65\x78\x74\x72\x61\x63\x74\x5f\x72\x65\x71\x75\x65\x73\x74\x3a\x20\x63\x61\x6e\x6e\x6f\x74\x20\x63\x6f\x70\x79\x20\x74\x6f\x20\x75\x73\x65\x72\x20\x62\x75\x66\x66\x65\x72\x28\x34\x29" "\n"
);IlIlI=(0x24db+476-0x26b7);break;}}
#endif
else{IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x65\x78\x74\x72\x61\x63\x74\x5f\x72\x65\x71\x75\x65\x73\x74\x3a\x20\x69\x6e\x74\x65\x72\x6e\x61\x6c\x20\x65\x72\x72\x6f\x72\x21" "\n"
);IlIlI=(0x3b7+7338-0x2061);break;}IlIlI+=lIIlII;}}while((0x16a9+441-0x1862));
IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x65\x78\x74\x72\x61\x63\x74\x5f\x72\x65\x71\x75\x65\x73\x74\x3a\x20\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x3d\x25\x6c\x75" "\n"
,(unsigned long)IlIlI);return IlIlI;}struct IlIII*IlIlIllll(struct IllIl*lIlII,
const void __user*llIlI,size_t IIlII){lIIll IlIlIlll;IIllIIIlI lllIlIl;struct 
IlIII*IIIll=NULL;size_t IIIllll,llIlIl,lllllIII;IIIII flags,endpoint;int IlIlI=-
(0xa02+1907-0x1174);int lIllll;do{if(copy_from_user(&lllIlIl,llIlI,min(sizeof(
lllIlIl),IIlII))!=(0x2c7+1053-0x6e4)){IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x63\x72\x65\x61\x74\x65\x5f\x72\x65\x71\x75\x65\x73\x74\x3a\x20\x63\x61\x6e\x6e\x6f\x74\x20\x63\x6f\x70\x79\x20\x66\x72\x6f\x6d\x20\x75\x73\x65\x72\x20\x62\x75\x66\x66\x65\x72\x20\x28\x32\x29" "\n"
);break;}if(!access_ok(VERIFY_READ,llIlI,lllIlIl.IIIlI.IIIlII)){IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x63\x72\x65\x61\x74\x65\x5f\x72\x65\x71\x75\x65\x73\x74\x3a\x20\x6d\x65\x6d\x6f\x72\x79\x20\x61\x63\x63\x65\x73\x73\x20\x63\x68\x65\x63\x6b\x20\x66\x61\x69\x6c\x65\x64" "\n"
);IlIlI=-EFAULT;break;}if(IIIIlIllI(&lllIlIl,&IIIllll,&llIlIl,&flags,&endpoint)<
(0x9f1+6185-0x221a)){IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x63\x72\x65\x61\x74\x65\x5f\x72\x65\x71\x75\x65\x73\x74\x3a\x20\x69\x6e\x76\x61\x6c\x69\x64\x20\x64\x61\x74\x61" "\n"
);IlIlI=-EINVAL;break;}


if((llIlIl==(0xd1d+3326-0x1a1b))||((sizeof(struct IlIII)+IIIllll+llIlIl+
(0xe2a+1217-0x12ab))<=IIIlIlll)){
lIllll=llIIlIl;}else if(lllIlIl.IIIlI.IIlIlI==lllIlIlI){
lIllll=lIlII->IIlIllI;}else if(lllIlIl.IIIlI.IIlIlI==lIIlllII){
lIllll=lIlII->IIIIIlll;}else if(lllIlIl.IIIlI.IIlIlI==lIIlIIIl){
lIllll=lIlII->IllIllII;}else{
lIllll=llIIlIl;}

if(lIllll==llIIlIl){lllllIII=sizeof(struct IlIII)+IIIllll+llIlIl+
(0xc53+1810-0x1325);}else{lllllIII=sizeof(struct IlIII)+IIIllll;}IIIll=IllllIl(
lllllIII,GFP_KERNEL);if(!IIIll){IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x63\x72\x65\x61\x74\x65\x5f\x72\x65\x71\x75\x65\x73\x74\x3a\x20\x63\x61\x6e\x6e\x6f\x74\x20\x61\x6c\x6c\x6f\x63\x61\x74\x65\x20\x72\x65\x71\x75\x65\x73\x74\x2c\x20\x75\x6e\x72\x62\x73\x69\x7a\x65\x3d\x25\x6c\x75\x20\x2b\x20\x25\x6c\x75" "\n"
,(unsigned long)IIIllll,(unsigned long)sizeof(struct IlIII));break;}
#ifdef _USBD_DEBUG_MEMORY_
atomic_inc(&lIllllll);
#endif


memset(IIIll,(0x13fb+1223-0x18c2),sizeof(*IIIll));INIT_LIST_HEAD(&IIIll->IlIlIl)
;IIIll->lllllI=lllllIII;atomic_set(&IIIll->state,lIlIIIIl);IIIll->lIlII=IlllIIlI
(lIlII);IIIll->lIllll=lIllll;IIIll->lIlllIl=(0xd80+4135-0x1da7);IIIll->endpoint=
endpoint;IIIll->lIIIl=lllIlIl.IIIlI.lIlIlI;IIIll->lIlIll.IlllIIIl=lllIlIl.IIIlI.
lIlIIll;kref_init(&IIIll->lllllIl);IlIlIlll=(lIIll)(IIIll+(0x422+2120-0xc69));


if(__copy_from_user(IlIlIlll,llIlI,IIIllll)!=(0xa76+6833-0x2527)){IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x63\x72\x65\x61\x74\x65\x5f\x72\x65\x71\x75\x65\x73\x74\x3a\x20\x63\x61\x6e\x6e\x6f\x74\x20\x63\x6f\x70\x79\x20\x66\x72\x6f\x6d\x20\x75\x73\x65\x72\x20\x62\x75\x66\x66\x65\x72\x20\x28\x33\x29" "\n"
);break;}llIlI+=IIIllll;IIlII-=IIIllll;

if(lIllll==llIIlIl){IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x63\x72\x65\x61\x74\x65\x5f\x72\x65\x71\x75\x65\x73\x74\x3a\x20\x73\x6f\x6c\x69\x64\x20\x75\x6e\x72\x62" "\n"
);
IIIll->IlIlII.IIIIl=(void*)(((unsigned long)IlIlIlll+IIIllll+(0x1a5+6141-0x1962)
)&(~(unsigned long)((0x15d8+1952-0x1d38)-(0x621+1040-0xa30))));
if(llIlIl&&!(flags&IIIIIl)){if(llIlIl>IIlII){IlIlI=-(0xff6+3818-0x1edf);break;}
if(__copy_from_user(IIIll->IlIlII.IIIIl,llIlI,llIlIl)){IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x63\x72\x65\x61\x74\x65\x5f\x72\x65\x71\x75\x65\x73\x74\x3a\x20\x63\x61\x6e\x6e\x6f\x74\x20\x63\x6f\x70\x79\x20\x66\x72\x6f\x6d\x20\x75\x73\x65\x72\x20\x62\x75\x66\x66\x65\x72\x20\x28\x34\x29" "\n"
);break;}llIlI+=llIlIl;IIlII-=llIlIl;}}else if(lIllll==lIlllll){IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x63\x72\x65\x61\x74\x65\x5f\x72\x65\x71\x75\x65\x73\x74\x3a\x20\x70\x61\x72\x74\x69\x74\x69\x6f\x6e\x65\x64" "\n"
);
if(IlIlIlll->IIIlI.IIlIlI==lIIlIIIl){IlIlI=lIIlIIIlI(&IIIll->IIllIl.lIllIIl,
llIlIl,IlIlIlll->llIIl.IIlIIll,IlIlIlll->llIIl.lIllIlI);if(IlIlI<
(0x947+502-0xb3d)){IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x63\x72\x65\x61\x74\x65\x5f\x72\x65\x71\x75\x65\x73\x74\x3a\x20\x75\x73\x62\x64\x5f\x62\x63\x5f\x61\x6c\x6c\x6f\x63\x5f\x69\x73\x6f\x20\x66\x61\x69\x6c\x65\x64" "\n"
);break;}}else{int IlllIllI=IIIlIlII(lIlII->llIII,endpoint);if(IlllIllI<
(0x996+177-0xa47)){IlIlI=IlllIllI;IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x63\x72\x65\x61\x74\x65\x5f\x72\x65\x71\x75\x65\x73\x74\x3a\x20\x6e\x6f\x20\x65\x6e\x64\x70\x6f\x69\x6e\x74" "\n"
);break;}IlIlI=IllllIIIl(&IIIll->IIllIl.lIllIIl,llIlIl,IlllIllI);if(IlIlI<
(0x5b9+665-0x852)){IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x63\x72\x65\x61\x74\x65\x5f\x72\x65\x71\x75\x65\x73\x74\x3a\x20\x75\x73\x62\x64\x5f\x62\x63\x5f\x61\x6c\x6c\x6f\x63\x20\x66\x61\x69\x6c\x65\x64" "\n"
);break;}}
if(llIlIl&&!(flags&IIIIIl)){if(llIlIl>IIlII){IlIlI=-(0x1764+1017-0x1b5c);break;}
if(IlIlIllII(&IIIll->IIllIl.lIllIIl,llIlI,min(llIlIl,IIlII))<llIlIl){IlIlI=-
(0x2200+122-0x2279);break;}llIlI+=llIlIl;IIlII-=llIlIl;}}
#if KERNEL_GT_EQ((0x39+9346-0x24b9),(0x147+9419-0x260c),(0x1447+4707-0x268b))
else if(lIllll==lIlIllI){int IlllIllI=IIIlIlII(lIlII->llIII,endpoint);IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x63\x72\x65\x61\x74\x65\x5f\x72\x65\x71\x75\x65\x73\x74\x3a\x20\x73\x67" "\n"
);if(IlllIllI<(0x720+3956-0x1694)){IlIlI=IlllIllI;IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x63\x72\x65\x61\x74\x65\x5f\x72\x65\x71\x75\x65\x73\x74\x3a\x20\x6e\x6f\x20\x65\x6e\x64\x70\x6f\x69\x6e\x74" "\n"
);break;}IlIlI=llIlllIII(&IIIll->lIllIll.sg,llIlIl,IlllIllI);if(IlIlI<
(0x1486+102-0x14ec)){IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x63\x72\x65\x61\x74\x65\x5f\x72\x65\x71\x75\x65\x73\x74\x3a\x20\x75\x73\x62\x64\x5f\x73\x67\x5f\x61\x6c\x6c\x6f\x63\x20\x66\x61\x69\x6c\x65\x64" "\n"
);break;}if(llIlIl&&(flags&IIIIIl)==(0x89+6675-0x1a9c)){if(llIlIl>IIlII){IlIlI=-
(0x809+1084-0xc44);break;}if(llIllIIll(&IIIll->lIllIll.sg,llIlI,llIlIl)<llIlIl){
IlIlI=-(0xf27+2096-0x1756);break;}llIlI+=llIlIl;IIlII-=llIlIl;}}
#endif 
else{IlIlI=-EINVAL;break;}IlIlI=(0x39f+294-0x4c5);}while((0x1b06+779-0x1e11));
if(IlIlI<(0x747+4692-0x199b)){if(IIIll){lllIllI(IIIll);IIIll=NULL;}}return IIIll
;}


struct IlIII*lIIIIIIII(struct IlIII*IIIll,gfp_t llllI){struct IlIII*lIIIllI;if(
IIIll->lIllll==llIIlIl)
return NULL;lIIIllI=IllllIl(IIIll->lllllI,llllI);if(lIIIllI){memset(lIIIllI,
(0x16c5+2371-0x2008),sizeof(*lIIIllI));
memcpy(lIIIllI+(0x1297+1554-0x18a8),IIIll+(0xb07+3424-0x1866),IIIll->lllllI-
sizeof(*IIIll));
INIT_LIST_HEAD(&lIIIllI->IlIlIl);lIIIllI->lllllI=IIIll->lllllI;lIIIllI->lIIIl=
IIIll->lIIIl;lIIIllI->lIlIll=IIIll->lIlIll;atomic_set(&lIIIllI->state,lIlIIIIl);
lIIIllI->lIlII=IlllIIlI(IIIll->lIlII);lIIIllI->endpoint=IIIll->endpoint;lIIIllI
->IlIlII.IIIIl=(void*)lIIIllI+((unsigned long)IIIll->IlIlII.IIIIl-(unsigned long
)IIIll);lIIIllI->lIllll=IIIll->lIllll;kref_init(&lIIIllI->lllllIl);
#ifdef _USBD_DEBUG_MEMORY_
atomic_inc(&lIllllll);
#endif
}return lIIIllI;}void lllllIlI(struct kref*llllIlII){struct IlIII*IIIll=
container_of(llllIlII,struct IlIII,lllllIl);IlllI(
"\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x64\x65\x73\x74\x72\x6f\x79\x5f\x72\x65\x71\x75\x65\x73\x74\x3a\x20\x75\x6e\x69\x71\x75\x65\x5f\x69\x64\x3d\x30\x78\x25\x6c\x6c\x78" "\n"
,IIIll->lIIIl);
#ifdef _USBD_DEBUG_MEMORY_
atomic_inc(&lIllIIlIl);
#endif
if(IIIll->lIllll==llIIlIl){if(IIIll->IlIlII.lIlll){if(IIIll->IlIlII.lIlll->
setup_packet)lllIII(IIIll->IlIlII.lIlll->setup_packet);IlIIllIl(IIIll->IlIlII.
lIlll);}


}else if(IIIll->lIllll==lIlllll){IlllIIIll(&IIIll->IIllIl.IlIIIII);IlIlllIII(&
IIIll->IIllIl.lIllIIl);}
#if KERNEL_GT_EQ((0x1b75+1425-0x2104),(0x969+2883-0x14a6),(0x307+8098-0x228a))
else if(IIIll->lIllll==lIlIllI){if(IIIll->lIllIll.lIlll){if(IIIll->lIllIll.lIlll
->setup_packet)lllIII(IIIll->lIllIll.lIlll->setup_packet);IlIIllIl(IIIll->
lIllIll.lIlll);}IIlIIllI(&IIIll->lIllIll.sg);}
#endif
if(IIIll->lIlII){lIlIIlIl(IIIll->lIlII);}lllIII(IIIll);}void lllIllI(struct 
IlIII*IIIll){
#ifdef _USBD_DEBUG_MEMORY_
atomic_inc(&lIlIllIII);
#endif
kref_put(&IIIll->lllllIl,lllllIlI);}
#endif 
Illlll lIlllllIl(void){static Illlll lIlIlI=(0xa3b+2899-0x158e);return(++lIlIlI)
;}int IlIlIIlll(void*IIllllll,struct vm_area_struct*IlIllll){int IlIlI=
(0x997+3673-0x17f0);unsigned long start=IlIllll->vm_start;unsigned long IIlIIl=
IlIllll->vm_end-IlIllll->vm_start;unsigned long lllIllllI;IlllI(
"\x75\x73\x62\x64\x5f\x6d\x61\x70\x5f\x76\x6d\x65\x6d\x3a\x20\x2b\x2b" "\n");
while(IIlIIl>(0x1ba1+256-0x1ca1)){lllIllllI=vmalloc_to_pfn(IIllllll);IlIlI=
remap_pfn_range(IlIllll,start,lllIllllI,PAGE_SIZE,PAGE_SHARED);if(IlIlI<
(0x392+3323-0x108d)){IlllI(
"\x75\x73\x62\x64\x5f\x6d\x61\x70\x5f\x76\x6d\x65\x6d\x3a\x20\x63\x61\x6e\x6e\x6f\x74\x20\x6d\x61\x70\x20\x74\x68\x65\x20\x70\x61\x67\x65" "\n"
);break;}start+=PAGE_SIZE;IIllllll+=PAGE_SIZE;IIlIIl-=PAGE_SIZE;}IlllI(
"\x75\x73\x62\x64\x5f\x6d\x61\x70\x5f\x76\x6d\x65\x6d\x3a\x20\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x3d\x25\x64" "\n"
,IlIlI);return IlIlI;}void llIlllll(dma_addr_t lIIlIII,void*lllIIl,unsigned long
 IIlIIl){void*IllIIl;struct page*IIllIlII;unsigned long flags;unsigned long 
lIIllI;unsigned long IlIlllI,IllIllI;local_irq_save(flags);while(IIlIIl){

IlIlllI=lIIlIII&(PAGE_SIZE-(0x13db+4226-0x245c));IllIllI=PAGE_SIZE-IlIlllI;
lIIllI=(IllIllI<IIlIIl)?IllIllI:IIlIIl;
IIllIlII=pfn_to_page(lIIlIII>>PAGE_SHIFT);
#if KERNEL_GT_EQ((0x4bf+7278-0x212b),(0x199a+425-0x1b3d),(0x1020+1921-0x177c))
IllIIl=kmap_atomic(IIllIlII);
#else
IllIIl=kmap_atomic(IIllIlII,KM_IRQ0);
#endif
memcpy(IllIIl+IlIlllI,lllIIl,lIIllI);
#if KERNEL_GT_EQ((0x4b+4422-0x118f),(0x300+7443-0x200d),(0xc7d+4220-0x1cd4))
kunmap_atomic(IllIIl);
#else
kunmap_atomic(IllIIl,KM_IRQ0);
#endif

lIIlIII+=lIIllI;lllIIl+=lIIllI;IIlIIl-=lIIllI;}local_irq_restore(flags);}void 
IllIlIIl(void*lIIlIII,dma_addr_t lllIIl,unsigned long IIlIIl){struct page*
IIllIlII;unsigned char*IllIIl;unsigned long flags;unsigned long lIIllI;unsigned 
long IlIlllI,IllIllI;local_irq_save(flags);while(IIlIIl){

IlIlllI=lllIIl&(PAGE_SIZE-(0x275+7072-0x1e14));IllIllI=PAGE_SIZE-IlIlllI;lIIllI=
(IllIllI<IIlIIl)?IllIllI:IIlIIl;
IIllIlII=pfn_to_page(lllIIl>>PAGE_SHIFT);
#if KERNEL_GT_EQ((0x1923+972-0x1ced),(0x1c0c+2521-0x25df),(0x2025+58-0x203a))
IllIIl=kmap_atomic(IIllIlII);
#else
IllIIl=kmap_atomic(IIllIlII,KM_IRQ0);
#endif
memcpy(lIIlIII,IllIIl+IlIlllI,lIIllI);
#if KERNEL_GT_EQ((0x7da+2654-0x1236),(0x1e40+53-0x1e6f),(0x67+8663-0x2219))
kunmap_atomic(IllIIl);
#else
kunmap_atomic(IllIIl,KM_IRQ0);
#endif

lllIIl+=lIIllI;lIIlIII+=lIIllI;IIlIIl-=lIIllI;}local_irq_restore(flags);}int 
lIIIllIl(lllIl status){int IlIlI;switch(status){case IIllIlIlI:IlIlI=
(0x4bc+6481-0x1e0d);break;case IIllIIlII:IlIlI=-EINPROGRESS;break;case IIlIIIllI
:IlIlI=-ECONNRESET;break;case lIIllIIIl:IlIlI=-EXDEV;break;case IIllllIIl:IlIlI=
-ETIMEDOUT;break;case IllIIlIlI:IlIlI=-EINVAL;break;case IIlIIllII:IlIlI=-ENODEV
;break;case llIllIIII:IlIlI=-EREMOTEIO;break;case IIIIllIlI:IlIlI=-EOVERFLOW;
break;case lIllIllll:IlIlI=-ENOSR;break;case lllIIlIII:IlIlI=-ECOMM;break;case 
IllllllII:IlIlI=-EPIPE;break;case llIIIlllI:IlIlI=-EILSEQ;break;case IllIlIlIl:
IlIlI=-EPROTO;break;case IllIIllII:IlIlI=-ENOMEM;break;case lIIIIlIII:IlIlI=-
EPROTO;break;case lllIIIlIl:default:IlIlI=-EPROTO;break;}return IlIlI;}
size_t IIIllIll(struct usb_iso_packet_descriptor*llIlIII,int IIlII,void*lIIlIII,
void*lllIIl,int llIIIIlI){IIIII*IlIIlIIl;size_t IlIlI;IlIlI=(0x9f0+2069-0x1205);
IlIIlIIl=lIIlIII;for(;IIlII;IIlII--){IIIII*llIlIlIII=lllIIl+llIlIII->offset;
unsigned int length=llIIIIlI?llIlIII->actual_length:llIlIII->length;if(length&&
IlIIlIIl!=llIlIlIII)
memmove(IlIIlIIl,llIlIlIII,length);IlIIlIIl+=length;IlIlI+=length;llIlIII++;}
IlllI(
"\x75\x73\x62\x64\x5f\x70\x61\x63\x6b\x5f\x69\x73\x6f\x5f\x62\x75\x66\x66\x65\x72\x3a\x20\x70\x61\x63\x6b\x65\x64\x3d\x25\x6c\x75" "\n"
,(unsigned long)IlIlI);return IlIlI;}
size_t IllIllll(struct usb_iso_packet_descriptor*llIlIII,int IIlII,int llIIIIlI)
{size_t IlIlI;IlIlI=(0xc+4586-0x11f6);for(;IIlII>(0xcc8+3417-0x1a21);IIlII--){
IlIlI+=llIIIIlI?llIlIII->actual_length:llIlIII->length;llIlIII++;}IlllI(
"\x75\x73\x62\x64\x5f\x63\x6f\x75\x6e\x74\x5f\x69\x73\x6f\x5f\x62\x75\x66\x66\x65\x72\x3a\x20\x70\x61\x63\x6b\x65\x64\x3d\x25\x6c\x75" "\n"
,(unsigned long)IlIlI);return IlIlI;}char*IlIIlIlI(struct kobject*kobj,gfp_t 
llIIllIll){
#if KERNEL_GT_EQ((0x159+8396-0x2223),(0xa31+2967-0x15c2),(0x20c2+1512-0x2697))
return kobject_get_path(kobj,llIIllIll);
#else
char*IIIlllI;int length;struct kobject*IIlIII;
for(IIlIII=kobj,length=(0x26c+9093-0x25f1);IIlIII&&kobject_name(IIlIII);IIlIII=
IIlIII->parent){length+=strlen(kobject_name(IIlIII));length+=(0xb3f+156-0xbda);
}if(IIlIII)
return NULL;
IIIlllI=IllllIl(length+(0x1611+1831-0x1d37),llIIllIll);if(IIIlllI==NULL)return 
NULL;*(IIIlllI+length)='\0';
for(IIlIII=kobj;IIlIII&&length>(0x4b9+1430-0xa4f);IIlIII=IIlIII->parent){int l=
strlen(kobject_name(IIlIII));strncpy(IIIlllI+length-l,kobject_name(IIlIII),l);*(
IIIlllI+length-l-(0x983+2189-0x120f))=((char)(0xbd2+1954-0x1345));length-=l+
(0x1c2d+2203-0x24c7);}
if(length!=(0x7c9+389-0x94e)||IIlIII){lllIII(IIIlllI);return NULL;}return 
IIIlllI;
#endif
}void llIIlIIIl(char*IIIlllI){
#if KERNEL_GT_EQ((0xfd7+4364-0x20e1),(0xad7+2618-0x150b),(0xc5c+6279-0x24d0))
kfree(IIIlllI);
#else
lllIII(IIIlllI);
#endif
}int lIIllIIlI(struct device*dev){



if(dev->bus&&!strcmp(dev->bus->name,"\x75\x73\x62"))return(0x158f+1612-0x1bda);
return(0x18f+2435-0xb12);}int lIIIIIIlI(struct device*dev){if(lIIllIIlI(dev)){
#if KERNEL_LT_EQ((0x5a6+6248-0x1e0c),(0x167b+3772-0x2531),(0xf1f+4392-0x2032))

if(!strchr(IlIIlI(dev),((char)(0x1728+1415-0x1c75))))return(0x1df0+1788-0x24eb);
#else




if(dev->type&&!strcmp(dev->type->name,
"\x75\x73\x62\x5f\x69\x6e\x74\x65\x72\x66\x61\x63\x65"))return(0x105+3233-0xda5)
;
#endif
}return(0x1dac+667-0x2047);}int IlIlIIlII(struct device*dev){if(lIIllIIlI(dev)){
#if KERNEL_LT_EQ((0x1c7b+1870-0x23c7),(0x5e3+5424-0x1b0d),(0x161a+4053-0x25da))


if(strchr(IlIIlI(dev),((char)(0xbe1+4248-0x1c3f))))return(0x4ac+4467-0x161e);
#else




if(dev->type&&!strcmp(dev->type->name,"\x75\x73\x62\x5f\x64\x65\x76\x69\x63\x65"
))return(0xfe4+2126-0x1831);
#endif
}return(0x12bd+327-0x1404);}
#if KERNEL_GT_EQ((0x94f+1804-0x1059),(0x231b+831-0x2654),(0x1eb2+2127-0x26eb))












void llIlIIll(struct device*dev,int lIllIIll){
#if KERNEL_LT_EQ((0x1a07+82-0x1a57),(0x77d+6906-0x2271),(0x868+7043-0x23ce))
dev->uevent_suppress=lIllIIll;
#elif KERNEL_GT_EQ((0x13b3+2696-0x1e39),(0x1739+3722-0x25bd),(0x24c4+321-0x25e7)\
)
dev_set_uevent_suppress(dev,lIllIIll);
#endif
}int IlIIIlllI(struct device*dev){
#if KERNEL_LT_EQ((0x17f7+1269-0x1cea),(0x27+9518-0x254f),(0xbc+1954-0x841))
return dev->uevent_suppress;
#elif KERNEL_GT_EQ((0xe00+773-0x1103),(0xab1+6315-0x2356),(0xd6+8105-0x2061))
return dev_get_uevent_suppress(dev);
#endif
}
#endif 
#ifndef _USBD_DEBUG_BUILD_
const char*IIllIlll(unsigned long lIllIII){return"";}const char*lllIlIII(
unsigned long lIllIII){return"";}void IlIlIIll(struct urb*lIlll,Illlll lIIIl){}
#else
const char*IIllIlll(unsigned long lIllIII){switch(lIllIII){
#if KERNEL_GT_EQ((0x1c43+1868-0x238d),(0x94b+5908-0x2059),(0xa8f+3446-0x17f1))
case BUS_NOTIFY_ADD_DEVICE:return
"\x42\x55\x53\x5f\x4e\x4f\x54\x49\x46\x59\x5f\x41\x44\x44\x5f\x44\x45\x56\x49\x43\x45"
;case BUS_NOTIFY_DEL_DEVICE:return
"\x42\x55\x53\x5f\x4e\x4f\x54\x49\x46\x59\x5f\x44\x45\x4c\x5f\x44\x45\x56\x49\x43\x45"
;case BUS_NOTIFY_BOUND_DRIVER:return
"\x42\x55\x53\x5f\x4e\x4f\x54\x49\x46\x59\x5f\x42\x4f\x55\x4e\x44\x5f\x44\x52\x49\x56\x45\x52"
;case BUS_NOTIFY_UNBIND_DRIVER:return
"\x42\x55\x53\x5f\x4e\x4f\x54\x49\x46\x59\x5f\x55\x4e\x42\x49\x4e\x44\x5f\x44\x52\x49\x56\x45\x52"
;
#endif
#if KERNEL_GT_EQ((0x507+7164-0x2101),(0x1261+2014-0x1a39),(0x515+7111-0x20bd))
case BUS_NOTIFY_UNBOUND_DRIVER:return
"\x42\x55\x53\x5f\x4e\x4f\x54\x49\x46\x59\x5f\x55\x4e\x42\x4f\x55\x4e\x44\x5f\x44\x52\x49\x56\x45\x52"
;
#endif
#if KERNEL_GT_EQ((0x149+6009-0x18c0),(0xa51+1698-0x10ed),(0xf72+69-0xf93))
case BUS_NOTIFY_BIND_DRIVER:return
"\x42\x55\x53\x5f\x4e\x4f\x54\x49\x46\x59\x5f\x42\x49\x4e\x44\x5f\x44\x52\x49\x56\x45\x52"
;
#endif
#if KERNEL_GT_EQ((0xbdd+4177-0x1c2b),(0x161+7973-0x2074),(0x1144+377-0x12bd))
case BUS_NOTIFY_REMOVED_DEVICE:return
"\x42\x55\x53\x5f\x4e\x4f\x54\x49\x46\x59\x5f\x52\x45\x4d\x4f\x56\x45\x44\x5f\x44\x45\x56\x49\x43\x45"
;
#endif
default:break;}return"\x75\x6e\x6b\x6e\x6f\x77\x6e";}const char*lllIlIII(
unsigned long lIllIII){switch(lIllIII){case USB_DEVICE_ADD:return
"\x55\x53\x42\x5f\x44\x45\x56\x49\x43\x45\x5f\x41\x44\x44";case 
USB_DEVICE_REMOVE:return
"\x55\x53\x42\x5f\x44\x45\x56\x49\x43\x45\x5f\x52\x45\x4d\x4f\x56\x45";case 
USB_BUS_ADD:return"\x55\x53\x42\x5f\x42\x55\x53\x5f\x41\x44\x44";case 
USB_BUS_REMOVE:return"\x55\x53\x42\x5f\x42\x55\x53\x5f\x52\x45\x4d\x4f\x56\x45";
default:break;}return"\x75\x6e\x6b\x6e\x6f\x77\x6e";}void IlIlIIll(struct urb*
lIlll,Illlll lIIIl){const char*IIlIllIII[]={"\x69\x73\x6f","\x69\x6e\x74",
"\x63\x74\x72\x6c","\x62\x75\x6c\x6b"};if(!lIlll)return;IlllI(
"\x2b\x2b\x2b\x2b\x20\x55\x52\x42\x20\x53\x54\x41\x52\x54\x20\x2b\x2b\x2b\x2b" "\n"
);IlllI("\x20\x20\x55\x52\x42\x3d\x30\x78\x25\x70" "\n",lIlll);IlllI(
"\x20\x20\x50\x69\x70\x65\x3d\x30\x78\x25\x30\x38\x58\x20\x28\x64\x65\x76\x3a\x20\x25\x64\x20\x65\x6e\x64\x70\x3a\x20\x25\x64\x20\x64\x69\x72\x3a\x20\x25\x73\x20\x74\x79\x70\x65\x3a\x20\x25\x73\x29" "\n"
,lIlll->pipe,usb_pipedevice(lIlll->pipe),usb_pipeendpoint(lIlll->pipe),
usb_pipein(lIlll->pipe)?"\x69\x6e":"\x6f\x75\x74",IIlIllIII[usb_pipetype(lIlll->
pipe)]);IlllI("\x20\x20\x53\x74\x61\x74\x75\x73\x3d\x25\x64" "\n",lIlll->status)
;IlllI(
"\x20\x20\x54\x72\x61\x6e\x73\x66\x65\x72\x46\x6c\x61\x67\x73\x3d\x30\x78\x25\x30\x38\x58" "\n"
,lIlll->transfer_flags);IlllI(
"\x20\x20\x42\x75\x66\x66\x65\x72\x3d\x30\x78\x25\x70" "\n",lIlll->
transfer_buffer);IlllI(
"\x20\x20\x42\x75\x66\x66\x65\x72\x4c\x65\x6e\x67\x74\x68\x3d\x25\x64" "\n",
lIlll->transfer_buffer_length);IlllI(
"\x20\x20\x41\x63\x74\x75\x61\x6c\x4c\x65\x6e\x67\x74\x68\x3d\x25\x64" "\n",
lIlll->actual_length);IlllI(
"\x20\x20\x54\x72\x61\x6e\x73\x66\x65\x72\x44\x6d\x61\x3d\x30\x78\x25\x30\x38\x58" "\n"
,(u32)lIlll->transfer_dma);IlllI(
"\x20\x20\x53\x65\x74\x75\x70\x44\x6d\x61\x3d\x30\x78\x25\x30\x38\x58" "\n",(u32
)lIlll->setup_dma);if(usb_pipecontrol(lIlll->pipe)){IlllI(
"\x20\x20\x53\x65\x74\x75\x70\x50\x61\x63\x6b\x65\x74\x3d\x25\x30\x32\x58\x20\x25\x30\x32\x58\x20\x25\x30\x32\x58\x20\x25\x30\x32\x58\x20\x25\x30\x32\x58\x20\x25\x30\x32\x58\x20\x25\x30\x32\x58\x20\x25\x30\x32\x58" "\n"
,lIlll->setup_packet[(0xfba+2092-0x17e6)],lIlll->setup_packet[
(0x7c2+4179-0x1814)],lIlll->setup_packet[(0x5d5+3666-0x1425)],lIlll->
setup_packet[(0xe6f+187-0xf27)],lIlll->setup_packet[(0x346+8354-0x23e4)],lIlll->
setup_packet[(0x1dec+766-0x20e5)],lIlll->setup_packet[(0x997+5485-0x1efe)],lIlll
->setup_packet[(0x1022+5150-0x2439)]);}else if(usb_pipeisoc(lIlll->pipe)){int i;
IlllI("\x20\x20\x53\x74\x61\x72\x74\x46\x72\x61\x6d\x65\x3d\x25\x64" "\n",lIlll
->start_frame);IlllI(
"\x20\x20\x4e\x75\x6d\x62\x65\x72\x4f\x66\x50\x61\x63\x6b\x65\x74\x73\x3d\x25\x64" "\n"
,lIlll->number_of_packets);IlllI(
"\x20\x20\x49\x6e\x74\x65\x72\x76\x61\x6c\x3d\x25\x64" "\n",lIlll->interval);
IlllI("\x20\x20\x45\x72\x72\x6f\x72\x43\x6f\x75\x6e\x74\x3d\x25\x64" "\n",lIlll
->error_count);IlllI("\x20\x20\x49\x73\x6f\x46\x72\x61\x6d\x65\x73\x3d" "\n");
for(i=(0x881+7162-0x247b);i<lIlll->number_of_packets;i++){IlllI(
"\x20\x20\x20\x20\x5b\x25\x64\x5d\x20\x4f\x66\x66\x73\x65\x74\x3d\x25\x64\x20\x4c\x65\x6e\x67\x74\x68\x3d\x25\x64\x20\x41\x63\x74\x75\x61\x6c\x4c\x65\x6e\x67\x74\x68\x3d\x25\x64\x20\x53\x74\x61\x74\x75\x73\x3d\x25\x64" "\n"
,i,lIlll->iso_frame_desc[i].offset,lIlll->iso_frame_desc[i].length,lIlll->
iso_frame_desc[i].actual_length,lIlll->iso_frame_desc[i].status);}}else if(
usb_pipeint(lIlll->pipe)){IlllI(
"\x20\x20\x49\x6e\x74\x65\x72\x76\x61\x6c\x3d\x25\x64" "\n",lIlll->interval);}
IlllI(
"\x2d\x2d\x2d\x2d\x20\x55\x52\x42\x20\x45\x4e\x44\x20\x2d\x2d\x2d\x2d" "\n");}
#endif 
#ifndef _USBD_DEBUG_BUILD_
void IlIIIIl(lIIll IIlIl){}
#else
static void IIIIlll(lIIll IIlIl);void IlIIIIl(lIIll IIlIl){int i;
if(!IIlIl)return;IlllI(
"\x2d\x2d\x2d\x2d\x20\x55\x4e\x52\x42\x20\x53\x54\x41\x52\x54" "\n");switch(
IIlIl->IIIlI.IIlIlI){case lllllIIl:IlllI(
"\x55\x4e\x52\x42\x5f\x46\x55\x4e\x43\x54\x49\x4f\x4e\x5f\x47\x45\x54\x5f\x44\x45\x53\x43\x52\x49\x50\x54\x4f\x52" "\n"
);IIIIlll(IIlIl);IlllI(
"\x20\x20\x44\x65\x73\x63\x72\x69\x70\x74\x6f\x72\x52\x65\x71\x75\x65\x73\x74" "\n"
);IlllI(
"\x20\x20\x20\x20\x52\x65\x71\x75\x65\x73\x74\x54\x79\x70\x65\x3d\x25\x64" "\n",
IIlIl->IllIII.IIlllII);IlllI(
"\x20\x20\x20\x20\x52\x65\x71\x75\x65\x73\x74\x52\x65\x63\x69\x70\x69\x65\x6e\x74\x3d\x25\x64" "\n"
,IIlIl->IllIII.IIIIIllI);IlllI(
"\x20\x20\x20\x20\x44\x65\x73\x63\x54\x79\x70\x65\x3d\x25\x64" "\n",IIlIl->
IllIII.IlllIlll);IlllI(
"\x20\x20\x20\x20\x44\x65\x73\x63\x49\x6e\x64\x65\x78\x3d\x25\x64" "\n",IIlIl->
IllIII.IIIIIIlI);IlllI(
"\x20\x20\x20\x20\x4c\x61\x6e\x67\x49\x64\x3d\x25\x64" "\n",IIlIl->IllIII.
IllllIll);IlllI(
"\x20\x20\x20\x20\x42\x75\x66\x66\x65\x72\x53\x69\x7a\x65\x3d\x25\x64" "\n",
IIlIl->IllIII.IlIll);break;case lIIlllll:IlllI(
"\x55\x4e\x52\x42\x5f\x46\x55\x4e\x43\x54\x49\x4f\x4e\x5f\x53\x45\x54\x5f\x44\x45\x53\x43\x52\x49\x50\x54\x4f\x52" "\n"
);IIIIlll(IIlIl);IlllI(
"\x20\x20\x44\x65\x73\x63\x72\x69\x70\x74\x6f\x72\x52\x65\x71\x75\x65\x73\x74" "\n"
);IlllI("\x20\x20\x20\x20\x44\x65\x73\x63\x54\x79\x70\x65\x3d\x25\x64" "\n",
IIlIl->IllIII.IlllIlll);IlllI(
"\x20\x20\x20\x20\x44\x65\x73\x63\x49\x6e\x64\x65\x78\x3d\x25\x64" "\n\n",IIlIl
->IllIII.IIIIIIlI);IlllI(
"\x20\x20\x20\x20\x4c\x61\x6e\x67\x49\x64\x3d\x25\x64" "\n",IIlIl->IllIII.
IllllIll);IlllI(
"\x20\x20\x20\x20\x42\x75\x66\x66\x65\x72\x53\x69\x7a\x65\x3d\x25\x64" "\n",
IIlIl->IllIII.IlIll);break;case IIllllII:IlllI(
"\x55\x4e\x52\x42\x5f\x46\x55\x4e\x43\x54\x49\x4f\x4e\x5f\x53\x45\x4c\x45\x43\x54\x5f\x43\x4f\x4e\x46\x49\x47\x55\x52\x41\x54\x49\x4f\x4e" "\n"
);IIIIlll(IIlIl);IlllI(
"\x20\x20\x53\x65\x6c\x65\x63\x74\x43\x6f\x6e\x66\x69\x67\x75\x72\x61\x74\x69\x6f\x6e" "\n"
);IlllI(
"\x20\x20\x20\x20\x43\x6f\x6e\x66\x69\x67\x75\x72\x61\x74\x69\x6f\x6e\x3d\x25\x64" "\n"
,IIlIl->IIIIlI.IlIIIIII);IlllI(
"\x20\x20\x20\x20\x4e\x75\x6d\x41\x6c\x74\x65\x72\x6e\x61\x74\x65\x73\x3d\x25\x64" "\n"
,IIlIl->IIIIlI.IllllIIl);for(i=(0x20da+1431-0x2671);i<IIlIl->IIIIlI.IllllIIl;i++
){IlllI(
"\x20\x20\x20\x20\x20\x20\x25\x2e\x33\x64\x3a\x20\x49\x6e\x74\x65\x72\x66\x61\x63\x65\x4e\x75\x6d\x3d\x25\x64" "\n"
,i,IIlIl->IIIIlI.lllIlII[i].IIllllI);IlllI(
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x41\x6c\x74\x65\x72\x6e\x61\x74\x65\x4e\x75\x6d\x3d\x25\x64" "\n"
,IIlIl->IIIIlI.lllIlII[i].IlllIII);}break;case lIIlIIII:IlllI(
"\x55\x4e\x52\x42\x5f\x46\x55\x4e\x43\x54\x49\x4f\x4e\x5f\x53\x45\x4c\x45\x43\x54\x5f\x49\x4e\x54\x45\x52\x46\x41\x43\x45" "\n"
);IIIIlll(IIlIl);IlllI(
"\x20\x20\x53\x65\x6c\x65\x63\x74\x49\x6e\x74\x65\x72\x66\x61\x63\x65" "\n");
IlllI("\x20\x20\x20\x20\x49\x6e\x74\x65\x72\x66\x61\x63\x65\x3d\x25\x64" "\n",
IIlIl->IlllIIl.IIllllI);IlllI(
"\x20\x20\x20\x20\x41\x6c\x74\x65\x72\x6e\x61\x74\x65\x3d\x25\x64" "\n",IIlIl->
IlllIIl.IlllIII);break;case llIlIIlI:IlllI(
"\x55\x4e\x52\x42\x5f\x46\x55\x4e\x43\x54\x49\x4f\x4e\x5f\x43\x4f\x4e\x54\x52\x4f\x4c\x5f\x54\x52\x41\x4e\x53\x46\x45\x52" "\n"
);IIIIlll(IIlIl);IlllI(
"\x20\x20\x43\x6f\x6e\x74\x72\x6f\x6c\x54\x72\x61\x6e\x73\x66\x65\x72" "\n");
IlllI("\x20\x20\x20\x20\x45\x6e\x64\x70\x6f\x69\x6e\x74\x3d\x25\x64" "\n",IIlIl
->IIIllI.Endpoint);IlllI(
"\x20\x20\x20\x20\x46\x6c\x61\x67\x73\x3d\x30\x78\x25\x2e\x32\x58" "\n",IIlIl->
IIIllI.Flags);IlllI(
"\x20\x20\x20\x20\x52\x65\x71\x75\x65\x73\x74\x54\x79\x70\x65\x3d\x30\x78\x25\x2e\x32\x58" "\n"
,IIlIl->IIIllI.IIlllII);IlllI(
"\x20\x20\x20\x20\x52\x65\x71\x75\x65\x73\x74\x3d\x30\x78\x25\x2e\x32\x58" "\n",
IIlIl->IIIllI.lIlIIIII);IlllI(
"\x20\x20\x20\x20\x56\x61\x6c\x75\x65\x3d\x30\x78\x25\x2e\x34\x58" "\n",IIlIl->
IIIllI.IlllIIIl);IlllI(
"\x20\x20\x20\x20\x49\x6e\x64\x65\x78\x3d\x30\x78\x25\x2e\x34\x58" "\n",IIlIl->
IIIllI.IIIIlllll);IlllI(
"\x20\x20\x20\x20\x42\x75\x66\x65\x72\x53\x69\x7a\x65\x3d\x25\x64" "\n",IIlIl->
IIIllI.IlIll);break;case lllIlIlI:IlllI(
"\x55\x4e\x52\x42\x5f\x46\x55\x4e\x43\x54\x49\x4f\x4e\x5f\x42\x55\x4c\x4b\x5f\x54\x52\x41\x4e\x53\x46\x45\x52" "\n"
);IIIIlll(IIlIl);IlllI(
"\x20\x20\x42\x75\x6c\x6b\x54\x72\x61\x6e\x73\x66\x65\x72" "\n");IlllI(
"\x20\x20\x20\x20\x45\x6e\x64\x70\x6f\x69\x6e\x74\x3d\x25\x64" "\n",IIlIl->
lIllIl.Endpoint);IlllI(
"\x20\x20\x20\x20\x46\x6c\x61\x67\x73\x3d\x30\x78\x25\x2e\x32\x58" "\n",IIlIl->
lIllIl.Flags);IlllI(
"\x20\x20\x20\x20\x42\x75\x66\x65\x72\x53\x69\x7a\x65\x3d\x25\x64" "\n",IIlIl->
lIllIl.IlIll);break;case lIIlllII:IlllI(
"\x55\x4e\x52\x42\x5f\x46\x55\x4e\x43\x54\x49\x4f\x4e\x5f\x49\x4e\x54\x45\x52\x52\x55\x50\x54\x5f\x54\x52\x41\x4e\x53\x46\x45\x52" "\n"
);IIIIlll(IIlIl);IlllI(
"\x20\x20\x49\x6e\x74\x65\x72\x72\x75\x70\x74\x54\x72\x61\x6e\x73\x66\x65\x72" "\n"
);IlllI("\x20\x20\x20\x20\x45\x6e\x64\x70\x6f\x69\x6e\x74\x3d\x25\x64" "\n",
IIlIl->IIIIII.Endpoint);IlllI(
"\x20\x20\x20\x20\x46\x6c\x61\x67\x73\x3d\x30\x78\x25\x2e\x32\x58" "\n",IIlIl->
IIIIII.Flags);IlllI(
"\x20\x20\x20\x20\x49\x6e\x74\x65\x72\x76\x61\x6c\x3d\x25\x64" "\n",IIlIl->
IIIIII.Interval);IlllI(
"\x20\x20\x20\x20\x42\x75\x66\x65\x72\x53\x69\x7a\x65\x3d\x25\x64" "\n",IIlIl->
IIIIII.IlIll);break;case lIIlIIIl:IlllI(
"\x55\x4e\x52\x42\x5f\x46\x55\x4e\x43\x54\x49\x4f\x4e\x5f\x49\x53\x4f\x43\x48\x5f\x54\x52\x41\x4e\x53\x46\x45\x52" "\n"
);IIIIlll(IIlIl);IlllI(
"\x20\x20\x49\x73\x6f\x63\x68\x54\x72\x61\x6e\x73\x66\x65\x72" "\n");IlllI(
"\x20\x20\x20\x20\x45\x6e\x64\x70\x6f\x69\x6e\x74\x3d\x25\x64" "\n",IIlIl->llIIl
.Endpoint);IlllI(
"\x20\x20\x20\x20\x46\x6c\x61\x67\x73\x3d\x30\x78\x25\x2e\x32\x58" "\n",IIlIl->
llIIl.Flags);IlllI(
"\x20\x20\x20\x20\x42\x75\x66\x65\x72\x53\x69\x7a\x65\x3d\x25\x64" "\n",IIlIl->
llIIl.IlIll);IlllI(
"\x20\x20\x20\x20\x49\x6e\x74\x65\x72\x76\x61\x6c\x3d\x25\x64" "\n",IIlIl->llIIl
.Interval);IlllI(
"\x20\x20\x20\x20\x53\x74\x61\x72\x74\x46\x72\x61\x6d\x65\x3d\x25\x64" "\n",
IIlIl->llIIl.lllIIlll);IlllI(
"\x20\x20\x20\x20\x4e\x75\x6d\x62\x65\x72\x4f\x66\x50\x61\x63\x6b\x65\x74\x73\x3d\x25\x64" "\n"
,IIlIl->llIIl.lIllIlI);IlllI(
"\x20\x20\x20\x20\x45\x72\x72\x6f\x72\x43\x6f\x75\x6e\x74\x3d\x25\x64" "\n",
IIlIl->llIIl.llllIlll);IlllI(
"\x20\x20\x20\x20\x49\x73\x6f\x63\x68\x50\x61\x63\x6b\x65\x74\x73\x3a" "\n");for
(i=(0x1f9+2230-0xaaf);i<IIlIl->llIIl.lIllIlI;i++){IlllI(
"\x20\x20\x20\x20\x20\x20\x25\x2e\x33\x64\x3a\x20\x4f\x66\x66\x73\x65\x74\x3d\x25\x64" "\n"
,i,IIlIl->llIIl.IIlIIll[i].Offset);IlllI(
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x4c\x65\x6e\x67\x74\x68\x3d\x25\x64" "\n"
,IIlIl->llIIl.IIlIIll[i].Length);IlllI(
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x53\x74\x61\x74\x75\x73\x3d\x25\x64" "\n"
,IIlIl->llIIl.IIlIIll[i].Status);}break;case lllIllll:IlllI(
"\x55\x4e\x52\x42\x5f\x46\x55\x4e\x43\x54\x49\x4f\x4e\x5f\x43\x4c\x45\x41\x52\x5f\x53\x54\x41\x4c\x4c" "\n"
);IIIIlll(IIlIl);IlllI("\x20\x20\x43\x6c\x65\x61\x72\x53\x74\x61\x6c\x6c" "\n");
IlllI("\x20\x20\x20\x20\x45\x6e\x64\x70\x6f\x69\x6e\x74\x3d\x25\x64" "\n",IIlIl
->llIlIlI.Endpoint);IlllI(
"\x20\x20\x20\x20\x46\x6c\x61\x67\x73\x3d\x30\x78\x25\x2e\x32\x58" "\n",IIlIl->
llIlIlI.Flags);break;case llIlIlll:IlllI(
"\x55\x4e\x52\x42\x5f\x46\x55\x4e\x43\x54\x49\x4f\x4e\x5f\x47\x45\x54\x5f\x43\x55\x52\x52\x45\x4e\x54\x5f\x46\x52\x41\x4d\x45\x5f\x4e\x55\x4d\x42\x45\x52" "\n"
);IIIIlll(IIlIl);IlllI(
"\x20\x20\x47\x65\x74\x43\x75\x72\x72\x65\x6e\x74\x46\x72\x61\x6d\x65\x4e\x75\x6d\x62\x65\x72" "\n"
);IlllI(
"\x20\x20\x20\x20\x46\x72\x61\x6d\x65\x4e\x75\x6d\x62\x65\x72\x3d\x25\x64" "\n",
IIlIl->IIlIlIII.lIlllIll);break;case IIIIllIl:IlllI(
"\x55\x4e\x52\x42\x5f\x46\x55\x4e\x43\x54\x49\x4f\x4e\x5f\x47\x45\x54\x5f\x50\x4f\x52\x54\x5f\x53\x54\x41\x54\x55\x53" "\n"
);IIIIlll(IIlIl);IlllI(
"\x20\x20\x47\x65\x74\x50\x6f\x72\x74\x53\x74\x61\x74\x75\x73" "\n");switch(
IIlIl->IlIllIll.llllllIl){case IIIllIlll:IlllI(
"\x20\x20\x20\x20\x50\x6f\x72\x74\x53\x74\x61\x74\x75\x73\x3d\x45\x4e\x41\x42\x4c\x45\x44" "\n"
);break;case IlIIlIIll:IlllI(
"\x20\x20\x20\x20\x50\x6f\x72\x74\x53\x74\x61\x74\x75\x73\x3d\x43\x4f\x4e\x4e\x45\x43\x54\x45\x44" "\n"
);break;default:IlllI(
"\x20\x20\x20\x20\x50\x6f\x72\x74\x53\x74\x61\x74\x75\x73\x3d\x75\x6e\x6b\x6e\x6f\x77\x6e" "\n"
);break;}break;case IllIIIll:IlllI(
"\x55\x4e\x52\x42\x5f\x46\x55\x4e\x43\x54\x49\x4f\x4e\x5f\x52\x45\x53\x45\x54\x5f\x50\x4f\x52\x54" "\n"
);IIIIlll(IIlIl);break;case lIIIIlII:IlllI(
"\x55\x4e\x52\x42\x5f\x46\x55\x4e\x43\x54\x49\x4f\x4e\x5f\x43\x41\x4e\x43\x45\x4c" "\n"
);IIIIlll(IIlIl);break;case IIlIlIlI:IlllI(
"\x55\x4e\x52\x42\x5f\x46\x55\x4e\x43\x54\x49\x4f\x4e\x5f\x41\x42\x4f\x52\x54\x5f\x45\x4e\x44\x50\x4f\x49\x4e\x54" "\n"
);IIIIlll(IIlIl);IlllI(
"\x20\x20\x41\x62\x6f\x72\x74\x45\x6e\x64\x70\x6f\x69\x6e\x74" "\n");IlllI(
"\x20\x20\x20\x20\x45\x6e\x64\x70\x6f\x69\x6e\x74\x3d\x25\x64" "\n",IIlIl->
lIIIllll.Endpoint);IlllI(
"\x20\x20\x20\x20\x46\x6c\x61\x67\x73\x3d\x30\x78\x25\x2e\x32\x58" "\n",IIlIl->
lIIIllll.Flags);break;default:IlllI(
"\x55\x4e\x52\x42\x5f\x46\x55\x4e\x43\x54\x49\x4f\x4e\x5f\x75\x6e\x6b\x6e\x6f\x77\x6e" "\n"
);IIIIlll(IIlIl);break;}IlllI(
"\x2d\x2d\x2d\x2d\x20\x55\x4e\x52\x42\x20\x45\x4e\x44" "\n");}static void 
IIIIlll(lIIll IIlIl){IlllI("\x20\x20\x48\x65\x61\x64\x65\x72" "\n");IlllI(
"\x20\x20\x20\x20\x55\x6e\x69\x71\x75\x65\x49\x64\x3d\x30\x78\x25\x2e\x38\x58\x25\x2e\x38\x58" "\n"
,(lllIl)(IIlIl->IIIlI.lIlIlI>>(0xd20+4130-0x1d22)),(lllIl)(IIlIl->IIIlI.lIlIlI))
;IlllI(
"\x20\x20\x20\x20\x53\x63\x72\x69\x70\x74\x3d\x30\x78\x25\x2e\x34\x58" "\n",(
llIIIl)IIlIl->IIIlI.lIlIIll);IlllI(
"\x20\x20\x20\x20\x53\x69\x7a\x65\x3d\x25\x64" "\n",IIlIl->IIIlI.IIIlII);IlllI(
"\x20\x20\x20\x20\x46\x75\x6e\x63\x74\x69\x6f\x6e\x3d\x25\x64" "\n",IIlIl->IIIlI
.IIlIlI);IlllI("\x20\x20\x20\x20\x53\x74\x61\x74\x75\x73\x3d\x25\x64" "\n",IIlIl
->IIIlI.Status);IlllI(
"\x20\x20\x20\x20\x43\x6f\x6e\x74\x65\x78\x74\x3d\x30\x78\x25\x2e\x38\x58" "\n",
IIlIl->IIIlI.Context);}
#endif 

