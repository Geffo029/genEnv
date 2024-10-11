#pragma once

#include <GLFW/glfw3.h>


namespace gen {
	
	class Window {
	private:
		GLFWwindow *handle;

	public: 
		Window(int, int, const char *);
		// ~Window();
		void setVSync(bool);
		bool shouldClose();
		void swapbuffers();
		float getAspectRatio();
		void destroy();
	};

}