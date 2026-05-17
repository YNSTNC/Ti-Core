#include "ti_log.h"
#include <sel4/sel4.h>
#include <stdarg.h>
#include <stdio.h>

void print_str(const char *str) {
    while (*str) {
        seL4_DebugPutChar(*str);
        str++;
    }
}

void ti_log(ti_log_level_t level, const char *fmt, ...) {
    char buffer[256];
    va_list args;

    switch(level) {
        case LOG_INFO:  print_str("[Ti-Init][INFO] "); break;
        case LOG_WARN:  print_str("[Ti-Init][WARN] "); break;
        case LOG_ERR:   print_str("[Ti-Init][ERR]  "); break;
        case LOG_DEBUG: print_str("[Ti-Init][DBG]  "); break;
    }

    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    print_str(buffer);
    print_str("\n");
}
