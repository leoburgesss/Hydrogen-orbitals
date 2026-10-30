#include "app/application.h"
#include "render/renderer.h"

#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <iostream>

Application::Application(GLFWwindow* window, int w, int h) : window_(window), width_(w), height_(h), renderer_(window, w, h) {}

void Application::run(){

  while (!glfwWindowShouldClose(window_)){
    //clear scren
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    renderer_.drawCircle(0.0f, 0.0f, 0.5f, 1);
    //gl draws to buffer behind current when rendering so when finished rendering it swaps buffers to flip frame
    glfwSwapBuffers(window_);
  glfwPollEvents();
}
  
}
