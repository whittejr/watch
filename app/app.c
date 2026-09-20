/**
* @file    app.c
* @brief   none
* @version 0.1.0
* @author  Alessandro Davi
* @date    2026-09-19
*/

#include "app.h"

#define GUIMGR_QUEUE_LEN 16U
static QEvt const *guimgr_queue[GUIMGR_QUEUE_LEN];
static QEvt const *alarmmgr_queue[16];
static QEvt const *notifmgr_queue[8];
static MedicineAlarmEvt event_pool[10];

void app_init(void) {
    // initialize publish-subscribe
    static QSubscrList subscrSto[MAX_PUB_SIG];
    QActive_psInit(subscrSto, Q_DIM(subscrSto));

    QF_poolInit(
        event_pool,
        sizeof(event_pool),
        sizeof(event_pool[0])
    );

    // instantiate and start AOs...
    GuiMgr_ctor();
    QActive_start(AO_GuiMgr, 1U, guimgr_queue, Q_DIM(guimgr_queue), NULL, 0U, NULL);

    AlarmMgr_ctor();
    QActive_start(AO_AlarmMgr, 2U, alarmmgr_queue, Q_DIM(alarmmgr_queue), NULL, 0U, NULL);

    NotificationMgr_ctor();
    QActive_start(AO_NotificationMgr, 3U, notifmgr_queue, Q_DIM(notifmgr_queue), NULL, 0U, NULL);
}