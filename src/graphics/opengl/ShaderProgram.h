#pragma once

#include <GL/glew.h>
#include "Math.h"


namespace gen {
	

	class ShaderProgram {
	private:
		GLuint ID;
		void addShader(int, const char *);

	public:
		ShaderProgram();
		void addVertexShader(const char *);
		void addFragmentShader(const char *);
		void link();
		void use();
		void setUniform(const char *, Mat4);
	};

	


} // namespace gen
