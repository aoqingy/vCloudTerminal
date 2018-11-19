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

#ifndef IllIIlIIl
#define IllIIlIIl
struct IllIIlIl;struct IllllI{struct{ssize_t(*read)(void*,char __user*,size_t);
ssize_t(*write)(void*,const char __user*,size_t);long(*unlocked_ioctl)(void*,
unsigned int,unsigned long);long(*compat_ioctl)(void*,unsigned int,unsigned long
);int(*open)(void*,int);int(*release)(void*,int);unsigned int(*poll)(void*,
struct file*lIIIlI,poll_table*);int(*mmap)(void*,struct vm_area_struct*IlIllll);
void(*IIlIlIll)(void*);void(*IIIIlIll)(void*);}ops;int lIIIll;int IlIllI;struct 
mutex mutex;
#if KERNEL_GT_EQ((0x4b2+857-0x809),(0x2303+432-0x24ad),(0x438+2043-0xc19)) 
struct device*dev;
#else 
struct class_device*dev;
#endif
struct IllIIlIl*IlllIlI;void*context;};struct IllIIlIl{const char*name;const 
char*IIllllIl;};int lIlIlllIl(void);int lllIIIll(void);int lllIIIIl(struct 
IllllI*lIllI,int IlIllIII,int lIllllII);void llIlIIIl(struct IllllI*lIllI);dev_t
 lllIllIlI(struct IllllI*lIllI);int IlIIIIIl(struct IllllI*lIllI);void lIllllIl(
struct IllllI*lIllI);void lIIllIll(struct IllllI*lIllI);
#endif 

