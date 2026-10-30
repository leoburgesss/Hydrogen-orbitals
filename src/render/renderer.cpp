#include "render/renderer.h"

#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>

constexpr float pi = 3.14159265358979323846f;
constexpr int circleSegments = 8;

//function to rewrite the vbo and reconfigure the vao
void Renderer::setVertices(const std::vector<float>& points, int components){
  components_ = components;
  vertexCount_ = static_cast<int>(points.size()) / components;

  glBindVertexArray(vao_); 
  glBindBuffer(GL_ARRAY_BUFFER, vbo_); //binds the buffer from the vbo handle to the gl array so using this array targets the vbo
  glBufferData(GL_ARRAY_BUFFER, 
                points.size() * sizeof(float),
                points.data(),
                GL_STATIC_DRAW); //uploads this to the vbo in gpu memory passing in the array, size in bytes, pointers to vertices and the usage hint

  glVertexAttribPointer(0,
                        components,
                        GL_FLOAT,
                        GL_FALSE,
                        components * sizeof(float),
                        (void*)0); //writes to the vao how the data in vbo is stored and how to read it 
  glEnableVertexAttribArray(0); //enables attribute 0 in the vao so that the attribute is read from the vbo at draw time
  
}

static GLuint compileShader(GLenum type, const std::string& src) {
    GLuint s = glCreateShader(type); //creates empty shader object handle with the type passed in 
    const char* c = src.c_str(); //pointer into the chars of the shader 
    glShaderSource(s, 1, &c, nullptr); //copies the shader source into s 
    glCompileShader(s); //compiles the shader 

    GLint ok = 0; 
    glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[1024];
        glGetShaderInfoLog(s, sizeof(log), nullptr, log);
        std::cerr << "Shader compile failed:\n" << log << "\n";
    } //if any errors give the error type 
    return s;
}

void Renderer::createProgram(const std::string& vertPath, const std::string& fragPath) {
    auto readFile = [](const std::string& path) {
        std::ifstream f(path); //reads file at path as string stream 
        std::stringstream ss; //in memory string stream 
        ss << f.rdbuf(); //streams the file buffer into the in memory string stream 
        return ss.str(); // returns as a string 
    };

    GLuint vs = compileShader(GL_VERTEX_SHADER, readFile(vertPath)); 
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, readFile(fragPath)); //compiles each shader 

    program_ = glCreateProgram(); //creates empty handle for the shaders 
    glAttachShader(program_, vs); 
    glAttachShader(program_, fs); //attaches both vertex and fragment shaders 
    glLinkProgram(program_); //links them into runnable shader pipeline 

    GLint ok = 0;
    glGetProgramiv(program_, GL_LINK_STATUS, &ok);
    if (!ok) {
        char log[1024];
        glGetProgramInfoLog(program_, sizeof(log), nullptr, log);
        std::cerr << "Program link failed:\n" << log << "\n";
    } // if any errors give error type

    glDeleteShader(vs); //delete compiled shaders once pased into program_ 
    glDeleteShader(fs);
}

glm::mat4 Renderer::computeMVP() {
    int fw, fh;
    glfwGetFramebufferSize(window_, &fw, &fh);
    float aspect = static_cast<float>(fw) / static_cast<float>(fh);
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);
    
    glm::mat4 view = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 3.0f), //where camera is 
        glm::vec3(0.0f, 0.0f, 0.0f), //where to look
        glm::vec3(0.0f, 1.0f, 0.0f) //up
        );
      
    glm::mat4 mvp = proj * view; 
    return mvp;
}

void Renderer::drawCircle(float cx, float cy, float cz, float radius, float d){
  std::vector<float> points; points.reserve((circleSegments + 2) * 3);

    points.push_back(cx); points.push_back(cy); points.push_back(cz); 


    for(int i{0}; i<=circleSegments; i++){
      float theta = 2 * (float)i * pi / (float)circleSegments;
      points.push_back(cx + radius * std::cos(theta)); 
      points.push_back(cy + radius * std::sin(theta));
      points.push_back(cz);
    }

    setVertices(points, 3);
    glUseProgram(program_); //uses the shader handle 
    glm::mat4 mvp = computeMVP();

    setMVP(mvp);
    glBindVertexArray(vao_); //makes vao the current vao
    glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount_); //draws the array in vbo every triangles made of the 3 points center point currect vertex and prior vertex to create a circle  
}

void Renderer::setMVP(const glm::mat4& mvp) {
    glUseProgram(program_);
    glUniformMatrix4fv(mvpLoc_, 1, GL_FALSE, glm::value_ptr(mvp));
}

Renderer::Renderer(GLFWwindow* window, int w, int h): window_(window), width_(w), height_(h) {
    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);
    createProgram("shaders/circle.vert", "shaders/circle.frag");
    mvpLoc_ = glGetUniformLocation(program_, "uMVP");
}


