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
    if((strcmp(token->strVal, "repeat")) == 0) {
        token->type = REPEAT;
    }else if((strcmp(token->strVal, "print")) == 0) {
        token->type = PRINT;
    }
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
            if (checkChar == c) {
                found = true;
                class = i;
            }
        } while (!found && checkChar != '\0');
    }
    return class;
}

TOKEN *scanner(TRANS_TABLE_TYPE *transitionTable) {
    TOKEN *token = NULL;
// TODO Implement the functions

    token = malloc(sizeof(token));
    token->type = INVALID_TOKEN;
    token->strVal = NULL;
    char tempString[BUF_SIZE];
    int index = 0;

    char c;
    int state = 0;
    int cClass = 0;
    char *nextState;
    char *toAccept;
    int acceptType = 0;
    bool firstEndOfFile = true;
    while((token->type == INVALID_TOKEN) && ((c = getchar()) != EOF || firstEndOfFile)) {
        if(c == EOF) {
            firstEndOfFile = false;
        }
        cClass = findIndexToClass(transitionTable, c);
        if(cClass == -1) {
            // If classes not found, use invalid class
            cClass = transitionTable->numberOfClasses;
        }
        nextState = getNthString(cClass, transitionTable->table[state], " ");
        if(nextState[0] == 'a') {
            ungetc(c, stdin);
            tempString[index] = '\0';
            copyStringToStrVal(token, tempString);
            toAccept = getNthString(transitionTable->numberOfClasses + 1, transitionTable->table[state], " ");
            sscanf(toAccept, "%d", &acceptType);
            token->type = acceptType;
            updateTypeIfKeyword(token);
        } else if(nextState[0] == 'e') {
            token->type = INVALID_TOKEN;
            break;
        } else {
            if(cClass != 12) tempString[index++] = c;
            sscanf(nextState, "%d", &state);
        }
        free(nextState);
    }
    if (c == EOF && token->type == INVALID_TOKEN)
    {
        free(token);
        return NULL;
    }
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

void copyStringToStrVal(TOKEN *token, char *str) {
    token->strVal = malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(token->strVal, str);
}

char* getNthString(int n, char *str, const char *delim) {
    char *result = NULL;
    char *toRead = malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(toRead, str); // Copy to new string
    char* currentStr = NULL;
    for(int i = 0; i <= n; i++) {
        currentStr = strsep(&toRead, delim);
    }
    result = malloc(sizeof(char) * (strlen(currentStr) + 1));
    strcpy(result,currentStr);
    return result;
}


