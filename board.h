#ifndef BOARD_H
#define BOARD_H

#include "constants.h"
#include "tetromino.h"

typedef struct {
  char cells[R0WS][COLS];
  Block *current_block;
} Board;

Board create_table();
void print_table(Board board);

#endif
