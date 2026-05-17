#include "ti_cap.h"
#include "ti_log.h"
#include <stddef.h>

static seL4_BootInfo *ti_boot_info = NULL;
static seL4_CPtr next_free_slot = 0;
static seL4_CPtr end_slot = 0;

void ti_cap_init(seL4_BootInfo *info) {
    if (info == NULL) {
        ti_log(LOG_ERR, "[Ti-Cap] HATA: BootInfo nesnesi eksik!");
        return;
    }
    
    ti_boot_info = info;
    next_free_slot = info->empty.start;
    end_slot = info->empty.end;
    
    ti_log(LOG_INFO, "[Ti-Cap] TiOS Capability Yoneticisi aktif.");
    ti_log(LOG_DEBUG, "[Ti-Cap] Toplam bos yetki yuvasi (Slot): %lu", (unsigned long)(end_slot - next_free_slot));
    ti_log(LOG_DEBUG, "[Ti-Cap] Untyped bellek sayisi: %d", info->untyped.end - info->untyped.start);
}

seL4_CPtr ti_cap_alloc_slot(void) {
    if (next_free_slot >= end_slot) {
        ti_log(LOG_ERR, "[Ti-Cap] KRITIK HATA: Bos yetki yuvasi kalmadi!");
        return 0; // Hata
    }
    
    seL4_CPtr allocated = next_free_slot;
    next_free_slot++;
    return allocated;
}

// Çekirdek bize bir sürü ham bellek verdi, uygun boyuttakini bulalım
seL4_CPtr ti_cap_get_untyped(size_t size_bits) {
    if (!ti_boot_info) return 0;

    int untyped_start = ti_boot_info->untyped.start;
    int untyped_end = ti_boot_info->untyped.end;

    for (int i = untyped_start; i < untyped_end; i++) {
        // Obje tablosundan (untypedList) uyumlu belleği bul
        if (ti_boot_info->untypedList[i - untyped_start].sizeBits >= size_bits) {
            // Şimdilik gelişmiş "bölme (retype)" algoritması yazmayacağız,
            // Bulduğumuz ilk yeterli Untyped blogun CPtr pointerını verelim
            return i;
        }
    }
    return 0;
}

// BÜYÜ BURADA: Ham bellekten Gerçek bir Endpoint (Haberleşme objesi) türet (Retype)
seL4_CPtr ti_cap_create_endpoint(void) {
    // Endpoint için 4 baytlık (2^4) bellek yeterlidir, ama standart 16 byte'a yuvarlanabilir
    // seL4_EndpointBits = 4'tür.
    seL4_CPtr untyped = ti_cap_get_untyped(seL4_EndpointBits);
    if (untyped == 0) {
        ti_log(LOG_ERR, "[Ti-Cap] Endpoint icin yeterli Untyped bellek bulunamadi!");
        return 0;
    }

    // Nereye kaydedeceğiz? Root CNode'da yeni bir CSlot (Boş Yuva) alalım
    seL4_CPtr target_slot = ti_cap_alloc_slot();
    
    // Çekirdek (Ti-Core) komutu: Retype.
    // Ham veriyi (untyped) al, seL4_EndpointObject şekline sok ve hedef (target_slot) yuvasına tak
    int err = seL4_Untyped_Retype(untyped,
                                  seL4_EndpointObject, 
                                  seL4_EndpointBits, 
                                  seL4_CapInitThreadCNode, 
                                  0, // root_depth
                                  0, // root_offset
                                  target_slot, 
                                  1); // Tek obje oluştur
                                  
    if (err != seL4_NoError) {
        ti_log(LOG_ERR, "[Ti-Cap] Endpoint yaratilamadi. Hata kodu: %d", err);
        return 0;
    }
    
    ti_log(LOG_INFO, "[Ti-Cap] BASARILI! Gercek Endpoint (CNode Slot: %d) yaratildi.", target_slot);
    return target_slot;
}
