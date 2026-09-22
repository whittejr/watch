/**
* @file    ui_manager.c
* @brief   none
* @version 0.1.0
* @author  Alessandro Davi
* @date    2026-09-19
*/

#include "ui_manager.h"
#include "ui.h"
#include "screens/screen_watchface.h"
#include "screens/screen_alarm_popup.h"
#include "screens/screen_cronometer.h"
#include "screens/screen_accel.h"
#include "screens/screen_timedate.h"

void ui_manager_init(void) {
    ui_init();
    screen_watchface_create();
    screen_alarm_popup_create();
    screen_cronometer_create();
    screen_accel_create();
    screen_timedate_face_create();
    screen_timedate_config_create();
}

void ui_manager_show_watchface(void) {
    screen_watchface_show();
}

void ui_manager_show_alarm_popup(void) {
    screen_alarm_popup_show();
}

void ui_manager_show_cronometer(void) {
    screen_cronometer_show();
}

void ui_manager_show_accel(void) {
    screen_accel_show();
}

void ui_manager_show_timedate(void) {
    screen_timedate_show();
}

void ui_manager_show_timedate_config(void) {
    screen_timedate_config_show();
}

// watchface
void ui_manager_update_time(uint8_t hours, uint8_t minutes, uint8_t seconds) {
    screen_watchface_update_time(hours, minutes, seconds);
}

void ui_manager_update_date(uint8_t month, uint16_t year) {
    screen_watchface_update_date(month, year);
}
// 

// accel
void ui_manager_update_xyz(int16_t x, int16_t y, int16_t z) {
    screen_accel_update_xyz(x, y, z);
}
// 

void ui_manager_set_alarm_text(const char *text) {
    // if (objects.alarm_label) {
    //     lv_label_set_text(objects.alarm_label, text);
    // }
}

void ui_manager_timedate_update_time(uint8_t hours, uint8_t minutes, uint8_t seconds) {
    screen_timedate_update_time(hours, minutes, seconds);
}

void ui_manager_timedate_update_config(uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t mode, bool blink) {
    screen_timedate_update_time_config(hours, minutes, seconds, mode, blink);
}
