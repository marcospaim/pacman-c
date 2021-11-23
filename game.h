#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include "graph.h"
#include "pilha_enc_plus.h"
#include <stdbool.h>
#include <SDL.h>

#define SPEED 8
#define FPS 60
#define TICK_INTERVAL 1000/FPS
#define COINS 244

typedef struct
{
    float x_vel;
    float y_vel;
    float x_pos;
    float y_pos;
    int graph_pos;
    int lives;
    int coins;
}Pacman;
typedef struct
{
    float x_vel;
    float y_vel;
    float x_pos;
    float y_pos;
    int x_pos_orig; //posicao x inicial do fantasma
    int y_pos_orig; //posicao y inicial do fantasma
    int flag;
    int returning;
    int graph_pos;
    pilhaEncPlus *pilha;
}Ghost;

typedef struct
{
    bool frightened;
    bool run;
    int last_game;
    Uint32 frightened_time;
}Game;

//conta moedas em grafo
int contaMoedas(GrafoLA *grafo);

void movimento_pacman(GrafoLA *grafo, Pacman *pacman);

void movimento_fantasma(GrafoLA *grafo, Ghost *fantasma);

void retorno_fantasma(GrafoLA *grafo, Ghost *fantasma);

int random_number(int upper);

void initialize_game (Game *game, Ghost *blinky, Ghost *pinky, Ghost *inky, Ghost *clyde, Pacman *pacman);
#endif // GAME_H_INCLUDED
