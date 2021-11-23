#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED


#define NUMVER 320

typedef struct arGrafo{
   int chaveDest; // Chave do nodo destino
   struct arGrafo *prox; // Proxima aresta
} ArestaGrafo;

typedef struct noGrafo{
   int x;
   int y;
   int coin;
   ArestaGrafo *lista; // Lista de arestas
} NoGrafo;

typedef struct{
   int numVertices; // Numero de vertices
   NoGrafo *vertices; // Vetor de vertices
} GrafoLA;

GrafoLA *criaGrafoLA(int numVertices);

//Inicializa grafo do pacman
void inicialize_graph (GrafoLA *grafo);

//inicializa grafo dos fantasmas
void inicialize_graphGhosts (GrafoLA *grafo);

// Funcao que insere uma aresta em um grafo
void insereArestaGrafoLA(GrafoLA *grafo, int chave1, int chave2);

void imprimearestas (GrafoLA *grafo);

void impreimegrafo (GrafoLA *grafo);

//funcao que verifica se ha uma aresta entre chave1 e chave2
int buscaArestaGrafoLA(GrafoLA *grafo, int chave1, int chave2);

//funcao que busca nodo e retorna seu indice
int buscaNodoGrafoLA(GrafoLA *grafo, int x, int y);


#endif // GRAPH_H_INCLUDED
