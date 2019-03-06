/* 代码清单 6.9  globalmem 设备驱动模块加载与卸载函数*/
int globalmem_init(void)
{
    int result;
    dev_t devno = MKDEV(globalmem_major, 0);

    /* 申请字符设备驱动区域*/
    if (globalmem_major)
    {
        result = register_chrdev_region(devno, 1, "globalmem");

    }
    else
    /* 动态获得主设备号 */
    {
        result = alloc_chrdev_region(&devno, 0, 1, "globalmem");
        globalmem_major = MAJOR(devno);
    }
    
    if(result < 0)
    {
        return result;
    }

    globalmem_setup_cdev(); /*完成 cdev 的初始化和添加*/
    return 0;
}

/* globalmem 设备驱动模块卸载函数 */
void globalmem_exit(void)
{
    cdev_del(&dev.cdev); /* 删除cdev 结构体*/
    unregister_chrdev_region(MKDEV(globalmem_major, 0), 1); /*注销设备区域*/
}