#include "Glfw.h"
#include <iostream>


using namespace gen;

bool Glfw::WAS_INITIALIZED = false;

void Glfw::init() {
	if (glfwInit() != 0) {
		std::cout << "[INFO] GLFW initialized" << std::endl;
		std::cout << "[INFO] GLFW version: " << glfwGetVersionString() << std::endl;
		WAS_INITIALIZED = true;
	} else {
		std::cout << "[INFO] Failed to initialize GLFW" << std::endl;
	}
}
void Glfw::pollEvents() {
	glfwPollEvents();
}

void Glfw::terminate() {
	glfwTerminate();
}
