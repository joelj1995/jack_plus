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
    write_chunk(chunk, chunk->goto_label_count);
    chunk->goto_labels[chunk->goto_label_count++] = label;
}

void label_chunk(Chunk* chunk, char* label)
{
    if (chunk->label_count == 256)
    {
        printf("Too many labels\n");
        exit(EEC_OVERLOW);
    }
    chunk->labels[chunk->label_count].name = label;
    chunk->labels[chunk->label_count].offset = chunk->count;
    chunk->label_count++;
    write_chunk(chunk, OP_NOP);
}

void replace_labels(Chunk* chunk)
{
    int i = 0;
    while(i < chunk->count)
    {
        if ( chunk->code[i] == OP_GOTO)
        {
            uint16_t label_idx = chunk->code[++i];
            char* goto_name = chunk->goto_labels[label_idx];
            for (int i = 0 ; i < chunk->label_count; i++)
            {
                CodeLabel label = chunk->labels[i];
                char* label_name = label.name;
                if (strcmp(label_name, goto_name) == 0)
                {
                    printf("replacement label for %s at %d found.\n", label_name, label.offset);
                    chunk->code[i] = label.offset;
                    break;
                }
            }
        } 
        i++;
    }
}