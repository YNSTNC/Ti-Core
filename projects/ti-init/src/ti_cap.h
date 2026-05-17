/*
 * Ti-Cap — Capability and Object Management
 */
#pragma once

#include <sel4/sel4.h>
#include <sel4platsupport/bootinfo.h>
#include <stdint.h>
#include <stddef.h>

void ti_cap_init(seL4_BootInfo *info);

