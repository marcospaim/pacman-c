#ifndef SDL2_GRAPHICS_H_INCLUDED
#define SDL2_GRAPHICS_H_INCLUDED
#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_image.h>

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

SDL_Texture* loadTexture(char *str);

void drawSprite(SDL_Texture* tex, int num, float x, float y);

// clean up resources before exiting
void quit_program();

// Desenha as moedas no mapa de acordo com o grafo
void draw_coins(GrafoLA *grafo);

#endif // SDL2_GRAPHICS_H_INCLUDED
