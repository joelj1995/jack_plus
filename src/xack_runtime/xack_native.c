#include <stdio.h>

#include "vm.h"
#include "xack_native.h"

extern VM vm;

typedef enum {
    SF_MAXLENGTH,
    SF_CURLENGTH,
    SF_STR
} StringFields;

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

void native_array_new()
{
    native_mem_alloc();
}

void native_array_dispose()
{
    native_mem_dealloc();
}

void native_string_new()
{
    uint16_t mem = pop();
    uint16_t maxLength = pop();
    vm.ram[mem + SF_CURLENGTH] = 0;
    vm.ram[mem + SF_MAXLENGTH] = maxLength;
    if (maxLength > 0) 
    {
        push(maxLength);
        native_mem_alloc();
        vm.ram[mem + SF_STR] = pop();
    }
    push(mem);
}

void native_string_appendchar()
{
    uint16_t _this = pop();
    uint16_t c = pop();
    printf("Appending %c at memory location %d", c, vm.ram[_this+SF_CURLENGTH] + vm.ram[_this+SF_STR]);
    uint16_t stringBase = vm.ram[_this+SF_CURLENGTH] + vm.ram[_this+SF_STR];
    vm.ram[_this+SF_CURLENGTH] += 1;
    vm.ram[stringBase] = c;
    push(_this);
}

NativeFunction native_functions[] = {
    {"Memory.alloc", native_mem_alloc},
    {"Memory.peek", native_mem_peek},
    {"Memory.poke", native_mem_poke},
    {"Memory.deAlloc", native_mem_dealloc},
    {"Array.new", native_array_new},
    {"Array.dispose", native_array_dispose},
    {"String.new", native_string_new},
    {"String.appendChar", native_string_appendchar},
    {"", 0}
};

