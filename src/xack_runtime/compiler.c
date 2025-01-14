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
                chunk->code[chunk->goto_labels[i].offset] = chunk->labels[j].offset;
            }
        }
    }
}

void replace_calls(Chunk* chunk)
{
    for (int i = 0; i < chunk->function_call_count; i++)
    {
        bool found = false;
        char* name = chunk->function_calls[i].name;
        for (int j = 0; j < chunk->function_count; j++)
        {
            char* function_name = chunk->functions[j].name;
            if (strcmp(name, function_name) == 0)
            {
                chunk->function_calls[i].function_idx = j;
                found = true;
            }
        }
        if (!found)
        {
            printf("Could not find function matching %s.\n", name);
            exit(EEC_COMPILATION_ERROR);
        }
    }
}

void find_entry_point(Chunk* chunk)
{
    for (int i = 0; i < chunk->function_count; i++)
    {
        if (strcmp(chunk->functions[i].name, "Main.main") == 0)
        {
            chunk->entry_function_idx = i;
            return;
        }
    }
}

void compile(Chunk* chunk)
{
    if (chunk->is_compiled)
    {
        printf("Chunk is already compiled\n");
        exit(EEC_BAD_STATE);
    }
    if (chunk->function_count == 0 || chunk->functions[0].offset != 0)
    {
        // code with no function
        chunk->functions[chunk->function_count].n_vars = 0;
        chunk->functions[chunk->function_count].name = "";
        chunk->functions[chunk->function_count].offset = 0;
        chunk->entry_function_idx = chunk->function_count++;
    }
    replace_labels(chunk);
    replace_calls(chunk);
    find_entry_point(chunk);
    chunk->is_compiled = true;
}