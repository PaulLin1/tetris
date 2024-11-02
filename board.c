#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"
#include "tetromino.h"
#include "constants.h"

Board init_board() {
  Board board;
  for (int y = 0; y < ROWS; y++) {
    for (int x = 0; x < COLS; x++) {
      board.cells[y][x] = '*';
    }
  }
  board.score = 0;
  return board;
}

void update_board(Board* board) {
  Block* curr = board->current_block;
  
  for (int y = 0; y < curr->size; y++) {
    for (int x = 0; x < curr->size; x++) {
      char current_char = curr->cells[(y*curr->size) + x];
      if (current_char == '1') {
        board->cells[curr->current_y + y][curr->current_x + x] = current_char;
      }
    }
  }
}

void drop_block(Board* board) {
  if (check_collision(*board, 's')) {
    board->current_block->current_y++;
  }
}

int check_collision(Board board, char movement) {
  Block* block = board.current_block;

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
 
  for (int i = 0; i < block->size; i++) {
    if (block->cells[((b_hitbox_offset - 1) * block->size) + i] == '1' && board.cells[bottom][block->current_x + i] == '1') {
      block->dropped = 1;
      return 0;
    }
  }

  if (movement == 'a' && block->current_x + l_hitbox_offset <= 0) {
    return 0;
  }
  if (movement == 'd' && block->current_x + r_hitbox_offset >= COLS) {
    return 0;
  }
  if (movement == 's' && block->current_y + b_hitbox_offset >= ROWS) {
    block->dropped = 1;
    return 0;
  }
  return 1;
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
    tetris(board);
    board->current_block = board->next_block;
    Block* z = malloc(sizeof(Block));
    Block* temp = load_block();
    memcpy(z, temp, sizeof(Block));
    board->next_block = z; 
  }
}

void tetris(Board *board) {
  int total = 0;

  for (int i = 0; i < COLS; ++i) {
    if (board->cells[ROWS - 1][i] == '1') {
      total += 1; 
    }
  }

  int clear_counter = 0;

  while (total == COLS) {
    clear_counter++;
    for (int i = ROWS - 1; i > 0; --i) {
      for (int j = 0; j < COLS; ++j) {
        board->cells[i][j] = board->cells[i - 1][j];
      }
    }

    for (int j = 0; j < COLS; ++j) {
      board->cells[0][j] = '*';
    }
    total = 0;

    for (int i = 0; i < COLS; ++i) {
      if (board->cells[ROWS - 1][i] == '1') {
        total += 1; 
      }
    }
  }
  
  switch (clear_counter) {
    case 1:
      board->score += 100;
      break;
    case 2:
      board->score += 300;
      break;
    case 3:
      board->score += 500;
      break;
    case 4:
      board->score += 800;
      break;
    default:
      ;

  } 
}

