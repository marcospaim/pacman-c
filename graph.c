#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include "sdl2_graphics.h"

// Funcao que cria um grafo
GrafoLA *criaGrafoLA(int numVertices){
   int chave;
   GrafoLA * grafo = (GrafoLA*)malloc(sizeof(GrafoLA));
   grafo->vertices = (NoGrafo*)malloc(sizeof(NoGrafo)*numVertices);
   for (chave = 0; chave < numVertices; chave++)
      grafo->vertices[chave].lista = NULL;
   grafo->numVertices = numVertices;
   return grafo;
}

// Funcao que insere um nodo
void insereNodoGrafoLA(GrafoLA *grafo, int i, int x, int y, int coin){
   // Assume ids que funcionam como indexadores
   grafo->vertices[i].x = x;
   grafo->vertices[i].y = y;
   grafo->vertices[i].coin = coin;
}

void inicialize_graph (GrafoLA *graph)
{
    int count = 0;
    for (int i = 0; i<36; i++)
    {
        for (int j=0;j<28;j++)
        {
            if (initial_map[i][j] <= 2)
            {
                insereNodoGrafoLA(graph, count, j, i, initial_map[i][j]);
                count++;
            }
        }
    }
}
