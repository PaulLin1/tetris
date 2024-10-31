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

int check_collision(Block* block, char movement) {
  int col_sum[block->size];
  int row_sum[block->size];

  for (int y = 0; y < block->size; y++) {
    int temp = 0;
    int temp2 = 0;
    for (int x = 0; x < block->size; x++) {
      temp += (block->cells[(x * block->size) + y] - '0');
      temp2 += (block->cells[(y * block->size) + x] - '0');
    }
    col_sum[y] = temp;
    row_sum[y] = temp2;
  }

  int l_hitbox_offset = 0;

  for (int i = 0; i < block->size; i++) {
    if (col_sum[i] > 0) {
      l_hitbox_offset = i;
      break;
    }
  }

  int r_hitbox_offset = 0;

  for (int i = block->size - 1; i >= 0; i--) {
    if (col_sum[i] > 0) {
      r_hitbox_offset = i + 1;
      break;
    }
  }

  int b_hitbox_offset = block->size - 1;

  for (int i = block->size - 1; i >= 0; i--) {
    if (row_sum[i] > 0) {
      b_hitbox_offset = i + 1;
      break;
    }
  }
  
  int bottom = block->current_y + b_hitbox_offset;
/*  
  for (int i = 0; i < block->size; i++) {
    if (block->cells[((block->size - 1) + block->size) + i] == '1' && board->cells[bottom + 1][block->current_x + i]) {
      return 0;
    }
  }
*/
  if (movement == 'a' && block->current_x - l_hitbox_offset == 0) {
    return 0;
  }
  if (movement == 'd' && block->current_x + r_hitbox_offset == COLS) {
    return 0;
  }
  if (movement == 's' && block->current_y + b_hitbox_offset == ROWS) {
    block->dropped = 1;
    return 0;
  }
  return 1;
}

void move_block(Block* block, char movement) {
  if (check_collision(block, movement) == 1) {
    if (movement == 's') {
      block->current_y++;
    } else if (movement == 'a') {
        block->current_x--;
    } else if (movement == 'd') {
        block->current_x++;
    }
  }
}
