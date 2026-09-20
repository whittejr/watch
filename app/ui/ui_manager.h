/**
 * @file ui_manager.h
 * @brief  none
 * @version 0.1
 * @author Alessandro Davi
 * @date 2026-09-19
 */

#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <stdint.h>

void ui_manager_init(void);

void ui_manager_show_watchface(void);
void ui_manager_show_alarm(void);

void ui_manager_update_time(uint8_t hours, uint8_t minutes, uint8_t seconds);
void ui_manager_set_alarm_text(const char *text);

#endif // UI_MANAGER_H