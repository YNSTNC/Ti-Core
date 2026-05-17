#pragma once

// QEMU ARM Virt platformu için UART0 (PL011) Donanım Adresi
#define UART0_PHYS_BASE 0x09000000 

void ti_uart_init(void);
char ti_uart_getchar(void);
