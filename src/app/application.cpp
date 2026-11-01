#include "application.h"
#include "render/renderer.h"
#include "hydrogen/hydrogen.h"

#include <cmath>
#include <iostream>

Application::Application(GLFWwindow* window, int w, int h) : window_(window), width_(w), height_(h), renderer_(window, w, h) {}

void Application::run(){
  double lastTime = glfwGetTime();
  int frames = 0;
  std::cout << "Generating density cloud!\n";
  std::vector<float> cloud = hydrogen::densityCloud(0.00001, 3, 2, 1, 256, 20);

  while (!glfwWindowShouldClose(window_)){
    double now = glfwGetTime();
    
    //clear screen
    glClearColor(0.0706f, 0.0431f, 0.0392f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
    renderer_.drawPoints(cloud);
 
    

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
