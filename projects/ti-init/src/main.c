#include <sel4/sel4.h>
#include <sel4platsupport/bootinfo.h>
#include "ti_log.h"
#include "ti_cap.h"
#include "ti_shell.h"

#define TICORE_VERSION  "0.1.0-alpha"
#define TIINIT_VERSION  "0.1.0"

static void ti_banner(void)
{
    ti_printf("\n");
    ti_printf("   ████████╗██╗       ██████╗ ██████╗ ██████╗ ███████╗\n");
    ti_printf("   ╚══██╔══╝██║      ██╔════╝██╔═══██╗██╔══██╗██╔════╝\n");
    ti_printf("      ██║   ██║█████╗██║     ██║   ██║██████╔╝█████╗\n");  
    ti_printf("      ██║   ██║╚════╝██║     ██║   ██║██╔══██╗██╔══╝\n");  
    ti_printf("      ██║   ██║      ╚██████╗╚██████╔╝██║  ██║███████╗\n");
    ti_printf("      ╚═╝   ╚═╝       ╚═════╝ ╚═════╝ ╚═╝  ╚═╝╚══════╝\n");
    ti_printf("\n");
    ti_printf("  Ti-Core v%s — Ti-Init v%s\n", TICORE_VERSION, TIINIT_VERSION);
    ti_printf("  \"Your System. Your Decision.\"\n");
    ti_printf("\n");
    ti_printf("  ======================================================\n");
    ti_printf("\n");
}

int main(int argc, char *argv[])
{
    ti_banner();
    ti_printf("[Ti-Init] Baslatiliyor...\n");

    seL4_BootInfo *info = platsupport_get_bootinfo();
    if (!info) {
        ti_printf("[Ti-Init] HATA: Boot bilgisi alinamadi!\n");
        return 1;
    }

    ti_printf("[Ti-Init] Boot bilgisi alindi.\n");
    ti_printf("[Ti-Init] Toplam untyped bellek: %lu eleman.\n",
           (unsigned long)(info->untyped.end - info->untyped.start));

    ti_printf("[Ti-Init] Ti-Cap modulu baslatiliyor...\n");
    ti_cap_init(info);

    ti_printf("[Ti-Init] Servisler baslatiliyor...\n");
    ti_printf("[Ti-Init]   [1/3] Ti-Log   ... hazir\n");
    ti_printf("[Ti-Init]   [2/3] Ti-Cap   ... hazir\n");
    ti_printf("[Ti-Init]   [3/3] Ti-Shell ... hazir (thread olarak basliyor)\n");
    ti_printf("\n");
    ti_printf("[Ti-Init] Ti-Core: All systems nominal. Your system, your decision.\n");
    ti_printf("\n");


    while (1) { seL4_Yield(); }
    return 0;
}
