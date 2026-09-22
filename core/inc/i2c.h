/**
 * @file i2c.h
 * @brief  none
 * @version 0.1
 * @author Alessandro Davi
 * @date 2026-08-28
 */

#ifndef I2C_H
#define I2C_H

#include "main.h"

uint8_t i2c_init(void);
uint8_t i2c_deinit(void);
uint8_t i2c_write(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);

#endif // I2C_H
