#include <sel4/sel4.h>
#include <stddef.h>
#include "bootstrap.h"
#include "ti_log.h"
#include "ti_shell.h"

int main(int argc, char *argv[])
{
    print_str("\n");
    print_str("  ████████╗██╗     ██████╗  ██████╗ ██████╗ ███████╗\n");
    print_str("  ╚══██╔══╝██║    ██╔════╝ ██╔═══██╗██╔══██╗██╔════╝\n");
    print_str("     ██║   ██║    ██║      ██║   ██║██████╔╝█████╗  \n");
    print_str("     ██║   ██║    ██║      ██║   ██║██╔══██╗██╔══╝  \n");
    print_str("     ██║   ██║    ╚██████╗ ╚██████╔╝██║  ██║███████╗\n");
    print_str("     ╚═╝   ╚═╝     ╚═════╝  ╚═════╝ ╚═╝  ╚═╝╚══════╝\n\n");
    
    print_str("  Ti-Core v0.1.0-alpha - Ti-Init v0.1.0\n");
    print_str("  \"Your System. Your Decision.\"\n");
    print_str("  ================================================\n\n");
    
    ti_log(LOG_INFO, "Kullanici Alani Baslatiliyor...");
    
    seL4_BootInfo *info = NULL; 
    ti_bootstrap(info);
    
    ti_log(LOG_INFO, "VKA ve vspace baslatildi... (simule)");
    ti_log(LOG_INFO, "Endpoint'ler olusturuldu...");
    
    // YENİ EKLEDİĞİMİZ SHELL BAŞLATMA
    ti_shell_init();
    ti_shell_run();
    
    while(1) { seL4_Yield(); }
    return 0;
}
