#include "chunk.h"
#include "memory.h"

void init_chunk(Chunk* chunk)
{
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    chunk->label_count = 0;
}

void write_chunk(Chunk* chunk, uint16_t byte)
{
    if (chunk->capacity < chunk->count + 1)
    {
        int old_capacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(old_capacity);
        chunk->code = GROW_ARRAY(uint16_t, chunk->code, old_capacity, chunk->capacity);
    }
    chunk->code[chunk->count] = byte;
    chunk->count++;
}

void label_chunk(Chunk* chunk, char* label)
{
    if (chunk->label_count == 256)
    {
        printf("Too many labels\n");
        exit(EEC_OVERLOW);
    }
    chunk->labels[chunk->label_count].name = label;
    chunk->labels[chunk->label_count].code = &chunk->code[chunk->count];
    chunk->label_count++;
    write_chunk(chunk, OP_NOP);
}