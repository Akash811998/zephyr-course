#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>

#define DT_DRV_COMPAT our_driver

LOG_MODULE_REGISTER(our_driver, LOG_LEVEL_INF);

#define LED_NODE DT_ALIAS(led0)

static struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);


static int my_sensor_attr_get(const struct device *dev,
				    enum sensor_channel chan,
				    struct sensor_value *val)
{
    LOG_INF("HELLO from channel Get, channel: %d", chan);
    gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);
    LOG_INF("LED OFF");
    return 0;
}

static int my_sensor_attr_fetch(const struct device *dev,
				     enum sensor_channel chan)
{
    LOG_INF("HELLO from channel Fetch, channel: %d", chan);
    gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    LOG_INF("LED ON");
    return 0;   
}

static DEVICE_API(sensor, our_driver_api) = {
    .sample_fetch = my_sensor_attr_fetch,
    .channel_get = my_sensor_attr_get,
    // Define the API functions for our driver here
};

static int init(const struct device *dev) {
     LOG_INF("Hello from our driver init");
     if(!gpio_is_ready_dt(&led)) {
        LOG_ERR("LED device not ready");
        return -ENODEV;
     }
     if(gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE) < 0) {
        LOG_ERR("Failed to configure LED pin");
        return -EIO;
     }
     return 0;
}

// Define the device instance for our driver
#define OUR_DRIVER_INST(inst) \
    DEVICE_DT_INST_DEFINE(inst, init, NULL, NULL, NULL, POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT, &our_driver_api);

DT_INST_FOREACH_STATUS_OKAY(OUR_DRIVER_INST)