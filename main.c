#include <SDL.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <SDL_timer.h>
#include <SDL_image.h>
#include "graph.h"
#include "sdl2_graphics.h"
#include "game.h"




int main(int argc, char* argv[])
{
    srand(time(0));
    //Main loop flag
    bool quit = false;
    GrafoLA *grafo = criaGrafoLA(NUMVER);
    inicialize_graph (grafo);
    GrafoLA *grafoGhosts = criaGrafoLA(NUMVER);
    inicialize_graphGhosts (grafoGhosts);

    printf("grafo: %d ", buscaArestaGrafoLA(grafo, buscaNodoGrafoLA(grafo, 0, 17), buscaNodoGrafoLA(grafo, 27, 17)));
    printf("grafo: %d ", buscaArestaGrafoLA(grafoGhosts, buscaNodoGrafoLA(grafoGhosts, 0, 17), buscaNodoGrafoLA(grafoGhosts, 27, 17)));
    Pacman pacman;
    // inicializar pacman
    pacman.x_vel = -SPEED;
    pacman.y_vel = 0;
    pacman.x_pos = 13;
    pacman.y_pos = 26;
    pacman.graph_pos = buscaNodoGrafoLA(grafo, (int)pacman.x_pos, (int)pacman.y_pos);
    //inicializar ghosts
    Ghost blinky; //vermelho
    blinky.x_vel = -SPEED;
    blinky.y_vel = 0;
    blinky.x_pos = 13;
    blinky.y_pos = 14;
    blinky.flag = 0;
    blinky.graph_pos = buscaNodoGrafoLA(grafo, (int)blinky.x_pos, (int)blinky.y_pos);
    Ghost pinky; //Rosa
    pinky.x_vel = -SPEED;
    pinky.y_vel = 0;
    pinky.x_pos = 13;
    pinky.y_pos = 17;
    pinky.flag = 0;
    pinky.graph_pos = buscaNodoGrafoLA(grafo, (int)pinky.x_pos, (int)pinky.y_pos);
    Ghost inky; //azul
    inky.x_vel = -SPEED;
    inky.y_vel = 0;
    inky.x_pos = 11;
    inky.y_pos = 17;
    inky.flag = 0;
    inky.graph_pos = buscaNodoGrafoLA(grafo, (int)inky.x_pos, (int)inky.y_pos);
    Ghost clyde; //laranja
    clyde.x_vel = -SPEED;
    clyde.y_vel = 0;
    clyde.x_pos = 15;
    clyde.y_pos = 17;
    clyde.flag = 0;
    clyde.graph_pos = buscaNodoGrafoLA(grafo, (int)clyde.x_pos, (int)clyde.y_pos);
    //inicia winRect
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
    //Carrega textura do mapa
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

    //Carrega Sprites
    tex = loadTexture("images/pacman-all-sprites.png");
    if (!tex)
    {
        printf("error opening image\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_RenderPresent(renderer);


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
        else
            SDL_Delay(next_time-now);
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
            }
        }
        const Uint8* keystates = SDL_GetKeyboardState(NULL);
        if (keystates[SDL_SCANCODE_LEFT])
        {
            if (buscaArestaGrafoLA(grafo, pacman.graph_pos, buscaNodoGrafoLA(grafo, (int)pacman.x_pos-1, (int)pacman.y_pos)))
            {
                pacman.x_vel = -SPEED;
                pacman.y_vel = 0;
            }
        }
        if (keystates[SDL_SCANCODE_RIGHT])
        {
            if (buscaArestaGrafoLA(grafo, pacman.graph_pos, buscaNodoGrafoLA(grafo, (int)pacman.x_pos+1, (int)pacman.y_pos)))
            {
                pacman.x_vel = SPEED;
                pacman.y_vel = 0;
            }
        }
        if (keystates[SDL_SCANCODE_UP])
        {
            if (buscaArestaGrafoLA(grafo, pacman.graph_pos, buscaNodoGrafoLA(grafo, (int)pacman.x_pos, (int)pacman.y_pos-1)))
            {
                pacman.x_vel = 0;
                pacman.y_vel = -SPEED;
            }
        }
        if (keystates[SDL_SCANCODE_DOWN])
        {
            if (buscaArestaGrafoLA(grafo, pacman.graph_pos, buscaNodoGrafoLA(grafo, (int)pacman.x_pos, (int)pacman.y_pos+1)))
            {
                pacman.x_vel = 0;
                pacman.y_vel = SPEED;
            }
        }
        pacman.graph_pos = buscaNodoGrafoLA(grafo, (int)pacman.x_pos, (int)pacman.y_pos); //Atualiza qual nodo do grafo o pacman está
        blinky.graph_pos = buscaNodoGrafoLA(grafoGhosts, (int)blinky.x_pos, (int)blinky.y_pos);
        pinky.graph_pos = buscaNodoGrafoLA(grafoGhosts, (int)pinky.x_pos, (int)pinky.y_pos);
        inky.graph_pos = buscaNodoGrafoLA(grafoGhosts, (int)inky.x_pos, (int)inky.y_pos);
        clyde.graph_pos = buscaNodoGrafoLA(grafoGhosts, (int)clyde.x_pos, (int)clyde.y_pos);
        // clear the window
        SDL_RenderClear(renderer);
        // draw the image to the window
        SDL_RenderCopy(renderer, tex2, NULL, NULL); // Desenha o mapa

        draw_coins(grafo);
        //Movimento do Pacman:
        movimento_pacman(grafo, &pacman);
        movimento_fantasma(grafoGhosts, &blinky);
        movimento_fantasma(grafoGhosts, &pinky);
        movimento_fantasma(grafoGhosts, &inky);
        movimento_fantasma(grafoGhosts, &clyde);
        if (grafo->vertices[pacman.graph_pos].coin == 1 || grafo->vertices[pacman.graph_pos].coin == 2)
            grafo->vertices[pacman.graph_pos].coin = 0;
        drawSprite(tex, 5, (int) pacman.x_pos, (int) pacman.y_pos);
        drawSprite(tex, 6, (int) blinky.x_pos, (int) blinky.y_pos);
        drawSprite(tex, 7, (int) pinky.x_pos, (int) pinky.y_pos);
        drawSprite(tex, 8, (int) inky.x_pos, (int) inky.y_pos);
        drawSprite(tex, 9, (int) clyde.x_pos, (int) clyde.y_pos);
        SDL_RenderPresent(renderer);
    }
    // clean up resources before exiting
    SDL_DestroyTexture(tex2); //destroi textura do mapa
    quit_program();

    return 0;
}

