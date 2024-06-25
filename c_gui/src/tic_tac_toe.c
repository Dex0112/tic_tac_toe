#include "tic_tac_toe.h"
#include <stdbool.h>
#include <stdlib.h>

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

GAME_RESULT has_result(Game *game, CellState target) {
    typedef struct {
        int x;
        int y;
    } Vector;

    // Implement the algorithm used in the python_gui project

    Board *board = game->board;

    // dirs = [(1, 0), (0, 1), (1, 1), (-1, 1)]

    Vector dirs[] = {
        {1, 0},
        {0, 1},
        {1, 1},
        {-1, 1},
    };

    for (int i = 0; i < board->width; i++) {
        for (int j = 0; j < board->height; j++) {
            // set pivot and look around
            if (board->grid[i][j] != target) {
                continue;
            }

            Vector pivot = {i, j};

            for (int idx = 0; idx < sizeof(dirs) / sizeof(dirs[0]); idx++) {
                // Algorithm
                int count = 1;
                int x = pivot.x + dirs[idx].x, y = pivot.y + dirs[idx].y;

                while (x < board->width && y < board->height && x >= 0 &&
                       y >= 0 && board->grid[x][y] == target) {
                    count++;

                    // Add this winning number to the game struct I've decided
                    if (count >= 3) {
                        return WIN;
                    }

                    x += dirs[idx].x;
                    y += dirs[idx].y;
                }
            }
        }
    }

    if (game->turn_index >= board->width * board->height - 1) {
        return DRAW;
    }

    return NONE;
}

// Only call this After checking for a win
bool is_draw(Game *game) {
    Board *board = game->board;

    if (game->turn_index >= board->width * board->height) {
        return true;
    }

    return false;
}
