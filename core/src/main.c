/**
* @file    main.c
* @brief   none
* @version 0.1.0
* @author  Alessandro Davi
* @date    2026-09-04
*/

#include "main.h"
#include "bsp.h"
#include "qpc.h"
#include "bsp.h"

int main(void) {
    HAL_Init();
    QF_init();
    bsp_init();    

    return QF_run();
}

// 
void QF_onStartup(void) {
    // Inicialização adicional do QP, se necessária.
}

void QV_onIdle(void) {
    QV_CPU_SLEEP();
    // CPU idle.
    // Pode colocar __WFI() posteriormente.
}

void Q_onError(char const *module, int_t loc) {
    (void)module;
    (void)loc;

    // Erro fatal do QP.
    __disable_irq();

    for (;;) {
    }
}
