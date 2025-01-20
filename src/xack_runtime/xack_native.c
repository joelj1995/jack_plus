#include <stdio.h>

#include "vm.h"
#include "xack_native.h"

extern VM vm;

NativeFunction native_functions[] = {
    {"Memory.alloc", native_mem_alloc},
    {"", 0}
};

void native_mem_alloc()
{
    int16_t param = pop();
    printf("in native_mem_alloc called with: %d", param);
    push(16);
}