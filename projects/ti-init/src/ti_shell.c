#include "ti_shell.h"
#include <sel4/sel4.h>
#include "ti_log.h"

/* Shell stack alani */
__attribute__((aligned(16))) uint64_t ti_shell_stack[1024];

void ti_shell_start(void)
{
    const char *msg = "[Ti-Shell] Shell thread klavye dinlemeye hazir!\n";
    for (int i = 0; msg[i] != '\0'; i++) seL4_DebugPutChar(msg[i]);

    char cmd_buffer[128];
    int buf_idx = 0;

    while (1) {
        ti_printf("TiOS> ");
        buf_idx = 0;

        while (1) {
            /* 
             * Kernel artik GetChar desteklemiyor. Donanim baglantisi (IRQ/UART Endpoint)
             * henuz Ti-Cap ile VSpace'e haritalanmadigi icin su anlik klavye okunamaz.
             * QEMU icinde sonsuz dongude (Idle process gibi) akmasin diye yield yapiyoruz.
             * 
             * NOT: Burada platsupport'un io_ops ve character server altyapisi kurulacak!
             */
             
            /* Gercek IO okuma kismi bir sonraki commitin hardware map isidir:
             * int c = platsupport_getchar();
             * (Simdilik simule edip cikiyoruz)
             */
             
            seL4_Yield();
        }
        
    }
}
