%option noyywrap nodefault
%{
#include "jack_vm.h"
#include "jack_vm.tab.h"
%}

%%

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

([1-9]+(0-9)*|0)          { yylval.intval = atoi(yytext); return INT_CONST; }
[a-zA-Z_][\.a-zA-z0-9_]*  { yylval.str = dupstr(yytext); return ID; }

%%