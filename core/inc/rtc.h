/**
 * @file rtc.h
 * @brief  none
 * @version 0.1
 * @author Alessandro Davi
 * @date 2026-09-01
 */

#ifndef RTC_H
#define RTC_H

#include "main.h"

uint8_t rtc_init(void);
void rtc_get_time(RTC_TimeTypeDef *sTime, RTC_DateTypeDef *sDate);
void rtc_set_time(uint8_t hours, uint8_t minutes, uint8_t seconds);

#endif // RTC_H
