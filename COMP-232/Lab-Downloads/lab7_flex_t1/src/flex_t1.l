/* NOTE: % must be in the first column (no indentation) */

%option noyywrap
%option nounput
%option noinput

%{
   #include "flex_t1.h"
%}

%%

"if"        {return IF_TOKEN;}
"then"      {return THEN_TOKEN;}

%%

void yyerror(char *s) {/* dummy */}
