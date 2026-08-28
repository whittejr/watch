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

#endif // SPI_H
