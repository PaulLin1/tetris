#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <pthread.h>

#include <GLFW/glfw3.h>
#include <leif/leif.h>

#include "constants.h"
#include "board.h"
#include "tetromino.h"  

static int winw = 720, winh = 720;
static char movement = 0;
static pthread_mutex_t movement_mutex;

static void render_game_board(Board board) {
  update_board(&board);
  const char* temp = "Tetris Board";

  // Container
  {
    LfUIElementProps props = lf_get_theme().div_props;
    props.color = (LfColor){27, 47, 53, 255};
    lf_push_style_props(props);

    float width = 300.0f, height = 600.0f;
    lf_div_begin(((vec2s){(winw) / 2.0f, (winh - height) / 2.0f}), ((vec2s){width, height}), false);

    lf_pop_style_props();
  }
  
  // Grid
  {
    for (int row = 0; row < ROWS; ++row) {
      for (int col = 0; col < COLS; ++col) {
        float block_size = 30.0f;
        LfColor color;
        switch (board.cells[row][col]) {
          case 1:
            color = (LfColor){62, 33, 36, 255};
            break;
          default:
            color = (LfColor){69, 80, 77, 255};
            break;
        }
        lf_rect(block_size, block_size, color, 2.0f); 

      }
    }
  }
  lf_div_end();
}

static void render_next(Board board) {
  const char* text = "Next";

  // Container
  {
    LfUIElementProps props = lf_get_theme().div_props;
    props.corner_radius = 7.0f;
    props.color = (LfColor){163, 161, 147, 255};
    lf_push_style_props(props);

    float width = 250.0f, height = 200.0f;
    lf_set_ptr_x_absolute(0);
    lf_div_begin(((vec2s){60.0f, 60.0f}), ((vec2s){width, height}), false);

    lf_pop_style_props();
  }
  
  // Text
  {
    LfUIElementProps props = lf_get_theme().text_props;
    props.text_color = LF_BLACK;
    lf_push_style_props(props);

    lf_text(text);

    lf_pop_style_props();
  }
  {
    lf_next_line();
    
    lf_set_ptr_y_absolute(120);
    int next_block_size = board.next_block->size;
    for (int row = 0; row < next_block_size; ++row) {
      lf_set_ptr_x_absolute(120);
      for (int col = 0; col < next_block_size; ++col) {
        float block_size = 30.0f;
        LfColor color;
        switch (board.next_block->cells[(row * next_block_size) +col]) {
          case 1:
            color = (LfColor){62, 33, 36, 255};
            break;
          default:
            color = (LfColor){163, 161, 147, 255};
            break;
        }
        lf_rect(block_size, block_size, color, 4.0f); 
      }
      lf_next_line();
    }
  }
  lf_div_end();
}

static void render_scoreboard(Board board) {
  const char* text = "Scoreboard";

  // Container
  {
    LfUIElementProps props = lf_get_theme().div_props;
    props.corner_radius = 7.0f;
    props.color = (LfColor){163, 161, 147, 255};
    lf_push_style_props(props);

    float width = 250.0f, height = 200.0f;
    lf_set_ptr_x_absolute(0);
    lf_div_begin(((vec2s){60.0f, winh - height - 60.0f}), ((vec2s){width, height}), false);

    lf_pop_style_props();
  }
  
  // Text
  {
    LfUIElementProps props = lf_get_theme().text_props;
    props.text_color = LF_BLACK;
    lf_push_style_props(props);
    lf_text(text);
    lf_next_line();
    char str[12];
    sprintf(str, "%d", board.score);
    lf_text(str);
    lf_pop_style_props();
  }

  lf_div_end();
}

// Function to disable canonical mode and echo
void disable_canonical_mode() {
    struct termios old_tio, new_tio;

    tcgetattr(STDIN_FILENO, &old_tio);

    new_tio = old_tio;
    new_tio.c_lflag &= ~(ICANON | ECHO); 

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

int main(int argc, char *argv[])
{
  Board game_board = init_board();
  initialize_all_blocks();
  Block* curr = load_block();
  game_board.current_block = curr; 
  
  Block* next_block = load_block();
  game_board.next_block = next_block; 
  
  srand(time(0));
  time_t current_time;

  time(&current_time);
  time_t move_time;
  time(&move_time);

  glfwInit();
  GLFWwindow* window = glfwCreateWindow(winw, winh, "Tetris", NULL, NULL);
  glfwMakeContextCurrent(window);
  lf_init_glfw(winw, winh, window);
 
  disable_canonical_mode();

  pthread_t input_thread;
  pthread_create(&input_thread, NULL, input_handler, NULL);

  while(!glfwWindowShouldClose(window)) {
    if (check_end(&game_board)) {
      break;
    }
    time_t next_time;  
    time(&next_time);
    
    new_block(&game_board);

    if (next_time - current_time > 5) {
      current_time = next_time;
      pthread_mutex_lock(&movement_mutex);

      drop_block(&game_board);

      pthread_mutex_unlock(&movement_mutex);
    } else if (movement != 0) {
      pthread_mutex_lock(&movement_mutex);
    
      move_block(&game_board, movement);

      pthread_mutex_unlock(&movement_mutex);

      movement = 0;
    }
 
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.106f, 0.184f, 0.208f, 1.0f);

    lf_begin();
    render_game_board(game_board);
    render_next(game_board);
    render_scoreboard(game_board);
    lf_end();

    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  pthread_join(input_thread, NULL);

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
