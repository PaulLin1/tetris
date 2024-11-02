#include <GLFW/glfw3.h>
#include <leif/leif.h>

static int winw = 720, winh = 720;

static void render_game_board() {
  const char* temp = "Tetris Board";

  // Container
  {
    LfUIElementProps props = lf_get_theme().div_props;
    props.corner_radius = 4.0f;
    lf_push_style_props(props);

    float width = 300.0f, height = 600.0f;
    lf_div_begin(((vec2s){(winw) / 2.0f, (winh - height) / 2.0f}), ((vec2s){width, height}), false);

    lf_pop_style_props();
  }
  
  // Text
  {
    lf_text(temp);
  }

  lf_div_end();
}

static void render_next() {
  const char* text = "Next";
  // Container
  {
    LfUIElementProps props = lf_get_theme().div_props;
    props.corner_radius = 7.0f;
    props.color = (LfColor){65, 167, 204, 255};
    lf_push_style_props(props);

    float width = 250.0f, height = 200.0f;
    lf_set_ptr_x_absolute(0);
    lf_div_begin(((vec2s){60.0f, 60.0f}), ((vec2s){width, height}), false);

    lf_pop_style_props();
  }
  
  // Text
  {
    lf_text(text);
  }

  lf_div_end();
}

static void render_scoreboard() {
  const char* text = "Scoreboard";
  // Container
  {
    LfUIElementProps props = lf_get_theme().div_props;
    props.corner_radius = 7.0f;
    props.color = (LfColor){65, 167, 204, 255};
    lf_push_style_props(props);

    float width = 250.0f, height = 200.0f;
    lf_set_ptr_x_absolute(0);
    lf_div_begin(((vec2s){60.0f, winh - height - 60.0f}), ((vec2s){width, height}), false);

    lf_pop_style_props();
  }
  
  // Text
  {
    lf_text(text);
  }

  lf_div_end();
}

int main(int argc, char *argv[])
{
  glfwInit();

  GLFWwindow* window = glfwCreateWindow(winw, winh, "Tetris", NULL, NULL);

  glfwMakeContextCurrent(window);

  lf_init_glfw(winw, winh, window);

  while(!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);

    lf_begin();
    render_game_board();
    render_next();
    render_scoreboard();
    lf_end();

    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
