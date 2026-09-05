/**
 * @file uart.h
 * @brief  none
 * @version 0.1
 * @author Alessandro Davi
 * @date 2026-09-04
 */

#ifndef UART_H
#define UART_H

#include "main.h"

uint8_t uart_init(void);

uint8_t uart_deinit(void);

uint8_t uart_write(uint8_t *data, uint16_t len);


#endif // UART_H