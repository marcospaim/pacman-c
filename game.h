#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include "graph.h"


#define SPEED 16
#define FPS 60
#define TICK_INTERVAL 1000/FPS

typedef struct
{
    float x_vel;
    float y_vel;
    float x_pos;
    float y_pos;
    int graph_pos;

}Pacman;
typedef struct
{
    float x_vel;
    float y_vel;
    float x_pos;
    float y_pos;
    int flag;
    int graph_pos;
}Ghost;

//conta moedas em grafo
int contaMoedas(GrafoLA *grafo);

void movimento_pacman(GrafoLA *grafo, Pacman *pacman);

void movimento_fantasma(GrafoLA *grafo, Ghost *fantasma);

int random_number(int upper);
#endif // GAME_H_INCLUDED
