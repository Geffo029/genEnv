#pragma once

#include "VAO.h"
#include "ShaderProgram.h"
#include "components/Model.h"



namespace gen {


	class Renderer	{
	
	private:
		ShaderProgram *shader;
	
	public:
		Renderer();
		~Renderer();

		void testTriangle();
		void setShader(ShaderProgram *);
		void render(VAO *);
		void render(Model *);
		void render(Model[], int);
		void renderGui(Model[], int);
		static void clearScreen();
		static void wireframeMode(bool);
	};
	

} 