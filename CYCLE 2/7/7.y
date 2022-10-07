%{
    #include <stdio.h>
    #include <stdlib.h>
%}

%token num
%left   '+' '-'
%left   '*' '/'
%left   '(' ')'

%%

S: E {  printf("Result: %d\n", $$); };

E:  E '+' E { $$=$1+$3; }  |
    E '-' E { $$=$1-$3; }  |
    E '*' E { $$=$1*$3; }  |
    E '/' E { $$=$1/$3; }  |
    '(' E ')' { $$=$2; }   |
    num     { $$=$1;}
    ;

%%

void yyerror(char *msg){
    printf("Error: %s\n", msg);
}

void main(){
    printf("Enter any arithmetic expression to be evaluated:\n");
    yyparse();
}