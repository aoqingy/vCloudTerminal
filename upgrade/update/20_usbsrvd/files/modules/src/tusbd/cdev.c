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
#include <linux/ctype.h> 
#define IIlIIIl (0x11fc+3532-0x1ec8)
static struct cdev*IIIllIl=NULL;static dev_t IlIlll=MKDEV((0x29+7369-0x1cf2),
(0x94a+2982-0x14f0));static void*IIIllllI[IIlIIIl]={(0x199+4918-0x14cf)};static 
struct mutex IIlIIII;static struct class*IIlIlll=NULL;ssize_t lllllIIIl(struct 
file*,char __user*,size_t,loff_t*);ssize_t llIIIIIII(struct file*,const char 
__user*,size_t,loff_t*);long IlIIIlIll(struct file*,unsigned int,unsigned long);
#ifdef CONFIG_COMPAT
long IlIlIIllI(struct file*,unsigned int,unsigned long);
#endif
int IIlIIIIII(struct inode*,struct file*);int llIlllllI(struct inode*,struct 
file*);unsigned int IlllllIIl(struct file*lIIIlI,poll_table*lllIll);int 
llllllllI(struct file*lIIIlI,struct vm_area_struct*IlIllll);
#if KERNEL_LT_EQ((0x230+5928-0x1956),(0xa82+909-0xe09),(0x66b+1360-0xba4)) 
static int IllIIIII(struct class_device*dev,char**envp,int lllIIIIll,char*IIIIl,
int IIlIlIIll);static void lIIIlIll(struct class_device*device);
#elif KERNEL_LT_EQ((0x373+4933-0x16b6),(0xc1c+6228-0x246a),(0x1842+2314-0x2133))\
 
static int IllIIIII(struct class_device*dev,struct kobj_uevent_env*IllllII);
static void lIIIlIll(struct class_device*device);
#else 
static int IllIIIII(struct device*dev,struct kobj_uevent_env*IllllII);
#endif
static struct file_operations IIllIllIl={.owner=THIS_MODULE,.read=lllllIIIl,.
write=llIIIIIII,.poll=IlllllIIl,.unlocked_ioctl=IlIIIlIll,
#ifdef CONFIG_COMPAT
.compat_ioctl=IlIlIIllI,
#endif
.mmap=llllllllI,.open=IIlIIIIII,.release=llIlllllI,};int lIlIlllIl(void){int 
IlIlI=(0x17b5+755-0x1aa8);IlllI(
"\x69\x6e\x69\x74\x5f\x63\x64\x65\x76\x5f\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x2b\x2b" "\n"
);do{mutex_init(&IIlIIII);IIlIlll=class_create(THIS_MODULE,llIIlII);if(IIlIlll==
NULL){IlllI(
"\x69\x6e\x69\x74\x5f\x63\x64\x65\x76\x5f\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x63\x6c\x61\x73\x73\x5f\x63\x72\x65\x61\x74\x65\x20\x66\x61\x69\x6c\x65\x64\x2e" "\n"
);IlIlI=-ENOMEM;break;}
#if KERNEL_LT_EQ((0x27f+3435-0xfe8),(0x12f6+2331-0x1c0b),(0x16c0+1677-0x1d3e)) 
IIlIlll->hotplug=IllIIIII,IIlIlll->release=lIIIlIll,
#elif KERNEL_LT_EQ((0x123b+2287-0x1b28),(0x18cb+1205-0x1d7a),(0xd90+943-0x1126))\
 
IIlIlll->uevent=IllIIIII,IIlIlll->release=lIIIlIll,
#else 
IIlIlll->dev_uevent=IllIIIII,
#endif
IlIlI=alloc_chrdev_region(&IlIlll,(0x87a+4640-0x1a9a),IIlIIIl,llIIlII);if(IlIlI
!=(0x15b4+4435-0x2707)){IlllI(
"\x69\x6e\x69\x74\x5f\x63\x64\x65\x76\x5f\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x61\x6c\x6c\x6f\x63\x5f\x63\x68\x72\x64\x65\x76\x5f\x72\x65\x67\x69\x6f\x6e\x20\x66\x61\x69\x6c\x65\x64\x2e\x20\x45\x72\x72\x6f\x72\x20\x6e\x75\x6d\x62\x65\x72\x20\x25\x64" "\n"
,IlIlI);break;}IlllI(
"\x69\x6e\x69\x74\x5f\x63\x64\x65\x76\x5f\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x61\x6c\x6c\x6f\x63\x61\x74\x65\x64\x20\x64\x65\x76\x6e\x75\x6d\x20\x72\x65\x67\x69\x6f\x6e\x3a\x20\x4d\x61\x6a\x6f\x72\x20\x25\x64\x20\x4d\x69\x6e\x6f\x72\x20\x25\x64" "\n"
,MAJOR(IlIlll),MINOR(IlIlll));memset(IIIllllI,(0x1242+4599-0x2439),sizeof(
IIIllllI));IIIllIl=cdev_alloc();if(IIIllIl==NULL){IlllI(
"\x69\x6e\x69\x74\x5f\x63\x64\x65\x76\x5f\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x63\x64\x65\x76\x5f\x61\x6c\x6c\x6f\x63\x20\x66\x61\x69\x6c\x65\x64\x2e" "\n"
);IlIlI=-ENOMEM;break;}IIIllIl->owner=THIS_MODULE;IIIllIl->ops=&IIllIllIl;IlIlI=
cdev_add(IIIllIl,IlIlll,IIlIIIl);if(IlIlI!=(0x1c4+6828-0x1c70)){IlllI(
"\x69\x6e\x69\x74\x5f\x63\x64\x65\x76\x5f\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x63\x64\x65\x76\x5f\x61\x64\x64\x20\x66\x61\x69\x6c\x65\x64\x2e\x20\x45\x72\x72\x6f\x72\x20\x6e\x75\x6d\x62\x65\x72\x20\x25\x64" "\n"
,IlIlI);break;}}while((0x1eda+1133-0x2347));if(IlIlI!=(0x590+6563-0x1f33)){if(
IIIllIl)cdev_del(IIIllIl);if(IlIlll!=MKDEV((0x2479+464-0x2649),
(0x1b37+1509-0x211c)))unregister_chrdev_region(IlIlll,(0x101f+2225-0x17d1));if(
IIlIlll)class_destroy(IIlIlll);IIIllIl=NULL;IlIlll=MKDEV((0x122c+2249-0x1af5),
(0x24b+125-0x2c8));IIlIlll=NULL;}IlllI(
"\x69\x6e\x69\x74\x5f\x63\x64\x65\x76\x5f\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x3d\x25\x64" "\n"
,IlIlI);return IlIlI;}int lllIIIll(void){IlllI(
"\x64\x65\x73\x74\x72\x6f\x79\x5f\x63\x64\x65\x76" "\n");if(IIIllIl)cdev_del(
IIIllIl);if(IlIlll!=MKDEV((0xe1f+747-0x110a),(0x78f+1465-0xd48)))
unregister_chrdev_region(IlIlll,IIlIIIl);if(IIlIlll)class_destroy(IIlIlll);
IIIllIl=NULL;IlIlll=MKDEV((0x17d0+2921-0x2339),(0x1345+530-0x1557));IIlIlll=NULL
;return(0xd6c+3654-0x1bb2);}
#if KERNEL_LT_EQ((0xc18+2801-0x1707),(0xc40+436-0xdee),(0xcd3+6063-0x2469)) 
static void lIIIlIll(struct class_device*device){kfree(device);}
#endif
#if KERNEL_LT_EQ((0x5c2+5950-0x1cfe),(0x519+4807-0x17da),(0xc84+6176-0x248d)) 
static int IllIIIII(struct class_device*device,char**envp,int lllIIIIll,char*
IIIIl,int IIlIlIIll){struct IllllI*lIllI=device->class_data;if(lIllI&&lIllI->
IlllIlI){int i;int length;struct IllIIlIl*lllIlll;for(lllIlll=lIllI->IlllIlI,i=
(0x1e56+192-0x1f16),length=(0xf5c+1560-0x1574);lllIlll->name&&lllIlll->IIllllIl;
lllIlll++){
#if KERNEL_LT_EQ((0x9e4+7129-0x25bb),(0x31d+897-0x698),(0x356+4734-0x15c5)) 
if(add_hotplug_env_var(
#else 
if(add_uevent_var(
#endif
envp,lllIIIIll,&i,IIIIl,IIlIlIIll,&length,"\x25\x73\x5f\x25\x73\x3d\x25\x73",
llIIlII,lllIlll->name,lllIlll->IIllllIl)==(0x3c4+8352-0x2464)){int llllIl;for(
llllIl=(0x59+9500-0x2575);envp[i-(0xa16+5647-0x2024)][llllIl]!='\0'&&envp[i-
(0x20d5+227-0x21b7)][llllIl]!=((char)(0x1216+2296-0x1ad1));llllIl++)envp[i-
(0x371+422-0x516)][llllIl]=toupper(envp[i-(0x84d+7802-0x26c6)][llllIl]);}}}
return(0x44f+1563-0xa6a);}
#else 
static int IllIIIII(
#if KERNEL_LT_EQ((0x492+4502-0x1626),(0x1e8c+575-0x20c5),(0xbcf+453-0xd7b)) 
struct class_device*device,
#else 
struct device*device,
#endif
struct kobj_uevent_env*IllllII){
#if KERNEL_LT_EQ((0x1117+5565-0x26d2),(0x819+861-0xb70),(0xac5+5780-0x2140)) 
struct IllllI*lIllI=device->class_data;
#else 
struct IllllI*lIllI=dev_get_drvdata(device);
#endif
if(lIllI&&lIllI->IlllIlI){struct IllIIlIl*lllIlll;for(lllIlll=lIllI->IlllIlI;
lllIlll->name&&lllIlll->IIllllIl;lllIlll++){if(add_uevent_var(IllllII,
"\x25\x73\x5f\x25\x73\x3d\x25\x73",llIIlII,lllIlll->name,lllIlll->IIllllIl)==
(0xa8a+818-0xdbc)){int llllIl;for(llllIl=(0xf37+1215-0x13f6);IllllII->envp[
IllllII->envp_idx-(0x109f+4694-0x22f4)][llllIl]!='\0'&&IllllII->envp[IllllII->
envp_idx-(0x13c8+842-0x1711)][llllIl]!=((char)(0x1ee2+370-0x2017));llllIl++)
IllllII->envp[IllllII->envp_idx-(0x42d+3624-0x1254)][llllIl]=toupper(IllllII->
envp[IllllII->envp_idx-(0x4a+1710-0x6f7)][llllIl]);}}}return(0xe38+4602-0x2032);
}
#endif 
int lIIIlIlll(struct IllllI*lIllI,int lIIIll){















#if KERNEL_GT_EQ((0x6f5+7701-0x2508),(0xa82+7099-0x2637),(0x75b+2526-0x111e)) 
struct device*dev=NULL;dev=device_create(IIlIlll,NULL,MKDEV(MAJOR(IlIlll),MINOR(
IlIlll)+lIIIll),lIllI,llIIlII"\x5f\x25\x64",lIIIll);
#elif KERNEL_EQ((0xea9+2001-0x1678),(0xd58+6359-0x2629),(0xc61+653-0xed4)) 
struct device*dev=NULL;dev=device_create_drvdata(IIlIlll,NULL,MKDEV(MAJOR(IlIlll
),MINOR(IlIlll)+lIIIll),lIllI,llIIlII"\x5f\x25\x64",lIIIll);
#else 
struct class_device*dev=NULL;int IIIIlIlII;dev=kzalloc(sizeof(*dev),GFP_KERNEL);
if(dev){dev->devt=MKDEV(MAJOR(IlIlll),MINOR(IlIlll)+lIIIll);dev->dev=NULL;dev->
class=IIlIlll;dev->parent=NULL;dev->release=NULL;
dev->class_data=lIllI;
#if KERNEL_LT_EQ((0x739+2125-0xf84),(0x12f9+2329-0x1c0c),(0x18ac+1705-0x1f46)) 
dev->hotplug=NULL;
#else 
dev->uevent=NULL;
#endif
snprintf(dev->class_id,BUS_ID_SIZE,llIIlII"\x5f\x25\x64",lIIIll);IIIIlIlII=
class_device_register(dev);if(IIIIlIlII){kfree(dev);dev=ERR_PTR(IIIIlIlII);}}
else{dev=ERR_PTR(-ENOMEM);}
#endif
if(IS_ERR(dev)){return PTR_ERR(dev);}lIllI->dev=dev;return(0x48+908-0x3d4);}void
 IlllIIIII(struct IllllI*lIllI,int lIIIll){if(lIllI->dev){
#if KERNEL_GT_EQ((0x158f+486-0x1773),(0xf76+4062-0x1f4e),(0x227+6622-0x1beb)) 
device_destroy(IIlIlll,MKDEV(MAJOR(IlIlll),MINOR(IlIlll)+lIIIll));
#else 
class_device_destroy(IIlIlll,MKDEV(MAJOR(IlIlll),MINOR(IlIlll)+lIIIll));
#endif
lIllI->dev=NULL;}}int lllIIIIl(struct IllllI*lIllI,int IlIllIII,int lIllllII){
int i;if(lIllllII==-(0xfb7+4508-0x2152)){lIllllII=IIlIIIl-(0x133d+2131-0x1b8f);}
if(IlIllIII<(0x9e3+3348-0x16f7)||IlIllIII>=IIlIIIl)return-EINVAL;if(lIllllII<
(0xa5c+4359-0x1b63)||lIllllII>=IIlIIIl)return-EINVAL;if(IlIllIII>lIllllII)return
-EINVAL;mutex_lock(&IIlIIII);for(i=IlIllIII;i<=lIllllII;i++){if(IIIllllI[i]==
NULL){if(lIIIlIlll(lIllI,i)==(0x5e6+7991-0x251d)){lIllI->lIIIll=i;IIIllllI[i]=
lIllI;if(lIllI->ops.IIlIlIll)lIllI->ops.IIlIlIll(lIllI->context);break;}}}
mutex_unlock(&IIlIIII);if(i>lIllllII)return-EOVERFLOW;return(0xda3+5716-0x23f7);
}dev_t lllIllIlI(struct IllllI*lIllI){dev_t IlIlI=MKDEV((0x13b1+4658-0x25e3),
(0x396+741-0x67b));mutex_lock(&IIlIIII);if(lIllI->lIIIll>=(0x532+5083-0x190d)&&
lIllI->lIIIll<IIlIIIl){IlIlI=MKDEV(MAJOR(IlIlll),MINOR(IlIlll)+lIllI->lIIIll);}
mutex_unlock(&IIlIIII);return IlIlI;}int IlIIIIIl(struct IllllI*lIllI){int 
lIIIll;mutex_lock(&IIlIIII);lIIIll=lIllI->lIIIll;mutex_unlock(&IIlIIII);return 
lIIIll;}void llIlIIIl(struct IllllI*lIllI){mutex_lock(&IIlIIII);if(lIllI->lIIIll
>=(0x11ad+3599-0x1fbc)&&lIllI->lIIIll<IIlIIIl&&IIIllllI[lIllI->lIIIll]==lIllI){
IIIllllI[lIllI->lIIIll]=NULL;IlllIIIII(lIllI,lIllI->lIIIll);}lIllI->lIIIll=-
(0x1167+1834-0x1890);mutex_unlock(&IIlIIII);if(lIllI->ops.IIIIlIll)lIllI->ops.
IIIIlIll(lIllI->context);}void lIllllIl(struct IllllI*lIllI){
#if KERNEL_LT_EQ((0x1a3c+754-0x1d2c),(0xc54+1499-0x1229),(0x319+6618-0x1ce4))
kobject_hotplug(&lIllI->dev->kobj,KOBJ_ONLINE);
#else
kobject_uevent(&lIllI->dev->kobj,KOBJ_ONLINE);
#endif
}void lIIllIll(struct IllllI*lIllI){
#if KERNEL_LT_EQ((0x49c+5464-0x19f2),(0x174+3143-0xdb5),(0x86d+1881-0xfb7))
kobject_hotplug(&lIllI->dev->kobj,KOBJ_OFFLINE);
#else
kobject_uevent(&lIllI->dev->kobj,KOBJ_OFFLINE);
#endif
}
ssize_t lllllIIIl(struct file*lIIIlI,char __user*lIIlIIIll,size_t IIlII,loff_t*
llIllIlll){struct IllllI*lIllI=lIIIlI->private_data;if(lIllI){if(lIllI->ops.read
)return lIllI->ops.read(lIllI->context,lIIlIIIll,IIlII);else return
(0x102c+81-0x107d);}return-ENODEV;}ssize_t llIIIIIII(struct file*lIIIlI,const 
char __user*lIIlIIIll,size_t IIlII,loff_t*llIllIlll){struct IllllI*lIllI=lIIIlI
->private_data;if(lIllI){if(lIllI->ops.write)return lIllI->ops.write(lIllI->
context,lIIlIIIll,IIlII);else return(0x13dc+1352-0x1924);}return-ENODEV;}
unsigned int IlllllIIl(struct file*lIIIlI,poll_table*lllIll){struct IllllI*lIllI
=lIIIlI->private_data;if(lIllI){if(lIllI->ops.poll)return lIllI->ops.poll(lIllI
->context,lIIIlI,lllIll);else return(0x859+2837-0x136e);}return-ENODEV;}long 
IlIIIlIll(struct file*lIIIlI,unsigned int llIIII,unsigned long llIIlI){struct 
IllllI*lIllI=lIIIlI->private_data;if(lIllI){if(lIllI->ops.unlocked_ioctl)return 
lIllI->ops.unlocked_ioctl(lIllI->context,llIIII,llIIlI);else return
(0x146c+408-0x1604);}return-ENODEV;}
#ifdef CONFIG_COMPAT
long IlIlIIllI(struct file*lIIIlI,unsigned int llIIII,unsigned long llIIlI){
struct IllllI*lIllI=lIIIlI->private_data;if(lIllI){if(lIllI->ops.compat_ioctl)
return lIllI->ops.compat_ioctl(lIllI->context,llIIII,llIIlI);else return
(0x1a4+5600-0x1784);}return-ENODEV;}
#endif
int llllllllI(struct file*lIIIlI,struct vm_area_struct*IlIllll){struct IllllI*
lIllI=lIIIlI->private_data;if(lIllI){if(lIllI->ops.mmap)return lIllI->ops.mmap(
lIllI->context,IlIllll);else return-EINVAL;}return-ENODEV;}int IIlIIIIII(struct 
inode*inode,struct file*lIIIlI){int IlIlI=-ENODEV;u32 m=iminor(inode);struct 
IllllI*lIllI;mutex_lock(&IIlIIII);lIllI=IIIllllI[m];if(lIllI&&lIllI->ops.
IIlIlIll)lIllI->ops.IIlIlIll(lIllI->context);mutex_unlock(&IIlIIII);if(lIllI){
lIIIlI->private_data=lIllI;





mutex_lock(&lIllI->mutex);if(lIllI->ops.open)IlIlI=lIllI->ops.open(lIllI->
context,++lIllI->IlIllI);else IlIlI=(0x13c8+378-0x1542);mutex_unlock(&lIllI->
mutex);}return IlIlI;}int llIlllllI(struct inode*inode,struct file*lIIIlI){int 
IlIlI=-ENODEV;struct IllllI*lIllI=lIIIlI->private_data;if(lIllI){





mutex_lock(&lIllI->mutex);if(lIllI->ops.release)IlIlI=lIllI->ops.release(lIllI->
context,--lIllI->IlIllI);else IlIlI=(0x9e4+6549-0x2379);mutex_unlock(&lIllI->
mutex);if(lIllI->ops.IIIIlIll)lIllI->ops.IIIIlIll(lIllI->context);}return-ENODEV
;}
