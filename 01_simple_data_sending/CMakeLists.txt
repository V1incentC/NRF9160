# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(simple_data_sending)

target_sources(app PRIVATE src/main.c)

zephyr_library_sources_ifdef(CONFIG_API_RESPONSE_PARSER_MODULE src/api_response_parser.c)
zephyr_library_sources_ifdef(CONFIG_HTTP_CLIENT_MODULE src/http_client.c)
zephyr_library_sources_ifdef(CONFIG_SHARED_DATA_MODULE src/shared_data.c)
zephyr_library_sources_ifdef(CONFIG_SENSOR_THREAD_MODULE src/sensor_thread.c)
target_sources(app PRIVATE src/thingy91.c)
# if(BOARD STREQUAL thingy91_nrf9160ns)
#     target_sources(app PRIVATE src/thingy91.c)
# endif()