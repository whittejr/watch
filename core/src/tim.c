/**
* @file    tim.c
* @brief   none
* @version 0.1.0
* @author  Alessandro Davi
* @date    2026-08-28
*/

#include "tim.h"

LPTIM_HandleTypeDef hlptim1;

void tim1_init(void) {
    hlptim1.Instance = LPTIM1;
    hlptim1.Init.Clock.Source = LPTIM_CLOCKSOURCE_APBCLOCK_LPOSC; 
    hlptim1.Init.Clock.Prescaler = LPTIM_PRESCALER_DIV4; 
    hlptim1.Init.Trigger.Source = LPTIM_TRIGSOURCE_SOFTWARE;
    hlptim1.Init.OutputPolarity = LPTIM_OUTPUTPOLARITY_HIGH;
    hlptim1.Init.UpdateMode = LPTIM_UPDATE_IMMEDIATE;
    hlptim1.Init.CounterSource = LPTIM_COUNTERSOURCE_INTERNAL;

    if (HAL_LPTIM_Init(&hlptim1) == HAL_OK) {
        HAL_LPTIM_PWM_Start(&hlptim1, 16666, 8333);
    }
}
