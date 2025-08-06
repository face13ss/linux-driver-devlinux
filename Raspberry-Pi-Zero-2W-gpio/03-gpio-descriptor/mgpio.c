#include <linux/module.h>           /* Defines function such as module_int/module_exit */
#include <linux/gpio.h>             /* Defines function such as gpio_request/gpio_free */
#include <linux/platform_device.h>  /* For platform devices*/
#include <linux/gpio/consumer.h>    /* For GPIO Descriptor */
#include <linux/of.h>               /* For DT */

#define LOW 0
#define HIGH 1

struct gpio_desc *gpio_27;

static const struct of_device_id gpiod_dt_ids[] = {
    { .compatible = "gpio-descriptor-based", },
    { /* sentinel */ }
};

static int mgpio_driver_probe(struct platform_device *pdev)
{
    struct device *dev = &pdev->dev;

    // Set GPIO27 to HIGH
    gpio_27 = gpiod_get(dev, "led27", GPIOD_OUT_LOW);
    if (IS_ERR(gpio_27)) {
        dev_err(dev, "Failed to get led27-gpios\n");
        return PTR_ERR(gpio_27);
    }
    gpiod_set_value(gpio_27, HIGH);

    pr_info("%s - %d\n", __func__, __LINE__);

    return 0;
}

static void mgpio_driver_remove(struct platform_device *pdev)
{
    if (!gpio_27)
        return;
    // Set GPIO27 to LOW before exiting
    gpiod_direction_output(gpio_27, LOW);  // Ép pin về output low
    gpiod_set_value(gpio_27, LOW);
    pr_info("%s - %d\n", __func__, __LINE__);

    gpiod_put(gpio_27);
}

static struct platform_driver mgpio = {
    .probe = mgpio_driver_probe,
    .remove = mgpio_driver_remove,
    .driver = {
        .name = "gpio-discriptor-based",
        .of_match_table = of_match_ptr(gpiod_dt_ids),
        .owner = THIS_MODULE
    }
};

module_platform_driver(mgpio);
MODULE_AUTHOR("dungla anhdungxd21@mail.com");
MODULE_LICENSE("GPL");