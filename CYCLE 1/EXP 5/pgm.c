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

char transitionSet[10];
int t = 0;

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
            if (g[i].childs[j].cost != 'E' && newTransition(g[i].childs[j].cost))
            {
                transitionSet[t++] = g[i].childs[j].cost;
            }
        }
    }
}

void main(){
    printf("***Program to minimize a given DFA***\n\n");

    collectDFA();
}