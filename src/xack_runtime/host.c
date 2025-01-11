#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chunk.h"
#include "debug.h"
#include "jack_vm.h"
#include "jack_vm.tab.h"
#include "vm.h"

Chunk* the_chunk;

int main(int argc, char *argv[]) 
{
    Chunk chunk_on_stack;
    the_chunk = &chunk_on_stack;

    init_chunk(the_chunk);

    yyparse();

    execute(the_chunk);

    printf("Done!\n");
}