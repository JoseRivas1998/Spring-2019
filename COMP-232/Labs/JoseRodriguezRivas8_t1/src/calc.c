/**
* Name: Jose de Jesus Rodriguez Rivas
* Lab: Lab 8_t1
* Date: 03/26/19
**/
#include "calc.h"

void yyerror(char *s) {
    printf("\nERROR: %s\n", s);
    // note stderr that normally defaults to stdout, but can be redirected: ./src 2> src.log
    // CLion will display stderr in a different color from stdin and stdout
}

/*
 * The function to resolve a name of a function; i.e., to translate it to an int equivalent (if possible)
 * that can be used conveniently in the src() function.
 */
int resolveFunc(char *func) {
    // all functions are exactly as they appear in math.h; use man to get details
    char *funcs[] = {"neg",
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
                     ""};

    int i = 0;
    while (funcs[i][0] != '\0') {
        if (!strcmp(funcs[i], func))
            return i;

        i++;
    }
    yyerror("invalid function"); // paranoic -- should never happen
    return -1;
}

/*
 * The function to calculate simple math operation.
 *
 * The values of op1 and op2 may be omitted for functions that take one or no parameters.
 */
double calc(char *func, double op1, double op2) {

// TODO: implement the function, so it returns correct values for each set of parameters
    if (isnan(op1)) {
        return nan("nan operand");
    }
    CALC_FUNC toRun = resolveFunc(func);
    switch (toRun) {
        case NEG:
            return op1 * -1.0;
        case ABS:
            return fabs(op1);
        case EXP:
            return exp(op1);
        case SQRT:
            return sqrt(op1);
        case ADD:
            return op1 + op2;
        case SUB:
            return op1 - op2;
        case MULT:
            return op1 * op2;
        case DIV:
            return op1 / op2;
        case REMAINDER:
            return remainder(op1, op2);
        case LOG:
            if(isnan(op2)) {
                return log(op1);
            }
            return log(op2) / log(op1);
        case POW:
            return pow(op1, op2);
        case MAX:
            return op1 > op2 ? op1 : op2;
        case MIN:
            return op1 < op2 ? op1 : op2;
        case EMPTY:
            break;
    }
    return 0.0;

}  
