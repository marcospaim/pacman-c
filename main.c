#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL_timer.h>
#include <SDL_image.h>
#include "graph.h"
#include "sdl2_graphics.h"


int main(int argc, char* argv[])
{
    const int FPS = 60;
    //Main loop flag
    bool quit = false;
    GrafoLA *grafo = criaGrafoLA(NUMVER);

    winRect.w = WIN_WIDTH/28;
    winRect.h = WIN_HEIGHT/36;
    winRect.x = winRect.y = 0;

    //initialize sdl
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }
    /*
    int count = 0;
    for (int i = 0; i<36; i++)
    {
        for (int j=0;j<28;j++)
        {
            if (initial_map[i][j] <= 2)
                count++;
        }
    }
    printf("Numero de vertices: %d\n", count);
    count = 0;
    for (int i = 0; i<36; i++)
    {
        for (int j=0;j<28;j++)
        {
            if (j < 27)
            {
                if (initial_map[i][j] <= 2 && initial_map[i][j+1] <= 2)
                    count++;
            }
            else
            {
                if (initial_map[i][j] <= 2 && initial_map[i][0] <= 2)
                    count++;
            }
        }
    }
    for (int i = 0; i<36; i++)
    {
        for (int j=0;j<28;j++)
        {

            if (initial_map[i][j] <= 2 && initial_map[i+1][j] <= 2)
                count++;
        }
    }
    printf("Numero de arestas: %d", count);*/
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
    tex = loadTexture("images/Pac-Man-mapa-244-288.png");
    if (!tex)
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
    inicialize_graph (grafo);
    draw_coins(grafo);
    SDL_RenderPresent(renderer);
    //Event handler
    SDL_Event e;
    //While application is running
    while( !quit )
    {
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
        }
    }
    // clean up resources before exiting
    void quit_program();

    return 0;
}

