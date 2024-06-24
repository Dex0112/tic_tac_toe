#ifndef TIC_TAC_TOE
#define TIC_TAC_TOE

#include <stdbool.h>

typedef enum {
    X,
    O,
    EMPTY,
} CellState;

typedef enum {
    WIN,
    DRAW,
    NONE,
} GAME_RESULT;

typedef struct {
    unsigned int width;
    unsigned int height;

    CellState **grid;
} Board;

typedef struct {
    unsigned int turn_index;
    Board *board;
} Game;

Game *create_game(unsigned int width, unsigned int height);
Board *create_board(unsigned int width, unsigned int height);
void free_board(Board *board);
void free_game(Game *game);
bool try_place(Game *game, unsigned int x, unsigned int y);
GAME_RESULT has_result(Game *game, CellState target);
// Is win returns game result
bool is_draw(Game *game);

#endif
