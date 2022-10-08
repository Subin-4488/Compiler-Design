#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n;

struct child
{
    char id;
    char cost;
};

struct node
{
    int finalStateFlag;
    char id;
    int links;
    struct child *childs;

} * g;

struct table{
    char state;
    char arr[20][2];
    int len;

}tab[20]; int size=0;

char transitionSet[10];
int t = 0;

int newTransition(int transition)
{
    for (int i = 0; i < t; i++)
    {
        if (transitionSet[i] == transition)
            return 0;
    }
    return 1;
}

void collectDFA()
{
    printf("Enter the no of states in the DFA:\n");
    scanf("%d", &n);
    getchar();

    g = (struct node *)malloc(sizeof(struct node) * n);

    for (int i = 0; i < n; i++)
    {
        printf("Enter name(id) of state %d: \n", i + 1);
        scanf("%c", &g[i].id);
        getchar();
        printf("Press 1 if the state %c is final, otherwise 0:\n", g[i].id);
        scanf("%d", &g[i].finalStateFlag);
        getchar();
    }

    for (int i = 0; i < n; i++)
    {
        printf("Enter the no of of transitions from %c:\n", g[i].id);
        scanf("%d", &g[i].links);
        printf("Enter the id of states reachable from %c and the corresponding cost of transition:\n", g[i].id);
        g[i].childs = (struct child *)malloc(sizeof(struct child) * g[i].links);
        for (int j = 0; j < g[i].links; j++)
        {
            scanf(" %c %c", &g[i].childs[j].id, &g[i].childs[j].cost);
            if (newTransition(g[i].childs[j].cost))
            {
                transitionSet[t++] = g[i].childs[j].cost;
            }
        }
    }
}

void prepareTable(){
    for (int i=0; i<n-1; i++){
        tab[size].state=g[i].id;
        tab[size].len=0;
        for (int j=i+1; j<n; j++){
            if (g[i].finalStateFlag ^ g[j].finalStateFlag){
                tab[size].arr[tab[size].len][0]=g[j].id;
                tab[size].arr[tab[size].len][1]='Y';
            }
            else{
                tab[size].arr[tab[size].len][0]=g[j].id;
                tab[size].arr[tab[size].len][1]='N';
            }
            tab[size].len++;
        }
        size++;
    }
}

char getTransition(char state, char edge)
{
    char arr;

        for (int i = 0; i < n; i++)
        {
            if (g[i].id == state)
            {
                for (int j = 0; j < g[i].links; j++)
                {
                    if (g[i].childs[j].cost == edge){
                        arr=g[i].childs[j].id;
                        return arr;
                    }
                }
            }
        }

    return arr;
}

int alreadyMarked(char c1, char c2){

    for (int i=0; i<size; i++){
        if (tab[i].state==c1){
            for (int j=0; j<tab[i].len; j++){
                if (tab[i].arr[j][0]==c2){
                    if (tab[i].arr[j][1]=='Y')
                        return 1;
                    else
                        break;
                }
            }
        }
        if (tab[i].state==c2){
            for (int j=0; j<tab[i].len; j++){
                if (tab[i].arr[j][0]==c1){
                    if (tab[i].arr[j][1]=='Y')
                        return 1;
                    else
                        break;
                }
            }
        }
    }
    
    return 0;
}

void debugPrintTable(){
    for (int i=0; i<size; i++){
        printf("%c: \n",tab[i].state);
        for (int j=0; j<tab[i].len; j++){
            printf("%c %c\n",tab[i].arr[j][0], tab[i].arr[j][1]);
        }
    }
}

void myhillNerode(){
    prepareTable();

    int c=0;
    while (c++ < 20)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < tab[i].len; j++)
            {
                if (tab[i].arr[j][1] == 'N')
                { // unmarked pair
                    for (int k = 0; k < t; k++)
                    {
                        char c1 = getTransition(tab[i].state, transitionSet[k]);
                        char c2 = getTransition(tab[i].arr[j][0], transitionSet[k]);
                        if (alreadyMarked(c1, c2))
                        {
                            tab[i].arr[j][1] = 'Y';
                        }
                    }
                }
            }
        }
    }

    printf("According to MYHILL_NERODE THEORM, the given DFA can be minimized by combining the following states:\n");
    for (int i=0; i<size; i++){
        for (int j=0; j<tab[i].len; j++){
            if (tab[i].arr[j][1]=='N'){
                printf("{%c and %c}\n", tab[i].state, tab[i].arr[j][0]);
            }
        }
    }
}

void main(){
    printf("***Program to minimize a given DFA***\n\n");

    collectDFA();
    myhillNerode();
}