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
    GLFWwindow* window_;
    GLuint vao_, vbo_;
    GLuint program_;
    int components_, vertexCount_;
    int width_, height_;
    
    void createProgram(const std::string& vertPath, const std::string& fragPath);
    
};


