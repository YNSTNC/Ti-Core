#pragma once

typedef enum {
    LOG_INFO,
    LOG_WARN,
    LOG_ERR,
    LOG_DEBUG
} ti_log_level_t;

void ti_log(ti_log_level_t level, const char *fmt, ...);
void print_str(const char *str); // Raw string yazdirmak icin (Afiş gibi)
