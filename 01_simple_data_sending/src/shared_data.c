// shared_data.c
#include "shared_data.h"

static struct shared_data shared_data_instance;

void shared_data_init(void) {
    k_sem_init(&shared_data_instance.api_key_sem, 0, 1);
    k_sem_init(&shared_data_instance.http_response_sem, 0, 1);
    k_mutex_init(&shared_data_instance.url_mutex);
    
    // Initialize other shared data here
}

struct shared_data *shared_data_get(void) {
    return &shared_data_instance;
}
