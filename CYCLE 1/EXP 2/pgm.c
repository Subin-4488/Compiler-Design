#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int n;

struct child{
      char id;
      char cost;
};

struct node{
      char id;
      int links;
      struct child *childs;
}*g;

struct e_closure{
      char id;
      int childCount;
      char states[20]; 
}*closure;  int p=0; int s=0;

struct Queue{
   char id;   
} que[50]; int f=0, r=0;

void enqueue(char ch){
      que[r++].id=ch;
}

char dequeue(){
      return que[f++].id;
}

int isEmpty(){
      if (f==r){
            f=r=0;
            return 1;
      }
      return 0;
}

int existInQueue(char ch){
    for (int i=f;i<=r; i++){
        if (que[i].id == ch)  
            return 1;
    }
    return 0;
}

void main(){
      printf("Enter the no of states in the NFA:\n");
      scanf("%d",&n);

      g=(struct node*)malloc(sizeof(struct node)*n);

      printf("Enter name(id) of each state starting from the start-state: \n");
      for (int i=0;i<n;i++){
            scanf(" %c",&g[i].id);
      }

      for (int i=0;i<n;i++){
            printf("Enter the no of of transitions from %c:\n", g[i].id);
            scanf("%d",&g[i].links);
            printf("Enter the id of states reachable from %c and the corresponding cost of transition:\n", g[i].id);
            g[i].childs=(struct child *)malloc(sizeof(struct child) * g[i].links);
            for (int j=0;j<g[i].links; j++){
                  scanf(" %c %c",&g[i].childs[j].id, &g[i].childs[j].cost);
            }
      }

      closure=(struct e_closure*) malloc(sizeof(struct e_closure)*n);
      for (int i=0;i<n;i++){
            enqueue(g[i].id);
            closure[p].id = g[i].id;
            s=0;
            while (!isEmpty()){
                  char ch=dequeue();
                  closure[p].states[s++]=ch;
                  closure[p].childCount++;
                  int flag=0;
                  for (int j=0;j<n; j++){
                        if (g[j].id==ch){
                              flag=1;
                              for (int k=0;k<g[j].links; k++){
                                    if (g[j].childs[k].cost=='E' && !existInQueue(g[j].childs[k].id)) 
                                        enqueue(g[j].childs[k].id);
                              }
                        }
                        if(flag) break;
                  }
            }
            p++;
      }

      printf("EPSILLON CLOSURES OF STATES:\n");
      for (int i=0;i<n;i++){
            printf("%c: ", closure[i].id);
            for (int j=0;j<closure[i].childCount; j++){
                  printf("%c ",closure[i].states[j]);
            }
            printf("\n");
      }
      
}