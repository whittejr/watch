/**
* @file    spi.c
* @brief   none
* @version 0.1.0
* @author  Alessandro Davi
* @date    2026-08-28
*/
#include "spi.h"
#include "stm32wb55xx.h"
#include "stm32wbxx_hal_spi.h"

SPI_HandleTypeDef hspi1; // display ls013b7dh03

void spi_init(void) {
    __HAL_RCC_SPI1_CLK_ENABLE();

    hspi1.Instance = SPI1;
    hspi1.Init.Mode = SPI_MODE_MASTER;
    hspi1.Init.Direction = SPI_DIRECTION_2LINES; 
    hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;   
    hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;       
    hspi1.Init.NSS = SPI_NSS_SOFT;              
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
    hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;      
    hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi1.Init.CRCPolynomial = 7;

    HAL_SPI_Init(&hspi1);
}

// 1. Envio de buffer contínuo (Display)
uint8_t spi_transmit(uint8_t *buf, uint16_t len) {
    return (HAL_SPI_Transmit(&hspi1, buf, len, 500) == HAL_OK) ? 0 : 1;
}

uint8_t spi_read(uint8_t reg, uint8_t *buf, uint16_t len) {
    if (HAL_SPI_Transmit(&hspi1, &reg, 1, 100) != HAL_OK) return 1;
    if (len > 0 && buf != NULL) {
        if (HAL_SPI_Receive(&hspi1, buf, len, 100) != HAL_OK) return 1;
    }
    return 0;
}

uint8_t spi_write(uint8_t reg, uint8_t *buf, uint16_t len) {
    if (HAL_SPI_Transmit(&hspi1, &reg, 1, 100) != HAL_OK) return 1;
    if (len > 0 && buf != NULL) {
        if (HAL_SPI_Transmit(&hspi1, buf, len, 100) != HAL_OK) return 1;
    }
    return 0;
}

uint8_t spi_read_address16(uint16_t addr, uint8_t *buf, uint16_t len) {
    uint8_t cmd[2] = { (uint8_t)(addr >> 8), (uint8_t)(addr & 0xFF) };

    if (HAL_SPI_Transmit(&hspi1, cmd, 2, 100) != HAL_OK) return 1;
    if (len > 0 && buf != NULL) {
        if (HAL_SPI_Receive(&hspi1, buf, len, 100) != HAL_OK) return 1;
    }
    return 0;
}

uint8_t spi_write_address16(uint16_t addr, uint8_t *buf, uint16_t len) {
    uint8_t cmd[2] = { (uint8_t)(addr >> 8), (uint8_t)(addr & 0xFF) };

    if (HAL_SPI_Transmit(&hspi1, cmd, 2, 100) != HAL_OK) return 1;
    if (len > 0 && buf != NULL) {
        if (HAL_SPI_Transmit(&hspi1, buf, len, 100) != HAL_OK) return 1;
    }
    return 0;
}
