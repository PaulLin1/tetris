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
  if (check_collision(board, 's')) {
    board->current_block->current_y++;
  }
}

int check_collision(Board* board, char movement) {
  Block* block = board->current_block;
  int dx, dy;
  switch (movement) {
    case 'a':
      dx = -1;
      dy = 0;
      break;
    case 'd':
      dx = 1;
      dy = 0;
      break;
    case 's':
      dx = 0;
      dy = 1;
      break;
    default:
      dx = 0;
      dy = 0;
      break;
  }
  for (int i = 0; i < block->size; ++i) {
    for (int j = 0; j < block->size; ++j) {
      if (block->cells[(j * block->size) + i] == '1') {
        int new_x = block->current_x + i + dx;
        int new_y = block->current_y + j + dy;
        if (new_y >= ROWS || (board->cells[new_y][new_x] == '1' && movement == 's')) {
          block->dropped = 1;
          return 0;
        }
        if (new_x < 0 || new_x >= COLS || new_y < 0 || new_y >= ROWS) {
          return 0;
        }
        if (board->cells[new_y][new_x] == '1') {
          return 0;
        }
      }
    }
  }
  return 1;
}

void move_block(Board* board, char movement) {
  Block* block = board->current_block;
  if (check_collision(board, movement)) {
    if (movement == 's') {
      block->current_y++;
    } else if (movement == 'a') {
        block->current_x--;
    } else if (movement == 'd') {
        block->current_x++;
    }
  }
  if (movement == 'w') {
    int n = block->size;
    int rotated[n * n];
    int temp[n*n];
    for (int i = 0; i < n * n; ++i) {
      temp[i] = block->cells[i];
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        rotated[j*n + (n- 1 -i)] = block->cells[i * n +j];
      }
    }
    for (int i = 0; i < n * n; ++i) {
      block->cells[i] = rotated[i];
    }
    
    while (block->current_x < 0) {
      block->current_x++;
    }
    while (block->current_x > COLS - block->size) {
      block->current_y--;
    }
    if (!check_collision(board, 'l')) { 
      for (int i = 0; i < n * n; ++i) {
      block->cells[i] = temp[i];
    }
    }
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
    tetris(board);
    board->current_block = board->next_block;
    Block* z = malloc(sizeof(Block));
    Block* temp = load_block();
    memcpy(z, temp, sizeof(Block));
    board->next_block = z; 
  }
}

void tetris(Board *board) {
  int clear_counter = 0;
  for (int j = 0; j < ROWS; ++j) {
    int total = 0;

    for (int i = 0; i < COLS; ++i) {
      if (board->cells[j][i] == '1') {
        total += 1; 
      }
    }
    if (total == COLS) {
      clear_counter++;
      for (int i = j; i > 0; --i) {
        for (int k = 0; k < COLS; ++k) {
          board->cells[i][k] = board->cells[i - 1][k];
        }
      }

      for (int q = 0; q < COLS; ++q) {
        board->cells[0][q] = '*';
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

