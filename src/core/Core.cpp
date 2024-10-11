#include <chrono>
#include <cmath>
#include <ostream>
#include <thread>
#include <memory>
#include <iostream>
#include <utility>

// L'ordine degli include e importante
#include "RawData.h"
#include "ShaderProgram.h"
#include "GLTexture.h"
#include "VAO.h"
#include "Renderer.h"
#include "Clock.h"
#include "OpenGL.h"
#include "Glfw.h"
#include "Window.h"
#include "components/Mesh.h"
#include "components/Model.h"
#include "components/Texture.h"
#include "components/Transform.h"
#include "RawData.h"




class Core
{

private:
	const float FPS = 60.0f; 
	bool STOP = false;
	bool NEW_FRAME = true;

	gen::Clock *clock;
	gen::Window *window;
	gen::ShaderProgram *shader;
	gen::Renderer *renderer;

	// gen::Transform *transform;
	// gen::Mesh *mesh;
	// gen::VAO *vao;
	gen::Model *plane;
	std::unique_ptr<gen::Transform> planeTransform;
	std::unique_ptr<gen::Mesh> planeMesh;
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

		shader = new gen::ShaderProgram();
		shader->addVertexShader("../res/shaders/VS_texturedModel.glsl"); // From ./build directory
		shader->addFragmentShader("../res/shaders/FS_texturedModel.glsl");
		shader->link();

		renderer = new gen::Renderer();
		renderer->setShader(shader);
		
		clock = new gen::Clock();
		clock->setEvent("SHOW FPS", 2.);
		
		gen::obj::data objData = gen::obj::readFile("../res/plane.obj");

		planeMesh = gen::Mesh::newMesh(new gen::VAO(objData));
		planeTransform = gen::Transform::newTransform(0,1,2, 90,0,0,1, 1,1,1);
		plane = gen::Model::newModel(std::move(planeTransform), std::move(planeMesh));
		
		objData = gen::obj::readFile("../res/die.obj");
		gen::image::data textureData = gen::image::readFile("../res/dieTexture.png");
		dieTransform = gen::Transform::newTransform(0,-1,5, 0,0,0,1, 1,1,1);
		dieMesh = gen::Mesh::newMesh(new gen::VAO(objData));
		dieTexture = gen::Texture::newTexture(new gen::GLTexture(textureData));

		die = gen::Model::newModel();
		die->addTransform(std::move(dieTransform));
		die->addMesh(std::move(dieMesh));
		die->addTexture(std::move(dieTexture));

		gen::obj::cleanup(objData);
		gen::image::cleanup(textureData);
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
		
		plane->rotate(0, clock->deltaTime()*100, 0, 0);
		// model->getTransform()->setRotation(0, std::sin(clock->getCurrentTime_micros()*0.000001)*180, 0, 1);
		plane->move(std::cos(clock->getCurrentTime_sec()*3.14) * 5 * clock->deltaTime(), 0, 0);

		die->rotate(clock->deltaTime()*20, clock->deltaTime()*100, clock->deltaTime()*20, 0);
		// die->move(std::cos(clock->getCurrentTime_sec()*3.14) * 20 * clock->deltaTime(), 0, 0);


		// Render...
		renderer->clearScreen();
		renderer->render(gen::Model::modelsQueue(), gen::Model::modelsCount());
		
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
