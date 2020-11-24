#version 330 core

layout (location = 0) in vec3 aPos;

out VertexData {
	vec3 TexCoords;
} vs_out;

//Porjection & view matrices
layout (std140) uniform Matrices {
    mat4 projection;
    mat4 view;
};

void main() {
    vs_out.TexCoords = vec3(aPos.x, -aPos.yz);
    vec4 finalPos = projection * mat4(mat3(view)) * vec4(aPos, 1.0);
    gl_Position = finalPos.xyww;
}