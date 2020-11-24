#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;
out vec4 ParticleColor;

layout (std140) uniform Matrices {
    mat4 projection;
    mat4 view;
};

uniform vec2 offset;
uniform vec4 color;

void main() {
	float scale = 10.f;
	TexCoords = aTexCoords;
	ParticleColor = color;
	gl_Position = projection * view * vec4(vec3((aPos * scale) + offset), 1.f);
}