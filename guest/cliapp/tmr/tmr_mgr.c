
#include <stdint.h>
#include <stdbool.h>
#include "util/util_mem.h"


struct TMR_MGR_DATA_s{
    uint8_t test;
};

typedef struct TMR_MGR_DATA_s TMR_MGR_DATA_t;

static TMR_MGR_DATA_t selfTmrMgr;

void Tmr_Mgr_init(void)
{
    UTIL_memclr(&selfTmrMgr, sizeof(selfTmrMgr));
}

