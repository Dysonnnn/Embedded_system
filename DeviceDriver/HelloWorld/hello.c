#include <linux/init.h>
#include <linux/module.h>

static int hello_init(void)
//int init_module(void) 
{
    printk("<1>Hello  <1> World \n");
    printk("<7>Hello  <7> World \n");
    printk(KERN_ALERT "Hello ALERT World \n");
    printk(KERN_DEBUG "Hello debug World \n");
    printk(KERN_INFO "Hello World enter \n");
    return 0;
}

static void hello_exit(void)
//void cleanup_module(void)
{
    printk(KERN_ALERT "Goodbye cruel world \n");
    //printk("<1>Goodbye cruel world \n");
    printk(KERN_INFO "Hello World exit \n");
}

module_init(hello_init);
module_exit(hello_exit);


MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("A simple Hello World Module");
MODULE_ALIAS("a simplest module");
