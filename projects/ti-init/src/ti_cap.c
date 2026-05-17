#include <stdbool.h>
#include "ti_cap.h"
#include "ti_log.h"
#include "ti_shell.h"
#include <sel4/sel4.h>

extern uint64_t ti_shell_stack[1024];

void ti_cap_init(seL4_BootInfo *info) 
{
    if (!info) return;

    ti_printf("[Ti-Cap] 1. CNode icerisindeki bos slot bulunuyor...\n");
    seL4_CPtr shell_tcb_cap = info->empty.start; 

    ti_printf("[Ti-Cap] 2. Untyped bellek listesi taranarak normal RAM araniyor...\n");
    seL4_CPtr untyped_cap = 0;
    
    for (seL4_CPtr cap = info->untyped.start; cap < info->untyped.end; cap++) {
        seL4_UntypedDesc *desc = &info->untypedList[cap - info->untyped.start];
        if (!desc->isDevice && desc->sizeBits >= seL4_TCBBits) {
            untyped_cap = cap;
            ti_printf("[Ti-Cap] -> Uygun normal bellek bulundu: Cap ID %lu\n", (unsigned long)cap);
            break;
        }
    }

    ti_printf("[Ti-Cap] 3. Secilen bellek TCB Objesine donusturuluyor (Retype)...\n");
    seL4_Untyped_Retype(untyped_cap, seL4_TCBObject, seL4_TCBBits,
                        seL4_CapInitThreadCNode, 0, 0, shell_tcb_cap, 1);
    
    ti_printf("[Ti-Cap] 4. TCB Yapilandiriliyor (CSpace ve VSpace yetkileri veriliyor)...\n");
    seL4_TCB_Configure(
        shell_tcb_cap, seL4_CapNull,
        seL4_CapInitThreadCNode, seL4_NilData,
        seL4_CapInitThreadVSpace, seL4_NilData,
        0, seL4_CapNull
    );
    
    /* Onceligini kendisiyle ayni degil, 1 yuksek yapiyoruz ki hemen buna ZIPLASIN! 
       seL4 en yuksek öncelikli threadi derhal çalıştırır. */
    seL4_TCB_SetPriority(shell_tcb_cap, seL4_CapInitThreadTCB, 255);

    ti_printf("[Ti-Cap] 5. Islemci Kaydedicileri (Registers) yaziliyor...\n");
    seL4_UserContext regs = {0};
    size_t reg_count = sizeof(seL4_UserContext) / sizeof(seL4_Word);
    
    seL4_TCB_ReadRegisters(shell_tcb_cap, false, 0, reg_count, &regs);
    regs.pc = (seL4_Word) ti_shell_start; 
    regs.sp = (seL4_Word) (ti_shell_stack + 1024);
    regs.spsr = 0; /* AArch64 EL0 (User Mode) calistirma kosulu! */
    seL4_TCB_WriteRegisters(shell_tcb_cap, false, 0, reg_count, &regs);

    ti_printf("[Ti-Cap] 6. Ti-Shell TCB Tetikleniyor (Resume)!\n");
    seL4_TCB_Resume(shell_tcb_cap);
}
