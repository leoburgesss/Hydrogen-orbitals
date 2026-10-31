#version 330 core
in float vDepth;
out vec4 FragColor; //final rgba output for this fragment written to the framebuffer at draw time 
void main() {
    float t = clamp(vDepth/2 + 0.5, 0, 1.0);
    vec3 cold = vec3(0.16, 0.0, 0.03);
    vec3 mid = vec3(0.91, 0.23, 0.37);
    vec3 hot = vec3(1.00, 0.89, 0.92);

    vec3 low = mix(cold, mid, smoothstep(0.0, 0.5, t));
    vec3 high = mix(mid, hot, smoothstep(0.5, 1.0, t));
    FragColor = vec4(mix(low, high, t), 1.0);
}
