#include <string.h>

#include "compiler.h"

void replace_labels(Chunk* chunk)
{
    for (int i = 0; i < chunk->goto_label_count; i++)
    {
        char* name = chunk->goto_labels[i].name;
        for (int j = 0; j < chunk->label_count; j++)
        {
            char* label_name = chunk->labels[j].name;
            if (strcmp(name, label_name) == 0)
            {
                printf("Found a match for %d at %d!\n", chunk->goto_labels[i].offset, chunk->labels[j].offset);
                chunk->code[chunk->goto_labels[i].offset] = chunk->labels[j].offset;
            }
        }
    }
}

void replace_calls(Chunk* chunk)
{
    for (int i = 0; i < chunk->function_call_count; i++)
    {
        char* name = chunk->function_calls[i].name;
        for (int j = 0; j < chunk->function_count; j++)
        {
            char* function_name = chunk->functions[j].name;
            if (strcmp(name, function_name) == 0)
            {
                printf("Found a fn match for %d at %d!\n", chunk->function_calls[i].offset, chunk->functions[j].offset);
                chunk->code[chunk->function_calls[i].offset + 1] = chunk->functions[j].offset;
            }
        }
    }
}

void find_entry_point(Chunk* chunk)
{
    for (int i = 0; i < chunk->function_count; i++)
    {
        if (strcmp(chunk->functions[i].name, "Main.main") == 0)
        {
            chunk->entry_point = chunk->functions[i].offset;
            return;
        }
    }
    printf("Could not find entry point.\n");
    exit(EEC_COMPILATION_ERROR);
}

void compile(Chunk* chunk)
{
    if (chunk->is_compiled)
    {
        printf("Chunk is already compiled\n");
        exit(EEC_BAD_STATE);
    }
    replace_labels(chunk);
    find_entry_point(chunk);
    replace_calls(chunk);
    chunk->is_compiled = true;
}