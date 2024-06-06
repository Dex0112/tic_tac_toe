#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    X,
    O,
    EMPTY,
} CellState;

typedef struct {
    unsigned int width;
    unsigned int height;

    CellState **grid;
} Board;

Board *createBoard(unsigned int width, unsigned int height);
int getGridValue(Board *board, int x, int y);
int setGridValue(Board *board, int x, int y, CellState state);
void freeBoard(Board *board);
void printBoard(Board *board);

int main() {
    // int xCord;
    // int yCord;

    // printf("Input cordinate: ");

    // scanf("%d %d", &xCord, &yCord);

    // printf("You choose (%d, %d)\n", xCord, yCord);

    Board *board = createBoard(10, 10);

    printBoard(board);

    freeBoard(board);

    return 0;
}

Board *createBoard(unsigned int width, unsigned int height) {
    Board *board = (Board *)malloc(sizeof(Board));

    board->width = width;
    board->height = height;

    board->grid = (CellState **)malloc(height * sizeof(CellState *));

    for (int i = 0; i < height; i++) {
        board->grid[i] = (CellState *)malloc(width * sizeof(CellState));
    }

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            board->grid[i][j] = EMPTY;
        }
    }

    return board;
}

// Return 0 on success and 1 on failure
int setGridValue(Board *board, int x, int y, CellState state) {
    assert(x >= 0 && x < board->width);
    assert(y >= 0 && y < board->height);

    board->grid[x][y] = state;

    return 0;
}

void freeBoard(Board *board) {
    printf("Freeing the board!\n");

    for (int i = 0; i < board->width; i++) {
        free(board->grid[i]);
    }

    free(board->grid);
    free(board);
}

void printBoard(Board *board) {
    printf("  ");

    for (int i = 0; i < board->width; i++) {
        printf(" %d  ", i);
    }

    printf("\n");

    for (int y = 0; y < board->height; y++) {
        if (y != 0) {
            printf("  ");
            for (int i = 0; i < board->width; i++) {
                if (i != 0) {
                    printf("+");
                }

                printf("---");
            }

            printf("\n");
        }

        // printf("  ");

        printf("%d ", y);
        for (int x = 0; x < board->width; x++) {
            if (x != 0) {
                printf("|");
            }

            switch (board->grid[x][y]) {
            case X:
                printf(" X ");
                break;
            case O:
                printf(" O ");
                break;
            case EMPTY:
                printf("   ");
                break;
            }
        }
        printf("\n");
    }
}
