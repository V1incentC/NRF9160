#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <stdio.h>
#include "thingy91.h"
#ifdef CONFIG_BOARD_THINGY91_NRF9160NS
const struct device *const dev = DEVICE_DT_GET_ONE(bosch_bme680);

void get_sensor_data(struct sensor_value *temp, struct sensor_value *press, struct sensor_value *humidity, struct sensor_value *gas_res)
{
    if (!device_is_ready(dev)) {
        printk("sensor: device not ready.\n");
        return;
    }

    sensor_sample_fetch(dev);
    sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, temp);
    sensor_channel_get(dev, SENSOR_CHAN_PRESS, press);
    sensor_channel_get(dev, SENSOR_CHAN_HUMIDITY, humidity);
    sensor_channel_get(dev, SENSOR_CHAN_GAS_RES, gas_res);
}

int thingy91_sensors_init()
{
    if (!device_is_ready(dev)) {
		printk("sensor: device not ready.\n");
		return 0;
	}
    printf("Device %p name is %s\n", dev, dev->name);
    return 1;
}
#endif