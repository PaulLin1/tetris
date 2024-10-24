#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "tetromino.h"
#include "constants.h"

struct Board createTable() {
  struct Board board;
  for (int y = 0; y < R0WS; y++) {
    for (int x = 0; x < COLS; x++) {
      board.cells[y][x] = '*';
    }
  }
  return board;
}


void update_board (struct Board *board) {
  board->current_block->current_y++;
  if (board->current_block->current_y == R0WS -4) {
    place_block(board); 
    board->current_block = (struct Block *)malloc(sizeof(struct Block));
    *(board->current_block) = load_block();
  }
}

void place_block (struct Board *board) {
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      if (board->current_block->cells[y][x] != '0') {
        board->cells[y + board->current_block->current_y][x + board->current_block->current_x] = board->current_block->cells[y][x];
      }
    }
  }
 
}
void print_table (struct Board *board) {
  printf("\033[H");
  struct Board board_copy = *board;
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      if (board_copy.current_block->cells[y][x] != '0') {
        board_copy.cells[y + board_copy.current_block->current_y][x + board_copy.current_block->current_x] = board_copy.current_block->cells[y][x];
      }
    }
  }
  for (int y = 0; y < R0WS; y++) {
    for (int x = 0; x < COLS; x++) {
      printf("%c", board_copy.cells[y][x]);
    }
    printf("\n");
  }
}


