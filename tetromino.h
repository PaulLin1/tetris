#ifndef TETROMINO_H
#define TETROMINO_H

#include "board.h"
struct Block {
  char cells[4][4];
  int current_x;
  int current_y;
  int rotation; // 0-3
  int dropped; // 0 = False; 1 = True
};

struct Board;
struct Block load_block(); 
void move_block (struct Board *board, char movement);

#endif // !TETROMINO_H
