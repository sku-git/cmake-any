#ifndef UTIL_MEM_H
#define	UTIL_MEM_H

#include <string.h>
#include <stdlib.h>

#define UTIL_memcpy memcpy
#define UTIL_memset memset
#define UTIL_memclr(data, len) memset((void*)(data), 0x00, (len))

#define UTIL_atoi    atoi

#endif	/* UTIL_MEM_H */

