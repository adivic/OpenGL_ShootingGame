#version 330 core
out vec4 finalColor;

in VertexData {
	vec3 TexCoords;
} fs_in;

uniform samplerCube skybox;

void main() {
	finalColor = texture(skybox, fs_in.TexCoords);
}