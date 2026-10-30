#version 330 core
layout (location = 0) in vec3 aPos; //vertex input attribute 3 floats for position
uniform mat4 uMVP;
out float vDepth;
void main()
{
  gl_Position = uMVP * vec4(aPos, 1.0); //4 component clip space position x, y, z, w where w is the perspective divide
  vDepth = aPos.z;
}
