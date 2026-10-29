#include "app/application.h"
#include "render/renderer.h"

#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <iostream>

Application::Application(GLFWwindow* window, int w, int h) : window_(window), width_(w), height_(h), renderer_(window, w, h) {}

void Application::run(){

  while (!glfwWindowShouldClose(window_)){
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    renderer_.drawCircle(0.0f, 0.0f, 1.0f, 1);

    glfwSwapBuffers(window_);
  glfwPollEvents();
}
  
}
