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
#include <linux/mm.h>
ssize_t IIlIIIIIl(void*,const char __user*,size_t);ssize_t IIlllIIll(void*,char 
__user*,size_t);long llIIIIllI(void*,unsigned int,unsigned long);
#ifdef CONFIG_COMPAT
long IIlllllII(void*,unsigned int,unsigned long);
#endif
int llIIllIII(void*,int);int IlIlIlIlI(void*,int);void llIIlIllI(void*);void 
IIlIllllI(void*);unsigned int lIIlIIllI(void*,struct file*,poll_table*lllIll);
int lllllIIlI(void*,struct vm_area_struct*);static struct IllIIlIl llIlIIlll[]={
{"\x74\x79\x70\x65","\x76\x73\x74\x75\x62"},{NULL,NULL},};int llIllIllI(struct 
lIlIl*lllll){struct IllllI*lIllI;lIllI=IlIIllI(sizeof(*lIllI),GFP_KERNEL);if(
lIllI){mutex_init(&lIllI->mutex);lIllI->context=lllll;lIllI->lIIIll=-
(0x142f+723-0x1701);lIllI->ops.open=llIIllIII;lIllI->ops.release=IlIlIlIlI;lIllI
->ops.unlocked_ioctl=llIIIIllI;
#ifdef CONFIG_COMPAT
lIllI->ops.compat_ioctl=IIlllllII;
#endif
lIllI->ops.read=IIlllIIll;lIllI->ops.write=IIlIIIIIl;lIllI->ops.poll=lIIlIIllI;
lIllI->ops.mmap=lllllIIlI;lIllI->ops.IIlIlIll=llIIlIllI;lIllI->ops.IIIIlIll=
IIlIllllI;lIllI->IlllIlI=llIlIIlll;lllll->lIllI=lIllI;return(0x936+5869-0x2023);
}return-ENOMEM;}void IIlIIIll(struct lIlIl*lllll){if(lllll->lIllI){lIIlIlIl(
lllll);lllIII(lllll->lIllI);lllll->lIllI=NULL;}}int IllIlIlII(struct lIlIl*lllll
){return lllIIIIl(lllll->lIllI,(0x1f2+5239-0x1667),-(0x5c0+4997-0x1944));}void 
lIIlIlIl(struct lIlIl*lllll){llIlIIIl(lllll->lIllI);}ssize_t IIlllIIll(void*
context,char __user*llIlI,size_t IIlII){IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x6d\x69\x6e\x6f\x72\x5f\x72\x65\x61\x64\x3a" "\n"
);return(0x66f+7127-0x2246);}ssize_t IIlIIIIIl(void*context,const char __user*
llIlI,size_t IIlII){IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x6d\x69\x6e\x6f\x72\x5f\x77\x72\x69\x74\x65" "\n"
);return(0xae1+2079-0x1300);}int llIIlllIl(struct lIlIl*lllll,void __user*llIlI)
{unsigned long offset=(unsigned long)llIlI;int IlIlI;lIIll IIlIl;unsigned long 
flags;struct IlllIl*IllII;IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x69\x6f\x63\x74\x6c\x5f\x72\x65\x61\x64\x5f\x75\x6e\x72\x62\x3a\x20\x2b\x2b" "\n"
);if(offset>=lIIllIIl){IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x69\x6f\x63\x74\x6c\x5f\x72\x65\x61\x64\x5f\x75\x6e\x72\x62\x3a\x20\x2d\x2d\x20\x69\x6e\x76\x61\x6c\x69\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74" "\n"
);return-EINVAL;}if(lllll->lIIIlIII){IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x69\x6f\x63\x74\x6c\x5f\x72\x65\x61\x64\x5f\x75\x6e\x72\x62\x3a\x20\x2d\x2d\x20\x72\x65\x73\x65\x74\x20\x69\x6e\x20\x70\x72\x6f\x67\x72\x65\x73\x73" "\n"
);return-ENODATA;}IIlIl=(lIIll)((char*)lllll->IIIIlIlIl+offset);IllII=NULL;
spin_lock_irqsave(&lllll->llllll,flags);if(!list_empty(&lllll->IllIIll)){IllII=
list_entry(lllll->IllIIll.next,struct IlllIl,IlIlIl);list_del_init(&IllII->
IlIlIl);}spin_unlock_irqrestore(&lllll->llllll,flags);IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x69\x6f\x63\x74\x6c\x5f\x72\x65\x61\x64\x5f\x75\x6e\x72\x62\x3a\x20\x70\x76\x72\x65\x71\x20\x3d\x20\x30\x78\x25\x70" "\n"
,IllII);if(IllII){IlIlI=IllIIlIll(lllll,IllII,IIlIl);if(IlIlI>=
(0x12a7+4850-0x2599)){spin_lock_irqsave(&lllll->llllll,flags);if(llIlllII(IllII)
){
spin_unlock_irqrestore(&lllll->llllll,flags);IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x69\x6f\x63\x74\x6c\x5f\x72\x65\x61\x64\x5f\x75\x6e\x72\x62\x3a\x20\x72\x65\x71\x75\x65\x73\x74\x20\x68\x61\x73\x20\x62\x65\x65\x6e\x20\x63\x61\x6e\x63\x65\x6c\x6c\x65\x64\x21" "\n"
);lIllIIIl(IllII,-ECONNRESET);IlllIIII(IllII);IlIlI=-ENODATA;}else{
list_add_tail(&IllII->IlIlIl,&lllll->IlIIIIll);spin_unlock_irqrestore(&lllll->
llllll,flags);IlIIIIl(IIlIl);}}else{IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x69\x6f\x63\x74\x6c\x5f\x72\x65\x61\x64\x5f\x75\x6e\x72\x62\x3a\x20\x63\x61\x6e\x20\x6e\x6f\x74\x20\x70\x61\x63\x6b\x20\x72\x65\x71\x75\x65\x73\x74\x2c\x20\x72\x65\x73\x75\x6c\x74\x3d\x25\x64" "\n"
,IlIlI);lIllIIIl(IllII,IlIlI);IlllIIII(IllII);IlIlI=-ENODATA;}}else{IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x69\x6f\x63\x74\x6c\x5f\x72\x65\x61\x64\x5f\x75\x6e\x72\x62\x3a\x20\x6e\x6f\x20\x65\x6e\x74\x72\x79" "\n"
);IlIlI=-ENODATA;}IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x69\x6f\x63\x74\x6c\x5f\x72\x65\x61\x64\x5f\x75\x6e\x72\x62\x3a\x20\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x3d\x25\x64" "\n"
,IlIlI);return IlIlI;}int IIIIIlIll(struct lIlIl*lllll,void __user*llIlI){
unsigned long offset=(unsigned long)llIlI;int IlIlI;lIIll IIlIl;unsigned long 
flags;struct IlllIl*IllII;struct IlllIl*IIlIIlI;IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x69\x6f\x63\x74\x6c\x5f\x77\x72\x69\x74\x65\x5f\x75\x6e\x72\x62\x3a\x20\x2b\x2b" "\n"
);if(offset>=lIIllIIl){IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x69\x6f\x63\x74\x6c\x5f\x72\x65\x61\x64\x5f\x75\x6e\x72\x62\x3a\x20\x2d\x2d\x20\x69\x6e\x76\x61\x6c\x69\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74" "\n"
);return-EINVAL;}IIlIl=(lIIll)((char*)lllll->IIIIIlllI+offset);IlIIIIl(IIlIl);
IllII=NULL;spin_lock_irqsave(&lllll->llllll,flags);list_for_each_entry(IIlIIlI,&
lllll->IlIIIIll,IlIlIl){if(IIlIIlI->lIIIl==IIlIl->IIIlI.lIlIlI){
list_del_init(&IIlIIlI->IlIlIl);
IllII=IIlIIlI;break;}}spin_unlock_irqrestore(&lllll->llllll,flags);if(IllII){int
 status;IlIlI=IlIIIIlIl(lllll,IllII,IIlIl,&status);if(IlIlI<(0x1319+248-0x1411))
{
spin_lock_irqsave(&lllll->llllll,flags);if(llIlllII(IllII)){
spin_unlock_irqrestore(&lllll->llllll,flags);lIllIIIl(IllII,-ECONNRESET);
IlllIIII(IllII);}else{



list_add_tail(&IllII->IlIlIl,&lllll->IlIIIIll);spin_unlock_irqrestore(&lllll->
llllll,flags);}}else{lIllIIIl(IllII,status);IlllIIII(IllII);}}else{IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x69\x6f\x63\x74\x6c\x5f\x77\x72\x69\x74\x65\x5f\x75\x6e\x72\x62\x3a\x20\x72\x65\x71\x75\x65\x73\x74\x20\x6e\x6f\x74\x20\x66\x6f\x75\x6e\x64" "\n"
);IlIlI=(0x1459+572-0x1695);}IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x69\x6f\x63\x74\x6c\x5f\x77\x72\x69\x74\x65\x5f\x75\x6e\x72\x62\x3a\x20\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x3d\x25\x64" "\n"
,IlIlI);return IlIlI;}int IllIIIIlI(struct lIlIl*lllll,struct lllIllIll __user*
ioctl){lllIl lllllI;lllIl devnum;lllIl busnum;if(get_user(lllllI,&ioctl->IIIlIl.
lIIIIII)<(0x4fb+8451-0x25fe))return-EFAULT;if(lllllI!=sizeof(struct lllIllIll))
return-EINVAL;lllIlIIII(lllll,&busnum,&devnum);if(put_user(busnum,&ioctl->busnum
)<(0x13f+7704-0x1f57))return-EFAULT;if(put_user(devnum,&ioctl->devnum)<
(0x1be4+2365-0x2521))return-EFAULT;return(0x94+5222-0x14fa);}long lIIIIlIll(void
*context,unsigned int llIIII,void __user*llIIlI){struct lIlIl*lllll=context;int 
IlIlI=(0xee8+785-0x11f9);IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x6d\x69\x6e\x6f\x72\x5f\x69\x6f\x63\x74\x6c\x3a\x20\x2b\x2b\x20\x63\x6d\x64\x3d\x25\x64\x20\x61\x72\x67\x3d\x30\x78\x25\x70" "\n"
,llIIII,llIIlI);switch(llIIII){case llIlIIIlI:IlIlI=llIIlllIl(lllll,llIIlI);
break;case IIIIlllII:IlIlI=IIIIIlIll(lllll,llIIlI);break;case IIlIlIIlI:IlIlI=
IllIIIIlI(lllll,llIIlI);break;default:IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x6d\x69\x6e\x6f\x72\x5f\x69\x6f\x63\x74\x6c\x3a\x20\x75\x6e\x6b\x6e\x6f\x77\x6e\x20\x69\x6f\x63\x74\x6c" "\n"
);IlIlI=-EINVAL;break;}IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x6d\x69\x6e\x6f\x72\x5f\x69\x6f\x63\x74\x6c\x3a\x20\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x3d\x25\x64" "\n"
,IlIlI);return IlIlI;}long llIIIIllI(void*context,unsigned int llIIII,unsigned 
long llIIlI){return lIIIIlIll(context,llIIII,(void __user*)llIIlI);}
#ifdef CONFIG_COMPAT
long IIlllllII(void*context,unsigned int llIIII,unsigned long llIIlI){return 
lIIIIlIll(context,llIIII,compat_ptr(llIIlI));}
#endif
int lllllIIlI(void*context,struct vm_area_struct*IlIllll){int IlIlI;struct lIlIl
*lllll=context;unsigned long IIlIIl;IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x6d\x69\x6e\x6f\x72\x5f\x6d\x6d\x61\x70\x3a\x20\x2b\x2b" "\n"
);IIlIIl=IlIllll->vm_end-IlIllll->vm_start;if((IIlIIl<lIIllIIl*
(0x10c+4222-0x1188))||(IIlIIl>lIIllIIl*(0xd47+1737-0x140d))){IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x6d\x69\x6e\x6f\x72\x5f\x6d\x6d\x61\x70\x3a\x20\x2d\x2d\x20\x69\x6e\x76\x61\x6c\x69\x64\x20\x6c\x65\x6e\x67\x74\x68" "\n"
);return-EINVAL;}
IlIlI=IlIlIIlll(lllll->llIIlll,IlIllll);IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x6d\x69\x6e\x6f\x72\x5f\x6d\x6d\x61\x70\x3a\x20\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x3d\x25\x64" "\n"
,IlIlI);return IlIlI;}

int llIIllIII(void*context,int IlIllI){int IlIlI=(0x19d2+1555-0x1fe5);struct 
lIlIl*lllll=context;unsigned char*llIIlll;IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x6d\x69\x6e\x6f\x72\x5f\x6f\x70\x65\x6e\x3a\x20\x2b\x2b\x20\x25\x64" "\n"
,IlIllI);if(IlIllI==(0x15a4+3731-0x2436)){
llIIlll=vmalloc(lIIllIIl*(0x163b+3056-0x2229));if(llIIlll==NULL){IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x6d\x69\x6e\x6f\x72\x5f\x6f\x70\x65\x6e\x3a\x20\x6e\x6f\x20\x6d\x65\x6d\x6f\x72\x79\x20\x66\x6f\x72\x20\x69\x6f\x62\x75\x66" "\n"
);IlIlI=-ENOMEM;}else{lllll->llIIlll=llIIlll;lllll->IIIIlIlIl=llIIlll+
(0x691+3487-0x1430);lllll->IIIIIlllI=llIIlll+lIIllIIl;}}IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x6d\x69\x6e\x6f\x72\x5f\x6f\x70\x65\x6e\x3a\x20\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x3d\x25\x64" "\n"
,IlIlI);return IlIlI;}

int IlIlIlIlI(void*context,int IlIllI){struct lIlIl*lllll=context;IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x6d\x69\x6e\x6f\x72\x5f\x72\x65\x6c\x65\x61\x73\x65\x20\x25\x64" "\n"
,IlIllI);if(IlIllI==(0x85c+1615-0xeab)){if(lllll->llIIlll){vfree(lllll->llIIlll)
;lllll->llIIlll=NULL;}

}return(0x1365+1011-0x1758);}void llIIlIllI(void*context){struct lIlIl*lllll=
context;lIllIIlI(lllll);}void IIlIllllI(void*context){struct lIlIl*lllll=context
;lllllIll(lllll);}unsigned int lIIlIIllI(void*context,struct file*lIIIlI,
poll_table*lllIll){int lIIIIllI;unsigned long flags;struct lIlIl*lllll=context;
poll_wait(lIIIlI,&lllll->lllIll,lllIll);spin_lock_irqsave(&lllll->llllll,flags);
lIIIIllI=list_empty(&lllll->IllIIll);spin_unlock_irqrestore(&lllll->llllll,flags
);if(!lIIIIllI&&!lllll->lIIIlIII){IlllI(
"\x75\x73\x62\x64\x5f\x76\x73\x74\x75\x62\x5f\x6d\x69\x6e\x6f\x72\x5f\x70\x6f\x6c\x6c\x3a\x20\x71\x75\x65\x75\x65\x20\x6e\x6f\x74\x20\x65\x6d\x70\x74\x79" "\n"
);return((POLLOUT|POLLWRNORM)|(POLLIN|POLLRDNORM));}return(POLLOUT|POLLWRNORM);}
#endif 

