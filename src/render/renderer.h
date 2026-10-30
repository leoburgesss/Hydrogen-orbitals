#pragma once 
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>

class Renderer{
  public:
    Renderer(GLFWwindow* window, int w, int h);
    void drawCircle(float x, float y, float radius, float d);
    void setVertices(const std::vector<float>& points, int components);

  private:
    GLFWwindow* window_; //pointer to glfw window
    GLuint vao_, vbo_; 
    //vertex buffer object and vertex array object
    //vbo: memory buffer located in gpu memory to store raw vertices
    //vao: the configuration of the vbo how to read it properly
    GLuint program_; // the handle for the shader in gpu memory
    int components_, vertexCount_;
    //components: float per vertex in vbo
    //vertex count: total number of vertices from every shape in the vbo
    int width_, height_;
    //screen size
    
    void createProgram(const std::string& vertPath, const std::string& fragPath);
    
};


