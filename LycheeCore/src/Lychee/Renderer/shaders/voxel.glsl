#type vertex
#version 450 core
layout (location = 0) in vec3 aPos;
uniform mat4 viewProjectionMatrix;
void main() {
    gl_Position = viewProjectionMatrix * vec4(aPos, 1.0);
}

#type fragment
#version 450 core
out vec4 FragColor;
void main() {
    FragColor = vec4(1.0, 0.5, 0.2, 1.0);
}
