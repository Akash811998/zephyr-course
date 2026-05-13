#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>


#define DT_DRV_COMPAT our_driver

typedef struct our_driver_struct {
    uint32_t my_param;
} our_driver_struct_t;

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

void our_driver_set_parameter(const struct device *dev, uint32_t param)
{
    our_driver_struct_t *drv_data = (our_driver_struct_t *)dev->data;

    LOG_INF("Calling the custom extensin API for our Driver");
    if (NULL != drv_data)
    {
        drv_data->my_param = param;
        LOG_INF("Setting my_param to %u", drv_data->my_param);
    }
    else
    {
        LOG_ERR("Device data is NULL");
    }
}

// Define the device instance for our driver
#define OUR_DRIVER_INST(inst) \
    static struct our_driver_struct my_led_struct_##inst;   \
    DEVICE_DT_INST_DEFINE(inst, init, NULL, &my_led_struct_##inst, NULL, POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT, &our_driver_api);

DT_INST_FOREACH_STATUS_OKAY(OUR_DRIVER_INST)