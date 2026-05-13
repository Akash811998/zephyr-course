#include <stdio.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

int main(void)
{
	printf("Hello World! %s\n", CONFIG_BOARD_TARGET);
const struct device *dev = DEVICE_DT_GET(DT_NODELABEL(our_driver0));
	

	if (!device_is_ready(dev)) {
		LOG_ERR("Device not ready");
		return 0;;
	}
	int ret;
	struct sensor_value val;

	while(1)
	{
	
		ret=sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &val);
		k_msleep(2000);
		ret=sensor_sample_fetch(dev);
		k_msleep(2000);

	}

	return 0;
}
