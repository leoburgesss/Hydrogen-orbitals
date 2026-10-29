#pragma once 

#include "render/renderer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Application {
  public:
    Application(GLFWwindow* window, int w, int h);
    void run();

  private:
    int width_, height_;
    GLFWwindow* window_;
    Renderer renderer_;
    void render();
};
