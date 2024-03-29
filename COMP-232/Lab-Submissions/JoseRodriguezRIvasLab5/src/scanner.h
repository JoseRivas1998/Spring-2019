// Lab5
//  scanner.h
//
/**
* Name: Jose de Jesus Rodriguez Rivas
* Lab: Lab 5
* Date: 03/04/19
**/
#ifndef __SCANNER_H
#define __SCANNER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef enum {
    INVALID_TOKEN = 0,
    NUMBER_TOKEN, //1
    IDENT_TOKEN,  //2
    ASSIGNMENT,   //3
    SEMICOLON,    //4
    LPAREN,       //5
    RPAREN,       //6
    PLUS,         //7
    MINUS,        //8
    MULT,         //9
    DIV,          //10
    MOD,          //11
    REPEAT,
    PRINT,
    END_OF_INPUT_TOKEN
} TOKEN_TYPE;

typedef struct token {
    TOKEN_TYPE type;
    char *strVal;
} TOKEN;

typedef struct {
    int numberOfStates;
    int numberOfClasses;
    char **inputSymbolClasses;
    char **table;
} TRANS_TABLE_TYPE;

TRANS_TABLE_TYPE *scanInit();

void updateTypeIfKeyword(TOKEN *token);

int findIndexToClass(TRANS_TABLE_TYPE *transitionTable, char c);

TOKEN *scanner(TRANS_TABLE_TYPE *outputTable);

void ungetToken(TOKEN **);

void freeToken(TOKEN **);

char *escapeStringsToChars(char *str);

void readCharClasses(TRANS_TABLE_TYPE *returnTable);

void readTransTable(TRANS_TABLE_TYPE *returnTable);

void copyStringToStrVal(TOKEN *token, char *str);

char* getNthString(int n, char *str, const char *delim);

#define BUF_SIZE 128
#define MAX_LINE_LENGTH 256

#endif