grammar JackParser;

import JackLexer;

class: CLASS ID '{' subroutineDec* '}';

subroutineDec: subroutineKind ID '(' ')';

subroutineKind: CONSTRUCTOR | FUNCTION | METHOD;