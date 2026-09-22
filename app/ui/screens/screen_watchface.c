/**
* @file    screen_watchface.c
* @brief   none
* @version 0.1.0
* @author  Alessandro Davi
* @date    2026-09-19
*/
#include "include/lvgl/core/lv_area.h"
#include "include/lvgl/display/lv_display.h"
#include "include/lvgl/font/lv_symbol_def.h"
#include "lvgl.h"
#include "screen_watchface.h"

static lv_obj_t *screen;
static lv_obj_t *label_time;
static lv_obj_t *label_secs;
static lv_obj_t *label_date;
static lv_obj_t *label_hr;

void screen_watchface_create(void) {
	screen = lv_obj_create(NULL);
	
    // CREATE TOP
	lv_obj_t *top = create_box(screen, 128, 18);	
	lv_obj_align(top, LV_ALIGN_TOP_MID, 0, 1);
    lv_obj_t *center = create_box(screen, 128, 18);	
	lv_obj_align(center, LV_ALIGN_CENTER, 0, 1);
    lv_obj_t *bottom = create_box(screen, 128, 18);	
	lv_obj_align(bottom, LV_ALIGN_BOTTOM_MID, 0, 0);

	label_date = create_label(top, &lv_font_montserrat_10); // filho de *top*
	lv_label_set_text(label_date, "--/--");
	lv_obj_align(label_date, LV_ALIGN_LEFT_MID, 3, 0);

    label_time = create_label(center, &lv_font_montserrat_14);
    lv_label_set_text(label_time, "--:--");
    lv_obj_align(label_time, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t *battery = lv_label_create(top);
    lv_label_set_text(battery, LV_SYMBOL_BATTERY_FULL);
    lv_obj_align(battery, LV_ALIGN_RIGHT_MID, -2, 0);
}

void screen_watchface_show(void) {
    if(screen) {
        lv_screen_load(screen);
        lv_screen_load_anim(screen, LV_SCREEN_LOAD_ANIM_MOVE_LEFT, 300, 0, false);
    }
}

void screen_watchface_update_time(uint8_t hours, uint8_t minutes, uint8_t seconds) {
    if (label_time) {
        char buf[16];
        lv_snprintf(buf, sizeof(buf), "%02u:%02u:%02u", hours, minutes, seconds);
        lv_label_set_text(label_time, buf);
    }
}

void screen_watchface_update_date(uint8_t month, uint16_t year) {
    if (label_date) {
        char buf[16];
        lv_snprintf(buf, sizeof(buf), "%02u/%02u", month, year);
        lv_label_set_text(label_date, buf);
    }
}
