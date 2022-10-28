#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct prod{
	char LHS;
	char RHS[25];
} *p;
int n=0;

struct first{
	char var;
	char values[25];
} f[20];
int fn=0;

struct queue{
	char que[50];
	int f,l;
}q;

char var[20];
int vn=0;

char ter[20];
int tn=0;

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

int isPresent(char ch){
	for (int i=q.f; i<q.l; i++){
		if (q.que[i]==ch)
			return 1;
		return 0;
	}
}

void collectGrammer(){

	printf("Enter the variables without space:\n");
	scanf("%s", var);
	vn=(int )strlen(var);
	
	printf("Enter the terminals without space:\n");
	scanf("%s",ter);
	tn=(int )strlen(ter);

	printf("Enter no of productions:\n");
	scanf("%d",&n);
	p=(struct prod*)malloc(sizeof(struct prod)*n);

	printf("Enter the Grammer Produtions:\n");
	for (int i=0; i<n; i++){
		printf("Enter LHS of prod %d: \n", i+1);
		scanf(" %c",&p[i].LHS);
		printf("Enter RHS of prod %d: \n", i+1);
		scanf(" %s",p[i].RHS);
	}
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

void addItemToFirst(char symbol, char value){
	for (int i=0; i<fn; i++){
		if (f[i].var == symbol){
            for (int j=0; j<strlen(f[i].values); j++){
                if (f[i].values[j]==value)
                    return;
            }
			f[i].values[strlen(f[i].values)]=value;
			return ;
		}
	}
	f[fn].var = symbol;
	f[fn].values[strlen(f[fn].values)]=value;
	fn++;
	
}

void display(char ch, int i){
        printf("%c %s\n", f[i].var, f[i].values);
}

char first(char main, char symbol){

	for (int i=0; i<n; i++){
		if (p[i].LHS == symbol){
			for (int j=0; j<strlen(p[i].RHS); j++){
                if (p[i].RHS[j]=='E')
                    return 'E';
				if (!isVariable(p[i].RHS[j])){
                    addItemToFirst(main, p[i].RHS[j]);
                    break;
				}
				else{
                    char c=first(main, p[i].RHS[j]);
					if (c=='E'){
                        if(j<strlen(p[i].RHS)-1)
                            continue;
                        else{
                            addItemToFirst(main, 'E');
                            break;
                        }
					}
                    return ' ';
				}
			}
		}
	}
}

void main(){
	q.f=q.l=0;
	collectGrammer();
    printf("\nFIRST: \n");
	for (int i=0; i<vn; i++){
		char c=first(var[i], var[i]);
        addItemToFirst(var[i], c);
        display(var[i], i);
        fflush(stdout);
	}

    printf("\nFOLLOW: \n");
	for (int i=0; i<vn; i++){
		
        display(var[i], i);
        fflush(stdout);
	}
}