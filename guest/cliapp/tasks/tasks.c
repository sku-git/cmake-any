
#include <stdint.h>
#include <stdbool.h>

#include "evt/event_intf.h"

#include "cli/cli.h"
#include "tmr/tmr.h"
#include "util/log.h"


void Event_hTask1ms(EVENT_ID_t evt)
{
    //    li("1ms:%4.4x", evt);
}

void Event_hTask10ms(EVENT_ID_t evt)
{
    //    li("10ms: %4.4x", evt);
    CLI_stateMachine();
}

void Event_hTask100ms(EVENT_ID_t evt)
{
    //    li("100ms: %4.4x", evt);
}

void Event_hTask1sec(EVENT_ID_t evt)
{
    //    li("1s: %4.4x", evt);
}
