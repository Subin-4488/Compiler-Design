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

struct Queue
{
    char arr[10];
    int size;

} que[10];
int f = 0, r = 0;

char transitionSet[10];
int t = 0;

struct result
{
    char ress[20];
    int size;
} res[30];
int rs = 0;

void enqueue(char ch[], int size)
{
    que[r].size = size;
    for (int i = 0; i < size; i++)
        que[r].arr[i] = ch[i];
    r++;
}

char *dequeue()
{
    return que[f++].arr;
}

int isEmpty()
{
    if (f == r)
    {
        f = r = 0;
        return 1;
    }
    return 0;
}

int newTransition(int transition)
{
    for (int i = 0; i < t; i++)
    {
        if (transitionSet[i] == transition)
            return 0;
    }
    return 1;
}

void collectNfa()
{
    printf("Enter the no of states in the NFA:\n");
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
            if (g[i].childs[j].cost != 'E' && newTransition(g[i].childs[j].cost))
            {
                transitionSet[t++] = g[i].childs[j].cost;
            }
        }
    }
}

int alreadyPresent(char arr[], int n, char id){
    for (int i=0; i<n; i++){
        if (arr[i]==id) return 1;
    }
    return 0;
}

int tmp = 0;
char *getTransition(char state[], int size, char edge)
{
    tmp = 0;
    char *arr = (char *)malloc(sizeof(char) * 20);

    for (int k = 0; k < size; k++)
    {
        for (int i = 0; i < n; i++)
        {
            if (g[i].id == state[k])
            {
                for (int j = 0; j < g[i].links; j++)
                {
                    if (g[i].childs[j].cost == edge && !alreadyPresent(arr, tmp, g[i].childs[j].id))
                        arr[tmp++] = g[i].childs[j].id;
                }
            }
        }
    }

    return arr;
}

void showOutput(char ptr[], int ssize, char edge, char q[], int size)
{
    for (int i = 0; i < ssize; i++)
    {
        printf("%c ", ptr[i]);
    }
    printf(" -> %c : ", edge);
    for (int i = 0; i < size; i++)
    {
        printf("%c ", q[i]);
    }

    printf("\n");
}

int visited(char arr[], int n)
{
    int c=0;
    for (int i = 0; i < rs; i++)
    {
        if (res[i].size == n)
        {
            c=0;
            for (int j=0; j<n ;j++){
                for (int k=0; k<n; k++){
                    if (arr[j]==res[i].ress[k]){
                        c+=1;
                        break;
                    }
                }
            }
            if (c==n) return 1;
        }
    }
    return 0;
}

void visit(char arr[], int n)
{
    res[rs].size = n;
    strcpy(res[rs].ress, arr);

    rs++;
}

void convert()
{
    char temp[20];
    temp[0] = g[0].id;  temp[1]='\0';
    visit(temp, 1);
    enqueue(temp, 1);

    char *ptr, *q;
    while (!isEmpty())
    {
        int ssize = que[f].size;
        ptr = dequeue();
        for (int i = 0; i < t; i++)
        {
            q = getTransition(ptr, ssize, transitionSet[i]);
            if (!visited(q, tmp))
            {
                visit(q, tmp);
                enqueue(q, tmp);
            }
            showOutput(ptr, ssize, transitionSet[i], q, tmp);
        }
    }
}

int isFinal(char ch){
    for (int i=0; i<n; i++){
        if (g[i].id==ch){
            if (g[i].finalStateFlag)
                return 1;
            else
                return 0;
        }
    }
}

void main()
{
    printf("***Program to convert NFA(non epsillon) to DFA***\n\n");

    collectNfa();

    printf("Resultant DFA:\n");
    convert();

    printf("\n Final states:\n");
    for (int i=0; i<rs; i++){
        for (int j=0; j<res[i].size; j++){
            if (isFinal(res[i].ress[j])){
                printf("%s\n", res[i].ress);
                break;
            }
        }
    }

    printf("\nNon Final states:\n");

    int flag=1;
    for (int i=0; i<rs; i++){
        flag=1;
        for (int j=0; j<res[i].size; j++){
            if (isFinal(res[i].ress[j])){
                flag=0;
                break;
            }
        }
        if (flag)
            printf("%s\n",res[i].ress);
    }
}