#include "ShaderProgram.h"
#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <vector>


using namespace gen;


	
ShaderProgram::ShaderProgram() {
	ID = glCreateProgram();
}

void ShaderProgram::addVertexShader(const char *shaderPath) {
	addShader(GL_VERTEX_SHADER, shaderPath);
}

void ShaderProgram::addFragmentShader(const char *shaderPath) {
	addShader(GL_FRAGMENT_SHADER, shaderPath);
}

void ShaderProgram::addShader(int shaderType, const char *shaderPath) {
	std::ifstream fileReader(shaderPath);
	std::string line;
	std::string fileContent = "";
	while (getline(fileReader, line)) {
		fileContent += line + "\n";
	}
	const char *shaderSource = fileContent.c_str();

	int shaderID = glCreateShader(shaderType);

	glShaderSource(shaderID, 1, &shaderSource, NULL);
	
	glCompileShader(shaderID);

	GLint compileStatus;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);

	if (compileStatus == GL_TRUE) {
		glAttachShader(ID, shaderID);
		std::cout << "[INFO] Shader " << shaderPath << " compiled." << std::endl;
	}
	else { 
		std::cout << "[INFO] Shader " << shaderPath << " compile error:" << std::endl;
		// int infoLogLength;
		// char *infoLog;
		// glGetShaderInfoLog(shaderID, 0, &infoLogLength, infoLog);
		// std::cout << "Info log: ";
		// for (int i = 0; i < infoLogLength; i++) std::cout << infoLog[i];
		// std::cout << std::endl;
		GLint maxLength = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);

		// Provide the infolog in whatever manor you deem best.
		for (GLchar c : errorLog) std::cout << c;
		std::cout << std::endl;
		
		// Exit with failure.
		glDeleteShader(shaderID); // Don't leak the shader.
	}
}

void ShaderProgram::link() {
	glLinkProgram(ID);
}

void ShaderProgram::use() {
	glUseProgram(ID);
}

void ShaderProgram::setUniform(const char *name, Mat4 value) {
	GLint location = glGetUniformLocation(ID, name);
	glUniformMatrix4fv(location, 1, GL_FALSE, value.toArray());
}