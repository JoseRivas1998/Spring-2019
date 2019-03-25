/**
* Name: Jose de Jesus Rodriguez Rivas
* Lab: Lab 7
* Date: 03/13/19
**/
#include "flex_t1.h"

extern char *yytext;

int main(int argc, char **argv) {

    freopen(argv[1], "r", stdin);

    TOKEN tok;

    char *token[] = {
            "if",
            "then",
            "do",
            "while",
            "print",
            "number",
            "identifier",
            "times",
            "plus",
            "minus",
            "divide",
            "mod",
            "semicolon",
            "lparen",
            "rparen",
            "assignment"
    };

    while ((tok = yylex()) != 0) {
        if(tok <= PRINT_TOKEN) {
            printf("{<keyword> \"%s\"}", token[tok - IF_TOKEN]);
        } else {
            printf("{<%s> \"%s\"}", token[tok - IF_TOKEN], yytext);
        }
    }
}
