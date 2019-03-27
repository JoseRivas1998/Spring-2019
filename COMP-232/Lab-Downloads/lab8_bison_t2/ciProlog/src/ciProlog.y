/*

 logexpr ::= 
   proposition
 | assert ( proposition )
 | retract ( proposition )
 | ( logexpr )
 | NOT logexpr
 | logexpr AND logexpr
 | logexpr OR logexpr

 letter ::= [a-zA-Z]
 proposition ::= '{letter}({letter}|\ )*'

 */

%{
#include "ciProlog.h"
%}

%union
{
   bool bval;
   char *sval;
};

%token <sval> PROPOSITION
%token ASSERT RETRACT NOT AND OR LPAREN RPAREN EOL HALT

%type <bval> logexpr

%%

program: logexpr EOL {
        fprintf(stderr, "yacc: program ::= logexpr EOL\n");
        printf("=> %s\n", bool2str($1));
}
;

logexpr:
HALT {
   fprintf(stderr, "yacc: logexpr ::= HALT\n");
   exit(0);
}
/* TODO complete the definition of the grammar */
;

%%

