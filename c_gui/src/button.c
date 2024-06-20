#include "button.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>

bool collide_point(Button button, int x, int y) {
    if (x < button.x || x > button.x + button.width) {
        return false;
    }

    if (y < button.y || y > button.y + button.height) {
        return false;
    }

    return true;
}

void render_button(SDL_Renderer *renderer, Button button) {
    SDL_SetRenderDrawColor(renderer, button.color.r, button.color.g,
                           button.color.b, button.color.a);
    SDL_Rect background_rect = {button.x, button.y, button.width,
                                button.height};
    SDL_RenderFillRect(renderer, &background_rect);

    SDL_Rect text_rect = {background_rect.x, background_rect.y, 0, 0};
    SDL_QueryTexture(button.text_texture, NULL, NULL, &text_rect.w,
                     &text_rect.h);

    text_rect.x += (background_rect.w - text_rect.w) / 2;
    text_rect.y += (background_rect.h - text_rect.h) / 2;

    SDL_RenderCopy(renderer, button.text_texture, NULL, &text_rect);
}

void free_button(Button *button) {
    SDL_DestroyTexture(button->text_texture);
    free(button);
}

// Remove text rendering stuff
Button *create_button(unsigned int width, unsigned int height, int center_x,
                      int center_y, SDL_Color button_color, SDL_Texture *text) {

    Button *button = (Button *)malloc(sizeof(Button));

    button->width = width;
    button->height = height;
    button->x = center_x - width / 2;
    button->y = center_y - height / 2;
    button->color = button_color;
    button->text_texture = text;

    return button;
}
