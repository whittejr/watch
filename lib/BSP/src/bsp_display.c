// /**
// * @file    bsp_display.c
// * @brief   none
// * @version 0.1.0
// * @author  Alessandro Davi
// * @date    2026-08-28
// */

// #include "bsp_display.h"
// #include "driver_ssd1306.h"
// #include "driver_ssd1306_basic.h"
// #include "ls013b7dh03.h"
// #include "ls013b7dh03_basic.h"
// #include "spi.h"

// uint8_t fb[2048];

// void bsp_display_write_string_ssd1306(uint8_t x, uint8_t y, char *texto) {
//     ssd1306_basic_string(x, y, texto, (uint16_t)strlen(texto), 1, SSD1306_FONT_16);
// }

// void bsp_display_init_ssd1306(ssd1306_interface_t interface, ssd1306_address_t addr) {
//     ssd1306_basic_init(interface, addr);
//     ssd1306_basic_display_on();

//     // ssd1306_basic_clear();

//     // bsp_display_write_string_ssd1306(0, 0,"TESTE");
// }


// void bsp_display_clear_ssd1306(void) {
//     ssd1306_basic_clear();
// }


// void bsp_display_init(void) {
//     // ls013b7dh03_basic_init(fb);

    
//     // // Display: 128x128
//     // // Framebuffer: 2048 bytes (128 * 128 / 8)

//     // const uint16_t width = 128;
//     // const uint16_t height = 128;

//     // // Quadrado de 32x32 pixels no centro
//     // const uint16_t square_size = 32;
//     // const uint16_t x0 = (width - square_size) / 2;
//     // const uint16_t y0 = (height - square_size) / 2;

//     // // Primeiro pinta TODO o display com 0xFF
//     // memset(fb, 0xFF, sizeof(fb));

//     // // Depois coloca o quadrado 0x00 no centro
//     // for (uint16_t y = y0; y < y0 + square_size; y++) {
//     //     for (uint16_t x = x0; x < x0 + square_size; x++) {

//     //         uint16_t byte_index = (y * width + x) / 8;
//     //         uint8_t bit_index = 7 - (x % 8);

//     //         fb[byte_index] &= ~(1 << bit_index);
//     //     }
//     // }

//     // // Atualiza o display
//     // ls013b7dh03_basic_clear();
//     // ls013b7dh03_basic_refresh();
// }

// void BSP_Display_Clear(void) {

// }

// void bsp_display_clear(void) {
//     // ls013b7dh03_basic_clear();
// }

// void bsp_display_write(void) {
//     // ls013b7dh03_basic_refresh();
// }

// uint8_t ls013b7dh03_interface_spi_init(void) {
//     // O hardware já foi iniciado no main via spi_init() no core.
//     return 0;
// }

// uint8_t ls013b7dh03_interface_spi_deinit(void) {
//     return 0;
// }

// uint8_t ls013b7dh03_interface_spi_write(uint8_t *buf, uint16_t len) {
//     if (HAL_SPI_Transmit(&hspi1, buf, len, 500) == HAL_OK) return 0;
//     return 1;
// }

// void ls013b7dh03_interface_cs_control(uint8_t state) {
//     if (state == 1) {
//         HAL_GPIO_WritePin(DISP_CS_PORT, DISP_CS_PIN, GPIO_PIN_SET);
//     } else {
//         HAL_GPIO_WritePin(DISP_CS_PORT, DISP_CS_PIN, GPIO_PIN_RESET);
//     }
// }

// void ls013b7dh03_interface_delay_ms(uint32_t ms) {
//     HAL_Delay(ms);
// }
