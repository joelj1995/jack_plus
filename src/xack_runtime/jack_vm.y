%{

%}

%union {
    int intval;
    char* str;
    char c;
}

%token NL
%token PUSH POP
%token ARGUMENT STATIC CONSTANT THIS THAT POINTER TEMP
%token <intval> INT_CONST 
%token <str> STR_CONST
%token <str> ID

%%

program: statements;

statements:
| statements NL statement;

statement: push_pop_command
;

push_pop_command: push_pop segment INT_CONST;

push_pop: PUSH
| POP
;

segment: ARGUMENT
| STATIC
| CONSTANT
| THIS
| THAT
| POINTER
| TEMP
;

