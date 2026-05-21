#include <stdio.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
#include "../../drivers/our_driver/our_driver.h"

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

int main(void)
{
	printf("Hello World! %s\n", CONFIG_BOARD_TARGET);
static const struct device *dev = DEVICE_DT_GET(DT_NODELABEL(our_driver0));
	

	if (!device_is_ready(dev)) {
		LOG_ERR("Device not ready");
		return 0;;
	}
	volatile int ret;
	struct sensor_value val;

	our_driver_set_parameter(dev, 42);

	while(1)
	{
		k_sleep(K_SECONDS(1));
	}

	return 0;
}
