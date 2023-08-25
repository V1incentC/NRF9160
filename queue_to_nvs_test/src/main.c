/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <stdio.h>
#include <zephyr/device.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/storage/flash_map.h>
#include <zephyr/fs/nvs.h>

#define MSGQ_ID 1
#define QUEUE_SIZE_ID 15  /* ID used to store the queue size in NVS */
static struct nvs_fs fs;

#define NVS_PARTITION storage_partition
#define NVS_PARTITION_DEVICE FIXED_PARTITION_DEVICE(NVS_PARTITION)
#define NVS_PARTITION_OFFSET FIXED_PARTITION_OFFSET(NVS_PARTITION)

K_MSGQ_DEFINE(my_msgq, sizeof(int), 10, 4);
struct k_msgq saved_msq;

void write_to_buffer(int data) {
    /* Read the queue size from NVS to get the next available ID */
    int id;
    int rc = nvs_read(&fs, QUEUE_SIZE_ID, &id, sizeof(int));
    if (rc == -ENOENT) {
        /* No entry found for queue size, initialize it to 0 */
        id = 0;
    } else if (rc < 0) {
        printk("Failed to read queue size from NVS\n");
        return;
    }

    while (k_msgq_put(&my_msgq, &data, K_NO_WAIT) != 0) {
        /* queue is full: wait for consumer to process and make room */
        k_sleep(K_MSEC(500));
    }
    rc = nvs_write(&fs, id, &data, sizeof(int));
    if (rc < 0) {
        printk("Failed to write to NVS\n");
    }

    /* Increment the queue size and write it back to NVS */
    id++;
    rc = nvs_write(&fs, QUEUE_SIZE_ID, &id, sizeof(int));
    if (rc < 0) {
        printk("Failed to write queue size to NVS\n");
    }
}
int read_data(void) {
    int rx_data;
    if (k_msgq_get(&my_msgq, &rx_data, K_NO_WAIT) == 0) {
        /* Update the queue size in NVS */
        int queue_size;
        int rc = nvs_read(&fs, QUEUE_SIZE_ID, &queue_size, sizeof(int));
        if (rc == -ENOENT) {
            printk("No entry found for queue size\n");
            return -1;
        } else if (rc < 0) {
            printk("Failed to read queue size from NVS\n");
            return -1;
        } else {
            /* Successfully read the queue size, decrement it */
            queue_size--;
        }
        rc = nvs_write(&fs, QUEUE_SIZE_ID, &queue_size, sizeof(int));
        if (rc < 0) {
            printk("Failed to write queue size to NVS\n");
            return -1;
        }
        return rx_data;
    } else {
        /* queue is empty */
        return -1;
    }
}

void load_queue(void) {
    int rc;
	int id;
    int rx_data;

    /* Read the queue size from NVS */
    int queue_size;
    rc = nvs_read(&fs, QUEUE_SIZE_ID, &queue_size, sizeof(int));
    if (rc == -ENOENT) {
        printk("No entry found for queue size\n");
        return;
    } else if (rc < 0) {
        printk("Failed to read queue size from NVS\n");
        return;
    }
	id = 0;
	rc = nvs_write(&fs, QUEUE_SIZE_ID, &id, sizeof(int));
    if (rc < 0) {
        printk("Failed to write queue size to NVS\n");
    }
    /* Load the items from NVS into the queue */
    for (int i = 0; i < queue_size; i++) {
        rc = nvs_read(&fs, i, &rx_data, sizeof(int));
        if (rc == -ENOENT) {
            printk("No entry found for ID %d\n", i);
        } else if (rc < 0) {
            printk("Failed to read from NVS\n");
        } else {
            write_to_buffer(rx_data);
        }
    }
}

int main(void) {

	int rc = 0;
	struct flash_pages_info info;

	/* define the nvs file system by settings with:
	 *	sector_size equal to the pagesize,
	 *	3 sectors
	 *	starting at NVS_PARTITION_OFFSET
	 */
	fs.flash_device = NVS_PARTITION_DEVICE;
	if (!device_is_ready(fs.flash_device))
	{
		printk("Flash device %s is not ready\n", fs.flash_device->name);
		return 0;
	}
	fs.offset = NVS_PARTITION_OFFSET;
	rc = flash_get_page_info_by_offs(fs.flash_device, fs.offset, &info);
	if (rc)
	{
		printk("Unable to get page info\n");
		return 0;
	}
	fs.sector_size = info.size;
	fs.sector_count = 3U;

	rc = nvs_mount(&fs);
	if (rc)
	{
		printk("Flash Init failed\n");
		return 0;
	}
	

    load_queue();

    int data;
    while ((data = read_data()) != -1) {
        printk("Got %d\n", data);
    }

    int id = 0;
	nvs_write(&fs, QUEUE_SIZE_ID, &id, sizeof(int));
	for (int i = 0; i < 5; i++) {
		write_to_buffer(i*3);
	}

	return 0;
}
