#ifndef PILHA_ENC_PLUS_H_INCLUDED
#define PILHA_ENC_PLUS_H_INCLUDED

typedef struct listaNodoPilha{
   int graph_pos;
   int x;
   int y;
   struct listaNodo *prox;
} ListaNodoPilha;


typedef struct pilhaEncPlus{
   struct listaNodoPilha *topo;
} pilhaEncPlus;

// Funcao que cria uma pilha
pilhaEncPlus* criaPilha();

// Funcao que destroi uma pilha
void destroiPilha(pilhaEncPlus *pilha);

// Funcao que insere um elemento na pilha
void empilhaPilha(pilhaEncPlus *pilha, int vertice, int x, int y);

// Funcao que remove um elemento da pilha
int desempilhaPilha(pilhaEncPlus *pilha);

// Funcao que determina se uma pilha eh vazia
int vaziaPilha(pilhaEncPlus* pilha);


#endif // PILHA_ENC_PLUS_H_INCLUDED
