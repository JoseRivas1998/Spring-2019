/**
* Name: Jose de Jesus Rodriguez Rivas
* Lab: Lab 6
* Date: 03/07/19
**/
#include "parser.h"

bool tokenIsType(TOKEN **token, TOKEN_TYPE type) {
    return (*token)->type == type;
}

NODE *getEmptyNode(NODE_TYPE type) {
    NODE *node = malloc(sizeof(NODE));
    node->leftNode = NULL;
    node->rightNode = NULL;
    node->type = type;
    return node;
}

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
//   TODO: implement - done
    TOKEN *currToken = getNextToken(NULL);
    NODE *node = getEmptyNode(STATEMENT_NODE);
    if (currToken == NULL || tokenIsType(&currToken, END_OF_INPUT_TOKEN)) {
        return NULL;
    }
    if (currToken->type == IDENT_TOKEN) {
        ungetToken(&currToken);
        node->leftNode = assignStmt(&currToken);
    } else if (currToken->type == REPEAT_TOKEN) {
        ungetToken(&currToken);
        node->leftNode = repeatStmt(&currToken);
    } else if (currToken->type == PRINT_TOKEN) {
        ungetToken(&currToken);
        node->leftNode = printStmt(&currToken);
    } else {
        error("Expected id, repeat, or print token");
    }
    freeToken(&currToken);
    return node;
}

NODE *assignStmt(TOKEN **currToken) {
//   TODO: implement - done
    NODE *node = getEmptyNode(ASSIGN_STMT_NODE);
    node->leftNode = id(currToken);
    *currToken = getNextToken(currToken);
    if (!tokenIsType(currToken, ASSIGNMENT_TOKEN)) {
        error("Unexpected token, expected =");
    }
    node->rightNode = expr(currToken);
    *currToken = getNextToken(currToken);
    if (!tokenIsType(currToken, SEMICOLON_TOKEN)) {
        error("Unexpected token, expected ;");
    }
    return node;
}

NODE *repeatStmt(TOKEN **currToken) {
//   TODO: implement - done
    NODE *node = getEmptyNode(REPEAT_STMT_NODE);
    *currToken = getNextToken(currToken);
    if (!tokenIsType(currToken, REPEAT_TOKEN)) {
        error("Unexpected token, expected repeat");
    }
    *currToken = getNextToken(currToken);
    if (!tokenIsType(currToken, LPAREN_TOKEN)) {
        error("Unexpected token, expected (");
    }
    node->leftNode = expr(currToken);
    *currToken = getNextToken(currToken);
    if (!tokenIsType(currToken, RPAREN_TOKEN)) {
        error("Unexpected token, expected )");
    }
    node->rightNode = statement();
    *currToken = getNextToken(currToken);
    if (!tokenIsType(currToken, SEMICOLON_TOKEN)) {
        error("Unexpected token, expected ;");
    }
    return node;
}

NODE *printStmt(TOKEN **currToken) {
//   TODO: implement
    NODE *node = getEmptyNode(PRINT_STMT_NODE);
    *currToken = getNextToken(currToken);
    if (!tokenIsType(currToken, PRINT_TOKEN)) {
        error("Unexpected token, expected print.");
    }
    node->leftNode = expr(currToken);
    *currToken = getNextToken(currToken);
    if (!tokenIsType(currToken, SEMICOLON_TOKEN)) {
        error("Unexpected token, expected ;");
    }
    return node;
}

NODE *expr(TOKEN **currToken) {
//   TODO: implement - done
    NODE *node = getEmptyNode(EXPR_NODE);
    node->leftNode = term(currToken);
    *currToken = getNextToken(currToken);
    if (tokenIsType(currToken, PLUS_TOKEN) | tokenIsType(currToken, MINUS_TOKEN)) {
        node->data.op = (*currToken)->strVal[0];
        node->rightNode = expr(currToken);
    } else {
        ungetToken(currToken);
    }
    return node;
}

NODE *term(TOKEN **currToken) {
//   TODO: implement - done
    NODE *node = getEmptyNode(TERM_NODE);
    node->leftNode = factor(currToken);
    *currToken = getNextToken(currToken);
    if (tokenIsType(currToken, MULT_TOKEN) | tokenIsType(currToken, DIV_TOKEN) |
        tokenIsType(currToken, MOD_TOKEN)) {
        node->data.op = (*currToken)->strVal[0];
        node->rightNode = expr(currToken);
    } else {
        ungetToken(currToken);
    }
    return node;
}

NODE *factor(TOKEN **currToken) {
//   TODO: implement - done
    NODE *node = getEmptyNode(FACTOR_NODE);
    *currToken = getNextToken(currToken);
    if (tokenIsType(currToken, IDENT_TOKEN)) {
        ungetToken(currToken);
        node->leftNode = id(currToken);
    } else if (tokenIsType(currToken, NUMBER_TOKEN)) {
        ungetToken(currToken);
        node->leftNode = number(currToken);
    } else if (tokenIsType(currToken, MINUS_TOKEN)) {
        node->data.op = (*currToken)->strVal[0];
        node->leftNode = factor(currToken);
    } else if (tokenIsType(currToken, LPAREN_TOKEN)) {
        node->leftNode = expr(currToken);
        *currToken = getNextToken(currToken);
        if (!tokenIsType(currToken, RPAREN_TOKEN)) {
            error("Unexpected token, expected )");
        }
    } else {
        error("Invalid factor");
    }
    return node;
}

NODE *id(TOKEN **currToken) {
//   TODO: implement - done
    NODE *node = getEmptyNode(IDENTIFIER_NODE);
    *currToken = getNextToken(currToken);
    if (tokenIsType(currToken, IDENT_TOKEN)) {
        strcpy(node->data.identifier, (*currToken)->strVal);
    } else {
        error("Unexpected token, expected identifier");
    }
    return node;
}

NODE *number(TOKEN **currToken) {
//   TODO: implement - done
    NODE *node = getEmptyNode(NUMBER_NODE);
    *currToken = getNextToken(currToken);
    if (tokenIsType(currToken, NUMBER_TOKEN)) {
        sscanf((*currToken)->strVal, "%lf", &node->data.number);
    } else {
        error("Unexpected token, expected number");
    }
    return node;
}

void error(char *errorMessage) {
    printf("PARSING ERROR: %s\nExiting...\n", errorMessage);
    exit(1);
}
