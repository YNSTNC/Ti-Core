#include "bootstrap.h"
#include <stddef.h>

int ti_bootstrap(seL4_BootInfo *info)
{
    if (info == NULL) {
        return -1;
    }
    return 0;
}
