#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct prod{
      char LHS;
      char RHS[10];
} *prod;
int n=0;

int vn=0;
int tn=0; 
char var[20], ter[20];

char str[25]={'\0'};  int idx=0; 
      
char stack[25]; int top=0;

void shift(){
      stack[++top]=str[idx++];
}

int* isReducable(){
      int *arr=(int *)malloc(sizeof(int)*2);
      for (int i=top; i>0; i--){
            for (int j=0; j<n; j++){
                  if (!strcmp(&stack[i],prod[j].RHS)){
                        arr[0]=i; arr[1]=j;
                        return arr;
                  }
            }
      }
      return NULL;
}

void reduce(int stackIDX, int prodIDX){
      stack[stackIDX]=prod[prodIDX].LHS;
      for (int i=stackIDX+1; i<25; i++)
            stack[i]='\0';
      top=stackIDX;
}

char * getInput(){
      
      char *temp=&str[idx];
      return temp;
}

int parse(){
      int flag=0;
      printf("STACK\t\tINPUT\t\tACTION\n");
      while (idx <= strlen(str)){
            if (stack[top] == '$'){
                  shift();
                  printf("%s\t\t%s\t\tSHIFT %c\n", stack, getInput(), str[idx-1]);
            }
            else{
                  int *arr=NULL;
                  if ((arr=isReducable())!=NULL){
                        reduce(arr[0], arr[1]);
                        printf("%s\t\t%s\t\tREDUCE %c->%s\n", stack, getInput(), prod[arr[1]].LHS, prod[arr[1]].RHS);
                  }
                  else{
                        if (top == 1 && stack[top]==prod[0].LHS){
                              printf("%s\t\t%s\t\tSHIFT %c\n", stack, getInput(), str[idx]);
                              flag=1;
                              printf("String parsed successfully\n");
                              idx++;
                        }
                        else{
                              shift();
                              printf("%s\t\t%s\t\tSHIFT %c\n", stack, getInput(), str[idx-1]);
                        }
                  }
            }
      }
      if (!flag)
            printf("String parse failed\n");
}

void loadGrammer(){
      strcpy(var, "E");
      vn=strlen(var);

      strcpy(ter,"234");
      tn=strlen(ter);

      n=3;
      prod=(struct prod*)malloc(sizeof(struct prod)*n);

      prod[0].LHS='E';
      strcpy(prod[0].RHS,"2E2");
      prod[1].LHS='E';
      strcpy(prod[1].RHS,"3E3");
      prod[2].LHS='E';
      strcpy(prod[2].RHS,"4");
     
      for (int i=0; i<n; i++){
            printf("%c -> %s\n", prod[i].LHS, prod[i].RHS);
      }
}

void main(){
      loadGrammer();
      printf("Enter the string to be parsed: \n");
      scanf("%s", str);
      
      strcat(stack, "$");
      parse(); 
}