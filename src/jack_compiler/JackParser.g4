grammar JackParser;

import JackLexer;

class: CLASS ID '{' classVarDec* subroutineDec* '}';

classVarDec: classVarDecType type classVarDecIDList ';' ;

classVarDecIDList: ID # LastID
    | ID ',' classVarDecIDList # ListedID;

classVarDecType: 'static' | 'field';

type: 'int' | 'char' | 'boolean' | ID;

subroutineDec: subroutineKind type ID '(' parameterList ')' subroutineBody;

subroutineKind: CONSTRUCTOR | FUNCTION | METHOD;

parameterList: (parameter (',' parameter)*)?;

subroutineBody: '{' subroutineVarDecs statements '}';
subroutineVarDecs: varDec*;

varDec: 'var' type ID (',' ID)* ';';

parameter: type ID;


statements: statement*;

statement: letStatement
    | ifStatement
    | whileStatement
    | doStatement
    | returnStatement
    ;

letStatement: LET ID '=' expression ';'       #LetVarStatement
    | LET ID letArrayIndex '=' expression ';' #LetArrayStatement
    ;
letArrayIndex: '[' expression ']';

ifStatement: IF '(' ifStatementExpression ')' '{' ifStatements '}' (ELSE '{' elseStatements '}')?;
ifStatementExpression: expression;
ifStatements: statements;
elseStatements: statements;

whileStatement: WHILE '(' whileStatementExpression ')' '{' statements '}';
whileStatementExpression: expression;

doStatement: DO subroutineCall ';';

returnStatement: RETURN expression? ';';


expression: term expressionPart*;
expressionPart: op term;

term: 
    INT_CONST                       #TermIntConst
    | STR_CONST                     #TermStrConst
    | keywordConstant               #TermKeywordConst
    | ID                            #TermID
    | ID '[' expression ']'         #TermArray
    | '(' expression ')'            #TermGroup
    | unaryOp term                  #TermUnary
    | subroutineCall                #TermSubroutineCall
    ;

subroutineCall: 
    ID '(' expressionList ')'           # thisSubroutineCall
    | ID '.' ID '(' expressionList ')'  # thatSubroutineCall
    ;

expressionList: (expression (',' expression)*)?;

op: '+' | '-' | '*' | '/' | '&' | '|' | '<' | '>' | '=';

unaryOp: '-' | '~';

keywordConstant: 'true' | 'false' | 'null' | 'this';