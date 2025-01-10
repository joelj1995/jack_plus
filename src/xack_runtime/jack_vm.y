%{
#include <stdio.h>
#include <stdlib.h>
#include "chunk.h"
#include "jack_vm.h"

extern Chunk* the_chunk;
%}

%union {
    int intval;
    char* str;
    char c;
}

%token NL
%token PUSH POP
%token ARGUMENT LOCAL STATIC CONSTANT THIS THAT POINTER TEMP
%token ADD SUB

%token <intval> INT_CONST 
%token <str> STR_CONST
%token <str> ID

%%

program: statements;

statements:
| statements statement;

statement: push_pop_command
;

push_pop_command: push_pop segment INT_CONST NL;

push_pop: PUSH  { write_chunk(the_chunk, OP_PUSH); }
| POP           { write_chunk(the_chunk, OP_POP); }
;

segment: ARGUMENT
| LOCAL
| STATIC
| CONSTANT
| THIS
| THAT
| POINTER
| TEMP
;

%%

void yyerror(char *s)
{
    extern int curr_lineno;
    
    fprintf(stderr, "error: %s\n", s);
    exit(100);
}