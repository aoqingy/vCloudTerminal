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

#ifndef IIIIIlIIl
#define IIIIIlIIl
#include "urb_chain.h"
#include "sg.h"

#define lIlIIIIl		(0x12e0+3155-0x1f33)
#define llllIll		(0x5ed+7048-0x2174)
#define IIIIlIl		(0x654+3287-0x1329)
#define llIlIllII	(0x1399+1677-0x1a23)
#define IIllIIl		(0xe37+5527-0x23ca)

#define llIIlIl		(0x682+5751-0x1cf9) 
#define lIlllll	(0xee7+4556-0x20b2) 
#if KERNEL_GT_EQ((0x110c+5359-0x25f9),(0x698+875-0x9fd),(0x81d+3052-0x13ea))
#define lIlIllI			(0x23+2744-0xad9) 
#endif
struct IlIII{size_t lllllI;struct kref lllllIl;atomic_t state;Illlll lIIIl;int 
lIllll;
lIlIllllI lIlIll;IIIII endpoint;
struct list_head IlIlIl;struct IllIl*lIlII;union{struct{struct urb*lIlll;
void*IIIIl;
}IlIlII;struct{struct lllIlI IlIIIII;
struct lIIlIlI lIllIIl;
}IIllIl;
#if KERNEL_GT_EQ((0x8+2026-0x7f0),(0x121+3345-0xe2c),(0x101d+3489-0x1d9f))
struct{struct urb*lIlll;
struct IlIIlll sg;}lIllIll;
#endif
};char lIlllIl:(0xe70+5686-0x24a5);
char lllIIII:(0x4ad+6988-0x1ff8);



};struct lIIIlIlI{struct list_head llllII;
Illlll lIIIl;int IlIllIIll;int llIIlIIII;};
#ifdef _USBD_DEBUG_MEMORY_
extern atomic_t lIIIlllll;extern atomic_t IlIIIIIII;extern atomic_t IllIlllI;
extern atomic_t IlIIllll;
#ifdef ATOMIC64_INIT
extern atomic64_t lIIIlIIl;
#endif
static inline struct urb*lIIIIlI(int lllIIlllI,gfp_t llllI){atomic_inc(&
lIIIlllll);return usb_alloc_urb(lllIIlllI,llllI);}static inline void IlIIllIl(
struct urb*urb){atomic_inc(&IlIIIIIII);usb_free_urb(urb);}static inline void*
IllllIl(size_t lllllI,int flags){atomic_inc(&IllIlllI);
#ifdef ATOMIC64_INIT
atomic64_add(lllllI,&lIIIlIIl);
#endif
return kmalloc(lllllI,flags);}static inline void*IlIIllI(size_t lllllI,int flags
){atomic_inc(&IllIlllI);
#ifdef ATOMIC64_INIT
atomic64_add(lllllI,&lIIIlIIl);
#endif
return kzalloc(lllllI,flags);}static inline void lllIII(const void*IlIlIIlIl){
atomic_inc(&IlIIllll);return kfree(IlIlIIlIl);}
#else 
#define	lIIIIlI	usb_alloc_urb
#define	IlIIllIl	usb_free_urb
#define	IllllIl		kmalloc
#define	IlIIllI		kzalloc
#define	lllIII			kfree
#endif 
#ifdef _USBD_ENABLE_STUB_
struct IlIII*IlIlIllll(struct IllIl*lIlII,const void __user*llIlI,size_t IIlII);
size_t IIlIlllll(struct IlIII*IIIll,void __user*llIlI,size_t IIlII);struct IlIII
*lIIIIIIII(struct IlIII*IIIll,gfp_t llllI);void lllIllI(struct IlIII*IIIll);void
 lllllIlI(struct kref*llllIlII);
#endif
void lllIIIllI(struct usb_device*IlIIl,u8*lIlIlIl,u8*llIllll,u8*IllIlII);const 
char*IIllIlll(unsigned long lIllIII);const char*lllIlIII(unsigned long lIllIII);
void IlIlIIll(struct urb*lIlll,Illlll lIIIl);void IlIIIIl(lIIll IIlIl);
#ifdef _USBD_ENABLE_VHCI_
int IIlIIIIlI(struct list_head*IIIIIIl,Illlll lIIIl,void*IIIIl);int IlIlIIIII(
lIIll IIlIl,struct list_head*IIIIIIl,int*status);
#endif
int lIIIllIl(lllIl status);int IlIlIIlll(void*IIllllll,struct vm_area_struct*
IlIllll);Illlll lIlllllIl(void);size_t IIIllIll(struct usb_iso_packet_descriptor
*llIlIII,int IIlII,void*lIIlIII,void*lllIIl,int llIIIIlI);size_t IllIllll(struct
 usb_iso_packet_descriptor*llIlIII,int IIlII,int llIIIIlI);void llIlllll(
dma_addr_t lIIlIII,void*lllIIl,unsigned long IIlIIl);void IllIlIIl(void*lIIlIII,
dma_addr_t lllIIl,unsigned long IIlIIl);char*IlIIlIlI(struct kobject*kobj,gfp_t 
llIIllIll);void llIIlIIIl(char*IIIlllI);int lIIllIIlI(struct device*dev);int 
IlIlIIlII(struct device*dev);int lIIIIIIlI(struct device*dev);
#if KERNEL_GT_EQ((0xe7f+4176-0x1ecd),(0x111a+1162-0x159e),(0x1361+1094-0x1791))
void llIlIIll(struct device*dev,int lIllIIll);int IlIIIlllI(struct device*dev);
#endif
#if KERNEL_GT_EQ((0x16f5+2946-0x2275),(0x7e2+1001-0xbc5),(0x93d+992-0xcff))
#define IlIIlI(llIIIlIl) dev_name((llIIIlIl))
#else
#define IlIIlI(llIIIlIl) (llIIIlIl)->bus_id
#endif
#if KERNEL_LT_EQ((0x2fd+7432-0x2003),(0x1597+851-0x18e4),(0x1493+4309-0x2559))
#include <asm/semaphore.h>
struct mutex{struct semaphore lllIlIll;};static inline void mutex_init(struct 
mutex*mutex){sema_init(&mutex->lllIlIll,(0x28a+2387-0xbdc));}static inline void 
mutex_lock(struct mutex*mutex){down(&mutex->lllIlIll);}static inline void 
mutex_unlock(struct mutex*mutex){up(&mutex->lllIlIll);}
#endif
#endif 

