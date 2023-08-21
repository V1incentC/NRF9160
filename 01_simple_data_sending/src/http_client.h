// http_client.h
#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <zephyr/net/http/client.h>
#include "api_response_parser.h"



struct request_fields {
    uint16_t field1;  // Battery (mV)
    int16_t field2;   // Signal Strength (dBm)
    int16_t field3;   // Temperature (*C)
    uint32_t field4;  // Pressure (Pa)
    uint32_t field5;  // Humidity (%)
    uint32_t field6;  // Weight (grams)
    uint32_t field7;  // Placeholder for Field7
    uint32_t field8;  // Placeholder for Field8
};


int http_client_send_get_request(const char *url);
void fetch_and_parse_json_response(const char *imei);
#endif // HTTP_CLIENT_H