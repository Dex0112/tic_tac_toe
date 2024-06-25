#include "button.h"
#include "constants.h"
#include "state.h"
#include "tic_tac_toe.h"
#include "utils.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct {
    Button *replay_button;
    Button *quit_button;
    SDL_Rect background_rect;
    SDL_Rect foreground_rect;
    SDL_Color background_color;
    SDL_Color foreground_color;
    SDL_Texture *result_text;
    SDL_Rect result_rect;
} GameOverPanel;

void grid_to_pixel_coords(unsigned int width, unsigned int height, int *x,
                          int *y) {
    *x *= WINDOW_WIDTH / width;
    *y *= WINDOW_HEIGHT / height;
}

void pixel_to_grid_coords(unsigned int width, unsigned int height, int *x,
                          int *y) {
    *x /= WINDOW_WIDTH / width;
    *y /= WINDOW_HEIGHT / height;
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

void render_panel(SDL_Renderer *renderer, GameOverPanel panel) {
    SDL_SetRenderDrawColor(renderer, panel.background_color.r,
                           panel.background_color.b, panel.background_color.g,
                           panel.background_color.a);

    SDL_RenderFillRect(renderer, &panel.background_rect);

    SDL_SetRenderDrawColor(renderer, panel.foreground_color.r,
                           panel.foreground_color.b, panel.foreground_color.g,
                           panel.foreground_color.a);

    SDL_RenderFillRect(renderer, &panel.foreground_rect);

    SDL_RenderCopy(renderer, panel.result_text, NULL, &panel.result_rect);

    render_button(renderer, *panel.replay_button);
    render_button(renderer, *panel.quit_button);
}

State game(SDL_Renderer *renderer) {
    bool running = true;
    bool game_over = false;
    State next_state = QUIT;

    SDL_Event event;

    SDL_Texture *board_texture = load_texture(renderer, "./gfx/Board.png");
    SDL_Texture *x_texture = load_texture(renderer, "./gfx/Cross.png");
    SDL_Texture *o_texture = load_texture(renderer, "./gfx/Circle.png");

    TTF_Font *regular_font =
        TTF_OpenFont("/usr/share/fonts/gnu-free/FreeSansBold.otf", 28);

    TTF_Font *large_font =
        TTF_OpenFont("/usr/share/fonts/gnu-free/FreeSansBold.otf", 42);

    SDL_Color button_color = {0, 0, 0, 255};
    SDL_Color text_color = {255, 255, 255, 255};
    SDL_Color result_text_color = {0, 0, 0, 0};
    SDL_Color panel_background_color = {230, 230, 230, 255};
    SDL_Color panel_foreground_color = {200, 200, 200, 255};

    SDL_Texture *restart_text =
        load_text(renderer, "Restart", regular_font, text_color);
    Button *restart_button = create_button(
        125, 50, WINDOW_CENTER_X, WINDOW_CENTER_Y, button_color, restart_text);

    SDL_Texture *quit_text =
        load_text(renderer, "Quit", regular_font, text_color);
    Button *quit_button =
        create_button(100, 50, WINDOW_CENTER_X, WINDOW_CENTER_Y + 60,
                      button_color, quit_text);

    SDL_Rect foreground_rect = {WINDOW_CENTER_X, WINDOW_CENTER_Y, 475, 475};
    SDL_Rect background_rect = {WINDOW_CENTER_X, WINDOW_CENTER_Y, 500, 500};

    foreground_rect.x -= foreground_rect.w / 2;
    background_rect.x -= background_rect.w / 2;

    foreground_rect.y -= foreground_rect.h / 2;
    background_rect.y -= background_rect.h / 2;

    // TODO: I need to compute the correct position and size for the panel rects
    GameOverPanel panel = {restart_button,         quit_button,
                           background_rect,        foreground_rect,
                           panel_background_color, panel_foreground_color};

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
                if (game_over)
                    continue;

                if (event.button.button != SDL_BUTTON_LEFT)
                    continue;

                int x, y;

                SDL_GetMouseState(&x, &y);

                pixel_to_grid_coords(board->width, board->height, &x, &y);

                if (try_place(game, x, y)) {
                    GAME_RESULT result =
                        has_result(game, game->turn_index % 2 == 0 ? X : O);

                    if (result != NONE) {
                        game_over = true;

                        char *text;

                        switch (result) {
                        case WIN:
                            text = game->turn_index % 2 == 0 ? "X Wins!"
                                                             : "O Wins!";
                            break;
                        case DRAW:
                            text = "Draw!";
                            break;
                        default:
                            printf("Unrecognized game result");
                            break;
                        }

                        panel.result_text = load_text(
                            renderer, text, large_font, result_text_color);

                        SDL_Rect text_rect = {WINDOW_CENTER_X,
                                              WINDOW_CENTER_Y - 60, 0, 0};
                        SDL_QueryTexture(panel.result_text, NULL, NULL,
                                         &text_rect.w, &text_rect.h);

                        text_rect.x -= text_rect.w / 2;
                        text_rect.y -= text_rect.h / 2;

                        panel.result_rect = text_rect;

                        continue;
                    }

                    game->turn_index++;
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

        if (game_over)
            render_panel(renderer, panel);

        SDL_RenderPresent(renderer);

        SDL_Delay(10);
    }

    free_game(game);

    SDL_DestroyTexture(board_texture);
    SDL_DestroyTexture(x_texture);
    SDL_DestroyTexture(o_texture);

    free_button(restart_button);
    free_button(quit_button);

    TTF_CloseFont(regular_font);

    return QUIT;
}
