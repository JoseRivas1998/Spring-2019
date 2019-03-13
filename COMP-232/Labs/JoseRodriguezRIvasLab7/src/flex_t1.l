/* NOTE: % must be in the first column (no indentation) */

%option noyywrap
%option nounput
%option noinput

digit       [0-9]
number      {digit}+(\.{digit}+)?
letter      [a-zA-Z]
identifier  {letter}+([{letter}{digit}_])*

%{
   #include "flex_t1.h"
%}

%%

"if"            {return IF_TOKEN;}
"then"          {return THEN_TOKEN;}
"do"            {return DO_TOKEN;}
"while"         {return WHILE_TOKEN;}
"print"         {return PRINT_TOKEN;}
{number}        {return NUMBER_TOKEN;}
{identifier}    {return ID_TOKEN;}
"*"             {return MULT_TOKEN;}
"+"             {return ADD_TOKEN;}
"-"             {return MINUS_TOKEN;}

%%

void yyerror(char *s) {/* dummy */}
