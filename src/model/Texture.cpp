#include "Texture.h"



using namespace gen;


Texture::Texture(unsigned int ID)
	: ID(ID)
{}

void Texture::copyFrom(std::unique_ptr<Texture> other)
{
	ID = other->ID;
}
	
unsigned int Texture::getID() { return ID; }

std::unique_ptr<Texture> Texture::newTexture(GLTexture* glTexture)
{
	return std::make_unique<Texture>(glTexture->getID());	
}

Texture Texture::emptyTexture() {
	return Texture(0);
}