/**
* @file    main.c
* @brief   none
* @version 0.1.0
* @a* @author  Your name here
* @date    2026-03-31
*/

#include "main.h"
#include "gpio.h"
#include "spi.h"

int main(void) {
    HAL_Init();
    gpio_init();
    spi_init();
    // i2c_init();    


    return 0;
}
