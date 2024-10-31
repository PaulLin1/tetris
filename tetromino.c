#include "tetromino.h"
#include "board.h"
#include "constants.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

Block all_blocks[7];

void initialize_all_blocks() {
  size_t o_block_length = 3;
  int *o_block_arr = malloc(o_block_length * o_block_length * sizeof(int));
  int o_block_template[2][2] = {
  {2, 2},
  {2, 2}
  };
  
  Block new_block = {o_block_arr, o_block_length, 0, 0, 0, 0};
  all_blocks[0] = new_block;
}

Block load_block() {
  Block new_block;
  memcpy(&new_block, &all_blocks[0], sizeof(Block));
  return new_block;
}
