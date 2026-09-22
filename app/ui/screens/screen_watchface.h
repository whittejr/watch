/**
 * @file screen_watchface.h
 * @brief  none
 * @version 0.1
 * @author Alessandro Davi
 * @date 2026-09-22
 */

#ifndef SCREEN_WATCHFACE_H
#define SCREEN_WATCHFACE_H

#include <stdint.h>
#include "ui.h"

void screen_watchface_create(void);
void screen_watchface_update_time(uint8_t hours, uint8_t minutes, uint8_t seconds);
void screen_watchface_update_date(uint8_t month, uint16_t year);
void screen_watchface_show(void);

#endif // SCREEN_WATCHFACE_H
