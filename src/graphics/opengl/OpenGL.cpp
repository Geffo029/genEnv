#include "OpenGL.h"
#include <GL/glew.h>
#include <iostream>
#include <ostream>


using namespace gen;


// void OpenGL::clearScreen() {
// 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// }

void OpenGL::init() {
	// glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cout << "!!Error initializing Glew!!" << std::endl;
	}
	// check that the machine supports the 2.1 API.
	if (!GLEW_VERSION_2_1)   {
		std::cout << "!!Glew 2.1 API not supported!!" << std::endl;
	}
}