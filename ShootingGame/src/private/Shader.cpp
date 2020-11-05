#include "Shader.h"

Shader& Shader::use() {
	glUseProgram(ID);
	return *this;
}

void Shader::compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource) {
	GLuint sVertex, sFragment, sGeometry;
	//vertex
	sVertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(sVertex, 1, &vertexSource, NULL);
	glCompileShader(sVertex);
	checkCompileErrors(sVertex, "VERTEX");
	//fragment
	sFragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(sFragment, 1, &fragmentSource, NULL);
	glCompileShader(sFragment);
	checkCompileErrors(sFragment, "FRAMGENT");
	//geometry
	if (geometrySource) {
		sGeometry = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(sGeometry, 1, &geometrySource, NULL);
		glCompileShader(sGeometry);
		checkCompileErrors(sGeometry, "GEOMETRY");
	}
	//shader programs
	ID = glCreateProgram();
	glAttachShader(ID, sVertex);
	glAttachShader(ID, sFragment);
	if (geometrySource)
		glAttachShader(ID, sGeometry);
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");

	glDeleteShader(sVertex);
	glDeleteShader(sFragment);
	if (geometrySource)
		glDeleteShader(sGeometry);
}

void Shader::setUniform1f(const char* name, float value) {
	glUniform1f(getUniformLocation(name), value);
}

void Shader::setUniform1i(const char* name, int value) {
	glUniform1i(getUniformLocation(name), value);
}

void Shader::setUniform2f(const char* name, float x, float y) {
	glUniform2f(getUniformLocation(name), x, y);
}

void Shader::setUniform2f(const char* name, const glm::vec2& value) {
	glUniform2f(getUniformLocation(name), value.x, value.y);
}

void Shader::setUniform3f(const char* name, float x, float y, float z) {
	glUniform3f(getUniformLocation(name), x, y, z);
}

void Shader::setUniform3f(const char* name, const glm::vec3& value) {
	glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
}

void Shader::setUniform4f(const char* name, float x, float y, float z, float w) {
	glUniform4f(getUniformLocation(name), x, y, z, w);
}

void Shader::setUniform4f(const char* name, const glm::vec4& value) {
	glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w);
}

void Shader::setUnifromMat4f(const char* name, const glm::mat4& matrix) {
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::checkCompileErrors(unsigned int object, std::string type) {
	int success;
	char infoLog[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(object, 1024, NULL, infoLog);
			std::cout << "[ERROR SHADER]: Compile-time error: Type: " << type << "\n" << infoLog << "\n";
		}
	} else {
		glGetShaderiv(object, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(object, 1024, NULL, infoLog);
			std::cout << "[ERROR SHADER]: Link-time error: Type: " << type << "\n" << infoLog << "\n";
		}
	}
}

unsigned int Shader::getUniformLocation(const char* name) {
	if (uniformNames.find(name) == uniformNames.end()) {
		unsigned int uniformLocation = glGetUniformLocation(ID, name);
		uniformNames.insert(std::pair<const char*, unsigned int>(name, uniformLocation));
		return uniformLocation;
	}
	return uniformNames.find(name)->second;
}
