/**
* @file    main.c
* @brief   none
* @version 0.1.0
* @author  Alessandro Davi
* @date    2026-09-04
*/

#include "main.h"
#include "driver_ssd1306_basic.h"
#include "qpc.h"
#include "bsp.h"
#include "lvgl.h"
#include "app.h"
#include "ui_manager.h"


#define hor_res 128
#define ver_res 64
static void my_flush_cb(lv_display_t * display, const lv_area_t * area, uint8_t * px_map);


static uint8_t buf1[hor_res * ver_res];

int main(void) {
    HAL_Init();
    QF_init();
    bsp_init(); 
    lv_init();   
    lv_tick_set_cb(HAL_GetTick);
    lv_display_t *display1 = lv_display_create(hor_res, ver_res);
    lv_display_set_color_format(display1, LV_COLOR_FORMAT_L8);
    lv_display_set_buffers(display1, buf1, NULL, sizeof(buf1), LV_DISPLAY_RENDER_MODE_FULL);
    lv_display_set_flush_cb(display1, my_flush_cb);
    ui_manager_init();
    app_init();
    // lv_init();   
    // lv_tick_set_cb(HAL_GetTick);
    // lv_display_t *display1 = lv_display_create(hor_res, ver_res);
    // lv_display_set_buffers(display1, buf1, NULL, sizeof(buf1), LV_DISPLAY_RENDER_MODE_PARTIAL);
    // lv_display_set_flush_cb(display1, my_flush_cb);

    // ui_manager_init();

    return QF_run();
}

// 
void QF_onStartup(void) {
}

void QV_onIdle(void) {
    QF_INT_ENABLE();
    lv_timer_handler();
    // QV_CPU_SLEEP();
    // CPU idle.
}

void Q_onError(char const *module, int_t loc) {
    (void)module;
    (void)loc;

    __disable_irq();

    for (;;) {
    }
}


static void my_flush_cb(lv_display_t *display,
                          const lv_area_t *area,
                          uint8_t *px_map)
  {
      for (int32_t y = area->y1; y <= area->y2; ++y) {
          for (int32_t x = area->x1; x <= area->x2; ++x) {
              uint8_t pixel = (*px_map++ >= 128U) ? 1U : 0U;

              ssd1306_basic_gram_write_point(
                  (uint8_t)x, (uint8_t)y, pixel
              );
          }
      }

      ssd1306_basic_gram_update();
      lv_display_flush_ready(display);
  }


