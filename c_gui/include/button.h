#ifndef BUTTON
#define BUTTON

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct {
    SDL_Texture *text_texture;
    SDL_Color color;
    unsigned int width;
    unsigned int height;
    int x;
    int y;
} Button;

bool collide_point(Button button, int x, int y);

void render_button(SDL_Renderer *renderer, Button button);

void free_button(Button *button);

Button *create_button(unsigned int width, unsigned int height, int center_x,
                      int center_y, SDL_Color button_color, SDL_Texture *text);
#endif
