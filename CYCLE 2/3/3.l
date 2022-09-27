%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
%}

st [a-zA-Z]*

%%

{st} {
    for (int i=0; i<strlen(yytext); i++){
        if (yytext[i]=='a' && yytext[i+1]=='b' && yytext[i+2]=='c'){
            yytext[i]='A';
            yytext[i+1]='B';
            yytext[i+2]='C';
        }
    }
    printf("%s", yytext);
}

\n {
    printf("%s", yytext);
}


%%

void main(){
    printf("Enter input sentence:\n");
    yylex();
}