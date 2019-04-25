/**
* Name: Jose de Jesus Rodriguez Rivas
* Lab: ciLisp
* Date: 04/24/19
**/
%{
    #include "ciLisp.h"
%}

%union {
    double dval;
    char *sval;
    struct ast_node *astNode;
    struct symbol_table_node *symbolNode;
};

%token <sval> FUNC SYMBOL TYPE
%token <dval> REAL_NUMBER INTEGER_NUMBER
%token LPAREN RPAREN EOL QUIT LET COND LAMBDA

%type <astNode> s_expr s_expr_list
%type <symbolNode> let_elem let_section let_list arg_list

%%

program:
	s_expr EOL {
	fprintf(stderr, "yacc: program ::= s_expr EOL\n");
	if ($1) {
	    RETURN_VALUE val = eval($1);
	    printf("%.2lf", val.value);
	    freeNode($1);
	}
	};

s_expr:
	REAL_NUMBER {
	fprintf(stderr, "yacc: s_expr ::= NUMBER\n");
	$$ = real_number($1);
	}
	| INTEGER_NUMBER {
	$$ = int_number($1);
	}
	| SYMBOL {
	$$ = symbol($1);
	}
	| LPAREN FUNC s_expr_list RPAREN {
	$$ = function($2, $3);
	}
	| LPAREN COND s_expr s_expr s_expr RPAREN {
	fprintf(stderr, "yacc: LPAREN COND s_expr s_expr s_expr RPAREN\n");
	$$ = conditional($3, $4, $5);
	}
	| LPAREN let_section s_expr RPAREN {
	$$ = setSymbolTable($2, $3);
	}
	| LPAREN SYMBOL s_expr_list RPAREN {
	$$ = function($2, $3);
	}
	| QUIT {
	fprintf(stderr, "yacc: s_expr ::= QUIT\n");
	exit(EXIT_SUCCESS);
	}
	| error {
	fprintf(stderr, "yacc: s_expr ::= error\n");
	yyerror("unexpected token");
	$$ = NULL;
	};
s_expr_list:
	s_expr s_expr_list {
	$$ = addNodeToList($1, $2);
	}
	| s_expr {
	$$ = $1;
	}
	| /*empty*/ {
	$$ = NULL;
	}

let_section:
	/*empty*/{
		$$ = NULL;
	}
	| LPAREN let_list RPAREN {
		$$ = $2;
	};
let_list:
	let_list let_elem {
		$$ = addSymbolToList($1, $2);
	}
	| LET let_elem {
		fprintf(stderr, "yacc: LET let_elem\n");
		$$ = $2;
	};
let_elem:
	LPAREN TYPE SYMBOL s_expr RPAREN {
		$$ = createSymbol($2, $3, $4);
	}
	| LPAREN SYMBOL s_expr RPAREN {
		$$ = createSymbol(NULL, $2, $3);
	}
	| LPAREN TYPE SYMBOL LAMBDA LPAREN arg_list RPAREN s_expr RPAREN {
		$$ = createLambda($2, $3, $6, $8);
	}
	| LPAREN SYMBOL LAMBDA LPAREN arg_list RPAREN s_expr RPAREN {
		fprintf(stderr, "yacc: LPAREN SYMBOL LAMBDA LPAREN arg_list RPAREN s_expr RPAREN\n");
		$$ = createLambda(NULL, $2, $5, $7);
	}
arg_list:
	SYMBOL arg_list {
		fprintf(stderr, "yacc: SYMBOL ARG_LIST\n");
		$$ = addSymbolToArgList($1, $2);
	}
	| SYMBOL {
		fprintf(stderr, "yacc: SYMBOL\n");
		$$ = createArgList($1);
	}
%%

