/*
 * Ti-Init — Bootstrap ve Capability Yönetimi
 */
#pragma once

#include <sel4/sel4.h>
#include <sel4/bootinfo.h>

/**
 * ti_bootstrap: Baslangic yetkilerini ve gerekli bellek yapisini kurar.
 *
 * @param info seL4'ten alinan boot bilgi yapisi
 * @return 0 basarili, sifirdan farkli ise hata
 */
int ti_bootstrap(seL4_BootInfo *info);
