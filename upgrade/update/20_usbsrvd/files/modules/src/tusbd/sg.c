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
#if KERNEL_GT_EQ((0xc17+2398-0x1573),(0x483+1630-0xadb),(0x1001+1245-0x14bf))
int llIlllIII(struct IlIIlll*IIlIll,size_t length,int lIlIllIl){int i;size_t 
lIIlIIll=IIIlIlll-(IIIlIlll%lIlIllIl);int num_sgs=(length+lIIlIIll-
(0x1105+1215-0x15c3))/lIIlIIll;struct scatterlist*sg;
#if KERNEL_LT_EQ((0x701+1993-0xec8),(0x6a+6410-0x196e),(0x103a+5362-0x250a)) 

int lIlIIIIIl=((PAGE_SIZE-sizeof(*IIlIll->lIIlllI))&~((0xfca+325-0x1107)-
(0x16b6+4071-0x269c)))/sizeof(*IIlIll->sg);
#else

int lIlIIIIIl=PAGE_SIZE/sizeof(*IIlIll->sg);
#endif
if(num_sgs>lIlIIIIIl){IlllI(
"\x75\x73\x62\x64\x5f\x73\x67\x5f\x61\x6c\x6c\x6f\x63\x3a\x20\x74\x6f\x6f\x20\x6c\x61\x72\x67\x65" "\n"
);return-EOVERFLOW;}IIlIll->num_sgs=num_sgs;
#if KERNEL_LT_EQ((0x1840+1338-0x1d78),(0x1970+1621-0x1fbf),(0xf22+2713-0x1999)) 

IIlIll->sg=IlIIllI(ALIGN(num_sgs*sizeof(*IIlIll->sg),sizeof(void*))+sizeof(*
IIlIll->lIIlllI),GFP_KERNEL);IIlIll->lIIlllI=(struct usb_sg_request*)((char*)
IIlIll->sg+ALIGN(num_sgs*sizeof(*IIlIll->sg),(0x7c0+7538-0x252a)));IIlIll->
lIIlllI->sg=IIlIll->sg;
#else

IIlIll->sg=IlIIllI(num_sgs*sizeof(*IIlIll->lIIlllI),GFP_KERNEL);IIlIll->lIIlllI=
IIlIll->sg;
#endif
if(IIlIll->sg==NULL){IlllI(
"\x75\x73\x62\x64\x5f\x73\x67\x5f\x61\x6c\x6c\x6f\x63\x3a\x20\x73\x67\x20\x61\x6c\x6c\x6f\x63\x20\x66\x61\x69\x6c\x65\x64\x28\x31\x29" "\n"
);return-ENOMEM;}sg_init_table(IIlIll->sg,IIlIll->num_sgs);for_each_sg(IIlIll->
sg,sg,IIlIll->num_sgs,i){size_t IIIlIIllI=min(length,lIIlIIll);void*IllllIlIl=
IllllIl(IIIlIIllI,GFP_KERNEL);if(IllllIlIl==NULL)break;sg_set_buf(sg,IllllIlIl,
IIIlIIllI);length-=IIIlIIllI;}if(i<IIlIll->num_sgs){IlllI(
"\x75\x73\x62\x64\x5f\x61\x6c\x6c\x6f\x63\x5f\x6e\x5f\x63\x6f\x70\x79\x5f\x70\x61\x72\x74\x69\x6f\x74\x69\x6f\x6e\x65\x64\x5f\x75\x6e\x72\x62\x3a\x20\x73\x67\x20\x61\x6c\x6c\x6f\x63\x20\x66\x61\x69\x6c\x65\x64\x28\x32\x29" "\n"
);IIlIll->num_sgs=i;IIlIIllI(IIlIll);return-ENOMEM;}return(0x114+4937-0x145d);}
void IIlIIllI(struct IlIIlll*IIlIll){if(IIlIll->sg){int i;struct scatterlist*sg;
for_each_sg(IIlIll->sg,sg,IIlIll->num_sgs,i){lllIII(sg_virt(sg));}lllIII(IIlIll
->sg);}IIlIll->sg=NULL;IIlIll->lIIlllI=NULL;IIlIll->num_sgs=(0x683+3071-0x1282);
}size_t llIllIIll(struct IlIIlll*IIlIll,const void __user*llIlI,size_t length){
int i;size_t IlIlI=(0xfd7+496-0x11c7);struct scatterlist*sg;for_each_sg(IIlIll->
sg,sg,IIlIll->num_sgs,i){size_t llllIIl;if(length==(0x1364+657-0x15f5))break;
llllIIl=min((size_t)sg->length,length);if(__copy_from_user(sg_virt(sg),llIlI,
llllIIl)){break;}length-=llllIIl;llIlI+=llllIIl;IlIlI+=llllIIl;}return IlIlI;}
size_t lIIIIIIIl(struct IlIIlll*IIlIll,void __user*llIlI,size_t length){int i;
size_t IlIlI=(0x1b56+2161-0x23c7);struct scatterlist*sg;for_each_sg(IIlIll->sg,
sg,IIlIll->num_sgs,i){size_t llllIIl;if(length==(0xf64+3587-0x1d67))break;
llllIIl=min((size_t)sg->length,length);if(__copy_to_user(llIlI,sg_virt(sg),
llllIIl)){break;}length-=llllIIl;llIlI+=llllIIl;IlIlI+=llllIIl;}return IlIlI;}
#endif 

