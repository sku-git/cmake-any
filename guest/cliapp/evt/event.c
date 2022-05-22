
#include <stdint.h>
#include <stdbool.h>

#include "event_configs.h"
#include "event_intf.h"

#include "util/util_mem.h"

#define EVENT_startCritical()  
#define EVENT_endCritical()    

extern const fp_EventHandler_t EVENT_HANDLER_FUNCS[];

struct EVENT_INFO_s {
    uint8_t evnts[EVENT_BYTES_LEN];
    bool active;
};

typedef struct EVENT_INFO_s EVENT_INFO_t;

struct EVENT_DATA_s {
    EVENT_INFO_t ev;
    EVENT_INFO_t evImm;
};

typedef struct EVENT_DATA_s EVENT_DATA_t;
static EVENT_DATA_t selfEvt;

void Event_init(void)
{
    UTIL_memclr(&selfEvt, sizeof (selfEvt));
    selfEvt.ev.active = false;
    selfEvt.evImm.active = false;
}

static void Event_setGeneric(EVENT_INFO_t *pEv, EVENT_ID_t evt)
{
    uint8_t idByte = EVENT_getIdByte(evt);
    uint8_t idBit = EVENT_getIdBit(evt);

    if (idByte < EVENT_BYTES_LEN) {
        EVENT_startCritical();
        pEv->evnts[idByte] |= idBit;
        pEv->active = true;
        EVENT_endCritical();
    }
}

static void Event_clearGeneric(EVENT_INFO_t *pEv, EVENT_ID_t evt)
{
    uint8_t idByte = EVENT_getIdByte(evt);
    uint8_t idBit = EVENT_getIdBit(evt);

    if (idByte < EVENT_BYTES_LEN) {
        EVENT_startCritical();
        pEv->evnts[idByte] &= (uint8_t) (~idBit);
        pEv->active = true;
        EVENT_endCritical();
    }
}

void Event_set(EVENT_ID_t evt)
{
    Event_setGeneric(&selfEvt.ev, evt);
}

void Event_clear(EVENT_ID_t evt)
{
    Event_clearGeneric(&selfEvt.ev, evt);
}

void Event_setImmediate(EVENT_ID_t evt)
{
    Event_setGeneric(&selfEvt.evImm, evt);
}

void Event_clearImmediate(EVENT_ID_t evt)
{
    Event_clearGeneric(&selfEvt.evImm, evt);
}

static void Event_processEvents(uint8_t evtByte, uint8_t bytePos)
{
    uint8_t i;
    for (i = 0U; i < 8U; i++) {
        uint8_t bitPos = (0x01U << i);
        if ((bitPos & evtByte) != 0x00U) {
            uint8_t functionId = (bytePos * 8U) + i;
            if (EVENT_HANDLER_FUNCS[functionId] != NULL) {
                EVENT_HANDLER_FUNCS[functionId](EVENT_createId(bytePos, i));
            }
        }
    }
}

static void Event_handleEvents(EVENT_INFO_t *pEv)
{
    uint8_t i;
    uint8_t evnts[EVENT_BYTES_LEN];

    EVENT_startCritical();
    for (i = 0x00U; i < EVENT_BYTES_LEN; i++) {
        evnts[i] = pEv->evnts[i];
        pEv->evnts[i] = 0x00U;
    }
    pEv->active = false;
    EVENT_endCritical();

    for (i = 0x00U; i < EVENT_BYTES_LEN; i++) {
        if (evnts[i] != 0x00U) {
            Event_processEvents(evnts[i], i);
        }
    }
}

void Event_process(void)
{

    if (selfEvt.ev.active == true) {

        Event_handleEvents(&selfEvt.ev);
    }

    while (selfEvt.evImm.active == true) {
        Event_handleEvents(&selfEvt.evImm);
    }
}

