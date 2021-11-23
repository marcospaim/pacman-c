#include <stdio.h>
#include "game.h"
#include "graph.h"
#include <time.h>
#include <stdlib.h>

//conta moedas em grafo
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

int random_number(int upper)
{
    int num = (rand() % upper );
    return num;
}

void movimento_pacman(GrafoLA *grafo, Pacman *pacman)
{
    if ((int)pacman->x_pos == 0)
        {
            printf("aqui");
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

void movimento_fantasma(GrafoLA *grafo, Ghost *fantasma)
{
    ArestaGrafo *arestaAux;
    ArestaGrafo arestas[4];
    if (fantasma->flag != fantasma->graph_pos)
        fantasma->flag = 0;
    int count = 0;
    //conta o numero de arestas
    for (arestaAux = grafo->vertices[fantasma->graph_pos].lista; arestaAux != NULL; arestaAux = arestaAux->prox)
    {
        arestas[count] = *arestaAux;
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
