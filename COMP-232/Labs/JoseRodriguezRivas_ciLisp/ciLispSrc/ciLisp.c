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
AST_NODE *function(char *funcName, AST_NODE *opList) {
    AST_NODE *p = calloc(1, sizeof(AST_NODE));
    if (p == NULL)
        yyerror("out of memory");

    p->type = FUNC_TYPE;
    p->data.function.name = funcName;
    p->data.function.opList = opList;
    AST_NODE *cN = opList;
    while (cN != NULL) {
        cN->parent = p;
        cN = cN->next;
    }

    return p;
}

//
// free a node
//
void freeNode(AST_NODE *p) {
    if (!p)
        return;

    freeNode(p->next);

    if (p->type == FUNC_TYPE) {
        free(p->data.function.name);
        freeNode(p->data.function.opList);
    }

    if (p->type == SYMBOL_TYPE) {
        free(p->data.symbol.name);
    }

    freeSymbolTable(p->symbolTable);

    free(p);
}

void evalUnary(RETURN_VALUE *out, OPER_TYPE operation, AST_NODE *p, AST_NODE *opList) {
    RETURN_VALUE p1 = eval(opList);
    double op = p1.value;
    out->type = p1.type;
    switch (operation) {
        case NEG_OPER:
            out->value = -op;
            break;
        case ABS_OPER:
            out->value = fabs(op);
            break;
        case EXP_OPER:
            out->value = exp(op);
            break;
        case SQRT_OPER:
            out->value = sqrt(op);
            break;
        case LOG_OPER:
            out->value = log(op);
            break;
        case EXP2_OPER:
            out->value = exp2(op);
            break;
        case CBRT_OPER:
            out->value = cbrt(op);
            break;
        case SIN_OPER:
            out->value = sin(op);
            break;
        case COS_OPER:
            out->value = cos(op);
            break;
        case TAN_OPER:
            out->value = tan(op);
            break;
        default:
            break;
    }
}

void evalBinary(RETURN_VALUE *out, OPER_TYPE operation, AST_NODE *p, AST_NODE *opList) {
    if (opList->next == NULL) {
        yyerror("Expected two params for operation.");
    }
    RETURN_VALUE p1 = eval(opList);
    RETURN_VALUE p2 = eval(opList->next);
    out->type = REAL_TYPE;
    if(p1.type == INTEGER_TYPE && p2.type == INTEGER_TYPE) {
        out->type = INTEGER_TYPE;
    }
    double op1 = p1.value;
    double op2 = p2.value;
    switch (operation) {
        case SUB_OPER:
            out->value = op1 - op2;
            break;
        case DIV_OPER:
            if(isnan(op2) || op2 == 0) {
                out->value = NaN;
                out->type = NO_TYPE;
            } else {
                out->value = op1 / op2;
            }
            break;
        case REMAINDER_OPER:
            out->value = remainder(op1, op2);
            break;
        case POW_OPER:
            out->value = pow(op1, op2);
            break;
        case MAX_OPER:
            out->value = fmax(op1, op2);
            break;
        case MIN_OPER:
            out->value = fmin(op1, op2);
            break;
        case HYPOT_OPER:
            out->value = hypot(op1, op2);
            break;
        default:
            break;
    }
}

void printFunc(RETURN_VALUE *out, RETURN_VALUE param , bool isFirst) {
    if(isFirst) {
        printf("=> ");
    }
    out->type = param.type;
    out->value = param.value;
    if(param.type == INTEGER_TYPE) {
        out->value = (int) out->value;
        printf("%d ", (int) out->value);
    } else {
        printf("%.2lf ", out->value);
    }
}

void evalArbitrary(RETURN_VALUE *out, OPER_TYPE operation, AST_NODE *p, AST_NODE *opList) {
    if(!opList) {
        return;
    }
    RETURN_VALUE param1 = eval(opList);
    out->value = param1.value;
    out->type = param1.type == NO_TYPE ? REAL_TYPE : param1.type;

    AST_NODE *cN = opList->next;
    if(operation == PRINT_OPER) printFunc(out, param1, true);
    while (cN != NULL) {
        RETURN_VALUE param = eval(cN);
        if(out->type == INTEGER_TYPE && param.type != INTEGER_TYPE) {
            out->type = REAL_TYPE;
        }
        switch (operation) {
            case ADD_OPER:
                out->value += param.value;
                break;
            case MULT_OPER:
                out->value *= param.value;
                break;
            case PRINT_OPER:
                printFunc(out, param, false);
                break;
            default:
                break;
        }
        cN = cN->next;
    }

}

RETURN_VALUE evalFunc(AST_NODE *p) {
    RETURN_VALUE *result = calloc(1, sizeof(RETURN_VALUE));
    result->type = NO_TYPE;
    OPER_TYPE op = resolveFunc(p->data.function.name);
    switch (op) {
        case NEG_OPER:
        case ABS_OPER:
        case EXP_OPER:
        case SQRT_OPER:
        case LOG_OPER:
        case EXP2_OPER:
        case CBRT_OPER:
        case SIN_OPER:
        case COS_OPER:
        case TAN_OPER:
            evalUnary(result, op, p, p->data.function.opList);
            break;
        case SUB_OPER:
        case DIV_OPER:
        case REMAINDER_OPER:
        case POW_OPER:
        case MAX_OPER:
        case MIN_OPER:
        case HYPOT_OPER:
            evalBinary(result, op, p, p->data.function.opList);
            break;
        case ADD_OPER:
        case MULT_OPER:
        case PRINT_OPER:
            evalArbitrary(result, op, p, p->data.function.opList);
            break;
        case CUSTOM_FUNC:
        default:
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
                if (cN->val_type == INTEGER_TYPE) {
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
    if (!p) {
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

SYMBOL_TABLE_NODE *createSymbol(char *type, char *symbol, AST_NODE *s_expr) {
    SYMBOL_TABLE_NODE *p = malloc(sizeof(SYMBOL_TABLE_NODE));

    if (p == NULL) {
        yyerror("out of memory");
    }

    if (type == NULL) {
        p->val_type = NO_TYPE;
    } else if (strcmp(type, "real") == 0) {
        p->val_type = REAL_TYPE;
    } else if (strcmp(type, "integer") == 0) {
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
    SYMBOL_TABLE_NODE *symbol = findSymbol(let_list, let_elem);
    if (symbol == NULL) {
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
    if (symbol == NULL) {
        return NULL;
    }
    SYMBOL_TABLE_NODE *cNode = symbolTable;
    while (cNode != NULL) {
        if (strcmp(cNode->ident, symbol->ident) == 0) {
            return cNode;
        }
        cNode = cNode->next;
    }
    return NULL;
}

AST_NODE *addNodeToList(AST_NODE *toAdd, AST_NODE *list) {
    if (toAdd == NULL) {
        return list;
    }

    toAdd->next = list;
    return toAdd;
}
