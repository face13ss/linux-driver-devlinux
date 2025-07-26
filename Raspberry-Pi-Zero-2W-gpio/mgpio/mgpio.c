#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/io.h>
#include "mgpio.h"

#define DRIVER_AUTHOR "dungla anhdungxd21@mail.com"
#define DRIVER_DESC "Hello world kernel module"
#define DRIVER_VERS "1.0"

static void __iomem *gpio_base;

static int __init gpio_driver_init(void)
{
    uint32_t reg;

    // Map GPIO registers into kernel virtual address space
    gpio_base = ioremap(BCM2836_GPIO_BASE_ADDR, 0x28);
    if (!gpio_base){
        pr_err("Failed to ioremap GPIO\n");
        return -ENOMEM;
    }

    // Configure GPIO27 as output
    reg = ioread32(gpio_base + GPIO_FSEL_OFFSET + (GPIO_NUMBER_27 / 10) * 4);
    reg &= ~(7 << ((GPIO_NUMBER_27 % 10 ) * 3)); // Clear current function
    reg |= (1 << ((GPIO_NUMBER_27 % 10 ) * 3)); // Set as ouput
    iowrite32(reg, gpio_base + GPIO_FSEL_OFFSET + (GPIO_NUMBER_27 / 10) * 4);

    // Set GPIO27 to HIGH
    iowrite32(1 << GPIO_NUMBER_27, gpio_base + GPIO_SET_0_OFFSET);
    pr_info("GPIO27 set to high\n");

    return 0;
}

static void __exit gpio_driver_exit(void)
{
    iowrite32(1 << GPIO_NUMBER_27, gpio_base + GPIO_CLR_0_OFFSET);
    pr_info("GPIO27 set to LOW\n");

    if(gpio_base)
        iounmap(gpio_base);
}

module_init(gpio_driver_init);
module_exit(gpio_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION(DRIVER_VERS);
