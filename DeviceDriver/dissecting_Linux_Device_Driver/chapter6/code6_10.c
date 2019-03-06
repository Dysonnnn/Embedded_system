/* 代码清单 6.10  初始化并添加 cdev 结构体  */
static void globalmem_setup_cdev()
{
    int err, devno = MKDEV(globalmem_major, 0);

    cdev_init(&dev.cdev, &globalmem_fops);
    dev.cdev.owner = THIS_MODULE;
    dev.cdev.ops = &globalmem_fops;
    err = cdev_add(&dev.cdev, devno, 1);
    if(err)
    {
        printk(KERN_NOTICE "Error %d adding globalmem", err);
    }
}

