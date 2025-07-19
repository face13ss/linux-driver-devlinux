#include <linux/module.h>   /* Define module_init(), module_exit() */
#include <linux/fs.h>       /* Define alloc_chrdev_region(), register_chrdev_region() */
#include <linux/device.h>
#include <linux/cdev.h>

#define DRIVER_AUTHOR "dungla anhdungxd21@mail.com"
#define DRIVER_DESC "Hello world kernel module"
#define DRIVER_VERS "1.0"

static int m_open(struct inode *inode, struct file *file);
static int m_release(struct inode *inode, struct file *file);
static ssize_t m_read(struct file *filp, char __user *user_buf, size_t size, loff_t * offset);
static ssize_t m_write(struct file *filp, const char *user_buf, size_t size, loff_t * offset);

struct m_chdev {
    dev_t dev_num;
    // /sys/class/
    struct class *m_class;
    // Đại diện cho character device dưới kernel
    struct cdev m_cdev;
} m_dev;

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .read = m_read,
    .write = m_write,
    .open = m_open,
    .release = m_release,
};

/* Constructor */
static int __init chdev_init(void)
{
    /* 1.0 Dynamic allocating device number (cat /proc/devices) */
    // trong alloc_chrdev_region, 0 là giá trị bắt đầu của minor
    // 1 số lượng minor
    if (alloc_chrdev_region(&m_dev.dev_num, 0, 1, "dev_num") < 0) {
        pr_err("Failed to alloc chrdev region\n");
        return -1;
    }

    // dev_t dev = MKDEV(173, 0);
    // register_chrdev_region(&m_dev.dev_num, 1, "m-cdev")

    pr_info("DevLinux: hello world kernel module!\n");
    pr_info("Major = %d Minor = %d\n", MAJOR(m_dev.dev_num), MINOR(m_dev.dev_num));

    /* 2.0 Creating struct class */
    if ((m_dev.m_class = class_create(THIS_MODULE, "m_class")) == NULL) {
        pr_err("Cannot create the struct class for my device\n");
        goto rm_device_numb;
    }

    /* 3.0 Creating devcie*/
    if ((device_create(m_dev.m_class, NULL, m_dev.dev_num, NULL, "m_device")) == NULL) {
        pr_err("Cannot create my device\n");
        goto rm_class;
    }

    /* 4.0 Creating cdev structure */
    cdev_init(&m_dev.m_cdev, &fops);

    /* 4.1 Adding character devices to the system */
    if (cdev_add(&m_dev.m_cdev, m_dev.dev_num, 1) < 0) {
        pr_err("Cannot add the device to the system\n");
        goto rm_device;
    }

    return 0;


rm_device:
    device_destroy(m_dev.m_class, m_dev.dev_num);
rm_class:
    class_destroy(m_dev.m_class);
rm_device_numb:
    unregister_chrdev_region(m_dev.dev_num, 1);
    return -1;
}

/* Destructor */
/* Tất cả tài nguyên cấp phát ở init phải được huỷ cấp phát ở exit*/
static void __exit chdev_exit(void)
{
    cdev_del(&m_dev.m_cdev);
    device_destroy(m_dev.m_class, m_dev.dev_num);
    class_destroy(m_dev.m_class);
    unregister_chrdev_region(m_dev.dev_num, 1);
    pr_info("DevLinux: goodbye\n");
}

static int m_open(struct inode *inode, struct file *file){
    pr_info("System call open() called ...!!!\n");
    return 0;
}
static int m_release(struct inode *inode, struct file *file){
    pr_info("System call release() called ...!!!\n");
    return 0;
}
static ssize_t m_read(struct file *filp, char __user *user_buf, size_t size, loff_t * offset){
    pr_info("System call read() called ...!!!\n");
    return 0;
}
static ssize_t m_write(struct file *filp, const char *user_buf, size_t size, loff_t * offset){
    pr_info("System call write() called ...!!!\n");
    return size;
}

module_init(chdev_init);
module_exit(chdev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION(DRIVER_VERS);