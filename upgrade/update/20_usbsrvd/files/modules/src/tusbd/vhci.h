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

#ifndef IlllIlIll
#define IlllIlIll
#ifdef _USBD_ENABLE_VHCI_
#include "vhci_hcd.h"


#if KERNEL_LT((0x1c9f+2225-0x254e),(0xa01+6306-0x229d),(0xb29+1326-0x1043))
#  define llIlll	(0x3c+9832-0x2695)
#else
#  if USB_MAXCHILDREN < (0xd96+5419-0x22b2)
#    define llIlll USB_MAXCHILDREN
#  else
#    define llIlll (0x17+8280-0x2060)
#  endif
#endif

#define IIllIlIl ((llIlll / (0x2b2+8568-0x2422)) + (0x1ab6+1411-0x2038))
struct lIlIl{struct list_head llllII;struct IllllI*lIllI;struct kref lllllIl;int
 lIIlI;int llllIlI;int speed;int lIIIlIII;u16 vid;u16 IllIIII;u16 IlIllIl;struct
 usb_hcd*parent;wait_queue_head_t lllIll;spinlock_t llllll;struct list_head 
lIlIIlI;struct list_head IllIIll;struct list_head IlIIIIll;void*llIIlll;
void*IIIIlIlIl;
void*IIIIIlllI;
};struct llIIIIl{struct list_head llllII;struct urb*lIlll;};

struct IlllIl{struct list_head IlIlIl;struct lIlIl*lllll;Illlll lIIIl;struct 
list_head lIIIIIl;struct llIIIIl urb;lIIll IIlIl;};struct IllIlI{spinlock_t lock
;struct lIlIl*IIIIIII[llIlll];int IllIllIl[llIlll];int IIIlIIl[llIlll];unsigned 
short IIIIIll[llIlll];unsigned short IIllll[llIlll];unsigned long IlIlIII[llIlll
];struct usb_hcd*IIlll;struct usb_hcd*IllIIllI;unsigned IIlIlllIl:
(0x1647+3599-0x2455);};enum IlIlIllIl{IIlllIll=(0x1f+2501-0x9e4),
llllIIII,
IlllllI,
IIIlIlI,
IIlllll,
IIIlIll,
IIIIllIII,
llIIIIll,
};enum IIIIllllI{llIIlIll,
IIIIIlIl,
lllIIlII,
llIIllII,
lIIIIIll,
lIIIIIIl,
IlIlIlI,
IllIIlll,
lIIlIll,
Illllllll,
lIlIIIlII,
lIIlIlIIl,
IlIIIlII,
llIIlIII,
lIllIlll,
lIlIIllll,
IlIIllIll,
IlIlllIl,
IlIIIlIlI,
IIlIIlIlI,
};int IlIlIIIlI(void);void IIlllIII(void);struct lIlIl*IlIlIIIIl(u16 vid,u16 
IllIIII,u16 IlIllIl,int speed);void IlllllII(struct lIlIl*lllll);void IllllIlII(
void);int lllIllIIl(struct lIlIl*lllll);void IIIIIIIll(struct lIlIl*lllll);
struct lIlIl*IIlllIlll(int IlllllllI);struct lIlIl*IlIIIIIlI(struct usb_hcd*
IIlll,int llllIlI);struct lIlIl*lIIIIIIll(struct usb_hcd*IIlll,int lIIlI);void 
IlIlIIII(struct lIlIl*lllll);struct IlllIl*IIlIIIlII(struct lIlIl*lllll,gfp_t 
llllI);void IlllIIII(struct IlllIl*IllII);int IlllIIlIl(struct IlllIl*IllII);
void IIllIlllI(struct lIlIl*lllll,int status);void lIllIIIl(struct IlllIl*IllII,
int status);int IllIIlIll(struct lIlIl*lllll,struct IlllIl*IlIllIIlI,lIIll IIlIl
);int IlIIIIlIl(struct lIlIl*lllll,struct IlllIl*IllII,lIIll IIlIl,int*status);
int IllIllllI(struct lIlIl*lllll,struct IlllIl**lIlllIII,struct urb*lIlll);int 
llIlllII(struct IlllIl*IllII);void lllIlIIII(struct lIlIl*lllll,lllIl*busnum,
lllIl*devnum);void llIIIllll(struct kref*llllIlII);static inline struct lIlIl*
lIllIIlI(struct lIlIl*lllll){kref_get(&lllll->lllllIl);return lllll;}static 
inline void lllllIll(struct lIlIl*lllll){kref_put(&lllll->lllllIl,llIIIllll);}
#endif 
#endif 

