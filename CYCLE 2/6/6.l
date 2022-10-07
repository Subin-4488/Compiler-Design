%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include "y.tab.h"
%}

letter [a-zA-Z]
digit [0-9]

%%

{letter}+ {return letters;}
{digit}+  {return digits;}
\n        {return 0;}
.         {return yytext[0];}

%%

int yywrap(){return 1;}