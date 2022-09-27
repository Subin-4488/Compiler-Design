%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>

    int l=0;
    int w=0;
    int c=0;
%}

line [\n]
words [a-zA-Z0-9!@#$%^&*<>/?.()]+

%%
{line} {l++;}
{words} {w++; c+=strlen(yytext);}
%%

int yywrap(void){}

void main(){
    yyin=fopen("input.txt", "r");
    yylex();

    printf("LINES: %d\n", l+1);
    printf("CHARACTERS: %d\n",c);
    printf("WORDS: %d\n", w);
}