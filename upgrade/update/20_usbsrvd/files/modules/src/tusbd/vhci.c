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
#include <linux/platform_device.h>
#include <linux/dma-mapping.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/highmem.h>
#include <asm/page.h>
#include <asm/unaligned.h>
struct IllllI*IlIIIlll=NULL;struct usb_hcd*llllIII=NULL;
#if KERNEL_GT_EQ((0xfcb+2468-0x196d),(0xcbf+5612-0x22a5),(0x12cf+3641-0x20e1)) \
|| RHEL_RELEASE_GT_EQ((0x1291+4250-0x2325),(0xcab+1605-0x12ed)) 
struct usb_hcd*IlIIlIl=NULL;
#define lIIIlll(IlllII) (((IlllII)->speed == HCD_USB3) ? "\x75\x73\x62\x33" : \
"\x75\x73\x62\x32")
#else
#define lIIIlll(IlllII) "\x55\x53\x42\x32"
#endif
#if defined(CONFIG_X86_32) && !defined(_USBD_VHCI_NO_DMA_)
int IIIlllII=(0x28+9241-0x2441);
#endif
#ifdef _USBD_DEBUG_MEMORY_
extern atomic_t llIIIlIlI;extern atomic_t IlllIlIlI;extern atomic_t lIlIlIIIl;
extern atomic_t IlIllIlI;extern atomic_t lIIlllIII;
#endif 


static int lIlllIIlI(struct platform_device*);static int lIIIlIIlI(struct 
platform_device*);static void IIlIlIIIl(struct device*dev);static int IllllIlll(
struct usb_hcd*IIlll);static int IIIllllII(struct usb_hcd*IIlll);static void 
llIIIlIII(struct usb_hcd*IIlll);static int lIIIlllIl(struct usb_hcd*IIlll);
#if KERNEL_LT((0x343+7921-0x2232),(0x423+8561-0x258e),(0x667+3773-0x150c))
static int lIIlIlll(struct usb_hcd*IIlll,struct urb*urb);static int IlllllIl(
struct usb_hcd*IIlll,struct usb_host_endpoint*ep,struct urb*urb,gfp_t llllI);
#else
static int lIIlIlll(struct usb_hcd*IIlll,struct urb*urb,int status);static int 
IlllllIl(struct usb_hcd*IIlll,struct urb*urb,gfp_t llllI);
#endif
static void llllIllIl(struct usb_hcd*IIlll,struct usb_host_endpoint*ep);static 
int lIIIllIll(struct usb_hcd*IIlll,u16 llIllIlI,u16 wValue,u16 wIndex,char*llIlI
,u16 wLength);static int IIlllIIII(struct usb_hcd*IIlll,char*llIlI);static int 
lIlIIIIII(struct usb_hcd*IIlll);static int lIlIlIlll(struct usb_hcd*IIlll);
#if KERNEL_GT_EQ((0x4f0+6240-0x1d4e),(0x16eb+2679-0x215c),(0x7b1+3309-0x1477)) \
|| RHEL_RELEASE_GT_EQ((0xa67+868-0xdc5),(0x6d1+3598-0x14dc)) 
static int llIIIIIlI(struct usb_hcd*IIlll,struct usb_device*IlIIl,struct 
usb_host_endpoint**lIlIllll,unsigned int IlIllllII,unsigned int IlIIIIllI,gfp_t 
llllI);static int IllIIIlll(struct usb_hcd*IIlll,struct usb_device*IlIIl,struct 
usb_host_endpoint**lIlIllll,unsigned int IlIllllII,gfp_t llllI);
#endif
static int IIIlIlIll(struct IllIlI*Illll,int lIIlI,int IlllIll,int llIIllI);
static int llllIlllI(struct IllIlI*Illll,int lIIlI,int IlllIll);static void 
lIlllI(struct IllIlI*Illll,int lIIlI,int llIllIl);static void lIlIlII(struct 
IllIlI*Illll,int lIIlI,int IlIIII,int llIIllI);
#if KERNEL_GT_EQ((0x2243+943-0x25f0),(0x12af+1147-0x1724),(0xcf0+5141-0x20de)) \
|| RHEL_RELEASE_GT_EQ((0x15a1+783-0x18aa),(0x10cd+5120-0x24ca)) 
static int lllIllIII(struct IllIlI*Illll,int lIIlI,int IlllIll,int llIIllI);
static int IlIlllIIl(struct IllIlI*Illll,int lIIlI,int IlllIll);static void 
lIIIlII(struct IllIlI*Illll,int lIIlI,int IlIIII,int llIIllI);static void 
IlIIlII(struct IllIlI*Illll,int lIIlI,int llIllIl);static void IIlIlII(struct 
IllIlI*Illll,int lIIlI,int IlIIlIIIl);
#endif
#define IIllII(IIlll) ((struct IllIlI*)(IIlll->hcd_priv))
static struct platform_driver lIllIllI={.probe=lIlllIIlI,.remove=lIIIlIIlI,.
driver={.name=llIIIll,.owner=THIS_MODULE,},};static struct platform_device 
lIllIlII={.name=llIIIll,.id=-(0xabf+7-0xac5),.dev={
.release=IIlIlIIIl,},};static struct hc_driver llIlllIlI={.description=llIIIll,.
product_desc=
"\x56\x69\x72\x74\x75\x61\x6c\x20\x55\x53\x42\x20\x48\x6f\x73\x74\x20\x43\x6f\x6e\x74\x72\x6f\x6c\x6c\x65\x72"
,.hcd_priv_size=sizeof(struct IllIlI),
#if KERNEL_GT_EQ((0x113b+5017-0x24d2),(0xf54+577-0x118f),(0x1533+1878-0x1c62)) \
|| RHEL_RELEASE_GT_EQ((0x9a3+1669-0x1022),(0xf11+1450-0x14b8)) 
.flags=HCD_USB3|HCD_SHARED,
#else
.flags=HCD_USB2,
#endif
.reset=IllllIlll,.start=IIIllllII,.stop=llIIIlIII,.urb_enqueue=IlllllIl,.
urb_dequeue=lIIlIlll,.endpoint_disable=llllIllIl,.get_frame_number=lIIIlllIl,.
hub_status_data=IIlllIIII,.hub_control=lIIIllIll,.bus_suspend=lIlIIIIII,.
bus_resume=lIlIlIlll,
#if KERNEL_GT_EQ((0xf9b+5637-0x259e),(0xeb2+2529-0x188d),(0x9f5+4637-0x1beb)) ||\
 RHEL_RELEASE_GT_EQ((0x1e0b+347-0x1f60),(0x140c+253-0x1506)) 
.alloc_streams=llIIIIIlI,.free_streams=IllIIIlll,
#endif
};static struct list_head lllllll;static spinlock_t lIIIII;
#if defined(CONFIG_X86_32) && !defined(_USBD_VHCI_NO_DMA_)
#  if KERNEL_LT((0xaf0+1795-0x11f1),(0x413+4223-0x148c),(0xdcb+2539-0x179e))
static u64 IlIllIllI=DMA_32BIT_MASK;
#  else
static u64 IlIllIllI=DMA_BIT_MASK((0xad+8609-0x222e));
#  endif
#endif
static int lIlllIIlI(struct platform_device*lIIIIl){struct IllIlI*Illll;int 
IlIlI=(0x1641+886-0x19b7);int i;IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x70\x6c\x61\x74\x66\x6f\x72\x6d\x5f\x64\x72\x69\x76\x65\x72\x5f\x70\x72\x6f\x62\x65\x3a\x20\x2b\x2b" "\n"
);do{if(lIIIIl->dev.dma_mask){IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x70\x6c\x61\x74\x66\x6f\x72\x6d\x5f\x64\x72\x69\x76\x65\x72\x5f\x70\x72\x6f\x62\x65\x3a\x20\x64\x6d\x61\x20\x6e\x6f\x74\x20\x73\x75\x70\x70\x6f\x72\x74\x65\x64\x21" "\n"
);return-EINVAL;}
#if defined(CONFIG_X86_32) && !defined(_USBD_VHCI_NO_DMA_)
if(IIIlllII)lIIIIl->dev.dma_mask=&IlIllIllI;
#endif

llllIII=usb_create_hcd(&llIlllIlI,&lIIIIl->dev,IlIIlI(&lIIIIl->dev));if(llllIII
==NULL){IlIlI=-ENOMEM;break;}
#if KERNEL_GT_EQ((0xe06+484-0xfe8),(0x691+4376-0x17a3),(0xd13+6148-0x24fd))
llllIII->has_tt=(0x1a18+2267-0x22f2);
#endif
Illll=IIllII(llllIII);memset(Illll,(0x2401+432-0x25b1),sizeof(*Illll));Illll->
IIlll=llllIII;spin_lock_init(&Illll->lock);for(i=(0x1d26+433-0x1ed7);i<llIlll;i
++){lIlIlII(Illll,i,llIIlIll,(0xe80+6147-0x2683));}IlIlI=usb_add_hcd(llllIII,
(0x9ca+6460-0x2306),(0xb2c+5506-0x20ae));if(IlIlI!=(0x83c+7083-0x23e7)){break;}
#if KERNEL_GT_EQ((0x1588+3084-0x2192),(0x1123+3297-0x1dfe),(0x5d1+5314-0x1a6c)) \
|| RHEL_RELEASE_GT_EQ((0x1ad9+3052-0x26bf),(0x1031+3254-0x1ce4)) 

IlIIlIl=usb_create_shared_hcd(&llIlllIlI,&lIIIIl->dev,IlIIlI(&lIIIIl->dev),
llllIII);if(IlIIlIl==NULL){IlIlI=-ENOMEM;break;}Illll=IIllII(IlIIlIl);memset(
Illll,(0x1111+4746-0x239b),sizeof(*Illll));Illll->IIlll=IlIIlIl;spin_lock_init(&
Illll->lock);for(i=(0xe44+4149-0x1e79);i<llIlll;i++){lIIIlII(Illll,i,llIIlIll,
(0x5c2+3945-0x152b));}IlIlI=usb_add_hcd(IlIIlIl,(0x1686+4176-0x26d6),
(0x339+615-0x5a0));if(IlIlI!=(0xc46+5040-0x1ff6)){break;}IIllII(llllIII)->
IllIIllI=IlIIlIl;IIllII(IlIIlIl)->IllIIllI=llllIII;
#endif 
}while((0x5b4+7578-0x234e));if(IlIlI!=(0x1ca7+1130-0x2111)){if(llllIII){
usb_put_hcd(llllIII);llllIII=NULL;}
#if KERNEL_GT_EQ((0x1239+4682-0x2481),(0x2a9+3659-0x10ee),(0x1499+2260-0x1d46)) \
|| RHEL_RELEASE_GT_EQ((0x149a+1598-0x1ad2),(0x121f+2772-0x1cf0)) 
if(IlIIlIl){usb_put_hcd(IlIIlIl);IlIIlIl=NULL;}
#endif
}IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x70\x6c\x61\x74\x66\x6f\x72\x6d\x5f\x64\x72\x69\x76\x65\x72\x5f\x70\x72\x6f\x62\x65\x3a\x20\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x20\x3d\x20\x25\x64" "\n"
,IlIlI);return IlIlI;}static int lIIIlIIlI(struct platform_device*lIIIIl){struct
 usb_hcd*IIlll=platform_get_drvdata(lIIIIl);struct IllIlI*Illll=IIllII(IIlll);
IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x70\x6c\x61\x74\x66\x6f\x72\x6d\x5f\x64\x72\x69\x76\x65\x72\x5f\x72\x65\x6d\x6f\x76\x65\x5b\x25\x73\x5d\x3a\x20\x2b\x2b" "\n"
,lIIIlll(IIlll));if(Illll->IllIIllI){usb_remove_hcd(Illll->IllIIllI);usb_put_hcd
(Illll->IllIIllI);Illll->IllIIllI=NULL;}usb_remove_hcd(IIlll);usb_put_hcd(IIlll)
;IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x70\x6c\x61\x74\x66\x6f\x72\x6d\x5f\x64\x72\x69\x76\x65\x72\x5f\x72\x65\x6d\x6f\x76\x65\x3a\x20\x2d\x2d" "\n"
);return(0x1c43+393-0x1dcc);}static void IIlIlIIIl(struct device*dev){return;}
static int IllllIlll(struct usb_hcd*IIlll){IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x72\x65\x73\x65\x74\x5b\x25\x73\x5d" "\n"
,lIIIlll(IIlll));


#if KERNEL_GT_EQ((0x19b3+2314-0x22bb),(0x1ed6+1584-0x2500),(0x126d+2414-0x1bb4))\
 || RHEL_RELEASE_GT_EQ((0x1a69+288-0x1b83),(0x1e0+591-0x42c)) 
if(usb_hcd_is_primary_hcd(IIlll)){
IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x72\x65\x73\x65\x74\x3a\x20\x73\x65\x74\x74\x69\x6e\x67\x20\x75\x70\x20\x55\x53\x42\x32\x20\x68\x63\x64" "\n"
);IIlll->speed=HCD_USB2;IIlll->self.root_hub->speed=USB_SPEED_HIGH;}
#endif
return(0xecd+4259-0x1f70);}static int IIIllllII(struct usb_hcd*IIlll){int i;
IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x73\x74\x61\x72\x74\x5b\x25\x73\x5d" "\n"
,lIIIlll(IIlll));IIlll->power_budget=(0xa81+1435-0x101c);IIlll->state=
HC_STATE_RUNNING;IIlll->uses_new_polling=(0x397+4812-0x1662);for(i=
(0x4fb+3968-0x147b);i<llIlll;i++){
#if KERNEL_GT_EQ((0x1418+59-0x1451),(0x70b+691-0x9b8),(0xc89+525-0xe6f)) || \
RHEL_RELEASE_GT_EQ((0x1c1+6460-0x1af7),(0xae6+1713-0x1194)) 
if(IIlll->speed==HCD_USB3){lIIIlII(IIllII(IIlll),i,IIIIIlIl,(0xffd+1141-0x1472))
;}else
#endif
{lIlIlII(IIllII(IIlll),i,IIIIIlIl,(0xcc6+3388-0x1a02));}}return
(0x828+2108-0x1064);}static void llIIIlIII(struct usb_hcd*IIlll){int i;IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x73\x74\x6f\x70\x5b\x25\x73\x5d" "\n",
lIIIlll(IIlll));for(i=(0x436+7503-0x2185);i<llIlll;i++){
#if KERNEL_GT_EQ((0xe0+4904-0x1406),(0x669+7466-0x238d),(0x530+2796-0xff5)) || \
RHEL_RELEASE_GT_EQ((0x2b1+6223-0x1afa),(0xc14+1724-0x12cd)) 
if(IIlll->speed==HCD_USB3){lIIIlII(IIllII(IIlll),i,lllIIlII,(0xab3+6901-0x25a8))
;}else
#endif
{lIlIlII(IIllII(IIlll),i,lllIIlII,(0x1432+1993-0x1bfb));}}}static int lIIIlllIl(
struct usb_hcd*IIlll){IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x67\x65\x74\x5f\x66\x72\x61\x6d\x65\x5f\x6e\x75\x6d\x62\x65\x72\x5b\x25\x73\x5d" "\n"
,lIIIlll(IIlll));return(0x27d+4284-0x1339);}int IllIllllI(struct lIlIl*lllll,
struct IlllIl**lIlllIII,struct urb*lIlll){IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x61\x64\x64\x5f\x75\x72\x62\x3a\x20\x75\x72\x62\x3d\x25\x70" "\n"
,lIlll);if(*lIlllIII){struct llIIIIl*IIlllI;IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x61\x64\x64\x5f\x75\x72\x62\x3a\x20\x65\x78\x69\x73\x74\x69\x6e\x67\x20\x70\x76\x72\x65\x71" "\n"
);IIlllI=IllllIl(sizeof(struct llIIIIl),GFP_ATOMIC);if(IIlllI){IIlllI->lIlll=
lIlll;list_add_tail(&IIlllI->llllII,&(*lIlllIII)->lIIIIIl);}else{IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x61\x64\x64\x5f\x75\x72\x62\x3a\x20\x6e\x6f\x20\x6d\x65\x6d\x6f\x72\x79\x20\x66\x6f\x72\x20\x75\x72\x62\x5f\x6c\x69\x73\x74" "\n"
);return-ENOMEM;}}else{IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x61\x64\x64\x5f\x75\x72\x62\x3a\x20\x6e\x65\x77\x20\x70\x76\x72\x65\x71" "\n"
);*lIlllIII=IIlIIIlII(lllll,GFP_ATOMIC);if(*lIlllIII==NULL){IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x61\x64\x64\x5f\x75\x72\x62\x3a\x20\x6e\x6f\x20\x6d\x65\x6d\x6f\x72\x79\x20\x66\x6f\x72\x20\x71\x75\x65\x75\x65\x5f\x65\x6e\x74\x72\x79" "\n"
);return-ENOMEM;}else{(*lIlllIII)->urb.lIlll=lIlll;list_add_tail(&(*lIlllIII)->
urb.llllII,&(*lIlllIII)->lIIIIIl);}}return(0x380+8897-0x2641);}
#if KERNEL_LT((0xd51+5247-0x21ce),(0x123c+3322-0x1f30),(0x90+5275-0x1513))
static int IlllllIl(struct usb_hcd*IIlll,struct usb_host_endpoint*ep,struct urb*
urb,gfp_t llllI)
#else
static int IlllllIl(struct usb_hcd*IIlll,struct urb*urb,gfp_t llllI)
#endif
{int IlIlI=-EINPROGRESS;struct IllIlI*Illll=IIllII(IIlll);struct lIlIl*lllll=
NULL;struct IlllIl*IllII=NULL;unsigned long flags;int IIllIIlll=
(0x15c8+3287-0x229f);IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x75\x72\x62\x5f\x65\x6e\x71\x75\x65\x75\x65\x5b\x25\x73\x5d\x3a\x20\x2b\x2b\x20\x75\x72\x62\x3d\x30\x78\x25\x70\x20\x75\x73\x62\x5f\x64\x65\x76\x69\x63\x65\x3d\x30\x78\x25\x70\x20\x70\x61\x72\x65\x6e\x74\x3d\x30\x78\x25\x70\x20\x64\x65\x76\x6e\x75\x6d\x3d\x25\x64\x20\x6e\x75\x6d\x5f\x73\x67\x73\x3d\x25\x64" "\n"
,lIIIlll(IIlll),urb,urb->dev,urb->dev->dev.parent,urb->dev->devnum,
#if KERNEL_GT_EQ((0x1560+1485-0x1b2b),(0xd5c+5708-0x23a2),(0x5e6+4679-0x180e))
urb->num_sgs);
#else
(0xbb7+2417-0x1528));
#endif
IlIlIIll(urb,(0xd6f+6355-0x2642));do
{
#if KERNEL_GT_EQ((0x3d0+893-0x74b),(0xac9+2634-0x150d),(0x8db+5623-0x1eba))
struct usb_host_endpoint*ep=urb->ep;
#endif
spin_lock_irqsave(&Illll->lock,flags);
#if KERNEL_GT_EQ((0x94+7058-0x1c24),(0x126a+2420-0x1bd8),(0xb8a+754-0xe64))


IlIlI=usb_hcd_link_urb_to_ep(IIlll,urb);
#else
spin_lock(&urb->lock);IlIlI=(urb->status==-EINPROGRESS)?(0x11a4+4194-0x2206):urb
->status;spin_unlock(&urb->lock);
#endif
if(IlIlI!=(0xd9d+5958-0x24e3)){spin_unlock_irqrestore(&Illll->lock,flags);IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x75\x72\x62\x5f\x65\x6e\x71\x75\x65\x75\x65\x3a\x20\x75\x72\x62\x20\x61\x6c\x72\x65\x61\x64\x79\x20\x75\x6e\x6c\x69\x6e\x6b\x65\x64" "\n"
);break;}
#if KERNEL_GT_EQ((0x3f8+7636-0x21ca),(0x14b1+4095-0x24aa),(0x1dd0+635-0x2024)) \
|| RHEL_RELEASE_GT_EQ((0x2336+673-0x25d1),(0x14f9+2180-0x1d7a)) 








if(IIlll->speed==HCD_USB3){
lllll=lIIIIIIll(IIlll,urb->dev->portnum);}else
#endif
{
lllll=IlIIIIIlI(IIlll,usb_pipedevice(urb->pipe));}if(lllll==NULL){
#if KERNEL_GT_EQ((0xb60+2363-0x1499),(0x88f+5164-0x1cb5),(0x1c93+1955-0x241e))
usb_hcd_unlink_urb_from_ep(IIlll,urb);
#endif
spin_unlock_irqrestore(&Illll->lock,flags);IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x75\x72\x62\x5f\x65\x6e\x71\x75\x65\x75\x65\x3a\x20\x64\x65\x76\x69\x63\x65\x20\x6e\x6f\x74\x20\x66\x6f\x75\x6e\x64" "\n"
);IlIlI=-ENODEV;break;}if(usb_pipedevice(urb->pipe)==(0x2143+694-0x23f9)&&
usb_pipetype(urb->pipe)==PIPE_CONTROL){struct usb_ctrlrequest*lIIlIl=(struct 
usb_ctrlrequest*)urb->setup_packet;if(!lIIlIl){
#if KERNEL_GT_EQ((0x2fd+1724-0x9b7),(0x1735+196-0x17f3),(0x1f48+256-0x2030))
usb_hcd_unlink_urb_from_ep(IIlll,urb);
#endif
spin_unlock_irqrestore(&Illll->lock,flags);IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x75\x72\x62\x5f\x65\x6e\x71\x75\x65\x75\x65\x3a\x20\x69\x6e\x76\x61\x6c\x69\x64\x20\x63\x6f\x6e\x74\x72\x6f\x6c\x20\x74\x72\x61\x6e\x73\x66\x65\x72\x20\x75\x72\x62" "\n"
);IlIlI=-EINVAL;break;}if(lIIlIl->bRequest==USB_REQ_SET_ADDRESS){IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x75\x72\x62\x5f\x65\x6e\x71\x75\x65\x75\x65\x3a\x20\x55\x53\x42\x5f\x52\x45\x51\x5f\x53\x45\x54\x5f\x41\x44\x44\x52\x45\x53\x53\x20\x61\x64\x64\x72\x65\x73\x73\x3d\x25\x64" "\n"
,lIIlIl->wValue);lllll->llllIlI=le16_to_cpu(lIIlIl->wValue);
#if KERNEL_GT_EQ((0x12c9+3534-0x2095),(0xb92+5929-0x22b5),(0x1a00+1908-0x215c))
usb_hcd_unlink_urb_from_ep(IIlll,urb);
#endif
spin_unlock(&Illll->lock);
#if KERNEL_LT((0xd7c+3754-0x1c24),(0x1a87+2420-0x23f5),(0xa6c+1084-0xe90))

spin_lock(&urb->lock);if(urb->status==-EINPROGRESS)urb->status=
(0x187b+3691-0x26e6);spin_unlock(&urb->lock);
#else

#endif
#if KERNEL_LT((0xde8+2695-0x186d),(0xb2f+4451-0x1c8c),(0xf74+4089-0x1f5a))
usb_hcd_giveback_urb(lllll->parent,urb,NULL);
#elif KERNEL_LT((0x4f2+5811-0x1ba3),(0xefa+4513-0x2095),(0x1ac+5336-0x166c))
usb_hcd_giveback_urb(lllll->parent,urb);
#else
usb_hcd_giveback_urb(lllll->parent,urb,(0x1425+486-0x160b));
#endif
local_irq_restore(flags);IlIlI=(0x1379+2941-0x1ef6);break;}}IllII=ep->hcpriv;
IlIlI=IllIllllI(lllll,&IllII,urb);if(IlIlI!=(0x69d+2409-0x1006)){
#if KERNEL_GT_EQ((0x3b+5654-0x164f),(0x136f+2504-0x1d31),(0x1349+2851-0x1e54))
usb_hcd_unlink_urb_from_ep(IIlll,urb);
#endif
spin_unlock_irqrestore(&Illll->lock,flags);break;}urb->hcpriv=IllII;if((
usb_pipetype(urb->pipe)==PIPE_BULK)&&(urb->transfer_flags&URB_NO_INTERRUPT)&&((
usb_pipein(urb->pipe)&&(urb->transfer_flags&URB_SHORT_NOT_OK))||(usb_pipeout(urb
->pipe)&&!(urb->transfer_flags&URB_ZERO_PACKET)))){IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x75\x72\x62\x5f\x65\x6e\x71\x75\x65\x75\x65\x3a\x20\x6d\x65\x72\x67\x65\x20\x73\x70\x6c\x69\x74\x74\x65\x64\x20\x75\x72\x62" "\n"
);if(ep->hcpriv==NULL){ep->hcpriv=IllII;
spin_lock(&lllll->llllll);list_add_tail(&IllII->IlIlIl,&lllll->lIlIIlI);
spin_unlock(&lllll->llllll);}}else{spin_lock(&lllll->llllll);if(ep->hcpriv){ep->
hcpriv=NULL;
list_del(&IllII->IlIlIl);}list_add_tail(&IllII->IlIlIl,&lllll->IllIIll);
IIllIIlll=(0x1858+3317-0x254c);spin_unlock(&lllll->llllll);}
spin_unlock_irqrestore(&Illll->lock,flags);if(IIllIIlll){wake_up(&lllll->lllIll)
;}IlIlI=-EINPROGRESS;}while((0x142c+4660-0x2660));if(lllll){
lllllIll(lllll);}if(IlIlI==-EINPROGRESS){
IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x75\x72\x62\x5f\x65\x6e\x71\x75\x65\x75\x65\x3a\x20\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x3d\x25\x64" "\n"
,(0xc65+2806-0x175b));return(0xaec+2884-0x1630);}IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x75\x72\x62\x5f\x65\x6e\x71\x75\x65\x75\x65\x3a\x20\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x3d\x25\x64" "\n"
,IlIlI);return IlIlI;}
#if KERNEL_LT((0x29c+2422-0xc10),(0x964+1401-0xed7),(0x777+3528-0x1527))
static int lIIlIlll(struct usb_hcd*IIlll,struct urb*urb)
#else
static int lIIlIlll(struct usb_hcd*IIlll,struct urb*urb,int status)
#endif
{struct IllIlI*Illll=IIllII(IIlll);struct IlllIl*IllII;lIIll IIlIl;int IlIlI=
(0x1385+798-0x16a3);int unlinked;unsigned long flags;IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x75\x72\x62\x5f\x64\x65\x71\x75\x65\x75\x65\x5b\x25\x73\x5d\x3a\x20\x2b\x2b\x20\x75\x72\x62\x3d\x30\x78\x25\x70" "\n"
,lIIIlll(IIlll),urb);do{spin_lock_irqsave(&Illll->lock,flags);
#if KERNEL_GT_EQ((0x9fa+2333-0x1315),(0x391+4095-0x138a),(0x11c+5791-0x17a3))
IlIlI=usb_hcd_check_unlink_urb(IIlll,urb,status);if(IlIlI!=(0x1e8b+131-0x1f0e)){

spin_unlock_irqrestore(&Illll->lock,flags);break;}
#endif
IllII=(struct IlllIl*)urb->hcpriv;if(!IllII){

IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x75\x72\x62\x5f\x64\x65\x71\x75\x65\x75\x65\x3a\x20\x6e\x6f\x20\x64\x65\x76\x69\x63\x65\x21" "\n"
);spin_unlock_irqrestore(&Illll->lock,flags);break;}spin_lock(&IllII->lllll->
llllll);unlinked=IlllIIlIl(IllII);spin_unlock(&IllII->lllll->llllll);
spin_unlock_irqrestore(&Illll->lock,flags);if(unlinked){
#if KERNEL_LT((0x1313+2593-0x1d32),(0x17c7+3536-0x2591),(0x1af+12-0x1a3))
lIllIIIl(IllII,-ECONNRESET);
#else
lIllIIIl(IllII,status);
#endif
IIlIl=IllllIl(sizeof(IIIllIlI),GFP_ATOMIC);if(!IIlIl){IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x75\x72\x62\x5f\x64\x65\x71\x75\x65\x75\x65\x3a\x20\x6e\x6f\x20\x6d\x65\x6d\x6f\x72\x79\x20\x66\x6f\x72\x20\x75\x6e\x72\x62" "\n"
);IlllIIII(IllII);break;}IIlIl->IIIlI.lIlIlI=IllII->lIIIl;IIlIl->IIIlI.lIlIIll=
(0x213c+548-0x2360);IIlIl->IIIlI.IIIlII=sizeof(IIIllIlI);IIlIl->IIIlI.IIlIlI=
lIIIIlII;IIlIl->IIIlI.Status=(0x114+101-0x179);IIlIl->IIIlI.Context=
(0x167b+2769-0x214c);INIT_LIST_HEAD(&IllII->lIIIIIl);IllII->urb.lIlll=NULL;IllII
->IIlIl=IIlIl;spin_lock_irqsave(&IllII->lllll->llllll,flags);list_add_tail(&
IllII->IlIlIl,&IllII->lllll->IllIIll);spin_unlock_irqrestore(&IllII->lllll->
llllll,flags);wake_up(&IllII->lllll->lllIll);}else{

IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x75\x72\x62\x5f\x64\x65\x71\x75\x65\x75\x65\x3a\x20\x75\x72\x62\x20\x6e\x6f\x74\x20\x66\x6f\x75\x6e\x64\x20\x69\x6e\x20\x71\x75\x65\x75\x65" "\n"
);}}while((0x7f7+1331-0xd2a));IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x75\x72\x62\x5f\x64\x65\x71\x75\x65\x75\x65\x3a\x20\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x3d\x25\x64" "\n"
,IlIlI);return IlIlI;}void llllIllIl(struct usb_hcd*IIlll,struct 
usb_host_endpoint*ep){unsigned long flags;struct IllIlI*Illll=IIllII(IIlll);
IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x68\x75\x62\x5f\x63\x6f\x6e\x74\x72\x6f\x6c\x5b\x25\x73\x5d\x3a\x20\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x65\x6e\x64\x70\x6f\x69\x6e\x74\x5f\x64\x69\x73\x61\x62\x6c\x65\x2b\x2b\x20\x65\x70\x3d\x25\x70" "\n"
,lIIIlll(IIlll),ep);spin_lock_irqsave(&Illll->lock,flags);if(ep->hcpriv){IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x68\x75\x62\x5f\x63\x6f\x6e\x74\x72\x6f\x6c\x3a\x20\x63\x6c\x65\x61\x6e\x69\x6e\x67\x20\x75\x70\x20\x68\x63\x70\x72\x69\x76" "\n"
);ep->hcpriv=NULL;}spin_unlock_irqrestore(&Illll->lock,flags);IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x68\x75\x62\x5f\x63\x6f\x6e\x74\x72\x6f\x6c\x3a\x20\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x65\x6e\x64\x70\x6f\x69\x6e\x74\x5f\x64\x69\x73\x61\x62\x6c\x65\x2d\x2d" "\n"
);}
#if KERNEL_GT_EQ((0x4d5+2169-0xd4c),(0x12fb+4156-0x2331),(0x18fd+1118-0x1d34)) \
|| RHEL_RELEASE_GT_EQ((0x26d+8284-0x22c3),(0x11ea+5219-0x264a)) 
#define IllIIllIl \
		( USB_PORT_STAT_C_CONNECTION \
		| USB_PORT_STAT_C_ENABLE \
		| USB_PORT_STAT_C_SUSPEND \
		| USB_PORT_STAT_C_OVERCURRENT \
		| USB_PORT_STAT_C_RESET \
		| USB_PORT_STAT_C_BH_RESET \
		| USB_PORT_STAT_C_LINK_STATE \
		| USB_PORT_STAT_C_CONFIG_ERROR )
#else
#define IllIIllIl \
		( USB_PORT_STAT_C_CONNECTION \
		| USB_PORT_STAT_C_ENABLE \
		| USB_PORT_STAT_C_SUSPEND \
		| USB_PORT_STAT_C_OVERCURRENT \
		| USB_PORT_STAT_C_RESET )
#endif
#if KERNEL_GT_EQ((0x2b3+2643-0xd04),(0x89d+7487-0x25d6),(0x698+552-0x899)) || \
RHEL_RELEASE_GT_EQ((0x291+8610-0x242d),(0x7ab+5634-0x1daa)) 
size_t IIIlIIlIl(void*llIlI,size_t IIlIIl){struct{struct usb_bos_descriptor 
lIlIlllI;struct usb_ss_cap_descriptor ss_cap;}__packed lllIIll;memset(&lllIIll,
(0xa7b+3142-0x16c1),sizeof(lllIIll));lllIIll.lIlIlllI.bLength=USB_DT_BOS_SIZE,
lllIIll.lIlIlllI.bDescriptorType=USB_DT_BOS,lllIIll.lIlIlllI.wTotalLength=
cpu_to_le16(sizeof(lllIIll)),lllIIll.lIlIlllI.bNumDeviceCaps=(0x76a+3248-0x1419)
,lllIIll.ss_cap.bLength=USB_DT_USB_SS_CAP_SIZE,lllIIll.ss_cap.bDescriptorType=
USB_DT_DEVICE_CAPABILITY,lllIIll.ss_cap.bDevCapabilityType=USB_SS_CAP_TYPE,
lllIIll.ss_cap.wSpeedSupported=cpu_to_le16(USB_5GBPS_OPERATION),lllIIll.ss_cap.
bFunctionalitySupport=ilog2(USB_5GBPS_OPERATION),IIlIIl=min(sizeof(lllIIll),
IIlIIl);memcpy(llIlI,&lllIIll,IIlIIl);return IIlIIl;}size_t lIllIlIlI(void*llIlI
,size_t IIlIIl){struct usb_hub_descriptor desc;memset(&desc,(0x3a3+8721-0x25b4),
sizeof(desc));desc.bDescLength=(0xac9+4709-0x1d22);desc.bDescriptorType=
(0x1066+2308-0x1940);desc.bNbrPorts=llIlll;
desc.wHubCharacteristics=cpu_to_le16((0x125a+4914-0x258b));desc.u.ss.
bHubHdrDecLat=(0x469+7815-0x22ec);
desc.u.ss.DeviceRemovable=cpu_to_le16(65534&(65535>>((0x138+3035-0xd04)-llIlll))
);IIlIIl=min((size_t)desc.bDescLength,IIlIIl);memcpy(llIlI,&desc,IIlIIl);return 
IIlIIl;}
#endif 
size_t lllIIlIlI(void*llIlI,size_t IIlIIl){__u8*lIllIlIl;struct 
usb_hub_descriptor desc;memset(&desc,(0xdb8+4856-0x20b0),sizeof(desc));desc.
bDescLength=(0x65f+1214-0xb16)+IIllIlIl*(0x1658+33-0x1677);desc.bDescriptorType=
(0x422+410-0x593);desc.bNbrPorts=llIlll;desc.wHubCharacteristics=cpu_to_le16(
(0x12d2+3792-0x21a1));
#if KERNEL_GT_EQ((0xf9b+3942-0x1eff),(0x118+3124-0xd46),(0x119b+2680-0x1bec)) ||\
 RHEL_RELEASE_GT_EQ((0xa46+5337-0x1f19),(0xe84+4983-0x21f9))
lIllIlIl=desc.u.hs.DeviceRemovable;
#else
lIllIlIl=desc.DeviceRemovable;
#endif
memset(&lIllIlIl[(0x4a7+2323-0xdba)],(0x9d8+5714-0x202a),IIllIlIl);memset(&
lIllIlIl[IIllIlIl],(0x22ab+1348-0x26f0),IIllIlIl);IIlIIl=min((size_t)desc.
bDescLength,IIlIIl);memcpy(llIlI,&desc,IIlIIl);return IIlIIl;}static int 
lIIIllIll(struct usb_hcd*IIlll,u16 llIllIlI,u16 wValue,u16 wIndex,char*llIlI,u16
 wLength){struct IllIlI*Illll=IIllII(IIlll);int IlIlI=(0x12c6+3638-0x20fc);int 
lIIlI=-(0xf97+269-0x10a3);int IllIIIlII=(0x66a+2634-0x10b4);unsigned long flags;
IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x68\x75\x62\x5f\x63\x6f\x6e\x74\x72\x6f\x6c\x5b\x25\x73\x5d\x3a\x20\x2b\x2b" "\n"
,lIIIlll(IIlll));if(!test_bit(HCD_FLAG_HW_ACCESSIBLE,&IIlll->flags))return-
ETIMEDOUT;spin_lock_irqsave(&Illll->lock,flags);switch(llIllIlI){case 
GetHubDescriptor:IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x68\x75\x62\x5f\x63\x6f\x6e\x74\x72\x6f\x6c\x3a\x20\x47\x65\x74\x48\x75\x62\x44\x65\x73\x63\x72\x69\x70\x74\x6f\x72" "\n"
);
#if KERNEL_GT_EQ((0x1964+3176-0x25ca),(0x17cf+399-0x1958),(0x1f47+961-0x22e1)) \
|| RHEL_RELEASE_GT_EQ((0x1344+2430-0x1cbc),(0x218c+452-0x234d)) 
if(IIlll->speed==HCD_USB3){if((wValue>>(0x48d+537-0x69e))!=USB_DT_SS_HUB){IlIlI=
-EPIPE;break;}

lIllIlIlI(llIlI,wLength);}else
#endif
{if((wValue>>(0x993+6544-0x231b))!=USB_DT_HUB){IlIlI=-EPIPE;break;}lllIIlIlI(
llIlI,wLength);}break;
#if KERNEL_GT_EQ((0x16a+5729-0x17c9),(0x7b1+3798-0x1681),(0x62b+3777-0x14c5)) ||\
 RHEL_RELEASE_GT_EQ((0x57+2444-0x9dd),(0x9b0+2828-0x14b9)) 
case DeviceRequest|USB_REQ_GET_DESCRIPTOR:if(IIlll->speed!=HCD_USB3){IlIlI=-
EPIPE;break;}if((wValue>>(0xa29+3542-0x17f7))!=USB_DT_BOS){IlIlI=-EPIPE;break;}
IlIlI=IIIlIIlIl(llIlI,wLength);break;case GetPortErrorCount:
if(IIlll->speed!=HCD_USB3){IlIlI=-EPIPE;break;}
*(__le16*)llIlI=cpu_to_le16((0x2c4+5195-0x170f));break;case SetHubDepth:
if(IIlll->speed!=HCD_USB3){IlIlI=-EPIPE;break;}
break;
#endif
case GetHubStatus:IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x68\x75\x62\x5f\x63\x6f\x6e\x74\x72\x6f\x6c\x3a\x20\x47\x65\x74\x48\x75\x62\x53\x74\x61\x74\x75\x73" "\n"
);*(__le32*)llIlI=cpu_to_le32((0x2a2+2682-0xd1c));break;case SetHubFeature:IlllI
(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x68\x75\x62\x5f\x63\x6f\x6e\x74\x72\x6f\x6c\x3a\x20\x53\x65\x74\x48\x75\x62\x46\x65\x61\x74\x75\x72\x65" "\n"
);
IlIlI=-EPIPE;break;case ClearHubFeature:IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x68\x75\x62\x5f\x63\x6f\x6e\x74\x72\x6f\x6c\x3a\x20\x43\x6c\x65\x61\x72\x48\x75\x62\x46\x65\x61\x74\x75\x72\x65" "\n"
);
break;case GetPortStatus:IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x68\x75\x62\x5f\x63\x6f\x6e\x74\x72\x6f\x6c\x3a\x20\x47\x65\x74\x50\x6f\x72\x74\x53\x74\x61\x74\x75\x73" "\n"
);lIIlI=(wIndex&(0xbfd+2332-0x141a))-(0x296+7378-0x1f67);IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x68\x75\x62\x5f\x63\x6f\x6e\x74\x72\x6f\x6c\x3a\x20\x70\x6f\x72\x74\x3d\x25\x64" "\n"
,lIIlI);if(lIIlI<(0xf72+3495-0x1d19)||lIIlI>=llIlll){lIIlI=-(0x504+7201-0x2124);
IlIlI=-EPIPE;break;}

if(Illll->IlIlIII[lIIlI]&&time_after_eq(jiffies,Illll->IlIlIII[lIIlI])){if(Illll
->IllIllIl[lIIlI]==IIIlIll){Illll->IIIIIII[lIIlI]->llllIlI=(0x326+6156-0x1b32);}
#if KERNEL_GT_EQ((0xcac+6197-0x24df),(0x388+6545-0x1d13),(0x107f+892-0x13d4)) ||\
 RHEL_RELEASE_GT_EQ((0xcfb+4763-0x1f90),(0xe17+4162-0x1e56)) 
if(IIlll->speed==HCD_USB3){lIIIlII(Illll,lIIlI,IlIIIlII,(0xd66+2887-0x18ad));}
else
#endif
{lIlIlII(Illll,lIIlI,IlIIIlII,(0x49b+5886-0x1b99));}}((__le16*)llIlI)[
(0x3f1+5265-0x1882)]=cpu_to_le16(Illll->IIIIIll[lIIlI]);((__le16*)llIlI)[
(0x11c3+2871-0x1cf9)]=cpu_to_le16(Illll->IIllll[lIIlI]);break;case 
SetPortFeature:lIIlI=(wIndex&(0xa24+1512-0xf0d))-(0x907+7580-0x26a2);if(lIIlI<
(0x39c+6586-0x1d56)||lIIlI>=llIlll){IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x68\x75\x62\x5f\x63\x6f\x6e\x74\x72\x6f\x6c\x3a\x20\x53\x65\x74\x50\x6f\x72\x74\x46\x65\x61\x74\x75\x72\x65\x20\x69\x6e\x76\x61\x6c\x69\x64\x20\x70\x6f\x72\x74\x20\x6e\x75\x6d\x62\x65\x72\x20\x28\x25\x64\x29" "\n"
,lIIlI);lIIlI=-(0x12b8+2303-0x1bb6);IlIlI=-EPIPE;break;}
#if KERNEL_GT_EQ((0xf53+868-0x12b5),(0x68c+5118-0x1a84),(0x314+8008-0x2235)) || \
RHEL_RELEASE_GT_EQ((0x1234+4712-0x2496),(0xab4+1993-0x127a)) 
if(IIlll->speed==HCD_USB3){IlIlI=lllIllIII(Illll,lIIlI,wValue,wIndex>>
(0xdf5+670-0x108b));}else
#endif
{IlIlI=IIIlIlIll(Illll,lIIlI,wValue,wIndex>>(0x35c+8817-0x25c5));}break;case 
ClearPortFeature:lIIlI=(wIndex&(0x1b32+1865-0x217c))-(0x20+5066-0x13e9);if(lIIlI
<(0xcc0+1872-0x1410)||lIIlI>=llIlll){IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x68\x75\x62\x5f\x63\x6f\x6e\x74\x72\x6f\x6c\x3a\x20\x43\x6c\x65\x61\x72\x50\x6f\x72\x74\x46\x65\x61\x74\x75\x72\x65\x20\x69\x6e\x76\x61\x6c\x69\x64\x20\x70\x6f\x72\x74\x20\x6e\x75\x6d\x62\x65\x72\x20\x28\x25\x64\x29" "\n"
,lIIlI);lIIlI=-(0x1672+1520-0x1c61);IlIlI=-EPIPE;break;}
#if KERNEL_GT_EQ((0x1092+2694-0x1b16),(0x989+1893-0x10e8),(0x565+2436-0xec2)) ||\
 RHEL_RELEASE_GT_EQ((0x69d+317-0x7d4),(0x59c+5996-0x1d05)) 
if(IIlll->speed==HCD_USB3){IlIlI=IlIlllIIl(Illll,lIIlI,wValue);}else
#endif
{IlIlI=llllIlllI(Illll,lIIlI,wValue);}break;default:IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x68\x75\x62\x5f\x63\x6f\x6e\x74\x72\x6f\x6c\x3a\x20\x52\x65\x71\x3d\x30\x78\x25\x30\x34\x58\x20\x56\x61\x6c\x75\x65\x3d\x30\x78\x25\x30\x34\x58\x20\x49\x6e\x64\x65\x78\x3d\x30\x78\x25\x30\x34\x58\x69\x20\x4c\x65\x6e\x67\x74\x68\x3d\x25\x64" "\n"
,llIllIlI,wValue,wIndex,wLength);
IlIlI=-EPIPE;break;}
IllIIIlII=(lIIlI!=-(0xd19+571-0xf53))&&((Illll->IIllll[lIIlI]&IllIIllIl)!=
(0x1fd5+3-0x1fd8));spin_unlock_irqrestore(&Illll->lock,flags);if(IllIIIlII)
usb_hcd_poll_rh_status(IIlll);IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x68\x75\x62\x5f\x63\x6f\x6e\x74\x72\x6f\x6c\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x20\x3d\x20\x25\x64" "\n"
,IlIlI);return IlIlI;}static int IIIlIlIll(struct IllIlI*Illll,int lIIlI,int 
IlllIll,int llIIllI){int IlIlI=(0x19d2+2410-0x233c);switch(IlllIll){case 
USB_PORT_FEAT_ENABLE:IlllI(
"\x53\x65\x74\x50\x6f\x72\x74\x46\x65\x61\x74\x75\x72\x65\x28\x25\x64\x2c\x55\x53\x42\x5f\x50\x4f\x52\x54\x5f\x46\x45\x41\x54\x5f\x45\x4e\x41\x42\x4c\x45\x29" "\n"
,lIIlI);


IlIlI=-EPIPE;break;case USB_PORT_FEAT_SUSPEND:IlllI(
"\x53\x65\x74\x50\x6f\x72\x74\x46\x65\x61\x74\x75\x72\x65\x28\x25\x64\x2c\x55\x53\x42\x5f\x50\x4f\x52\x54\x5f\x46\x45\x41\x54\x5f\x53\x55\x53\x50\x45\x4e\x44\x29" "\n"
,lIIlI);




lIlIlII(Illll,lIIlI,Illllllll,(0x1ef4+1850-0x262e));break;case 
USB_PORT_FEAT_RESET:IlllI(
"\x53\x65\x74\x50\x6f\x72\x74\x46\x65\x61\x74\x75\x72\x65\x28\x25\x64\x2c\x55\x53\x42\x5f\x50\x4f\x52\x54\x5f\x46\x45\x41\x54\x5f\x52\x45\x53\x45\x54\x29" "\n"
,lIIlI);





lIlIlII(Illll,lIIlI,lIIlIll,(0x1bbf+2116-0x2403));if(Illll->IIIIIII[lIIlI]&&
Illll->IIIIIII[lIIlI]->llllIlI>(0x788+4217-0x1801)){IlIlIIII(Illll->IIIIIII[
lIIlI]);}break;case USB_PORT_FEAT_POWER:IlllI(
"\x53\x65\x74\x50\x6f\x72\x74\x46\x65\x61\x74\x75\x72\x65\x28\x25\x64\x2c\x55\x53\x42\x5f\x50\x4f\x52\x54\x5f\x46\x45\x41\x54\x5f\x50\x4f\x57\x45\x52\x29" "\n"
,lIIlI);


lIlIlII(Illll,lIIlI,llIIllII,(0x1ec7+1171-0x235a));break;case USB_PORT_FEAT_TEST
:IlllI(
"\x53\x65\x74\x50\x6f\x72\x74\x46\x65\x61\x74\x75\x72\x65\x28\x25\x64\x2c\x55\x53\x42\x5f\x50\x4f\x52\x54\x5f\x46\x45\x41\x54\x5f\x54\x45\x53\x54\x29" "\n"
,lIIlI);
break;case USB_PORT_FEAT_INDICATOR:IlllI(
"\x53\x65\x74\x50\x6f\x72\x74\x46\x65\x61\x74\x75\x72\x65\x28\x25\x64\x2c\x55\x53\x42\x5f\x50\x4f\x52\x54\x5f\x46\x45\x41\x54\x5f\x49\x4e\x44\x49\x43\x41\x54\x4f\x52\x29" "\n"
,lIIlI);
break;case USB_PORT_FEAT_CONNECTION:case USB_PORT_FEAT_OVER_CURRENT:case 
USB_PORT_FEAT_C_CONNECTION:case USB_PORT_FEAT_C_OVER_CURRENT:case 
USB_PORT_FEAT_C_RESET:case USB_PORT_FEAT_LOWSPEED:case USB_PORT_FEAT_C_ENABLE:
case USB_PORT_FEAT_C_SUSPEND:


break;default:
IlllI(
"\x53\x65\x74\x50\x6f\x72\x74\x46\x65\x61\x74\x75\x72\x65\x28\x25\x64\x2c\x20\x25\x64\x29" "\n"
,lIIlI,IlllIll);IlIlI=-EPIPE;break;}return IlIlI;}static int llllIlllI(struct 
IllIlI*Illll,int lIIlI,int IlllIll){int IlIlI=(0x24b+6105-0x1a24);switch(IlllIll
){case USB_PORT_FEAT_ENABLE:IlllI(
"\x43\x6c\x65\x61\x72\x50\x6f\x72\x74\x46\x65\x61\x74\x75\x72\x65\x28\x25\x64\x2c\x55\x53\x42\x5f\x50\x4f\x52\x54\x5f\x46\x45\x41\x54\x5f\x45\x4e\x41\x42\x4c\x45\x29" "\n"
,lIIlI);



lIlIlII(Illll,lIIlI,IllIIlll,(0xa17+5568-0x1fd7));break;case 
USB_PORT_FEAT_SUSPEND:IlllI(
"\x43\x6c\x65\x61\x72\x50\x6f\x72\x74\x46\x65\x61\x74\x75\x72\x65\x28\x25\x64\x2c\x55\x53\x42\x5f\x50\x4f\x52\x54\x5f\x46\x45\x41\x54\x5f\x53\x55\x53\x50\x45\x4e\x44\x29" "\n"
,lIIlI);



lIlIlII(Illll,lIIlI,lIlIIIlII,(0x85c+1857-0xf9d));break;case USB_PORT_FEAT_POWER
:IlllI(
"\x43\x6c\x65\x61\x72\x50\x6f\x72\x74\x46\x65\x61\x74\x75\x72\x65\x28\x25\x64\x2c\x55\x53\x42\x5f\x50\x4f\x52\x54\x5f\x46\x45\x41\x54\x5f\x50\x4f\x57\x45\x52\x29" "\n"
,lIIlI);

lIlIlII(Illll,lIIlI,lIIIIIll,(0x4bd+4458-0x1627));break;case 
USB_PORT_FEAT_C_CONNECTION:IlllI(
"\x43\x6c\x65\x61\x72\x50\x6f\x72\x74\x46\x65\x61\x74\x75\x72\x65\x28\x25\x64\x2c\x55\x53\x42\x5f\x50\x4f\x52\x54\x5f\x46\x45\x41\x54\x5f\x43\x5f\x43\x4f\x4e\x4e\x45\x43\x54\x49\x4f\x4e\x29" "\n"
,lIIlI);lIlIlII(Illll,lIIlI,lIllIlll,(0x46f+719-0x73e));break;case 
USB_PORT_FEAT_C_ENABLE:IlllI(
"\x43\x6c\x65\x61\x72\x50\x6f\x72\x74\x46\x65\x61\x74\x75\x72\x65\x28\x25\x64\x2c\x55\x53\x42\x5f\x50\x4f\x52\x54\x5f\x46\x45\x41\x54\x5f\x43\x5f\x45\x4e\x41\x42\x4c\x45\x29" "\n"
,lIIlI);lIlIlII(Illll,lIIlI,lIlIIllll,(0x637+1259-0xb22));break;case 
USB_PORT_FEAT_C_SUSPEND:IlllI(
"\x43\x6c\x65\x61\x72\x50\x6f\x72\x74\x46\x65\x61\x74\x75\x72\x65\x28\x25\x64\x2c\x55\x53\x42\x5f\x50\x4f\x52\x54\x5f\x46\x45\x41\x54\x5f\x43\x5f\x53\x55\x53\x50\x45\x4e\x44\x29" "\n"
,lIIlI);lIlIlII(Illll,lIIlI,IlIIllIll,(0x656+1826-0xd78));break;case 
USB_PORT_FEAT_C_OVER_CURRENT:IlllI(
"\x43\x6c\x65\x61\x72\x50\x6f\x72\x74\x46\x65\x61\x74\x75\x72\x65\x28\x25\x64\x2c\x55\x53\x42\x5f\x50\x4f\x52\x54\x5f\x46\x45\x41\x54\x5f\x43\x5f\x4f\x56\x45\x52\x5f\x43\x55\x52\x52\x45\x4e\x54\x29" "\n"
,lIIlI);
break;case USB_PORT_FEAT_C_RESET:IlllI(
"\x43\x6c\x65\x61\x72\x50\x6f\x72\x74\x46\x65\x61\x74\x75\x72\x65\x28\x25\x64\x2c\x55\x53\x42\x5f\x50\x4f\x52\x54\x5f\x46\x45\x41\x54\x5f\x43\x5f\x52\x45\x53\x45\x54\x29" "\n"
,lIIlI);lIlIlII(Illll,lIIlI,IlIlllIl,(0x1185+689-0x1436));break;case 
USB_PORT_FEAT_INDICATOR:IlllI(
"\x43\x6c\x65\x61\x72\x50\x6f\x72\x74\x46\x65\x61\x74\x75\x72\x65\x28\x25\x64\x2c\x55\x53\x42\x5f\x50\x4f\x52\x54\x5f\x46\x45\x41\x54\x5f\x49\x4e\x44\x49\x43\x41\x54\x4f\x52\x29" "\n"
,lIIlI);
break;case USB_PORT_FEAT_CONNECTION:case USB_PORT_FEAT_OVER_CURRENT:case 
USB_PORT_FEAT_RESET:case USB_PORT_FEAT_TEST:


break;default:IlllI(
"\x43\x6c\x65\x61\x72\x50\x6f\x72\x74\x46\x65\x61\x74\x75\x72\x65\x28\x25\x64\x2c\x20\x25\x64\x29" "\n"
,lIIlI,IlllIll);IlIlI=-EPIPE;break;}return IlIlI;}
#if KERNEL_GT_EQ((0x2446+477-0x2621),(0x494+3557-0x1273),(0x3a5+3333-0x1083)) ||\
 RHEL_RELEASE_GT_EQ((0x1834+3084-0x243a),(0xa6d+3724-0x18f6)) 
static int lllIllIII(struct IllIlI*Illll,int lIIlI,int IlllIll,int llIIllI){int 
IlIlI=(0x18a3+353-0x1a04);switch(IlllIll){case USB_PORT_FEAT_BH_PORT_RESET:IlllI
(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x68\x75\x62\x5f\x63\x6f\x6e\x74\x72\x6f\x6c\x3a\x20\x53\x65\x74\x50\x6f\x72\x74\x46\x65\x61\x74\x75\x72\x65\x28\x25\x64\x2c\x55\x53\x42\x5f\x50\x4f\x52\x54\x5f\x46\x45\x41\x54\x5f\x42\x48\x5f\x50\x4f\x52\x54\x5f\x52\x45\x53\x45\x54\x29" "\n"
,lIIlI);







case USB_PORT_FEAT_RESET:IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x68\x75\x62\x5f\x63\x6f\x6e\x74\x72\x6f\x6c\x3a\x20\x53\x65\x74\x50\x6f\x72\x74\x46\x65\x61\x74\x75\x72\x65\x28\x25\x64\x2c\x55\x53\x42\x5f\x50\x4f\x52\x54\x5f\x46\x45\x41\x54\x5f\x52\x45\x53\x45\x54\x29" "\n"
,lIIlI);





lIIIlII(Illll,lIIlI,lIIlIll,(0xa2+6185-0x18cb));if(Illll->IIIIIII[lIIlI]&&Illll
->IIIIIII[lIIlI]->llllIlI>(0x656+5980-0x1db2)){IlIlIIII(Illll->IIIIIII[lIIlI]);}
break;case USB_PORT_FEAT_LINK_STATE:IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x68\x75\x62\x5f\x63\x6f\x6e\x74\x72\x6f\x6c\x3a\x20\x53\x65\x74\x50\x6f\x72\x74\x46\x65\x61\x74\x75\x72\x65\x28\x25\x64\x2c\x55\x53\x42\x5f\x50\x4f\x52\x54\x5f\x46\x45\x41\x54\x5f\x4c\x49\x4e\x4b\x5f\x53\x54\x41\x54\x45\x2c\x20\x30\x78\x25\x30\x34\x78\x29" "\n"
,lIIlI,llIIllI);


lIIIlII(Illll,lIIlI,llIIlIII,llIIllI);break;case USB_PORT_FEAT_POWER:IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x68\x75\x62\x5f\x63\x6f\x6e\x74\x72\x6f\x6c\x3a\x20\x53\x65\x74\x50\x6f\x72\x74\x46\x65\x61\x74\x75\x72\x65\x28\x25\x64\x2c\x55\x53\x42\x5f\x50\x4f\x52\x54\x5f\x46\x45\x41\x54\x5f\x50\x4f\x57\x45\x52\x29" "\n"
,lIIlI);

lIIIlII(Illll,lIIlI,llIIllII,(0x1257+4656-0x2487));break;case 
USB_PORT_FEAT_U1_TIMEOUT:case USB_PORT_FEAT_U2_TIMEOUT:IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x68\x75\x62\x5f\x63\x6f\x6e\x74\x72\x6f\x6c\x3a\x20\x53\x65\x74\x50\x6f\x72\x74\x46\x65\x61\x74\x75\x72\x65\x28\x25\x64\x2c\x55\x53\x42\x5f\x50\x4f\x52\x54\x5f\x46\x45\x41\x54\x5f\x55\x31\x2f\x55\x32\x5f\x54\x49\x4d\x45\x4f\x55\x54\x29" "\n"
,lIIlI);


break;case USB_PORT_FEAT_REMOTE_WAKE_MASK:IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x68\x75\x62\x5f\x63\x6f\x6e\x74\x72\x6f\x6c\x3a\x20\x53\x65\x74\x50\x6f\x72\x74\x46\x65\x61\x74\x75\x72\x65\x28\x25\x64\x2c\x55\x53\x42\x5f\x50\x4f\x52\x54\x5f\x46\x45\x41\x54\x5f\x52\x45\x4d\x4f\x54\x45\x5f\x57\x41\x4b\x45\x5f\x4d\x41\x53\x4b\x29" "\n"
,lIIlI);

break;case USB_PORT_FEAT_FORCE_LINKPM_ACCEPT:IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x68\x75\x62\x5f\x63\x6f\x6e\x74\x72\x6f\x6c\x3a\x20\x53\x65\x74\x50\x6f\x72\x74\x46\x65\x61\x74\x75\x72\x65\x28\x25\x64\x2c\x55\x53\x42\x5f\x50\x4f\x52\x54\x5f\x46\x45\x41\x54\x5f\x46\x4f\x52\x43\x45\x5f\x4c\x49\x4e\x4b\x50\x4d\x5f\x41\x43\x43\x45\x50\x54\x29" "\n"
,lIIlI);
break;case USB_PORT_FEAT_CONNECTION:case USB_PORT_FEAT_OVER_CURRENT:case 
USB_PORT_FEAT_C_CONNECTION:case USB_PORT_FEAT_C_OVER_CURRENT:case 
USB_PORT_FEAT_C_RESET:case USB_PORT_FEAT_C_PORT_LINK_STATE:case 
USB_PORT_FEAT_C_PORT_CONFIG_ERROR:case USB_PORT_FEAT_C_BH_PORT_RESET:


break;default:
IlllI(
"\x53\x65\x74\x50\x6f\x72\x74\x46\x65\x61\x74\x75\x72\x65\x28\x25\x64\x2c\x20\x25\x64\x29" "\n"
,lIIlI,IlllIll);IlIlI=-EPIPE;break;}return IlIlI;}static int IlIlllIIl(struct 
IllIlI*Illll,int lIIlI,int IlllIll){int IlIlI=(0x9dc+381-0xb59);switch(IlllIll){
case USB_PORT_FEAT_POWER:IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x68\x75\x62\x5f\x63\x6f\x6e\x74\x72\x6f\x6c\x3a\x20\x43\x6c\x65\x61\x72\x50\x6f\x72\x74\x46\x65\x61\x74\x75\x72\x65\x28\x25\x64\x2c\x55\x53\x42\x5f\x50\x4f\x52\x54\x5f\x46\x45\x41\x54\x5f\x50\x4f\x57\x45\x52\x29" "\n"
,lIIlI);

lIIIlII(Illll,lIIlI,lIIIIIll,(0x1399+1180-0x1835));break;case 
USB_PORT_FEAT_C_CONNECTION:IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x68\x75\x62\x5f\x63\x6f\x6e\x74\x72\x6f\x6c\x3a\x20\x43\x6c\x65\x61\x72\x50\x6f\x72\x74\x46\x65\x61\x74\x75\x72\x65\x28\x25\x64\x2c\x55\x53\x42\x5f\x50\x4f\x52\x54\x5f\x46\x45\x41\x54\x5f\x43\x5f\x43\x4f\x4e\x4e\x45\x43\x54\x49\x4f\x4e\x29" "\n"
,lIIlI);lIIIlII(Illll,lIIlI,lIllIlll,(0xc7f+352-0xddf));break;case 
USB_PORT_FEAT_C_OVER_CURRENT:IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x68\x75\x62\x5f\x63\x6f\x6e\x74\x72\x6f\x6c\x3a\x20\x43\x6c\x65\x61\x72\x50\x6f\x72\x74\x46\x65\x61\x74\x75\x72\x65\x28\x25\x64\x2c\x55\x53\x42\x5f\x50\x4f\x52\x54\x5f\x46\x45\x41\x54\x5f\x43\x5f\x4f\x56\x45\x52\x5f\x43\x55\x52\x52\x45\x4e\x54\x29" "\n"
,lIIlI);
break;case USB_PORT_FEAT_C_RESET:IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x68\x75\x62\x5f\x63\x6f\x6e\x74\x72\x6f\x6c\x3a\x20\x43\x6c\x65\x61\x72\x50\x6f\x72\x74\x46\x65\x61\x74\x75\x72\x65\x28\x25\x64\x2c\x55\x53\x42\x5f\x50\x4f\x52\x54\x5f\x46\x45\x41\x54\x5f\x43\x5f\x52\x45\x53\x45\x54\x29" "\n"
,lIIlI);lIIIlII(Illll,lIIlI,IlIlllIl,(0x3c0+6108-0x1b9c));break;case 
USB_PORT_FEAT_C_PORT_LINK_STATE:IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x68\x75\x62\x5f\x63\x6f\x6e\x74\x72\x6f\x6c\x3a\x20\x43\x6c\x65\x61\x72\x50\x6f\x72\x74\x46\x65\x61\x74\x75\x72\x65\x28\x25\x64\x2c\x55\x53\x42\x5f\x50\x4f\x52\x54\x5f\x46\x45\x41\x54\x5f\x43\x5f\x50\x4f\x52\x54\x5f\x4c\x49\x4e\x4b\x5f\x53\x54\x41\x54\x45\x29" "\n"
,lIIlI);lIIIlII(Illll,lIIlI,IIlIIlIlI,(0x1b87+714-0x1e51));break;case 
USB_PORT_FEAT_C_PORT_CONFIG_ERROR:IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x68\x75\x62\x5f\x63\x6f\x6e\x74\x72\x6f\x6c\x3a\x20\x43\x6c\x65\x61\x72\x50\x6f\x72\x74\x46\x65\x61\x74\x75\x72\x65\x28\x25\x64\x2c\x55\x53\x42\x5f\x50\x4f\x52\x54\x5f\x46\x45\x41\x54\x5f\x43\x5f\x50\x4f\x52\x54\x5f\x43\x4f\x4e\x46\x49\x47\x5f\x45\x52\x52\x4f\x52\x29" "\n"
,lIIlI);
break;case USB_PORT_FEAT_C_BH_PORT_RESET:IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x68\x75\x62\x5f\x63\x6f\x6e\x74\x72\x6f\x6c\x3a\x20\x43\x6c\x65\x61\x72\x50\x6f\x72\x74\x46\x65\x61\x74\x75\x72\x65\x28\x25\x64\x2c\x55\x53\x42\x5f\x50\x4f\x52\x54\x5f\x46\x45\x41\x54\x5f\x43\x5f\x42\x48\x5f\x50\x4f\x52\x54\x5f\x52\x45\x53\x45\x54\x29" "\n"
,lIIlI);lIIIlII(Illll,lIIlI,IlIIIlIlI,(0x131+1672-0x7b9));break;case 
USB_PORT_FEAT_FORCE_LINKPM_ACCEPT:IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x68\x75\x62\x5f\x63\x6f\x6e\x74\x72\x6f\x6c\x3a\x20\x43\x6c\x65\x61\x72\x50\x6f\x72\x74\x46\x65\x61\x74\x75\x72\x65\x28\x25\x64\x2c\x55\x53\x42\x5f\x50\x4f\x52\x54\x5f\x46\x45\x41\x54\x5f\x46\x4f\x52\x43\x45\x5f\x4c\x49\x4e\x4b\x50\x4d\x5f\x41\x43\x43\x45\x50\x54\x29" "\n"
,lIIlI);
break;case USB_PORT_FEAT_CONNECTION:case USB_PORT_FEAT_OVER_CURRENT:case 
USB_PORT_FEAT_RESET:case USB_PORT_FEAT_LINK_STATE:case USB_PORT_FEAT_U1_TIMEOUT:
case USB_PORT_FEAT_U2_TIMEOUT:case USB_PORT_FEAT_REMOTE_WAKE_MASK:case 
USB_PORT_FEAT_BH_PORT_RESET:


break;default:IlllI(
"\x43\x6c\x65\x61\x72\x50\x6f\x72\x74\x46\x65\x61\x74\x75\x72\x65\x28\x25\x64\x2c\x20\x25\x64\x29" "\n"
,lIIlI,IlllIll);IlIlI=-EPIPE;break;}return IlIlI;}
#endif 
static int IIlllIIII(struct usb_hcd*IIlll,char*llIlI){int IlIlI=
(0x8ed+6459-0x2228);struct IllIlI*Illll=IIllII(IIlll);u32*lIlllllI=(u32*)llIlI;
unsigned long flags;IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x68\x75\x62\x5f\x73\x74\x61\x74\x75\x73\x5f\x64\x61\x74\x61\x5b\x25\x73\x5d\x2b\x2b" "\n"
,lIIIlll(IIlll));spin_lock_irqsave(&Illll->lock,flags);do
{int i;int lIIlllIl=(0x12b4+2273-0x1b95);if(!test_bit(HCD_FLAG_HW_ACCESSIBLE,&
IIlll->flags))break;for(i=(0x891+6229-0x20e6);i<llIlll;i++){if(Illll->IIllll[i]&
IllIIllIl){IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x68\x75\x62\x5f\x73\x74\x61\x74\x75\x73\x5f\x64\x61\x74\x61\x3a\x20\x70\x6f\x72\x74\x20\x25\x64\x20\x68\x61\x73\x20\x63\x68\x61\x6e\x67\x65\x64\x2e\x20\x77\x50\x6f\x72\x74\x53\x74\x61\x74\x75\x73\x3d\x30\x78\x25\x30\x34\x58\x20\x77\x50\x6f\x72\x74\x43\x68\x61\x6e\x67\x65\x3d\x30\x78\x25\x30\x34\x58" "\n"
,i,Illll->IIIIIll[i],Illll->IIllll[i]);if(lIIlllIl==(0x1407+37-0x142c))*lIlllllI
=(0x353+7949-0x2260);lIIlllIl=(0xc6c+5064-0x2033);
*lIlllllI|=(0x15cc+1750-0x1ca1)<<(i+(0x819+966-0xbde));}}if(lIIlllIl){IlIlI=
IIllIlIl;if(Illll->IIlIlllIl){usb_hcd_resume_root_hub(IIlll);}}}while(
(0x23b+3808-0x111b));spin_unlock_irqrestore(&Illll->lock,flags);IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x68\x75\x62\x5f\x73\x74\x61\x74\x75\x73\x5f\x64\x61\x74\x61\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x20\x3d\x20\x25\x64\x20\x6d\x61\x73\x6b\x20\x3d\x20\x30\x78\x25\x30\x38\x58" "\n"
,IlIlI,(u32)*lIlllllI);return IlIlI;}static int lIlIIIIII(struct usb_hcd*IIlll){
struct IllIlI*Illll=IIllII(IIlll);Illll->IIlIlllIl=(0x669+1989-0xe2d);IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x62\x75\x73\x5f\x73\x75\x73\x70\x65\x6e\x64\x5b\x25\x73\x5d" "\n"
,lIIIlll(IIlll));return(0x9e6+2261-0x12bb);}static int lIlIlIlll(struct usb_hcd*
IIlll){
struct IllIlI*Illll=IIllII(IIlll);Illll->IIlIlllIl=(0x947+4036-0x190b);IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x62\x75\x73\x5f\x72\x65\x73\x75\x6d\x65\x5b\x25\x73\x5d" "\n"
,lIIIlll(IIlll));return(0x30+228-0x114);}
#if KERNEL_GT_EQ((0xeec+1224-0x13b2),(0xf3a+1086-0x1372),(0x1b3+4481-0x130d)) ||\
 RHEL_RELEASE_GT_EQ((0xcd8+2769-0x17a3),(0x871+6041-0x2007)) 
static int llIIIIIlI(struct usb_hcd*IIlll,struct usb_device*IlIIl,struct 
usb_host_endpoint**lIlIllll,unsigned int IlIllllII,unsigned int IlIIIIllI,gfp_t 
llllI){IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x61\x6c\x6c\x6f\x63\x5f\x73\x74\x72\x65\x61\x6d\x73\x5b\x25\x73\x5d" "\n"
,lIIIlll(IIlll));
return(0xcd+2505-0xa96);}static int IllIIIlll(struct usb_hcd*IIlll,struct 
usb_device*IlIIl,struct usb_host_endpoint**lIlIllll,unsigned int IlIllllII,gfp_t
 llllI){IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x66\x72\x65\x65\x5f\x73\x74\x72\x65\x61\x6d\x73\x5b\x25\x73\x5d" "\n"
,lIIIlll(IIlll));
return(0x33f+919-0x6d6);}
#endif 


int IlIlIIIlI(void){int IlIlI=(0x143a+4054-0x2410);int IlIIllIIl=
(0x224+9262-0x2652);int lIllIIIlI=(0xce3+5270-0x2179);IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x69\x6e\x69\x74\x5f\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x2b\x2b" "\n"
);do{struct sysinfo llIIlllI;INIT_LIST_HEAD(&lllllll);spin_lock_init(&lIIIII);
si_meminfo(&llIIlllI);IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x69\x6e\x69\x74\x5f\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x74\x6f\x74\x61\x6c\x72\x61\x6d\x3d\x25\x6c\x75\x20\x62\x79\x74\x65\x73\x20\x74\x6f\x74\x61\x6c\x68\x69\x67\x68\x3d\x25\x6c\x75\x20\x62\x79\x74\x65\x73" "\n"
,llIIlllI.totalram*llIIlllI.mem_unit,llIIlllI.totalhigh*llIIlllI.mem_unit);
#if defined(CONFIG_X86_32) && !defined(_USBD_VHCI_NO_DMA_)
















IIIlllII=(llIIlllI.totalhigh>(0x79d+8010-0x26e7));
#endif
IlIlI=platform_driver_register(&lIllIllI);if(IlIlI!=(0x9b4+6843-0x246f)){IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x69\x6e\x69\x74\x5f\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x70\x6c\x61\x74\x66\x6f\x72\x6d\x5f\x64\x72\x69\x76\x65\x72\x5f\x72\x65\x67\x69\x73\x74\x65\x72\x20\x66\x61\x69\x6c\x65\x64\x2e\x20\x45\x72\x72\x6f\x72\x20\x6e\x75\x6d\x62\x65\x72\x20\x25\x64" "\n"
,IlIlI);break;}IlIIllIIl=(0x16d+9489-0x267d);IlIlI=platform_device_register(&
lIllIlII);if(IlIlI!=(0xc08+3474-0x199a)){IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x69\x6e\x69\x74\x5f\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x70\x6c\x61\x74\x66\x6f\x72\x6d\x5f\x64\x65\x76\x69\x63\x65\x5f\x72\x65\x67\x69\x73\x74\x65\x72\x20\x66\x61\x69\x6c\x65\x64\x2e\x20\x45\x72\x72\x6f\x72\x20\x6e\x75\x6d\x62\x65\x72\x20\x25\x64" "\n"
,IlIlI);break;}lIllIIIlI=(0x759+6556-0x20f4);IlIIIlll=llIlIIllI();if(IlIIIlll==
NULL){IlIlI=-ENOMEM;IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x69\x6e\x69\x74\x5f\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x61\x6c\x6c\x6f\x63\x20\x6d\x69\x6e\x6f\x72\x20\x66\x61\x69\x6c\x65\x64\x2e\x20\x45\x72\x72\x6f\x72\x20\x6e\x75\x6d\x62\x65\x72\x20\x25\x64" "\n"
,IlIlI);break;}}while((0xe7c+1369-0x13d5));if(IlIlI!=(0x6c6+3401-0x140f)){if(
IlIIIlll){lIllIIII(IlIIIlll);IlIIIlll=NULL;}if(lIllIIIlI){
platform_device_unregister(&lIllIlII);}if(IlIIllIIl){platform_driver_unregister(
&lIllIllI);}}IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x69\x6e\x69\x74\x5f\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x20\x3d\x20\x25\x64" "\n"
,IlIlI);return IlIlI;}void IIlllIII(void){IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x64\x65\x69\x6e\x69\x74\x5f\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x2b\x2b" "\n"
);if(IlIIIlll){lIllIIII(IlIIIlll);IlIIIlll=NULL;}spin_lock(&lIIIII);while(!
list_empty(&lllllll)){struct lIlIl*lllll=(struct lIlIl*)lllllll.next;lIllIIlI(
lllll);spin_unlock(&lIIIII);IlllllII(lllll);lllllIll(lllll);spin_lock(&lIIIII);}
spin_unlock(&lIIIII);platform_device_unregister(&lIllIlII);
platform_driver_unregister(&lIllIllI);IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x64\x65\x69\x6e\x69\x74\x5f\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x2d\x2d" "\n"
);}struct lIlIl*IlIlIIIIl(u16 vid,u16 IllIIII,u16 IlIllIl,int speed){struct 
lIlIl*lllll;do{lllll=IlIIllI(sizeof(*lllll),GFP_KERNEL);if(!lllll){IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x63\x72\x65\x61\x74\x65\x3a\x20\x6b\x6d\x61\x6c\x6c\x6f\x63\x20\x66\x61\x69\x6c\x65\x64\x2e" "\n"
);break;}if(llIllIllI(lllll)<(0x10e0+5475-0x2643)){IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x63\x72\x65\x61\x74\x65\x3a\x20\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x61\x6c\x6c\x6f\x63\x5f\x6d\x69\x6e\x6f\x72\x20\x66\x61\x69\x6c\x65\x64\x2e" "\n"
);break;}
#ifdef _USBD_DEBUG_MEMORY_
atomic_inc(&lIlIlIIIl);
#endif
init_waitqueue_head(&lllll->lllIll);spin_lock_init(&lllll->llllll);
INIT_LIST_HEAD(&lllll->lIlIIlI);INIT_LIST_HEAD(&lllll->IllIIll);INIT_LIST_HEAD(&
lllll->IlIIIIll);kref_init(&lllll->lllllIl);lllll->vid=vid;lllll->IllIIII=
IllIIII;lllll->IlIllIl=IlIllIl;lllll->speed=speed;
#if KERNEL_GT_EQ((0x3a3+7530-0x210b),(0x13e1+3629-0x2208),(0x15e2+3312-0x22ab)) \
|| RHEL_RELEASE_GT_EQ((0x181b+1827-0x1f38),(0x59c+1343-0xad8)) 
lllll->parent=(speed==USB_SPEED_SUPER)?IlIIlIl:llllIII;
#else
lllll->parent=llllIII;
#endif
lllll->lIIlI=-(0xaf8+6222-0x2345);spin_lock(&lIIIII);list_add(&lllll->llllII,&
lllllll);spin_unlock(&lIIIII);return lllll;}while((0x3ad+8946-0x269f));if(lllll)
{IIlIIIll(lllll);lllIII(lllll);}return NULL;}void IlllllII(struct lIlIl*lllll){
struct list_head*IIlIllIlI;IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x72\x65\x6d\x6f\x76\x65\x2b\x2b" "\n"
);
spin_lock(&lIIIII);list_for_each(IIlIllIlI,&lllllll){if(IIlIllIlI==&lllll->
llllII){list_del_init(&lllll->llllII);break;}}spin_unlock(&lIIIII);


if(IIlIllIlI==&lllll->llllII){
#ifdef _USBD_DEBUG_MEMORY_
atomic_inc(&IlIllIlI);
#endif


IIIIIIIll(lllll);lllllIll(lllll);}IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x72\x65\x6d\x6f\x76\x65\x2d\x2d" "\n"
);}void IllllIlII(void){struct lIlIl*lllll;IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x72\x65\x6d\x6f\x76\x65\x5f\x61\x6c\x6c\x2b\x2b" "\n"
);spin_lock(&lIIIII);while(!list_empty(&lllllll)){lllll=list_entry(lllllll.next,
struct lIlIl,llllII);list_del_init(&lllll->llllII);spin_unlock(&lIIIII);
#ifdef _USBD_DEBUG_MEMORY_
atomic_inc(&IlIllIlI);
#endif
IIIIIIIll(lllll);lllllIll(lllll);spin_lock(&lIIIII);}spin_unlock(&lIIIII);IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x72\x65\x6d\x6f\x76\x65\x5f\x61\x6c\x6c\x2d\x2d" "\n"
);}int lllIllIIl(struct lIlIl*lllll){int IlIlI;unsigned long flags;int lIIlI;
struct IllIlI*Illll;struct IllIlI*llIIllIl;IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x70\x6c\x75\x67\x3a\x20\x2b\x2b" "\n"
);IlIlI=IllIlIlII(lllll);if(IlIlI<(0xb23+1897-0x128c)){IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x70\x6c\x75\x67\x3a\x20\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x3d\x25\x64" "\n"
,IlIlI);return IlIlI;}Illll=IIllII(lllll->parent);llIIllIl=Illll->IllIIllI?
IIllII(Illll->IllIIllI):NULL;spin_lock_irqsave(&Illll->lock,flags);if(llIIllIl)
spin_lock(&llIIllIl->lock);IlIlI=-ENOENT;for(lIIlI=(0x848+1551-0xe57);lIIlI<
llIlll;lIIlI++){if((Illll->IIIIIII[lIIlI]==NULL)&&((llIIllIl==NULL)||(llIIllIl->
IIIIIII[lIIlI]==NULL))){IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x70\x6c\x75\x67\x3a\x20\x66\x6f\x75\x6e\x64\x20\x66\x72\x65\x65\x20\x70\x6f\x72\x74\x20\x25\x64" "\n"
,lIIlI);lIllIIlI(lllll);lllll->lIIlI=lIIlI;lllll->llllIlI=-(0x22f+5110-0x1624);
Illll->IIIIIII[lIIlI]=lllll;
#if KERNEL_GT_EQ((0x1671+2402-0x1fd1),(0x1c8a+2216-0x252c),(0x190+271-0x278)) ||\
 RHEL_RELEASE_GT_EQ((0x19b+7100-0x1d51),(0x1cf5+271-0x1e01)) 
if(lllll->parent->speed==HCD_USB3){lIIIlII(Illll,lIIlI,lIIIIIIl,
(0x11+9906-0x26c3));}else
#endif
{lIlIlII(Illll,lIIlI,lIIIIIIl,(0x1236+2929-0x1da7));}IlIlI=(0xcb6+4053-0x1c8b);
break;}}if(llIIllIl)spin_unlock(&llIIllIl->lock);spin_unlock_irqrestore(&Illll->
lock,flags);if(IlIlI<(0x7b5+7007-0x2314)){
lIIlIlIl(lllll);}else{
usb_hcd_poll_rh_status(lllll->parent);}IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x70\x6c\x75\x67\x3a\x20\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x3d\x25\x64" "\n"
,IlIlI);return IlIlI;}void IIIIIIIll(struct lIlIl*lllll){unsigned long flags;
struct IllIlI*Illll=IIllII(lllll->parent);IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x75\x6e\x70\x6c\x75\x67\x3a\x20\x2b\x2b" "\n"
);
lIIlIlIl(lllll);spin_lock_irqsave(&Illll->lock,flags);if(lllll->lIIlI!=-
(0x12fb+3626-0x2124)){IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x75\x6e\x70\x6c\x75\x67\x3a\x20\x75\x6e\x70\x6c\x75\x67\x67\x69\x6e\x67\x20\x76\x69\x72\x74\x75\x61\x6c\x20\x64\x65\x76\x69\x63\x65\x20\x61\x74\x20\x70\x6f\x72\x74\x20\x25\x64" "\n"
,lllll->lIIlI);

Illll->IIIIIII[lllll->lIIlI]=NULL;
#if KERNEL_GT_EQ((0x86d+6134-0x2061),(0x429+5337-0x18fc),(0x27+2962-0xb92)) || \
RHEL_RELEASE_GT_EQ((0x118+5228-0x157e),(0x1799+1611-0x1de1)) 
if(lllll->parent->speed==HCD_USB3){lIIIlII(Illll,lllll->lIIlI,IlIlIlI,
(0x9b8+3479-0x174f));}else
#endif
{lIlIlII(Illll,lllll->lIIlI,IlIlIlI,(0x1599+4375-0x26b0));}lllll->lIIlI=-
(0x22c+2854-0xd51);spin_unlock_irqrestore(&Illll->lock,flags);
usb_hcd_poll_rh_status(lllll->parent);IIllIlllI(lllll,-ENODEV);lllllIll(lllll);}
else{spin_unlock_irqrestore(&Illll->lock,flags);}IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x75\x6e\x70\x6c\x75\x67\x3a\x20\x2d\x2d" "\n"
);}struct lIlIl*IIlllIlll(int IlllllllI){struct lIlIl*lllll;IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x66\x69\x6e\x64\x31\x3a\x20\x2b\x2b" "\n"
);spin_lock(&lIIIII);list_for_each_entry(lllll,&lllllll,llllII){if(IlIIIIIl(
lllll->lIllI)==IlllllllI){lIllIIlI(lllll);spin_unlock(&lIIIII);IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x66\x69\x6e\x64\x31\x3a\x20\x2d\x2d\x20\x66\x6f\x75\x6e\x64\x21" "\n"
);return lllll;}}spin_unlock(&lIIIII);IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x66\x69\x6e\x64\x31\x3a\x20\x2d\x2d\x20\x6e\x6f\x74\x20\x66\x6f\x75\x6e\x64" "\n"
);return NULL;}
struct lIlIl*IlIIIIIlI(struct usb_hcd*IIlll,int llllIlI){struct IllIlI*Illll=
IIllII(IIlll);struct lIlIl*lllll=NULL;int lIIlI;IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x66\x69\x6e\x64\x32\x28\x29\x3a\x20\x2b\x2b\x20\x61\x64\x64\x72\x65\x73\x73\x20\x3d\x20\x25\x64" "\n"
,llllIlI);if(Illll==NULL)return NULL;if(llllIlI<(0x1215+3845-0x211a))return NULL
;for(lIIlI=(0x1ac8+620-0x1d34);lIIlI<llIlll;lIIlI++){if(Illll->IIIIIII[lIIlI]&&
Illll->IIIIIII[lIIlI]->llllIlI==llllIlI){lllll=Illll->IIIIIII[lIIlI];lIllIIlI(
lllll);break;}}IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x66\x69\x6e\x64\x32\x3a\x20\x2d\x2d\x20\x25\x73" "\n"
,lllll?"\x66\x6f\x75\x6e\x64":"\x6e\x6f\x74\x20\x66\x6f\x75\x6e\x64");return 
lllll;}
struct lIlIl*lIIIIIIll(struct usb_hcd*IIlll,int lIIlI){struct IllIlI*Illll=
IIllII(IIlll);struct lIlIl*lllll=NULL;IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x66\x69\x6e\x64\x33\x28\x29\x3a\x20\x2b\x2b\x20\x70\x6f\x72\x74\x20\x3d\x20\x25\x64" "\n"
,lIIlI);if(Illll==NULL)return NULL;if(lIIlI<=(0x571+3003-0x112c)||lIIlI>llIlll)
return NULL;lIIlI--;
if(Illll->IIIIIII[lIIlI]){lllll=Illll->IIIIIII[lIIlI];lIllIIlI(lllll);}IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x66\x69\x6e\x64\x33\x3a\x20\x2d\x2d\x20\x25\x73" "\n"
,lllll?"\x66\x6f\x75\x6e\x64":"\x6e\x6f\x74\x20\x66\x6f\x75\x6e\x64");return 
lllll;}void IlIlIIII(struct lIlIl*lllll){lIIll IIlIl;struct IlllIl*IllII;
unsigned long flags;IIlIl=IllllIl(sizeof(lIIIIlIlI),GFP_ATOMIC);if(!IIlIl){IlllI
(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x73\x65\x6e\x64\x5f\x72\x65\x73\x65\x74\x5f\x70\x6f\x72\x74\x3a\x20\x6e\x6f\x20\x6d\x65\x6d\x6f\x72\x79" "\n"
);return;}IllII=IIlIIIlII(lllll,GFP_ATOMIC);if(!IllII){IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x73\x65\x6e\x64\x5f\x72\x65\x73\x65\x74\x5f\x70\x6f\x72\x74\x3a\x20\x6e\x6f\x20\x6d\x65\x6d\x6f\x72\x79" "\n"
);lllIII(IIlIl);return;}IIlIl->IIIlI.lIlIlI=IllII->lIIIl;IIlIl->IIIlI.lIlIIll=
(0x925+4247-0x19bc);IIlIl->IIIlI.IIIlII=sizeof(lIIIIlIlI);IIlIl->IIIlI.IIlIlI=
IllIIIll;IIlIl->IIIlI.Status=(0x18e8+3091-0x24fb);IIlIl->IIIlI.Context=lllll->
lIIlI;IllII->IIlIl=IIlIl;spin_lock_irqsave(&lllll->llllll,flags);list_add_tail(&
IllII->IlIlIl,&lllll->IllIIll);spin_unlock_irqrestore(&lllll->llllll,flags);
wake_up(&lllll->lllIll);}struct IlllIl*IIlIIIlII(struct lIlIl*lllll,gfp_t llllI)
{struct IlllIl*IllII;IllII=IlIIllI(sizeof(struct IlllIl),llllI);if(!IllII){IlllI
(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x63\x72\x65\x61\x74\x65\x5f\x72\x65\x71\x75\x65\x73\x74\x3a\x20\x6e\x6f\x20\x6d\x65\x6d\x6f\x72\x79" "\n"
);return NULL;}
#ifdef _USBD_DEBUG_MEMORY_
atomic_inc(&llIIIlIlI);
#endif
INIT_LIST_HEAD(&IllII->IlIlIl);INIT_LIST_HEAD(&IllII->lIIIIIl);INIT_LIST_HEAD(&
IllII->urb.llllII);IllII->lIIIl=lIlllllIl();IllII->lllll=lIllIIlI(lllll);return 
IllII;}void IlllIIII(struct IlllIl*IllII){


#ifdef _USBD_DEBUG_MEMORY_
atomic_inc(&IlllIlIlI);
#endif
if(IllII->lllll)lllllIll(IllII->lllll);lllIII(IllII);}
int IlllIIlIl(struct IlllIl*IllII){struct usb_host_endpoint*ep;struct IlllIl*
IIlIIlI;if(!list_empty(&IllII->lIIIIIl)){struct llIIIIl*IIlllI=list_entry(IllII
->lIIIIIl.next,struct llIIIIl,llllII);
#if KERNEL_LT((0x947+6435-0x2268),(0x175+3596-0xf7b),(0x12db+2990-0x1e71))
ep=(usb_pipein(IIlllI->lIlll->pipe)?IIlllI->lIlll->dev->ep_in:IIlllI->lIlll->dev
->ep_out)[usb_pipeendpoint(IIlllI->lIlll->pipe)];
#else
ep=IIlllI->lIlll->ep;
#endif

if(ep&&ep->hcpriv==IllII){ep->hcpriv=NULL;

list_del_init(&IllII->IlIlIl);return(0xc84+5806-0x2331);}}
list_for_each_entry(IIlIIlI,&IllII->lllll->lIlIIlI,IlIlIl){if(IIlIIlI==IllII){
list_del_init(&IllII->IlIlIl);return(0xda5+1476-0x1368);}}
list_for_each_entry(IIlIIlI,&IllII->lllll->IlIIIIll,IlIlIl){if(IIlIIlI==IllII){
list_del_init(&IllII->IlIlIl);return(0x9f8+1555-0x100a);}}
list_for_each_entry(IIlIIlI,&IllII->lllll->IllIIll,IlIlIl){if(IIlIIlI==IllII){
list_del_init(&IllII->IlIlIl);return(0x12a5+51-0x12d7);}}return(0x370+79-0x3bf);
}int llIlllII(struct IlllIl*IllII){struct llIIIIl*IIlllI;list_for_each_entry(
IIlllI,&IllII->lIIIIIl,llllII){
#if KERNEL_LT((0x6ba+1102-0xb06),(0x1464+3167-0x20bd),(0x234+5473-0x177d))
spin_lock(&IIlllI->lIlll->lock);if(IIlllI->lIlll->status!=-EINPROGRESS){
spin_unlock(&IIlllI->lIlll->lock);return(0x1f16+1430-0x24ab);}spin_unlock(&
IIlllI->lIlll->lock);
#else
if(IIlllI->lIlll->unlinked)return(0x4d0+7297-0x2150);
#endif
}return(0x23aa+348-0x2506);}void IIllIlllI(struct lIlIl*lllll,int status){
unsigned long flags;struct list_head IIlllllI;struct IlllIl*IllII;INIT_LIST_HEAD
(&IIlllllI);spin_lock_irqsave(&IIllII(lllll->parent)->lock,flags);spin_lock(&
lllll->llllll);list_for_each_entry(IllII,&lllll->lIlIIlI,IlIlIl){struct llIIIIl*
lIlIII;list_for_each_entry(lIlIII,&IllII->lIIIIIl,llllII){struct 
usb_host_endpoint*ep;
#if KERNEL_LT((0x10e4+251-0x11dd),(0x5dd+2535-0xfbe),(0xbb9+999-0xf88))
ep=(usb_pipein(lIlIII->lIlll->pipe)?lIlIII->lIlll->dev->ep_in:lIlIII->lIlll->dev
->ep_out)[usb_pipeendpoint(lIlIII->lIlll->pipe)];
#else
ep=lIlIII->lIlll->ep;
#endif
if(ep)ep->hcpriv=NULL;}}list_splice_init(&lllll->lIlIIlI,&IIlllllI);
list_splice_init(&lllll->IllIIll,&IIlllllI);list_splice_init(&lllll->IlIIIIll,&
IIlllllI);spin_unlock(&lllll->llllll);spin_unlock_irqrestore(&IIllII(lllll->
parent)->lock,flags);while(!list_empty(&IIlllllI)){struct IlllIl*IllII=
list_entry(IIlllllI.next,struct IlllIl,IlIlIl);list_del_init(&IllII->IlIlIl);
lIllIIIl(IllII,status);IlllIIII(IllII);}}void lIllIIIl(struct IlllIl*IllII,int 
status){struct lIlIl*lllll=IllII->lllll;
#if KERNEL_GT_EQ((0x17eb+2897-0x233a),(0x191+5218-0x15ed),(0x4f2+7033-0x2053))
struct IllIlI*Illll=IIllII(lllll->parent);
#endif
unsigned long flags;int lIlIIIIlI=(0xf4+6502-0x1a5a);IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x67\x69\x76\x65\x62\x61\x63\x6b\x5f\x72\x65\x71\x75\x65\x73\x74\x3a\x20\x72\x65\x71\x75\x65\x73\x74\x20\x30\x78\x25\x70\x20\x73\x74\x61\x74\x75\x73\x3d\x25\x64" "\n"
,IllII,status);local_irq_save(flags);while(!list_empty(&IllII->lIIIIIl)){struct 
llIIIIl*IIlllI=list_entry(IllII->lIIIIIl.next,struct llIIIIl,llllII);if(IIlllI->
lIlll){int llIlIlIl=status;

if(usb_pipetype(IIlllI->lIlll->pipe)==PIPE_BULK||usb_pipetype(IIlllI->lIlll->
pipe)==PIPE_INTERRUPT){






switch(lIlIIIIlI){case(0xe30+1430-0x13c6):if(IIlllI->lIlll->actual_length<IIlllI
->lIlll->transfer_buffer_length){if((status==(0x1d4+6499-0x1b37))&&(IIlllI->
lIlll->transfer_flags&URB_SHORT_NOT_OK)){llIlIlIl=-EREMOTEIO;}else{llIlIlIl=
status;}lIlIIIIlI=(0x9e2+1891-0x1144);}else if(IIlllI->llllII.next==&IllII->
lIIIIIl){llIlIlIl=status;lIlIIIIlI=(0x3c+2191-0x8ca);}else{llIlIlIl=
(0x902+2543-0x12f1);}break;case(0x154c+230-0x1631):llIlIlIl=-ECONNRESET;break;}}
IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x67\x69\x76\x65\x62\x61\x63\x6b\x5f\x72\x65\x71\x75\x65\x73\x74\x3a\x20\x67\x69\x76\x65\x62\x61\x63\x6b\x20\x75\x72\x62\x20\x30\x78\x25\x70\x20\x77\x69\x74\x68\x20\x73\x74\x61\x74\x75\x73\x20\x25\x64" "\n"
,IIlllI->lIlll,llIlIlIl);
#if KERNEL_LT((0xe64+528-0x1072),(0x8c6+2471-0x1267),(0xaaa+3688-0x18fa))


spin_lock(&IIlllI->lIlll->lock);if(IIlllI->lIlll->status==-EINPROGRESS)IIlllI->
lIlll->status=llIlIlIl;spin_unlock(&IIlllI->lIlll->lock);
#else


spin_lock(&Illll->lock);usb_hcd_unlink_urb_from_ep(lllll->parent,IIlllI->lIlll);
spin_unlock(&Illll->lock);
#endif



IIlllI->lIlll->hcpriv=NULL;
#if KERNEL_LT((0xdd3+5206-0x2227),(0x1536+585-0x1779),(0x807+4318-0x18d2))
usb_hcd_giveback_urb(lllll->parent,IIlllI->lIlll,NULL);
#elif KERNEL_LT((0x7bf+4622-0x19cb),(0x739+7716-0x2557),(0xe4f+3669-0x1c8c))
usb_hcd_giveback_urb(lllll->parent,IIlllI->lIlll);
#else
usb_hcd_giveback_urb(lllll->parent,IIlllI->lIlll,llIlIlIl);
#endif
}list_del_init(&IIlllI->llllII);if(IIlllI!=&IllII->urb)lllIII(IIlllI);}
local_irq_restore(flags);if(IllII->IIlIl){if(IllII->IIlIl->IIIlI.IIlIlI==
IllIIIll){IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x67\x69\x76\x65\x62\x61\x63\x6b\x5f\x72\x65\x71\x75\x65\x73\x74\x3a\x20\x72\x65\x73\x65\x74\x20\x63\x6f\x6d\x70\x6c\x65\x74\x65\x64" "\n"
);lllll->lIIIlIII=(0x31f+4363-0x142a);wake_up(&lllll->lllIll);}IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x67\x69\x76\x65\x62\x61\x63\x6b\x5f\x72\x65\x71\x75\x65\x73\x74\x3a\x20\x66\x72\x65\x65\x69\x6e\x67\x20\x75\x6e\x72\x62" "\n"
);lllIII(IllII->IIlIl);IllII->IIlIl=NULL;}}int IllIIlIll(struct lIlIl*lllll,
struct IlllIl*IllII,lIIll IIlIl){int IlIlI=(0x1d8f+1316-0x22b3);if(!list_empty(&
IllII->lIIIIIl)){IlIlI=IIlIIIIlI(&IllII->lIIIIIl,IllII->lIIIl,IIlIl);}else if(
IllII->IIlIl){memcpy(IIlIl,IllII->IIlIl,IllII->IIlIl->IIIlI.IIIlII);if(IllII->
IIlIl->IIIlI.IIlIlI==IllIIIll){lllll->lIIIlIII=(0x84+9160-0x244b);}}else{IlIlI=-
EIO;}IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x70\x61\x63\x6b\x5f\x72\x65\x71\x75\x65\x73\x74\x3a\x20\x72\x65\x73\x75\x6c\x74\x20\x3d\x20\x25\x64" "\n"
,IlIlI);return IlIlI;}int IlIIIIlIl(struct lIlIl*lllll,struct IlllIl*IllII,lIIll
 IIlIl,int*status){int IlIlI;if(!list_empty(&IllII->lIIIIIl)){IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x75\x6e\x70\x61\x63\x6b\x5f\x72\x65\x71\x75\x65\x73\x74\x3a\x20\x75\x6e\x70\x61\x63\x6b\x69\x6e\x67\x20\x75\x72\x62" "\n"
);IlIlI=IlIlIIIII(IIlIl,&IllII->lIIIIIl,status);}else{*status=lIIIllIl(IIlIl->
IIIlI.Status);IlIlI=(0x40b+3211-0x1096);}return IlIlI;}void llIIIllll(struct 
kref*llllIlII){struct lIlIl*lllll=container_of(llllIlII,struct lIlIl,lllllIl);
IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x64\x65\x73\x74\x72\x6f\x79\x28\x70\x76\x73\x74\x75\x62\x3d\x30\x78\x25\x70\x29" "\n"
,lllll);
#ifdef _USBD_DEBUG_MEMORY_
atomic_inc(&lIIlllIII);
#endif
IIlIIIll(lllll);lllIII(lllll);}
static inline size_t llllIIlll(struct urb*lIlll,void*IIIIl){int i;void*lllIIl;if
(!lIlll->transfer_buffer)return(0xcd1+2564-0x16d5);lllIIl=IIIIl;for(i=
(0x1bc6+436-0x1d7a);i<lIlll->number_of_packets;i++){memcpy(lIlll->
transfer_buffer+lIlll->iso_frame_desc[i].offset,lllIIl,lIlll->iso_frame_desc[i].
actual_length);lllIIl+=lIlll->iso_frame_desc[i].actual_length;}return(size_t)(
lllIIl-IIIIl);}
#if defined(CONFIG_X86_32) && !defined(_USBD_VHCI_NO_DMA_)






int IllIIlII(void*IIIIl,struct urb*lIlll,int IIlII){
if(IIlII==(0x1465+0-0x1465))return(0x4c2+3803-0x139d);if(IIIlllII&&((lIlll->
transfer_buffer==NULL)||(lIlll->transfer_flags&URB_NO_TRANSFER_DMA_MAP))&&(lIlll
->transfer_dma!=(0xf31+590-0x117f))&&(lIlll->transfer_dma!=~(dma_addr_t)
(0x80d+1397-0xd82))){IllIlIIl(IIIIl,lIlll->transfer_dma,IIlII);}else if(lIlll->
transfer_buffer){memcpy(IIIIl,lIlll->transfer_buffer,IIlII);}else return-EINVAL;
return IIlII;}





int IlIIlIll(struct urb*lIlll,void*IIIIl,int IIlII){
if(IIlII==(0x71a+3417-0x1473))return(0x2c2+1162-0x74c);if(IIIlllII&&((lIlll->
transfer_buffer==NULL)||(lIlll->transfer_flags&URB_NO_TRANSFER_DMA_MAP))&&(lIlll
->transfer_dma!=(0x11b6+2570-0x1bc0))&&(lIlll->transfer_dma!=~(dma_addr_t)
(0x4f2+1039-0x901))){llIlllll(lIlll->transfer_dma,IIIIl,IIlII);}else if(lIlll->
transfer_buffer){memcpy(lIlll->transfer_buffer,IIIIl,IIlII);}else return-EINVAL;
return IIlII;}





int llllllIIl(void*IIIIl,struct urb*lIlll,int IIlII){
if(IIlII==(0x495+4421-0x15da))return(0xcd9+5813-0x238e);
#if KERNEL_LT_EQ((0x9cb+6722-0x240b),(0x85a+3315-0x1547),(0x15df+1960-0x1d65))
if(IIIlllII&&((lIlll->setup_packet==NULL)||(lIlll->transfer_flags&
URB_NO_SETUP_DMA_MAP))&&(lIlll->setup_dma!=(0x833+3496-0x15db))&&(lIlll->
setup_dma!=~(dma_addr_t)(0x1613+3678-0x2471))){IllIlIIl(IIIIl,lIlll->setup_dma,
IIlII);}else
#endif
if(lIlll->setup_packet){memcpy(IIIIl,lIlll->setup_packet,IIlII);}else return-
EINVAL;return IIlII;}





int IlIllIIIl(struct urb*lIlll,void*IIIIl,int IIlII){
if(IIlII==(0x14ba+390-0x1640))return(0x8d5+4251-0x1970);
#if KERNEL_LT_EQ((0xb90+1480-0x1156),(0x831+7341-0x24d8),(0x373+924-0x6ed))
if(IIIlllII&&((lIlll->setup_packet==NULL)||(lIlll->transfer_flags&
URB_NO_SETUP_DMA_MAP))&&(lIlll->setup_dma!=(0x975+327-0xabc))&&(lIlll->setup_dma
!=~(dma_addr_t)(0x7dd+2027-0xfc8))){llIlllll(lIlll->setup_dma,IIIIl,IIlII);}else
#endif
if(lIlll->setup_packet){memcpy(lIlll->setup_packet,IIIIl,IIlII);}else return-
EINVAL;return IIlII;}


static inline size_t lIIIlIlII(void*IIIIl,struct urb*lIlll){if(IIIlllII&&((lIlll
->transfer_buffer==NULL)||(lIlll->transfer_flags&URB_NO_TRANSFER_DMA_MAP))&&(
lIlll->transfer_dma!=(0x655+6895-0x2144))&&(lIlll->transfer_dma!=~(dma_addr_t)
(0xbe1+5977-0x233a))){int i;void*lIIlIII=IIIIl;dma_addr_t lllIIl;void*IllIIl;
unsigned long flags;unsigned long lIIllI,IIlIIl;unsigned long IlIlllI,IllIllI,
lllIIIl,lIIlIIl;lllIIIl=(0x1db6+697-0x206f);IllIIl=NULL;local_irq_save(flags);
for(i=(0x12df+3338-0x1fe9);i<lIlll->number_of_packets;i++){IIlIIl=lIlll->
iso_frame_desc[i].length;lllIIl=lIlll->transfer_dma+lIlll->iso_frame_desc[i].
offset;while(IIlIIl){lIIlIIl=lllIIl>>PAGE_SHIFT;if(lIIlIIl!=lllIIIl){if(lllIIIl)
#if KERNEL_GT_EQ((0xf70+5296-0x241e),(0x5b9+7046-0x2139),(0x189+5336-0x163c))
kunmap_atomic(IllIIl);
#else
kunmap_atomic(IllIIl,KM_IRQ0);
#endif
lllIIIl=lIIlIIl;
#if KERNEL_GT_EQ((0x998+126-0xa14),(0xf6c+5844-0x263a),(0xe13+1626-0x1448))
IllIIl=kmap_atomic(pfn_to_page(lIIlIIl));
#else
IllIIl=kmap_atomic(pfn_to_page(lIIlIIl),KM_IRQ0);
#endif
}IlIlllI=lllIIl&(PAGE_SIZE-(0xdb0+6447-0x26de));IllIllI=PAGE_SIZE-IlIlllI;lIIllI
=(IllIllI<IIlIIl)?IllIllI:IIlIIl;memcpy(lIIlIII,IllIIl+IlIlllI,lIIllI);lllIIl+=
lIIllI;lIIlIII+=lIIllI;IIlIIl-=lIIllI;}}if(lllIIIl)
#if KERNEL_GT_EQ((0x1c30+1392-0x219e),(0x1b31+1206-0x1fe1),(0xc71+3361-0x196d))
kunmap_atomic(IllIIl);
#else
kunmap_atomic(IllIIl,KM_IRQ0);
#endif
local_irq_restore(flags);IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x70\x61\x63\x6b\x5f\x69\x73\x6f\x63\x68\x5f\x62\x75\x66\x3a\x20\x70\x61\x63\x6b\x65\x64\x3d\x25\x6c\x75" "\n"
,(unsigned long)(lIIlIII-IIIIl));return(size_t)(lIIlIII-IIIIl);}else if(lIlll->
transfer_buffer){return IIIllIll(lIlll->iso_frame_desc,lIlll->number_of_packets,
IIIIl,lIlll->transfer_buffer,(0x21d3+597-0x2428));}IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x70\x61\x63\x6b\x5f\x69\x73\x6f\x63\x68\x5f\x62\x75\x66\x3a\x20\x6e\x6f\x20\x62\x75\x66\x66\x65\x72" "\n"
);return(0x33f+5902-0x1a4d);}static inline size_t lIllIlllI(struct urb*lIlll,
void*IIIIl){if(IIIlllII&&((lIlll->transfer_buffer==NULL)||(lIlll->transfer_flags
&URB_NO_TRANSFER_DMA_MAP))&&(lIlll->transfer_dma!=(0xe9d+6257-0x270e))&&(lIlll->
transfer_dma!=~(dma_addr_t)(0x1d59+1826-0x247b))){int i;void*lllIIl=IIIIl;
dma_addr_t lIIlIII;void*IllIIl;unsigned long flags;unsigned long lIIllI,IIlIIl;
unsigned long IlIlllI,IllIllI,lllIIIl,lIIlIIl;lllIIIl=(0x1395+2779-0x1e70);
IllIIl=NULL;local_irq_save(flags);for(i=(0x1227+634-0x14a1);i<lIlll->
number_of_packets;i++){IIlIIl=lIlll->iso_frame_desc[i].actual_length;lIIlIII=
lIlll->transfer_dma+lIlll->iso_frame_desc[i].offset;while(IIlIIl){lIIlIIl=
lIIlIII>>PAGE_SHIFT;if(lIIlIIl!=lllIIIl){if(lllIIIl)
#if KERNEL_GT_EQ((0x649+5456-0x1b97),(0x109a+1388-0x1600),(0xb6f+1374-0x10a8))
kunmap_atomic(IllIIl);
#else
kunmap_atomic(IllIIl,KM_IRQ0);
#endif
lllIIIl=lIIlIIl;
#if KERNEL_GT_EQ((0xee8+3717-0x1d6b),(0x343+3526-0x1103),(0xbc6+6466-0x24e3))
IllIIl=kmap_atomic(pfn_to_page(lIIlIIl));
#else
IllIIl=kmap_atomic(pfn_to_page(lIIlIIl),KM_IRQ0);
#endif
}IlIlllI=lIIlIII&(PAGE_SIZE-(0xe1f+5160-0x2246));IllIllI=PAGE_SIZE-IlIlllI;
lIIllI=(IllIllI<IIlIIl)?IllIllI:IIlIIl;memcpy(IllIIl+IlIlllI,lllIIl,lIIllI);
lllIIl+=lIIllI;lIIlIII+=lIIllI;IIlIIl-=lIIllI;}}if(lllIIIl)
#if KERNEL_GT_EQ((0xc40+2109-0x147b),(0xddf+6300-0x2675),(0xbcd+4060-0x1b84))
kunmap_atomic(IllIIl);
#else
kunmap_atomic(IllIIl,KM_IRQ0);
#endif
local_irq_restore(flags);IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x75\x6e\x70\x61\x63\x6b\x5f\x69\x73\x6f\x63\x68\x5f\x62\x75\x66\x3a\x20\x70\x61\x63\x6b\x65\x64\x3d\x25\x6c\x75" "\n"
,(unsigned long)(lllIIl-IIIIl));return(size_t)(lllIIl-IIIIl);}else if(lIlll->
transfer_buffer){return llllIIlll(lIlll,IIIIl);}IlllI(
"\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x75\x6e\x70\x61\x63\x6b\x5f\x69\x73\x6f\x63\x68\x5f\x62\x75\x66\x3a\x20\x6e\x6f\x20\x62\x75\x66\x66\x65\x72" "\n"
);return(0x32+6660-0x1a36);}
#else 

static inline int IlIIlIll(struct urb*lIlll,void*IIIIl,int IIlII){if(!IIlII)
return(0x268+9258-0x2692);if(!lIlll->transfer_buffer)return-EINVAL;memcpy(lIlll
->transfer_buffer,IIIIl,IIlII);return IIlII;}static inline int IllIIlII(void*
IIIIl,struct urb*lIlll,int IIlII){if(!IIlII)return(0x1885+1937-0x2016);if(!lIlll
->transfer_buffer)return-EINVAL;memcpy(IIIIl,lIlll->transfer_buffer,IIlII);
return IIlII;}static inline int IlIllIIIl(struct urb*lIlll,void*IIIIl,int IIlII)
{if(!IIlII)return(0x1f3+2407-0xb5a);if(!lIlll->setup_packet)return-EINVAL;memcpy
(lIlll->setup_packet,IIIIl,IIlII);return IIlII;}static inline int llllllIIl(void
*IIIIl,struct urb*lIlll,int IIlII){if(!IIlII)return(0x938+5821-0x1ff5);if(!lIlll
->setup_packet)return-EINVAL;memcpy(IIIIl,lIlll->setup_packet,IIlII);return 
IIlII;}static inline size_t lIIIlIlII(void*IIIIl,struct urb*lIlll){if(!lIlll->
transfer_buffer)return(0x1c99+101-0x1cfe);return IIIllIll(lIlll->iso_frame_desc,
lIlll->number_of_packets,IIIIl,lIlll->transfer_buffer,(0x127d+2508-0x1c49));}

static inline size_t lIllIlllI(struct urb*lIlll,void*IIIIl){return llllIIlll(
lIlll,IIIIl);}
#endif 




static inline int IlIIlllII(struct list_head*IIIIIIl,Illlll lIIIl,void*IIIIl){
int IlIlI=(0x218c+973-0x2559);int lIlllII=sizeof(IlIlllIll);lIIll IIlIl=IIIIl;
struct llIIIIl*lIlIII;IIlIl->IIIlI.lIlIlI=lIIIl;IIlIl->IIIlI.lIlIIll=
(0x87+1836-0x7b3);IIlIl->IIIlI.IIIlII=lIlllII;IIlIl->IIIlI.IIlIlI=lllIlIlI;IIlIl
->IIIlI.Status=(0x64c+4996-0x19d0);IIlIl->IIIlI.Context=(0x18e6+2266-0x21c0);
lIlIII=list_entry(IIIIIIl->prev,struct llIIIIl,llllII);IIlIl->lIllIl.IlIll=
(0x197d+3032-0x2555);IIlIl->lIllIl.Endpoint=usb_pipeendpoint(lIlIII->lIlll->pipe
);IIlIl->lIllIl.Flags=usb_pipein(lIlIII->lIlll->pipe)?IIIIIl:(0xde6+4557-0x1fb3)
;
if(usb_pipein(lIlIII->lIlll->pipe)&&!(lIlIII->lIlll->transfer_flags&
URB_SHORT_NOT_OK)){IIlIl->lIllIl.Flags|=Illllll;}


list_for_each_entry(lIlIII,IIIIIIl,llllII){if(usb_pipeout(lIlIII->lIlll->pipe)){
if(IllIIlII((char*)IIIIl+IIlIl->IIIlI.IIIlII,lIlIII->lIlll,lIlIII->lIlll->
transfer_buffer_length)<(0xc65+4558-0x1e33))return-EINVAL;IIlIl->IIIlI.IIIlII+=
lIlIII->lIlll->transfer_buffer_length;}IIlIl->lIllIl.IlIll+=lIlIII->lIlll->
transfer_buffer_length;}return IlIlI;}static inline int lllIIIIlI(struct urb*
lIlll,Illlll lIIIl,void*IIIIl){int IlIlI=(0x1d35+2082-0x2557);int lIlllII=sizeof
(IlIIlIllI);lIIll IIlIl=IIIIl;IIlIl->IIIlI.lIlIlI=lIIIl;IIlIl->IIIlI.lIlIIll=
(0x13e6+4901-0x270b);IIlIl->IIIlI.IIIlII=lIlllII;IIlIl->IIIlI.IIlIlI=lIIlllII;
IIlIl->IIIlI.Status=(0xa74+873-0xddd);IIlIl->IIIlI.Context=(0xd07+4055-0x1cde);
IIlIl->IIIIII.IlIll=lIlll->transfer_buffer_length;IIlIl->IIIIII.Interval=lIlll->
interval;IIlIl->IIIIII.Endpoint=usb_pipeendpoint(lIlll->pipe);IIlIl->IIIIII.
Flags=usb_pipein(lIlll->pipe)?IIIIIl:(0x1445+325-0x158a);IIlIl->IIIIII.Flags|=(
lIlll->transfer_flags&URB_SHORT_NOT_OK)?(0x49b+7161-0x2094):Illllll;if(
usb_pipeout(lIlll->pipe)){if(IllIIlII((char*)IIIIl+lIlllII,lIlll,lIlll->
transfer_buffer_length)<(0x1966+654-0x1bf4))return-EINVAL;IIlIl->IIIlI.IIIlII+=
lIlll->transfer_buffer_length;}return IlIlI;}static inline int lIlIIIIll(struct 
urb*lIlll,Illlll lIIIl,void*IIIIl){int IlIlI=(0x1402+883-0x1775);lIIll IIlIl=
IIIIl;int i;int lIlllII=sizeof(llIIIllI)-sizeof(IIIIlII)+sizeof(IIIIlII)*lIlll->
number_of_packets;IIlIl->IIIlI.lIlIlI=lIIIl;IIlIl->IIIlI.lIlIIll=
(0x3fd+825-0x736);IIlIl->IIIlI.IIIlII=lIlllII;IIlIl->IIIlI.IIlIlI=lIIlIIIl;IIlIl
->IIIlI.Status=(0x3e0+7847-0x2287);IIlIl->IIIlI.Context=(0xb04+2701-0x1591);
IIlIl->llIIl.Endpoint=usb_pipeendpoint(lIlll->pipe);IIlIl->llIIl.Flags=
usb_pipein(lIlll->pipe)?IIIIIl:(0x6c0+5446-0x1c06);IIlIl->llIIl.Flags|=(lIlll->
transfer_flags&URB_SHORT_NOT_OK)?(0x15c3+1860-0x1d07):Illllll;IIlIl->llIIl.Flags
|=(lIlll->transfer_flags&URB_ISO_ASAP)?lIIIIlll:(0x773+7785-0x25dc);IIlIl->llIIl
.IlIll=lIlll->transfer_buffer_length;IIlIl->llIIl.Interval=lIlll->interval;IIlIl
->llIIl.lllIIlll=lIlll->start_frame;IIlIl->llIIl.llllIlll=(0xacc+788-0xde0);
IIlIl->llIIl.lIllIlI=lIlll->number_of_packets;for(i=(0x1c8+2872-0xd00);i<lIlll->
number_of_packets;i++){IIlIl->llIIl.IIlIIll[i].Offset=lIlll->iso_frame_desc[i].
offset;IIlIl->llIIl.IIlIIll[i].Length=lIlll->iso_frame_desc[i].length;IIlIl->
llIIl.IIlIIll[i].Status=(0x61d+7654-0x2403);}if(usb_pipeout(lIlll->pipe))IIlIl->
IIIlI.IIIlII+=lIIIlIlII((char*)IIIIl+lIlllII,lIlll);return IlIlI;}static inline 
int llIllIIIl(struct urb*lIlll,Illlll lIIIl,struct usb_ctrlrequest*IIlllIl,void*
IIIIl){int IlIlI=(0x262+656-0x4f2);lIIll IIlIl=IIIIl;int lIlllII=sizeof(
IlIIlIlll);IIlIl->IIIlI.lIlIlI=lIIIl;IIlIl->IIIlI.lIlIIll=(0x708+1033-0xb11);
IIlIl->IIIlI.IIIlII=lIlllII;IIlIl->IIIlI.IIlIlI=llIlIIlI;IIlIl->IIIlI.Status=
(0x17bc+2093-0x1fe9);IIlIl->IIIlI.Context=(0x991+4310-0x1a67);IIlIl->IIIllI.
Endpoint=usb_pipeendpoint(lIlll->pipe);IIlIl->IIIllI.Flags=usb_pipein(lIlll->
pipe)?IIIIIl:(0x1e77+1315-0x239a);if(usb_pipein(lIlll->pipe))IIlIl->IIIllI.Flags
|=(lIlll->transfer_flags&URB_SHORT_NOT_OK)?(0xdb6+682-0x1060):Illllll;IIlIl->
IIIllI.IIlllII=IIlllIl->bRequestType;IIlIl->IIIllI.lIlIIIII=IIlllIl->bRequest;
IIlIl->IIIllI.IlllIIIl=le16_to_cpu(IIlllIl->wValue);IIlIl->IIIllI.IIIIlllll=
le16_to_cpu(IIlllIl->wIndex);IIlIl->IIIllI.IlIll=lIlll->transfer_buffer_length;
if(usb_pipeout(lIlll->pipe)){if(IllIIlII((char*)IIIIl+lIlllII,lIlll,lIlll->
transfer_buffer_length)<(0x598+630-0x80e))return-EINVAL;IIlIl->IIIlI.IIIlII+=
lIlll->transfer_buffer_length;}return IlIlI;}static inline int lIlIlIlIl(struct 
urb*lIlll,Illlll lIIIl,struct usb_ctrlrequest*IIlllIl,void*IIIIl,int lIlIlIll){
int IlIlI=(0x1be8+2462-0x2586);lIIll IIlIl=IIIIl;int lIlllII=sizeof(IIIlIlllI);
IIlIl->IIIlI.lIlIlI=lIIIl;IIlIl->IIIlI.lIlIIll=(0xcf+400-0x25f);IIlIl->IIIlI.
IIIlII=lIlllII;IIlIl->IIIlI.IIlIlI=lIlIlIll?lllllIIl:lIIlllll;IIlIl->IIIlI.
Status=(0x700+8049-0x2671);IIlIl->IIIlI.Context=(0x104+137-0x18d);IIlIl->IllIII.
IllllIll=le16_to_cpu(IIlllIl->wIndex);IIlIl->IllIII.IlIll=lIlll->
transfer_buffer_length;IIlIl->IllIII.IlllIlll=(le16_to_cpu(IIlllIl->wValue)>>
(0xaaf+1437-0x1044))&(0x690+7512-0x22e9);IIlIl->IllIII.IIIIIIlI=le16_to_cpu(
IIlllIl->wValue)&(0x72c+3595-0x1438);switch(IIlllIl->bRequestType&USB_TYPE_MASK)
{case USB_TYPE_STANDARD:IIlIl->IllIII.IIlllII=IlllllIll;break;case 
USB_TYPE_CLASS:IIlIl->IllIII.IIlllII=IIllIIllI;break;case USB_TYPE_VENDOR:IIlIl
->IllIII.IIlllII=IIlllllIl;break;case USB_TYPE_RESERVED:IIlIl->IllIII.IIlllII=
llIIlIlIl;break;default:IIlIl->IllIII.IIlllII=(0x1dd+715-0x4a8);}switch(IIlllIl
->bRequestType&USB_RECIP_MASK){case USB_RECIP_DEVICE:IIlIl->IllIII.IIIIIllI=
IllllIIII;break;case USB_RECIP_INTERFACE:IIlIl->IllIII.IIIIIllI=lIllIllII;break;
case USB_RECIP_ENDPOINT:IIlIl->IllIII.IIIIIllI=lIlIlIIlI;break;case 
USB_RECIP_OTHER:IIlIl->IllIII.IIIIIllI=IlllIIIIl;break;default:IIlIl->IllIII.
IIlllII=(0xc30+3519-0x19ef);}if(!lIlIlIll){if(IllIIlII((char*)IIIIl+lIlllII,
lIlll,lIlll->transfer_buffer_length)<(0xd4d+371-0xec0))return-EINVAL;IIlIl->
IIIlI.IIIlII+=lIlll->transfer_buffer_length;}return IlIlI;}static inline int 
lIlIIIllI(struct urb*lIlll,Illlll lIIIl,struct usb_ctrlrequest*IIlllIl,void*
IIIIl){int IlIlI=(0xad2+6347-0x239d);lIIll IIlIl=IIIIl;int IIlIIlIl=sizeof(
llIlIlllI);IIlIl->IIIlI.lIlIlI=lIIIl;IIlIl->IIIlI.lIlIIll=(0x1032+5527-0x25c9);
IIlIl->IIIlI.IIIlII=IIlIIlIl;IIlIl->IIIlI.IIlIlI=lIIlIIII;IIlIl->IIIlI.Status=
(0x1331+2852-0x1e55);IIlIl->IIIlI.Context=(0x12a4+3102-0x1ec2);IIlIl->IlllIIl.
IIllllI=(IIIII)le16_to_cpu(IIlllIl->wIndex);IIlIl->IlllIIl.IlllIII=(IIIII)
le16_to_cpu(IIlllIl->wValue);return IlIlI;}static inline int IlIlllllI(struct 
urb*lIlll,Illlll lIIIl,struct usb_ctrlrequest*IIlllIl,void*IIIIl){int IlIlI=
(0xf2c+848-0x127c);lIIll IIlIl=IIIIl;int IIlIIlIl=sizeof(IlllIIIlI)-sizeof(IIlIl
->IIIIlI.lllIlII[(0x54f+1708-0xbfb)]);IIlIl->IIIlI.lIlIlI=lIIIl;IIlIl->IIIlI.
lIlIIll=(0xec2+654-0x1150);IIlIl->IIIlI.IIIlII=IIlIIlIl;IIlIl->IIIlI.IIlIlI=
IIllllII;IIlIl->IIIlI.Status=(0x80f+6182-0x2035);IIlIl->IIIlI.Context=
(0x421+1004-0x80d);IIlIl->IIIIlI.IlIIIIII=(IIIII)le16_to_cpu(IIlllIl->wValue);
IIlIl->IIIIlI.IllllIIl=(0x831+2808-0x1329);return IlIlI;}static inline int 
lllIIIlII(struct urb*lIlll,Illlll lIIIl,struct usb_ctrlrequest*IIlllIl,void*
IIIIl){int IlIlI=(0xe3d+2419-0x17b0);lIIll IIlIl=IIIIl;int IIlIIlIl=sizeof(
lIllIlIll);IIlIl->IIIlI.lIlIlI=lIIIl;IIlIl->IIIlI.lIlIIll=(0x1d48+822-0x207e);
IIlIl->IIIlI.IIIlII=IIlIIlIl;IIlIl->IIIlI.IIlIlI=lllIllll;IIlIl->IIIlI.Status=
(0x792+1560-0xdaa);IIlIl->IIIlI.Context=(0x194+4126-0x11b2);IIlIl->llIlIlI.
Endpoint=IIlllIl->wIndex&(0x72d+721-0x9ef);
IIlIl->llIlIlI.Flags=(IIlllIl->wIndex&USB_DIR_IN)?IIIIIl:(0x1b37+396-0x1cc3);
return IlIlI;}int IIlIIIIlI(struct list_head*IIIIIIl,Illlll lIIIl,void*IIIIl){
int IlIlI=-EINVAL;do
{struct usb_ctrlrequest lIIlIl;struct urb*lIlll;struct llIIIIl*lIlIII;lIlIII=
list_entry(IIIIIIl->next,struct llIIIIl,llllII);lIlll=lIlIII->lIlll;if(!lIlll){
IlllI(
"\x75\x73\x62\x64\x5f\x70\x61\x63\x6b\x5f\x75\x72\x62\x5f\x6c\x69\x73\x74\x3a\x20\x70\x75\x72\x62\x20\x69\x73\x20\x6e\x75\x6c\x6c\x28\x30\x78\x25\x70\x29\x2c\x20\x70\x76\x75\x72\x62\x3d\x30\x78\x25\x70\x20\x70\x75\x72\x62\x5f\x6c\x69\x73\x74\x3d\x30\x78\x25\x70" "\n"
,lIlll,lIlIII,IIIIIIl);break;}switch(usb_pipetype(lIlll->pipe)){case PIPE_BULK:
IlIlI=IlIIlllII(IIIIIIl,lIIIl,IIIIl);break;case PIPE_INTERRUPT:IlIlI=lllIIIIlI(
lIlll,lIIIl,IIIIl);break;case PIPE_ISOCHRONOUS:IlIlI=lIlIIIIll(lIlll,lIIIl,IIIIl
);break;case PIPE_CONTROL:IlIlI=llllllIIl(&lIIlIl,lIlll,sizeof(lIIlIl));if(IlIlI
<(0x1b28+2385-0x2479))break;if(IlIlI!=sizeof(lIIlIl)){IlIlI=-EINVAL;break;}if(
lIIlIl.bRequestType==(USB_DIR_IN|USB_TYPE_STANDARD|USB_RECIP_DEVICE)&&lIIlIl.
bRequest==USB_REQ_GET_DESCRIPTOR){
IlIlI=lIlIlIlIl(lIlll,lIIIl,&lIIlIl,IIIIl,(0xc91+6217-0x24d9));}else if(lIIlIl.
bRequestType==(USB_DIR_OUT|USB_TYPE_STANDARD|USB_RECIP_DEVICE)&&lIIlIl.bRequest
==USB_REQ_SET_DESCRIPTOR){
IlIlI=lIlIlIlIl(lIlll,lIIIl,&lIIlIl,IIIIl,(0x62d+587-0x878));}else if(lIIlIl.
bRequestType==(USB_DIR_OUT|USB_TYPE_STANDARD|USB_RECIP_DEVICE)&&lIIlIl.bRequest
==USB_REQ_SET_CONFIGURATION){
IlIlI=IlIlllllI(lIlll,lIIIl,&lIIlIl,IIIIl);}else if(lIIlIl.bRequestType==(
USB_DIR_OUT|USB_TYPE_STANDARD|USB_RECIP_INTERFACE)&&lIIlIl.bRequest==
USB_REQ_SET_INTERFACE){
IlIlI=lIlIIIllI(lIlll,lIIIl,&lIIlIl,IIIIl);}else if(lIIlIl.bRequestType==(
USB_DIR_OUT|USB_TYPE_STANDARD|USB_RECIP_ENDPOINT)&&lIIlIl.bRequest==
USB_REQ_CLEAR_FEATURE&&lIIlIl.wValue==USB_ENDPOINT_HALT){
IlIlI=lllIIIlII(lIlll,lIIIl,&lIIlIl,IIIIl);}else{
IlIlI=llIllIIIl(lIlll,lIIIl,&lIIlIl,IIIIl);}break;default:IIIIll(
"\x75\x6e\x6b\x6e\x6f\x77\x6e\x20\x70\x69\x70\x65\x20\x74\x79\x70\x65\x20\x25\x64\x20\x69\x6e\x20\x75\x72\x62" "\n"
,usb_pipetype(lIlll->pipe));IlIlI=-EINVAL;break;}}while((0x616+2349-0xf43));if(
IlIlI<(0x130a+1617-0x195b)){IIIIll(
"\x62\x72\x6f\x6b\x65\x6e\x20\x75\x72\x62\x20\x64\x65\x74\x65\x63\x74\x65\x64\x2c\x20\x65\x72\x72\x6f\x72\x20\x63\x6f\x64\x65\x20\x25\x64" "\n"
,IlIlI);}return IlIlI;}



static inline int IlIIlIIII(lIIll IIlIl,struct urb*lIlll,int lIlIlIll){int IlIlI
=(0x350+2595-0xd73);lIlll->actual_length=min((lllIl)lIlll->
transfer_buffer_length,IIlIl->IllIII.IlIll);if(lIlIlIll){IlIIlIll(lIlll,(char*)
IIlIl+sizeof(IIlIl->IllIII),lIlll->actual_length);}return IlIlI;}static inline 
int llIllIlII(lIIll IIlIl,struct list_head*IIIIIIl){int IlIlI=
(0xec1+4305-0x1f92);struct llIIIIl*lIlIII;unsigned long IlllIIlll;unsigned char*
IIIIl;IlllIIlll=IIlIl->lIllIl.IlIll;IIIIl=(unsigned char*)IIlIl+sizeof(IIlIl->
lIllIl);


list_for_each_entry(lIlIII,IIIIIIl,llllII){lIlIII->lIlll->actual_length=min((
unsigned long)lIlIII->lIlll->transfer_buffer_length,IlllIIlll);if(usb_pipein(
lIlIII->lIlll->pipe)){IlllI(
"\x75\x73\x62\x64\x5f\x75\x6e\x70\x61\x63\x6b\x5f\x75\x72\x62\x5f\x62\x75\x6c\x6b\x3a\x20\x63\x6f\x70\x79\x20\x25\x64\x20\x62\x79\x74\x65\x73\x20\x74\x6f\x20\x75\x72\x62\x20\x25\x70" "\n"
,lIlIII->lIlll->actual_length,lIlIII->lIlll);IlIIlIll(lIlIII->lIlll,IIIIl,lIlIII
->lIlll->actual_length);}IlllIIlll-=lIlIII->lIlll->actual_length;IIIIl+=lIlIII->
lIlll->actual_length;}return IlIlI;}static inline int lIIIlllII(lIIll IIlIl,
struct urb*lIlll){int i;int IlIlI=(0x1b1+4824-0x1489);IIIII*llIIllllI=(IIIII*)
IIlIl+lllIIIlI(IIlIl);if(IIlIl->llIIl.lIllIlI!=lIlll->number_of_packets)return-
EINVAL;lIlll->start_frame=IIlIl->llIIl.lllIIlll;lIlll->error_count=IIlIl->llIIl.
llllIlll;lIlll->actual_length=(0x1073+4691-0x22c6);for(i=(0xbb7+3889-0x1ae8);i<
lIlll->number_of_packets;i++){lIlll->iso_frame_desc[i].status=lIIIllIl(IIlIl->
llIIl.IIlIIll[i].Status);lIlll->iso_frame_desc[i].actual_length=IIlIl->llIIl.
IIlIIll[i].Length;lIlll->actual_length+=lIlll->iso_frame_desc[i].actual_length;}
if(usb_pipein(lIlll->pipe))lIllIlllI(lIlll,llIIllllI);return IlIlI;}static 
inline int IlllllIlI(lIIll IIlIl,struct urb*lIlll){int IlIlI=
(0x1120+1905-0x1891);lIlll->actual_length=min((lllIl)lIlll->
transfer_buffer_length,IIlIl->IIIllI.IlIll);if(usb_pipein(lIlll->pipe)){IlIIlIll
(lIlll,(char*)IIlIl+sizeof(IIlIl->IIIllI),lIlll->actual_length);}return IlIlI;}
static inline int IlIllIlIl(lIIll IIlIl,struct urb*lIlll){int IlIlI=
(0x237+7121-0x1e08);lIlll->actual_length=min((lllIl)lIlll->
transfer_buffer_length,IIlIl->IIIIII.IlIll);if(usb_pipein(lIlll->pipe)){IlIIlIll
(lIlll,(char*)IIlIl+sizeof(IIlIl->IIIIII),lIlll->actual_length);}return IlIlI;}
int IlIlIIIII(lIIll IIlIl,struct list_head*IIIIIIl,int*status){int IlIlI=
(0x753+6297-0x1fec);struct llIIIIl*lIlIII=list_entry(IIIIIIl->next,struct 
llIIIIl,llllII);struct urb*lIlll=lIlIII->lIlll;*status=lIIIllIl(IIlIl->IIIlI.
Status);switch(IIlIl->IIIlI.IIlIlI){case lllllIIl:IlllI(
"\x75\x73\x62\x64\x5f\x75\x6e\x70\x61\x63\x6b\x5f\x75\x72\x62\x3a\x20\x47\x65\x74\x44\x65\x73\x63\x72\x69\x70\x74\x6f\x72" "\n"
);IlIlI=IlIIlIIII(IIlIl,lIlll,(0xd80+2115-0x15c2));break;case lIIlllll:IlllI(
"\x75\x73\x62\x64\x5f\x75\x6e\x70\x61\x63\x6b\x5f\x75\x72\x62\x3a\x20\x53\x65\x74\x44\x65\x73\x63\x72\x69\x70\x74\x6f\x72" "\n"
);IlIlI=IlIIlIIII(IIlIl,lIlll,(0x10d0+4581-0x22b5));break;case IIllllII:IlllI(
"\x75\x73\x62\x64\x5f\x75\x6e\x70\x61\x63\x6b\x5f\x75\x72\x62\x3a\x20\x53\x65\x6c\x65\x63\x74\x43\x6f\x6e\x66\x69\x67\x75\x72\x61\x74\x69\x6f\x6e" "\n"
);IlIlI=(0xf39+2831-0x1a48);break;case lIIlIIII:IlllI(
"\x75\x73\x62\x64\x5f\x75\x6e\x70\x61\x63\x6b\x5f\x75\x72\x62\x3a\x20\x53\x65\x6c\x65\x63\x74\x49\x6e\x74\x65\x72\x66\x61\x63\x65" "\n"
);IlIlI=(0x3a9+1665-0xa2a);break;case llIlIIlI:IlllI(
"\x75\x73\x62\x64\x5f\x75\x6e\x70\x61\x63\x6b\x5f\x75\x72\x62\x3a\x20\x43\x6f\x6e\x74\x72\x6f\x6c\x54\x72\x61\x6e\x73\x66\x65\x72" "\n"
);IlIlI=IlllllIlI(IIlIl,lIlll);break;case lllIlIlI:IlllI(
"\x75\x73\x62\x64\x5f\x75\x6e\x70\x61\x63\x6b\x5f\x75\x72\x62\x3a\x20\x42\x75\x6c\x6b\x54\x72\x61\x6e\x73\x66\x65\x72" "\n"
);IlIlI=llIllIlII(IIlIl,IIIIIIl);break;case lIIlIIIl:IlllI(
"\x75\x73\x62\x64\x5f\x75\x6e\x70\x61\x63\x6b\x5f\x75\x72\x62\x3a\x20\x49\x73\x6f\x63\x68\x54\x72\x61\x6e\x73\x66\x65\x72" "\n"
);IlIlI=lIIIlllII(IIlIl,lIlll);break;case lIIlllII:IlllI(
"\x75\x73\x62\x64\x5f\x75\x6e\x70\x61\x63\x6b\x5f\x75\x72\x62\x3a\x20\x49\x6e\x74\x65\x72\x72\x75\x70\x74\x54\x72\x61\x6e\x73\x66\x65\x72" "\n"
);IlIlI=IlIllIlIl(IIlIl,lIlll);break;case lllIllll:IlllI(
"\x75\x73\x62\x64\x5f\x75\x6e\x70\x61\x63\x6b\x5f\x75\x72\x62\x3a\x20\x43\x6c\x65\x61\x72\x53\x74\x61\x6c\x6c" "\n"
);IlIlI=(0x9f3+6926-0x2501);break;case IllIIIll:IlllI(
"\x75\x73\x62\x64\x5f\x75\x6e\x70\x61\x63\x6b\x5f\x75\x72\x62\x3a\x20\x52\x65\x73\x65\x74\x50\x6f\x72\x74" "\n"
);IlIlI=(0x14b4+3378-0x21e6);break;default:IlllI(
"\x75\x73\x62\x64\x5f\x75\x6e\x70\x61\x63\x6b\x5f\x75\x72\x62\x3a\x20\x75\x6e\x6b\x6e\x6f\x77\x6e\x20\x66\x75\x6e\x63\x74\x69\x6f\x6e" "\n"
);IlIlI=-EINVAL;break;}return IlIlI;}void lllIlIIII(struct lIlIl*lllll,lllIl*
busnum,lllIl*devnum){if(busnum)*busnum=lllll->parent->self.busnum;
if(devnum)*devnum=lllll->llllIlI;}
























































void lIlIlII(struct IllIlI*Illll,int lIIlI,int IlIIII,int llIIllI){
switch(IlIIII){case llIIlIll:case IIIIIlIl:case lllIIlII:lIlllI(Illll,lIIlI,
IIlllIll);break;case lIIIIIll:lIlllI(Illll,lIIlI,IIlllIll);break;case lIllIlll:
Illll->IIllll[lIIlI]&=~USB_PORT_STAT_C_CONNECTION;break;case lIlIIllll:Illll->
IIllll[lIIlI]&=~USB_PORT_STAT_C_ENABLE;break;case IlIIllIll:Illll->IIllll[lIIlI]
&=~USB_PORT_STAT_C_SUSPEND;break;case IlIlllIl:Illll->IIllll[lIIlI]&=~
USB_PORT_STAT_C_RESET;break;}
switch(Illll->IllIllIl[lIIlI]){case IIlllIll:if(IlIIII==llIIllII)lIlllI(Illll,
lIIlI,IlllllI);break;case IlllllI:if(IlIIII==lIIIIIIl)lIlllI(Illll,lIIlI,IIIlIlI
);break;case IIIlIlI:if(IlIIII==IlIlIlI)lIlllI(Illll,lIIlI,IlllllI);if(IlIIII==
lIIlIll)lIlllI(Illll,lIIlI,IIIlIll);break;case IIIlIll:if(IlIIII==IlIlIlI)lIlllI
(Illll,lIIlI,IlllllI);if(IlIIII==IllIIlll)lIlllI(Illll,lIIlI,IIIlIlI);if(IlIIII
==IlIIIlII)lIlllI(Illll,lIIlI,IIlllll);break;case IIlllll:if(IlIIII==IlIlIlI)
lIlllI(Illll,lIIlI,IlllllI);if(IlIIII==IllIIlll)lIlllI(Illll,lIIlI,IIIlIlI);if(
IlIIII==lIIlIll)lIlllI(Illll,lIIlI,IIIlIll);if(IlIIII==Illllllll)lIlllI(Illll,
lIIlI,IIIIllIII);break;case IIIIllIII:if(IlIIII==IlIlIlI)lIlllI(Illll,lIIlI,
IlllllI);if(IlIIII==IllIIlll)lIlllI(Illll,lIIlI,IIIlIlI);if(IlIIII==lIIlIll)
lIlllI(Illll,lIIlI,IIIlIll);if(IlIIII==lIlIIIlII||IlIIII==lIIlIlIIl)lIlllI(Illll
,lIIlI,llIIIIll);break;case llIIIIll:if(IlIIII==IlIlIlI)lIlllI(Illll,lIIlI,
IlllllI);if(IlIIII==IllIIlll)lIlllI(Illll,lIIlI,IIIlIlI);if(IlIIII==lIIlIll)
lIlllI(Illll,lIIlI,IIIlIll);if(IlIIII==IlIIIlII)lIlllI(Illll,lIIlI,IIlllll);
break;}}static inline int llIlIlIll(int speed){switch(speed){case USB_SPEED_HIGH
:return USB_PORT_STAT_HIGH_SPEED;case USB_SPEED_LOW:return 
USB_PORT_STAT_LOW_SPEED;case USB_SPEED_FULL:return(0x109c+887-0x1413);}return
(0x2343+536-0x255b);}
void lIlllI(struct IllIlI*Illll,int lIIlI,int llIllIl){
int IlIlIIl=Illll->IllIllIl[lIIlI];if(llIllIl==IlIlIIl)return;Illll->IllIllIl[
lIIlI]=llIllIl;Illll->IlIlIII[lIIlI]=(0x445+5040-0x17f5);if(IlIlIIl==IIIlIll)
Illll->IIllll[lIIlI]|=USB_PORT_STAT_C_RESET;if(IlIlIIl==llIIIIll)Illll->IIllll[
lIIlI]|=USB_PORT_STAT_C_SUSPEND;switch(llIllIl){case IIlllIll:Illll->IIIIIll[
lIIlI]=(0x15+2650-0xa6f);Illll->IIllll[lIIlI]=(0x1fc+2243-0xabf);
break;case IlllllI:Illll->IIIIIll[lIIlI]=USB_PORT_STAT_POWER;if(IlIlIIl!=
IIlllIll)Illll->IIllll[lIIlI]|=USB_PORT_STAT_C_CONNECTION;
if(Illll->IIIIIII[lIIlI]){lIlllI(Illll,lIIlI,IIIlIlI);}break;case IIIlIlI:Illll
->IIIIIll[lIIlI]=USB_PORT_STAT_POWER|USB_PORT_STAT_CONNECTION;if(IlIlIIl==
IlllllI)Illll->IIllll[lIIlI]|=USB_PORT_STAT_C_CONNECTION;break;case IIIlIll:
Illll->IIIIIll[lIIlI]=USB_PORT_STAT_POWER|USB_PORT_STAT_CONNECTION|
USB_PORT_STAT_RESET;
Illll->IlIlIII[lIIlI]=jiffies+msecs_to_jiffies((0x7f9+51-0x7fa));
Illll->IlIlIII[lIIlI]+=Illll->IlIlIII[lIIlI]?(0x143c+1918-0x1bba):
(0x25d+8931-0x253f);break;case IIlllll:Illll->IIIIIll[lIIlI]=USB_PORT_STAT_POWER
|USB_PORT_STAT_CONNECTION|USB_PORT_STAT_ENABLE|llIlIlIll(Illll->IIIIIII[lIIlI]->
speed);break;case IIIIllIII:Illll->IIIIIll[lIIlI]=USB_PORT_STAT_POWER|
USB_PORT_STAT_CONNECTION|USB_PORT_STAT_ENABLE|USB_PORT_STAT_SUSPEND|llIlIlIll(
Illll->IIIIIII[lIIlI]->speed);break;case llIIIIll:Illll->IIIIIll[lIIlI]=
USB_PORT_STAT_POWER|USB_PORT_STAT_CONNECTION|USB_PORT_STAT_ENABLE|
USB_PORT_STAT_SUSPEND|llIlIlIll(Illll->IIIIIII[lIIlI]->speed);
Illll->IlIlIII[lIIlI]=jiffies+msecs_to_jiffies((0x20+6674-0x1a1e));
Illll->IlIlIII[lIIlI]+=Illll->IlIlIII[lIIlI]?(0x75b+6473-0x20a4):
(0x21+1144-0x498);break;default:IIIIll(
"\x69\x6e\x76\x61\x6c\x69\x64\x20\x6e\x65\x77\x20\x70\x6f\x72\x74\x20\x73\x74\x61\x74\x65" "\n"
);break;}}
#if KERNEL_GT_EQ((0x292+8777-0x24d9),(0x2018+380-0x218e),(0x96d+569-0xb7f)) || \
RHEL_RELEASE_GT_EQ((0x2b3+7539-0x2020),(0x3c2+7787-0x222a)) 

























void lIIIlII(struct IllIlI*Illll,int lIIlI,int IlIIII,int llIIllI){
switch(IlIIII){case llIIlIll:case lllIIlII:IlIIlII(Illll,lIIlI,IIlllIll);return;
case lIllIlll:Illll->IIllll[lIIlI]&=~USB_PORT_STAT_C_CONNECTION;return;case 
IlIlllIl:Illll->IIllll[lIIlI]&=~USB_PORT_STAT_C_RESET;return;case IlIIIlIlI:
Illll->IIllll[lIIlI]&=~USB_PORT_STAT_C_BH_RESET;return;case IIlIIlIlI:Illll->
IIllll[lIIlI]&=~USB_PORT_STAT_C_LINK_STATE;return;case llIIlIII:if(llIIllI==
(0x1884+3164-0x24dc)){
IlIIlII(Illll,lIIlI,IIIlIlI);return;}break;}
switch(Illll->IllIllIl[lIIlI]){case IIlllIll:if(IlIIII==IIIIIlIl)IlIIlII(Illll,
lIIlI,IlllllI);break;case llllIIII:if(IlIIII==llIIllII)IlIIlII(Illll,lIIlI,
IlllllI);if(IlIIII==lIIlIll)IlIIlII(Illll,lIIlI,IIIlIll);break;case IlllllI:if(
IlIIII==lIIIIIll)IlIIlII(Illll,lIIlI,llllIIII);if(IlIIII==lIIIIIIl)IlIIlII(Illll
,lIIlI,IIlllll);break;case IIIlIlI:if(IlIIII==lIIIIIll)IlIIlII(Illll,lIIlI,
llllIIII);if(IlIIII==lIIlIll)IlIIlII(Illll,lIIlI,IIIlIll);if(IlIIII==llIIlIII&&
llIIllI==(0x5ac+1035-0x9b2)){


IlIIlII(Illll,lIIlI,IlllllI);}break;case IIlllll:if(IlIIII==lIIIIIll)IlIIlII(
Illll,lIIlI,llllIIII);if(IlIIII==IlIlIlI)IlIIlII(Illll,lIIlI,IlllllI);if(IlIIII
==lIIlIll)IlIIlII(Illll,lIIlI,IIIlIll);if(IlIIII==llIIlIII&&llIIllI==
(0x1fa2+866-0x2304)){
if(Illll->IIIlIIl[lIIlI]==USB_SS_PORT_LS_U3){

Illll->IIllll[lIIlI]|=USB_PORT_STAT_C_LINK_STATE;}IIlIlII(Illll,lIIlI,
USB_SS_PORT_LS_U0);}if(IlIIII==llIIlIII&&llIIllI==(0x11ad+1986-0x196e)){

if(Illll->IIIlIIl[lIIlI]==USB_SS_PORT_LS_U0){IIlIlII(Illll,lIIlI,
USB_SS_PORT_LS_U1);}}if(IlIIII==llIIlIII&&llIIllI==(0x8d+8617-0x2234)){

if(Illll->IIIlIIl[lIIlI]==USB_SS_PORT_LS_U0){IIlIlII(Illll,lIIlI,
USB_SS_PORT_LS_U2);}}if(IlIIII==llIIlIII&&llIIllI==(0x1212+1551-0x181e)){

if(Illll->IIIlIIl[lIIlI]==USB_SS_PORT_LS_U0||Illll->IIIlIIl[lIIlI]==
USB_SS_PORT_LS_U1||Illll->IIIlIIl[lIIlI]==USB_SS_PORT_LS_U2){

if(Illll->IIIlIIl[lIIlI]!=USB_SS_PORT_LS_U0){IIlIlII(Illll,lIIlI,
USB_SS_PORT_LS_U0);}IIlIlII(Illll,lIIlI,USB_SS_PORT_LS_U3);}}break;case IIIlIll:
if(IlIIII==lIIIIIll)IlIIlII(Illll,lIIlI,llllIIII);if(IlIIII==IlIlIlI)IlIIlII(
Illll,lIIlI,IlllllI);if(IlIIII==IlIIIlII)IlIIlII(Illll,lIIlI,IIlllll);break;}}
static inline int lllIlIIll(int speed){switch(speed){case USB_SPEED_SUPER:return
 USB_PORT_STAT_SPEED_5GBPS;default:return(0x4d2+4896-0x17f2);}return
(0x4b4+4819-0x1787);}
void IlIIlII(struct IllIlI*Illll,int lIIlI,int llIllIl){int IIlIIlII=Illll->
IIIIIll[lIIlI];int IlIlIIl=Illll->IllIllIl[lIIlI];if(llIllIl==IlIlIIl)return;
Illll->IllIllIl[lIIlI]=llIllIl;Illll->IlIlIII[lIIlI]=(0x17b7+2080-0x1fd7);switch
(llIllIl){case IIlllIll:IIlIlII(Illll,lIIlI,USB_SS_PORT_LS_SS_DISABLED);Illll->
IIIIIll[lIIlI]=Illll->IIIlIIl[lIIlI];Illll->IIllll[lIIlI]=(0xc4c+2449-0x15dd);
break;case llllIIII:IIlIlII(Illll,lIIlI,USB_SS_PORT_LS_RX_DETECT);Illll->IIIIIll
[lIIlI]=Illll->IIIlIIl[lIIlI];Illll->IIllll[lIIlI]=(0x112f+3094-0x1d45);
break;case IIIlIlI:IIlIlII(Illll,lIIlI,USB_SS_PORT_LS_SS_DISABLED);Illll->
IIIIIll[lIIlI]=Illll->IIIlIIl[lIIlI]|USB_SS_PORT_STAT_POWER;if(IIlIIlII&
USB_PORT_STAT_CONNECTION)Illll->IIllll[lIIlI]|=USB_PORT_STAT_C_CONNECTION;
break;case IlllllI:IIlIlII(Illll,lIIlI,USB_SS_PORT_LS_RX_DETECT);Illll->IIIIIll[
lIIlI]=Illll->IIIlIIl[lIIlI]|USB_SS_PORT_STAT_POWER;if(IIlIIlII&
USB_PORT_STAT_CONNECTION)Illll->IIllll[lIIlI]|=USB_PORT_STAT_C_CONNECTION;

if(Illll->IIIIIII[lIIlI]){IlIIlII(Illll,lIIlI,IIlllll);}break;case IIlllll:
IIlIlII(Illll,lIIlI,USB_SS_PORT_LS_U0);Illll->IIIIIll[lIIlI]=Illll->IIIlIIl[
lIIlI]|USB_SS_PORT_STAT_POWER|USB_PORT_STAT_CONNECTION|USB_PORT_STAT_ENABLE|
lllIlIIll(Illll->IIIIIII[lIIlI]->speed);if(IlIlIIl==IIIlIll)Illll->IIllll[lIIlI]
|=USB_PORT_STAT_C_RESET;
if(IlIlIIl==IlllllI)Illll->IIllll[lIIlI]|=USB_PORT_STAT_C_CONNECTION;
break;case IIIlIll:Illll->IIIIIll[lIIlI]=Illll->IIIlIIl[lIIlI]|
USB_SS_PORT_STAT_POWER|USB_PORT_STAT_RESET|(IIlIIlII&USB_PORT_STAT_CONNECTION);

Illll->IlIlIII[lIIlI]=jiffies+msecs_to_jiffies((0x1de9+2308-0x26bb));
Illll->IlIlIII[lIIlI]+=Illll->IlIlIII[lIIlI]?(0xbda+4941-0x1f27):
(0x130d+1912-0x1a84);break;default:IlllI(
"\x69\x6e\x76\x61\x6c\x69\x64\x20\x70\x6f\x72\x74\x20\x73\x74\x61\x74\x65" "\n")
;break;}}
void IIlIlII(struct IllIlI*Illll,int lIIlI,int IlIIlIIIl){switch(IlIIlIIIl){case
 USB_SS_PORT_LS_U0:IlllI(
"\x73\x65\x74\x5f\x6c\x69\x6e\x6b\x5f\x73\x74\x61\x74\x65\x20\x55\x53\x42\x5f\x53\x53\x5f\x50\x4f\x52\x54\x5f\x4c\x53\x5f\x55\x30" "\n"
);
Illll->IIIlIIl[lIIlI]=USB_SS_PORT_LS_U0;break;case USB_SS_PORT_LS_U1:IlllI(
"\x73\x65\x74\x5f\x6c\x69\x6e\x6b\x5f\x73\x74\x61\x74\x65\x20\x55\x53\x42\x5f\x53\x53\x5f\x50\x4f\x52\x54\x5f\x4c\x53\x5f\x55\x31" "\n"
);
Illll->IIIlIIl[lIIlI]=USB_SS_PORT_LS_U1;break;case USB_SS_PORT_LS_U2:IlllI(
"\x73\x65\x74\x5f\x6c\x69\x6e\x6b\x5f\x73\x74\x61\x74\x65\x20\x55\x53\x42\x5f\x53\x53\x5f\x50\x4f\x52\x54\x5f\x4c\x53\x5f\x55\x32" "\n"
);
Illll->IIIlIIl[lIIlI]=USB_SS_PORT_LS_U2;break;case USB_SS_PORT_LS_U3:IlllI(
"\x73\x65\x74\x5f\x6c\x69\x6e\x6b\x5f\x73\x74\x61\x74\x65\x20\x55\x53\x42\x5f\x53\x53\x5f\x50\x4f\x52\x54\x5f\x4c\x53\x5f\x55\x33" "\n"
);
Illll->IIIlIIl[lIIlI]=USB_SS_PORT_LS_U3;break;case USB_SS_PORT_LS_SS_DISABLED:
IlllI(
"\x73\x65\x74\x5f\x6c\x69\x6e\x6b\x5f\x73\x74\x61\x74\x65\x20\x55\x53\x42\x5f\x53\x53\x5f\x50\x4f\x52\x54\x5f\x4c\x53\x5f\x53\x53\x5f\x44\x49\x53\x41\x42\x4c\x45\x44" "\n"
);
Illll->IIIlIIl[lIIlI]=USB_SS_PORT_LS_SS_DISABLED;break;case 
USB_SS_PORT_LS_RX_DETECT:IlllI(
"\x73\x65\x74\x5f\x6c\x69\x6e\x6b\x5f\x73\x74\x61\x74\x65\x20\x55\x53\x42\x5f\x53\x53\x5f\x50\x4f\x52\x54\x5f\x4c\x53\x5f\x52\x58\x5f\x44\x45\x54\x45\x43\x54" "\n"
);
Illll->IIIlIIl[lIIlI]=USB_SS_PORT_LS_RX_DETECT;break;}Illll->IIIIIll[lIIlI]&=~
USB_PORT_STAT_LINK_STATE;Illll->IIIIIll[lIIlI]|=Illll->IIIlIIl[lIIlI];}
#endif 
#endif 

