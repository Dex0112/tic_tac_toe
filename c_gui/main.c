#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdio.h>

#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 720

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Tic-Tac-Toe", SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                                          WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    IMG_Init(IMG_INIT_PNG);

    SDL_Surface *board_surface = IMG_Load("./gfx/Board.png");
    SDL_Surface *x_surface = IMG_Load("./gfx/Cross.png");
    SDL_Surface *o_surface = IMG_Load("./gfx/Circle.png");

    SDL_Texture *board_texture =
        SDL_CreateTextureFromSurface(renderer, board_surface);
    SDL_Texture *x_texture = SDL_CreateTextureFromSurface(renderer, x_surface);
    SDL_Texture *o_texture = SDL_CreateTextureFromSurface(renderer, o_surface);

    SDL_FreeSurface(board_surface);
    SDL_FreeSurface(x_surface);
    SDL_FreeSurface(o_surface);

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

                printf("Click at (%d, %d)\n", x, y);

                printf("Grid Square: (%d, %d)\n", x / (WINDOW_WIDTH / 3),
                       y / (WINDOW_HEIGHT / 3));
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        SDL_Rect board_rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

        SDL_Rect x_rect = {0, 0, WINDOW_WIDTH / 3, WINDOW_HEIGHT / 3};
        SDL_Rect o_rect = {720 / 3, 720 / 3, WINDOW_WIDTH / 3, WINDOW_HEIGHT / 3};
        SDL_Rect x_rect1 = {720 / 3 * 2, 720 / 3 * 2, WINDOW_WIDTH / 3, WINDOW_HEIGHT / 3};

        SDL_RenderCopy(renderer, board_texture, NULL, &board_rect);
        SDL_RenderCopy(renderer, x_texture, NULL, &x_rect);
        SDL_RenderCopy(renderer, x_texture, NULL, &o_rect);
        SDL_RenderCopy(renderer, x_texture, NULL, &x_rect1);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    return 0;
}
