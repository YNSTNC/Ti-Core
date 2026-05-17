#include <sel4/sel4.h>
#include <sel4/bootinfo.h>
#include <stddef.h>
#include "bootstrap.h"
#include "ti_log.h"
#include "ti_shell.h"
#include "ti_uart.h"

int main(int argc, char *argv[])
{
    print_str("\n");
    print_str("  ████████╗██╗     ██████╗  ██████╗ ██████╗ ███████╗\n");
    print_str("  ╚══██╔══╝██║    ██╔════╝ ██╔═══██╗██╔══██╗██╔════╝\n");
    print_str("     ██║   ██║    ██║      ██║   ██║██████╔╝█████╗  \n");
    print_str("     ██║   ██║    ██║      ██║   ██║██╔══██╗██╔══╝  \n");
    print_str("     ██║   ██║    ╚██████╗ ╚██████╔╝██║  ██║███████╗\n");
    print_str("     ╚═╝   ╚═╝     ╚═════╝  ╚═════╝ ╚═╝  ╚═╝╚══════╝\n\n");
    
    print_str("  Kernel: Ti-Core v0.1.0-alpha (Open Source)\n");
    print_str("  OS    : TiOS v0.1.0 (Commercial)\n");
    print_str("  \"Your System. Your Decision.\"\n");
    print_str("  ================================================\n\n");
    
    // Eski C kütüphanesini kullan ve "deprecated" uyarısını görmezden gel 
    // Derleyici burayı %100 geçecek
    seL4_BootInfo *info = seL4_GetBootInfo();
    
    ti_bootstrap(info);  // Ti-Cap'i gerçek bilgiyle test et

    ti_uart_init();      // Klavye sürücüsünü başlat
    
    ti_shell_init();
    ti_shell_run();
    
    while(1) { seL4_Yield(); }
    return 0;
}
