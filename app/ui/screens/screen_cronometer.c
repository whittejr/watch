/**
* @file    screen_cronometer.c
* @brief   none
* @version 0.1.0
* @author  Alessandro Davi
* @date    2026-09-22
*/

#include "screen_cronometer.h"
#include "include/lvgl/core/lv_area.h"
#include "include/lvgl/font/lv_symbol_def.h"

static lv_obj_t *screen;
static lv_obj_t *label_time;
static lv_obj_t *label_msg;

void screen_cronometer_create(void) {
	screen = lv_obj_create(NULL);

    lv_obj_t *center = create_box(screen, 128, 15);	
	lv_obj_align(center, LV_ALIGN_CENTER, 0, 1);
    // lv_obj_t *bottom = create_box(screen, 128, 18);	
	// lv_obj_align(bottom, LV_ALIGN_BOTTOM_MID, 0, 0);

	// label_msg = create_label(center, &lv_font_montserrat_14); // filho de *top*
	// lv_label_set_text(label_msg, "TEST CRONOMETER");
	// lv_obj_align(label_msg, LV_ALIGN_CENTER, 0, 0);
	lv_obj_t *icon = lv_label_create(center);
    lv_label_set_text(icon, LV_SYMBOL_LOOP);
	lv_obj_set_style_text_font(icon, &lv_font_montserrat_18, 0);
    lv_obj_align(icon, LV_ALIGN_CENTER, 0, 0);
}

void screen_cronometer_show(void) {
    if(screen) {
        // lv_screen_load(screen);
		lv_screen_load_anim(screen, LV_SCREEN_LOAD_ANIM_MOVE_LEFT, 300, 0, false);
    }
}

