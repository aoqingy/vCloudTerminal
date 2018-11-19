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

#ifndef IlllIlllI
#define IlllIlllI

#ifdef __KERNEL__
#include <linux/types.h>
#else
#include <stdint.h>
#endif
typedef int8_t lIllllIII;typedef int16_t IllIIIlIl;typedef int32_t IIIIIIIlI;
typedef int64_t IIlIIlIIl;typedef uint8_t IIIII;typedef uint16_t llIIIl;typedef 
uint32_t lllIl;typedef uint64_t Illlll;typedef int BOOL;
#ifndef __KERNEL__
#include <semaphore.h>
typedef sem_t*lIIllllII;
#endif
#ifndef TRUE
#define TRUE (0x1632+1292-0x1b3d)
#endif
#ifndef FALSE
#define FALSE (0x8bb+3769-0x1774)
#endif
#ifndef __KERNEL__
#include <endian.h>
#include <byteswap.h>
#if __BYTE_ORDER == __BIG_ENDIAN
#define lIIlIIIII(IlllII) lIIIllllI((IlllII))
#define lIlIllIll(IlllII) llIIlIlll((IlllII))
#define IllIlIIII(IlllII) lIIIlIlIl((IlllII))
#define IlllIIllI(IlllII) lIIIllllI((IlllII))
#define llIIIIlIl(IlllII) llIIlIlll((IlllII))
#define lIIlIlIll(IlllII) lIIIlIlIl((IlllII))
#else
#define lIIlIIIII(IlllII) (IlllII)
#define lIlIllIll(IlllII) (IlllII)
#define IllIlIIII(IlllII) (IlllII)
#define IlllIIllI(IlllII) (IlllII)
#define llIIIIlIl(IlllII) (IlllII)
#define lIIlIlIll(IlllII) (IlllII)
#endif
# endif
#endif 

