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
    double now = glfwGetTime();
    
    //clear screen
    glClearColor(0.0706f, 0.0431f, 0.0392f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderer_.drawAxis();
    for(float z{-2}; z<=2;z+=0.1){
      for(float x{-2}; x<=2; x+=0.1){
      renderer_.drawSphere(x, std::sin(now + z + x), z , 0.025, 1);
    }}
 
    

    frames++;
    if (now - lastTime >= 10) {
      std::cout << (frames / (now - lastTime)) << " FPS\n";
      frames = 0;
      lastTime = now;
    }
    
    //gl draws to buffer behind current when rendering so when finished rendering it swaps buffers to flip frame
    glfwSwapBuffers(window_);
    glfwPollEvents();
}
  
}
