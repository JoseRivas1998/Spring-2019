%option noyywrap
%option nounput
%option noinput

%{
#include "calc.h"

%}

digit[0-9]
number {digit}+(\.{digit}+)?
func "neg"|"abs"|"exp"|"sqrt"|"add"|"sub"|"mult"|"div"|"remainder"|"log"|"pow"|"max"|"min"

%%

{number} {
    yylval.dval = strtod(yytext, NULL);
    fprintf(stderr, "lex: NUMBER dval = %lf\n", yylval.dval);
    return NUMBER;
}

"quit" {
    return QUIT;
}

{func} {
    yylval.
    sval = (char *) malloc(strlen(yytext) * sizeof(char));
    strcpy(yylval.sval, yytext);
    fprintf(stderr,
    "lex: FUNC sval = %s\n", yylval.sval);
    return FUNC;
}
"(" {
    fprintf(stderr,
    "lex: LPAREN\n");
    return LPAREN;
}

")" {
    fprintf(stderr,
    "lex: RPAREN\n");
    return RPAREN;
}

[\n] {
    fprintf(stderr,
    "lex: EOL\n");
    YY_FLUSH_BUFFER;
    return EOL;
}

[|\t]; /* skip whitespace */

. {
    printf("ERROR: invalid character: >>%s<<\n", yytext);
}
%%

/*
 * DO NOT CHANGE THE FOLLOWING CODE CRITICAL FOR REPL!
 */
int main(void)
{

    // freopen("/dev/null", "w", stderr); // except for this line that can be uncommented to throw away debug printouts

    char *s_expr_str = NULL;
    size_t s_expr_str_len = 0;
    YY_BUFFER_STATE buffer;
    while (1)
    {
        printf("\n> ");
        getline(&s_expr_str, &s_expr_str_len, stdin);
        s_expr_str[s_expr_str_len++] = '\0';
        s_expr_str[s_expr_str_len++] = '\0';
        buffer = yy_scan_buffer(s_expr_str, s_expr_str_len);
        yyparse();
        yy_delete_buffer(buffer);
    }
}
