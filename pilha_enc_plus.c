#include "pilha_enc_plus.h"
#include <stdio.h>
#include <stdlib.h>
#include "fila_enc.h"

// Funcao que cria uma pilha
pilhaEncPlus* criaPilha(){
   pilhaEncPlus *pilha = (pilhaEncPlus*)malloc(sizeof(pilhaEncPlus));
   pilha->topo = NULL;
   return pilha;
}

// Funcao que destroi uma pilha
void destroiPilha(pilhaEncPlus *pilha){
   ListaNodoPilha *aux = pilha->topo;
   while(aux != NULL){
       ListaNodoPilha *tmp = aux->prox;
       free(aux); // Cuidar ordem do free
       aux = tmp;
   }
   free(pilha);
}

// Funcao que insere um elemento na pilha
void empilhaPilha(pilhaEncPlus *pilha, int vertice, int x, int y){
   ListaNodoPilha *novo = (ListaNodo*)malloc(sizeof(ListaNodo));
   novo->graph_pos = vertice;
   novo->x = x;
   novo->y = y;
   novo->prox = pilha->topo;
   pilha->topo = novo;
}


// Funcao que remove um elemento da pilha
int desempilhaPilha(pilhaEncPlus* pilha){
   ListaNodoPilha *aux = pilha->topo;
   /* Aqui assumimos que desempilha eh
   chamada apenas se a pilha nao eh vazia */
   int vertice = aux->graph_pos;
   pilha->topo = aux->prox;
   free(aux);
   return vertice;
}

// Funcao que determina se uma pilha eh vazia
int vaziaPilha(pilhaEncPlus *pilha){
   return (pilha->topo == NULL);
}
