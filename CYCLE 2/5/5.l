%{

#include <stdio.h>
#include "y.tab.h"

%}

%%

[0-9]+                 {return num; }
[a-zA-Z_][a-zA-Z_0-9]*  {return id; }
[+\-*/]                {return op; }
\n                          return 0;
.                      {return yytext[0];}
%%

int yywrap(){return 1;}