#include "tetromino.h"
#include "board.h"
#include "constants.h"
#include <stdlib.h>

// Define all Tetris blocks
char all_blocks[6][4][4] = {
  // char s_block[4][4]
  {
      {'0', '0', '0', '0'},
      {'0', '1', '1', '0'},
      {'0', '1', '1', '0'},
      {'0', '0', '0', '0'}
  },
  // char l_block[4][4]
  {
      {'0', '0', '0', '0'},
      {'0', '0', '1', '0'},
      {'1', '1', '1', '0'},
      {'0', '0', '0', '0'}
  },
  // char reverse_l_block[4][4]
  {
      {'0', '0', '0', '0'},
      {'0', '1', '0', '0'},
      {'0', '1', '1', '1'},
      {'0', '0', '0', '0'}
  },
  // char line_block[4][4]
  {
      {'0', '0', '0', '0'},
      {'1', '1', '1', '1'},
      {'0', '0', '0', '0'},
      {'0', '0', '0', '0'}
  },
  // char t_block[4][4]
  {
      {'0', '0', '0', '0'},
      {'0', '1', '1', '1'},
      {'0', '0', '1', '0'},
      {'0', '0', '0', '0'}
  },
  // char z_block[4][4]
  {
      {'0', '0', '0', '0'},
      {'0', '1', '1', '0'},
      {'0', '0', '1', '1'},
      {'0', '0', '0', '0'}
  }
};

struct Block load_block() {
  int rd_num = rand() % 5; 
  int initial_x = 3;
  int initial_y = 0;

  struct Block block;
  block.current_x = 3;
  block.current_y = 0;
  block.rotation = 0;
  block.dropped = 0;

  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      block.cells[y][x] = all_blocks[rd_num][y][x];
    }
  }
  
  return block;
}

void move_block (struct Board *board, char movement) {
  if (board->current_block->current_x == 0 && movement == 'a' ||
      board->current_block->current_x == COLS - 4 && movement == 'd') {
   ; 
  }
  else {
    if (movement == 'w') {
      board->current_block->current_x++;
    } else if (movement == 'a') {
      board->current_block->current_x--;
    } else if (movement == 's') {
      board->current_block->current_y++;
    } else if (movement == 'd') {
      board->current_block->current_x++;
    }
  }  
  if (board->current_block->current_y == R0WS -4) {
    place_block(board); 
    board->current_block = (struct Block *)malloc(sizeof(struct Block));
    *(board->current_block) = load_block();
  }

}
