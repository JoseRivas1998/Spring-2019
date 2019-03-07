/**
* Name: Jose de Jesus Rodriguez Rivas
* Lab: Lab 6
* Date: 03/07/19
**/
#include "eval.h"
#include "parser.h"

void printProgram(NODE *node) {
    printf("=> START program\n");
    if (node->leftNode != NULL)
        printStatement(node->leftNode);
    if (node->rightNode != NULL)
        printProgram(node->rightNode);
    printf("=> END program\n");
}

void printStatement(NODE *node) {
//   TODO: implement - done
    puts("=> START statement");
    switch (node->leftNode->type) {
        case ASSIGN_STMT_NODE:
            printAssignStmt(node->leftNode);
            break;
        case REPEAT_STMT_NODE:
            printRepeatStmt(node->leftNode);
            break;
        case PRINT_STMT_NODE:
            printPrintStmt(node->leftNode);
            break;
        default:
            break;
    }
    puts("=> END statement");
}

void printAssignStmt(NODE *node) {
//   TODO: implement
    puts("=> START assignment");
    printId(node->leftNode);
    printExpr(node->rightNode);
    puts("=> END assignment");
}

void printRepeatStmt(NODE *node) {
//   TODO: implement
    puts("=> START repeat");
    printExpr(node->leftNode);
    printStatement(node->rightNode);
    puts("=> END repeat");
}

void printPrintStmt(NODE *node) {
//   TODO: implement
    puts("=> START print");
    printExpr(node->leftNode);
    puts("=> END print");
}

void printExpr(NODE *node) {
//   TODO: implement
    puts("=> START expression");
    printTerm(node->leftNode);
    if (node->rightNode != NULL) {
        printf("%c\n", node->data.op);
        printExpr(node->rightNode);
    }
    puts("=> END expression");
}

void printTerm(NODE *node) {
//   TODO: implement
    puts("=> START term");
    printFactor(node->leftNode);
    if (node->rightNode != NULL) {
        printf("%c\n", node->data.op);
        printExpr(node->rightNode);
    }
    puts("=> END term");
}

void printFactor(NODE *node) {
//   TODO: implement
    puts("=> START factor");
    switch (node->leftNode->type) {
        case IDENTIFIER_NODE:
            printId(node->leftNode);
            break;
        case NUMBER_NODE:
            printNumber(node->leftNode);
            break;
        case FACTOR_NODE:
            printf("%c\n", node->data.op);
            printFactor(node->leftNode);
            break;
        case EXPR_NODE:
            printExpr(node->leftNode);
            break;
        default:
            break;
    }
    puts("=> END factor");
}

void printId(NODE *node) {
//   TODO: implement
    puts("=> START identifier");
    printf("<id> %s\n", node->data.identifier);
    puts("=> END identifier");
}

void printNumber(NODE *node) {
//   TODO: implement
    puts("=> START number");
    printf("<number> %lf\n", node->data.number);
    puts("=> END number");
}

