#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL_timer.h>
#include <SDL_image.h>
//0=caminho sem nada, 1=caminho com moeda, 2 = caminho com moed grande, 3 = parede, 4 = fora do mapa
char initial_map[36][28] = {
    {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
    {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
    {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
    {3,1,1,1,1,1,1,1,1,1,1,1,1,3,3,1,1,1,1,1,1,1,1,1,1,1,1,3},
    {3,1,3,3,3,3,1,3,3,3,3,3,1,3,3,1,3,3,3,3,3,1,3,3,3,3,1,3},
    {3,2,3,3,3,3,1,3,3,3,3,3,1,3,3,1,3,3,3,3,3,1,3,3,3,3,2,3},
    {3,1,3,3,3,3,1,3,3,3,3,3,1,3,3,1,3,3,3,3,3,1,3,3,3,3,1,3},
    {3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
    {3,1,3,3,3,3,1,3,3,1,3,3,3,3,3,3,3,3,1,3,3,1,3,3,3,3,1,3},
    {3,1,3,3,3,3,1,3,3,1,3,3,3,3,3,3,3,3,1,3,3,1,3,3,3,3,1,3},
    {3,1,1,1,1,1,1,3,3,1,1,1,1,3,3,1,1,1,1,3,3,1,1,1,1,1,1,3},
    {3,3,3,3,3,3,1,3,3,3,3,3,0,3,3,0,3,3,3,3,3,1,3,3,3,3,3,3},
    {4,4,4,4,4,3,1,3,3,3,3,3,0,3,3,0,3,3,3,3,3,1,3,4,4,4,4,4},
    {4,4,4,4,4,3,1,3,3,0,0,0,0,0,0,0,0,0,0,3,3,1,3,4,4,4,4,4},
    {4,4,4,4,4,3,1,3,3,0,3,3,3,0,0,3,3,3,0,3,3,1,3,4,4,4,4,4},
    {3,3,3,3,3,3,1,3,3,0,3,0,0,0,0,0,0,3,0,3,3,1,3,3,3,3,3,3},
    {0,0,0,0,0,0,1,0,0,0,3,0,0,0,0,0,0,3,0,0,0,1,0,0,0,0,0,0},
    {3,3,3,3,3,3,1,3,3,0,3,0,0,0,0,0,0,3,0,3,3,1,3,3,3,3,3,3},
    {4,4,4,4,4,3,1,3,3,0,3,3,3,3,3,3,3,3,0,3,3,1,3,4,4,4,4,4},
    {4,4,4,4,4,3,1,3,3,0,0,0,0,0,0,0,0,0,0,3,3,1,3,4,4,4,4,4},
    {4,4,4,4,4,3,1,3,3,0,3,3,3,3,3,3,3,3,0,3,3,1,3,4,4,4,4,4},
    {3,3,3,3,3,3,1,3,3,0,3,3,3,3,3,3,3,3,0,3,3,1,3,3,3,3,3,3},
    {3,1,1,1,1,1,1,1,1,1,1,1,1,3,3,1,1,1,1,1,1,1,1,1,1,1,1,3},
    {3,1,3,3,3,3,1,3,3,3,3,3,1,3,3,1,3,3,3,3,3,1,3,3,3,3,1,3},
    {3,1,3,3,3,3,1,3,3,3,3,3,1,3,3,1,3,3,3,3,3,1,3,3,3,3,1,3},
    {3,2,1,1,3,3,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,3,3,1,1,2,1},
    {3,3,3,1,3,3,1,3,3,1,3,3,3,3,3,3,3,3,1,3,3,1,3,3,1,3,3,3},
    {3,3,3,1,3,3,1,3,3,1,3,3,3,3,3,3,3,3,1,3,3,1,3,3,1,3,3,3},
    {3,1,1,1,1,1,1,3,3,1,1,1,1,3,3,1,1,1,1,3,3,1,1,1,1,1,1,3},
    {3,1,3,3,3,3,3,3,3,3,3,3,1,3,3,1,3,3,3,3,3,3,3,3,3,3,1,3},
    {3,1,3,3,3,3,3,3,3,3,3,3,1,3,3,1,3,3,3,3,3,3,3,3,3,3,1,3},
    {3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
    {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
    {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
    };

// Global renderer:
SDL_Renderer* renderer = NULL;
// functions:
SDL_Texture* loadTexture(char *str);

int main(int argc, char* argv[])
{
    //Main loop flag
    bool quit = false;


    //initialize sdl
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    printf("sucesso!\n");
    // Create game window
    SDL_Window* window =  SDL_CreateWindow("Pacman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 448, 576, 0);
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

    SDL_Texture* tex = loadTexture("images/Pac-Man-mapa-244-288.png");
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
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

SDL_Texture* loadTexture(char *str)
{
    SDL_Texture* tex = NULL;
    // load the image into memory using SDL_image library function
    SDL_Surface* surface = IMG_Load(str);
    if (!surface)
    {
        printf("error creating surface\n");
    }
    else
    {
        // load the image data into the graphics hardware's memory
        tex = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        if (!tex)
        {
            printf("error creating texture: %s\n", SDL_GetError());
        }
    }
    return tex;
}
