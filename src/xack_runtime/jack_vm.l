%option noyywrap nodefault
%{
#include "jack_vm.h"
#include "jack_vm.tab.h"
%}

%%
^[ \t\r]*(\/\/.*)?\n     { }

\/\/.*          { }
(\r)?\n         { return NL; }
[ \t\f\v]*      { }


"push"          { return PUSH; }
"pop"           { return POP; }

"argument"      { return ARGUMENT; }
"local"         { return LOCAL; }
"static"        { return STATIC; }
"constant"      { return CONSTANT; }
"this"          { return THIS; }
"that"          { return THAT; }
"pointer"       { return POINTER; }
"temp"          { return TEMP; }

"add"           { return ADD; }
"sub"           { return SUB; }
"neg"           { return NEG; }
"eq"            { return EQ; }
"gt"            { return GT; }
"lt"            { return LT; }
"and"           { return AND; }
"or"            { return OR; }
"not"           { return NOT; }

"label"         { return LABEL; }
"goto"          { return GOTO; }
"if-goto"       { return IF_GOTO; }

"function"       { return FUNCTION; }
"return"         { return RETURN; }
"call"           { return CALL; }


[+-]?[0-9]+               { yylval.intval = atoi(yytext); return INT_CONST; }
[a-zA-Z_][\.a-zA-z0-9_]*  { yylval.str = dupstr(yytext); return ID; }

%%