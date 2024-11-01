#include "tetromino.h"
#include "board.h"
#include "constants.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

Block all_blocks[7];

void initialize_all_blocks() {
  size_t o_block_length = 2;
  int *o_block_arr = malloc(o_block_length * o_block_length * sizeof(int));
  o_block_arr[0] = '1'; 
  o_block_arr[1] = '1'; 
  o_block_arr[2] = '1'; 
  o_block_arr[3] = '1'; 
  
  Block new_block = {o_block_arr, o_block_length, 0, 0, 0, 0};
  all_blocks[0] = new_block;

  size_t l_block_length = 3;
  int *l_block_arr = malloc(l_block_length * l_block_length * sizeof(int));
  l_block_arr[0] = '1'; 
  l_block_arr[1] = '0'; 
  l_block_arr[2] = '0'; 
  l_block_arr[3] = '1'; 
  l_block_arr[4] = '1'; 
  l_block_arr[5] = '1'; 
  l_block_arr[6] = '0'; 
  l_block_arr[7] = '0'; 
  l_block_arr[8] = '0'; 
  
  Block l_block = {l_block_arr, l_block_length, 0, 0, 0, 0};
  all_blocks[1] = l_block;
  
  size_t j_block_length = 3;
  int *j_block_arr = malloc(j_block_length * j_block_length * sizeof(int));
  j_block_arr[0] = '0'; 
  j_block_arr[1] = '0'; 
  j_block_arr[2] = '1'; 
  j_block_arr[3] = '1'; 
  j_block_arr[4] = '1'; 
  j_block_arr[5] = '1'; 
  j_block_arr[6] = '0'; 
  j_block_arr[7] = '0'; 
  j_block_arr[8] = '0'; 
  
  Block j_block = {j_block_arr, j_block_length, 0, 0, 0, 0};
  all_blocks[2] = j_block;
}

Block load_block() {
  int rand_index = rand() % 3;
  Block new_block;
  memcpy(&new_block, &all_blocks[rand_index], sizeof(Block));
  return new_block;
}

void move_block(Block* block, char movement) {
  if (movement == 's') {
    block->current_y++;
  } else if (movement == 'a') {
      block->current_x--;
  } else if (movement == 'd') {
      block->current_x++;
  } else if (movement == 'r') {
    int n = block->size;
    int rotated[n * n];

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        rotated[j*n + (n- 1 -i)] = block->cells[i * n +j];
      }
    }

    for (int i = 0; i < n * n; i++) {
      block->cells[i] = rotated[i];
    }
  }
}
