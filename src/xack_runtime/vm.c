#include "vm.h"

VM vm;

void push(int16_t word)
{
    *vm.stack_top = word;
    vm.stack_top++; 
}

int16_t pop()
{
    vm.stack_top--;
    return *vm.stack_top;
}

int execute(Chunk* chunk) {
#define READ_WORD() *vm.ip++;
    vm.chunk = chunk;
    vm.ip = vm.chunk->code;
    vm.stack_top = vm.stack;

    for (int i = 0; i < MEMORY_LENGTH; i++)
    {
        vm.ram[i] = 0;
    }

    while(true) {
        printf("      ");
        for (int16_t* slot = vm.stack; slot < vm.stack_top; slot++)
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
        {
            uint16_t segment = READ_WORD();
            uint16_t index = READ_WORD();
            switch (segment)
            {
                case S_LOCAL:
                {
                    uint16_t base = vm.ram[1];
                    push(*(vm.ram + base + index));
                    break;
                }
                case S_ARGUMENT:
                {
                    uint16_t base = vm.ram[2];
                    push(*(vm.ram + base + index));
                    break;
                }
                case S_THIS:
                {
                    uint16_t base = vm.ram[3];
                    push(*(vm.ram + base + index));
                    break;
                }
                case S_THAT:
                {
                    uint16_t base = vm.ram[4];
                    push(*(vm.ram + base + index));
                    break;
                }
                case S_TEMP:
                {
                    push(vm.ram[5 + index]);
                    break;
                }
                case S_CONSTANT:
                {
                    push(index);
                    break;
                }
                default:
                {
                    printf("Segment %d not implemented.\n", segment);
                    return INTERPRET_RUNTIME_ERROR;
                }
            }
            break;
        }
        case OP_POP:
        {
            uint16_t segment = READ_WORD();
            uint16_t index = READ_WORD();
            switch (segment)
            {
                case S_LOCAL:
                {
                    uint16_t base = vm.ram[1];
                    int16_t val = pop();
                    *(vm.ram + base + index) = val;
                    break;
                }

                case S_ARGUMENT:
                {
                    uint16_t base = vm.ram[2];
                    int16_t val = pop();
                    *(vm.ram + base + index) = val;
                    break;
                }
                case S_THIS:
                {
                    uint16_t base = vm.ram[3];
                    int16_t val = pop();
                    *(vm.ram + base + index) = val;
                    break;
                }
                case S_THAT:
                {
                    uint16_t base = vm.ram[4];
                    int16_t val = pop();
                    *(vm.ram + base + index) = val;
                    break;
                }
                case S_TEMP:
                {
                    int16_t val = pop();
                    vm.ram[5 + index] = val;
                    break;
                }
                default:
                    printf("Segment %d not implemented.\n", segment);
                    return INTERPRET_RUNTIME_ERROR;
            }
            break;
        }
        case OP_ADD: 
        {
            int16_t b = pop();
            int16_t a = pop();
            push(a + b);
            break;
        }
        case OP_SUB:
        {
            int16_t b = pop();
            int16_t a = pop();
            push(a - b);
            break;
        }
        case OP_EQ:
        {
            int16_t y = pop();
            int16_t x = pop();
            push(JACK_BOOL(x == y));
            break;
        }
        case OP_NEG:
        {
            push(-pop());
            break;
        }
        case OP_GT:
        {
            int16_t y = pop();
            int16_t x = pop();
            push(JACK_BOOL(x > y));
            break;
        }
        case OP_LT:
        {
            int16_t y = pop();
            int16_t x = pop();
            push(JACK_BOOL(x < y));
            break;
        }
        case OP_AND:
        {
            int16_t y = pop();
            int16_t x = pop();
            push(x & y);
            break;
        }
        case OP_OR:
        {
            int16_t y = pop();
            int16_t x = pop();
            push(x | y);
            break;
        }
        case OP_NOT:
        {
            push(~pop());
            break;
        }
        default:
            printf("Op %d not implemented\n", instruction);
            break;
        }
    }

    return INTERPRET_RUNTIME_ERROR;
#undef READ_WORD
}