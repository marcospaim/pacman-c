#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED


#define NUMVER 320
typedef enum{
  EXPLORATORIA = 0,
  OUTRA /* Nao Exploratoria */
} tipoAresta;

typedef enum{
  BRANCO = 0, /* Nao Explorado */
  CINZA, /* Sob Exploracao */
  PRETO /* Explorado */
} corVertice;

typedef struct arGrafo{
   int chaveDest; // Chave do nodo destino
   struct arGrafo *prox; // Proxima aresta
   tipoAresta tipo; // Util para DFS e BFS
} ArestaGrafo;

typedef struct noGrafo{
   int x;
   int y;
   int coin;
   ArestaGrafo *lista; // Lista de arestas
   corVertice cor; // Util para DFS e BFS
   int tEntrada; // Util para DFS e BFS
   int tSaida; // Util para DFS e BFS
   int pai; // Util para DFS e BFS
   int distInicio; // Util para BFS
} NoGrafo;

typedef struct{
   int numVertices; // Numero de vertices
   NoGrafo *vertices; // Vetor de vertices
   int timestamp; // Util para DFS e BFS
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

// Funcao auxiliar para Algs. de Caminhamento
void inicializaCaminhamentoGrafoLA(GrafoLA *grafo);

// Alg. para Caminhamento em Amplitude
void BFSGrafoLA(GrafoLA *grafo, int chaveInicial);

#endif // GRAPH_H_INCLUDED
