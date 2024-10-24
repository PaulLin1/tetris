#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <pthread.h>
#include "tetromino.h"
#include "board.h"
#include "constants.h"

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
  struct Block curr = load_block(); 
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
