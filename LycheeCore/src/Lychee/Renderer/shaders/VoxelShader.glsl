#type vertex
#version 450 core
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(std140, binding = 0) uniform Camera {
	mat4 u_ViewProjection;
};
layout (location = 0) out vec4 Color;

void main() {
	Color = a_Color;
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}

#type fragment
#version 450 core
layout(location = 0) out vec4 o_Color;
layout(location = 0) in  vec4 i_Color;

void main() {
	if (i_Color.a == 0.0) {
		discard;
	}
	o_Color = i_Color;
}
