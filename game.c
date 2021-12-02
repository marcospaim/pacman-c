#include <stdio.h>
#include <stdbool.h>
#include "game.h"
#include "graph.h"
#include <time.h>
#include <stdlib.h>
#include "pilha_enc_plus.h"

//count coins in graph
int contaMoedas(GrafoLA *grafo)
{
    int count=0;
    for (int i = 0; i< grafo->numVertices; i++)
    {
        if (grafo->vertices[i].coin == 1 && grafo->vertices[i].coin == 2)
            count++;
    }
    return count;
}

//return random number
int random_number(int upper)
{
    int num = (rand() % upper );
    return num;
}

//control pacman's movement
void movimento_pacman(GrafoLA *grafo, Pacman *pacman)
{
    if ((int)pacman->x_pos == 0)
        {
            if (pacman->x_vel == SPEED
                 && buscaArestaGrafoLA(grafo, pacman->graph_pos, buscaNodoGrafoLA(grafo, (int)pacman->x_pos+1, (int)pacman->y_pos)))
                 pacman->x_pos += pacman->x_vel/FPS;

            if (pacman->x_vel == -SPEED
                 && buscaArestaGrafoLA(grafo, pacman->graph_pos, buscaNodoGrafoLA(grafo, 27, (int)pacman->y_pos)))
                    pacman->x_pos = 27;
        }
        else if ((int)pacman->x_pos == 27)
        {
            if (pacman->x_vel == SPEED
                 && buscaArestaGrafoLA(grafo, pacman->graph_pos, buscaNodoGrafoLA(grafo, 0, (int)pacman->y_pos)))
                 pacman->x_pos = 0;

            if (pacman->x_vel == -SPEED
                 && buscaArestaGrafoLA(grafo, pacman->graph_pos, buscaNodoGrafoLA(grafo, 0, (int)pacman->y_pos)))
                    pacman->x_pos += pacman->x_vel/FPS;
        }
        else
        {
            if ((pacman->x_vel == SPEED
                 && buscaArestaGrafoLA(grafo, pacman->graph_pos, buscaNodoGrafoLA(grafo, (int)pacman->x_pos+1, (int)pacman->y_pos)))
                 || (pacman->x_vel == -SPEED
                 && buscaArestaGrafoLA(grafo, pacman->graph_pos, buscaNodoGrafoLA(grafo, (int)pacman->x_pos-1, (int)pacman->y_pos))))
                    pacman->x_pos += pacman->x_vel/FPS;
        }

        if ((pacman->y_vel == SPEED
                 && buscaArestaGrafoLA(grafo, pacman->graph_pos, buscaNodoGrafoLA(grafo, (int)pacman->x_pos, (int)pacman->y_pos+1)))
                 || (pacman->y_vel == -SPEED
                 && buscaArestaGrafoLA(grafo, pacman->graph_pos, buscaNodoGrafoLA(grafo, (int)pacman->x_pos, (int)pacman->y_pos-1))))
                    pacman->y_pos += pacman->y_vel/FPS;
}

//controls ghosts' movement
void movimento_fantasma(GrafoLA *grafo, Ghost *fantasma)
{
    ArestaGrafo *arestaAux;
    //ArestaGrafo arestas[4];
    if (fantasma->flag != fantasma->graph_pos)
        fantasma->flag = 0;
    int count = 0;
    //conta o numero de arestas
    for (arestaAux = grafo->vertices[fantasma->graph_pos].lista; arestaAux != NULL; arestaAux = arestaAux->prox)
    {
        //arestas[count] = *arestaAux;
        count++;
    }
    if (count == 2 && fantasma->flag == 0 && (int)fantasma->x_pos != 0 && (int)fantasma->x_pos != 27)
    {
        fantasma->flag = fantasma->graph_pos;
        if (!buscaArestaGrafoLA(grafo, fantasma->graph_pos, buscaNodoGrafoLA(grafo, (int)(fantasma->x_pos+(fantasma->x_vel/SPEED)), (int)(fantasma->y_pos+(fantasma->y_vel/SPEED)))))
        {
            //printf("Aquii");
            if (fantasma->x_vel)
            {
                if(buscaArestaGrafoLA(grafo, fantasma->graph_pos, buscaNodoGrafoLA(grafo, (int)fantasma->x_pos, (int)fantasma->y_pos+1)))
                {
                    fantasma->x_vel = 0;
                    fantasma->y_vel = SPEED;
                }
                else
                {
                    fantasma->x_vel = 0;
                    fantasma->y_vel = -SPEED;
                }
            }
            else if (fantasma->y_vel)
            {
                if(buscaArestaGrafoLA(grafo, fantasma->graph_pos, buscaNodoGrafoLA(grafo, (int)fantasma->x_pos+1, (int)fantasma->y_pos)))
                {
                    fantasma->x_vel = SPEED;
                    fantasma->y_vel = 0;
                }
                else
                {
                    fantasma->x_vel = -SPEED;
                    fantasma->y_vel = 0;
                }
            }
        }
    }
    if (count == 3 && fantasma->flag == 0)
    {
        fantasma->flag = fantasma->graph_pos;
        int num = random_number(4);
        if(fantasma->x_vel)
        {
            if(buscaArestaGrafoLA(grafo, fantasma->graph_pos, buscaNodoGrafoLA(grafo, (int)fantasma->x_pos, (int)fantasma->y_pos+1)) && buscaArestaGrafoLA(grafo, fantasma->graph_pos, buscaNodoGrafoLA(grafo, (int)fantasma->x_pos, (int)fantasma->y_pos-1)))
            {
                if (num < 2)
                {
                    fantasma->x_vel = 0;
                    fantasma->y_vel = SPEED;
                }
                else
                {
                    fantasma->x_vel = 0;
                    fantasma->y_vel = -SPEED;
                }
            }
            else if(buscaArestaGrafoLA(grafo, fantasma->graph_pos, buscaNodoGrafoLA(grafo, (int)fantasma->x_pos, (int)fantasma->y_pos+1)))
            {
                if (num == 0)
                {
                    fantasma->x_vel = 0;
                    fantasma->y_vel = SPEED;
                }
            }
            else if(buscaArestaGrafoLA(grafo, fantasma->graph_pos, buscaNodoGrafoLA(grafo, (int)fantasma->x_pos, (int)fantasma->y_pos-1)))
            {
                if (num == 0)
                {
                    fantasma->x_vel = 0;
                    fantasma->y_vel = -SPEED;
                }
            }
        }
        else if (fantasma->y_vel)
        {
            if(buscaArestaGrafoLA(grafo, fantasma->graph_pos, buscaNodoGrafoLA(grafo, (int)fantasma->x_pos+1, (int)fantasma->y_pos)) && buscaArestaGrafoLA(grafo, fantasma->graph_pos, buscaNodoGrafoLA(grafo, (int)fantasma->x_pos-1, (int)fantasma->y_pos)))
            {
                if (num == 0)
                {
                    fantasma->x_vel = SPEED;
                    fantasma->y_vel = 0;
                }
                else
                {
                    fantasma->x_vel = -SPEED;
                    fantasma->y_vel = 0;
                }
            }
            else if(buscaArestaGrafoLA(grafo, fantasma->graph_pos, buscaNodoGrafoLA(grafo, (int)fantasma->x_pos+1, (int)fantasma->y_pos)))
            {
                if (num == 0)
                {
                    fantasma->x_vel = SPEED;
                    fantasma->y_vel = 0;
                }
            }
            else if(buscaArestaGrafoLA(grafo, fantasma->graph_pos, buscaNodoGrafoLA(grafo, (int)fantasma->x_pos-1, (int)fantasma->y_pos)))
            {
                if (num == 0)
                {
                    fantasma->x_vel = -SPEED;
                    fantasma->y_vel = 0;
                }
            }
        }
    }
    if ((int)fantasma->x_pos == 0)
        {
            if (fantasma->x_vel == SPEED
                 && buscaArestaGrafoLA(grafo, fantasma->graph_pos, buscaNodoGrafoLA(grafo, (int)fantasma->x_pos+1, (int)fantasma->y_pos)))
                 fantasma->x_pos += fantasma->x_vel/FPS;

            if (fantasma->x_vel == -SPEED
                 && buscaArestaGrafoLA(grafo, fantasma->graph_pos, buscaNodoGrafoLA(grafo, 27, (int)fantasma->y_pos)))
                    fantasma->x_pos = 27;
        }
        else if ((int)fantasma->x_pos == 27)
        {
            if (fantasma->x_vel == SPEED
                 && buscaArestaGrafoLA(grafo, fantasma->graph_pos, buscaNodoGrafoLA(grafo, 0, (int)fantasma->y_pos)))
                 fantasma->x_pos = 0;

            if (fantasma->x_vel == -SPEED
                 && buscaArestaGrafoLA(grafo, fantasma->graph_pos, buscaNodoGrafoLA(grafo, 0, (int)fantasma->y_pos)))
                    fantasma->x_pos += fantasma->x_vel/FPS;
        }
        else
        {
            if ((fantasma->x_vel == SPEED
                 && buscaArestaGrafoLA(grafo, fantasma->graph_pos, buscaNodoGrafoLA(grafo, (int)fantasma->x_pos+1, (int)fantasma->y_pos)))
                 || (fantasma->x_vel == -SPEED
                 && buscaArestaGrafoLA(grafo, fantasma->graph_pos, buscaNodoGrafoLA(grafo, (int)fantasma->x_pos-1, (int)fantasma->y_pos))))
                    fantasma->x_pos += fantasma->x_vel/FPS;
        }

        if ((fantasma->y_vel == SPEED
                 && buscaArestaGrafoLA(grafo, fantasma->graph_pos, buscaNodoGrafoLA(grafo, (int)fantasma->x_pos, (int)fantasma->y_pos+1)))
                 || (fantasma->y_vel == -SPEED
                 && buscaArestaGrafoLA(grafo, fantasma->graph_pos, buscaNodoGrafoLA(grafo, (int)fantasma->x_pos, (int)fantasma->y_pos-1))))
                    fantasma->y_pos += fantasma->y_vel/FPS;
}

//move ghost to the original position taking the shortest path
void retorno_fantasma(GrafoLA *grafo, Ghost *fantasma)
{
    if (!fantasma->returning)
    {
        BFSGrafoLA(grafo, fantasma->graph_pos);
        ArestaGrafo *arestaAux;

        // find shortest path from destination node to initial node and save it in a stack
        int vertice = buscaNodoGrafoLA(grafo, (int)fantasma->x_pos_orig, (int)fantasma->y_pos_orig); //destination node
        int d = grafo->vertices[vertice].distInicio; //distance from destination node to initial node
        fantasma->pilha = criaPilha();
        while (d != 0)
        {
            d--;
            for (arestaAux = grafo->vertices[vertice].lista; arestaAux != NULL; arestaAux = arestaAux->prox)
            {
                if (grafo->vertices[arestaAux->chaveDest].distInicio == d)
                {
                    vertice = arestaAux->chaveDest;
                    empilhaPilha(fantasma->pilha, vertice, grafo->vertices[arestaAux->chaveDest].x, grafo->vertices[arestaAux->chaveDest].y);
                    break;
                }

            }
        }
        fantasma->returning = 1;
    }

    //control speed and pop stack
    if (fantasma->pilha->topo != NULL)
    {
        if ((int)fantasma->x_pos < fantasma->pilha->topo->x)
        {
            fantasma->x_vel = SPEED;
            fantasma->y_vel = 0;
        }
        else if ((int)fantasma->x_pos > fantasma->pilha->topo->x)
        {
            fantasma->x_vel = -SPEED;
            fantasma->y_vel = 0;
        }
        else if ((int)fantasma->y_pos > fantasma->pilha->topo->y)
        {
            fantasma->x_vel = 0;
            fantasma->y_vel = -SPEED;
        }
        else if ((int)fantasma->y_pos < fantasma->pilha->topo->y)
        {
            fantasma->x_vel = 0;
            fantasma->y_vel = SPEED;
        }
        if (fantasma->graph_pos == fantasma->pilha->topo->graph_pos)
        {
            if (fantasma->pilha->topo != NULL)
                desempilhaPilha(fantasma->pilha);
        }
    }

    if (fantasma->graph_pos == buscaNodoGrafoLA(grafo, (int)fantasma->x_pos_orig, (int)fantasma->y_pos_orig))
    {
        fantasma->returning = 0;
        destroiPilha(fantasma->pilha);
    }
    //move ghost
    if ((int)fantasma->x_pos == 0)
        {
            if (fantasma->x_vel == SPEED
                 && buscaArestaGrafoLA(grafo, fantasma->graph_pos, buscaNodoGrafoLA(grafo, (int)fantasma->x_pos+1, (int)fantasma->y_pos)))
                 fantasma->x_pos += fantasma->x_vel/FPS;

            if (fantasma->x_vel == -SPEED
                 && buscaArestaGrafoLA(grafo, fantasma->graph_pos, buscaNodoGrafoLA(grafo, 27, (int)fantasma->y_pos)))
                    fantasma->x_pos = 27;
        }
        else if ((int)fantasma->x_pos == 27)
        {
            if (fantasma->x_vel == SPEED
                 && buscaArestaGrafoLA(grafo, fantasma->graph_pos, buscaNodoGrafoLA(grafo, 0, (int)fantasma->y_pos)))
                 fantasma->x_pos = 0;

            if (fantasma->x_vel == -SPEED
                 && buscaArestaGrafoLA(grafo, fantasma->graph_pos, buscaNodoGrafoLA(grafo, 0, (int)fantasma->y_pos)))
                    fantasma->x_pos += fantasma->x_vel/FPS;
        }
        else
        {
            if ((fantasma->x_vel == SPEED
                 && buscaArestaGrafoLA(grafo, fantasma->graph_pos, buscaNodoGrafoLA(grafo, (int)fantasma->x_pos+1, (int)fantasma->y_pos)))
                 || (fantasma->x_vel == -SPEED
                 && buscaArestaGrafoLA(grafo, fantasma->graph_pos, buscaNodoGrafoLA(grafo, (int)fantasma->x_pos-1, (int)fantasma->y_pos))))
                    fantasma->x_pos += fantasma->x_vel/FPS;
        }

        if ((fantasma->y_vel == SPEED
                 && buscaArestaGrafoLA(grafo, fantasma->graph_pos, buscaNodoGrafoLA(grafo, (int)fantasma->x_pos, (int)fantasma->y_pos+1)))
                 || (fantasma->y_vel == -SPEED
                 && buscaArestaGrafoLA(grafo, fantasma->graph_pos, buscaNodoGrafoLA(grafo, (int)fantasma->x_pos, (int)fantasma->y_pos-1))))
                    fantasma->y_pos += fantasma->y_vel/FPS;
}

//inicialize game
void initialize_game (Game *game, Ghost *blinky, Ghost *pinky, Ghost *inky, Ghost *clyde, Pacman *pacman)
{
    // inicializar pacman
    pacman->x_vel = -SPEED;
    pacman->y_vel = 0;
    pacman->x_pos = 13;
    pacman->y_pos = 26;
    pacman->lives = 3;
    pacman->coins = 0;

    blinky->x_vel = -SPEED;
    blinky->y_vel = 0;
    blinky->x_pos = blinky->x_pos_orig = 13;
    blinky->y_pos = blinky->y_pos_orig = 14;
    blinky->flag = 0;
    blinky->returning = 0;

    pinky->x_vel = -SPEED;
    pinky->y_vel = 0;
    pinky->x_pos = pinky->x_pos_orig = 13;
    pinky->y_pos = pinky->y_pos_orig = 17;
    pinky->flag = 0;
    pinky->returning = 0;

    inky->x_vel = -SPEED;
    inky->y_vel = 0;
    inky->x_pos = inky->x_pos_orig = 11;
    inky->y_pos = inky->y_pos_orig = 17;
    inky->flag = 0;
    inky->returning = 0;

    clyde->x_vel = -SPEED;
    clyde->y_vel = 0;
    clyde->x_pos = clyde->x_pos_orig = 15;
    clyde->y_pos = clyde->y_pos_orig = 17;
    clyde->flag = 0;
    clyde->returning = 0;

    game->frightened = 0;
}
