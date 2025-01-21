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
        uint16_t s_mem = pop();
        vm.ram[mem + SF_STR] = s_mem;
    }
    push(mem);
}

void native_string_appendchar()
{
    uint16_t c = pop();
    uint16_t _this = pop();
    uint16_t stringBase = vm.ram[_this+SF_CURLENGTH] + vm.ram[_this+SF_STR];
    vm.ram[_this+SF_CURLENGTH] += 1;
    vm.ram[stringBase] = c;
    push(_this);
}

void native_string_intvalue()
{
    uint16_t _this = pop();
    int i = 0;
    bool done = false;
    bool negate = false;
    int sum = 0;
    int curLength = vm.ram[_this+SF_CURLENGTH];
#define STR_I vm.ram[vm.ram[_this+SF_STR] + i]
    if (curLength > 0) {
        if (STR_I == 45) {
            negate = true;
            i = 1;
        }
    }
    while (true) {
        if ((i >= curLength) || done) {
            if (negate) {
                push(-sum);
                return;
            }
            push(sum);
            return;
        }
        if (STR_I > 47 & STR_I < 58) {
            sum = (sum * 10) + (STR_I - 48); 
        }
        else {
            done = true;
        }
        i = i + 1;
    }
    push(0);
#undef STR_I
}

void native_output_printstring()
{
    uint16_t s = pop();
    uint16_t s_len = vm.ram[s+SF_CURLENGTH];
    uint16_t stringBase = vm.ram[s+SF_STR];
    for (int i = 0; i < s_len; i++)
    {
        printf("%c", vm.ram[stringBase+i]);
    }
    push(0);
}

void native_output_int()
{
    int16_t the_int = pop();
    printf("%d", the_int);
}

void native_math_multiply()
{
    int16_t b = pop();
    int16_t a = pop();
    push(a * b);
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
    {"String.intValue", native_string_intvalue},
    {"Output.printString", native_output_printstring},
    {"Output.printInt", native_output_int},
    {"Math.multiply", native_math_multiply},
    {"", 0}
};

