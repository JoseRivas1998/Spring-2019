#ifndef __flex_t1_h_
#define __flex_t1_h_

#include <stdio.h>

typedef enum {
      IF_TOKEN = 258, // since Bison will start token at that number
      THEN_TOKEN,
      // and so on...
   } TOKEN;

int yylex(void);
void yyerror(char *s);

#endif
