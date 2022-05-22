
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "event_intf.h"


extern void Event_hTask1ms(EVENT_ID_t evt);
extern void Event_hTask10ms(EVENT_ID_t evt);
extern void Event_hTask100ms(EVENT_ID_t evt);
extern void Event_hTask1sec(EVENT_ID_t evt);

const fp_EventHandler_t EVENT_HANDLER_FUNCS[] = {
    Event_hTask1ms,
    Event_hTask10ms,
    Event_hTask100ms,
    Event_hTask1sec,
    NULL,
    NULL,
    NULL,
    NULL,
    
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,

    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};
