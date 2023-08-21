// sensor_thread.c
#include "sensor_thread.h"
#include "http_client.h"
#include "shared_data.h"
#include <stdio.h>
#include <modem/modem_info.h>
#ifdef CONFIG_BOARD_THINGY91_NRF9160NS
#include "thingy91.h"
#include <zephyr/drivers/sensor.h>
#endif

#define STACKSIZE 4*1024
#define THREAD_PRIORITY 5
#define SLEEP_TIME K_MINUTES(10)

K_THREAD_STACK_DEFINE(sensor_thread_stack_area, STACKSIZE);
struct k_thread sensor_thread_data;


void sensor_thread_send_func(void *arg1, void *arg2, void *arg3)
{
    
    ARG_UNUSED(arg1);
    ARG_UNUSED(arg2);
    ARG_UNUSED(arg3);

    char url[HTTP_URL_BUF_SIZE];  // Define the url buffer here
    char sbuf[128];
    int16_t signal_strength;
    uint16_t battery_voltage;

    struct shared_data *sd = shared_data_get();
    
    // Fetch the semaphores from the shared data
    struct k_sem *api_key_sem = &sd->api_key_sem;
    struct k_sem *http_response_sem = &sd->http_response_sem;
    struct k_mutex  *url_mutex = &sd-> url_mutex;

	k_sem_take(api_key_sem, K_FOREVER);
	printk("Hello from sensor thread\n");

	while (1) {
        /* Wait for api_key to be received */
        
		printk("Sensor thread: semaphore taken\n");
        #ifdef CONFIG_BOARD_THINGY91_NRF9160NS
        // Get Sensor Data
        struct sensor_value temp, press, humidity, gas_res;
        get_sensor_data(&temp, &press, &humidity, &gas_res);
        
        modem_info_string_get(MODEM_INFO_RSRP, sbuf, sizeof(sbuf));
        printk("Signal strength: %s\n", sbuf);
        sscanf(sbuf, "%d", &signal_strength);

        modem_info_string_get(MODEM_INFO_BATTERY, sbuf, sizeof(sbuf));
        printk("Battery voltage: %s\n", sbuf);
        sscanf(sbuf, "%hu", &battery_voltage);
        /* Format URL with query parameters */
		k_mutex_lock(url_mutex, K_FOREVER);
		snprintf(url, sizeof(url),
                 "/update.json?api_key=%s&field1=%hu&field2=%d&field3=%d.%06d&field4=%d.%06d&field5=%d.%06d",
                 sd->api_key,
                 battery_voltage,
                 signal_strength,
                 temp.val1, temp.val2,
                 press.val1*10, press.val2*10,
                 humidity.val1, humidity.val2);
		
        /* Clear the response buffer */
        memset(sd->response_buf, 0, sizeof(sd->response_buf));
        k_mutex_unlock(url_mutex);

#else
        // Generate random data for fields when Thingy:91 is not defined
        int temp_val = k_cycle_get_32() % 100;
        int press_val = k_cycle_get_32() % 1000;
        int humidity_val = k_cycle_get_32() % 50;
        int gas_res_val = k_cycle_get_32() % 500;
        signal_strength = -80;  // Default signal strength
        battery_voltage = 3700; // Default battery voltage
        k_mutex_lock(url_mutex, K_FOREVER);
		snprintf(url, sizeof(url),
                 "/update.json?api_key=%s&field1=%hu&field2=%d&field3=%d&field4=%d&field5=%d",
                 sd->api_key,
                 battery_voltage,
                 signal_strength,
                 temp_val,
                 press_val,
                 humidity_val);
		
        /* Clear the response buffer */
        memset(sd->response_buf, 0, sizeof(sd->response_buf));
        k_mutex_unlock(url_mutex);
#endif

		
        
		/* Send GET request and get response */
		int err = http_client_send_get_request(url);
		if (err < 0) {
			printk("Failed to get response from server, error:%d", err);
			//return;
		}
        
		/* Wait for the response data */
		k_sem_take(http_response_sem, K_FOREVER);
        k_mutex_lock(url_mutex, K_FOREVER);
		/* Print the response data */
		printk("Received response (%d bytes):\n%s\n", sd->response_len, sd->response_buf);
        k_mutex_unlock(url_mutex);

        k_sleep(SLEEP_TIME);
        
    }
}

void sensor_thread_start(void) {
    // ... Create and start sensor thread ...
    k_thread_create(&sensor_thread_data, sensor_thread_stack_area,
                    STACKSIZE,
                    sensor_thread_send_func, NULL, NULL, NULL,
                    THREAD_PRIORITY, 0, K_NO_WAIT);
}