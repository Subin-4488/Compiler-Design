%{

#include <stdio.h>
#include "y.tab.h"

%}

%%

[0-9]+                 {printf("NUM: %s\n", yytext);   return num; }
[a-zA-Z_][a-zA-Z_0-9]*  {printf("ID: %s\n", yytext);   return id; }
[+\-*/]                {printf("OP: %s\n", yytext);   return op; }
\n                          return 0;
.                      {printf("REM: %c\n", yytext[0]); return yytext[0];}
%%

int yywrap(){return 1;}