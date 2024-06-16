#include <stdlib.h>
#include "tic_tac_toe.h"


Board *create_board(unsigned int width, unsigned int height) {
    Board *board = (Board *)malloc(sizeof(Board));

    board->width = width;
    board->height = height;
    board->grid = (CellState **)malloc(sizeof(CellState *) * width);

    for (int i = 0; i < width; i++) {
        board->grid[i] = (CellState *)malloc(sizeof(CellState *) * height);

        for(int j = 0; j < height; j++) {
            board->grid[i][j] = EMPTY;
        }
    }

    return board;
}

void free_board(Board *board) {
    for(int i = 0; i < board->width; i++) {
        free(board->grid[i]);
    }

    free(board->grid);

    free(board);
}
