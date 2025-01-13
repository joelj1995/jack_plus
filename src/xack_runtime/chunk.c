#include <string.h>
#include "chunk.h"
#include "memory.h"

void init_chunk(Chunk* chunk)
{
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    chunk->label_count = 0;
    chunk->goto_label_count = 0;
    chunk->function_count = 0;
    chunk->is_compiled = false;
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

void label_goto(Chunk* chunk, uint16_t op, char* label)
{
    write_chunk(chunk, op);
    chunk->goto_labels[chunk->goto_label_count].name = label;
    chunk->goto_labels[chunk->goto_label_count++].offset = chunk->count;
    write_chunk(chunk,OP_NOP);
}

void label_chunk(Chunk* chunk, char* label)
{
    if (chunk->label_count == 256)
    {
        printf("Too many labels\n");
        exit(EEC_OVERLOW);
    }
    chunk->labels[chunk->label_count].name = label;
    chunk->labels[chunk->label_count++].offset = chunk->count;
    write_chunk(chunk, OP_NOP);
}

void label_function(Chunk* chunk, uint16_t arity, char* label)
{
    chunk->functions[chunk->function_count].name = label;
    chunk->functions[chunk->function_count].arity = arity;
    chunk->functions[chunk->function_count++].offset = chunk->count-1;
}