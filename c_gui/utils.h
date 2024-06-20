#ifndef UTILS
#define UTILS

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

SDL_Texture *load_text(SDL_Renderer *renderer, char *text,
                               TTF_Font *font, SDL_Color text_color);

#endif
