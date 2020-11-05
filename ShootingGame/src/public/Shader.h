#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include <map>

class Shader {
public:
	unsigned int ID;
	Shader() {};
	Shader& use();
	void compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource = nullptr);

	void setUniform1f(const char* name, float value);
	void setUniform1i(const char* name, int value);
	void setUniform2f(const char* name, float f1, float f2);
	void setUniform2f(const char* name, const glm::vec2& value);
	void setUniform3f(const char* name, float f1, float f2, float f3);
	void setUniform3f(const char* name, const glm::vec3& value);
	void setUniform4f(const char* name, float x, float y, float z, float w);
	void setUniform4f(const char* name, const glm::vec4& value);
	void setUnifromMat4f(const char* name, const glm::mat4& matrix);

private:
	std::map<const char*, unsigned int> uniformNames;
	void checkCompileErrors(unsigned int object, std::string type);
	unsigned int getUniformLocation(const char* name);
};

#endif // !SHADER_H
