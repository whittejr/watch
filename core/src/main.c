/**
* @file    main.c
* @brief   none
* @version 0.1.0
* @author  Alessandro Davi
* @date    2026-09-04
*/

#include "main.h"
#include "bsp.h"
#include "display/lv_display.h"
#include "driver_ssd1306.h"
#include "lv_init.h"
#include "misc/lv_area.h"
#include "qpc.h"
#include "bsp.h"
#include "lvgl.h"
#include "stm32wbxx_hal.h"
#include "tick/lv_tick.h"

#define hor_res 128
#define ver_res 64
#define BYTES_PER_PIXEL (LV_COLOR_FORMAT_GET_SIZE(LV_COLOR_FORMAT_I1))


static uint8_t buf1[hor_res * ver_res / 10 * BYTES_PER_PIXEL];

int main(void) {
    HAL_Init();
    QF_init();
    bsp_init(); 
    lv_init();   
    lv_tick_set_cb(HAL_GetTick);
    lv_display_t *display1 = lv_display_create(hor_res, ver_res);
    lv_display_set_buffers(display1, buf1, NULL, sizeof(buf1), LV_DISPLAY_RENDER_MODE_FULL);

    return QF_run();
}

// 
void QF_onStartup(void) {
    // Inicialização adicional do QP, se necessária.
}

void QV_onIdle(void) {
    QV_CPU_SLEEP();
    // CPU idle.
    // Pode colocar __WFI() posteriormente.
}

void Q_onError(char const *module, int_t loc) {
    (void)module;
    (void)loc;

    // Erro fatal do QP.
    __disable_irq();

    for (;;) {
    }
}


void my_flush_cb(lv_display_t * display, const lv_area_t * area, uint8_t * px_map)
{
    /*The most simple case (but also the slowest) to put all pixels to the screen one-by-one
     *`put_px` is just an example, it needs to be implemented by you.*/
    uint16_t * buf16 = (uint16_t *)px_map; /*Let's say it's a 16 bit (RGB565) display*/
    int32_t x, y;
    for(y = area->y1; y <= area->y2; y++) {
        for(x = area->x1; x <= area->x2; x++) {
            put_px(x, y, *buf16);
            buf16++;
        }
    }

    /* IMPORTANT!!!
     * Inform LVGL that you are ready with the flushing and buf is not used anymore*/
    lv_display_flush_ready(disp);
}


ssd1306_gram_write_point(ssd1306_handle_t *handle, uint8_t x, uint8_t y, uint8_t data);