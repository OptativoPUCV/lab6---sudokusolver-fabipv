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
  int i;
  int j;
  int k;

  int arraysNum[10] = {0,0,0,0,0,0,0,0,0,0};
  
  //No se repitan numeros en las filas
  for(i = 0; i < 9; i++)
  {
    for(j = 0; j < 9; j++)
    {
      if(n->sudo[i][j] != 0)
      {
        if(arraysNum[n->sudo[i][j]] == 1)
        {
          return 0;
        }
        else
        {
          arraysNum[n->sudo[i][j]] = 1;
        }
        
      }
    }
    
    for(k = 1; k <= 9; k++)
    {
      arraysNum[k] = 0;
    }
  }
  
  //No se repitan numeros en las columnas
  for(j = 0; j < 9; j++)
  {
    for(i = 0; i < 9; i++)
    {
      if(n->sudo[i][j] != 0)
      {
        if(arraysNum[n->sudo[i][j]] == 1)
        {
          return 0;
        }
        else
        {
          arraysNum[n->sudo[i][j]] = 1;
        }
      }
    }

    for(k = 1 ; k <= 9 ; k++)
    {
      arraysNum[k] = 0;
    }
  }
  
  //No se repitan en las submatrices de 3x3

  for(i = 1 ; i < 9 ; i+= 3)
  {
    for(j = 1 ; j < 9 ; j+= 3)
    {
      int  k = 3 * (i/3) + (j/3);
      int s;

      int x = (k/3) * 3 + (s/3);
      int y = (k%3) * 3 + (s%3);

      //int numActual = n->sudo[x][y];
      
    }
  }

    return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();
    int i;
    int j;
    int k;

    for(i = 0 ; i < 9 ; i++)
    {
      for(j = 0 ; j < 9 ; j++)
      {
        if(n->sudo[i][j] == 0)
        {
          for(k = 1 ; k <= 9 ; k++)
          {
            Node *nuevoNodo = createNode();
            nuevoNodo = copy(n);
            nuevoNodo->sudo[i][j] = k;
            pushBack(list, nuevoNodo);
          }
        }
      }
    }
    return list;
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
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