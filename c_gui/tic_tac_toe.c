#include <stdbool.h>
#include <stdlib.h>
#include "tic_tac_toe.h"

Game *create_game(unsigned int width, unsigned int height) {
    Game *game = (Game *)malloc(sizeof(Game));

    game->board = create_board(width, height);

    game->turn_index = 0;

    return game;
}

Board *create_board(unsigned int width, unsigned int height) {
    Board *board = (Board *)malloc(sizeof(Board));

    board->width = width;
    board->height = height;
    board->grid = (CellState **)malloc(sizeof(CellState *) * width);

    for (int i = 0; i < width; i++) {
        board->grid[i] = (CellState *)malloc(sizeof(CellState *) * height);

        for (int j = 0; j < height; j++) {
            board->grid[i][j] = EMPTY;
        }
    }

    return board;
}

void free_game(Game *game) {
    free_board(game->board);
    free(game);
}

void free_board(Board *board) {
    for (int i = 0; i < board->width; i++) {
        free(board->grid[i]);
    }

    free(board->grid);

    free(board);
}

// Return 0 on success
bool try_place(Game *game, unsigned int x, unsigned int y) {
    if (x < 0 || x >= game->board->width)
        return false;

    if (y < 0 || y >= game->board->height)
        return false;

    if (game->board->grid[x][y] != EMPTY)
        return false;

    // I don't know if try_place should handle this logic or take in parameter

    CellState token = game->turn_index % 2 == 0 ? X : O;

    game->board->grid[x][y] = token;

    return true;
}
