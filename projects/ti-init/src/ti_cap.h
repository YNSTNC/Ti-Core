#pragma once
#include <sel4/sel4.h>
#include <sel4/bootinfo.h>
#include <stddef.h>

// TiOS Capability Modülü
void ti_cap_init(seL4_BootInfo *info);

// Basit slot (yuva) ayırma
seL4_CPtr ti_cap_alloc_slot(void);

// GERÇEK SİSTEM: Seçilen boyutta bir Untyped objesi bul
seL4_CPtr ti_cap_get_untyped(size_t size_bits);

// Yeni bir Endpoint Objesi (Süreçler arası iletişim portu) Yaratır
seL4_CPtr ti_cap_create_endpoint(void);

int ti_cap_get_free_slots(void);
