%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int v=0, c=0;
%}

vows [aeiouAEIOU]
consonants [a-zA-Z]

%%
{vows} {v++;}
{consonants} {c++;}
\n {
    printf("Total vowels: %d\n", v);
    printf("Total consonants: %d\n", c);
}
%%

void main(){
    yylex();
}