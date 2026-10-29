#include "application.h"

#include <iostream>

application::application(GLFWwindow* window, int w, int h) : window_(window), width_(w), height_(h) {}

void application::run(){

  while (!glfwWindowShouldClose(window_)){
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window_);
  glfwPollEvents();
}
  
}
