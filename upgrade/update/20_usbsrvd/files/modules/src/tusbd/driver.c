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

#if KERNEL_LT((0xcf2+3234-0x1992),(0x13dd+107-0x1442),(0x1d7+6216-0x1a10))
#error This module requires kernel version 2.6.15 or newer
#endif

#if !defined(CONFIG_USB) && !defined(CONFIG_USB_MODULE)
#error This module requires kernel to be compiled with USB support (CONFIG_USB)
#endif

#if KERNEL_LT((0xd7a+1035-0x1182),(0x2436+138-0x24b8),(0x491+3596-0x129d)) && !\
defined(CONFIG_HOTPLUG)
#error\
 This module requires kernel to be compiled with hotplug support (CONFIG_HOTPLUG)
#endif

#if !defined(CONFIG_NET) && !defined(CONFIG_NET_MODULE)
#error\
 This module requires kernel to be compiled with networking support (CONFIG_NET)
#endif

#if KERNEL_LT_EQ((0xe66+885-0x11d9),(0x31f+7170-0x1f1b),(0xbd8+3484-0x1965)) && \
!defined(CONFIG_KOBJECT_UEVENT)
#error\
 This module requires kernel to be compiled with uevent support (CONFIG_KOBJECT_UEVENT)
#endif

#if !defined(CONFIG_UNIX) && !defined(CONFIG_UNIX_MODULE)
#error\
 This module requires kernel to be compiled with Unix domain sockets support (CONFIG_UNIX)
#endif
#ifdef _USBD_DEBUG_MEMORY_
atomic_t lIIIlllll=ATOMIC_INIT((0xebc+1470-0x147a));atomic_t IlIIIIIII=
ATOMIC_INIT((0x21d+5463-0x1774));atomic_t IllIlllI=ATOMIC_INIT((0x101a+1-0x101b)
);atomic_t IlIIllll=ATOMIC_INIT((0x1755+3955-0x26c8));
#ifdef ATOMIC64_INIT
atomic64_t lIIIlIIl=ATOMIC64_INIT((0xa8+9658-0x2662));
#endif
atomic_t lIllllll=ATOMIC_INIT((0x11c5+288-0x12e5));atomic_t lIlIllIII=
ATOMIC_INIT((0xa93+4160-0x1ad3));atomic_t lIllIIlIl=ATOMIC_INIT(
(0x13a+6270-0x19b8));atomic_t llIIIlIlI=ATOMIC_INIT((0x834+684-0xae0));atomic_t 
IlllIlIlI=ATOMIC_INIT((0xd51+1979-0x150c));atomic_t lllIlllll=ATOMIC_INIT(
(0x153a+1784-0x1c32));atomic_t llIllllI=ATOMIC_INIT((0xd9c+164-0xe40));atomic_t 
llIIIlIIl=ATOMIC_INIT((0x18d6+1781-0x1fcb));atomic_t lIlIlIIIl=ATOMIC_INIT(
(0x4a4+2733-0xf51));atomic_t IlIllIlI=ATOMIC_INIT((0x228+6053-0x19cd));atomic_t 
lIIlllIII=ATOMIC_INIT((0x19d6+952-0x1d8e));
#endif 
static int IllllIII=(0x495+5782-0x1b2b);module_param(IllllIII,int,
(0x1147+4238-0x21d5));static int __init IlIIllllI(void){int IlIlI;int llIlIIIIl=
(0xf35+5716-0x2589);
#ifdef _USBD_ENABLE_STUB_
int llllIllII=(0x1793+1446-0x1d39);
#endif
#ifdef _USBD_ENABLE_VHCI_
int lIlllIlll=(0x1bea+1524-0x21de);
#endif
IlllI("\x75\x73\x62\x64\x5f\x69\x6e\x69\x74\x3a\x20\x2b\x2b" "\n");do{if(
IllllIII){IlllI(
"\x75\x73\x62\x64\x5f\x69\x6e\x69\x74\x3a\x20\x70\x72\x6f\x62\x65\x2d\x6f\x6e\x6c\x79\x20\x6d\x6f\x64\x65" "\n"
);IlIlI=(0x2331+785-0x2642);break;}IlIlI=lIlIlllIl();if(IlIlI!=
(0xd67+3991-0x1cfe)){IlllI(
"\x75\x73\x62\x64\x5f\x69\x6e\x69\x74\x3a\x20\x75\x73\x62\x64\x5f\x63\x64\x65\x76\x5f\x69\x6e\x69\x74\x5f\x6d\x6f\x64\x75\x6c\x65\x20\x66\x61\x69\x6c\x65\x64\x2e\x20\x45\x72\x72\x6f\x72\x20\x6e\x75\x6d\x62\x65\x72\x20\x25\x64" "\n"
,IlIlI);break;}llIlIIIIl=(0x58+7114-0x1c21);
#ifdef _USBD_ENABLE_STUB_
IlIlI=IlIIIIlll();if(IlIlI!=(0x13e0+283-0x14fb)){IlllI(
"\x75\x73\x62\x64\x5f\x69\x6e\x69\x74\x3a\x20\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x69\x6e\x69\x74\x5f\x6d\x6f\x64\x75\x6c\x65\x20\x66\x61\x69\x6c\x65\x64\x2e\x20\x45\x72\x72\x6f\x72\x20\x6e\x75\x6d\x62\x65\x72\x20\x25\x64" "\n"
,IlIlI);break;}llllIllII=(0x6bd+3144-0x1304);
#endif
#ifdef _USBD_ENABLE_VHCI_
IlIlI=IlIlIIIlI();if(IlIlI!=(0x3c7+280-0x4df)){IlllI(
"\x75\x73\x62\x64\x5f\x69\x6e\x69\x74\x3a\x20\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x69\x6e\x69\x74\x5f\x6d\x6f\x64\x75\x6c\x65\x20\x66\x61\x69\x6c\x65\x64\x2e\x20\x45\x72\x72\x6f\x72\x20\x6e\x75\x6d\x62\x65\x72\x20\x25\x64" "\n"
,IlIlI);break;}lIlllIlll=(0x1990+2526-0x236d);
#endif
}while((0x1582+1323-0x1aad));if(IlIlI!=(0x1806+3388-0x2542)){
#ifdef _USBD_ENABLE_VHCI_
if(lIlllIlll)IIlllIII();
#endif
#ifdef _USBD_ENABLE_STUB_
if(llllIllII)IIIIlIIlI();
#endif
if(llIlIIIIl)lllIIIll();}IlllI(
"\x75\x73\x62\x64\x5f\x69\x6e\x69\x74\x3a\x20\x2d\x2d" "\n");return IlIlI;}
static void __exit usbd_exit(void){if(IllllIII){IlllI(
"\x75\x73\x62\x64\x5f\x65\x78\x69\x74\x3a\x20\x70\x72\x6f\x62\x65\x2d\x6f\x6e\x6c\x79\x20\x6d\x6f\x64\x65" "\n"
);return;}
#ifdef _USBD_ENABLE_VHCI_
IIlllIII();
#endif
#ifdef _USBD_ENABLE_STUB_
IIIIlIIlI();
#endif
lllIIIll();
#ifdef _USBD_DEBUG_MEMORY_
IIIIll("\x73\x74\x61\x74\x73\x3a" "\n");IIIIll(
"\x75\x72\x62\x20\x61\x6c\x6c\x6f\x63\x3a\x20\x25\x64" "\n",atomic_read(&
lIIIlllll));IIIIll("\x75\x72\x62\x20\x66\x72\x65\x65\x3a\x20\x25\x64" "\n",
atomic_read(&IlIIIIIII));IIIIll(
"\x6d\x65\x6d\x20\x61\x6c\x6c\x6f\x63\x3a\x20\x25\x64" "\n",atomic_read(&
IllIlllI));IIIIll("\x6d\x65\x6d\x20\x66\x72\x65\x65\x3a\x20\x25\x64" "\n",
atomic_read(&IlIIllll));
#ifdef ATOMIC64_INIT
IIIIll("\x6d\x65\x6d\x20\x73\x69\x7a\x65\x3a\x20\x25\x6c\x6c\x64" "\n",(long 
long)atomic64_read(&lIIIlIIl));
#endif
IIIIll("\x75\x72\x65\x71\x20\x63\x72\x65\x61\x74\x65\x3a\x20\x25\x64" "\n",
atomic_read(&lIllllll));IIIIll(
"\x75\x72\x65\x71\x20\x66\x72\x65\x65\x3a\x20\x25\x64" "\n",atomic_read(&
lIlIllIII));IIIIll(
"\x75\x72\x65\x71\x20\x64\x65\x73\x74\x72\x6f\x79\x3a\x20\x25\x64" "\n",
atomic_read(&lIllIIlIl));IIIIll(
"\x76\x72\x65\x71\x20\x63\x72\x65\x61\x74\x65\x3a\x20\x25\x64" "\n",atomic_read(
&llIIIlIlI));IIIIll("\x76\x72\x65\x71\x20\x66\x72\x65\x65\x3a\x20\x25\x64" "\n",
atomic_read(&IlllIlIlI));IIIIll(
"\x73\x74\x75\x62\x20\x63\x72\x65\x61\x74\x65\x3a\x20\x25\x64" "\n",atomic_read(
&lllIlllll));IIIIll(
"\x73\x74\x75\x62\x20\x72\x65\x6d\x6f\x76\x65\x3a\x20\x25\x64" "\n",atomic_read(
&llIllllI));IIIIll(
"\x73\x74\x75\x62\x20\x64\x65\x73\x74\x72\x6f\x79\x3a\x20\x25\x64" "\n",
atomic_read(&llIIIlIIl));IIIIll(
"\x76\x73\x74\x75\x62\x20\x63\x72\x65\x61\x74\x65\x3a\x20\x25\x64" "\n",
atomic_read(&lIlIlIIIl));IIIIll(
"\x76\x73\x74\x75\x62\x20\x72\x65\x6d\x6f\x76\x65\x3a\x20\x25\x64" "\n",
atomic_read(&IlIllIlI));IIIIll(
"\x76\x73\x74\x75\x62\x20\x64\x65\x73\x74\x72\x6f\x79\x3a\x20\x25\x64" "\n",
atomic_read(&lIIlllIII));
#endif 
IlllI("\x75\x73\x62\x64\x5f\x65\x78\x69\x74" "\n");}module_init(IlIIllllI);
module_exit(usbd_exit);MODULE_LICENSE("\x47\x50\x4c");
