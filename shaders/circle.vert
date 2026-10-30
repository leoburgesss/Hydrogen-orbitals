#version 330 core 
layout (location = 0) in vec2 aPos; //vertex input attribute 2 floats for position 
void main(){
  gl_Position = vec4(aPos, 0.0, 1.0); //4 component clip space position x, y, z, w where w is the perspective divide
}
