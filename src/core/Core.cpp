#include <chrono>
#include <cmath>
#include <ostream>
#include <thread>
#include <memory>
#include <iostream>
#include <utility>

// L'ordine degli include e importante

#include "ShaderProgram.h"
#include "GLTexture.h"
#include "TexturedModel.hpp"
#include "VAO.h"
#include "Renderer.h"
#include "Clock.h"
#include "OpenGL.h"
#include "Glfw.h"
#include "Window.h"
#include "Mesh.h"
#include "Model.h"
#include "Texture.h"
#include "Transform.h"
#include "Color.hpp"
#include "ColoredModel.hpp"
#include "RawData.h"



class Core
{

private:
	const float FPS = 60.0f; 
	bool STOP = false;
	bool NEW_FRAME = true;

	gen::Clock *clock;
	gen::Window *window;
	gen::ShaderProgram *colorShader;
	gen::ShaderProgram *textureShader;
	gen::Renderer *renderer;

	// gen::Transform *transform;
	// gen::Mesh *mesh;
	// gen::VAO *vao;
	gen::Model *plane;
	std::unique_ptr<gen::Transform> planeTransform;
	std::unique_ptr<gen::Mesh> planeMesh;
	std::unique_ptr<gen::Color> planeColor;
	gen::Model *die;
	std::unique_ptr<gen::Transform> dieTransform;
	std::unique_ptr<gen::Mesh> dieMesh;
	std::unique_ptr<gen::Texture> dieTexture;


public:
	void init()
	{
		gen::Glfw::init();

		window = new gen::Window(1280, 720, "Test");
		window->setVSync(false);
		
		gen::OpenGL::init(); //TODO: deve essere chiamato dopo la creazione di una finestra. Questa cosa deve FINIRE!!

		colorShader = new gen::ShaderProgram();
		colorShader->addVertexShader("../res/shaders/VS_coloredModel.glsl");
		colorShader->addFragmentShader("../res/shaders/FS_coloredModel.glsl");
		colorShader->link();
		textureShader = new gen::ShaderProgram();
		textureShader->addVertexShader("../res/shaders/VS_texturedModel.glsl"); // From ./build directory
		textureShader->addFragmentShader("../res/shaders/FS_texturedModel.glsl");
		textureShader->link();

		renderer = new gen::Renderer();
		
		clock = new gen::Clock();
		clock->setEvent("SHOW FPS", 2.);
		
		planeTransform = gen::Transform::newTransform(0,1,2, 90,0,0,1, 1,1,1);
		planeMesh = gen::Mesh::newMesh(new gen::VAO(gen::obj::readFile("../res/plane.obj")));
		planeColor = gen::Color::newColor(1, 0, 0, 0);
		plane = gen::ColoredModel::newModel(std::move(planeTransform), std::move(planeMesh), std::move(planeColor));
		
		dieTransform = gen::Transform::newTransform(0,-1,5, 0,0,0,1, 1,1,1);
		dieMesh = gen::Mesh::newMesh(new gen::VAO(gen::obj::readFile("../res/die.obj")));
		dieTexture = gen::Texture::newTexture(new gen::GLTexture(gen::image::readFile("../res/dieTexture.png")));
		die = gen::TexturedModel::newModel(std::move(dieTransform), std::move(dieMesh), std::move(dieTexture));
	}

	void update()
	{
		clock->updateTime();
		if (clock->getCurrentDeltaTime() >= 1/FPS) {
			NEW_FRAME = true;
		}

		if (window->shouldClose()) {
			STOP = true;
			NEW_FRAME = false;
		}
	}

	void perFrameUpdate()
	{
		NEW_FRAME = false;
		clock->newFrame();

		if (clock->checkEventAndTrigger("SHOW FPS"))
			std::cout << "FPS: " << 1/clock->deltaTime() << std::endl;
		
		// plane->rotate(0, clock->deltaTime()*100, 0, 0);
		plane->move(std::cos(clock->getCurrentTime_sec()*3.14) * 5 * clock->deltaTime(), 0, 0);

		die->rotate(clock->deltaTime()*20, clock->deltaTime()*100, clock->deltaTime()*20, 0);
		// die->move(std::cos(clock->getCurrentTime_sec()*3.14) * 20 * clock->deltaTime(), 0, 0);


		// Render...
		renderer->clearScreen();
		renderer->setShader(colorShader);
		renderer->render(gen::ColoredModel::modelsArray(), gen::ColoredModel::modelsCount());
		renderer->setShader(textureShader);
		renderer->render(gen::TexturedModel::modelsArray(), gen::TexturedModel::modelsCount());
		
		window->swapbuffers();
		gen::Glfw::pollEvents();
	}

	void end()
	{
		window->destroy();
		gen::Glfw::terminate();
	}

	void run()
	{
		std::cout << "INITIALIZING..." << std::endl;
		init();
		std::cout << "STARTING..." << std::endl;
		while (!STOP) {
			update();
			if (NEW_FRAME) perFrameUpdate();
			std::this_thread::sleep_for(std::chrono::microseconds(10));
		}
		std::cout << "ENDING..." << std::endl;
		end();
	}
};


int main(int argc, char const *argv[])
{
	Core().run();

	return 0;
}
