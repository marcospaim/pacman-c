#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL_timer.h>
#include <SDL_image.h>
#include "graph.h"
#include "sdl2_graphics.h"

#define SPEED 8
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
int main(int argc, char* argv[])
{
    //Main loop flag
    bool quit = false;
    GrafoLA *grafo = criaGrafoLA(NUMVER);
    Pacman pacman;
    // Velocidade y e x do pacman
    pacman.x_vel = -SPEED;
    pacman.y_vel = 0;

    winRect.w = WIN_WIDTH/28;
    winRect.h = WIN_HEIGHT/36;
    winRect.x = winRect.y = 0;

    //initialize sdl
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }
    // Create game window
    window =  SDL_CreateWindow("Pacman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, 0);
    if (!window) // handle errors
    {
        printf("error creating window: %s\n", SDL_GetError());
        // safely shut down all subsystems
        SDL_Quit();
        return 1;
    }
    // create renderer flags and renderer

    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    renderer = SDL_CreateRenderer(window, -1, render_flags);
    if (!renderer)
    {
        printf("error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    //Draw map background
    SDL_Texture* tex2 = loadTexture("images/Pac-Man-mapa-244-288.png");
    if (!tex2)
    {
        printf("error opening image\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    // clear the window
    SDL_RenderClear(renderer);
    // draw the image to the window
    SDL_RenderCopy(renderer, tex, NULL, NULL);
    SDL_RenderPresent(renderer);

    //test sprites
    tex = loadTexture("images/pacman-all-sprites.png");
    if (!tex)
    {
        printf("error opening image\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    drawSprite(tex, 5, 13, 26);
    pacman.x_pos = 13;
    pacman.y_pos = 26;
    pacman.graph_pos = buscaNodoGrafoLA(grafo, (int)pacman.x_pos, (int)pacman.y_pos);
    inicialize_graph (grafo);
    draw_coins(grafo);
    SDL_RenderPresent(renderer);
    //printf("%d\n",buscaNodoGrafoLA(grafo, 0, 17));
    //imprimearestas (grafo);
    //impreimegrafo (grafo);

    //Event handler
    SDL_Event e;
    static Uint32 next_time;
    Uint32 now;
    //While application is running
    next_time = SDL_GetTicks() + TICK_INTERVAL;
    while( !quit )
    {
        // Controla o tempo do jogo
        now = SDL_GetTicks();
        if (next_time <= now)
            SDL_Delay(0);
        //else
            //SDL_Delay(next_time-now);
        //printf("%lu \n", (unsigned long)next_time-now);
        next_time += TICK_INTERVAL;
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            switch (e.type)
            {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYUP:
                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym)
                    {
                        case SDLK_LEFT:
                            if (buscaArestaGrafoLA(grafo, pacman.graph_pos, buscaNodoGrafoLA(grafo, (int)pacman.x_pos-1, (int)pacman.y_pos)))
                            {
                                pacman.x_vel = -SPEED;
                                pacman.y_vel = 0;
                            }
                            break;
                        case SDLK_RIGHT:
                            if (buscaArestaGrafoLA(grafo, pacman.graph_pos, buscaNodoGrafoLA(grafo, (int)pacman.x_pos+1, (int)pacman.y_pos)))
                            {
                                pacman.x_vel = SPEED;
                                pacman.y_vel = 0;
                            }
                            break;
                        case SDLK_UP:
                            if (buscaArestaGrafoLA(grafo, pacman.graph_pos, buscaNodoGrafoLA(grafo, (int)pacman.x_pos, (int)pacman.y_pos-1)))
                            {
                                pacman.x_vel = 0;
                                pacman.y_vel = -SPEED;
                            }
                            break;
                        case SDLK_DOWN:
                            if (buscaArestaGrafoLA(grafo, pacman.graph_pos, buscaNodoGrafoLA(grafo, (int)pacman.x_pos, (int)pacman.y_pos+1)))
                            {
                                pacman.x_vel = 0;
                                pacman.y_vel = SPEED;
                            }
                            break;
                    }
                    break;
            }
        }
        // clear the window
        SDL_RenderClear(renderer);
        // draw the image to the window
        SDL_RenderCopy(renderer, tex2, NULL, NULL); // Desenha o mapa

        draw_coins(grafo);

        if (pacman.x_vel) // se eh diferente de 0
        {
            if (pacman.x_vel == SPEED
                 && buscaArestaGrafoLA(grafo, pacman.graph_pos, buscaNodoGrafoLA(grafo, (int)pacman.x_pos+1, (int)pacman.y_pos))
                 || pacman.x_vel == -SPEED
                 && buscaArestaGrafoLA(grafo, pacman.graph_pos, buscaNodoGrafoLA(grafo, (int)pacman.x_pos-1, (int)pacman.y_pos)))
                    pacman.x_pos += pacman.x_vel/FPS;
        }
        else if (pacman.y_vel)
        {
            if ((pacman.y_vel == SPEED
                 && buscaArestaGrafoLA(grafo, pacman.graph_pos, buscaNodoGrafoLA(grafo, (int)pacman.x_pos, (int)pacman.y_pos+1)))
                 || (pacman.y_vel == -SPEED
                 && buscaArestaGrafoLA(grafo, pacman.graph_pos, buscaNodoGrafoLA(grafo, (int)pacman.x_pos, (int)pacman.y_pos-1))))
                    pacman.y_pos += pacman.y_vel/FPS;
        }

        pacman.graph_pos = buscaNodoGrafoLA(grafo, (int)pacman.x_pos, (int)pacman.y_pos);
        drawSprite(tex, 5, (int) pacman.x_pos, (int) pacman.y_pos);
        SDL_RenderPresent(renderer);
    }
    // clean up resources before exiting
    SDL_DestroyTexture(tex2); //destroi textura do mapa
    quit_program();

    return 0;
}

