#ifndef UTIL_H
#define	UTIL_H

#include <stdint.h>
#include <stdbool.h>

#include "util_mem.h"

#define UTIL_writeString(str)  UTIL_writeStringToOut((uint8_t *)(str), sizeof(str))
extern void UTIL_writeStringToOut(uint8_t * pucStr, uint16_t len);
bool UTIL_getChar(char * ch);
char UTIL_putChar(uint8_t ch);

#endif	/* UTIL_H */

