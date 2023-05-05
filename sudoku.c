#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
    size_t i,j;
    for (i=0;i<9;i++)
    {
        int filas[10]={0};
        int columnas[10]={0};
        for (j=0;j<9;j++)
        {
            if (n->sudo[i][j]!=0 && filas[n->sudo[i][j]]==1) return 0;
            else filas[n->sudo[i][j]]=1;
            
            if(n->sudo[j][i]!=0 && columnas[n->sudo[j][i]]==1)return 0;
            else columnas[n->sudo[j][i]]=1;
        }
    }
    
    for (int k=0;k<9;k++)
    {
        int subMatriz[10]={0};
        for(int p=0;p<9;p++)
        {
            int i=3*(k/3) + (p/3) ;
            int j=3*(k%3) + (p%3) ;
            if(n->sudo[i][j]!=0 && subMatriz[n->sudo[i][j]]==1)return 0;
            else subMatriz[n->sudo[i][j]]=1;
        }
    }
    return 1;
}

List* get_adj_nodes(Node* n){
    List* list=createList();
    size_t i,j;

    for (i=0;i < 9;i++)
    {
        for(j=0;j<9;j++)
        {
            if (n->sudo[i][j]==0)
            {
                for (size_t k=1;k<=9;k++)
                {
                    Node* nodo=copy(n);
                    nodo->sudo[i][j]=k;
                    if(is_valid(nodo))pushBack(list,nodo);
                    else free(nodo);  
                }
                return list;
            }
        }
    }
    return list;
    
}

int is_final(Node* n){
    for (size_t i=0;i<9;i++)
    {
        for (size_t j=0;j<9;j++)
        {
            if (n->sudo[i][j]==0)return 0;
        }
    }
    return 1;
}

Node* DFS(Node* initial, int* cont){
    Stack* pila=createStack();
    push(pila,initial);
    while(top(pila)!=NULL)
    {
        Node* current=top(pila);
        pop(pila);
        if(is_final(current)==1)return current;
        List* lista=get_adj_nodes(current);
        for(Node*  primero=first(lista);primero!=NULL;primero=next(lista))
            push(pila,primero);
        free(current);
        (*cont)++;
    }
    return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/