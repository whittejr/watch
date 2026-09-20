/**
* @file    ui_manager.c
* @brief   none
* @version 0.1.0
* @author  Alessandro Davi
* @date    2026-09-19
*/

#include "screens.h"
#include "ui.h"
#include "ui_manager.h"

void ui_manager_init(void) {
    ui_init();
}

void ui_manager_show_watchface(void) {
    loadScreen(SCREEN_ID_WATCHFACE);
}

void ui_manager_show_alarm(void) {
    loadScreen(SCREEN_ID_ALARM);
}

void ui_manager_show_countdown(void) {
    loadScreen(SCREEN_ID_COUNTDOWN);
}

void ui_manager_update_time(uint8_t hours, uint8_t minutes, uint8_t seconds) {
    if (objects.timekeeping_label) {
        char buf[16];
        lv_snprintf(buf, sizeof(buf), "%02u:%02u:%02u", hours, minutes, seconds);
        lv_label_set_text(objects.timekeeping_label, buf);
    }
}

void ui_manager_set_alarm_text(const char *text) {
    if (objects.alarm_label) {
        lv_label_set_text(objects.alarm_label, text);
    }
}