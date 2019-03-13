#ifndef __flex_t1_h_
#define __flex_t1_h_

#include <stdio.h>

typedef enum {
    IF_TOKEN = 258, // since Bison will start token at that number
    THEN_TOKEN,
    DO_TOKEN,
    WHILE_TOKEN,
    PRINT_TOKEN,
    NUMBER_TOKEN,
    ID_TOKEN,
    MULT_TOKEN,
    ADD_TOKEN,
    MINUS_TOKEN,
    DIV_TOKEN,
    MOD_TOKEN,
    SEMICOLON_TOKEN,
    LPAREN_TOKEN,
    RPAREN_TOKEN,
    ASSIGNMENT_TOKEN
    // and so on...
} TOKEN;

int yylex(void);

void yyerror(char *s);

#endif
