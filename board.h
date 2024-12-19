#ifndef BOARD_H
#define BOARD_H

#include "constants.h"
#include "tetromino.h"

typedef struct {
    int cells[ROWS][COLS];
    Block *current_block;
    Block *next_block;
    int score;
} Board;

Board init_board();
void update_board(Board* board);
void drop_block(Board* board);
void new_block(Board* board); 
void move_block(Board* board, char movement);
int check_collision(Board* board, char movement); 
int check_end(Board* board);
void tetris(Board *board); 

#endif
