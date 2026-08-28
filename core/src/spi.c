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
SPI_HandleTypeDef hspi2; // accel   adxl362

void spi_init(void) {
    __HAL_RCC_SPI1_CLK_ENABLE();
    __HAL_RCC_SPI2_CLK_ENABLE();

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

    hspi2.Instance = SPI2;
    hspi2.Init.Mode = SPI_MODE_MASTER;
    hspi2.Init.Direction = SPI_DIRECTION_2LINES; 
    hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;   
    hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;       
    hspi2.Init.NSS = SPI_NSS_SOFT;              
    hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64; 
    hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;      
    hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi2.Init.CRCPolynomial = 7;
    HAL_SPI_Init(&hspi2);
}
