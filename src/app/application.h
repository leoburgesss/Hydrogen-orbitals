#pragma once 
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class application {
  public:
    application(GLFWwindow* window, int w, int h);
    bool init();
    void run();

  private:
    int width_, height_;
    GLFWwindow* window_;
    void render();
};
