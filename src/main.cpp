#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "app/application.h"

#include <iostream>
#include <vector>
#include <cmath>

constexpr int screenWidth = 1080;
constexpr int screenHeight = 1080;

int main(){
//glfw initialisation
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
//glfw window pointer to window
  GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Hydrogen Orbitals", nullptr, nullptr);
  if(!window){std::cerr << "Failed to create window\n"; return -1;}

//make current context window 
  glfwMakeContextCurrent(window);
  glfwSwapInterval(0);

//glew initialisation
glewExperimental = GL_TRUE;
GLenum err = glewInit();
if (err != GLEW_OK){std::cerr << "Failed to init Glew\n"; return -1;}
glGetError();

glEnable(GL_DEPTH_TEST);
glDepthMask(GL_TRUE);
glDepthFunc(GL_LEQUAL);

//create application class which manages everything
Application app = Application(window, screenWidth, screenHeight);

//calls the main loop of the application 
app.run();

//terminates when main loop finishes
glfwDestroyWindow(window);
glfwTerminate();
return 0;

}
