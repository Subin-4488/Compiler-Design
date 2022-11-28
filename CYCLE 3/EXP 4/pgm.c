#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct contants{
      char id[20];
      int val;
      int line;
} c[20]; int cn=0;

void identifyConstants(char *str, int line){
      char var[20]={'\0'};
      int nos=0;
      for (int i=0; i<strlen(str); i++){
            if (str[i] == ' ' || str[i] == '=' || str[i]=='\n') continue;

            if ((str[i]>='a' && str[i]<='z') || (str[i]>='A' && str[i]<='Z')){
                  strncat(var, &str[i], 1);
            }
            else if(str[i]=='+' || str[i]=='-' || str[i]=='*' || str[i]=='/' || str[i]=='('){
                  return;
            }
            else{
                  char *t=(char *)malloc(sizeof(char)*1);
                  t[0]=str[i];
                  nos=(nos*10)+atoi(t);
            }
      }
      strcpy(c[cn].id, var);
      c[cn].line=line;
      c[cn++].val=nos;
}

char *substr(int f, int l, char *str){
      char *ret=(char *)malloc(sizeof(char)*(l-f+1));
      memset(ret, '\0', l-f+1 * sizeof(char));
      
      int k=0;
      for (int i=f; i<l; i++)
            strncat(ret, &str[i], 1*sizeof(char));
      return ret;
}

int getMatch(char *substring){
      for (int i=0; i<cn; i++){
            if (!strcmp(substring, c[i].id))
                  return i;
      }
      return -1;
}

void processLine(char *str){
      int flag=0;
      for (int i=0; i<strlen(str)-1; i++){
            for (int j=i+1; j<=strlen(str); j++){
                  flag=0;
                  char *substring=substr(i, j, str);
                  int idx=-1;
                  if ((idx=getMatch(substring))!=-1){
                        flag=1;
                        printf("%d",c[idx].val);
                        i=j-1;
                        break;
                  }     
            }
            if (!flag)
            printf("%c", str[i]);
      }
}

int constantLine(int line){
      for (int i=0; i<cn; i++){
            if (c[i].line == line)
                  return 1;
      }
      return 0;
}

void main(){
      
      FILE *finput=fopen("input program.txt", "r");

      printf("\nInput:\n");
      while (!feof(finput)){
            char *str=(char *)malloc(sizeof(char)*250);
            fgets(str, 250, finput);
            printf("\t%s", str);
      }
      printf("\n\n");
      fseek(finput,0,0);
      
      int line=1;
      while (!feof(finput)){
            char *str=(char *)malloc(sizeof(char)*250);
            fgets(str, 250, finput);
            identifyConstants(str, line++);
      }

      fseek(finput, 0, 0);

      printf("Optimized:\n"); 
      line=1;
      while (!feof(finput)){
            char *str=(char *)malloc(sizeof(char)*250);
            fgets(str, 250, finput);
            if (!constantLine(line++)){
                  printf("\t");
                  processLine(str);
                  printf("\n");
            }
            else{
                  printf("\t");
                  printf("%s", str);
            }
      }
}