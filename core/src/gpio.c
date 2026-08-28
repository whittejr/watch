/**
* @file    gpio.c
* @brief   none
* @version 0.1.0
* @author  Alessandro Davi
* @date    2026-08-28
*/

#include "gpio.h"

void gpio_init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // SPI1 Pins (SCK, MISO, MOSI)
    GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1; 
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    HAL_GPIO_WritePin(DISP_ON_PORT, DISP_ON_PIN, GPIO_PIN_SET); // turn display on

    // PWM/LPTIM1 for EXTCOM
    GPIO_InitStruct.Pin = DISP_EXTCOM_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF1_LPTIM1; 
    HAL_GPIO_Init(DISP_EXTCOM_PORT, &GPIO_InitStruct);

    
}