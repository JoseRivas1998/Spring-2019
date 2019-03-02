// Lab5
//  main.c (driver for a scanner test)
//
//  ASSUMES: Lecture 1, 2, 3, 4

#include "scanner.h"
#include <unistd.h>

void printTalbeDebug(TRANS_TABLE_TYPE *table) {
    puts("Character classes:");
    for (int i = 0; i < table->numberOfClasses; ++i) {
        printf("%d\t%s\n", i, table->inputSymbolClasses[i]);
    }
    puts("State Transitions");
    for(int i = 0; i < table->numberOfStates; i++) {
        printf("%d\t%s\n", i, table->table[i]);
    }
}

int main(int argc, char** argv)
{
    TOKEN *token = NULL;
    char *token2str[] = {"INVALID", "NUMBER", "IDENT", "ASSIGNMENT", "SEMICOLON", "LPAREN", "RPAREN", "PLUS", "MINUS",
                         "MULT", "DIV", "MOD", "REPEAT", "PRINT", "END_OF_INPUT"};

    int savedstdin = dup(0); // save stdin file descriptor

    freopen(argv[1], "r", stdin); // possibly switch stdin to get the table from the file

    TRANS_TABLE_TYPE *transitionTable = scanInit();
    printTalbeDebug(transitionTable);

    dup2(savedstdin, 0);  // restore the original stdin, so we can read the input data from stdin

    freopen(argv[2], "r", stdin);

    while ((token = scanner(transitionTable)) != NULL)
    {
        if ( token->strVal == NULL)
            printf("{%s}\n", token2str[token->type]);
        else
            printf("{%s, %s}\n", token2str[token->type], token->strVal);
        freeToken(&token);
        fflush(stdout);
    }
    printf("\n");
}