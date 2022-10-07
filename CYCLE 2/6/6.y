%{
    #include <stdio.h>
    #include <stdlib.h>
    int flag=1;
%}

%token letters digits

%%
    s: letters T;
    T: letters | digits | epsillon ;
    epsillon: ;
%%

void yyerror(char *msg){
    printf("ERROR: %s\n", msg);
    flag=0;
}

void main(){
    printf("Enter ID: \n"); flag=1;
    yyparse();
    if (flag) printf("Valid ID\n");
}