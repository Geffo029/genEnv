#pragma once

#include <GL/glew.h>
#include "RawData.h"


namespace gen {

	class VAO {
	private:
		GLuint ID;
		GLushort verticesCount;
		GLushort indicesCount;

		void addBuffer(float[], GLint, GLuint);
		void addIndexBuffer(unsigned short[]);
	
	public:
		VAO(unsigned short, float[], int, unsigned short, unsigned short[]);
		VAO(unsigned short, float[], int, float[], int, unsigned short, unsigned short[]);
		VAO(obj::data);
		// void bind();
		unsigned int getID();
		unsigned short getElementCount();

		static void bind(VAO);
		static void bind(GLuint);
		static void unbind();		
	};

	
} // namespace gen

