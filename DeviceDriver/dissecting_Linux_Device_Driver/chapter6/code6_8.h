// globalmem struct and define
#include <linux/types>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <asm/io.h>
#include <asm/system.h>
#include <asm/uaccess.h>

#define GLOBALMEM_SIZE 0x1000 /* 全局内存大小 -- global memery size 4KB* */
#define MEM_CLEAR 0x1 /* 清零全局内存 -- clear global memery*/
#define GLOBALMEM_MAJOR 254 /* 预设的globalmem的主设备号 -- pre set the main driver number of the globalmem*/

static globalmem_major = GLOBALmem_MAJOR;

/* global driver struct -- globalmem设备结构体 */
struct globalmem_dev
{
    struct cdev cdev; /* cdev struct 结构体*/
    unsigned char mem[GLOBALMEM_SIZE]; /* 全局内存 -- global memery*/
};


struct globalmem_dev dev; /* 设备结构体实例*/

