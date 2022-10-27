#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

int gnfaIDX = 0;

struct e_closure
{
    char id;
    int childCount;
    char states[20];

} * closure;

int p = 0;
int s = 0;

char transitionSet[10];
int t = 0;

struct Queue
{
    char id;
} que[50];
int f = 0, r = 0;

void enqueue(char ch)
{
    que[r++].id = ch;
}

char dequeue()
{
    return que[f++].id;
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

int existInQueue(char ch)
{
    for (int i = f; i <= r; i++)
    {
        if (que[i].id == ch)
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
        printf("Enter name(id) of state %d: \n",i+1);
        scanf("%c", &g[i].id);  getchar();  
        printf("Press 1 if the state %c is final, otherwise 0:\n",g[i].id);
        scanf("%d",&g[i].finalStateFlag);  getchar();
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

void findClosure()
{
    closure = (struct e_closure *)malloc(sizeof(struct e_closure) * n);
    for (int i = 0; i < n; i++)
    {
        enqueue(g[i].id);
        closure[p].id = g[i].id;
        s = 0;
        while (!isEmpty())
        {
            char ch = dequeue();
            closure[p].states[s++] = ch;
            closure[p].childCount++;
            int flag = 0;
            for (int j = 0; j < n; j++)
            {
                if (g[j].id == ch)
                {
                    flag = 1;
                    for (int k = 0; k < g[j].links; k++)
                    {
                        if (g[j].childs[k].cost == 'E' && !existInQueue(g[j].childs[k].id))
                            enqueue(g[j].childs[k].id);
                    }
                }
                if (flag)
                    break;
            }
        }
        p++;
    }
}

int newState(char id[], char state, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (id[i] == state)
            return 0;
    }
    return 1;
}

char* getTransition(char state, char edge)
{
    char *arr=(char *)malloc(sizeof(char)*10); int tmp=0;
    for (int i = 0; i < n; i++)
    {
        if (g[i].id == state)
        {
            for (int j = 0; j < g[i].links; j++)
            {
                if (g[i].childs[j].cost == edge)
                    arr[tmp++]= g[i].childs[j].id;
            }
        }
    }
    if (tmp==0) arr[0]='E';

    return arr;
}

void convert()
{
    char id[20];
    int l = 0;
    char *ch;
    char stateSet[20];
    int ss = 0;
    printf("Resultant NFA: \n");

    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < t; k++)
        {
            l = 0;
            id[0] = '\0';
            ss = 0;
            stateSet[0] = '\0';
            for (int j = 0; j < closure[i].childCount; j++)
            {
                ch=getTransition(closure[i].states[j], transitionSet[k]);
                for (int tt=0; tt<10; tt++){
                    if (ch[tt]=='\0') break;
                    else id[l++]=ch[tt];
                }
            }
            
            for (int j = 0; j < l; j++)
            {
                for (int d = 0; d < n; d++)
                {
                    if (closure[d].id == id[j])
                    {
                        for (int m = 0; m < closure[d].childCount; m++)
                        {
                            if (newState(stateSet, closure[d].states[m], ss))
                            {
                                stateSet[ss++] = closure[d].states[m];
                            }
                        }
                        break;
                    }
                }
            }
            fflush(stdout);
            printf("&(%c,%c) = { ", closure[i].id, transitionSet[k]);
            for (int j = 0; j < ss; j++)
                printf("%c ", stateSet[j]);
            printf("}\n");
        }
    }
    printf("\nFinal states:\n");
    for (int i=0; i<n; i++){
    	int flag=0;
    	for (int j=0; j<closure[i].childCount; j++){
    		for (int k=0; k<n; k++){
    			if (closure[i].states[j] == g[k].id && g[k].finalStateFlag==1){
    				flag=1;
    				break;
    			}
    		}
        	if (flag){
	            	printf("%c ",g[i].id);
	            	break;
            	}
        }
    }

}

void main()
{
    collectNfa();
    findClosure();

    printf("EPSILLON CLOSURES OF STATES:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%c: ", closure[i].id);
        for (int j = 0; j < closure[i].childCount; j++)
        {
            printf("%c ", closure[i].states[j]);
        }
        printf("\n");
    }

    convert();
}