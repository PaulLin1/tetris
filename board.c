#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"
#include "tetromino.h"
#include "constants.h"

Board create_table() {
  Board board;
  for (int y = 0; y < ROWS; y++) {
    for (int x = 0; x < COLS; x++) {
      board.cells[y][x] = '*';
    }
  }
  return board;
}

void drop_block(Board* board) {
  if (check_collision(board->current_block, 's')) {
    board->current_block->current_y++;
  }
}

void new_block(Board* board) {
  Block* curr = board->current_block;

  if (curr->dropped) {
    for (int y = 0; y < curr->size; y++) {
      for (int x = 0; x < curr->size; x++) {
        char current_char = curr->cells[(y*curr->size) + x];
        if (current_char == '1') {
          board->cells[curr->current_y + y][curr->current_x + x] = current_char;
        }
      }
    }
    Block* z = malloc(sizeof(Block));
    Block temp = load_block();
    memcpy(z, &temp, sizeof(Block));
    board->current_block = z; 
  }
}
void print_table(Board board) {
  Block* curr = board.current_block;
  
  for (int y = 0; y < curr->size; y++) {
    for (int x = 0; x < curr->size; x++) {
      char current_char = curr->cells[(y*curr->size) + x];
      if (current_char == '1') {
        board.cells[curr->current_y + y][curr->current_x + x] = current_char;
      }
    }
  }
  for (int y = 0; y < ROWS; y++) {
    for (int x = 0; x < COLS; x++) {
      printf("%c", board.cells[y][x]);
    }
    printf("\n");
  }
}

