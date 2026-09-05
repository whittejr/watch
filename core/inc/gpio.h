/**
 * @file gpio.h
 * @brief  none
 * @version 0.1
 * @author Alessandro Davi
 * @date 2026-08-28
 */

#ifndef GPIO_H
#define GPIO_H

#include "main.h"

void gpio_init(void);
void gpio_write(GPIO_TypeDef *port, uint16_t pin, uint8_t state);
uint8_t gpio_read(GPIO_TypeDef *port, uint16_t pin);

#endif // GPIO_H
