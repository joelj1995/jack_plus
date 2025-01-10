#include "common.h"
#include "debug.h"

void disassemble_segment(uint16_t byte)
{
    switch (byte)
    {
        case S_ARGUMENT:
            printf("argument ");
            break;
        case S_LOCAL:
            printf("local ");
            break;
        case S_STATIC:
            printf("static ");
            break;
        case S_CONSTANT:
            printf("constant ");
            break;
        case S_THIS:
            printf("this ");
            break;
        case S_THAT:
            printf("that ");
            break;
        case S_POINTER:
            printf("pointer ");
            break;
        case S_TEMP:
            printf("temp ");
            break;
        default:
            exit(EEC_OP_NOT_KNOWN);
    }
}

void disassemble_int_constant(uint16_t val)
{
    printf("%d", val);
}

void disassemble_chunk(Chunk* chunk)
{
    int i = 0;
    while (i < chunk->count)
    {
        if (chunk->code[i] == OP_PUSH)
        {
            printf("push ");
            i++;
            disassemble_segment(chunk->code[i]);
            i++;
            disassemble_int_constant(chunk->code[i]);
            printf("\n");
        }
        else if (chunk->code[i] == OP_POP)
        {
            printf("pop ");
            i++;
            disassemble_segment(chunk->code[i]);
            i++;
            disassemble_int_constant(chunk->code[i]);
            printf("\n");
        }
        else
        {
            printf("Op %d not recognized\n", chunk->code[i]);
            exit(EEC_OP_NOT_KNOWN);
        }
        i++;
    }
}