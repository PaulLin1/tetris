#ifndef BOARD_H
#define BOARD_H

#include "constants.h"
struct Board {
  char cells[R0WS][COLS];
  int size;
  struct Block *current_block;
};

struct Board createTable();
void update_board (struct Board *board);
void place_block (struct Board *board); 
void print_table (struct Board *board);

#endif
