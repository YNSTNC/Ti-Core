#include "ti_log.h"
#include <sel4/sel4.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>

void ti_printf(const char *fmt, ...)
{
    char buf[512];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);

    for (int i = 0; buf[i] != '\0'; i++) {
        seL4_DebugPutChar(buf[i]);
    }
}
