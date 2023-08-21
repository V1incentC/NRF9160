// shared_data.h
#ifndef SHARED_DATA_H
#define SHARED_DATA_H

#include <zephyr/kernel.h>
#include "app_config.h"
#include "api_response_parser.h"

struct shared_data {
    struct k_sem api_key_sem;
    struct k_sem http_response_sem;
    struct k_mutex url_mutex;
    char response_buf[HTTP_RESPONSE_BUF_SIZE]; // Include response here
    int response_len;
    char api_key[17];
    struct api_response json_response;
    // Add more shared data here
};

void shared_data_init(void);
struct shared_data *shared_data_get(void);

#endif // SHARED_DATA_H
