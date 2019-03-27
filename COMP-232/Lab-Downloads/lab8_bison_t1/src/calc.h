#ifndef __calc_h_
#define __calc_h_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

// the following include file is generated automatically by CMake (along the scanner and the parser)
#include "calcParser.h"

// declaring the following Bison functions limits compiler warnings
int yyparse(void);
int yylex(void);
void yyerror(char *);

// declaration of the function to calculate s-expressions
double calc(char *, double, double);

#endif
