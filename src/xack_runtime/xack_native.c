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
    int16_t result = vm.ram[address];
    push(result);
}

void native_mem_poke()
{
    int16_t value = pop();
    uint16_t address = pop();
    vm.ram[address] = value;
    push(0);
}

void native_mem_dealloc()
{
    uint16_t address = pop();
    push(0);
}

NativeFunction native_functions[] = {
    {"Memory.alloc", native_mem_alloc},
    {"Memory.peek", native_mem_peek},
    {"Memory.poke", native_mem_poke},
    {"Memory.deAlloc", native_mem_dealloc},
    {"", 0}
};

