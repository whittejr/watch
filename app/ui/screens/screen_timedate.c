/**
* @file    screen_timedate.c
* @brief   none
* @version 0.1.0
* @author  Alessandro Davi
* @date    2026-09-22
*/

#include "include/lvgl/core/lv_area.h"
#include "include/lvgl/core/lv_obj_pos.h"
#include "screen_accel.h"
#include "screen_timedate.h"
#include "screens/screen_watchface.h"

static lv_obj_t *screen_face;
static lv_obj_t *screen_config;
static lv_obj_t *label_time;
static lv_obj_t *timedate_icon;

void screen_timedate_face_create(void) {
    screen_face = lv_obj_create(NULL);
    
    lv_obj_t *center = create_box(screen_face, 128, 25);	
	lv_obj_align(center, LV_ALIGN_CENTER, 0, 1);
    lv_obj_t *bottom = create_box(screen_face, 128, 18);	
	lv_obj_align(bottom, LV_ALIGN_BOTTOM_MID, 0, 0);
    timedate_icon = lv_label_create(center);
    lv_label_set_text(timedate_icon, LV_SYMBOL_SETTINGS);
    lv_obj_set_style_text_font(timedate_icon, &lv_font_montserrat_18, 0);
    lv_obj_align(timedate_icon, LV_ALIGN_CENTER, -2, 0);
}

void screen_timedate_show(void) {
    if(screen_face) {
        // lv_screen_load(screen_face);
        lv_screen_load_anim(screen_face, LV_SCREEN_LOAD_ANIM_MOVE_LEFT, 300, 0, false);
    }
}

void screen_timedate_config_show(void) {
    if(screen_config) {
        lv_screen_load(screen_config);
    }
}

void screen_timedate_config_create(void) {
    screen_config = lv_obj_create(NULL);

    lv_obj_t *center = create_box(screen_config, 128, 25);	
	lv_obj_align(center, LV_ALIGN_CENTER, 0, 1);
    lv_obj_t *bottom = create_box(screen_config, 128, 18);	
	lv_obj_align(bottom, LV_ALIGN_BOTTOM_MID, 0, 0);

    label_time = create_label(center, &lv_font_montserrat_14);
    lv_label_set_text(label_time, "--:--");
    lv_obj_align(label_time, LV_ALIGN_CENTER, 0, 0);
}

void screen_timedate_update_time(uint8_t hours, uint8_t minutes, uint8_t seconds) {
    if (label_time) {
    char buf[16];
    lv_snprintf(buf, sizeof(buf), "%02u:%02u:%02u", hours, minutes, seconds);
    lv_label_set_text(label_time, buf);
    }
}

void screen_timedate_update_time_config(uint8_t h, uint8_t m, uint8_t s, uint8_t mode, bool blink) {
    if (!label_time) return;

    char buf[16];
    if (!blink) {
        if (mode == 0)      lv_snprintf(buf, sizeof(buf), "__:%02u:%02u", m, s);
        else if (mode == 1) lv_snprintf(buf, sizeof(buf), "%02u:__:%02u", h, s);
        else                lv_snprintf(buf, sizeof(buf), "%02u:%02u:__", h, m);
    } else {
        lv_snprintf(buf, sizeof(buf), "%02u:%02u:%02u", h, m, s);
    }

    lv_label_set_text(label_time, buf);
}
