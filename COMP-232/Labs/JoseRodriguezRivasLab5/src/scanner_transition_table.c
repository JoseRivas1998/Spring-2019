//
// Lab5
// scanner_transition_table.c
//
// Assumes lectures: 1, 2, 3, 4

#include "scanner.h"

size_t lineBufferSize = MAX_LINE_LENGTH;

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
    readCharClasses(returnTable);
    readTransTable(returnTable);
    return returnTable;
}

void readCharClasses(TRANS_TABLE_TYPE *returnTable) {
    // Read the next line in the file, which is the list of classes
    char *classLine = malloc(sizeof(char) * lineBufferSize);
    scanf("%[^\n]", classLine);
    scanf("%*c");
    // Make sure \n and \t are read as the actual chars, not \\n or \\t
    char *escapedClassline = escapeStringsToChars(classLine);
    // Each class is separated by a comma in the file
    char *delim = malloc(sizeof(char));
    *delim = ',';
    returnTable->inputSymbolClasses = malloc(sizeof(char *) * returnTable->numberOfClasses);
    char *currentClass;
    size_t currentSize;
    for (int i = 0; i < returnTable->numberOfClasses; i++) {
        // Read next class into temp string
        currentClass = strsep(&escapedClassline, delim);
        currentSize = strlen(currentClass) + 1;
        // Copy the temp string into the symbol class
        returnTable->inputSymbolClasses[i] = malloc(currentSize);
        strcpy(returnTable->inputSymbolClasses[i], currentClass);
    }
    // thank you C
    free(delim);
    free(classLine);
    free(escapedClassline);
}

void readTransTable(TRANS_TABLE_TYPE *returnTable) {
    // The table is represented by an array of strings, each string is a row in the table
    // Each row is a series of state transitions separated by a space, each transition can be an a, an e, or a number
    returnTable->table = malloc(sizeof(char *) * returnTable->numberOfStates);
    for (int i = 0; i < returnTable->numberOfStates; i++) {
        // Simply read the line from the file directly into the current row
        returnTable->table[i] = malloc(sizeof(char) * lineBufferSize);
        scanf("%[^\n]", returnTable->table[i]);
        scanf("%*c");
    }
}


int findIndexToClass(TRANS_TABLE_TYPE *transitionTable, char c) {
    int class;

// TODO Implement the function
    bool found = false;
    class = -1; // Return -1 if the given char is not in a symbol class
    int currentIndex;
    char checkChar;
    for (int i = 0; i < transitionTable->numberOfClasses && !found; i++) {
        currentIndex = 0;
        do {
            checkChar = transitionTable->inputSymbolClasses[i][currentIndex++];
            if(checkChar == c) {
                found = true;
                class = i;
            }
        } while(!found && checkChar != '\0');
    }
    return class;
}

TOKEN *scanner(TRANS_TABLE_TYPE *transitionTable) {
    TOKEN *token = NULL;

// TODO Implement the functions


    return token;
}

char *escapeStringsToChars(char *str) {
    size_t len = strlen(str) + 1;
    char *tempString = malloc(len);
    int index = 0;
    char c;
    int strIndex = 0; // Index of the current character in the string
    do {
        c = str[strIndex++];
        if (c == '\\') { // If current character is a backslash
            c = str[strIndex++]; // then read the next character in the string
            switch (c) {
                case 'n':
                    c = '\n';
                    break;
                case 't':
                    c = '\t';
                    break;
                default:
                    break;
            }
        }
        tempString[index++] = c;
    } while (c != '\0');
    tempString[index] = '\0'; // Null terminate that boy
    return tempString;
}



