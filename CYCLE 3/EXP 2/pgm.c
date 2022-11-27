#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

# define epsillon "&"
struct prod{
	char LHS;
	char RHS[25];
} *p;
int n=0;

struct newProd{
	char LHS;
	char RHS[25];
} np[25];
int nn=0;

struct queue{
	char que[50];
	int f,l;
}q;

char var[20];
int vn=0;

char ter[20];
int tn=0;

char symbolTemp[1];

char str[25]; int idx=0; static int errorFlag=0;

void displayGrammer(void *ptr, int flag){
    struct newProd *newProd=NULL;
    struct prod *prod=NULL;
    if (flag){
        newProd=(struct newProd*)ptr;
        for (int i=0; i<nn; i++){
            printf("%c -> %s\n",newProd[i].LHS, newProd[i].RHS);
        }
    }
    else{
        prod=(struct prod*)ptr;
        for (int i=0; i<n; i++){
            printf("%c -> %s\n",prod[i].LHS, prod[i].RHS);
        }
    }
}

void enqueue(char ch){
	q.que[q.l++]=ch;
}

char dequeue(){
	char ch;
	ch=q.que[q.f];
	if (q.f==q.l)
		q.f = q.l = 0;
	else
		q.f ++;
	return ch;
}

int isEmpty(){
	if (q.f==0 && q.l==0)
		return 1;
	return 0;
}

void collectGrammer(){

    strcpy(var,"ETF");
	vn=(int )strlen(var);
	
    strcpy(ter,"+*()a");
	tn=(int )strlen(ter);

    n=6;
	p=(struct prod*)malloc(sizeof(struct prod)*n);
    p[0].LHS='E';
    strcpy(p[0].RHS,"E+T");
    p[1].LHS='E';
    strcpy(p[1].RHS,"T");
    p[2].LHS='T';
    strcpy(p[2].RHS,"T*F");
    p[3].LHS='T';
    strcpy(p[3].RHS,"F");
    p[4].LHS='F';
    strcpy(p[4].RHS,"(E)");
    p[5].LHS='F';
    strcpy(p[5].RHS,"a");
	
	return;
}

int isVariable(char ch){
	for (int i=0; i<vn; i++){
		if (var[i]==ch) return 1;
	}
	return 0;
}

int isTerminal(char ch){
	for (int i=0; i<tn; i++){
		if (ter[i]==ch) return 1;
	}
	return 0;
}

char *substring(char arr[], int init, int final){
    char *temp; int k=0; 
    temp=(char *)malloc(sizeof(char)*strlen(arr));
    for (int i=init; i<final; i++){
        temp[k++]=arr[i];
    }
    return temp;
}

int alreadyPresent(char LHS, char RHS[]){
    for (int i=0; i<nn; i++){
        if (np[i].LHS == LHS && !strcmp(np[i].RHS,RHS))
            return 1;
    }
    return 0;
}

void leftRecursion(char ch, char sym){
    int flag=0;
    int entered=0;

    for (int i=0; i<n; i++){
        if (p[i].LHS == ch && p[i].RHS[0]==ch){
            entered=1;
            for (int j=0; j<n; j++){
                if (p[j].LHS==ch && p[j].RHS[0]!=ch){
                    symbolTemp[0]=sym;
                    char *temp; 
                    temp=(char *)malloc(sizeof(char)*10);
                    temp[0]='\0';
                    strcpy(temp,p[j].RHS);
                    strcat(temp, symbolTemp);

                    np[nn].LHS=ch;
                    strcpy(np[nn++].RHS, temp);
                    
                    temp[0]='\0';
                    temp=substring(p[i].RHS, 1, strlen(p[i].RHS));

                    np[nn].LHS=symbolTemp[0];
                    strcpy(np[nn].RHS, temp);
                    strcat(np[nn++].RHS, symbolTemp);

                    if (!alreadyPresent(symbolTemp[0], epsillon)){
                        np[nn].LHS=symbolTemp[0];
                        strcpy(np[nn++].RHS, epsillon);
                    }
                }
            }
        }
    }
    if (!entered){
        for (int i=0; i<n; i++){
            if (p[i].LHS == ch){
                np[nn].LHS=ch;
                strcpy(np[nn++].RHS, p[i].RHS);
            }
        }
    }
}

void E();
void P();
void T();
void Q();
void F();

void main(){
	q.f=q.l=0;
	collectGrammer();
    printf("\nGiven Grammer:\n");
    displayGrammer(p, 0);

    printf("\nEliminating immediate left recursion...\n");
    char sym='P';
    for (int i=0; i<vn; i++)
        leftRecursion(var[i], sym++);
    
    printf("\nNon Left Recusrive Grammer:\n");
    displayGrammer(np, 1);

    printf("Enter the string to be parsed:\n");
    scanf("%s", str);
    
    E();
    if (idx!=strlen(str))
        errorFlag=1;
    if (!errorFlag){
        printf("String successfully parsed\n");
        exit(EXIT_SUCCESS);
    }
    else{
        printf("Error encountered\n");
        exit(EXIT_SUCCESS);
    }
}

void E(){
    T();
    P();
}

void P(){
    if (str[idx] == '+'){
        idx++;
        T();
        P();
    }
}

void T(){
    F();
    Q();
}

void Q(){
    if (str[idx] == '*'){
        idx++;
        F();
        Q();
    }
    return ;
}

void F(){
    if (str[idx] == '('){
        idx++;
        E();
        if (str[idx] == ')'){
            idx++;
        }
        else{
            printf("Error encountered\n");
            errorFlag=1;
            return;
        }
    }
    else if (str[idx] == 'a'){
        idx++;
    }
    else{
        printf("Error encountered\n");
        errorFlag=1;
        return;
    }
}