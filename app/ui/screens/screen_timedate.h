/**
 * @file screen_timedate.h
 * @brief  none
 * @version 0.1
 * @author Alessandro Davi
 * @date 2026-09-22
 */

#ifndef SCREEN_TIMEDATE_H
#define SCREEN_TIMEDATE_H

#include "ui.h"

void screen_timedate_face_create(void);
void screen_timedate_config_create(void);
void screen_timedate_show(void);
void screen_timedate_config_show(void);
void screen_timedate_update_time(uint8_t hours, uint8_t minutes, uint8_t seconds);
void screen_timedate_update_time_config(uint8_t h, uint8_t m, uint8_t s, uint8_t mode, bool blink);

#endif // SCREEN_TIMEDATE_H
