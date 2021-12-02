#ifndef SDL2_GRAPHICS_H_INCLUDED
#define SDL2_GRAPHICS_H_INCLUDED
#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_image.h>
#include "game.h"

#define WIN_WIDTH 448
#define WIN_HEIGHT 576


extern char initial_map[36][28];
    // Global renderer:
extern SDL_Renderer* renderer;
//global window
extern SDL_Window* window;
//global texture
extern SDL_Texture* tex;

SDL_Rect winRect;
SDL_Rect spriteRect;

//load texture from image
SDL_Texture* loadTexture(char *str);

//draw sprites
void drawSprite(SDL_Texture* tex, int num, float x, float y, Ghost *fantasma, Game *game);

// clean up resources before exiting
void quit_program();

// Draw coins on map
void draw_coins(GrafoLA *graph);

//Write text on game window
void write(SDL_Texture* tex, char* text, int x, int y);

#endif // SDL2_GRAPHICS_H_INCLUDED
