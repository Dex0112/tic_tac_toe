#include "main_menu.h"
#include "state.h"
#include "button.h"
#include "utils.h"
#include "constants.h"
#include <SDL2/SDL_render.h>
#include <stdio.h>

State main_menu(SDL_Renderer *renderer) {
    State next_state = QUIT;

    TTF_Font *font =
        TTF_OpenFont("/usr/share/fonts/gnu-free/FreeSansBold.otf", 28);

    SDL_Color text_color = {255, 255, 255};
    SDL_Color button_color = {0, 0, 0, 255};

    SDL_Texture *start_text = load_text(renderer, "Start", font, text_color);
    SDL_Texture *quit_text = load_text(renderer, "Quit", font, text_color);

    Button *start_button =
        create_button(125, 50, WINDOW_CENTER_X, WINDOW_CENTER_Y - 30,
                      button_color, start_text);

    Button *quit_button =
        create_button(100, 50, WINDOW_CENTER_X, WINDOW_CENTER_Y + 30,
                      button_color, quit_text);

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                next_state = QUIT;
                continue;
            }

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button != SDL_BUTTON_LEFT) {
                    continue;
                }

                int x, y;

                SDL_GetMouseState(&x, &y);
                if (collide_point(*start_button, x, y)) {
                    running = false;
                    next_state = GAME;
                }

                if (collide_point(*quit_button, x, y)) {
                    running = false;
                    next_state = QUIT;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        render_button(renderer, *start_button);
        render_button(renderer, *quit_button);

        SDL_RenderPresent(renderer);

        // Set ticking speed
        SDL_Delay(10);
    }

    free_button(start_button);
    free_button(quit_button);

    TTF_CloseFont(font);

    return next_state;
}
