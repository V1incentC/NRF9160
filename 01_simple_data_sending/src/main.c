/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <modem/modem_info.h>
#include <modem/pdn.h>
#include "shared_data.h"
#include "app_config.h"
#include "http_client.h"
#include "sensor_thread.h"
#ifdef CONFIG_BOARD_THINGY91_NRF9160NS
#include "thingy91.h"
#endif	

#define PDN_IPV6_WAIT_MS 1000
K_SEM_DEFINE(pdn_ipv6_up_sem, 0, 1);

void print_modem_info(void) {
    char sbuf[128];
    modem_info_string_get(MODEM_INFO_RSRP, sbuf, sizeof(sbuf));
    printk("Signal strength: %s\n", sbuf);

    modem_info_string_get(MODEM_INFO_BATTERY, sbuf, sizeof(sbuf));
    printk("Battery voltage: %s\n", sbuf);

    modem_info_string_get(MODEM_INFO_FW_VERSION, sbuf, sizeof(sbuf));
    printk("Modem firmware version: %s\n", sbuf);

    modem_info_string_get(MODEM_INFO_IMSI, sbuf, sizeof(sbuf));
    printk("Modem IMSI: %s\n", sbuf);
}

void pdn_event_handler(uint8_t cid, enum pdn_event event, int reason)
{
	struct shared_data *sd = shared_data_get();
	switch (event)
	{
	case PDN_EVENT_CNEC_ESM:
		printk("PDP context %d error, %s\n", cid, pdn_esm_strerror(reason));
		break;
	case PDN_EVENT_ACTIVATED:
		printk("PDP context %d activated\n", cid);
		break;
	case PDN_EVENT_DEACTIVATED:
		printk("PDP context %d deactivated\n", cid);
		break;
	case PDN_EVENT_NETWORK_DETACH:
		printk("PDP context %d network detached\n", cid);
		break;
#if !IS_ENABLED(CONFIG_PDN_DEFAULT_FAM_IPV4)
	case PDN_EVENT_IPV6_UP:
		printk("PDP context %d IPv6 up\n", cid);
		k_sem_give(&pdn_ipv6_up_sem);
		break;
	case PDN_EVENT_IPV6_DOWN:
		printk("PDP context %d IPv6 down\n", cid);
		break;
#endif
	default:
		printk("PDP context %d, unknown event %d\n", cid, event);
		break;
	}
}
void wait_for_ipv6(void) {
#if !IS_ENABLED(CONFIG_PDN_DEFAULT_FAM_IPV4)
    // Get the shared_data structure using shared_data_get()
    struct shared_data *sd = shared_data_get();

    printk("Waiting for IPv6...\n");
    int err = k_sem_take(&pdn_ipv6_up_sem, K_MSEC(PDN_IPV6_WAIT_MS));
    if (err) {
        printk("IPv6 not available\n");
    }
#endif
}


int main(void)
{
	int err;
    char imei[IMEI_BUF_SIZE];

    printk("HTTPS client sample started\n\r");
	shared_data_init();
	#ifdef CONFIG_BOARD_THINGY91_NRF9160NS
	thingy91_sensors_init();
	#endif
	// Initialize modem library
    err = nrf_modem_lib_init();
    if (err)
    {
        printk("Modem library initialization failed, error: %d\n", err);
        return 0;
    }

	// Initialize modem info
    err = modem_info_init();
    if (err)
    {
        printk("Failed to initialize modem info: %d", err);
        return 0;
    }
	/* Setup a callback for the default PDP context (zero).
	 * Do this before switching to function mode 1 (CFUN=1)
	 * to receive the first activation event.
	 */
    err = pdn_default_ctx_cb_reg(pdn_event_handler);
    if (err)
    {
        printk("pdn_default_ctx_cb_reg() failed, err %d\n", err);
        return 0;
    }

	printk("Waiting for network.. ");
	err = lte_lc_init_and_connect();
	if (err)
	{
		printk("Failed to connect to the LTE network, err %d\n", err);
		return 0;
	}
	printk("OK\n");
	// Print modem information
    print_modem_info();
	// Get IMEI
    err = modem_info_string_get(MODEM_INFO_IMEI, imei, sizeof(imei));
    if (err < 0) {
        printk("Failed to get IMEI, error: %d\n", err);
        return err;
    }
	fetch_and_parse_json_response(imei);
	struct shared_data *sd = shared_data_get();
	printk("Received data: %s\n", sd->response_buf);
	sensor_thread_start();
	
	return 0;
}
