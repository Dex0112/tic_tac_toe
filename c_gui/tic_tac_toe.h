#ifndef TIC_TAC_TOE
#define TIC_TAC_TOE

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

typedef struct {
    unsigned int turn_index;
    Board *board;
} Game;

Board *create_board(unsigned int width, unsigned int height);
void free_board(Board *board);
bool try_place(Game *game, unsigned int x, unsigned int y);
// Check for winner

#endif
