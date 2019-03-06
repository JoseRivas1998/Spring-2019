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
}

void printPrintStmt(NODE *node) {
//   TODO: implement
}

void printExpr(NODE *node) {
//   TODO: implement
    puts("=> START expression");
    printTerm(node->leftNode);
    if(node->rightNode != NULL) {
        printf("%c\n", node->data.op);
        printExpr(node->rightNode);
    }
    puts("=> START expression");
}

void printTerm(NODE *node) {
//   TODO: implement
    puts("=> START expression");
    printFactor(node->leftNode);
    if(node->rightNode != NULL) {
        printf("%c\n", node->data.op);
        printExpr(node->rightNode);
    }
    puts("=> START expression");
}

void printFactor(NODE *node) {
//   TODO: implement
}

void printId(NODE *node) {
//   TODO: implement
    puts("=> START identifier");
    printf("<id> %s\n", node->data.identifier);
    puts("=> END identifier");
}

void printNumber(NODE *node) {
//   TODO: implement
}

