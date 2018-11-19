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

#ifndef IIIIIlIII
#define IIIIIlIII
#if KERNEL_GT_EQ((0x57d+3324-0x1277),(0x18bc+1021-0x1cb3),(0x2277+1202-0x270a))
#include <linux/scatterlist.h>
struct IlIIlll{
#if KERNEL_LT_EQ((0x966+738-0xc46),(0xbe0+1216-0x109a),(0x2d6+4359-0x13bb)) 
struct usb_sg_request*lIIlllI;
#else
struct scatterlist*lIIlllI;
#endif
struct scatterlist*sg;int num_sgs;};int llIlllIII(struct IlIIlll*sg,size_t 
length,int lIlIllIl);void IIlIIllI(struct IlIIlll*sg);size_t llIllIIll(struct 
IlIIlll*sg,const void __user*llIlI,size_t length);size_t lIIIIIIIl(struct 
IlIIlll*sg,void __user*llIlI,size_t length);
#endif 
#endif 

