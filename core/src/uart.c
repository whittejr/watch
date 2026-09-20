/**
* @file    uart.c
* @brief   none
* @version 0.1.0
* @author  Alessandro Davi
* @date    2026-09-04
*/

#include "uart.h"
#include "app.h"
#include "qp.h"
#include "qpc.h"
#include "stm32wbxx_hal_rcc.h"

UART_HandleTypeDef uart1;
static uint8_t rx_char;
static const QEvt modeEvt   = { MODE_SIG,   0U, 0U };
static const QEvt enterEvt  = { ENTER_SIG,  0U, 0U };
static const QEvt toggleEvt = { TOGGLE_SIG, 0U, 0U };

uint8_t uart_init(void) {
    __HAL_RCC_USART1_CLK_ENABLE();
    uart1.Instance = USART1;
    uart1.Init.BaudRate = 115200;
    uart1.Init.WordLength = UART_WORDLENGTH_8B;
    uart1.Init.StopBits = UART_STOPBITS_1;
    uart1.Init.Parity = UART_PARITY_NONE;
    uart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    uart1.Init.Mode = UART_MODE_TX_RX;

    // Enabling USART1 IRQ and set up the priority (NVIC)
    HAL_NVIC_SetPriority(USART1_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
   

    if (HAL_UART_Init(&uart1) != 0) return 1;

    HAL_UART_Receive_IT(&uart1, &rx_char, 1);
    
    return 0;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART1) {
        switch (rx_char) {
            case 'm': // MODE (Set / Avançar modo)
            case 'M':
                QACTIVE_PUBLISH(&modeEvt, &uart1);
                break;

            case 'e': // OK / ENTER
            case 'E':
                QACTIVE_PUBLISH(&enterEvt, &uart1);
                break;

            case 't': // TOGGLE / ABORT
            case 'T':
                QACTIVE_PUBLISH(&toggleEvt, &uart1);
                break;

            default:
                break;
        }

        // Re-arma a recepção do próximo caractere
        HAL_UART_Receive_IT(&uart1, &rx_char, 1);
    }
}