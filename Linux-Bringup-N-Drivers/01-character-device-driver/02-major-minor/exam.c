#include <linux/module.h>   /* Define module_init(), module_exit() */
#include <linux/fs.h>       /* Define alloc_chrdev_region(), register_chrdev_region() */

#define DRIVER_AUTHOR "dungla anhdungxd21@mail.com"
#define DRIVER_DESC "Hello world kernel module"
#define DRIVER_VERS "1.0"

struct m_chdev {
    dev_t dev_num;
} m_dev;

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

    return 0;
}

/* Destructor */
/* Tất cả tài nguyên cấp phát ở init phải được huỷ cấp phát ở exit*/
static void __exit chdev_exit(void)
{
    unregister_chrdev_region(m_dev.dev_num, 1);
    pr_info("DevLinux: goodbye\n");
}

module_init(chdev_init);
module_exit(chdev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION(DRIVER_VERS);