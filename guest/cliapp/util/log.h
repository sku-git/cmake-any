
#ifndef LOG_H
#define	LOG_H

#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

void Log_init(void);

void Log_initBuff(char ch);
void Log_vspfunc(char *format, ...);
void Log_data(void);
void Log_clearScreen(void);
void Log_char(uint8_t ch);

// Carriage return only
//#define Log_appendNewLine(format)  format "\r"

// New line and carriage return 
#define Log_appendNewLine(format)  format "\r\n"

//Log information on a new line
#define li(format, ...) do { Log_initBuff('i'); Log_vspfunc(Log_appendNewLine(format), __VA_ARGS__); Log_data();}while(0)
//Log warning on a new line
#define lw(format, ...) do { Log_initBuff('w'); Log_vspfunc(Log_appendNewLine(format), __VA_ARGS__); Log_data();}while(0)
//Log error on a new line
#define le(format, ...) do { Log_initBuff('e'); Log_vspfunc(Log_appendNewLine(format), __VA_ARGS__); Log_data();}while(0)

//Log print string on a new line
#define lp(format, ...) do { Log_initBuff('\0'); Log_vspfunc(Log_appendNewLine(format), __VA_ARGS__); Log_data();}while(0)
//Log a string as information
#define lis(str) li("%s", (str))
//Log a string 
#define lps(str) lp("%s", (str))
//Log new line
#define lnl()  li("")
//Log horizontal line
#define lhr()  lps("-----------------------------------------------------------")

// Print char
#define lc(ch)  Log_char((ch))

#endif	/* LOG_H */

