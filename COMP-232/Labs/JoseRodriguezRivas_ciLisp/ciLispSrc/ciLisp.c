#include "ciLisp.h"

#define NaN NAN

void yyerror(char *s) {
    fprintf(stderr, "\nERROR: %s\n", s);
    // note stderr that normally defaults to stdout, but can be redirected: ./src 2> src.log
    // CLion will display stderr in a different color from stdin and stdout
}

//
// find out which function it is
//

char *func[] = {
        "neg",
        "abs",
        "exp",
        "sqrt",
        "add",
        "sub",
        "mult",
        "div",
        "remainder",
        "log",
        "pow",
        "max",
        "min",
        "exp2",
        "cbrt",
        "hypot",
        "sin",
        "cos",
        "tan",
        "read",
        "rand",
        "print",
        "equal",
        "smaller",
        "larger",
        ""
};

OPER_TYPE resolveFunc(char *funcName) {
    int i = 0;
    while (func[i][0] != '\0') {
        if (strcmp(func[i], funcName) == 0)
            return i;

        i++;
    }
    return CUSTOM_FUNC;
}

//
// create a node for a number
//
AST_NODE *number(double value) {
    AST_NODE *p;
    size_t nodeSize;

    // allocate space for the fixed sie and the variable part (union)
    nodeSize = sizeof(AST_NODE) + sizeof(NUMBER_AST_NODE);
    if ((p = malloc(nodeSize)) == NULL)
        yyerror("out of memory");

    p->type = NUM_TYPE;
    p->data.number.value = value;

    return p;
}

//
// create a node for a function
//
AST_NODE *function(char *funcName, AST_NODE *op1, AST_NODE *op2) {
    AST_NODE *p;
    size_t nodeSize;

    // allocate space for the fixed sie and the variable part (union)
    nodeSize = sizeof(AST_NODE) + sizeof(FUNCTION_AST_NODE);
    if ((p = malloc(nodeSize)) == NULL)
        yyerror("out of memory");

    p->type = FUNC_TYPE;
    p->data.function.name = funcName;
    if(op1 != NULL) {
        op1->parent = p;
    }
    if(op2 != NULL) {
        op2->parent = p;
    }
    p->data.function.op1 = op1;
    p->data.function.op2 = op2;

    return p;
}

//
// free a node
//
void freeNode(AST_NODE *p) {
    if (!p)
        return;

    if (p->type == FUNC_TYPE) {
        free(p->data.function.name);
        freeNode(p->data.function.op1);
        freeNode(p->data.function.op2);
    }

    if (p->type == SYMBOL_TYPE) {
        free(p->data.symbol.name);
    }

    freeSymbolTable(p->symbolTable);

    free(p);
}

//
// evaluate an abstract syntax tree
//
// p points to the root
//
double eval(AST_NODE *p) {
    if (!p)
        return 0.0;

// TBD: implement
    if (p->type == NUM_TYPE) {
        return p->data.number.value;
    }
    double op2;

    if (p->type == FUNC_TYPE) {
        switch (resolveFunc(p->data.function.name)) {
            case NEG_OPER:
                return -eval(p->data.function.op1);
            case ABS_OPER:
                return fabs(eval(p->data.function.op1));
            case EXP_OPER:
                return exp(eval(p->data.function.op1));
            case SQRT_OPER:
                return sqrt(eval(p->data.function.op1));
            case ADD_OPER:
                return eval(p->data.function.op1) + eval(p->data.function.op2);
            case SUB_OPER:
                return eval(p->data.function.op1) - eval(p->data.function.op2);
            case MULT_OPER:
                return eval(p->data.function.op1) * eval(p->data.function.op2);
            case DIV_OPER:
                op2 = eval(p->data.function.op2);
                if (isnan(op2) || op2 == 0) {
                    return NaN;
                }
                return eval(p->data.function.op1) / op2;
            case REMAINDER_OPER:
                return remainder(eval(p->data.function.op1), eval(p->data.function.op2));
            case LOG_OPER:
                return log(eval(p->data.function.op1));
            case POW_OPER:
                return pow(eval(p->data.function.op1), eval(p->data.function.op2));
            case MAX_OPER:
                return fmax(eval(p->data.function.op1), eval(p->data.function.op2));
            case MIN_OPER:
                return fmin(eval(p->data.function.op1), eval(p->data.function.op2));
            case EXP2_OPER:
                return exp2(eval(p->data.function.op1));
            case CBRT_OPER:
                return cbrt(eval(p->data.function.op1));
            case HYPOT_OPER:
                return hypot(eval(p->data.function.op1), eval(p->data.function.op2));
            case CUSTOM_FUNC:
                break;
            case SIN_OPER:
                return sin(eval(p->data.function.op1));
            case COS_OPER:
                return cos(eval(p->data.function.op1));
            case TAN_OPER:
                return tan(eval(p->data.function.op1));
        }
    }

    if(p->type == SYMBOL_TYPE) {
        AST_NODE *parent = p;
        while(parent != NULL) {
            SYMBOL_TABLE_NODE *cN = parent->symbolTable;
            while(cN != NULL) {
                if(cN->ident == NULL) {
                    cN = cN->next;
                    continue;
                }
                if(strcmp(cN->ident, p->data.symbol.name) == 0) {
                    return eval(cN->val);
                }
                cN = cN->next;
            }
            parent = parent->parent;
        }
        char* error = malloc(128 * sizeof(char));
        sprintf(error, "The variable %s is undefined", p->data.symbol.name);
        yyerror(error);
        free(error);
        exit(-1);
    }

    return 0.0;
}

SYMBOL_TABLE_NODE *createSymbol(char *symbol, AST_NODE *s_expr) {
    SYMBOL_TABLE_NODE *p;
    size_t nodeSize = sizeof(SYMBOL_TABLE_NODE);

    if ((p = malloc(nodeSize)) == NULL) {
        yyerror("out of memory");
    }

    p->ident = symbol;
    p->val = s_expr;
    p->next = NULL;

    return p;
}

SYMBOL_TABLE_NODE *addSymbolToList(SYMBOL_TABLE_NODE *let_list, SYMBOL_TABLE_NODE *let_elem) {
    if (let_elem == NULL) {
        return let_list;
    }
    if (let_elem->val == NULL) {
        return let_list;
    }
    SYMBOL_TABLE_NODE *prev_node = let_list;
    SYMBOL_TABLE_NODE *curr_node = let_list->next;
    while(curr_node != NULL) {
        prev_node = curr_node;
        curr_node = curr_node->next;
    }
    prev_node->next = let_elem;
    return let_list;
}

AST_NODE *setSymbolTable(SYMBOL_TABLE_NODE *let_section, AST_NODE *s_expr) {
    if (s_expr == NULL) {
        return NULL;
    }

    SYMBOL_TABLE_NODE *cN = let_section;
    while (cN != NULL) {
        cN->val->parent = s_expr;
        cN = cN->next;
    }

    s_expr->symbolTable = let_section;
    return s_expr;
}

AST_NODE *symbol(char *symb) {
    AST_NODE *p;
    size_t nodeSize;

    // allocate space for the fixed sie and the variable part (union)
    nodeSize = sizeof(AST_NODE) + sizeof(SYMBOL_AST_NODE);
    if ((p = malloc(nodeSize)) == NULL)
        yyerror("out of memory");

    p->type = SYMBOL_TYPE;
    p->data.symbol.name = symb;
    return p;
}

void freeSymbolTable(SYMBOL_TABLE_NODE *node) {
    if (!node) {
        return;
    }
    freeSymbolTable(node->next);
    freeNode(node->val);
    free(node);

}