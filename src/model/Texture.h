#pragma once

#include "GLTexture.h"
#include <memory>



namespace gen
{

	class Texture
	{
	
	private:
		// bool empty; 
		int ID;
	
	public:
		Texture(unsigned int);
		void copyFrom(std::unique_ptr<Texture>);
		unsigned int getID();

		static std::unique_ptr<Texture> newTexture(GLTexture*);
		static Texture emptyTexture();

	};


}