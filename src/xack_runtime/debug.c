#include "common.h"
#include "debug.h"

void disassemble_chunk(Chunk* chunk)
{
    int i = 0;
    while (i < chunk->count)
    {
        if (chunk->code[i] == OP_PUSH)
        {
            printf("push ");
        }
        else if (chunk->code[i] == OP_POP)
        {
            printf("pop ");
        }
        else
        {
            printf("Op %d not recognized\n", chunk->code[i]);
            exit(EEC_OP_NOT_KNOWN);
        }
        i++;
    }
}