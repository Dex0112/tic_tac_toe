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

Board *create_board(unsigned int width, unsigned int height);
void free_board(Board *board);
// Function to place and check for winning and what not

#endif
