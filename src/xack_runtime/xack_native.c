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
    int16_t size = pop();
    int result = vm.free;
    vm.free = vm.free + size;
    push(result);
}