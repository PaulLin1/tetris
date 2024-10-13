#include <stdio.h>

const int HEIGHT = 20;
const int WIDTH = 51;

struct GameBoard {
  char board[HEIGHT][WIDTH];
};

struct GameBoard initializeBoard() {
  struct GameBoard b1;

  for(int row = 0; row < HEIGHT; ++row) {
    for(int column = 0; column < WIDTH - 1; ++column) {
      b1.board[row][column] = 'X';
    }
    b1.board[row][WIDTH - 1] = '\n';
  }

  for(int startY = 5; startY < 15; ++startY) {
    for(int startX = 5; startX < 15; ++startX) {
      b1.board[startY][startX] = '*';
    }
  } 

  for(int startY = 0; startY < 20; ++startY){ 
    for(int startX = 20; startX < 30; ++startX) {
      b1.board[startY][startX] = '*';
    }
  }
  return b1;
}

int main(int argc, char *argv[])
{
  struct GameBoard newBoard = initializeBoard();

  for(int i = 0; i < HEIGHT; i++) {
    for(int j = 0; j < WIDTH; j++) {
        printf("%c", newBoard.board[i][j]);
    }
  } 
  return 0;
}
