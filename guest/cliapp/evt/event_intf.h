#ifndef EVENT_INTF_H
#define	EVENT_INTF_H

#include <stdint.h>
#include <stdbool.h>

#include "event_configs.h"

void Event_set(EVENT_ID_t evt);
void Event_clear(EVENT_ID_t evt);

void Event_setImmediate(EVENT_ID_t evt);
void Event_clearImmediate(EVENT_ID_t evt);

typedef void(*fp_EventHandler_t)(EVENT_ID_t evt);

#endif	/* EVENT_INTF_H */

