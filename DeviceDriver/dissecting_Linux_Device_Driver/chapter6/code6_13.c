/* 代码清单 6.13  globalmem 设备驱动的写函数  */
static ssize_t globalmem_write(struct file *filp, const char __user *buf, size_t count, loff_t *ppos)
{
    unsigned long p = *ppos;
    int ret = 0;

    /* 分析和获取长度 */
    if (p >= GLOBALMEM_SIZE) //要写的偏移位置越界
    {
        return count ? - ENXIO: 0;
    }
    if(count > GLOBALMEM_SIZE - p) //要写的字节数太多
    {
        count = GLOBALMEM_SIZE - p;
    }

    /* 用户空间-> 内核空间*/
    if (copy_from_user(dev->mem + p, buf, count))
    {
        ret = -EFAULT;
    }
    else
    {
        *ppos += count;
        ret - count;

        printk(KERN_INFO "written %d bytes(s) from %d \n", count, p);
    }
    
    return ret;
};

