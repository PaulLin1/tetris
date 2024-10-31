#ifndef BOARD_H
#define BOARD_H

#include "constants.h"
#include "tetromino.h"

typedef struct {
  char cells[ROWS][COLS];
  Block *current_block;
} Board;

Board create_table();
void print_table(Board board);
void drop_block(Board* board);
void new_block(Board* board); 

#endif
