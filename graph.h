#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED


#define NUMVER 321

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
void inicialize_graph (GrafoLA *graph);
#endif // GRAPH_H_INCLUDED
