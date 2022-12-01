#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char str[50];
char stack[50]={'\0'}; int top=-1;
char pos[50]={'\0'};

int isEmpty(){
      if (top==-1) 
            return 1;
      return 0;
}

struct T_3AC{
      char LHS;
      char arg1;
      char arg2;
      char op;

} arr[50]; int k=0;

void push(char ch){
      stack[++top]=ch;
}

char pop(){
      char ch=stack[top];
      stack[top]='\0';
      top-=1;
      return ch;
}

int getPrecidence(char ch){
      switch (ch){
            case '*':{
                  return 2;
                  break;
            }     
            case '/':{
                  return 2;
                  break;
            }
            case '+':{
                  return 1;
                  break;
            }
            case '-':{
                  return 1;
                  break;
            }
      }
}

int isOperator(char ch){
      if (ch=='*' || ch=='/' || ch=='+' || ch=='-')
            return 1;
      return 0;
}

int alreadyExist(char a1, char op, char a2){
      for (int i=0; i<k; i++){
            if (arr[i].arg1==a1 && arr[i].op==op && arr[i].arg2==a2)
                  return i;
      }
      return -1;
}

void inf2pos(){
      for (int i=0; i<strlen(str); i++){
            if (str[i]==' ') continue;
            if (!isOperator(str[i]))
                  strncat(pos, &str[i], sizeof(char)*1);
            else{
                  while (getPrecidence(str[i])<=getPrecidence(stack[top]) && !isEmpty()){
                        char ch=pop();
                        strncat(pos, &ch, 1*sizeof(char));
                  }
                  push(str[i]);
            }
      }
      while (!isEmpty()){
            char ch=pop();
            strncat(pos, &ch, 1*sizeof(char));
      }
}

void _3AC(){
      char sym='P';
      memset(stack, '\0', 50*sizeof(char));
      top=-1;

      for (int i=0; i<strlen(pos); i++){
            if (!isOperator(pos[i]))
                  push(pos[i]);
            else{
                  char a2=pop();
                  char a1=pop();
                  int temp;
                  if ((temp=alreadyExist(a1, pos[i], a2))==-1){
                        arr[k].LHS=sym;
                        arr[k].op=pos[i];
                        arr[k].arg2=a2;
                        arr[k].arg1=a1;
                        push(arr[k++].LHS);
                        sym++;
                  }
                  else{
                        push(arr[temp].LHS);
                  }
            }
      }
}

void main(){
      printf("Enter any simple expression: \n"); //without (, -(unary) 
      gets(str);

      char LHS=str[0];
      inf2pos();
      _3AC();

      printf("\n\n3 ADDRESS CODE: \n");
      for (int i=0; i<k; i++)
            printf("%c := %c %c %c\n", arr[i].LHS, arr[i].arg1, arr[i].op, arr[i].arg2);
      printf("%c := %c\n", LHS, arr[k-1].LHS);
}