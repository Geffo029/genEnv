#pragma once

#include <GL/glew.h>
#include "RawData.h"



namespace gen
{

	class GLTexture 
	{
	private:
		GLuint ID;


	public:
		GLTexture(image::data);
		unsigned int getID();
		
		static void bind(GLuint);
		static void bind(GLTexture);
		static void unbind();

	};

}
