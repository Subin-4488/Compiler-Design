%{
    #include <stdio.h>
    int flag=1;
%}

%token num op id

%%

S: id '=' E ;
E : E op T | T;
T : '(' E ')' | id | num;


%%

void yyerror(char *s){
    printf("Invalid expression %s\n",s);
    flag=0;
}

void main(){
    printf("Enter expression:\n");
    yyparse();
    if (flag) printf("Valid expression\n");
}