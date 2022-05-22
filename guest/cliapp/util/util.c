
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>


bool UTIL_getChar(char* ch)
{
    bool retval = false;

    int c = getchar();
    *ch = (char)c;
    retval = true;

    return retval;
}

void UTIL_putChar(uint8_t ch)
{
    putchar(ch);
}

void UTIL_writeStringToOut(uint8_t* pucStr, uint16_t len)
{
    while (len--) {
        UTIL_putChar(*pucStr++);
    }
}
