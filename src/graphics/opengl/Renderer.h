#pragma once

#include "ColoredModel.hpp"
#include "TexturedModel.hpp"
#include "VAO.h"
#include "ShaderProgram.h"
#include "Model.h"



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
		void render(ColoredModel[], int);
		void render(TexturedModel[], int);
		void renderGui(Model[], int);
		static void clearScreen();
		static void wireframeMode(bool);
	};
	

} 