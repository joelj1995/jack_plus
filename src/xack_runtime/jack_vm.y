%{
#include <stdio.h>
#include <stdlib.h>
#include "chunk.h"
#include "jack_vm.h"

extern Chunk* the_chunk;
int current_label = 0;
%}

%union {
    int intval;
    char* str;
    char c;
}

%token NL
%token PUSH POP
%token ARGUMENT LOCAL STATIC CONSTANT THIS THAT POINTER TEMP
%token ADD SUB NEG EQ GT LT AND OR NOT
%token LABEL GOTO IF_GOTO
%token FUNCTION RETURN CALL

%token <intval> INT_CONST 
%token <str> STR_CONST
%token <str> ID

%%

program: statements;

statements:
| statements statement;

statement: push_pop_command
| arith_command
| branching_command
| function_command
;

push_pop_command: push_pop segment INT_CONST NL { write_chunk(the_chunk, $3); }; 

push_pop: PUSH  { write_chunk(the_chunk, OP_PUSH); }
| POP           { write_chunk(the_chunk, OP_POP); }
;

segment: ARGUMENT { write_chunk(the_chunk, S_ARGUMENT); }
| LOCAL           { write_chunk(the_chunk, S_LOCAL); }
| STATIC          { write_chunk(the_chunk, S_STATIC); }
| CONSTANT        { write_chunk(the_chunk, S_CONSTANT); }
| THIS            { write_chunk(the_chunk, S_THIS); }
| THAT            { write_chunk(the_chunk, S_THAT); }
| POINTER         { write_chunk(the_chunk, S_POINTER); }
| TEMP            { write_chunk(the_chunk, S_TEMP); }
;

arith_command: ADD NL { write_chunk(the_chunk, OP_ADD); }
| SUB NL              { write_chunk(the_chunk, OP_SUB); }
| NEG NL              { write_chunk(the_chunk, OP_NEG); }
| EQ NL               { write_chunk(the_chunk, OP_EQ); }
| GT NL               { write_chunk(the_chunk, OP_GT); }
| LT NL               { write_chunk(the_chunk, OP_LT); }
| AND NL              { write_chunk(the_chunk, OP_AND); }
| OR NL               { write_chunk(the_chunk, OP_OR); }
| NOT NL              { write_chunk(the_chunk, OP_NOT); }
;

branching_command: LABEL ID NL    { label_chunk(the_chunk, $2); }
| GOTO ID NL                      { label_goto(the_chunk, OP_GOTO, $2); }
| IF_GOTO ID NL                   { label_goto(the_chunk, OP_IF_GOTO, $2); }
;

function_command: FUNCTION ID INT_CONST NL  { label_function(the_chunk, $2, $3); }
| CALL ID INT_CONST NL                      { label_call(the_chunk, $2, $3);     }
| RETURN NL                                 { write_chunk(the_chunk, OP_RETURN); }
;

%%

void yyerror(char *s)
{
    extern int curr_lineno;
    
    fprintf(stderr, "error: %s\n", s);
    exit(100);
}