#include <stdio.h>
#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL_timer.h>
#include <SDL_image.h>
#include "graph.h"
#include "sdl2_graphics.h"
#include "game.h"

//matrix to inicialize graph
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

//load texture from image
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
//Write text on game window
void write(SDL_Texture* tex, char* text, int x, int y)
{
    winRect.w = WIN_WIDTH/28;
    winRect.h = WIN_HEIGHT/36;
    spriteRect.w = spriteRect.h = 8;
    char *t;
    int i = 0;
    for (t = text; *t != '\0'; t++)
    {
        if (*t >= 'a' && *t <= 'm')
        {
            winRect.x = i*winRect.w + x*winRect.w;
            winRect.y = 0 + y*winRect.h;
            spriteRect.y = 28;
            spriteRect.x = 201 + (*t-'a')*9;
            // draw the image to the window
            SDL_RenderCopy(renderer, tex, &spriteRect, &winRect);
        }
        else if(*t >= 'n' && *t <= 'z')
        {
            winRect.x = i*winRect.w + x*winRect.w;
            winRect.y = 0 + y*winRect.h;
            spriteRect.y = 37;
            spriteRect.x = 201 + (*t-'n')*9;
            // draw the image to the window
            SDL_RenderCopy(renderer, tex, &spriteRect, &winRect);
        }
        i++;
    }
}

//draw sprites
void drawSprite(SDL_Texture* tex, int num, float x, float y, Ghost *fantasma, Game *game)
{
    int texturewidth, textureheight;
    SDL_QueryTexture(tex, NULL, NULL, &texturewidth, &textureheight);
    winRect.w = WIN_WIDTH/28;
    winRect.h = WIN_HEIGHT/36;
    switch (num)
    {
        case 0:
            return;
        //small dot
        case 1:
            winRect.x = x*winRect.w;
            winRect.y = y*winRect.h;
            spriteRect.w = spriteRect.h = 8;
            spriteRect.x = 3*200+136;
            spriteRect.y = 186+19;
            break;
        //big dot
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
            if (game->frightened == true || fantasma->returning == 1)
            {
                spriteRect.x = 201;
                spriteRect.y = 168;
            }
            else
            {
                spriteRect.x = 1;
                spriteRect.y = 83;
            }
            break;
        //Pinky
        case 7:
            winRect.x = x*winRect.w - winRect.w/2;
            winRect.y = y*winRect.h - winRect.h/2;
            winRect.w *= 2;
            winRect.h *= 2;
            spriteRect.w = spriteRect.h = 16;
            if (game->frightened == true || fantasma->returning == 1)
            {
                spriteRect.x = 201;
                spriteRect.y = 168;
            }
            else
            {
                spriteRect.x = 1+200;
                spriteRect.y = 83;
            }
            break;
        //Inky
        case 8:
            winRect.x = x*winRect.w - winRect.w/2;
            winRect.y = y*winRect.h - winRect.h/2;
            winRect.w *= 2;
            winRect.h *= 2;
            spriteRect.w = spriteRect.h = 16;
            if (game->frightened == true || fantasma->returning == 1)
            {
                spriteRect.x = 201;
                spriteRect.y = 168;
            }
            else
            {
                spriteRect.x = 1+200+200;
                spriteRect.y = 83;
            }

            break;
        //Clyde
        case 9:
            winRect.x = x*winRect.w - winRect.w/2;
            winRect.y = y*winRect.h - winRect.h/2;
            winRect.w *= 2;
            winRect.h *= 2;
            spriteRect.w = spriteRect.h = 16;
            if (game->frightened == true || fantasma->returning == 1)
            {
                spriteRect.x = 201;
                spriteRect.y = 168;
            }
            else
            {
                spriteRect.x = 1+200+200+200;
                spriteRect.y = 83;
            }
            break;
    }
    // draw the image to the window
    SDL_RenderCopy(renderer, tex, &spriteRect, &winRect);
    //SDL_RenderPresent(renderer);
}

// Draw coins on map
void draw_coins(GrafoLA *graph)
{
    for (int i = 0; i< graph->numVertices; i++)
    {
        if(graph->vertices[i].coin != 0)
            drawSprite(tex, graph->vertices[i].coin, graph->vertices[i].x, graph->vertices[i].y, NULL, NULL);
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
