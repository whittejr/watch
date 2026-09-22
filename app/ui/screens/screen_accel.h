/**
 * @file screen_accel.h
 * @brief  none
 * @version 0.1
 * @author Alessandro Davi
 * @date 2026-09-22
 */

#ifndef SCREEN_ACCEL_H
#define SCREEN_ACCEL_H

#include "ui.h"

void screen_accel_create(void);
void screen_accel_show(void);
void screen_accel_update_xyz(int16_t x, int16_t y, int16_t z);

#endif // SCREEN_ACCEL_H
