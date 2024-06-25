#include "utils.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

SDL_Texture *load_text(SDL_Renderer *renderer, char *text,
                               TTF_Font *font, SDL_Color text_color) {
    SDL_Surface *text_surface = TTF_RenderText_Blended(font, text, text_color);

    if (text_surface == NULL) {
        printf("Something went wrong while trying to laod text onto surface");
    }

    SDL_Texture *text_texture =
        SDL_CreateTextureFromSurface(renderer, text_surface);

    if (text_texture == NULL) {
        printf("Something went wrong while trying to load text onto texture");
    }

    SDL_FreeSurface(text_surface);

    return text_texture;
}
