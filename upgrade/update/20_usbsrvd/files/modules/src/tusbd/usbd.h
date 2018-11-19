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

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/usb.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/poll.h>
#include <linux/spinlock.h>
#include <linux/list.h>
#include <linux/version.h>
#include <linux/kref.h>
#include <linux/device.h>
#include <linux/compat.h>
#include <asm/uaccess.h>
#include <linux/vmalloc.h>
#include <linux/module.h>
#define IIIlIlll			((0x11f5+2076-0x19f1)*(0x53f+4686-0x138d)) 
#define KERNEL_GT(lIIlll,llIllI,lIIIlIl)			(LINUX_VERSION_CODE > KERNEL_VERSION(\
(lIIlll),(llIllI),(lIIIlIl)))
#define KERNEL_LT(lIIlll,llIllI,lIIIlIl)			(LINUX_VERSION_CODE < KERNEL_VERSION(\
(lIIlll),(llIllI),(lIIIlIl)))
#define KERNEL_EQ(lIIlll,llIllI,lIIIlIl)			(LINUX_VERSION_CODE == KERNEL_VERSION\
((lIIlll),(llIllI),(lIIIlIl)))
#define KERNEL_GT_EQ(lIIlll,llIllI,lIIIlIl)			(LINUX_VERSION_CODE >= \
KERNEL_VERSION((lIIlll),(llIllI),(lIIIlIl)))
#define KERNEL_LT_EQ(lIIlll,llIllI,lIIIlIl)			(LINUX_VERSION_CODE <= \
KERNEL_VERSION((lIIlll),(llIllI),(lIIIlIl)))
#if defined(RHEL_RELEASE_CODE) 
#define RHEL_RELEASE_GT(lIIlll,llIllI) 		(RHEL_RELEASE_CODE > \
RHEL_RELEASE_VERSION((lIIlll),(llIllI)))
#define RHEL_RELEASE_LT(lIIlll,llIllI)		(RHEL_RELEASE_CODE < \
RHEL_RELEASE_VERSION((lIIlll),(llIllI)))
#define RHEL_RELEASE_EQ(lIIlll,llIllI)		(RHEL_RELEASE_CODE == \
RHEL_RELEASE_VERSION((lIIlll),(llIllI)))
#define RHEL_RELEASE_GT_EQ(lIIlll,llIllI)		(RHEL_RELEASE_CODE >= \
RHEL_RELEASE_VERSION((lIIlll),(llIllI)))
#define RHEL_RELEASE_LT_EQ(lIIlll,llIllI)		(RHEL_RELEASE_CODE <= \
RHEL_RELEASE_VERSION((lIIlll),(llIllI)))
#else
#define RHEL_RELEASE_GT(lIIlll,llIllI) 		(0x67f+7565-0x240c)
#define RHEL_RELEASE_LT(lIIlll,llIllI)		(0x18e8+88-0x1940)
#define RHEL_RELEASE_EQ(lIIlll,llIllI)		(0x156+660-0x3ea)
#define RHEL_RELEASE_GT_EQ(lIIlll,llIllI)		(0x178d+1358-0x1cdb)
#define RHEL_RELEASE_LT_EQ(lIIlll,llIllI)		(0x1140+1518-0x172e)
#endif

#ifndef BUS_ID_SIZE
#define BUS_ID_SIZE (0x353+174-0x3ed)
#endif
#include "../public/pubstt2.h"
#include "../public/apitypes.h"
#include "../public/pubuniprotocol.h"
#include "../public/interface.h"
#include "../public/public_devices.h"
#include "utils.h"
#include "driver.h"
#include "cdev.h"
#include "stub.h"
#include "vhci.h"
#include "minor_loader.h"
#include "minor_stub.h"
#include "minor_vbus.h"
#include "minor_vstub.h"
#include "urb_chain.h"
#include "sg.h"

#if KERNEL_LT_EQ((0x4d4+6019-0x1c55),(0xfb4+3180-0x1c1a),(0x1338+1807-0x1a38))
#define lllIIIII __stringify(KBUILD_MODNAME)
#else
#define lllIIIII KBUILD_MODNAME
#endif

#ifndef CONFIG_PRINTK_TIME
#define lIlIlIIl(IIIllII, llIlIIl...) printk(KERN_DEBUG \
"\x5b\x25\x30\x39\x75\x5d\x20\x25\x73\x3a\x20" IIIllII, jiffies_to_msecs(jiffies\
), lllIIIII, ## llIlIIl)
#else
#define lIlIlIIl(IIIllII, llIlIIl...) printk(KERN_DEBUG "\x25\x73\x3a\x20" \
IIIllII, lllIIIII, ## llIlIIl)
#endif

#ifdef _USBD_DEBUG_BUILD_
#define IlllI(IIIllII, llIlIIl...) lIlIlIIl(IIIllII, ##llIlIIl)
#define llIll(IIIllII, llIlIIl...) lIlIlIIl("\x25\x73\x3a\x20" IIIllII, __func__\
, ##llIlIIl)
#else
#define IlllI(IIIllII, llIlIIl...) do {} while((0x60a+7645-0x23e7))
#define llIll(IIIllII, llIlIIl...) do {} while((0x92c+6061-0x20d9))
#endif

#define IIIIll(IIIllII, llIlIIl...) lIlIlIIl(IIIllII, ##llIlIIl)
#if KERNEL_LT_EQ((0xda+2815-0xbd7),(0x1685+2674-0x20f1),(0xd8c+2253-0x1642))
typedef unsigned long uintptr_t;
#endif
#if KERNEL_LT_EQ((0x170+7405-0x1e5b),(0x73+7151-0x1c5c),(0x12ed+662-0x1574))
#define atomic_xchg(lIIIIllIl, new) (xchg(&((lIIIIllIl)->counter), new))
#endif
#if KERNEL_LT((0x161f+1406-0x1b9a),(0xb82+5037-0x1f1d),(0x248f+219-0x256a))




#undef strncasecmp
#define strncasecmp strnicmp
#endif

