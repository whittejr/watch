#include "adxl362_interface.h"
#include "board_config.h"
#include "gpio.h"
#include "spi.h"
#include <stdarg.h>

extern SPI_HandleTypeDef hspi1;

uint8_t adxl362_interface_spi_init(void) {
    return 0;
}

uint8_t adxl362_interface_spi_deinit(void) {
    return 0;
}

uint8_t adxl362_interface_spi_read(uint8_t reg, uint8_t *buf, uint16_t len) {
    uint8_t res;
    gpio_write(ACCEL_CS_PORT, ACCEL_CS_PIN, 0);
    res = spi_read(reg, buf, len);
    gpio_write(ACCEL_CS_PORT, ACCEL_CS_PIN, 1);
    return res;
}

uint8_t adxl362_interface_spi_read_address16(uint16_t addr, uint8_t *buf, uint16_t len) {
    uint8_t res;
    gpio_write(ACCEL_CS_PORT, ACCEL_CS_PIN, 0);
    res = spi_read_address16(addr, buf, len);
    gpio_write(ACCEL_CS_PORT, ACCEL_CS_PIN, 1);
    return res;
}

uint8_t adxl362_interface_spi_write_address16(uint16_t addr, uint8_t *buf, uint16_t len) {
    uint8_t res;
    gpio_write(ACCEL_CS_PORT, ACCEL_CS_PIN, 0);
    res = spi_write_address16(addr, buf, len);
    gpio_write(ACCEL_CS_PORT, ACCEL_CS_PIN, 1);
    return res;
}

void adxl362_interface_delay_ms(uint32_t ms) {
    HAL_Delay(ms);
}

void adxl362_interface_debug_print(const char *const fmt, ...) {
    // UART debug output if needed
}

void adxl362_interface_receive_callback(uint8_t type) {
    // Handle interrupts if used
}
