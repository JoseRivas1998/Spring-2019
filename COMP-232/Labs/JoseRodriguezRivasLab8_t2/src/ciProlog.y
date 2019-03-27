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
	| PROPOSITION {
		fprintf(stderr, "yacc: logexpr ::= prop \n");
		$$ = eval($1);
		fprintf(stderr, "src returns %s\n", bool2str($$));
	}
	| ASSERT LPAREN PROPOSITION RPAREN {
		fprintf(stderr, "yacc: logexpr ::= assert ( prop ) \n");
		$$ = assert($3);
		fprintf(stderr, "src returns %s\n", bool2str($$));
	}
	| RETRACT LPAREN PROPOSITION RPAREN {
		fprintf(stderr, "yacc: logexpr ::= retract ( prop ) \n");
		$$ = retract($3);
		fprintf(stderr, "src returns %s\n", bool2str($$));
	}
	| LPAREN logexpr RPAREN {
		fprintf(stderr, "yacc: logexpr ::= (logexpr) \n");
		$$ = $2;
		fprintf(stderr, "src returns %s\n", bool2str($$));
	}
	| NOT logexpr {
		fprintf(stderr, "yacc: logexpr ::= NOT logexpr \n");
		$$ = not($2);
		fprintf(stderr, "src returns %s\n", bool2str($$));
	}
	| logexpr AND logexpr {
		fprintf(stderr, "yacc: logexpr ::= logexpr AND logexpr \n");
		$$ = and($1, $3);
		fprintf(stderr, "src returns %s\n", bool2str($$));
	}
	| logexpr OR logexpr {
		fprintf(stderr, "yacc: logexpr ::= logexpr OR logexpr \n");
		$$ = or($1, $3);
		fprintf(stderr, "src returns %s\n", bool2str($$));
	}
/* TODO complete the definition of the grammar */
;

%%

