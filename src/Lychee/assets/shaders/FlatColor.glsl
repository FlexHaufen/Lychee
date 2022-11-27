/**
 * @file FlatColor.glsl
 * @author flexhaufen
 * @brief Flat Color Shader
 * @version 0.1
 * @date 2022-11-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

void main() {
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;

void main() {
	color = u_Color;
}