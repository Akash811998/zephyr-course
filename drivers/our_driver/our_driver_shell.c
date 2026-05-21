#include <zephyr/shell/shell.h>
#include <zephyr/drivers/sensor.h>

int ret=0;

static int cmd_my_sensor_read_handler(const struct shell *shell, size_t argc, char **argv)
{

    const struct device *dev = shell_device_get_binding("our_driver0");
    if(!dev) {
        shell_error(shell, "Could not find device %s", "our_driver0");
        return -EFAULT;
    }
        
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);

    struct sensor_value val;
    ret = sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &val);
    if (ret) {
        shell_error(shell, "Failed to read sensor value");
        return ret;
    }

    shell_info(shell, "Sensor value: %d.%06d", val.val1, val.val2);
    return 0;

}

static int cmd_my_sensor_fetch_handler(const struct shell *shell, size_t argc, char **argv)
{
        
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);

    const struct device *dev = shell_device_get_binding("our_driver0");
    if(!dev) {
        shell_error(shell, "Could not find device %s", "our_driver0");
        return -EFAULT;
    }
    ret=sensor_sample_fetch(dev);
    if (ret) {
        shell_error(shell, "Failed to fetch sensor value");
        return ret;
    }
    return 0;
}

static int cmd_my_sensor_info_handler(const struct shell *shell, size_t argc, char **argv)
{
        
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);

    const struct device *dev = shell_device_get_binding("our_driver0");
    if(!dev) {
        shell_error(shell, "Could not find device %s", "our_driver0");
        return -EFAULT;
    }
    shell_info(shell, "Device name: %s", dev->name);
    shell_info(shell, "Device ready: %s", device_is_ready(dev) ? "Yes" : "No");
    return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(shell_driver,
    //SHELL_CMD(my_sensor_attr_get, NULL, "Get my sensor attribute", cmd_my_sensor_get_handler),
    SHELL_CMD(read, NULL, "read my sensor attribute", cmd_my_sensor_read_handler),
    SHELL_CMD(fetch, NULL, "CAll the fetch function ", cmd_my_sensor_fetch_handler),
    SHELL_CMD(info, NULL, "Get the device name and ready state", cmd_my_sensor_info_handler),
    SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(sensor, &shell_driver, "Commands for our driver", NULL);