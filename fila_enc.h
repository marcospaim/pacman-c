#ifndef FILA_ENC_H_INCLUDED
#define FILA_ENC_H_INCLUDED

typedef struct listaNodo{
   int info;
   struct listaNodo *prox;
} ListaNodo;

typedef struct filaEnc{
   struct listaNodo *ini;
   struct listaNodo *fim;
} FilaEnc;

// Funcao que cria uma fila
FilaEnc* criaFila();

// Funcao que destroi uma fila
void destroiFila(FilaEnc *fila);

// Funcao que insere um elemento na fila
void enfileiraFila(FilaEnc *fila, int info);

// Funcao que remove um elemento da fila
int desenfileiraFila(FilaEnc *fila);

// Funcao que determina se uma fila eh vazia
int vaziaFila(FilaEnc* fila);



#endif // FILA_ENC_H_INCLUDED
