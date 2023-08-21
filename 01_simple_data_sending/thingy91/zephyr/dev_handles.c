#include <zephyr/device.h>
#include <zephyr/toolchain.h>

/* 1 : /soc/peripheral@40000000/clock@5000:
 */
const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_dts_ord_64[] = { DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, DEVICE_HANDLE_ENDS };

/* 2 : /soc/peripheral@40000000/gpio@842500:
 * Supported:
 *    - /soc/peripheral@40000000/spi@b000
 *    - /soc/peripheral@40000000/spi@b000/adxl362@0
 *    - /soc/peripheral@40000000/spi@b000/adxl372@1
 */
const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_dts_ord_6[] = { DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, 7, 8, 9, DEVICE_HANDLE_ENDS };

/* 3 : /psa-rng:
 */
const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_dts_ord_8[] = { DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, DEVICE_HANDLE_ENDS };

/* 4 : /soc/peripheral@40000000/uart@8000:
 */
const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_dts_ord_91[] = { DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, DEVICE_HANDLE_ENDS };

/* 5 : __device_nrf91_socket:
 */
const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_nrf91_socket[] = { DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, DEVICE_HANDLE_ENDS };

/* 6 : /soc/peripheral@40000000/i2c@a000:
 * Supported:
 *    - /soc/peripheral@40000000/i2c@a000/bme680@76
 */
const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_dts_ord_107[] = { DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, 10, DEVICE_HANDLE_ENDS };

/* 7 : /soc/peripheral@40000000/spi@b000:
 * Direct Dependencies:
 *    - /soc/peripheral@40000000/gpio@842500
 * Supported:
 *    - /soc/peripheral@40000000/spi@b000/adxl362@0
 *    - /soc/peripheral@40000000/spi@b000/adxl372@1
 */
const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_dts_ord_113[] = { 2, DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, 8, 9, DEVICE_HANDLE_ENDS };

/* 8 : /soc/peripheral@40000000/spi@b000/adxl362@0:
 * Direct Dependencies:
 *    - /soc/peripheral@40000000/gpio@842500
 *    - /soc/peripheral@40000000/spi@b000
 */
const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_dts_ord_114[] = { 2, 7, DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, DEVICE_HANDLE_ENDS };

/* 9 : /soc/peripheral@40000000/spi@b000/adxl372@1:
 * Direct Dependencies:
 *    - /soc/peripheral@40000000/gpio@842500
 *    - /soc/peripheral@40000000/spi@b000
 */
const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_dts_ord_115[] = { 2, 7, DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, DEVICE_HANDLE_ENDS };

/* 10 : /soc/peripheral@40000000/i2c@a000/bme680@76:
 * Direct Dependencies:
 *    - /soc/peripheral@40000000/i2c@a000
 */
const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_dts_ord_109[] = { 6, DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, DEVICE_HANDLE_ENDS };
