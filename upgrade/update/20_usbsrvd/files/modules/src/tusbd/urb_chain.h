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

#ifndef IllllIIll
#define IllllIIll
#define lIlIllII (0x2a7+2483-0xc3a)
struct lllIlI;typedef void(*urb_chain_complete_t)(struct lllIlI*);struct lllIlI{
spinlock_t lock;struct urb*lIlIIl[lIlIllII];struct usb_device*lIIIIl;int pipe;
int lIIIIll;int IIIIlIII;int status;size_t lIllllIIl;unsigned char IIlII;
atomic_t IllllllIl;void*context;urb_chain_complete_t complete;};struct lIIlIlI{
void*transfer_buffer[lIlIllII];
size_t transfer_buffer_length[lIlIllII];
size_t actual_length[lIlIllII];
unsigned int number_of_packets[lIlIllII];
unsigned int IIlII;
};int lIIIIIlll(struct lllIlI*lIIII,int pipe,int interval,int IIIIlIII,int 
lIIIIll,struct usb_device*lIIIIl,struct lIIlIlI*IIIlIIll,void*context,
urb_chain_complete_t complete,gfp_t llllI);int IlllIIIll(struct lllIlI*lIIII);
int lIIllIIII(struct lllIlI*lIIII);int IIIlIllII(struct lllIlI*lIIII);int 
IIlIllIIl(struct lllIlI*lIIII);int IIlIIIlIl(struct lllIlI*lIIII);int lIllIIIII(
struct lllIlI*lIIII);int IIIlIIIII(struct lllIlI*lIIII,struct urb*lIlll);int 
IllllIIIl(struct lIIlIlI*lIIII,size_t length,int lIlIllIl);int lIIlIIIlI(struct 
lIIlIlI*lIIII,size_t length,IIIIlII*llIllII,lllIl IllllllI);int IlIlIllII(struct
 lIIlIlI*lIIII,const void*llIlI,size_t length);int IIIlIllIl(struct lIIlIlI*
lIIII,void*llIlI,size_t length);int IlIlllIII(struct lIIlIlI*lIIII);size_t 
llIIlllII(struct lIIlIlI*lIIII,IIIIlII*llIllII,lllIl IllllllI);size_t IllIIlIII(
struct lIIlIlI*lIIII,IIIIlII*llIllII,lllIl IllllllI);
#endif 

