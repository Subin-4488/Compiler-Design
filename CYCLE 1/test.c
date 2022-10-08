#include <stdio.h>
#include <string.h>

void main(){

    char arr[10][2];
    strcpy(arr[0], "BN");
    strcpy(arr[1], "CN");

    printf("%s", arr[0]);
}