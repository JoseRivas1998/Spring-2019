/**
* Name: Jose de Jesus Rodriguez Rivas
* Lab: Lab 8_t2
* Date: 03/26/19
**/
#include "ciProlog.h"

// the knowledge base
// a linked list of propositions
// if a proposition is on the list, it is assumed to be true
// anything not on the list is false
// the first element is empty; it is used as an anchor for kb_head and kb_tail
// we always add at kb_tail
// we always search from kb_head->next;

PROP_TYPE *kb_head, *kb_tail;

void initKnowledgeBase(void)
{
    kb_head = kb_tail = (PROP_TYPE *) malloc(sizeof(PROP_TYPE)); // always empty head of the list
    kb_head->name = ""; // indicates the empty head; skip in searches
    kb_head->next = NULL;
}

void yyerror(char *s)
{
    fprintf(stderr, "yyerror: %s\n", s);
}

bool not(bool logexpr1)
{
    // TODO implement the function

    return !logexpr1;
}

bool and(bool logexpr1, bool logexpr2)
{
    // TODO implement the function

    return logexpr1 && logexpr2;
}

bool or(bool logexpr1, bool logexpr2)
{
    // TODO implement the function

    return logexpr1 || logexpr2;
}

// add the assertion to the database
// finding a proposition in the list makes it true
bool assert(char *proposition)
{
    // TODO implement the function
    PROP_TYPE *curType = kb_head->next;
    while(curType != NULL) {
        if(strcmp(curType->name, proposition) == 0) {
            return false;
        }
        curType = curType->next;
    }
    PROP_TYPE *toAdd = (PROP_TYPE *) malloc(sizeof(PROP_TYPE));
    toAdd->next = NULL;
    toAdd->name = (char *) malloc((strlen(proposition) + 1) * sizeof(char));
    strcpy(toAdd->name, proposition);
    kb_tail->next = toAdd;
    kb_tail = toAdd;
    return true;
}

// remove the assertion to the database
// after that the proposition is assumed to be false -- it cannot be found
bool retract(char *proposition)
{
    // TODO implement the function
    PROP_TYPE *curType = kb_head->next;
    PROP_TYPE *preType = kb_head;
    while(curType != NULL) {
        if(strcmp(curType->name, proposition) == 0) {
            preType->next = curType->next;
            if(preType->next == NULL) {
                kb_tail = preType;
            }
            free(curType->name);
            free(curType);
            return true;
        }
        preType = curType;
        curType = preType->next;
    }
    return false;
}

// find the proposition in the knowledge base
// if found, return true
// otherwise, return false
bool eval(char *proposition)
{
    // TODO implement the function
    PROP_TYPE *curType = kb_head->next;
    while(curType != NULL) {
        if(strcmp(curType->name, proposition) == 0) {
            return true;
        }
        curType = curType->next;
    }
    return false;
};
