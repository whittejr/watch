#ifndef BSP_H
#define BSP_H

#include "qpc.h"

enum WatchSignals {
    ENTER_SIG = Q_USER_SIG,
    MODE_SIG,
    BACK_SIG,
    TOGGLE_SIG,
    TICK_SIG,
    TIMEOUT_SIG,
    MAX_SIG
};

extern QActive * const AO_Watch;
void Watch_ctor(void);

#endif // BSP_H