/* 代码清单 6.12  globalmem 设备驱动的读函数 */
static ssize_t globalmem_read(struct file *filp, char __user *buf, size_t count, loff_t *ppos)
{
    unsigned long p = *ppos;
    int ret  = 0;

    /* 分析和获取有效的读长度 */
    if (p >= GLOBALMEM_SIZE) // 要读的偏移位置越界
    {
        return count ? - ENXIO: 0;
    }
    if(count > GLOBALMEM_SIZE - p) // 要读的字节数太大
    {
        count = GLOBALMEM_SIZE - p;
    }

    /* 内核空间 -> 用户空间*/
    if(copy_to_user(buf, (void*)(dev.mem + p), count))
    {
        ret =EFAULT;
    }
    else
    {
        *ppos += count;
        ret = count;

        printk(KERN_INFO "read %d bytes(s) from %d \n", count, p);
    }
    
    return ret;

};
