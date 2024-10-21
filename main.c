#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <pthread.h>

#define R0WS 20
#define COLS 10

// Function to disable canonical mode and echo
void disable_canonical_mode() {
    struct termios old_tio, new_tio;

    // Get the terminal settings
    tcgetattr(STDIN_FILENO, &old_tio);

    // Copy old settings and modify new settings
    new_tio = old_tio;
    new_tio.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo

    // Apply the new settings
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
}

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

struct Block {
  char cells[4][4];
  int current_x;
  int current_y;
  int rotation; // 0-3
  int dropped; // 0 = False; 1 = True
};

struct Board {
  char cells[R0WS][COLS];
  int size;
  struct Block *current_block;
};

struct Board createTable() {
  struct Board board;
  for (int y = 0; y < R0WS; y++) {
    for (int x = 0; x < COLS; x++) {
      board.cells[y][x] = '*';
    }
  }
  // board.size = 0;
  return board;
}

void update_board (struct Board *board) {
 board->current_block->current_y++;
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

struct Block load_block(struct Board *board) {
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
  if (movement == 'w') {
    board->current_block->current_x++;
  } else if (movement == 'a') {
    board->current_block->current_x--;
  } else if (movement == 's') {
    board->current_block->current_x++;
  } else if (movement == 'd') {
    board->current_block->current_y++;
  }
}

void* input_handler(void* arg) {
    struct Board *board= (struct Board*) arg; 

    while (1) {
 
      char movement = getchar();
      move_block(board, movement);
      print_table(board);
    }
}

int main(int argc, char *argv[]) {   
  srand(time(0));
  struct Board tetris_board = createTable();
  load_block(&tetris_board);
  struct Block curr = load_block(&tetris_board); 
  tetris_board.current_block = &curr; 
  time_t current_time;
  time(&current_time);

  time_t move_time;
  time(&move_time);

  disable_canonical_mode();
  
  pthread_t input_thread;
  pthread_create(&input_thread, NULL, input_handler, &tetris_board);
 
  while (1) {
    time_t next_time;  
    time(&next_time);
    
    if (next_time - current_time > 1) {
      current_time = next_time;
      update_board(&tetris_board);
      print_table(&tetris_board);
    }

  }
  pthread_join(input_thread, NULL);
  return 0;
}
