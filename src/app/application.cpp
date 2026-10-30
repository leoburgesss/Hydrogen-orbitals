#include "app/application.h"
#include "render/renderer.h"

#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <iostream>

Application::Application(GLFWwindow* window, int w, int h) : window_(window), width_(w), height_(h), renderer_(window, w, h) {}

void Application::run(){
  double lastTime = glfwGetTime();
  int frames = 0;

  while (!glfwWindowShouldClose(window_)){
    //clear scren
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderer_.drawSphere(-0.7f,  0.3f,  0.8f, 0.2f, 1);
    renderer_.drawSphere( 0.9f, -0.4f, -0.6f, 0.35f, 1);
    renderer_.drawSphere(-0.2f, -0.8f,  1.4f, 0.15f, 1);
    renderer_.drawSphere( 1.3f,  0.6f,  0.1f, 0.45f, 1);
    renderer_.drawSphere( 0.1f,  1.1f, -1.7f, 0.25f, 1);
    renderer_.drawSphere(-1.1f, -0.9f,  0.4f, 0.6f, 1);
    renderer_.drawSphere( 0.6f, -1.3f,  2.2f, 0.3f, 1);
    renderer_.drawSphere(-0.5f,  0.9f, -0.3f, 0.12f, 1);
    renderer_.drawSphere( 1.8f, -0.2f, -1.2f, 0.5f, 1);
    renderer_.drawSphere(-1.4f,  1.2f,  1.0f, 0.22f, 1);
    renderer_.drawSphere( 0.3f, -0.6f, -2.1f, 0.4f, 1);
    renderer_.drawSphere(-0.9f,  0.1f,  1.8f, 0.18f, 1);
 
    

    frames++;
    double now = glfwGetTime();
    if (now - lastTime >= 0.5) {
      std::cout << (frames / (now - lastTime)) << " FPS\n";
      frames = 0;
      lastTime = now;
    }
    
    //gl draws to buffer behind current when rendering so when finished rendering it swaps buffers to flip frame
    glfwSwapBuffers(window_);
    glfwPollEvents();
}
  
}
