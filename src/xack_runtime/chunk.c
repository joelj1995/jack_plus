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
    chunk->function_call_count = 0;
    chunk->entry_function_idx = -1;
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
    if (chunk->goto_label_count == 256)
    {
        printf("Too many gotos\n");
        exit(EEC_OVERLOW);
    }
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

void label_function(Chunk* chunk, char* name, uint16_t n_vars)
{
    if (chunk->function_count == 256)
    {
        printf("Too many functions.\n");
        exit(EEC_OVERLOW);
    }
    chunk->functions[chunk->function_count].name = name;
    chunk->functions[chunk->function_count].n_vars = n_vars;
    chunk->functions[chunk->function_count++].offset = (uint16_t)chunk->count;
}

void label_call(Chunk* chunk, char* name, uint16_t n_args)
{
    if (chunk->function_call_count == 256)
    {
        printf("Too many function calls.\n");
        exit(EEC_OVERLOW);
    }
    write_chunk(chunk,OP_CALL);
    write_chunk(chunk,chunk->function_call_count);
    chunk->function_calls[chunk->function_call_count].name = name;
    chunk->function_calls[chunk->function_call_count].n_args = n_args;
    chunk->function_calls[chunk->function_call_count++].function_idx = -1;
}