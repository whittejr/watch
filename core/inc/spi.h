/**
 * @file spi.h
 * @brief  none
 * @version 0.1
 * @author Alessandro Davi
 * @date 2026-08-28
 */

#ifndef SPI_H
#define SPI_H

#include "main.h"

extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;

void spi_init(void);
uint8_t spi_transmit(uint8_t *buf, uint16_t len);
uint8_t spi_read(uint8_t reg, uint8_t *buf, uint16_t len);
uint8_t spi_write(uint8_t reg, uint8_t *buf, uint16_t len);
uint8_t spi_read_address16(uint16_t addr, uint8_t *buf, uint16_t len);
uint8_t spi_write_address16(uint16_t addr, uint8_t *buf, uint16_t len);

#endif // SPI_H
