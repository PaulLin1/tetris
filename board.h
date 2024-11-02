#ifndef BOARD_H
#define BOARD_H

#include "constants.h"
#include "tetromino.h"

typedef struct {
  char cells[ROWS][COLS];
  Block *current_block;
} Board;

Board init_board();
void update_board(Board* board);
void drop_block(Board* board);
void new_block(Board* board); 
int check_collision(Board board, char movement); 

#endif
