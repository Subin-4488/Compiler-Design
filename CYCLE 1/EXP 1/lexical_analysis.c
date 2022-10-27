#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

FILE *fin=NULL, *fout=NULL;
char line[1000];
char subs[1000];

int kws=27;
int ops=13;
int seps=7;
int lits=12;

char keywords[][20]={"void", "main", "include", "define", "printf", "scanf", "fgets", 
"for", "while", "int", "char", "strlen", "FILE", "fopen", "feof", "NULL",
"if", "return", "double", "continue", "break", "strcmp", "strcat", "fflush", "fscanf", "fprintf", "strcpy"};
char operators[][20]={"+", "-", "&", "%", "=", "!", "#", ">=", "<=", ">", "<", "[", "]"};
char seperators[][20]={"{", "}", "(", ")", ";", ",", "\n",};
char literals[][20]={"\"", "\'", "1","2","3","4","5","6","7","8","9","0"};

char ids[1000][1000]; int id=0;

void substring(char str[], int f, int l){
	int n=strlen(str);
	subs[0]='\0';
	int k=0;
	for (int i=f; i<l ;i++)
		subs[k++]=str[i];
	subs[k]='\0';
	return;
}

void writeToOutput(char res[], int flag){
	if (!flag)
	fprintf(fout, "\n%s", res);
	else{
		fprintf(fout,"\nError: ");
		fprintf(fout, "%s", res);
	}
	fflush(fout);
}

int isComment(int start, int end, int n){
	substring(line, start,2+start);  
	if (!strcmp(subs, "//"))   return 1;
	else if(!strcmp(subs, "/*"))  return 2;
	else if (line[start]=='/')	return -1;   //error token
	else return 0;
}

int isKeyword(int start, int end, int n){
	substring(line, start, end);
	for(int i=0; i<kws; i++){
		if (!strcmp(subs,keywords[i]))
			return 1;
	}
	return 0;
}

int isOperator(int start, int end, int n){
	substring(line, start, end);
	for (int i=0;i< ops; i++){
		if (!strcmp(subs,operators[i])){
			substring(line, start, end+1);
			for (int j=0;j< ops; j++){
				if (!strcmp(subs,operators[j]))
					return 1;
			}
			substring(line,start,end);
			return 1;
		}
	}
	return 0;
}

int isseperator(int start, int end, int n){
	substring(line, start, end);
	for (int i=0;i< seps; i++){
		if (!strcmp(subs,seperators[i]))
			return 1;
	}
	return 0;
}

int isLiteral(int start, int end, int n){
	substring(line, start,1+start);  
	for (int i=0;i<lits ;i++){
		if (!strcmp(subs,literals[i])){
			if (!strcmp(subs, "\""))
		 		return 1;
			else if(!strcmp(subs, "\'"))
				return 2;
			else 
				return 3;
		}
	}
	
	return 0;
}

void findTerminatingComment(int start){
	while (1){
		for (int i=start; i<strlen(line)-1; i++){
			if (line[i]=='*' && line[i+1]=='/'){
				line[0]='\0';
				return;
			}
		}
		fgets(line, 250, fin);
		start=0;
	}
}

void processLine(){
	int n=strlen(line);
	int invalid=0;
	for (int i=0;i<n-1;i++){
		invalid=0;
		if (line[i]==' ' || line[i]=='\t') continue;
		for (int j=i+1; j<n; j++){
			int ret=-2; 
			if ((ret=isComment(i ,j, n))>0){
				if (ret==1){ //single line comment
					return; 
				}
				else{ //multi line comment 
					findTerminatingComment(i);
					return;
				}
			}
			else if(ret==-1){
				//treat error token
				writeToOutput("/", 1);
			}
			else if ((ret=isOperator(i, j, n))>0){
				char buff[100]; buff[0]='\0';
				strcat(buff, "<< "); strcat(buff,subs); strcat(buff,", operator >>");
				writeToOutput(buff, 0);
				i=j-1;
				break;
			}
			else if((ret=isKeyword(i, j, n))>0){
				char buff[100]; buff[0]='\0';
				strcat(buff, "<< "); strcat(buff,subs); strcat(buff,",keyword >>");
				writeToOutput(buff, 0);
				i=j-1;
				break;
			}
			else if((ret=isseperator(i, j, n)>0)){
				char buff[100]; buff[0]='\0';
				strcat(buff, "<< "); strcat(buff,subs); strcat(buff,", seperator >>");
				writeToOutput(buff, 0);
				i=j-1;
				break;
			}
			else if((ret=isLiteral(i, j, n))>0){
				if (ret==1){
					while (j<strlen(line)){
						if (line[j]=='\"'){
							substring(line, i ,j+1);
							i=j;
							break;
						}
						j++;
					}
				}
				else if (ret==2){
					while (j<strlen(line)){
						if (line[j]=='\''){
							substring(line, i ,j+1);
							i=j;
							break;
						}
						j++;
					}
				}
				else if(ret==3){
					while (j<strlen(line) && !isOperator(j, j + 1, n) && !isseperator(j, j + 1, n) && line[j] != ' '){
						if (isLiteral(j,j+1,n)!=3)
							invalid=1;
						j++;
					}
					substring(line, i,j);
					i=j-1;
				}
				char buff[100]; buff[0]='\0';
				if (!invalid){
					strcat(buff, "<< "); strcat(buff,subs); strcat(buff,", literal >>");
				}
				else{
					strcat(buff, "<< "); strcat(buff,subs); strcat(buff,", Invalid Identifier >>");
				}
				writeToOutput(buff, 0);
				break;
			}
			else{
				if (isOperator(j, j + 1, n) || isseperator(j, j + 1, n) || line[j] == ' '){
					substring(line, i, j);
					char buff[100];
					buff[0] = '\0';
					strcat(buff, "<< ");
					strcat(buff, subs);
					strcat(buff, ", identifier >>");
					writeToOutput(buff, 0);
					i = j - 1;
					break;
				}
			}
		}
	}	
}

void main(){
	//printf("Enter the name of the input program file:\n");
    //scanf("%s",line);
	fin=fopen("input.txt", "r");
	fout=fopen("tokens.txt", "w");
	fprintf(fout, "< CHARACTER(S), TOKEN>\n");
	int k=1;
	while (!feof(fin)){
		fprintf(fout, "\n\nLINE NO: %d",k++);
		fgets(line, 250, fin);
		processLine(); 
		line[0]='\0';
		subs[0]='\0';
	}
}