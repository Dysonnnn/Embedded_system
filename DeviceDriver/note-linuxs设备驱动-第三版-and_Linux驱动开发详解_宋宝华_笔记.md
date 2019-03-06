

```
#include <linux/init.h> #include <linux/module.h> MODULE_LICENSE("Dual BSD/GPL"); 
 
static int hello_init(void) {         printk(KERN_ALERT "Hello, world\n");         return 0; } static void hello_exit(void) {         printk(KERN_ALERT "Goodbye, cruel world\n"); } 
 
module_init(hello_init); module_exit(hello_exit);

```


大部分相 关的头文件位于 include/linux 和 include/asm, 





<linux/init.h>，<linux/module.h>头文件不存在等问题的解决方法
https://www.cnblogs.com/nerohwang/p/3621316.html




**Makefile 开头一定要大写，不然识别不到**

你可以用 insmod 和 rmmod 工具来测试这个模块. 注意只有超级用户可以加载和卸载模块.  
% 

```
% make  
make[1]: Entering directory `/usr/src/linux-2.6.10'  
CC [M] /home/ldd3/src/misc-modules/hello.o  
Building modules, stage 2.  
MODPOST  CC /home/ldd3/src/misc-modules/hello.mod.o  
LD [M] /home/ldd3/src/misc-modules/hello.ko 
make[1]: Leaving directory `/usr/src/linux-2.6.10' 

% su 
root# insmod ./hello.ko 

Hello, world 

root# rmmod 

hello Goodbye cruel world 

```


lsmod // 显示内核模块

dmesg -c  // 显示内核打印的信息



## 详解 第四章
宋宝华的csdn博客：  讲了内核部分的：
https://blog.csdn.net/21cnbao/article/details/36395963

lsmod命令实际上读取并分析“/proc/modules”文件，与上述lsmod命令结果对应的“/proc/modules”文件如下：
$ cat /proc/modules

使用modinfo <模块名>命令可以获得模块的信息，包括模块作者、模块的说明、模块所支持的参数以及vermagic：
└─[$] <> modinfo hello.ko

filename:       /home/sjj/Desktop/code/driver_dir/hello.ko
alias:          a simplest module
description:    A simple Hello World Module
license:        GPL v2
srcversion:     872AFEA93C2C9BCE2FA3657
depends:
retpoline:      Y
name:           hello
vermagic:       4.15.0-45-generic SMP mod_unload



ubuntu是修改了内核的，把这些都放到log里面了,在图形界面的时候只能dmesg -c 看。

---

【Linux内核】Ubuntu下printk函数无法在终端显示
https://blog.csdn.net/wr132/article/details/73825888

printk信息的输出去向

这是在内核的命令行参数console=ttyXXX里指定死了，比如console=tty1表示printk的信息输出到终端1。如果是这种情况，你需要使用Ctrl+Alt+（F1-F6）来切换终端。

Ctrl+Alt+F1  这个终端执行命令 insmod  rmmod 可以看到 输出信息


日志输出级别过低

用printk，内核会根据日志级别，可能把消息打印到当前控制台上，这个控制台通常是一个字符模式的终端、一个串口打印机或是一个并口打印机。这些消息正常输出的前提是──日志输出级别高于console_loglevel（在内核中数字越小优先级越高）。

日志级别一共有8个级别，printk的日志级别定义如下（在include/linux/kernel.h中）：

0 #define KERN_EMERG 
1 #define KERN_ALERT 
2 #define KERN_CRIT 
3 #define KERN_ERR 
4 #define KERN_WARNING 
5 #define KERN_NOTICE 
6 #define KERN_INFO 
7 #define KERN_DEBUG


---

查看当前控制台的打印级别
cat /proc/sys/kernel/printk 4 4 1 7 

目前只能看到
0 #define KERN_EMERG 
1 #define KERN_ALERT 
2 #define KERN_CRIT 
3 #define KERN_ERR 

这四种的消息




4.6 导出符号

代码清单 4.5 给出了一 个导出整数加、减运算函数符号的内核模块的例子
（这些导出符号没有实际意义，只 是为了演示） 

```
#include <linux/init.h>
#include <linux/module.h>
MODULE_LICENSE("Dual BSD/GPL");

int add_integar(int a, int b)
{
	return  a + b;
}

int sub_integar(int a, int b)
{
	return a - b;
}
EXPORT_SYMBOL(add_integar)；
EXPORT_SYMBOL(sub_integar);

```


4.7 模块声明与描述 
在Linux 内核模块中，我们可以用 MODULE_AUTHOR、MODULE_DESCRIPTION、 MODULE_ VERSION、MODULE_DEVICE_TABLE、MODULE_ALIAS 
分别声明模块的 作者、描述、版本、设备表和别名

```
MODULE_AUTHOR(author); 
MODULE_DESCRIPTION(description); 
MODULE_VERSION(version_string);
MODULE_DEVICE_TABLE(table_info); 
MODULE_ALIAS(alternate_name); 
```

对于 USB、PCI 等设备驱动，通常会创建一个 MODULE_DEVICE_TABLE，如代 码清单 4.6 所示。 

代码清单 4.6  驱动所支持的设备列表 
```
1 /* 对应此驱动的设备表 */  
2 static struct usb_device_id skel_table [] = {  
3 { USB_DEVICE(USB_SKEL_VENDOR_ID,  
4    USB_SKEL_PRODUCT_ID) },  
5   { } /* 表结束 */  6 };  
7  
8 MODULE_DEVICE_TABLE (usb, skel_table); 
```
此时，并不需要读者理解 MODULE_DEVICE_TABLE 的作用，后续相关章节会 有详细介绍




# 第 5 章  Linux 文件系统与设备文件系统 

## 5.1  文件操作
### 5.1.1  文件操作的相关系统调用 
1．创建 
```
int creat(const char *filename, mode_t mode); 
```
2. 打开 
```
	int open(const char *pathname, int flags);  
	int open(const char *pathname, int flags, mode_t mode);  
```
open()函数有两个形式，其中 pathname 是我们要打开的文件名（包含路径名称， 默认时认为在当前路径下面）， 
flags  可以是如表 5.1 所示的一个值或者是几个值的组合



文件打开标志 
标    志 |  含    义 
O_RDONLY 以只读的方式打开文件 
O_WRONLY 以只写的方式打开文件 
O_RDWR 以读写的方式打开文件 
O_APPEND 以追加的方式打开文件 
O_CREAT 创建一个文件 
O_EXEC 
如果使用了 O_CREAT 而且文件已经存在，就会 发生一个错误 
O_NOBLOCK 以非阻塞的方式打开一个文件 
O_TRUNC 如果文件已经存在，则删除文件的内容 


3．读写 
在文件打开以后，我们才可对文件进行读写，Linux 系统中提供文件读写的系统
调用是 read、write 函数，如下所示： 
```
int read(int fd, const void *buf, size_t length); 
int write(int fd, const void *buf, size_t length); 
```


4．定位 
对于随机文件，我们可以随机地指定位置读写，使用如下函数进行定位： 
```int lseek(int fd, offset_t offset, int whence); 
```

lseek()将文件读写指针相对 whence 移动 offset 个字节。操作成功时，返回文件指 针相对于文件头的位置。参数 whence 可以使用如下值。 SEEK_SET：相对文件开头。 SEEK_CUR：相对文件读写指针的当前位置。 SEEK_END：相对文件末尾。 offset 可取负值，例如下述调用可将文件指针相对当前位置向前移动 5 个字节。 lseek(fd, -5, SEEK_CUR); 由于 lseek 函数的返回值为文件指针相对于文件头的位置， 因此下列调用的返回值就 是文件的长度： 
```
lseek(fd, 0, SEEK_END); 
```


5．关闭 
当操作完成以后，就要关闭文件了，只要调用 close 函数就可以了，其中 fd 是要 关闭的文件描述符。 
```
int close(int fd); 
```

### 5.1.2  C库函数的文件操作 C 库函数的文件操作实际上是独立于具体的操作系统平台的，不管是在 DOS、 Windows、Linux 还是在 VxWorks 中都是这些函数。 

- 1．创建和打开 
```
FILE *fopen(const char *path, const char *mode); 
```

fopen()实现打开指定文件 filename，其中的 mode 为打开模式，C 库函数中支持的 打开模式如表 5.3 所示。 


...**未完待续**




# 第 6 章 字符设备驱动 
## 6.1 Linux 字符设备驱动结构
### 6.1.1  cdev 结构体 在 Linux 2.6 内核中使用 cdev 结构体描述字符设备， cdev 结构体的定义如代码 清单 6.1   所示。 

代码清单 6.1  cdev 结构体 
```
1  struct cdev  
2  { 
3   struct kobject kobj; /* 内嵌的 kobject对象 */ 
4   struct module *owner;    /*所属模块*/  
5   struct file_operations *ops;  /*文件操作结构体*/ 
6   struct list_head list; 
7   dev_t dev;           /*设备号*/ 
8   unsigned int count; 
9  };
```


## 6.3 globalmen 设备驱动





