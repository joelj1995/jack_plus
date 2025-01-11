#include "vm.h"

VM vm;

void push(uint16_t word)
{
    *vm.stack_top = word;
    vm.stack_top++; 
}

uint16_t pop()
{
    vm.stack_top--;
    return *vm.stack_top;
}

int execute(Chunk* chunk) {
#define READ_WORD() *vm.ip++;
    vm.chunk = chunk;
    vm.ip = vm.chunk->code;
    vm.stack_top = vm.stack;

    while(true) {
        printf("      ");
        for (uint16_t* slot = vm.stack; slot < vm.stack_top; slot++)
        {
            printf("[%d]", *slot);
        }
        printf("\n");

        if (vm.ip >= chunk->code + chunk->count)  {
            printf("End of input reached\n");
            break;
        }

        uint16_t instruction = READ_WORD();
        switch (instruction)
        {
        case OP_PUSH:
            uint16_t segment = READ_WORD();
            uint16_t index = READ_WORD();
            switch (segment)
            {
                case S_CONSTANT:
                    push(index);
                    break;
                default:
                    printf("Segment %d not implemented.\n", segment);
                    return INTERPRET_RUNTIME_ERROR;
            }
            break;
        case OP_POP:
            break;
        case OP_ADD:
            uint16_t b = pop();
            uint16_t a = pop();
            push(a + b);
            break;
        default:
            printf("Op %d not implemented\n", instruction);
            break;
        }
    }

    return INTERPRET_RUNTIME_ERROR;
#undef READ_WORD
}