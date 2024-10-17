#pragma once

#include "GLTexture.h"
#include <memory>



namespace gen
{

	class Texture
	{
	
	private:
		bool empty; 
		unsigned int ID;
	
	public:
		Texture(bool, unsigned int);
		void copyFrom(std::unique_ptr<Texture>);
		unsigned int getID();
		bool isEmpty();

		static std::unique_ptr<Texture> newTexture(GLTexture*);
		static Texture emptyTexture();

	};


}