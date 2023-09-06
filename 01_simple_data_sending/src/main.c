/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <modem/modem_info.h>
#include <modem/pdn.h>
#include <modem/nrf_modem_lib.h>
#include <modem/lte_lc.h>
#include <stdio.h>
#include <string.h>
#include <zephyr/logging/log.h>
#include "shared_data.h"
#include "app_config.h"
#include "http_client.h"
#include "sensor_thread.h"
#ifdef CONFIG_BOARD_THINGY91_NRF9160NS
#include "thingy91.h"
#endif	

#define PDN_IPV6_WAIT_MS 1000
K_SEM_DEFINE(pdn_ipv6_up_sem, 0, 1);
LOG_MODULE_REGISTER(Cellfund_Project, LOG_LEVEL_INF);
void print_modem_info(void) {
    char sbuf[128];
	uint16_t mcc, mnc;
    modem_info_string_get(MODEM_INFO_RSRP, sbuf, sizeof(sbuf));
    printk("Signal strength: %s\n", sbuf);

    modem_info_string_get(MODEM_INFO_AREA_CODE, sbuf, sizeof(sbuf));
    printk("Area code: %s\n", sbuf);

	modem_info_string_get(MODEM_INFO_CELLID, sbuf, sizeof(sbuf));
	printk("Cell ID: %s\n", sbuf);

	modem_info_string_get(MODEM_INFO_DATE_TIME, sbuf, sizeof(sbuf));
	printk("Date and time: %s\n", sbuf);

	modem_info_short_get(MODEM_INFO_MCC, &mcc);
	printk("Mobile country code: %d\n", mcc);

	modem_info_short_get(MODEM_INFO_MNC, &mnc);
	printk("Mobile network code: %d\n", mnc);

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

static void lte_handler(const struct lte_lc_evt *const evt)
{
	struct shared_data *sd = shared_data_get();
	switch (evt->type) {
	case LTE_LC_EVT_NW_REG_STATUS:
		if ((evt->nw_reg_status != LTE_LC_NW_REG_REGISTERED_HOME) &&
		     (evt->nw_reg_status != LTE_LC_NW_REG_REGISTERED_ROAMING)) {
			break;
		}

		LOG_INF("Network registration status: %s\n",
			evt->nw_reg_status == LTE_LC_NW_REG_REGISTERED_HOME ?
			"Connected - home network" : "Connected - roaming\n");
		k_sem_give(&sd->lte_connected);
		break;
	case LTE_LC_EVT_PSM_UPDATE:
		LOG_INF("PSM parameter update: TAU: %d, Active time: %d",
			evt->psm_cfg.tau, evt->psm_cfg.active_time);
		if (evt->psm_cfg.active_time == -1){
			LOG_ERR("Network rejected PSM parameters. Failed to enable PSM");
		}
		break;
	case LTE_LC_EVT_EDRX_UPDATE: 
		LOG_INF("eDRX parameter update: eDRX: %f, PTW: %f",
			evt->edrx_cfg.edrx, evt->edrx_cfg.ptw);
		break;
	
	case LTE_LC_EVT_RRC_UPDATE:
		LOG_INF("RRC mode: %s\n",
			evt->rrc_mode == LTE_LC_RRC_MODE_CONNECTED ?
			"Connected" : "Idle\n");
		break;
	case LTE_LC_EVT_CELL_UPDATE:
		LOG_INF("LTE cell changed: Cell ID: %d, Tracking area: %d\n",
		       evt->cell.id, evt->cell.tac);
		break;
	default:
		break;
	}
}
static int modem_configure(void)
{
	int err;

	LOG_INF("Initializing modem library");

	err = nrf_modem_lib_init();
	if (err)
	{
		LOG_ERR("Failed to initialize the modem library, error: %d", err);
		return err;
	}

	// Initialize modem info
	err = modem_info_init();
	if (err)
	{
		printk("Failed to initialize modem info: %d", err);
		return 0;
	}
	/* STEP 8 - Request PSM and eDRX from the network */
	err = lte_lc_psm_req(true);
	if (err) {
		LOG_ERR("lte_lc_psm_req, error: %d", err);
	}
	err = lte_lc_edrx_req(true);
	if (err) {
		LOG_ERR("lte_lc_edrx_req, error: %d", err);
	}

	LOG_INF("Connecting to LTE network");

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

	err = lte_lc_init_and_connect_async(lte_handler);
	if (err)
	{
		LOG_ERR("Modem could not be configured, error: %d", err);
		return err;
	}

	// /* Decativate LTE and enable GNSS. */
	// err = lte_lc_func_mode_set(LTE_LC_FUNC_MODE_DEACTIVATE_LTE);
	// if (err)
	// {
	// 	LOG_ERR("Failed to decativate LTE and enable GNSS functional mode");
	// 	return err;
	// }

	return 0;
}

int main(void)
{
	int err;
    char imei[IMEI_BUF_SIZE];

    printk("HTTPS client sample started\n\r");
	shared_data_init();
	struct shared_data *sd = shared_data_get();
	#ifdef CONFIG_BOARD_THINGY91_NRF9160NS
	thingy91_sensors_init();
	#endif
	err = modem_configure();
	if (err) {
		LOG_ERR("Failed to configure the modem");
		return 0;
	}
	k_sem_take(&sd->lte_connected, K_FOREVER);
	// Print modem information
    print_modem_info();
	// Get IMEI
    err = modem_info_string_get(MODEM_INFO_IMEI, imei, sizeof(imei));
    if (err < 0) {
        printk("Failed to get IMEI, error: %d\n", err);
        return err;
    }
	fetch_and_parse_json_response(imei);
	printk("Received data: %s\n", sd->response_buf);
	err = lte_lc_func_mode_set(LTE_LC_FUNC_MODE_DEACTIVATE_LTE);
	if (err != 0){
		LOG_ERR("Failed to decativate LTE and enable GNSS functional mode");
		
	}
	//sensor_thread_start();
	
	return 0;
}
