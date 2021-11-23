#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include "sdl2_graphics.h"
#include "fila_enc.h"

void impreimegrafo (GrafoLA *grafo)
{

    for (int i = 0; i< grafo->numVertices; i++)
    {
        printf("%d: x: %d, y: %d\n",i, grafo->vertices[i].x, grafo->vertices[i].y);
    }
}
void imprimearestas (GrafoLA *grafo)
{
    for (int i = 0; i< grafo->numVertices; i++)
    {
        ArestaGrafo *arestaAux;
        for (arestaAux = grafo->vertices[i].lista; arestaAux != NULL; arestaAux = arestaAux->prox)
        printf("\n{%d, %d}", i, arestaAux->chaveDest);
    }
}
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
   grafo->vertices[i].x = x;
   grafo->vertices[i].y = y;
   grafo->vertices[i].coin = coin;
}
//funcao que busca nodo e retorna seu indice
int buscaNodoGrafoLA(GrafoLA *grafo, int x, int y)
{
    for (int i = 0; i< grafo->numVertices; i++)
    {
        if (grafo->vertices[i].x == x && grafo->vertices[i].y == y)
            return i;
    }
    return -1;
}
//funcao que verifica se ha uma aresta entre chave1 e chave2
int buscaArestaGrafoLA(GrafoLA *grafo, int chave1, int chave2)
{
    if (chave1 == -1 || chave2 == -1)
        return 0;
    ArestaGrafo *arestaAux;
    for (arestaAux = grafo->vertices[chave1].lista; arestaAux != NULL; arestaAux = arestaAux->prox)
    {
        if (arestaAux->chaveDest == chave2)
            return 1;
    }
    return 0;
}

// Funcao que insere uma aresta em um grafo
void insereArestaGrafoLA(GrafoLA *grafo, int chave1, int chave2){
    if (!buscaArestaGrafoLA(grafo, chave1, chave2))
    {
        ArestaGrafo *arestaAux = (ArestaGrafo*)malloc(sizeof(ArestaGrafo));
        arestaAux->chaveDest = chave2;
        arestaAux->prox = grafo->vertices[chave1].lista;
        grafo->vertices[chave1].lista = arestaAux;
    }
    //Insere aresta simetrica
    if (!buscaArestaGrafoLA(grafo, chave2, chave1))
    {
        ArestaGrafo *arestaAux2 = (ArestaGrafo*)malloc(sizeof(ArestaGrafo));
        arestaAux2->chaveDest = chave1;
        arestaAux2->prox = grafo->vertices[chave2].lista;
        grafo->vertices[chave2].lista = arestaAux2;
    }
}

//Inicializa grafo do pacman
void inicialize_graph (GrafoLA *grafo)
{
    int count = 0;
    for (int i = 0; i<36; i++)
    {
        for (int j=0;j<28;j++)
        {
            if (initial_map[i][j] <= 2 )
            {
                insereNodoGrafoLA(grafo, count, j, i, initial_map[i][j]);
                count++;
            }
        }
    }
    //insere arestas
    for (int i = 0; i<36; i++)
    {
        for (int j=0;j<28;j++)
        {
            if (initial_map[i][j] <= 2)
            {
                if (j == 0)
                {
                    if (initial_map[i-1][j] <= 2)
                        insereArestaGrafoLA(grafo, buscaNodoGrafoLA(grafo, j, i), buscaNodoGrafoLA(grafo, j, i-1));
                    if (initial_map[i+1][j] <= 2)
                        insereArestaGrafoLA(grafo, buscaNodoGrafoLA(grafo, j, i), buscaNodoGrafoLA(grafo, j, i+1));
                    if (initial_map[i][27] <= 2)
                        insereArestaGrafoLA(grafo, buscaNodoGrafoLA(grafo, j, i), buscaNodoGrafoLA(grafo, 27, i));
                    if (initial_map[i][j+1] <= 2)
                        insereArestaGrafoLA(grafo, buscaNodoGrafoLA(grafo, j, i), buscaNodoGrafoLA(grafo, j+1, i));
                }
                else if (j == 27)
                {
                    if (initial_map[i-1][j] <= 2)
                        insereArestaGrafoLA(grafo, buscaNodoGrafoLA(grafo, j, i), buscaNodoGrafoLA(grafo, j, i-1));
                    if (initial_map[i+1][j] <= 2)
                        insereArestaGrafoLA(grafo, buscaNodoGrafoLA(grafo, j, i), buscaNodoGrafoLA(grafo, j, i+1));
                    if (initial_map[i][j-1] <= 2)
                        insereArestaGrafoLA(grafo, buscaNodoGrafoLA(grafo, j, i), buscaNodoGrafoLA(grafo, j-1, i));
                    if (initial_map[i][0] <= 2)
                        insereArestaGrafoLA(grafo, buscaNodoGrafoLA(grafo, j, i), buscaNodoGrafoLA(grafo, 0, i));
                }
                else
                {
                    if (initial_map[i-1][j] <= 2)
                        insereArestaGrafoLA(grafo, buscaNodoGrafoLA(grafo, j, i), buscaNodoGrafoLA(grafo, j, i-1));
                    if (initial_map[i+1][j] <= 2)
                        insereArestaGrafoLA(grafo, buscaNodoGrafoLA(grafo, j, i), buscaNodoGrafoLA(grafo, j, i+1));
                    if (initial_map[i][j-1] <= 2)
                        insereArestaGrafoLA(grafo, buscaNodoGrafoLA(grafo, j, i), buscaNodoGrafoLA(grafo, j-1, i));
                    if (initial_map[i][j+1] <= 2)
                        insereArestaGrafoLA(grafo, buscaNodoGrafoLA(grafo, j, i), buscaNodoGrafoLA(grafo, j+1, i));
                }
            }
        }
    }
}
//inicializa grafo dos fantasmas
void inicialize_graphGhosts (GrafoLA *grafo)
{
    int count = 0;
    for (int i = 0; i<36; i++)
    {
        for (int j=0;j<28;j++)
        {
            if (initial_map[i][j] <= 2 || initial_map[i][j] == 5)
            {
                insereNodoGrafoLA(grafo, count, j, i, initial_map[i][j]);
                count++;
            }
        }
    }

    //insere arestas
    for (int i = 0; i<36; i++)
    {
        for (int j=0;j<28;j++)
        {
            if (initial_map[i][j] <= 2 || initial_map[i-1][j] == 5)
            {
                if (j == 0)
                {
                    if (initial_map[i-1][j] <= 2 || initial_map[i-1][j] == 5)
                        insereArestaGrafoLA(grafo, buscaNodoGrafoLA(grafo, j, i), buscaNodoGrafoLA(grafo, j, i-1));
                    if (initial_map[i+1][j] <= 2 || initial_map[i+1][j] == 5)
                        insereArestaGrafoLA(grafo, buscaNodoGrafoLA(grafo, j, i), buscaNodoGrafoLA(grafo, j, i+1));
                    if (initial_map[i][27] <= 2 || initial_map[i][27] == 5)
                        insereArestaGrafoLA(grafo, buscaNodoGrafoLA(grafo, j, i), buscaNodoGrafoLA(grafo, 27, i));
                    if (initial_map[i][j+1] <= 2 || initial_map[i][j+1] == 5)
                        insereArestaGrafoLA(grafo, buscaNodoGrafoLA(grafo, j, i), buscaNodoGrafoLA(grafo, j+1, i));
                }
                else if (j == 27)
                {
                    if (initial_map[i-1][j] <= 2 || initial_map[i-1][j] == 5)
                        insereArestaGrafoLA(grafo, buscaNodoGrafoLA(grafo, j, i), buscaNodoGrafoLA(grafo, j, i-1));
                    if (initial_map[i+1][j] <= 2 || initial_map[i+1][j] == 5)
                        insereArestaGrafoLA(grafo, buscaNodoGrafoLA(grafo, j, i), buscaNodoGrafoLA(grafo, j, i+1));
                    if (initial_map[i][j-1] <= 2 || initial_map[i][j-1] == 5)
                        insereArestaGrafoLA(grafo, buscaNodoGrafoLA(grafo, j, i), buscaNodoGrafoLA(grafo, j-1, i));
                    if (initial_map[i][0] <= 2 || initial_map[i][0] == 5)
                        insereArestaGrafoLA(grafo, buscaNodoGrafoLA(grafo, j, i), buscaNodoGrafoLA(grafo, 0, i));
                }
                else
                {
                    if (initial_map[i-1][j] <= 2 || initial_map[i-1][j] == 5)
                        insereArestaGrafoLA(grafo, buscaNodoGrafoLA(grafo, j, i), buscaNodoGrafoLA(grafo, j, i-1));
                    if (initial_map[i+1][j] <= 2 || initial_map[i+1][j] == 5)
                        insereArestaGrafoLA(grafo, buscaNodoGrafoLA(grafo, j, i), buscaNodoGrafoLA(grafo, j, i+1));
                    if (initial_map[i][j-1] <= 2 || initial_map[i][j-1] == 5)
                        insereArestaGrafoLA(grafo, buscaNodoGrafoLA(grafo, j, i), buscaNodoGrafoLA(grafo, j-1, i));
                    if (initial_map[i][j+1] <= 2 || initial_map[i][j+1] == 5)
                        insereArestaGrafoLA(grafo, buscaNodoGrafoLA(grafo, j, i), buscaNodoGrafoLA(grafo, j+1, i));
                }
            }
        }
    }
}

// Funcao auxiliar para Algs. de Caminhamento
void inicializaCaminhamentoGrafoLA(GrafoLA *grafo){
   int chave;
   grafo->timestamp = 0;
   for (chave = 0; chave < grafo->numVertices; chave++){
      grafo->vertices[chave].cor = BRANCO;
      grafo->vertices[chave].tEntrada = -1;
      grafo->vertices[chave].tSaida = -1;
      grafo->vertices[chave].pai = -1;
   }
   for (chave = 0; chave < grafo->numVertices; chave++)
      for (ArestaGrafo *arestaAux = grafo->vertices[chave].lista;
           arestaAux != NULL; arestaAux = arestaAux->prox){
           arestaAux->tipo = OUTRA;
      }
}

// Alg. para Caminhamento em Amplitude
void BFSGrafoLA(GrafoLA *grafo, int chaveInicial){
   inicializaCaminhamentoGrafoLA(grafo);
   FilaEnc *fila = criaFila();
   enfileiraFila(fila, chaveInicial);
   grafo->vertices[chaveInicial].tEntrada = grafo->timestamp++;
   grafo->vertices[chaveInicial].cor = CINZA;
   grafo->vertices[chaveInicial].distInicio = 0;
   while(!vaziaFila(fila)){
      int chave1 = desenfileiraFila(fila);
      for(ArestaGrafo *arestaAux = grafo->vertices[chave1].lista;
          arestaAux != NULL; arestaAux = arestaAux->prox){
          int chave2 = arestaAux->chaveDest;
          if(grafo->vertices[chave2].cor == BRANCO){
             grafo->vertices[chave2].pai = chave1;
             grafo->vertices[chave2].distInicio = grafo->vertices[chave1].distInicio + 1;
             grafo->vertices[chave2].tEntrada = grafo->timestamp++;
             grafo->vertices[chave2].cor = CINZA;
             arestaAux->tipo = EXPLORATORIA;
             enfileiraFila(fila, chave2);
          }
      }
      grafo->vertices[chave1].cor = PRETO;
      grafo->vertices[chave1].tSaida = grafo->timestamp++;
   }
   destroiFila(fila);
}
