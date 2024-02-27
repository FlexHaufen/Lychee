#type vertex
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;

layout(std140, binding = 0) uniform Camera {
	mat4 u_ViewProjection;
};

struct VertexOutput {
	vec4 Color;
};

layout (location = 0) out VertexOutput Output;

void main() {
	Output.Color = a_Color;
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}

#type fragment
#version 450 core

layout(location = 0) out vec4 o_Color;

struct VertexOutput {
	vec4 Color;
	vec2 TexCoord;
	float TilingFactor;
};

layout (location = 0) in VertexOutput Input;

void main() {
	vec4 color = Input.Color;

	if (color.a == 0.0) {
		discard;
	}
	o_Color = color;
}
