#include <sel4/sel4.h>
#include <stddef.h>
#include "ti_uart.h"
#include "ti_log.h"

// PL011 UART Çipi Kayıtcıları (Registers)
volatile unsigned int *uart_data_reg = NULL; 
volatile unsigned int *uart_flag_reg = NULL;

#define PL011_RXFE (1 << 4) // Receive FIFO empty bayrağı

void ti_uart_init(void) {
    ti_log(LOG_WARN, "[Ti-UART] Donanim adresleri henuz MMU'da haritalanmadi.");
    ti_log(LOG_INFO, "[Ti-UART] QEMU PL011 (0x09000000) hazirliklari tamam.");
}

char ti_uart_getchar(void) {
    if (uart_flag_reg == NULL || uart_data_reg == NULL) {
        seL4_Yield();
        return '\0'; 
    }

    while ((*uart_flag_reg) & PL011_RXFE) {
        seL4_Yield();
    }
    
    return (char)((*uart_data_reg) & 0xFF);
}
