#version 330 core
in float vDepth;
out vec4 FragColor; //final rgba output for this fragment written to the framebuffer at draw time 
void main() {
    float t = clamp(vDepth * 0.3 + 0.5, 0, 1.0);
    vec3 cold = vec3(0.1, 0.4, 1.0);
    vec3 hot = vec3(1.0, 0.2, 0.1);
    FragColor = vec4(mix(cold, hot, t), 1.0);
}

