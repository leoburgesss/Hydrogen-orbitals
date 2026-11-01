#version 330 core
in float vRho;
out vec4 FragColor; //final rgba output for this fragment written to the framebuffer at draw time 
vec3 inferno(float t) {
    // approximation of matplotlib "inferno"
    vec3 c0 = vec3(0.001, 0.000, 0.014);
    vec3 c1 = vec3(0.227, 0.031, 0.267);
    vec3 c2 = vec3(0.571, 0.148, 0.310);
    vec3 c3 = vec3(0.866, 0.316, 0.226);
    vec3 c4 = vec3(0.988, 0.652, 0.211);
    vec3 c5 = vec3(0.988, 0.998, 0.645);
    // piecewise-linear across 5 segments
    if (t < 0.25) return mix(c0, c1, t / 0.25);
    if (t < 0.50) return mix(c1, c2, (t - 0.25) / 0.25);
    if (t < 0.75) return mix(c2, c3, (t - 0.50) / 0.25);
    if (t < 0.90) return mix(c3, c4, (t - 0.75) / 0.15);
    return mix(c4, c5, (t - 0.90) / 0.10);
}

void main(){
    float t = clamp(log(1.0 + vRho * 1000000) / 7.0, 0.0, 1.0);

    FragColor = vec4(inferno(t), 0.008);
}
