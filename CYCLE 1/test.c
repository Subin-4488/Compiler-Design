#include <stdio.h>
#include <stdlib.h>

char * fun(){
    char *arr=(char *)malloc(sizeof(char)*5);
    arr[0]='A'; arr[1]='B'; arr[2]='C'; arr[3]='D'; arr[4]='E'; 
    return arr;
}

void main(){
    char *arr=fun();
    int c=0;
    for (int i=0; i<50; i++){
        //printf("%c ",arr[i]);
        printf("%d",c++);
        if (arr[i]=='\0') break;
    }
}