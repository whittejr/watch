/**
* @file    it.c
* @brief   none
* @version 0.1.0
* @author  Alessandro Davi
* @date    2026-04-01
*/

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "it.h"
#include "qp.h"
#include "stm32wbxx_hal.h"
#include "rtc.h"

extern UART_HandleTypeDef uart1;

void SysTick_Handler(void) {
    HAL_IncTick();

    QTIMEEVT_TICK_X(0U, &l_tick);
}

void USART1_IRQHandler(void) {
    HAL_UART_IRQHandler(&uart1);
}

void RTC_Alarm_IRQHandler(void) {
        HAL_RTC_AlarmIRQHandler(&hrtc);
}
