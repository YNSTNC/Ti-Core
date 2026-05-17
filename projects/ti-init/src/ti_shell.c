#include "ti_shell.h"
#include "ti_log.h"
#include <sel4/sel4.h>

void ti_shell_init(void) {
    ti_log(LOG_INFO, "[Ti-Shell] Modul baslatiliyor...");
}

void ti_shell_run(void) {
    print_str("\n");
    ti_log(LOG_INFO, "--- Ti-Shell Etkilesimli Mod ---");
    ti_log(LOG_WARN, "[Ti-Shell] UART (Klavye) Kesmeleri (IRQ) henuz baglanmadi!");
    ti_log(LOG_INFO, "[Ti-Shell] Otomatik komut testi calistiriliyor...\n");

    // Simüle eilen kullanici girisi 1
    print_str("TiOS> help\n");
    print_str("    Mevcut Komutlar:\n");
    print_str("      help  - Bu mesaji gosterir\n");
    print_str("      info  - Sistem kaynak durumunu gosterir\n");
    print_str("      clear - Ekrani temizler\n\n");

    // Simüle eilen kullanici girisi 2
    print_str("TiOS> info\n");
    print_str("    Sistem         : Ti-Core v0.1.0-alpha\n");
    print_str("    Kullanici Alani: Ti-Init Başlatıcısı\n");
    print_str("    Mimari         : ARM Cortex-A53 (aarch64)\n");
    print_str("    Durum          : Tüm sistemler nominal.\n\n");

    ti_log(LOG_WARN, "[Ti-Shell] Test döngüsü bitti. Sistem beklemeye aliniyor...");
}
