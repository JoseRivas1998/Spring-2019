/**
* Name: Jose de Jesus Rodriguez Rivas
* Lab: Lab 6
* Date: 03/07/19
**/
#ifndef __EVAL_H
#define __EVAL_H

#include "parser.h"

void printProgram(NODE *node);
void printStatement(NODE *node);
void printAssignStmt(NODE *node);
void printRepeatStmt(NODE *node);
void printPrintStmt(NODE *node);
void printExpr(NODE *node);
void printTerm(NODE *node);
void printFactor(NODE *node);
void printId(NODE *node);
void printNumber(NODE *node);

#endif