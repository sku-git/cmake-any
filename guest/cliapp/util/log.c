
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>

#include "util_mem.h"
#include "util.h"

#define LOG_SIZE  128

struct LOG_DATA_s {
    char buffer[LOG_SIZE];
    char *buffPtr;
    uint16_t logLen;
};

typedef struct LOG_DATA_s LOG_DATA_t;

static LOG_DATA_t selfLog;

void Log_init(void)
{
    UTIL_memclr(&selfLog, sizeof (selfLog));
}

char buffer[80];

void Log_initBuff(char ch)
{
    UTIL_memclr(&selfLog.buffer, LOG_SIZE);
    selfLog.buffPtr = selfLog.buffer;
    selfLog.logLen = 0x00U;
    
    if (ch != '\0') {
        *selfLog.buffPtr = ch;
        selfLog.buffPtr++;
        *selfLog.buffPtr = ':';
        selfLog.buffPtr++;
        selfLog.logLen = 2U;
    }
}

void Log_vspfunc(char *format, ...)
{
    va_list aptr;

    va_start(aptr, format);
    selfLog.logLen += vsprintf(selfLog.buffPtr, format, aptr);
    va_end(aptr);
}

void Log_data(void)
{
    UTIL_writeStringToOut((uint8_t *) selfLog.buffer, selfLog.logLen);
}

void Log_char(uint8_t ch)
{
    UTIL_putChar(ch);
}

void Log_clearScreen(void)
{
    UTIL_memclr(&selfLog.buffer, LOG_SIZE);
    selfLog.buffer[0] = 0x1B;
    selfLog.buffer[1] = 0x5B;
    selfLog.buffer[2] = 0x32;
    selfLog.buffer[3] = 'J';
    selfLog.buffer[4] = 0x00;
    selfLog.logLen = 5;
    Log_data();

    // selfLog.buffer[0] = 0x1B;
    // selfLog.buffer[1] = 0x5B;
    selfLog.buffer[2] = 'H';
    selfLog.buffer[3] = 0x00;
    selfLog.logLen = 4;
    Log_data();
}
