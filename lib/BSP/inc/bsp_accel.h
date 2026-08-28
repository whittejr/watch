/**
 * @file bsp_accel.h
 * @brief  none
 * @version 0.1
 * @author Alessandro Davi
 * @date 2026-08-28
 */

#ifndef BSP_ACCEL_H
#define BSP_ACCEL_H

#include <stdint.h>

uint8_t BSP_Accel_Init(void);
void BSP_Accel_FallDetection(void);

#endif // BSP_ACCEL_H