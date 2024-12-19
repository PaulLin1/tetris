#ifndef BOARD_H
#define BOARD_H

#include "constants.h"
#include "tetromino.h"

typedef struct {
    int cells[ROWS * COLS];
    Block *current_block;
    Block *next_block;
    int score;
} Board;

Board init_board();
void update_board(Board* board);
void drop_block(Board* board);
void new_block(Board* board); // Generates a new block when the current one is dropped
void move_block(Board* board, char movement);
int check_collision(Board* board, char movement); // Check if the current block is touching a block on the board
int check_end(Board* board); // Checks if a dropped block is touching the top of the board
void tetris(Board *board); // Clears row when it becomes filled

#endif
