#include <stdio.h>

#include "vm.h"
#include "xack_native.h"

extern VM vm;

void native_mem_alloc()
{
    int16_t size = pop();
    int result = vm.free;
    vm.free = vm.free + size;
    push(result);
}

void native_mem_peek()
{
    uint16_t address = pop();
    push(vm.ram[address]);
}

NativeFunction native_functions[] = {
    {"Memory.alloc", native_mem_alloc},
    {"Memory.peek", native_mem_peek},
    {"", 0}
};

