#ifndef TETROMINO_H
#define TETROMINO_H

#include <stddef.h>

typedef struct {
  int* cells;
  size_t size;
  int current_x;
  int current_y;
  int rotation; // 0-3
  int dropped; // 0 = False; 1 = True
} Block;

void initialize_all_blocks();
Block load_block(); 
void move_block(Block* block, char movement);

#endif // !TETROMINO_H
