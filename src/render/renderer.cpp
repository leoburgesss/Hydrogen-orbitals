#include "render/renderer.h"

#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>

constexpr float pi = 3.14159265358979323846f;
constexpr int circleSegments = 100;

void Renderer::setVertices(const std::vector<float>& points, int components){
  components_ = components;
  vertexCount_ = static_cast<int>(points.size()) / components;


  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER,
                points.size() * sizeof(float),
                points.data(),
                GL_STATIC_DRAW);

  glVertexAttribPointer(0,
                        components,
                        GL_FLOAT,
                        GL_FALSE,
                        components * sizeof(float),
                        (void*)0);
  glEnableVertexAttribArray(0);
  
}

static GLuint compileShader(GLenum type, const std::string& src) {
    GLuint s = glCreateShader(type);
    const char* c = src.c_str();
    glShaderSource(s, 1, &c, nullptr);
    glCompileShader(s);

    GLint ok = 0;
    glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[1024];
        glGetShaderInfoLog(s, sizeof(log), nullptr, log);
        std::cerr << "Shader compile failed:\n" << log << "\n";
    }
    return s;
}

void Renderer::createProgram(const std::string& vertPath, const std::string& fragPath) {
    auto readFile = [](const std::string& path) {
        std::ifstream f(path);
        std::stringstream ss;
        ss << f.rdbuf();
        return ss.str();
    };

    GLuint vs = compileShader(GL_VERTEX_SHADER, readFile(vertPath));
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, readFile(fragPath));

    program_ = glCreateProgram();
    glAttachShader(program_, vs);
    glAttachShader(program_, fs);
    glLinkProgram(program_);

    GLint ok = 0;
    glGetProgramiv(program_, GL_LINK_STATUS, &ok);
    if (!ok) {
        char log[1024];
        glGetProgramInfoLog(program_, sizeof(log), nullptr, log);
        std::cerr << "Program link failed:\n" << log << "\n";
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
}

void Renderer::drawCircle(float cx, float cy, float radius, float d){
  std::vector<float> points; points.reserve((circleSegments + 2) * 2);

    points.push_back(cx); points.push_back(cy);

    for(int i{0}; i<=circleSegments; i++){
      float theta = 2 * (float)i * pi / (float)circleSegments;
      points.push_back(cx + radius * std::cos(theta)); 
      points.push_back(cy + radius * std::sin(theta));
    }

    setVertices(points, 2);
    glUseProgram(program_);
    glBindVertexArray(vao_);
    glDrawArrays(GL_TRIANGLE_FAN, 0, circleSegments + 2);
}

Renderer::Renderer(GLFWwindow* window, int w, int h): window_(window), width_(w), height_(h) {
    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);
    createProgram("shaders/circle.vert", "shaders/circle.frag");
}


