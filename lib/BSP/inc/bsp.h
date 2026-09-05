/**
 * @file bsp.h
 * @brief  none
 * @version 0.1
 * @author Alessandro Davi
 * @date 2026-09-01
 */

#ifndef BSP_H
#define BSP_H

#include "main.h"

typedef struct {
    uint8_t  hour, minute, second;
    uint8_t time_format;
    uint8_t  day, month;
    uint16_t year;
} bsp_datetime_t;

typedef struct {
    int16_t x, y, z;
} bsp_accel_raw_t;

/* GERAL */
void bsp_init(void);
/* SENSORES */
uint8_t bsp_accel_init(void);
uint8_t bsp_accel_get_xyz(bsp_accel_raw_t *raw_out);
void bsp_accel_fall_detection(void);
/* DISPLAY */
void bsp_display_init_ssd1306(void);
void bsp_display_write_string_ssd1306(uint8_t x, uint8_t y, char *texto);
void bsp_display_clear_ssd1306(void);
/* TEMPO */
void bsp_get_time(bsp_datetime_t *dt);
void bsp_set_time(const bsp_datetime_t *dt);
// P
void bsp_gpio_write(GPIO_TypeDef *port, uint16_t pin, uint8_t state);
uint8_t bsp_gpio_read(GPIO_TypeDef *port, uint16_t pin);

#endif // BSP_H
