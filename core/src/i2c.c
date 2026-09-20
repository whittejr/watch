/**
* @file    i2c.c
* @brief   none
* @version 0.1.0
* @author  Alessandro Davi
* @date    2026-08-28
*/

#include "i2c.h"

I2C_HandleTypeDef hi2c1;

uint8_t i2c_init(void) {
    GPIO_InitTypeDef GPIOHandle = {0};

    __HAL_RCC_I2C1_CLK_ENABLE();

    GPIOHandle.Pin = I2C_SDA_PIN | I2C_SCL_PIN;
    GPIOHandle.Mode = GPIO_MODE_AF_OD;
    GPIOHandle.Alternate = GPIO_AF4_I2C1;
    GPIOHandle.Pull = GPIO_PULLUP;
    GPIOHandle.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(I2C_SDA_PORT, &GPIOHandle); 

    hi2c1.Instance = I2C_INSTANCE;
    hi2c1.Init.Timing = 0x00300617; // Valor TIMINGR gerado para I2C Fast Mode (400kHz) em 16 MHz
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLED;
    hi2c1.Init.OwnAddress1 = 0;
    hi2c1.Init.OwnAddress2 = 0;
    hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLED;
    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLED;

    if (HAL_I2C_Init(&hi2c1) != 0) {
        return 1;
    }

    /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK) {
    // Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK) {
    // Error_Handler();
  }

    return 0;
}

uint8_t i2c_write(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len) {
    if (HAL_I2C_Mem_Write(&hi2c1, addr, reg, I2C_MEMADD_SIZE_8BIT, buf, len, 100) != HAL_OK) {
        return 1;
    }
    return 0;
}

uint8_t i2c_deinit(void) {
    HAL_GPIO_DeInit(I2C_SDA_PORT, I2C_SDA_PIN | I2C_SCL_PIN);
    HAL_I2C_DeInit(&hi2c1);
    
    return 0;
}

