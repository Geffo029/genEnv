#include "Window.h"
#include "Glfw.h"
#include <iostream>


using namespace gen;

Window::Window(int width, int height, const char *title) {
	glfwInitHint(GLFW_RESIZABLE, GLFW_TRUE);
	// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // glfwCreateWindow() returns NULL
	
	// Glfw::init();  //TODO: non ha senso che solo questa funzione arrivi dalla classe Glfw

	handle = glfwCreateWindow(width, height, title, 0, 0);
	
	if (handle == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		// ...
	}

	glfwSetWindowSizeLimits(handle, 200, 200, 2240, 1400);

	// glfwSetInputMode(handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	/* A window object encapsulates both a top-level window and an OpenGL or OpenGL ES context. 
		It is created with glfwCreateWindow and destroyed with glfwDestroyWindow or glfwTerminate. 
		As the window and context are inseparably linked, the window object also serves as the 
		context handle. */
	glfwMakeContextCurrent(handle);
	
	// std::cout << "Finestra creata" << std::endl;
}

void Window::setVSync(bool enable) {
	if (enable) 
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);
}

bool Window::shouldClose() {
	return glfwWindowShouldClose(handle);
}

void Window::swapbuffers() {
	glfwSwapBuffers(handle);
}

float Window::getAspectRatio() {
	int *width, *height;
	glfwGetWindowSize(handle, width, height);
	return (float) *width / *height;
}

void Window::destroy() {
	glfwDestroyWindow(handle);
}