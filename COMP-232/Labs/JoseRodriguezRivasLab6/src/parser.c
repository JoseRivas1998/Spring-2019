#include "parser.h"

TOKEN *getNextToken(TOKEN **token) {
    freeToken(token);
    return scannerAdHoc();
}

NODE *program() {
    NODE *node = malloc(sizeof(NODE));
    node->type = PROGRAM_NODE;
    node->leftNode = statement();
    if (node->leftNode != NULL)
        node->rightNode = program();
    return node;
}

NODE *statement() {
//   TODO: implement
}

NODE *assignStmt(TOKEN **currToken) {
//   TODO: implement
}

NODE *repeatStmt(TOKEN **currToken) {
//   TODO: implement
}

NODE *printStmt(TOKEN **currToken) {
//   TODO: implement
}

NODE *expr(TOKEN **currToken) {
//   TODO: implement
}

NODE *term(TOKEN **currToken) {
//   TODO: implement
}

NODE *factor(TOKEN **currToken) {
//   TODO: implement
}

NODE *id(TOKEN **currToken) {
//   TODO: implement
}

NODE *number(TOKEN **currToken) {
//   TODO: implement
}

void error(char *errorMessage) {
    printf("PARSING ERROR: %s\nExiting...\n", errorMessage);
    exit(1);
}
