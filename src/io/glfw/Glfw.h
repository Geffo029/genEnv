#pragma once

#include <GLFW/glfw3.h>

// namespace gen {


// 	class Glfw {
// 	private:
// 		static bool WAS_INITIALIZED;

// 	public:
// 		static void init() {
// 			if (glfwInit() != 0) {
// 				std::cout << "[INFO] GLFW initialized" << std::endl;
// 				std::cout << "[INFO] GLFW version: " << glfwGetVersionString() << std::endl;
// 				WAS_INITIALIZED = true;
// 			} else {
// 				std::cout << "[INFO] Failed to initialize GLFW" << std::endl;
// 			}
// 		}

// 		static void pollEvents() {
// 			glfwPollEvents();
// 		}

// 		static void terminate() {
// 			glfwTerminate();
// 		}

// 	};


// } // namespace gen

namespace gen {

	namespace Glfw {
		extern bool WAS_INITIALIZED;
		
		void init();
		void pollEvents();
		void terminate();
	} // namespace Glfw
	

} // namespace gen