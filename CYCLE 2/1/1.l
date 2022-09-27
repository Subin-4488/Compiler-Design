%{
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
%}

operator [+*\-&/%=!#\[\]]|(<=)|(>=)|[<>]
letter [a-zA-Z]
digit [0-9]
literal (["]({letter}|{operator}|{digit}|[\\n]|[\\t]|[ ])*["])|{digit}+
identifier ({letter}|_)({letter}|_|{digit})*

%%

"void"|"main"|"include"|"define"|"printf"|"scanf"|"fgets"|"for"|"while"|"int"|"char"|"strlen"|"FILE"|"fopen"|"feof"|"NULL","if"|"return"|"double"|"continue"|"break"|"strcmp"|"strcat"|"fflush"|"fscanf"|"fprintf"|"strcpy"|"return" {printf("%s, keyword\n", yytext);}

{operator} {printf("%s, operator\n", yytext);}

"{"|"}"|"("|")"|";"|"," {printf("%s, seperator\n",yytext);}

"1","2","3","4","5","6","7","8","9","0" {printf("%s, literal\n",yytext);}

{literal} {printf("%s, literal\n", yytext);}

{identifier} {printf("%s, identifier\n", yytext);}

%%

void main(){
    yyin=fopen("input.txt", "r");
    yylex();
}