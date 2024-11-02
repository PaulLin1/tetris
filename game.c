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

char movement = 0;
pthread_mutex_t movement_mutex;

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
  while (1) {
    char key_input = getchar();
    if (key_input != '\0') {
      pthread_mutex_lock(&movement_mutex);
      movement = key_input;
      pthread_mutex_unlock(&movement_mutex);
    }
  }
}

int init_game(int argc, char *argv[]) {   
  Board tetris_board = init_board();
  initialize_all_blocks();
  Block curr = load_block();
  
  tetris_board.current_block = &curr; 
   
  srand(time(0));
  time_t current_time;

  time(&current_time);
  time_t move_time;
  time(&move_time);

  disable_canonical_mode();
   
  pthread_t input_thread;
  pthread_create(&input_thread, NULL, input_handler, NULL);
 
  while (1) {
    time_t next_time;  
    time(&next_time);
    
    new_block(&tetris_board);

    if (next_time - current_time > 1) {
      current_time = next_time;
      pthread_mutex_lock(&movement_mutex);

      drop_block(&tetris_board);
      print_table(tetris_board);

      pthread_mutex_unlock(&movement_mutex);
    } else if (movement != 0 && check_collision(tetris_board, movement)) {
      pthread_mutex_lock(&movement_mutex);
    
      move_block(tetris_board.current_block, movement);
      print_table(tetris_board);

      pthread_mutex_unlock(&movement_mutex);

      movement = 0;
    }
  }
  pthread_join(input_thread, NULL);
}
