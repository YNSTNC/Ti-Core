#include "bootstrap.h"
#include "ti_log.h"
#include "ti_cap.h"
#include <stddef.h>

int ti_bootstrap(seL4_BootInfo *info)
{
    if (info == NULL) return -1;
    
    ti_log(LOG_INFO, "[TiOS-Bootstrap] Acik Kaynak Ti-Core ile baglanti kuruldu.");
    
    // 1. Yetki ve Bellek analizcisini kur
    ti_cap_init(info);
    
    // 2. GERÇEK MÜHENDİSLİK: Simülasyon değil, çekirdekteki ilk objemizi yaratalım!
    seL4_CPtr my_first_endpoint = ti_cap_create_endpoint();
    if (my_first_endpoint != 0) {
        ti_log(LOG_INFO, "[TiOS-Bootstrap] Sistem ilk iletisim portunu donanimsal olarak acti!");
    } else {
        ti_log(LOG_ERR, "[TiOS-Bootstrap] Cekirdek endpoint protokolu reddetti!");
    }

    return 0;
}
