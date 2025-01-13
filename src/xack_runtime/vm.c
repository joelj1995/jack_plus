#include "vm.h"

VM vm;

#define HACK_SP vm.ram[0]

void push(int16_t word)
{
    vm.ram[HACK_SP] = word;
    HACK_SP++; 
}

int16_t pop()
{
    HACK_SP--;
    return vm.ram[HACK_SP];
}

int execute(Chunk* chunk) {

    if (!chunk->is_compiled) 
    {
        printf("Tried to run a chunk that isn't compiled.");
        exit(EEC_BAD_STATE);
    }
    
#define READ_WORD() *vm.ip++;
    vm.chunk = chunk;
    vm.ip = vm.chunk->code + vm.chunk->entry_point;

    for (int i = 0; i < MEMORY_LENGTH; i++)
    {
        vm.ram[i] = 0;
    }

    vm.ram[0] = 256;
    vm.ram[1] = 300;
    vm.ram[2] = 400;
    vm.ram[3] = 3000;
    vm.ram[4] = 3010;

    while(true) {
        printf("      ");
        for (int16_t* slot = &vm.ram[256]; slot < &vm.ram[HACK_SP]; slot++)
        {
            printf("[%d]", *slot);
        }
        printf("\n");

    printf("      ");
        for (int i = 0; i < 16; i++)
        {
            printf("RAM[%d]=%d; ", i, vm.ram[i]);
        }
        printf("RAM[%d]=%d; ", 300, vm.ram[300]);
        printf("RAM[%d]=%d; ", 400, vm.ram[400]);
        printf("\n");

        if (vm.ip >= chunk->code + chunk->count)  {
            printf("End of input reached\n");
            break;
        }

        uint16_t instruction = READ_WORD();
        switch (instruction)
        {
        case OP_NOP:
            break;
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
                case S_POINTER:
                {
                    uint16_t value = vm.ram[3+index];
                    push(value);
                    break;
                }
                case S_TEMP:
                {
                    push(vm.ram[5 + index]);
                    break;
                }
                case S_STATIC:
                {
                    push(vm.ram[16 + index]);
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
                case S_POINTER:
                {
                    int16_t val = pop();
                    vm.ram[3+index] = val;
                    break;
                }
                case S_TEMP:
                {
                    int16_t val = pop();
                    vm.ram[5 + index] = val;
                    break;
                }
                 case S_STATIC:
                {
                    int16_t val = pop();
                    vm.ram[16 + index] = val;
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
        case OP_GOTO:
        {
            vm.ip = vm.chunk->code + READ_WORD();
            break;
        }
        case OP_IF_GOTO:
        {
            if (pop() != 0)
            {
                vm.ip = vm.chunk->code + READ_WORD();
            }
            else
            {
                READ_WORD();
            }
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