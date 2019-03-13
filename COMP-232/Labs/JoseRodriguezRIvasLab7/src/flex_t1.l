/* NOTE: % must be in the first column (no indentation) */

%option noyywrap
%option nounput
%option noinput

digit       [0-9]
identifier  {letter}+({letter}|{digit}|_)*
number      {digit}+(\.{digit}+)?
letter      [a-zA-Z]

%{
   #include "flex_t1.h"
%}

%%

"if"            {return IF_TOKEN;}
"then"          {return THEN_TOKEN;}
"do"            {return DO_TOKEN;}
"while"         {return WHILE_TOKEN;}
"print"         {return PRINT_TOKEN;}
{identifier}    {return ID_TOKEN;}
{number}        {return NUMBER_TOKEN;}
"*"             {return MULT_TOKEN;}
"+"             {return ADD_TOKEN;}
"-"             {return MINUS_TOKEN;}
"/"             {return DIV_TOKEN;}
"%"             {return MOD_TOKEN;}
";"             {return SEMICOLON_TOKEN;}
"("             {return LPAREN_TOKEN;}
")"             {return RPAREN_TOKEN;}
"="             {return ASSIGNMENT_TOKEN;}

%%

void yyerror(char *s) {/* dummy */}
