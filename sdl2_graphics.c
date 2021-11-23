#include <stdio.h>
#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL_timer.h>
#include <SDL_image.h>
#include "graph.h"
#include "sdl2_graphics.h"

//0=caminho sem nada, 1=caminho com moeda, 2 = caminho com moed grande, 3 = parede, 4 = fora do mapa, 5 = porta da casa dos fantasmas
char initial_map[36][28] = {
    {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},//0
    {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},//1
    {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},//2
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},//3
    {3,1,1,1,1,1,1,1,1,1,1,1,1,3,3,1,1,1,1,1,1,1,1,1,1,1,1,3},//4
    {3,1,3,3,3,3,1,3,3,3,3,3,1,3,3,1,3,3,3,3,3,1,3,3,3,3,1,3},//5
    {3,2,3,3,3,3,1,3,3,3,3,3,1,3,3,1,3,3,3,3,3,1,3,3,3,3,2,3},//6
    {3,1,3,3,3,3,1,3,3,3,3,3,1,3,3,1,3,3,3,3,3,1,3,3,3,3,1,3},//7
    {3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},//8
    {3,1,3,3,3,3,1,3,3,1,3,3,3,3,3,3,3,3,1,3,3,1,3,3,3,3,1,3},//9
    {3,1,3,3,3,3,1,3,3,1,3,3,3,3,3,3,3,3,1,3,3,1,3,3,3,3,1,3},//10
    {3,1,1,1,1,1,1,3,3,1,1,1,1,3,3,1,1,1,1,3,3,1,1,1,1,1,1,3},//11
    {3,3,3,3,3,3,1,3,3,3,3,3,0,3,3,0,3,3,3,3,3,1,3,3,3,3,3,3},//12
    {4,4,4,4,4,3,1,3,3,3,3,3,0,3,3,0,3,3,3,3,3,1,3,4,4,4,4,4},//13
    {4,4,4,4,4,3,1,3,3,0,0,0,0,0,0,0,0,0,0,3,3,1,3,4,4,4,4,4},//14
    {4,4,4,4,4,3,1,3,3,0,3,3,3,5,3,3,3,3,0,3,3,1,3,4,4,4,4,4},
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
    {3,2,1,1,3,3,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,3,3,1,1,2,3},
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
//global window
SDL_Window* window = NULL;
//global texture
SDL_Texture* tex = NULL;

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
void drawSprite(SDL_Texture* tex, int num, float x, float y)
{
    int texturewidth, textureheight;
    SDL_QueryTexture(tex, NULL, NULL, &texturewidth, &textureheight);
    winRect.w = WIN_WIDTH/28;
    winRect.h = WIN_HEIGHT/36;
    switch (num)
    {
        case 0:
            return;
        //moeda pequena
        case 1:
            winRect.x = x*winRect.w;
            winRect.y = y*winRect.h;
            spriteRect.w = spriteRect.h = 8;
            spriteRect.x = 3*200+136;
            spriteRect.y = 186+19;
            break;
        //moeda grande
        case 2:
            winRect.x = x*winRect.w;
            winRect.y = y*winRect.h;
            spriteRect.w = spriteRect.h = 8;
            spriteRect.x = 3*200+136;
            spriteRect.y = 186+19+9;
            break;
        //Pacman
        case 5:
            winRect.x = x*winRect.w - winRect.w/2;
            winRect.y = y*winRect.h - winRect.h/2;
            winRect.w *= 2;
            winRect.h *= 2;
            spriteRect.w = spriteRect.h = 16;
            spriteRect.x = 200+200+103;
            spriteRect.y = 186+151;
            break;
        //blinky
        case 6:
            winRect.x = x*winRect.w - winRect.w/2;
            winRect.y = y*winRect.h - winRect.h/2;
            winRect.w *= 2;
            winRect.h *= 2;
            spriteRect.w = spriteRect.h = 16;
            spriteRect.x = 1;
            spriteRect.y = 83;
            break;
        //Pinky
        case 7:
            winRect.x = x*winRect.w - winRect.w/2;
            winRect.y = y*winRect.h - winRect.h/2;
            winRect.w *= 2;
            winRect.h *= 2;
            spriteRect.w = spriteRect.h = 16;
            spriteRect.x = 1+200;
            spriteRect.y = 83;
            break;
        //Inky
        case 8:
            winRect.x = x*winRect.w - winRect.w/2;
            winRect.y = y*winRect.h - winRect.h/2;
            winRect.w *= 2;
            winRect.h *= 2;
            spriteRect.w = spriteRect.h = 16;
            spriteRect.x = 1+200+200;
            spriteRect.y = 83;
            break;
        //Clyde
        case 9:
            winRect.x = x*winRect.w - winRect.w/2;
            winRect.y = y*winRect.h - winRect.h/2;
            winRect.w *= 2;
            winRect.h *= 2;
            spriteRect.w = spriteRect.h = 16;
            spriteRect.x = 1+200+200+200;
            spriteRect.y = 83;
            break;
    }
    // draw the image to the window
    SDL_RenderCopy(renderer, tex, &spriteRect, &winRect);
    //SDL_RenderPresent(renderer);
}

// Desenha as moedas no mapa de acordo com o grafo
void draw_coins(GrafoLA *grafo)
{
    for (int i = 0; i< grafo->numVertices; i++)
    {
        if(grafo->vertices[i].coin != 0)
            drawSprite(tex, grafo->vertices[i].coin, grafo->vertices[i].x, grafo->vertices[i].y);
    }
}
// clean up resources before exiting
void quit_program()
{
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);
    SDL_Quit();
}
