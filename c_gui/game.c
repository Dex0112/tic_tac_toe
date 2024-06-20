#include "constants.h"
#include "state.h"
#include "tic_tac_toe.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <stdbool.h>
#include <stdio.h>

void grid_to_pixel_coords(unsigned int width, unsigned int height, int *x,
                          int *y) {
    *x *= (WINDOW_WIDTH / width);
    *y *= (WINDOW_HEIGHT / height);
}

void pixel_to_grid_coords(unsigned int width, unsigned int height, int *x,
                          int *y) {
    *x /= (WINDOW_WIDTH / width);
    *y /= (WINDOW_HEIGHT / height);
}

// When working return void * instead
// return null on quit
SDL_Texture *load_texture(SDL_Renderer *renderer, char *path) {
    SDL_Surface *loaded_surface = IMG_Load(path);

    SDL_Texture *loaded_texture =
        SDL_CreateTextureFromSurface(renderer, loaded_surface);

    SDL_FreeSurface(loaded_surface);

    return loaded_texture;
}

State game(SDL_Renderer *renderer) {
    bool running = true;
    State next_state = QUIT;

    SDL_Event event;

    SDL_Texture *board_texture = load_texture(renderer, "./gfx/Board.png");
    SDL_Texture *x_texture = load_texture(renderer, "./gfx/Cross.png");
    SDL_Texture *o_texture = load_texture(renderer, "./gfx/Circle.png");

    Game *game = create_game(3, 3);
    Board *board = game->board;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                next_state = QUIT;

                continue;
            }

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button != SDL_BUTTON_LEFT)
                    continue;

                int x, y;

                SDL_GetMouseState(&x, &y);

                pixel_to_grid_coords(board->width, board->height, &x, &y);

                if (try_place(game, x, y)) {
                    game->turn_index++;
                    // Check if draw or win
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        SDL_Rect board_rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
        SDL_RenderCopy(renderer, board_texture, NULL, &board_rect);

        for (int i = 0; i < board->width; i++) {
            for (int j = 0; j < board->height; j++) {
                CellState cell = board->grid[i][j];
                if (cell == EMPTY)
                    continue;

                SDL_Texture *token_texture = cell == X ? x_texture : o_texture;

                int x = i, y = j;

                grid_to_pixel_coords(board->width, board->height, &x, &y);

                SDL_Rect token_rect = {x, y, WINDOW_WIDTH / board->width,
                                       WINDOW_HEIGHT / board->height};

                SDL_RenderCopy(renderer, token_texture, NULL, &token_rect);
            }
        }

        SDL_RenderPresent(renderer);

        SDL_Delay(10);
    }

    free_game(game);

    SDL_DestroyTexture(board_texture);
    SDL_DestroyTexture(x_texture);
    SDL_DestroyTexture(o_texture);

    return QUIT;
}
