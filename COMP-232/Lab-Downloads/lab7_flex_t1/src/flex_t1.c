#include "flex_t1.h"

int main(void) {

   TOKEN tok;

   char *token[] = {"if", "then" /* and so on */};

   while ((tok = yylex()) != 0)
      printf("{<keyword> \"%s\"}", token[tok - IF_TOKEN]);
}