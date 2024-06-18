#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdio.h>

#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 720

// For buttons I guess
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
        TTF_OpenFont("/usr/share/fonts/gsfonts/NimbusRoman-Italic.otf", 42);

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Tic-Tac-Toe", SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                                          WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Color white = {255, 255, 255};

    SDL_Surface *message_surface = TTF_RenderText_Blended(font, "Test", white);

    SDL_Texture *message_texture = SDL_CreateTextureFromSurface(renderer, message_surface);

    SDL_FreeSurface(message_surface);

    IMG_Init(IMG_INIT_PNG);

    SDL_Texture *board_texture = load_texture(renderer, "./gfx/Board.png");
    SDL_Texture *x_texture = load_texture(renderer, "./gfx/Cross.png");
    SDL_Texture *o_texture = load_texture(renderer, "./gfx/Circle.png");

    bool running = true;
    SDL_Event event;

    int grid[3][3] = {{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}};

    int turn_index = 0;

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

                x /= WINDOW_WIDTH / 3;
                y /= WINDOW_HEIGHT / 3;

                grid[x][y] = turn_index;

                turn_index = 1 - turn_index;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        SDL_Rect board_rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

        SDL_RenderCopy(renderer, board_texture, NULL, &board_rect);

        SDL_Rect rect = {50, 50, 100, 60};
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);

        SDL_Rect message_rect = {rect.x, rect.y, 76, 44};
        SDL_QueryTexture(message_texture, NULL, NULL, &message_rect.w, &message_rect.h);
        message_rect.x += (rect.w - message_rect.w) / 2;
        message_rect.y += (rect.h - message_rect.h) / 2;

        SDL_RenderCopy(renderer, message_texture, NULL, &message_rect);

        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                if (grid[x][y] == -1) {
                    continue;
                }

                int new_x = x * WINDOW_WIDTH / 3;
                int new_y = y * WINDOW_HEIGHT / 3;

                SDL_Rect token_rect = {
                    new_x,
                    new_y,
                    WINDOW_WIDTH / 3,
                    WINDOW_HEIGHT / 3,
                };

                SDL_Texture *texture = grid[x][y] == 0 ? x_texture : o_texture;

                SDL_RenderCopy(renderer, texture, NULL, &token_rect);
            }
        }

        SDL_RenderPresent(renderer);
        // Set ticking speed
        SDL_Delay(10);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_DestroyTexture(message_texture);
    SDL_DestroyTexture(board_texture);
    SDL_DestroyTexture(o_texture);
    SDL_DestroyTexture(x_texture);

    TTF_CloseFont(font);

    printf("Goodbye\n");

    return 0;
}
