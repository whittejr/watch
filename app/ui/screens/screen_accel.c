/**
* @file    screen_accel.c
* @brief   none
* @version 0.1.0
* @author  Alessandro Davi
* @date    2026-09-22
*/

#include "screen_accel.h"
#include "include/lvgl/core/lv_area.h"

static lv_obj_t *screen;
static lv_obj_t *label_xyz;

void screen_accel_create(void) {
	screen = lv_obj_create(NULL);

    lv_obj_t *center = create_box(screen, 128, 25);	
	lv_obj_align(center, LV_ALIGN_CENTER, 0, 1);
    lv_obj_t *bottom = create_box(screen, 128, 18);	
	lv_obj_align(bottom, LV_ALIGN_BOTTOM_MID, 0, 0);

	label_xyz = create_label(center, &lv_font_montserrat_10); // filho de *top*
	lv_label_set_text(label_xyz, "x: -- | y: -- |  z: --");
	lv_obj_align(label_xyz, LV_ALIGN_LEFT_MID, 0, 0);
}

void screen_accel_show(void) {
    if(screen) {
        // lv_screen_load(screen);
        lv_screen_load_anim(screen, LV_SCREEN_LOAD_ANIM_MOVE_LEFT, 300, 0, false);
    }
}

void screen_accel_update_xyz(int16_t x, int16_t y, int16_t z) {
    if (label_xyz) {
        char buf[30];
        lv_snprintf(buf, sizeof(buf), "x: %03" PRId16 " | y: %03" PRId16 " | z: %03" PRId16, x, y, z);
        lv_label_set_text(label_xyz, buf);
    }
}