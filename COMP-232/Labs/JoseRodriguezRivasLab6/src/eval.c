#include "eval.h"

void printProgram(NODE *node)
{
    printf("=> START program\n");
    if (node->leftNode != NULL)
        printStatement(node->leftNode);
    if (node->rightNode != NULL)
        printProgram(node->rightNode);
    printf("=> END program\n");
}

void printStatement(NODE *node)
{
//   TODO: implement
}

void printAssignStmt(NODE *node)
{
//   TODO: implement
}

void printRepeatStmt(NODE *node)
{
//   TODO: implement
}

void printPrintStmt(NODE *node)
{
//   TODO: implement
}

void printExpr(NODE *node)
{
//   TODO: implement
}

void printTerm(NODE *node)
{
//   TODO: implement
}

void printFactor(NODE *node)
{
//   TODO: implement
}

void printId(NODE *node)
{
//   TODO: implement
}

void printNumber(NODE *node)
{
//   TODO: implement
}

