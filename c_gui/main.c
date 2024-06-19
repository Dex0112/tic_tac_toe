#include "button.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>

#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 720

SDL_Texture *load_text_texture(SDL_Renderer *renderer, char *text,
                               TTF_Font *font, SDL_Color text_color) {
    SDL_Surface *text_surface = TTF_RenderText_Blended(font, text, text_color);

    SDL_Texture *text_texture =
        SDL_CreateTextureFromSurface(renderer, text_surface);

    SDL_FreeSurface(text_surface);

    return text_texture;
}

SDL_Texture *load_texture(SDL_Renderer *renderer, char *path) {
    SDL_Surface *loaded_surface = IMG_Load(path);

    SDL_Texture *loaded_texture =
        SDL_CreateTextureFromSurface(renderer, loaded_surface);

    SDL_FreeSurface(loaded_surface);

    return loaded_texture;
}

// Setup(SDL_Window **window, **renderer, **font) just like returns all the
// necessary bits

int main() {
    TTF_Init();
    TTF_Font *font =
        TTF_OpenFont("/usr/share/fonts/gnu-free/FreeSansBold.otf", 42);

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Tic-Tac-Toe", SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                                          WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    IMG_Init(IMG_INIT_PNG);

    SDL_Color text_color = {255, 255, 255};
    SDL_Color button_color = {0, 0, 0, 255};
    SDL_Texture *message_texture =
        load_text_texture(renderer, "Text", font, text_color);

    Button *button =
        create_button(100, 60, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, button_color, message_texture);

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                continue;
            }

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                // Check for specifically left click
                if (event.button.button != SDL_BUTTON_LEFT) {
                    continue;
                }

                int x, y;

                SDL_GetMouseState(&x, &y);
                if(collide_point(*button, x, y)) {
                    printf("Button was clicked!\n");
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        render_button(renderer, *button);

        SDL_RenderPresent(renderer);

        // Set ticking speed
        SDL_Delay(10);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_DestroyTexture(message_texture);

    free_button(button);

    TTF_CloseFont(font);
    TTF_Quit();

    printf("Goodbye\n");

    return 0;
}
