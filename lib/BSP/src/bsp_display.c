/**
* @file    bsp_display.c
* @brief   none
* @version 0.1.0
* @author  Alessandro Davi
* @date    2026-08-28
*/

#include "bsp_display.h"
#include "ls013b7dh03.h"
#include "ls013b7dh03_basic.h"
#include "spi.h"



void BSP_Display_Init(void) {
    ls013b7dh03_basic_init(const uint8_t *fb_pointer);
}

void BSP_Display_Clear(void) {

}

// flush (lvgl)
void BSP_Display_Flush(void) {
    ls013b7dh03_basic_clear();
}

uint8_t ls013b7dh03_interface_spi_init(void) {
    // O hardware já foi iniciado no main via spi_init() no core.
    return 0;
}

uint8_t ls013b7dh03_interface_spi_deinit(void) {
    return 0;
}

uint8_t ls013b7dh03_interface_spi_write(uint8_t *buf, uint16_t len) {
    if (HAL_SPI_Transmit(&hspi1, buf, len, 500) == HAL_OK) return 0;
    return 1;
}

void ls013b7dh03_interface_cs_control(uint8_t state) {
    if (state == 1) {
        HAL_GPIO_WritePin(DISP_CS_PORT, DISP_CS_PIN, GPIO_PIN_SET);
    } else {
        HAL_GPIO_WritePin(DISP_CS_PORT, DISP_CS_PIN, GPIO_PIN_RESET);
    }
}

void ls013b7dh03_interface_delay_ms(uint32_t ms) {
    HAL_Delay(ms);
}
