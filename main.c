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
    Game game;
    //Main loop flag
    bool quit = false;
    GrafoLA *grafo = criaGrafoLA(NUMVER);
    inicialize_graph (grafo);
    GrafoLA *grafoGhosts = criaGrafoLA(NUMVER);
    inicialize_graphGhosts (grafoGhosts);

    Pacman pacman;

    //inicializar ghosts
    Ghost blinky; //vermelho

    Ghost pinky; //Rosa

    Ghost inky; //azul

    Ghost clyde; //laranja

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
    game.frightened = 0;
    game.run = false;
    game.last_game = 0;
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
                case SDL_KEYDOWN:
                    if (game.run == false)
                    {
                        inicialize_graph (grafo);
                        initialize_game (&game, &blinky, &pinky, &inky, &clyde, &pacman);
                    }

                    game.run = true;
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
        if (!game.run)
        {
           write(tex, "press any button to start", 0, 0);
           if (game.last_game)
           {
                if (game.last_game == 1)
                    write(tex, "you won", 10, 16);
                else
                    write(tex, "game over", 10, 16);
           }
        }
        if (game.run)
        {
            draw_coins(grafo);
            //Movimento do Pacman:
            movimento_pacman(grafo, &pacman);
            //Movimento fantasmas:
            if (blinky.returning == 0)
                movimento_fantasma(grafoGhosts, &blinky);
            else
                retorno_fantasma(grafoGhosts, &blinky);
            if (pinky.returning == 0)
                movimento_fantasma(grafoGhosts, &pinky);
            else
                retorno_fantasma(grafoGhosts, &pinky);
            if (inky.returning == 0)
                movimento_fantasma(grafoGhosts, &inky);
            else
                retorno_fantasma(grafoGhosts, &inky);
            if (clyde.returning == 0)
                movimento_fantasma(grafoGhosts, &clyde);
            else
                retorno_fantasma(grafoGhosts, &clyde);
            // Checa se pacman comeu moeda grande
            if (grafo->vertices[pacman.graph_pos].coin == 2)
            {
                game.frightened = true;
                game.frightened_time = SDL_GetTicks();
            }
            if ((SDL_GetTicks() - game.frightened_time > 6000))
                game.frightened = false;
            // Checa se pacman comeu alguma moeda
            if (grafo->vertices[pacman.graph_pos].coin == 1 || grafo->vertices[pacman.graph_pos].coin == 2)
            {
                grafo->vertices[pacman.graph_pos].coin = 0;
                pacman.coins++;
            }
            if (game.frightened)
            {
                if (pacman.graph_pos == blinky.graph_pos && blinky.returning == 0)
                    retorno_fantasma(grafoGhosts, &blinky);
                if (pacman.graph_pos == pinky.graph_pos && pinky.returning == 0)
                    retorno_fantasma(grafoGhosts, &pinky);
                if (pacman.graph_pos == inky.graph_pos && inky.returning == 0)
                    retorno_fantasma(grafoGhosts, &inky);
                if (pacman.graph_pos == clyde.graph_pos && clyde.returning == 0)
                    retorno_fantasma(grafoGhosts, &clyde);
            }
            else //Checa se o pacman se chocou com algum fantasma
            {
                if (pacman.graph_pos == blinky.graph_pos)
                    pacman.lives--;
                if (pacman.graph_pos == pinky.graph_pos)
                    pacman.lives--;
                if (pacman.graph_pos == inky.graph_pos)
                    pacman.lives--;
                if (pacman.graph_pos == clyde.graph_pos)
                    pacman.lives--;
            }
            if (pacman.lives < 1)
            {
                game.last_game = 2;
                game.run = false;
            }
            else if (pacman.coins == COINS)
            {
                game.last_game = 1;
                game.run = false;
            }
            drawSprite(tex, 5, (int) pacman.x_pos, (int) pacman.y_pos, NULL, &game);
            drawSprite(tex, 6, (int) blinky.x_pos, (int) blinky.y_pos, &blinky, &game);
            drawSprite(tex, 7, (int) pinky.x_pos, (int) pinky.y_pos, &pinky, &game);
            drawSprite(tex, 8, (int) inky.x_pos, (int) inky.y_pos, &inky, &game);
            drawSprite(tex, 9, (int) clyde.x_pos, (int) clyde.y_pos, &clyde, &game);

        }


        SDL_RenderPresent(renderer);
    }
    // clean up resources before exiting
    SDL_DestroyTexture(tex2); //destroi textura do mapa
    quit_program();

    return 0;
}

