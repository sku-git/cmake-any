
#include <stdint.h>
#include <stdbool.h>
#include "util/util_mem.h"
#include "evt/event_intf.h"
#include "util/log.h"

#define TMR_COUNT_1ms  10U
#define TMR_COUNT_10ms  10U
#define TMR_COUNT_100ms  10U
#define TMR_COUNT_1000ms  10U

#define TMR_checkCount(count, val)   (((count) % (val)) == 0)

struct TMR_DATA_s {
    uint8_t us100Ctr;
    uint16_t msCtr;
    uint16_t ms10Ctr;
    uint16_t ms100Ctr;
    uint16_t secCtr;
};

typedef struct TMR_DATA_s TMR_DATA_t;

static TMR_DATA_t selfTmr;

void Tmr_init(void)
{
    UTIL_memclr(&selfTmr, sizeof (selfTmr));
}

/* The ISR timer 1 callback routine. Called after every 100us */
void TMR1_CallBack(void)
{
    selfTmr.us100Ctr++;
    if (selfTmr.us100Ctr >= TMR_COUNT_1ms) {
        //1ms event
        selfTmr.msCtr++;
        selfTmr.us100Ctr -= TMR_COUNT_1ms;
        Event_set(EVENT_ID_TMR_1ms);
        if (TMR_checkCount(selfTmr.msCtr, TMR_COUNT_10ms)) {
            //10ms event
            Event_set(EVENT_ID_TMR_10ms);
        }
    }
}

/*Coarser timers handled in Non ISR task functions */
void TMR_updateTimers(void)
{
    selfTmr.ms10Ctr++;
    if (TMR_checkCount(selfTmr.ms10Ctr, TMR_COUNT_100ms)) {
        //100ms event
        selfTmr.ms100Ctr++;
        Event_setImmediate(EVENT_ID_TMR_100ms);
        if (TMR_checkCount(selfTmr.ms100Ctr, TMR_COUNT_1000ms)) {
            //1sec event
            selfTmr.secCtr++;
            Event_setImmediate(EVENT_ID_TMR_1sec);
        }
    }
}
