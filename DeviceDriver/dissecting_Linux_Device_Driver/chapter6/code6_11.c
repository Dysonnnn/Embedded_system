/* 代码清单 6.11  globalmem 设备驱动文件操作结构体  */
static const struct file_operations globalmem_fops = 
{
    .ower = THIS_MODULE,
    .llseek = globalmem_llseek,
    .read = globalmem_read,
    .write = globalmem_write,
    .ioctl = globalmem_ioctl,
}
