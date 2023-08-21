#ifndef THINGY91_H_
#define THINGY91_H_

#ifdef __cplusplus
extern "C" {
#endif
#include <zephyr/drivers/sensor.h>

#ifdef CONFIG_BOARD_THINGY91_NRF9160NS
void get_sensor_data(struct sensor_value *temp, struct sensor_value *press, struct sensor_value *humidity, struct sensor_value *gas_res);
int thingy91_sensors_init();
#endif

#ifdef __cplusplus
}
#endif

#endif /* THINGY91_H_ */
