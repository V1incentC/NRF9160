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
#include <zephyr/data/json.h>
#include <zephyr/random/rand32.h>
#include <string.h>

#define MSGQ_ID 1
#define QUEUE_SIZE_ID 21  /* ID used to store the queue size in NVS */
static struct nvs_fs fs;
#define JSON_UPDATES_NUM 20
#define BATCH_SIZE 5
#define NVS_PARTITION storage_partition
#define NVS_PARTITION_DEVICE FIXED_PARTITION_DEVICE(NVS_PARTITION)
#define NVS_PARTITION_OFFSET FIXED_PARTITION_OFFSET(NVS_PARTITION)


K_MUTEX_DEFINE(my_mutex);
struct k_msgq saved_msq;
/* Define a struct to describe the structure of an update object */
struct update {
    char created_at[32];
    int field1;
    int field2;
    int field3;
    int field4;
    int field5;
    int field6;
    int field7;
    int field8;
    int Latitude;
    int Longitude;
    int Elevation;
    char Status[128];
};
/* Define a struct to describe the structure of an update object */
struct update_json {
    char* created_at;
    int field1;
    int field2;
    int field3;
    int field4;
    int field5;
    int field6;
    int field7;
    int field8;
    int Latitude;
    int Longitude;
    int Elevation;
    char* Status;
};
K_MSGQ_DEFINE(my_msgq, sizeof(struct update), JSON_UPDATES_NUM, 4);
/* Define a descriptor to map the JSON fields to the update struct */
static const struct json_obj_descr update_descr[] = {
    JSON_OBJ_DESCR_PRIM(struct update_json, created_at, JSON_TOK_STRING),
    JSON_OBJ_DESCR_PRIM(struct update_json, field1, JSON_TOK_NUMBER),
    JSON_OBJ_DESCR_PRIM(struct update_json, field2, JSON_TOK_NUMBER),
    JSON_OBJ_DESCR_PRIM(struct update_json, field3, JSON_TOK_NUMBER),
    JSON_OBJ_DESCR_PRIM(struct update_json, field4, JSON_TOK_NUMBER),
    JSON_OBJ_DESCR_PRIM(struct update_json, field5, JSON_TOK_NUMBER),
    JSON_OBJ_DESCR_PRIM(struct update_json, field6, JSON_TOK_NUMBER),
    JSON_OBJ_DESCR_PRIM(struct update_json, field7, JSON_TOK_NUMBER),
    JSON_OBJ_DESCR_PRIM(struct update_json, field8, JSON_TOK_NUMBER),
    JSON_OBJ_DESCR_PRIM(struct update_json, Latitude, JSON_TOK_NUMBER),
    JSON_OBJ_DESCR_PRIM(struct update_json, Longitude, JSON_TOK_NUMBER),
    JSON_OBJ_DESCR_PRIM(struct update_json, Elevation, JSON_TOK_NUMBER),
    JSON_OBJ_DESCR_PRIM(struct update_json, Status, JSON_TOK_STRING),
};

/* Define a struct to describe the structure of the top-level object */
struct my_data {
    char* write_api_key;
    struct update_json updates[JSON_UPDATES_NUM];
    size_t updates_len;
};

/* Define a descriptor to map the top-level object's fields to the my_data struct */
static const struct json_obj_descr my_data_descr[] = {
    JSON_OBJ_DESCR_PRIM(struct my_data, write_api_key, JSON_TOK_STRING),
    /* Use an array descriptor to map the updates array */
    JSON_OBJ_DESCR_OBJ_ARRAY(struct my_data,
                         updates,
                         JSON_UPDATES_NUM,
                         updates_len,
                         update_descr,
                         ARRAY_SIZE(update_descr)),
};

void write_to_buffer(struct update *data)
{
    /* Read the queue size from NVS to get the next available ID */
    int id;
    int rc = nvs_read(&fs, QUEUE_SIZE_ID, &id, sizeof(int));
    if (rc == -ENOENT)
    {
        /* No entry found for queue size, initialize it to 0 */
        id = 0;
    }
    else if (rc < 0)
    {
        printk("Failed to read queue size from NVS\n");
        return;
    }
    k_mutex_lock(&my_mutex, K_FOREVER);
    while (k_msgq_put(&my_msgq, data, K_NO_WAIT) != 0)
    {
        /* queue is full: wait for consumer to process and make room */
        k_mutex_unlock(&my_mutex);
        k_sleep(K_MSEC(500));
    }
    k_mutex_unlock(&my_mutex);
    rc = nvs_write(&fs, id, data, sizeof(struct update));
    if (rc < 0)
    {
        printk("Failed to write to NVS\n");
    }

    /* Increment the queue size and write it back to NVS */
    id++;
    rc = nvs_write(&fs, QUEUE_SIZE_ID, &id, sizeof(int));
    if (rc < 0)
    {
        printk("Failed to write queue size to NVS\n");
    }
}
int read_data(struct update *rx_data)
{
    k_mutex_lock(&my_mutex, K_FOREVER);
    if (k_msgq_get(&my_msgq, rx_data, K_NO_WAIT) == 0)
    {
        k_mutex_unlock(&my_mutex);
        /* Update the queue size in NVS */
        int queue_size;
        int rc = nvs_read(&fs, QUEUE_SIZE_ID, &queue_size, sizeof(int));
        if (rc == -ENOENT)
        {
            printk("No entry found for queue size\n");
            return 0;
        }
        else if (rc < 0)
        {
            printk("Failed to read queue size from NVS\n");
            return 0;
        }
        else
        {
            /* Successfully read the queue size, decrement it */
            queue_size--;
        }
        rc = nvs_write(&fs, QUEUE_SIZE_ID, &queue_size, sizeof(int));
        if (rc < 0)
        {
            printk("Failed to write queue size to NVS\n");
            return 0;
        }
        return 0;
    }
    else
    {
        k_mutex_unlock(&my_mutex);
        /* queue is empty */
        return -1;
    }
}

void load_queue(void) {
    int rc;

    /* Read the queue size from NVS */
    int queue_size;
    rc = nvs_read(&fs, QUEUE_SIZE_ID, &queue_size, sizeof(int));
    if (rc == -ENOENT) {
        /* No entry found for queue size, initialize it to 0 */
        queue_size = 0;
        rc = nvs_write(&fs, QUEUE_SIZE_ID, &queue_size, sizeof(int));
        if (rc < 0) {
            printk("Failed to write queue size to NVS\n");
            return;
        }
        /* Nothing to read from NVS, return immediately */
        return;
    } else if (rc < 0) {
        /* Nothing to read from NVS, return immediately */
        printk("Failed to read queue size from NVS\n");
        return;
    }
    int id = 0;
	rc = nvs_write(&fs, QUEUE_SIZE_ID, &id, sizeof(int));
    if (rc < 0) {
        printk("Failed to write queue size to NVS\n");
    }
    /* Load the items from NVS into the queue */
    for (int i = 0; i < queue_size; i++) {
        struct update rx_data;
        rc = nvs_read(&fs, i, &rx_data, sizeof(rx_data));
        if (rc == -ENOENT) {
            printk("No entry found for ID %d\n", i);
        } else if (rc < 0) {
            printk("Failed to read from NVS\n");
        } else {
            write_to_buffer(&rx_data);
        }
    }
}

void write_thread(void) {
    k_msleep(3000);
    while (1) {
        /* Create an update struct and populate it with random data */
        struct update data = {
            .created_at = "2023-08-17 10:26:2",
            .field1 =  1010,
            .field2 =  1002,
            .field3 =  1300,
            .field4 =  1400,
            .field5 =  1005,
            .field6 =  1050,
            .field7 =  1050,
            .field8 =  1050,
            .Latitude = 90,
            .Longitude =  NULL,
            .Elevation =  NULL,
            .Status = "random status"
        };

        /* Write the update struct to the buffer */
        write_to_buffer(&data);
        printk("Wrote update\n");

        // k_sleep(K_SECONDS(1));
        k_msleep(1000);
    }
}
void encode_batch(struct my_data *data, int start, int end, char *json_str, size_t json_str_len) {
    /* Encode the current batch of updates into a JSON string */
    int len = json_obj_encode_buf(my_data_descr,
                                  ARRAY_SIZE(my_data_descr),
                                  data,
                                  json_str,
                                  json_str_len);
    if (len < 0) {
        printk("Failed to encode data\n");
    } else {
        printk("JSON string: %s\n", json_str);
    }

    /* Free allocated memory for the current batch of updates */
    for (int j = start; j < end; j++) {
        k_free(data->updates[j].created_at);
        k_free(data->updates[j].Status);
    }
}

void copy_update(struct update_json *dst, struct update *src) {
    /* Allocate memory for the created_at and Status fields */
    dst->created_at = k_malloc(strlen(src->created_at) + 1);
    if (dst->created_at == NULL) {
        printk("Failed to allocate memory\n");
        return;
    }
    dst->Status = k_malloc(strlen(src->Status) + 1);
    if (dst->Status == NULL) {
        printk("Failed to allocate memory\n");
        return;
    }

    /* Copy data from the src struct into the dst struct */
    strcpy(dst->created_at, src->created_at);
    dst->field1 = src->field1;
    dst->field2 = src->field2;
    dst->field3 = src->field3;
    dst->field4 = src->field4;
    dst->field5 = src->field5;
    dst->field6 = src->field6;
    dst->field7 = src->field7;
    dst->field8 = src->field8;
    dst->Latitude = src->Latitude;
    dst->Longitude = src->Longitude;
    dst->Elevation = src->Elevation;
    strcpy(dst->Status, src->Status);
}

void read_thread(void) {
    k_msleep(3100);
    printk("Started read thread\n");
    while (1) {
        /* Create a my_data struct and populate it with data */
        struct my_data data = {
            .write_api_key = "0M1HAJYG2ZUGBOTX",
        };

        /* Dequeue all items from the message queue and add them to the updates array */
        int i = 0;
        struct update rx_data;
        while (read_data(&rx_data) == 0) {
            copy_update(&data.updates[i], &rx_data);

            i++;
            if (i >= ARRAY_SIZE(data.updates)) {
                break;
            }

            /* Encode the current batch of updates if we've reached the batch size */
            if (i % BATCH_SIZE == 0) {
                data.updates_len = BATCH_SIZE;

                /* Create a buffer to hold the encoded JSON string */
                char json_str[2500];
                encode_batch(&data, i - BATCH_SIZE, i, json_str, sizeof(json_str));

                /* Use the encoded JSON string */
                // ...
            }
        }

        /* Encode any remaining updates that didn't fit into a full batch */
        if (i % BATCH_SIZE != 0) {
            data.updates_len = i % BATCH_SIZE;

            /* Create a buffer to hold the encoded JSON string */
            char json_str[2500];
            encode_batch(&data, i - (i % BATCH_SIZE), i, json_str, sizeof(json_str));

            /* Use the encoded JSON string */
            // ...
        }
        k_sleep(K_SECONDS(7));
    }
}


K_THREAD_DEFINE(write_tid, 6*1024, write_thread, NULL, NULL, NULL, 7, 0, 3000);
K_THREAD_DEFINE(read_tid, 8*1024, read_thread, NULL, NULL, NULL, 7, 0, 3100);

int main(void) {

    k_msleep(2000);
    printk("Started main\n");
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
    fs.offset =  0xfa000;
	rc = flash_get_page_info_by_offs(fs.flash_device, fs.offset, &info);
	if (rc)
	{
		printk("Unable to get page info\n");
		return 0;
	}
	fs.sector_size = info.size;
	fs.sector_count = 6U;

	rc = nvs_mount(&fs);
	if (rc)
	{
		printk("Flash Init failed\n");
		return 0;
	}

    printk("Started loading queue\n");
    load_queue();
    printk("Finished loading queue\n");
    
}
