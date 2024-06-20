#include "main_menu.h"
#include "constants.h"
#include "game.h"
#include "state.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>

// I do not really know where to put this
int main() {
    TTF_Init();

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window *window = SDL_CreateWindow("Tic-Tac-Toe", SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                                          WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


    State current_state = MAIN_MENU;

    while(current_state != QUIT) {
        switch (current_state) {
            case GAME:
                current_state = game(renderer);
                break;
            case MAIN_MENU:
                current_state = main_menu(renderer);
                break;
            default:
                fprintf(stderr, "Unknown state reached!");
                current_state = QUIT;
                break;
        }
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);


    TTF_Quit();

    SDL_Quit();

    printf("Goodbye\n");

    return 0;
}
