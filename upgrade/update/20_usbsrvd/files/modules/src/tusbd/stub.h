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

#ifndef IllIllIll
#define IllIllIll
#ifdef _USBD_ENABLE_STUB_
struct IllIl{struct list_head llllII;struct IllllI*lIllI;struct kref lllllIl;u16
 vid;u16 IllIIII;u16 IlIllIl;char bus_id[BUS_ID_SIZE];struct usb_device*llIII;
char*llIIlIlI;int llIlllI;int IIIllIIl;int IIIlIIII;int lIIIllII;int lIIIIll;int
 IIIlllIl;int IIlllIlI;
int IIllIIIl[(0x8ec+4810-0x1ba6)];int lIlllIIl[(0xd2c+3559-0x1b03)];int IIllIIlI
[(0x12c6+2701-0x1d43)];int llllIIll[(0x15c6+739-0x1899)];wait_queue_head_t 
lllIll;spinlock_t IlIIIl;struct list_head lIlIIlI;spinlock_t lIIllll;struct 
list_head IIlIllll;struct list_head lIlIIlII;
int IIlIllI;int IIIIIlll;int IllIllII;
int lllIIlI;int IIlIIlll;struct IlIII*llIIIII;int llllIllI;int lIlllIlI;struct 
IllIIlIl IlllIlI[(0xa6f+1239-0xf43)];};int IlIIIIlll(void);void IIIIlIIlI(void);
struct IllIl*lIllIIIll(struct usb_device*IlIIl);void IlIIllII(struct IllIl*lIlII
);int llIllIII(struct usb_device*IlIIl);int lIIIlllI(struct usb_device*IlIIl);
int IlIllIIl(struct usb_device*IlIIl);int IIIllllIl(struct usb_interface*IIllI,
int lllIIlIIl);void lIlIIlIll(struct usb_interface*IIllI);struct IllIl*llIlIllI(
struct usb_device*IlIIl);void lllllIlII(struct IllIl*lIlII);void lIIlllllI(
struct IllIl*lIlII);int IIlllIllI(struct IllIl*lIlII);void llllIIlIl(struct 
IllIl*lIlII);void lIlIIIlll(struct IllIl*lIlII,int lIllllI);void IlIIIIlII(
struct IllIl*lIlII,int lIllllI);int IIIIIIII(struct IllIl*lIlII,int pipe);int 
IIlIlIIl(struct IllIl*lIlII,int pipe);void llllIlIII(struct IllIl*lIlII,int pipe
);int lIIllIII(struct IllIl*lIlII,int pipe);void lIlIlIII(struct IllIl*lIlII,int
 pipe,int IlIIIll);int IIIlIlII(struct usb_device*llIII,IIIII endpoint);void 
IIIIIllll(struct IllIl*lIlII,struct usb_interface*lIllII,struct IlIII*lIlIlll,
int lllIIII);void lIlIllIlI(struct IllIl*lIlII,int endpoint,struct IlIII*lIlIlll
);void IlIlIlII(struct IllIl*lIlII,struct IlIII*lIlIlll,int IIIllIIlI,int 
lllIIII);void IIlllIIIl(struct IllIl*lIlII,Illlll lIIIl,struct IlIII*lIlIlll);
void IlIlIlIIl(struct kref*llllIlII);static inline struct IllIl*IlllIIlI(struct 
IllIl*lIlII){kref_get(&lIlII->lllllIl);return lIlII;}static inline void lIlIIlIl
(struct IllIl*lIlII){kref_put(&lIlII->lllllIl,IlIlIlIIl);}


#pragma pack(push,1)


struct lllllllIl{lllIl IIlIlIllI;lllIl lIllllIll;lllIl IIIIlllIl;IIIII lIIllllIl
;IIIII lIIlllIll;IIIII IIlllIlII;IIIII IlIIlIlIl[(0xd60+6335-0x260f)];};

struct IIllIIlIl{lllIl IllIlIIll;lllIl lIIlIllII;lllIl lIlllIIII;IIIII lIIlIIlll
;};
#pragma pack(pop)
int lllIlllI(struct IllIl*lIlII);int IIIlIllll(struct IlIII*IIIll,gfp_t llllI);
#endif 
#endif 

