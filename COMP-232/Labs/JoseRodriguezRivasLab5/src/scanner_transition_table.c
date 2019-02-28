//
// Lab5
// scanner_transition_table.c
//
// Assumes lectures: 1, 2, 3, 4

#include "scanner.h"

#define LINEBUFF 80

size_t lineBufferSize = LINEBUFF;

TOKEN *ungottenToken = NULL; // may be used by parser in the next lab

//
// return token to the input, so it can be analyzed again
//
void ungetToken(TOKEN **token) {
    ungottenToken = *token;
    *token = NULL;
}

//
// clean up the token structure
//
void freeToken(TOKEN **token) {
    if (*token == NULL)
        return;

    if ((*token)->strVal != NULL)
        free((*token)->strVal);

    free(*token);

    *token = NULL;
}

//
// check if a collected sequence of characters is a keyword
//
void updateTypeIfKeyword(TOKEN *token) {
// TODO Implement the function
}


TRANS_TABLE_TYPE *scanInit() {
    TRANS_TABLE_TYPE *returnTable = malloc(sizeof(TRANS_TABLE_TYPE));

// TODO Implement the function

    scanf("%d %d\n", &returnTable->numberOfStates, &returnTable->numberOfClasses);
    char *classLine = malloc(lineBufferSize);
    getline(&classLine, &lineBufferSize, stdin);
    char *delim = malloc(sizeof(char));
    *delim = ',';
    returnTable->inputSymbolClasses = malloc(sizeof(char *) * returnTable->numberOfClasses);
    char *currentClass;
    size_t currentSize;
    for (int i = 0; i < returnTable->numberOfClasses; i++) {
        currentClass = strsep(&classLine, delim);
        currentSize = strlen(currentClass + 1);
        returnTable->inputSymbolClasses[i] = malloc(currentSize);
        strcpy(returnTable->inputSymbolClasses[i], currentClass);
    }

    return returnTable;
}

int findIndexToClass(TRANS_TABLE_TYPE *transitionTable, char c) {
    int class;

// TODO Implement the function

    return class;
}

TOKEN *scanner(TRANS_TABLE_TYPE *transitionTable) {
    TOKEN *token = NULL;

// TODO Implement the functions

    return token;
}



