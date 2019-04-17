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
        "print",
        "read",
        "rand",
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
AST_NODE *real_number(double value) {
    AST_NODE *p = calloc(1, sizeof(AST_NODE));
    if (p == NULL)
        yyerror("out of memory");

    p->type = NUM_TYPE;
    p->data.number.value.type = REAL_TYPE;
    p->data.number.value.value = value;

    return p;
}
AST_NODE *int_number(int value) {
    AST_NODE *p = calloc(1, sizeof(AST_NODE));
    if (p == NULL)
        yyerror("out of memory");

    p->type = NUM_TYPE;
    p->data.number.value.type = INTEGER_TYPE;
    p->data.number.value.value = value;

    return p;
}

//
// create a node for a function
//
AST_NODE *function(char *funcName, AST_NODE *op1, AST_NODE *op2) {
    AST_NODE *p = calloc(1, sizeof(AST_NODE));
    if (p == NULL)
        yyerror("out of memory");

    p->type = FUNC_TYPE;
    p->data.function.name = funcName;
    if (op1 != NULL) {
        op1->parent = p;
    }
    if (op2 != NULL) {
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

RETURN_VALUE evalFunc(AST_NODE *p) {
    RETURN_VALUE p1 = eval(p->data.function.op1);
    RETURN_VALUE p2 = eval(p->data.function.op2);
    double op1 = p1.value;
    double op2 = p2.value;
    RETURN_VALUE *result = calloc(1, sizeof(RETURN_VALUE));
    result->type = REAL_TYPE;
    if(p1.type == INTEGER_TYPE && p2.type == INTEGER_TYPE) {
        result->type = INTEGER_TYPE;
    }
    OPER_TYPE op = resolveFunc(p->data.function.name);
    switch (op) {
        case NEG_OPER:
            result->type = p1.type;
            result->value = -op1;
            break;
        case ABS_OPER:
            result->type = p1.type;
            result->value = fabs(op1);
            break;
        case EXP_OPER:
            result->type = p1.type;
            result->value = exp(op1);
            break;
        case SQRT_OPER:
            result->type = p1.type;
            result->value = sqrt(op1);
            break;
        case ADD_OPER:
            result->value = op1 + op2;
            break;
        case SUB_OPER:
            result->value = op1 - op2;
            break;
        case MULT_OPER:
            result->value = op1 * op2;
            break;
        case DIV_OPER:
            if (isnan(op2) || op2 == 0) {
                result->value = NaN;
                break;
            }
            result->value = op1 / op2;
            break;
        case REMAINDER_OPER:
            result->value = remainder(op1, op2);
            break;
        case LOG_OPER:
            result->type = p1.type;
            result->value = log(op1);
            break;
        case POW_OPER:
            result->value = pow(op1, op2);
            break;
        case MAX_OPER:
            result->value = fmax(op1, op2);
            break;
        case MIN_OPER:
            result->value = fmin(op1, op2);
            break;
        case EXP2_OPER:
            result->type = p1.type;
            result->value = exp2(op1);
            break;
        case CBRT_OPER:
            result->type = p1.type;
            result->value = cbrt(op1);
            break;
        case HYPOT_OPER:
            result->value = hypot(op1, op2);
            break;
        case CUSTOM_FUNC:
            break;
        case SIN_OPER:
            result->type = p1.type;
            result->value = sin(op1);
            break;
        case COS_OPER:
            result->type = p1.type;
            result->value = cos(op1);
            break;
        case TAN_OPER:
            result->type = p1.type;
            result->value = tan(op1);
            break;
        case PRINT_OPER:
            result->type = p1.type;
            switch (result->type) {
                case NO_TYPE:
                case REAL_TYPE:
                    result->value = p1.value;
                    printf("=> %.2f", result->value);
                    break;
                case INTEGER_TYPE:
                    result->value = (int) p1.value;
                    printf("=> %d", (int) result->value);
                    break;
            }
            break;
    }
    return *result;
}

RETURN_VALUE evalSymbol(AST_NODE *p) {
    AST_NODE *parent = p;
    while (parent != NULL) {
        SYMBOL_TABLE_NODE *cN = parent->symbolTable;
        while (cN != NULL) {
            if (strcmp(cN->ident, p->data.symbol.name) == 0) {
                double literalVal = eval(cN->val).value;
                if(cN->val_type == INTEGER_TYPE) {
                    literalVal = (int) literalVal;
                }
                RETURN_VALUE *result = calloc(1, sizeof(RETURN_VALUE));
                result->type = cN->val_type;
                result->value = literalVal;
                return *result;
            }
            cN = cN->next;
        }
        parent = parent->parent;
    }
    char *error = malloc(128 * sizeof(char));
    sprintf(error, "The variable %s is undefined", p->data.symbol.name);
    yyerror(error);
    free(error);
    exit(0);
}

RETURN_VALUE numVal(double num) {
    RETURN_VALUE *result = calloc(1, sizeof(RETURN_VALUE));
    result->type = NO_TYPE;
    result->value = num;
    return *result;
}

RETURN_VALUE zero() {
    return numVal(0);
}

RETURN_VALUE one() {
    return numVal(1);
}

//
// evaluate an abstract syntax tree
//
// p points to the root
//
RETURN_VALUE eval(AST_NODE *p) {
    if (!p){
        return zero();
    }


// TBD: implement
    if (p->type == NUM_TYPE) {

        return p->data.number.value;
    }

    if (p->type == FUNC_TYPE) {
        return evalFunc(p);
    }

    if (p->type == SYMBOL_TYPE) {
        return evalSymbol(p);
    }

    return zero();
}

SYMBOL_TABLE_NODE *createSymbol(char* type, char *symbol, AST_NODE *s_expr) {
    SYMBOL_TABLE_NODE *p = malloc(sizeof(SYMBOL_TABLE_NODE));

    if (p == NULL) {
        yyerror("out of memory");
    }

    if(type == NULL) {
        p->val_type = NO_TYPE;
    } else if(strcmp(type, "real") == 0) {
        p->val_type = REAL_TYPE;
    } else if(strcmp(type, "integer") == 0) {
        p->val_type = INTEGER_TYPE;
    } else {
        p->val_type = NO_TYPE;
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
    SYMBOL_TABLE_NODE *symbol = findSymbol(let_elem, let_elem);
    if(symbol == NULL) {
        let_elem->next = let_list;
        return let_elem;
    } else {
        symbol->val = let_elem->val;
        symbol->val->data = let_elem->val->data;
        freeSymbolTable(let_elem);
        return let_list;
    }
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
    AST_NODE *p = calloc(1, sizeof(AST_NODE));
    if (p == NULL)
        yyerror("out of memory");

    p->type = SYMBOL_TYPE;
    p->data.symbol.name = malloc(strlen(symb) + 1);
    strcpy(p->data.symbol.name, symb);
    return p;
}

void freeSymbolTable(SYMBOL_TABLE_NODE *node) {
    if (node == NULL) {
        return;
    }
    freeSymbolTable(node->next);
    free(node->ident);
    freeNode(node->val);
    free(node);
}

SYMBOL_TABLE_NODE *findSymbol(SYMBOL_TABLE_NODE *symbolTable, SYMBOL_TABLE_NODE *symbol) {
    if(symbol == NULL) {
        return NULL;
    }
    SYMBOL_TABLE_NODE *cNode = symbolTable;
    while(cNode != NULL) {
        if(strcmp(cNode->ident, symbol->ident) == 0) {
            return cNode;
        }
        cNode = cNode->next;
    }
    return NULL;
}
