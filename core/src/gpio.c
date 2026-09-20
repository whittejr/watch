/**
* @file    gpio.c
* @brief   none
* @version 0.1.0
* @author  Alessandro Davi
* @date    2026-08-28
*/

#include "gpio.h"
#include "board_config.h"
#include "stm32wbxx_hal_gpio.h"
#include "stm32wbxx_hal_rcc.h"

void gpio_init(void) {
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // SPI1 Pins (SCK, MISO, MOSI)
    GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1; 
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);


    // ACCEL 
    GPIO_InitTypeDef ACCEL_CS = {0};
    ACCEL_CS.Pin = ACCEL_CS_PIN;
    ACCEL_CS.Mode = GPIO_MODE_OUTPUT_PP;
    ACCEL_CS.Pull = GPIO_PULLUP;
    ACCEL_CS.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(ACCEL_CS_PORT, &ACCEL_CS);

    GPIO_InitTypeDef CS_PIN = {0};
    CS_PIN.Pin = DISP_CS_PIN;
    CS_PIN.Mode = GPIO_MODE_OUTPUT_PP;
    CS_PIN.Pull = GPIO_PULLUP;
    CS_PIN.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOB, &CS_PIN);
    
   

    // UART
     GPIO_InitTypeDef gpio_uart = {0};
    gpio_uart.Pin = uart_pin;
    gpio_uart.Mode = GPIO_MODE_AF_PP;
    gpio_uart.Alternate = GPIO_AF7_USART1;
    gpio_uart.Pull = GPIO_PULLUP;
    gpio_uart.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(uart_port, &gpio_uart);
}

void gpio_write(GPIO_TypeDef *port, uint16_t pin, uint8_t state) {
    HAL_GPIO_WritePin(port, pin, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

uint8_t gpio_read(GPIO_TypeDef *port, uint16_t pin) {
    return (uint8_t)HAL_GPIO_ReadPin(port, pin);
}
