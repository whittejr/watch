#include "qpc.h"
#include "bsp.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h> 

Q_DEFINE_THIS_FILE

static QEvtPtr watch_queue[20]; 

// Memória obrigatória para a funcionalidade de "Subscribe" (que o relógio usa para ler teclas)
static QSubscrList subscrSto[MAX_SIG];

int main(int argc, char *argv[]) {
    // Desativa o buffer do printf no Windows para vermos as mensagens instantaneamente!
    setvbuf(stdout, NULL, _IONBF, 0);

    printf("--- Simulacao do ao_watch no PC (QP/C) ---\n");
    printf("Controles do teclado: [M]=MODE, [T]=TOGGLE, [E]=ENTER, [ESC]=Sair\n\n");

    QF_init();
    
    // Inicializa o dicionário de Pub/Sub do framework antes de iniciar o relógio!
    QF_psInit(subscrSto, Q_DIM(subscrSto));

    Watch_ctor();
    
    QActive_start(AO_Watch, 
                  1U, 
                  watch_queue, Q_DIM(watch_queue), 
                  (void *)0, 0U, 
                  (QEvt *)0);

    return QF_run(); 
}

void QV_onIdle(void) {
    if (_kbhit()) { 
        char c = _getch(); 
        
        static QEvt const modeEvt   = { MODE_SIG, 0U, 0U };
        static QEvt const toggleEvt = { TOGGLE_SIG, 0U, 0U };
        static QEvt const enterEvt  = { ENTER_SIG, 0U, 0U };

        if      (c == 'm' || c == 'M') { printf("\n[DEBUG] Enviando MODE...\n"); QACTIVE_POST(AO_Watch, &modeEvt,   0); }
        else if (c == 't' || c == 'T') { printf("\n[DEBUG] Enviando TOGGLE...\n"); QACTIVE_POST(AO_Watch, &toggleEvt, 0); }
        else if (c == 'e' || c == 'E') { printf("\n[DEBUG] Enviando ENTER...\n"); QACTIVE_POST(AO_Watch, &enterEvt,  0); }
        else if (c == 27) /* ESC */    { printf("\nSaindo...\n"); exit(0); }
    }
}

// Callbacks obrigatórios do QP/C
void QF_onStartup(void) {
    // Inicialização do hardware (vazio no PC)
}

void QF_onCleanup(void) {
    // Limpeza (vazio no PC)
}

void QF_onClockTick(void) {
    // Essa função é chamada por uma thread interna do Windows no port win32-qv
    // Serve para atualizar os temporizadores do relógio
    QTIMEEVT_TICK_X(0U, (void *)0);
}

void Q_onAssert(char const * const module, int loc) {
    fprintf(stderr, "Crash interno no modulo %s:%d\n", module, loc);
    exit(-1);
}