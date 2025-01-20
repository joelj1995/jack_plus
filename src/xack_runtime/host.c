#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chunk.h"
#include "compiler.h"
#include "debug.h"
#include "jack_vm.h"
#include "jack_vm.tab.h"
#include "vm.h"

Chunk* the_chunk;

int main(int argc, char *argv[]) 
{
    Chunk chunk_on_stack;
    the_chunk = &chunk_on_stack;

    printf("Initializing chunk.\n");
    init_chunk(the_chunk);

    printf("Parsing.\n");
    yyparse();

    printf("Compiling.\n");
    compile(the_chunk);

    printf("Executing.\n");
    execute(the_chunk);

    printf("Done!\n");
}