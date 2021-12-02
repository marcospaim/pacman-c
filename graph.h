#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED


#define NUMVER 320
typedef enum{
  EXPLORATORIA = 0,
  OUTRA /* non exploratory */
} tipoAresta;

typedef enum{
  BRANCO = 0, /* Not explored */
  CINZA, /* being explored */
  PRETO /* Explored */
} corVertice;

typedef struct arGrafo{
   int chaveDest; // node adjacent to this node
   struct arGrafo *prox; // Next edge
   tipoAresta tipo; // Useful for DFS and BFS
} ArestaGrafo;

typedef struct noGrafo{
   int x;
   int y;
   int coin;
   ArestaGrafo *lista; // edges list
   corVertice cor; // Useful for DFS and BFS
   int tEntrada; // Useful for DFS and BFS
   int tSaida; // Useful for DFS and BFS
   int pai; // Useful for DFS and BFS
   int distInicio; // Useful for DFS and BFS
} NoGrafo;

// Graph using adjacency list
typedef struct{
   int numVertices; // Number of vertices
   NoGrafo *vertices; // Vertices vector
   int timestamp; // Useful for DFS and BFS
} GrafoLA;

// create graph
GrafoLA *criaGrafoLA(int numVertices);

//Initialize pacman's graph
void inicialize_graph (GrafoLA *grafo);

//initialize ghosts' map
void inicialize_graphGhosts (GrafoLA *grafo);

// insert edge in graph
void insereArestaGrafoLA(GrafoLA *grafo, int chave1, int chave2);

//print graph's edges
void imprimearestas (GrafoLA *grafo);

//print graph
void impreimegrafo (GrafoLA *grafo);

//check if there is edge between two nodes
int buscaArestaGrafoLA(GrafoLA *grafo, int chave1, int chave2);

//Search node and return index
int buscaNodoGrafoLA(GrafoLA *grafo, int x, int y);

// Auxiliary function for search algorithm
void inicializaCaminhamentoGrafoLA(GrafoLA *grafo);

// Breadth-first search
void BFSGrafoLA(GrafoLA *grafo, int chaveInicial);

#endif // GRAPH_H_INCLUDED
