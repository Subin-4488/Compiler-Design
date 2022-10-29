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

struct follow{
    char var;
    char values[25];
} fl[20];
int fln=0;

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

void collectGrammer(){

	printf("Enter the variables starting from START_SYMBOL without space:\n");
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

void addItemToFollow(char symbol, char value){
	for (int i=0; i<fln; i++){
		if (fl[i].var == symbol){
            for (int j=0; j<strlen(fl[i].values); j++){
                if (fl[i].values[j]==value)
                    return;
            }
			fl[i].values[strlen(fl[i].values)]=value;
			return ;
		}
	}
	fl[fln].var = symbol;
	fl[fln].values[strlen(fl[fln].values)]=value;
	fln++;
	
}

void displayFirst(){
	for (int i=0; i<fn; i++)
        printf("%c: %s\n", f[i].var, f[i].values);
}

void displayFollow(){
	for (int i=0; i<fln; i++)
        printf("%c: %s\n", fl[i].var, fl[i].values);
}

char first(char main, char symbol){

	for (int i=0; i<n; i++){
		if (p[i].LHS == symbol){
			for (int j=0; j<strlen(p[i].RHS); j++){
                if (p[i].RHS[j]=='E')
                    return 'E';
				else if (isTerminal(p[i].RHS[j])){
                    addItemToFirst(main, p[i].RHS[j]);
                    break;
				}
				else{
                    char c=first(main, p[i].RHS[j]);
					if (c=='E'){
                        if(j<strlen(p[i].RHS)-1)
                            continue;
                        else{
                            if (main==symbol)
                                addItemToFirst(main, 'E');
                            else
                                return 'E';
                        }
					}
					else
						break;
				}
			}
		}
	}
}

char *getFirst(char symbol){

    for (int i=0; i<fn; i++){
        if (f[i].var == symbol){
            return f[i].values;
        }
    }
    return NULL;
}

char *getFollow(char symbol){
    for (int i=0; i<fln; i++){
        if (fl[i].var == symbol){
            return fl[i].values;
        }
    }
    return NULL;
}

char follow(char symbol){
    for (int i=0; i<n; i++){
        for (int j=0; j<strlen(p[i].RHS); j++){
            if (p[i].RHS[j] == symbol){
                char *arr=getFollow(p[i].LHS);
                if (j==strlen(p[i].RHS)-1){
                    for (int k=0; k<strlen(arr); k++)   
						addItemToFollow(symbol, arr[k]);
                }
				else{
					for (int k=j+1; k<strlen(p[i].RHS); k++){
						if (isTerminal(p[i].RHS[k])){
							addItemToFollow(symbol, p[i].RHS[k]);
							break;
						}
						else{
							char *a = getFirst(p[i].RHS[k]);
							for (int ii = 0; ii < strlen(a); ii++){
								if (a[ii] == 'E'){
									if (k == strlen(p[i].RHS) - 1){
										if (arr!=NULL){
											for (int kk = 0; kk < strlen(arr); kk++)
												addItemToFollow(symbol, arr[kk]);
										}
									}
									else
										break;
								}
								else if (isTerminal(a[ii])){
									addItemToFollow(symbol, a[ii]);
								}
							}
						}
					}
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
        fflush(stdout);
	}
	displayFirst();

    printf("\nFOLLOW: \n");
	int c=0;
	for (int i=0; i<3*vn; i++){
		follow(var[i%vn]);
        if (i==0){
            addItemToFollow(var[i%vn], '$');
        }
        fflush(stdout);
	}
	displayFollow();
}