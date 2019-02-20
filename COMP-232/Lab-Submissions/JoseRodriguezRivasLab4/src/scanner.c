/**
* Name: Jose de Jesus Rodriguez Rivas
* Lab: Lab 4
* Date: 02/20/19
**/
#include "scannerNestedCases.h"

TOKEN *scannerNestedCases() {
    TOKEN *token = malloc(sizeof(TOKEN));
    char tempString[BUF_SIZE];
    int curIndex = 0;
    token->type = INVALID_TOKEN;
    token->strVal = NULL;
    int state = 1;
    char c;
    while ((token->type == INVALID_TOKEN) && ((c = getchar()) != EOF)) {
        switch (state) {
            case 1:
                switch (c) {
                    case ' ':
                    case '\t':
                    case '\n':
                        break; // Skip whitespace
                    case '*':
                        state = 2;
                        break;
                    case '/':
                        state = 3;
                        break;
                    case '+':
                        state = 4;
                        break;
                    case '-':
                        state = 5;
                        break;
                    case '%':
                        state = 6;
                        break;
                    case ';':
                        state = 7;
                        break;
                    case '(':
                        state = 8;
                        break;
                    case ')':
                        state = 9;
                        break;
                    case '=':
                        state = 10;
                        break;
                    case '0'...'9':
                        tempString[curIndex] = c;
                        state = 11;
                        curIndex++;
                        break;
                    case 'a'...'z':
                        tempString[curIndex] = c;
                        state = 12;
                        curIndex++;
                        break;
                    default: // Anything else
                        token->type = INVALID_TOKEN;
                        return token;
                }
                break;
            case 2: // mult state
                ungetc(c, stdin);
                token->type = MULT_TOKEN;
                copyIntoStringValue(token, "*");
                break;
            case 3:
                ungetc(c, stdin);
                token->type = DIV_TOKEN;
                copyIntoStringValue(token, "/");
                break;
            case 4:
                ungetc(c, stdin);
                token->type = PLUS_TOKEN;
                copyIntoStringValue(token, "+");
                break;
            case 5:
                ungetc(c, stdin);
                token->type = MINUS_TOKEN;
                copyIntoStringValue(token, "-");
                break;
            case 6:
                ungetc(c, stdin);
                token->type = MOD_TOKEN;
                copyIntoStringValue(token, "%");
                break;
            case 7:
                ungetc(c, stdin);
                token->type = SEMICOLON_TOKEN;
                copyIntoStringValue(token, ";");
                break;
            case 8:
                ungetc(c, stdin);
                token->type = LPAREN_TOKEN;
                copyIntoStringValue(token, "(");
                break;
            case 9:
                ungetc(c, stdin);
                token->type = RPAREN_TOKEN;
                copyIntoStringValue(token, ")");
                break;
            case 10:
                ungetc(c, stdin);
                token->type = ASSIGNMENT_TOKEN;
                copyIntoStringValue(token, "=");
                break;
            case 11:
                switch (c) {
                    case '0'...'9':
                        // If current char is still a digit, collect it and return to top of loop
                        tempString[curIndex] = c;
                        curIndex++;
                        state = 11;
                        break;
                    default:
                        // Otherwise, push back the current char, copy the read number into the token
                        ungetc(c, stdin);
                        tempString[curIndex] = '\0';
                        token->type = NUMBER_TOKEN;
                        copyIntoStringValue(token, tempString);
                        break;
                }
                break;
            case 12:
                switch (c) {
                    case 'a'...'z':
                        // If current char is still a letter, collect it and return to top of loop
                        tempString[curIndex] = c;
                        curIndex++;
                        state = 12;
                        break;
                    default:
                        // Otherwise, push back the current char
                        ungetc(c, stdin);
                        tempString[curIndex] = '\0';
                        // If the read string is not a keyword, it is an identifier
                        if(!isKeyword(token, tempString)) {
                            token->type = IDENT_TOKEN;
                        }
                        // Copy the read string into the token
                        copyIntoStringValue(token, tempString);
                        break;
                }
                break;
        }
    }
    if (c == EOF)
    {
        free(token);
        return NULL;
    }
    return token;
}

void copyIntoStringValue(TOKEN *token, char *strToCpy) {
    token->strVal = (char *) malloc((strlen(strToCpy) + 1) * sizeof(char));
    strcpy(token->strVal, strToCpy);
}
