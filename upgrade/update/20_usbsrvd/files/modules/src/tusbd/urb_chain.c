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
int IIIllIII(struct lllIlI*lIIII,struct urb*IIlIlllI);int lllIlllIl(struct 
lllIlI*lIIII,struct urb*IIlIlllI);void lllllllll(struct urb*lIlll
#if KERNEL_LT((0x5d6+377-0x74d),(0xb44+3159-0x1795),(0xe2b+424-0xfc0))
,struct pt_regs*IIllIII
#endif
);int lIIIIIlll(struct lllIlI*lIIII,int pipe,int interval,int IIIIlIII,int 
lIIIIll,struct usb_device*lIIIIl,struct lIIlIlI*IIIlIIll,void*context,
urb_chain_complete_t complete,gfp_t llllI){int i,IlIlI=(0x17cd+3414-0x2523);
struct usb_host_endpoint*ep;IlllI(
"\x75\x73\x62\x64\x5f\x75\x63\x5f\x69\x6e\x69\x74\x3a\x20\x2b\x2b" "\n");ep=
usb_pipein(pipe)?lIIIIl->ep_in[usb_pipeendpoint(pipe)]:lIIIIl->ep_out[
usb_pipeendpoint(pipe)];if(!ep){IlllI(
"\x75\x73\x62\x64\x5f\x75\x63\x5f\x69\x6e\x69\x74\x3a\x20\x65\x6e\x64\x70\x6f\x69\x6e\x74\x20\x69\x73\x20\x4e\x55\x4c\x4c" "\n"
);IlllI(
"\x75\x73\x62\x64\x5f\x75\x63\x5f\x69\x6e\x69\x74\x3a\x20\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x3d\x2d\x31" "\n"
);return-(0x966+2032-0x1155);}lIIII->pipe=pipe;lIIII->IIIIlIII=IIIIlIII;lIIII->
lIIIIll=lIIIIll;lIIII->lIIIIl=lIIIIl;lIIII->IIlII=IIIlIIll->IIlII;lIIII->status=
(0xfe2+2557-0x19df);lIIII->lIllllIIl=(0x6a0+6929-0x21b1);lIIII->context=context;
lIIII->complete=complete;spin_lock_init(&lIIII->lock);for(i=(0x1630+273-0x1741);
i<lIIII->IIlII;i++){
if(IlIlI<(0x14aa+946-0x185c))break;lIIII->lIlIIl[i]=lIIIIlI(IIIlIIll->
number_of_packets[i],llllI);if(!lIIII->lIlIIl[i]){IIIIll(
"\x75\x73\x62\x64\x5f\x75\x63\x5f\x69\x6e\x69\x74\x3a\x20\x66\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x61\x6c\x6c\x6f\x63\x61\x74\x65\x20\x61\x6e\x20\x75\x72\x62\x20\x2d\x20\x6e\x6f\x20\x6d\x65\x6d\x6f\x72\x79" "\n"
);IlIlI=-ENOMEM;break;}lIIII->lIlIIl[i]->transfer_flags|=URB_NO_INTERRUPT;switch
(usb_pipetype(pipe)){case PIPE_BULK:usb_fill_bulk_urb(lIIII->lIlIIl[i],lIIII->
lIIIIl,pipe,IIIlIIll->transfer_buffer[i],IIIlIIll->transfer_buffer_length[i],
lllllllll,lIIII);if(usb_pipein(pipe))lIIII->lIlIIl[i]->transfer_flags|=
URB_SHORT_NOT_OK;break;case PIPE_ISOCHRONOUS:lIIII->lIlIIl[i]->dev=lIIIIl;lIIII
->lIlIIl[i]->pipe=pipe;lIIII->lIlIIl[i]->transfer_flags=URB_ISO_ASAP;lIIII->
lIlIIl[i]->transfer_buffer=IIIlIIll->transfer_buffer[i];lIIII->lIlIIl[i]->
transfer_buffer_length=IIIlIIll->transfer_buffer_length[i];lIIII->lIlIIl[i]->
start_frame=-(0x271+482-0x452);lIIII->lIlIIl[i]->number_of_packets=IIIlIIll->
number_of_packets[i];lIIII->lIlIIl[i]->context=lIIII;lIIII->lIlIIl[i]->complete=
lllllllll;if(interval){lIIII->lIlIIl[i]->interval=interval;}else{lIIII->lIlIIl[i
]->interval=ep?ep->desc.bInterval:(0x5e8+6236-0x1e43);lIIII->lIlIIl[i]->interval
=(0x143+4761-0x13db)<<(lIIII->lIlIIl[i]->interval-(0xa03+5154-0x1e24));}break;
default:IIIIll(
"\x75\x73\x62\x64\x5f\x75\x63\x5f\x69\x6e\x69\x74\x3a\x20\x69\x6e\x76\x61\x6c\x69\x64\x20\x70\x69\x70\x65\x20\x74\x79\x70\x65" "\n"
);IlIlI=-EINVAL;break;}lIIII->lIlIIl[i]->dev=NULL;
}if(IlIlI==(0x650+2696-0x10d8)){
lIIII->lIlIIl[lIIII->IIlII-(0xadc+81-0xb2c)]->transfer_flags&=~URB_NO_INTERRUPT;
}else{
for(i--;i>=(0x2160+257-0x2261);i--){IlIIllIl(lIIII->lIlIIl[i]);lIIII->lIlIIl[i]=
NULL;}}IlllI(
"\x75\x73\x62\x64\x5f\x75\x63\x5f\x69\x6e\x69\x74\x3a\x20\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x3d\x25\x64" "\n"
,IlIlI);return IlIlI;}

int IlllIIIll(struct lllIlI*lIIII){int i,IlIlI=(0x16b9+1423-0x1c48);IlllI(
"\x75\x73\x62\x64\x5f\x75\x63\x5f\x63\x6c\x65\x61\x6e" "\n");for(i=
(0xbf5+4780-0x1ea1);i<lIIII->IIlII;i++)if(lIIII->lIlIIl[i])IlIIllIl(lIIII->
lIlIIl[i]);return IlIlI;}void lllllllll(struct urb*lIlll
#if KERNEL_LT((0x1089+1269-0x157c),(0x1d40+366-0x1ea8),(0x6f0+6435-0x2000))
,struct pt_regs*IIllIII
#endif
){struct lllIlI*lIIII=lIlll->context;








if(lIlll->status&&lIlll->status!=-ECONNRESET&&lIlll->status!=-ENOENT){int abort=
(0x20d+9338-0x2687);spin_lock(&lIIII->lock);if(lIIII->status==(0x2b9+496-0x4a9))
{
if(lIlll->status==-EREMOTEIO&&lIIII->IIIIlIII){lIIII->status=(0xeb0+5481-0x2419)
;IlllI(
"\x75\x73\x62\x64\x5f\x75\x63\x5f\x75\x72\x62\x5f\x63\x6f\x6d\x70\x6c\x65\x74\x65\x3a\x20\x73\x68\x6f\x72\x74\x20\x74\x72\x61\x6e\x73\x66\x65\x72\x20\x64\x65\x74\x65\x63\x74\x65\x64\x20\x61\x6e\x64\x20\x69\x73\x20\x6f\x6b\x2e\x20\x61\x63\x74\x75\x61\x6c\x5f\x6c\x65\x6e\x67\x74\x68\x3d\x25\x64" "\n"
,lIlll->actual_length);}else{lIIII->status=lIlll->status;IlllI(
"\x75\x73\x62\x64\x5f\x75\x63\x5f\x75\x72\x62\x5f\x63\x6f\x6d\x70\x6c\x65\x74\x65\x3a\x20\x65\x61\x72\x6c\x79\x20\x75\x72\x62\x20\x63\x6f\x6d\x70\x6c\x65\x74\x65\x64\x20\x77\x69\x74\x68\x20\x73\x74\x61\x74\x75\x73\x20\x25\x64" "\n"
,lIlll->status);}abort=(0x256+6767-0x1cc4);}spin_unlock(&lIIII->lock);if(abort)
IIIllIII(lIIII,lIlll);}
#if defined(_USBD_USE_EHCI_FIX_) && KERNEL_GT_EQ((0x1c1c+1026-0x201c),\
(0x11ac+4059-0x2181),(0x177d+2718-0x2202)) && KERNEL_LT_EQ((0x7c3+1349-0xd06),\
(0x14c2+2362-0x1df6),(0x1377+3107-0x1f7e))
if(lIIII->lIIIIll&&usb_pipeisoc(lIlll->pipe)&&lIlll->status==(0x19b3+102-0x1a19)
){if(atomic_read(&lIlll->kref.refcount)>(0x3c4+282-0x4dd))usb_put_urb(lIlll);}
#endif
lIlll->dev=NULL;
lIIII->lIllllIIl+=lIlll->actual_length;
if(atomic_dec_and_test(&lIIII->IllllllIl)){IlllI(
"\x75\x73\x62\x64\x5f\x75\x63\x5f\x75\x72\x62\x5f\x63\x6f\x6d\x70\x6c\x65\x74\x65\x3a\x20\x61\x6c\x6c\x20\x75\x72\x62\x73\x20\x66\x69\x6e\x69\x73\x68\x65\x64\x20\x2d\x20\x63\x6f\x6d\x70\x6c\x65\x74\x69\x6e\x67\x20\x74\x68\x65\x20\x63\x68\x61\x69\x6e" "\n"
);lIIII->complete(lIIII);}}int lIIllIIII(struct lllIlI*lIIII){int i,llllIl,IlIlI
=(0xc2+5155-0x14e5);unsigned long flags;IlllI(
"\x75\x73\x62\x64\x5f\x75\x63\x5f\x73\x75\x62\x6d\x69\x74\x3a\x20\x2b\x2b" "\n")
;atomic_set(&lIIII->IllllllIl,lIIII->IIlII);spin_lock_irqsave(&lIIII->lock,flags
);for(i=(0xc5d+6631-0x2644),llllIl=(0x4ed+2818-0xfef);i<lIIII->IIlII;i++){if(
lIIII->status!=(0x431+5894-0x1b37))break;lIIII->lIlIIl[i]->dev=lIIII->lIIIIl;
IlIlI=usb_submit_urb(lIIII->lIlIIl[i],GFP_ATOMIC);
if(IlIlI!=(0x2c5+418-0x467))lIIII->lIlIIl[i]->dev=NULL;
spin_unlock_irqrestore(&lIIII->lock,flags);if(IlIlI==-ENXIO||IlIlI==-EAGAIN||
IlIlI==-ENOMEM){IlllI(
"\x75\x73\x62\x64\x5f\x75\x63\x5f\x73\x75\x62\x6d\x69\x74\x3a\x20\x72\x65\x74\x72\x79\x69\x6e\x67\x20\x66\x61\x69\x6c\x65\x64\x20\x75\x72\x62" "\n"
);
if(llllIl++<(0x176b+2245-0x2026)){i--;IlIlI=(0x145d+1969-0x1c0e);yield();}}else{
cpu_relax();llllIl=(0x14b1+285-0x15ce);}spin_lock_irqsave(&lIIII->lock,flags);if
(IlIlI!=(0x960+3356-0x167c)){IlllI(
"\x75\x73\x62\x64\x5f\x75\x63\x5f\x73\x75\x62\x6d\x69\x74\x3a\x20\x73\x75\x62\x6d\x69\x74\x20\x66\x61\x69\x6c\x65\x64" "\n"
);lIIII->status=-(0x2e2+4484-0x1465);break;}}spin_unlock_irqrestore(&lIIII->lock
,flags);
if(IlIlI<(0x211+1786-0x90b))IIIllIII(lIIII,NULL);else{int lllIlIIIl=lIIII->IIlII
-i;
if(lllIlIIIl>(0x1f14+1610-0x255e)&&atomic_sub_and_test(lllIlIIIl,&lIIII->
IllllllIl)){IlllI(
"\x75\x73\x62\x64\x5f\x75\x63\x5f\x73\x75\x62\x6d\x69\x74\x3a\x20\x69\x6f\x63\x6f\x6e\x74\x20\x69\x73\x20\x30\x2c\x20\x63\x61\x6c\x6c\x69\x6e\x67\x20\x63\x6f\x6d\x70\x6c\x65\x74\x69\x6f\x6e" "\n"
);lIIII->complete(lIIII);}}IlllI(
"\x75\x73\x62\x64\x5f\x75\x63\x5f\x73\x75\x62\x6d\x69\x74\x3a\x20\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x3d\x25\x64" "\n"
,IlIlI);return IlIlI;}int IIIlIllII(struct lllIlI*lIIII){int i;for(i=
(0x23c4+362-0x252e);i<lIIII->IIlII;i++)usb_get_urb(lIIII->lIlIIl[i]);return
(0x1474+1362-0x19c6);}int IIlIllIIl(struct lllIlI*lIIII){int i;for(i=
(0xef0+1130-0x135a);i<lIIII->IIlII;i++)usb_put_urb(lIIII->lIlIIl[i]);return
(0x587+5200-0x19d7);}int IIlIIIlIl(struct lllIlI*lIIII){unsigned long flags;int 
abort=(0x1777+2338-0x2099);IlllI(
"\x75\x73\x62\x64\x5f\x75\x63\x5f\x75\x6e\x6c\x69\x6e\x6b\x3a\x20\x2b\x2b" "\n")
;spin_lock_irqsave(&lIIII->lock,flags);if(lIIII->status==(0x8d8+3086-0x14e6)){
lIIII->status=-ECONNRESET;abort=(0x1715+3270-0x23da);}spin_unlock_irqrestore(&
lIIII->lock,flags);if(abort)IIIllIII(lIIII,NULL);IlllI(
"\x75\x73\x62\x64\x5f\x75\x63\x5f\x75\x6e\x6c\x69\x6e\x6b\x3a\x20\x2d\x2d" "\n")
;return(0xd72+6241-0x25d3);}int lIllIIIII(struct lllIlI*lIIII){unsigned long 
flags;IlllI(
"\x75\x73\x62\x64\x5f\x75\x63\x5f\x6b\x69\x6c\x6c\x3a\x20\x2b\x2b" "\n");
spin_lock_irqsave(&lIIII->lock,flags);if(lIIII->status==(0xa70+6828-0x251c)){
lIIII->status=-ECONNRESET;}spin_unlock_irqrestore(&lIIII->lock,flags);lllIlllIl(
lIIII,NULL);IlllI(
"\x75\x73\x62\x64\x5f\x75\x63\x5f\x6b\x69\x6c\x6c\x3a\x20\x2d\x2d" "\n");return
(0x93c+5634-0x1f3e);}int lllIlllIl(struct lllIlI*lIIII,struct urb*IIlIlllI){int 
i,lIlIIII=(0x25a+2126-0xaa8);for(i=(0x401+7133-0x1fde);i<lIIII->IIlII;i++){if(!
lIlIIII&&IIlIlllI){if(lIIII->lIlIIl[i]==IIlIlllI)lIlIIII=(0xe77+2996-0x1a2a);}
else{if(lIIII->lIlIIl[i]&&lIIII->lIlIIl[i]->dev)usb_kill_urb(lIIII->lIlIIl[i]);}
}return(0x511+463-0x6e0);}int IIIllIII(struct lllIlI*lIIII,struct urb*IIlIlllI){
int i,lIlIIII=(0x458+2698-0xee2);for(i=(0x13a7+4728-0x261f);i<lIIII->IIlII;i++){
if(!lIlIIII&&IIlIlllI){if(lIIII->lIlIIl[i]==IIlIlllI)lIlIIII=
(0x1562+3761-0x2412);}else{if(lIIII->lIlIIl[i]&&lIIII->lIlIIl[i]->dev)
usb_unlink_urb(lIIII->lIlIIl[i]);}}return(0xd1d+4620-0x1f29);}int IIIlIIIII(
struct lllIlI*lIIII,struct urb*lIlll){int i;for(i=(0xec1+2288-0x17b1);i<lIIII->
IIlII;i++)if(lIIII->lIlIIl[i]==lIlll)break;return(i==lIIII->IIlII)?-
(0x1450+199-0x1516):i;}





int IllllIIIl(struct lIIlIlI*lIIII,size_t length,int lIlIllIl){size_t lIIllIlI,
IllIlIl;int i;IlllI(
"\x75\x73\x62\x64\x5f\x62\x63\x5f\x61\x6c\x6c\x6f\x63\x3a\x20\x2b\x2b" "\n");if(
unlikely(lIlIllIl==(0xc9+9796-0x270d)))return-(0x6f3+4794-0x19ac);if(unlikely(
length==(0x16d1+4067-0x26b4)))return-(0x14a4+3317-0x2198);lIIllIlI=IIIlIlll-(
IIIlIlll%lIlIllIl);IlllI(
"\x75\x73\x62\x64\x5f\x62\x63\x5f\x61\x6c\x6c\x6f\x63\x3a\x20\x70\x61\x72\x74\x73\x69\x7a\x65\x20\x3d\x20\x25\x6c\x75" "\n"
,(unsigned long)lIIllIlI);lIIII->IIlII=(0x972+3210-0x15fc);for(i=
(0x5dc+5078-0x19b2);i<lIlIllII&&length>(0x350+5706-0x199a);i++,length-=IllIlIl){
IllIlIl=min(lIIllIlI,length);IlllI(
"\x75\x73\x62\x64\x5f\x62\x63\x5f\x61\x6c\x6c\x6f\x63\x3a\x20\x61\x6c\x6c\x6f\x63\x61\x74\x69\x6e\x67\x20\x25\x6c\x75\x20\x62\x79\x74\x65\x73" "\n"
,(unsigned long)IllIlIl);lIIII->transfer_buffer[i]=IllllIl(IllIlIl,GFP_KERNEL);
lIIII->transfer_buffer_length[i]=IllIlIl;lIIII->actual_length[i]=
(0x1d88+274-0x1e9a);lIIII->number_of_packets[i]=(0x1cd+7661-0x1fba);if(!lIIII->
transfer_buffer[i]){IlllI(
"\x75\x73\x62\x64\x5f\x62\x63\x5f\x61\x6c\x6c\x6f\x63\x3a\x20\x6b\x6d\x61\x6c\x6c\x6f\x63\x20\x66\x61\x69\x6c\x65\x64" "\n"
);break;}}
if(length)for(i--;i>=(0xcc9+3468-0x1a55);i--){lllIII(lIIII->transfer_buffer[i]);
lIIII->transfer_buffer[i]=NULL;lIIII->transfer_buffer_length[i]=
(0x11d9+1832-0x1901);lIIII->actual_length[i]=(0x9ab+7440-0x26bb);}else lIIII->
IIlII=i;IlllI(
"\x75\x73\x62\x64\x5f\x62\x63\x5f\x61\x6c\x6c\x6f\x63\x3a\x20\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x3d\x25\x64" "\n"
,lIIII->IIlII?(0x61+2420-0x9d5):-(0x34f+8923-0x2629));return lIIII->IIlII?
(0xcc5+960-0x1085):-(0x1519+165-0x15bd);}


int lIIlIIIlI(struct lIIlIlI*lIIII,size_t length,IIIIlII*llIllII,lllIl IllllllI)
{int i,lIIlIIlI;size_t IlIlIIlI;IlllI(
"\x75\x73\x62\x64\x5f\x62\x63\x5f\x61\x6c\x6c\x6f\x63\x5f\x69\x73\x6f\x3a\x20\x2b\x2b\x20\x69\x73\x6f\x70\x61\x63\x6b\x65\x74\x73\x3d\x25\x64\x20\x6c\x65\x6e\x67\x74\x68\x3d\x25\x6c\x75" "\n"
,IllllllI,(unsigned long)length);lIIlIIlI=(0x16aa+3856-0x25ba);lIIII->IIlII=
IlIlIIlI=(0xded+4871-0x20f4);
for(i=(0xff9+5888-0x26f9);i<IllllllI&&lIIII->IIlII<lIlIllII&&length>
(0x1de8+1283-0x22eb);i++){lllIl IIIlIlIIl,lllIlIIlI;int IllllIlI=(i==IllllllI-
(0x8c5+7397-0x25a9));

IIIlIlIIl=llIllII[i].Offset;lllIlIIlI=IllllIlI?llIllII[i].Offset+llIllII[i].
Length:llIllII[i+(0x1d01+1418-0x228a)].Offset;
if(IIIlIlIIl>lllIlIIlI){
IIIIll(
"\x75\x73\x62\x64\x5f\x62\x63\x5f\x61\x6c\x6c\x6f\x63\x5f\x69\x73\x6f\x3a\x20\x42\x55\x47\x21\x21\x21\x20\x4e\x6f\x6e\x2d\x6c\x69\x6e\x65\x61\x72\x20\x69\x73\x6f\x20\x62\x75\x66\x66\x65\x72\x2e\x20\x50\x6c\x65\x61\x73\x65\x20\x72\x65\x70\x6f\x72\x74\x20\x74\x68\x69\x73\x2e" "\n"
);break;}
if((IlIlIIlI+llIllII[i].Length)>IIIlIlll||IllllIlI){size_t IllIlIl;if(IllllIlI)
IlIlIIlI+=llIllII[i].Length;IllIlIl=min(IlIlIIlI,length);lIIII->transfer_buffer[
lIIII->IIlII]=IllllIl(IllIlIl,GFP_KERNEL);lIIII->transfer_buffer_length[lIIII->
IIlII]=IllIlIl;lIIII->actual_length[lIIII->IIlII]=(0x1546+1586-0x1b78);lIIII->
number_of_packets[lIIII->IIlII]=(i-lIIlIIlI);if(IllllIlI)lIIII->
number_of_packets[lIIII->IIlII]++;IlllI(
"\x75\x73\x62\x64\x5f\x62\x63\x5f\x61\x6c\x6c\x6f\x63\x5f\x69\x73\x6f\x3a\x20\x61\x6c\x6c\x6f\x63\x61\x74\x69\x6e\x67\x20\x62\x75\x66\x66\x65\x72\x20\x25\x6c\x75\x20\x62\x79\x74\x65\x73\x2c\x20\x6e\x75\x6d\x62\x65\x72\x5f\x6f\x66\x5f\x70\x61\x63\x6b\x65\x74\x73\x3d\x25\x64" "\n"
,(unsigned long)IllIlIl,lIIII->number_of_packets[lIIII->IIlII]);if(!lIIII->
transfer_buffer[lIIII->IIlII]){IlllI(
"\x75\x73\x62\x64\x5f\x62\x63\x5f\x61\x6c\x6c\x6f\x63\x5f\x69\x73\x6f\x3a\x20\x6b\x6d\x61\x6c\x6c\x6f\x63\x20\x66\x61\x69\x6c\x65\x64" "\n"
);break;}lIIII->IIlII++;length-=IllIlIl;IlIlIIlI=(0xe16+4978-0x2188);lIIlIIlI=i;
}IlIlIIlI+=llIllII[i].Length;}
if(i<IllllllI){for(i=(0x507+5945-0x1c40);i<lIIII->IIlII;i++){lllIII(lIIII->
transfer_buffer[i]);lIIII->transfer_buffer[i]=NULL;lIIII->transfer_buffer_length
[i]=(0x533+4606-0x1731);lIIII->actual_length[i]=(0x1bd8+1157-0x205d);lIIII->
number_of_packets[i]=(0x6d2+278-0x7e8);}lIIII->IIlII=(0x13d8+2657-0x1e39);}IlllI
(
"\x75\x73\x62\x64\x5f\x62\x63\x5f\x61\x6c\x6c\x6f\x63\x5f\x69\x73\x6f\x3a\x20\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x3d\x25\x64" "\n"
,lIIII->IIlII?(0x1ba2+1107-0x1ff5):-(0x468+4761-0x1700));return lIIII->IIlII?
(0x3b2+7674-0x21ac):-(0xa77+2878-0x15b4);}int IlIlIllII(struct lIIlIlI*lIIII,
const void*llIlI,size_t length){int i;size_t lIIlII,IlIlI=(0x13fa+4495-0x2589);
IlllI(
"\x75\x73\x62\x64\x5f\x62\x63\x5f\x63\x6f\x70\x79\x5f\x66\x72\x6f\x6d\x5f\x75\x73\x65\x72\x3a\x20\x63\x6f\x75\x6e\x74\x3d\x25\x64" "\n"
,lIIII->IIlII);for(i=(0x13f3+3259-0x20ae);i<lIIII->IIlII&&length>
(0x15b7+1848-0x1cef);i++){lIIlII=min(length,lIIII->transfer_buffer_length[i]);if
(__copy_from_user(lIIII->transfer_buffer[i],llIlI,lIIlII)!=(0xddd+1087-0x121c)){
IlllI(
"\x75\x73\x62\x64\x5f\x62\x63\x5f\x63\x6f\x70\x79\x5f\x66\x72\x6f\x6d\x5f\x75\x73\x65\x72\x3a\x20\x63\x61\x6e\x6e\x6f\x74\x20\x63\x6f\x70\x79\x20\x66\x72\x6f\x6d\x20\x75\x73\x65\x72\x20\x62\x75\x66\x66\x65\x72" "\n"
);break;}lIIII->actual_length[i]=lIIlII;llIlI+=lIIlII;length-=lIIlII;IlIlI+=
lIIlII;}return IlIlI;}int IIIlIllIl(struct lIIlIlI*lIIII,void*llIlI,size_t 
length){int i;size_t lIIlII,IlIlI=(0x10b0+4214-0x2126);IlllI(
"\x75\x73\x62\x64\x5f\x62\x63\x5f\x63\x6f\x70\x79\x5f\x74\x6f\x5f\x75\x73\x65\x72\x3a\x20\x63\x6f\x75\x6e\x74\x3d\x25\x64" "\n"
,lIIII->IIlII);for(i=(0x130a+525-0x1517);i<lIIII->IIlII&&length>
(0xc1b+1063-0x1042);i++){lIIlII=min(length,lIIII->actual_length[i]);if(
__copy_to_user(llIlI,lIIII->transfer_buffer[i],lIIlII)!=(0x434+1136-0x8a4)){
IlllI(
"\x75\x73\x62\x64\x5f\x62\x63\x5f\x63\x6f\x70\x79\x5f\x74\x6f\x5f\x75\x73\x65\x72\x3a\x20\x63\x61\x6e\x6e\x6f\x74\x20\x63\x6f\x70\x79\x20\x66\x72\x6f\x6d\x20\x75\x73\x65\x72\x20\x62\x75\x66\x66\x65\x72" "\n"
);break;}llIlI+=lIIlII;length-=lIIlII;IlIlI+=lIIlII;}return IlIlI;}int IlIlllIII
(struct lIIlIlI*lIIII){int i;for(i=(0x13a+6018-0x18bc);i<lIIII->IIlII;i++){if(
lIIII->transfer_buffer[i]){lllIII(lIIII->transfer_buffer[i]);lIIII->
transfer_buffer[i]=NULL;lIIII->transfer_buffer_length[i]=(0x1e36+1150-0x22b4);
lIIII->actual_length[i]=(0x245+2601-0xc6e);lIIII->number_of_packets[i]=
(0x785+7114-0x234f);}}return(0xf63+2527-0x1942);}
#endif 

