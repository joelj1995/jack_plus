lexer grammar JackLexer;

CLASS       : 'class';
CONSTRUCTOR : 'constructor';
FUNCTION    : 'function';
METHOD      : 'method';
FIELD       : 'field';
STATIC      : 'static';
VAR         : 'var';
INT         : 'int';
CHAR        : 'char';
BOOLEAN     : 'boolean';
TRUE        : 'true';
FALSE       : 'false';
NULL        : 'null';
THIS        : 'this';
LET         : 'let';
DO          : 'do';
IF          : 'if';
ELSE        : 'else';
WHILE       : 'while';
RETURN      : 'return';

INT_CONST   : [0-9]+;
STR_CONST   : '"' .*? '"';
ID          : [_a-zA-Z][_a-zA-Z0-9]*;
WS          : [ \t\n\r] -> skip;