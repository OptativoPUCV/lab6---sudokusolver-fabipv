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

      for(s = 0 ; s < 9 ; s++)
      {
        int x = (k/3) * 3 + (s/3);
        int y = (k%3) * 3 + (s%3);

        int numActual = n->sudo[x][y];

        if(numActual != 0)
        {
          if(arraysNum[numActual] == 0)
          {
            arraysNum[numActual] = 1;
          }
          else
          {
            return 0;
          }
        }
  
      }

      for(k = 0 ; k < 10 ; k++)
      {
        arraysNum[k] = 0;
      }
    }
  }
  return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();
    int casillaVacia = 0;

    for(int i = 0 ; i < 9 ; i++)
    {
      for(int j = 0 ; j < 9 ; j++)
      {
        if(n->sudo[i][j] == 0)
        {
          casillaVacia = 1;
          for(int k = 1 ; k <= 9 ; k++)
          {
            Node *nuevoNodo = createNode();
            nuevoNodo = copy(n);
            nuevoNodo->sudo[i][j] = k;

            if(is_valid(nuevoNodo) == 1)
            {
              pushBack(list, nuevoNodo);
            }
            else
            {
              free(nuevoNodo);
            }
          }
          break;
        }
      }

      if(casillaVacia)
      {
        break;
      }
    }
  return list;
}


int is_final(Node* n){
  int i;
  int j;

  for(i = 0 ; i < 9 ; i++)
  {
    for(j = 0 ; j < 9 ; j++)
    {
      if(n->sudo[i][j] == 0)
      {
        return 0;
      }
    }
  }
  return 1;
}

Node* DFS(Node* initial, int* cont){

  //Cree un stack S (pila) e inserte el nodo
  Stack *s = createStack();
  push(s, initial);

  (*cont) = 0;

  //Mientras el stack S no se encuentre vacío:

  while(is_empty(s) == 0)
  {
    //a) Saque y elimine el primer nodo de S.
    Node *encontrado = top(s);
    pop(s);

    //b) Verifique si corresponde a un estado final, si es así retorne el nodo.
    if(is_final(encontrado))
    {
      return encontrado;
    }
    
    //c) Obtenga la lista de nodos adyacentes al nodo.
    List *listaNodos = get_adj_nodes(encontrado);

    
    //d) Agregue los nodos de la lista (uno por uno) al stack S.
    Node *actual = first(listaNodos);
    while(actual != NULL)
    {
      push(s,actual);
      actual = next(listaNodos);
    }
    
    //e) Libere la memoria usada por el nodo.
    free(encontrado);
    (*cont)++;

  }

  //Si terminó de recorre el grafo sin encontrar una solución, retorne NULL.
  
  return NULL;
}




int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}