/**
 * @file ui_manager.h
 * @brief  none
 * @version 0.1
 * @author Alessandro Davi
 * @date 2026-09-19
 */

#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <stdbool.h>
#include <stdint.h>

void ui_manager_init(void);

void ui_manager_show_watchface(void);
void ui_manager_show_alarm(void);
void ui_manager_show_countdown(void);
void ui_manager_show_accel(void);
void ui_manager_show_timedate(void);
void ui_manager_show_timedate_config(void);

void ui_manager_update_time(uint8_t hours, uint8_t minutes, uint8_t seconds);
void ui_manager_update_date(uint8_t month, uint16_t year);

void ui_manager_set_alarm_text(const char *text);
void ui_manager_show_alarm_popup(void);

void ui_manager_update_xyz(int16_t x, int16_t y, int16_t z);

void ui_manager_timedate_update_time(uint8_t hours, uint8_t minutes, uint8_t seconds);
void ui_manager_timedate_update_config(uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t mode, bool blink);



#endif // UI_MANAGER_H
