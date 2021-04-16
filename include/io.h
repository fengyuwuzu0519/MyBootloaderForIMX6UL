#ifndef   __IO_H__
#define   __IO_H__

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef unsigned int uint;
typedef unsigned short      ushort;

#define readl(a)          (*(volatile unsigned int *)(a))
#define writel(v,a)        (*(volatile unsigned int *)(a) = (v))

#endif
