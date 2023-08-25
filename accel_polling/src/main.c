/*
 * Copyright (c) 2022 TOKITA Hiroshi <tokita.hiroshi@fujitsu.com
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <zephyr/zephyr.h>
#include <stdio.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>

K_SEM_DEFINE(sem, 0, 1);

static void trigger_handler(const struct device *dev,
			    const struct sensor_trigger *trig)
{
	static int trigger_count = 0;
	switch (trig->type) {
	case SENSOR_TRIG_DATA_READY:
		if (sensor_sample_fetch(dev) < 0) {
			printf("Sample fetch error\n");
			return;
		}
		k_sem_give(&sem);
		break;
	case SENSOR_TRIG_THRESHOLD:
		printf("Threshold trigger\n");
		break;
	case SENSOR_TRIG_MOTION:
		printf("Motion trigger count: %d\n", ++trigger_count);
			//Check on which channel the trigger is set
			switch (trig->chan)
			{
			case SENSOR_CHAN_ACCEL_X:
				/* code */
				printf("Motion trigger on X\n");
				break;
			case SENSOR_CHAN_ACCEL_Y:
				/* code */
				printf("Motion trigger on Y\n");
				break;
			case SENSOR_CHAN_ACCEL_Z:
				/* code */
				printf("Motion trigger on Z\n");
				break;
			default:
				printf("Unknown channel: %d\n", trig->chan);
				break;
			}
		break;
	default:
		printf("Unknown trigger: %d\n", trig->type);
		//k_sem_give(&sem);
	}
}

int main(void)
{
	struct sensor_value accel[3];
	k_sleep(K_MSEC(2000));
	printk("Hello World! %s\n", CONFIG_BOARD);
	const struct device *dev = DEVICE_DT_GET_ONE(adi_adxl362);
	if (dev == NULL) {
		printf("Device get binding device\n");
		return;
	}

	struct sensor_trigger trig_x = { .chan = SENSOR_CHAN_ACCEL_X };
	struct sensor_trigger trig_y = { .chan = SENSOR_CHAN_ACCEL_Y };
	struct sensor_trigger trig_z = { .chan = SENSOR_CHAN_ACCEL_Z };
	struct sensor_trigger trig_drdy = { .chan = SENSOR_CHAN_ACCEL_X };

	struct sensor_value sensorVal = {
		.val1 = 12, // before decimal - 1G = 1000
		.val2 = 0 // after decimal
	};
	int ret = sensor_attr_set(dev, SENSOR_CHAN_ACCEL_XYZ, SENSOR_ATTR_SAMPLING_FREQUENCY, &sensorVal);
	printf("sensor_attr_set: %d\n", ret);

	trig_drdy.type = SENSOR_TRIG_DATA_READY;
	if (sensor_trigger_set(dev, &trig_drdy, trigger_handler)) {
		printf("Trigger set error\n");
	}

	trig_x.type = SENSOR_TRIG_MOTION;

	if (sensor_trigger_set(dev, &trig_x, trigger_handler)) {
		printf("Trigger set error\n");
		return;
	}
	


	while (true) {

		k_sem_take(&sem, K_FOREVER);

		if (sensor_channel_get(dev, SENSOR_CHAN_ACCEL_X, &accel[0]) < 0) {
			printf("Channel get error\n");
			return;
		}

		if (sensor_channel_get(dev, SENSOR_CHAN_ACCEL_Y, &accel[1]) < 0) {
			printf("Channel get error\n");
			return;
		}

		if (sensor_channel_get(dev, SENSOR_CHAN_ACCEL_Z, &accel[2]) < 0) {
			printf("Channel get error\n");
			return;
		}

		printf("x: %.1f, y: %.1f, z: %.1f (m/s^2)\n",
		       sensor_value_to_double(&accel[0]),
		       sensor_value_to_double(&accel[1]),
		       sensor_value_to_double(&accel[2]));
	}
}

