/**
* @file    screen_alarm_popup.c
* @brief   none
* @version 0.1.0
* @author  Alessandro Davi
* @date    2026-09-19
*/

/**
* @file    screen_watchface.c
* @brief   none
* @version 0.1.0
* @author  Alessandro Davi
* @date    2026-09-19
*/
#include "include/lvgl/font/lv_symbol_def.h"
#include "lvgl.h"
#include "screen_watchface.h"

static lv_obj_t *screen;
static lv_obj_t *label_time;
static lv_obj_t *label_msg;

void screen_alarm_popup_create(void) {
	screen = lv_obj_create(NULL);

    lv_obj_t *top = create_box(screen, 128, 18);	
	lv_obj_align(top, LV_ALIGN_TOP_MID, 0, 1);
    lv_obj_t *center = create_box(screen, 128, 25);	
	lv_obj_align(center, LV_ALIGN_CENTER, 0, 1);
    lv_obj_t *bottom = create_box(screen, 128, 18);	
	lv_obj_align(bottom, LV_ALIGN_BOTTOM_MID, 0, 0);

	label_msg = create_label(center, &lv_font_montserrat_14); // filho de *top*
	lv_label_set_text(label_msg, "TOMAR REMEDIO");
	lv_obj_align(label_msg, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t *battery = lv_label_create(top);
    lv_label_set_text(battery, LV_SYMBOL_EYE_OPEN);
    lv_obj_align(battery, LV_ALIGN_RIGHT_MID, -2, 0);
}

void screen_alarm_popup_show(void) {
    if(screen) {
        lv_screen_load(screen);
    }
}
