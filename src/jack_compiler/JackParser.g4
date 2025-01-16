grammar JackParser;

import JackLexer;

class: CLASS ID '{' classVarDec* subroutineDec* '}';

classVarDec: classVarDecType type classVarDecIDList ';';

classVarDecIDList: ID # LastID
    | ID ',' classVarDecIDList # ListedID;

classVarDecType: 'static' | 'field';

type: 'int' | 'char' | 'boolean' | ID;

subroutineDec: subroutineKind ID '(' parameterList ')';

subroutineKind: CONSTRUCTOR | FUNCTION | METHOD;

parameterList: (parameter (',' parameter)*)?;

parameter: type ID;


statements: statement*;

statement: letStatement
    | ifStatement
    | whileStatement
    | doStatement
    | returnStatement
    ;

letStatement: LET ID ('[' expression ']') ? '=' expression;

ifStatement: IF '(' expression ')' '{' statements '}' (ELSE '{' statements '}')?;

whileStatement: WHILE '(' expression ')' '{' statements '}';

doStatement: DO subroutineCall ';';

returnStatement: RETURN expression? ';';


expression: term (op term)*;

term: INT_CONST | STR_CONST | keywordConstant | ID | ID '[' expression ']' | '(' expression ')' | unaryOp term | subroutineCall;

subroutineCall: ID '(' expressionList ')' | ID '.' ID '(' expressionList ')';

expressionList: (expression (',' expression)*)?;

op: '+' | '-' | '*' | '/' | '&' | '|' | '<' | '>' | '=';

unaryOp: '-' | '~';

keywordConstant: 'true' | 'false' | 'null' | 'this';