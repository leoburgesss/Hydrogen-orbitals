#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <cmath>

int main(){
//glfw initialisation
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
//glfw window pointer to window
  GLFWwindow* window = glfwCreateWindow(1080, 1080, "Hydrogen Orbitals", nullptr, nullptr);
  if(!window){std::cerr << "Failed to create window\n"; return -1;}

//make current context window 
  glfwMakeContextCurrent(window);

//glew initialisation
glewExperimental = GL_TRUE;
GLenum err = glewInit();
if (err != GLEW_OK){std::cerr << "Failed to init Glew\n"; return -1;}
glGetError();

//main render loop 
while (!glfwWindowShouldClose(window)){
  glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glfwSwapBuffers(window);
  glfwPollEvents();
}

glfwTerminate();
return 0;

}
