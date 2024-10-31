#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "tetromino.h"
#include "constants.h"

Board create_table() {
  Board board;
  for (int y = 0; y < R0WS; y++) {
    for (int x = 0; x < COLS; x++) {
      board.cells[y][x] = '*';
    }
  }
  return board;
}

void print_table(Board board) {
  for (int y = 0; y < R0WS; y++) {
    for (int x = 0; x < COLS; x++) {
      printf("%c", board.cells[y][x]);
    }
    printf("\n");
  }
}

