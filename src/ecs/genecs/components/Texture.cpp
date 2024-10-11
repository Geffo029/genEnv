#include "Texture.h"



using namespace gen;


Texture::Texture(bool empty, unsigned int ID)
	: empty(empty), ID(ID)
{}

void Texture::copyFrom(std::unique_ptr<Texture> other)
{
	empty = other->empty;
	ID = other->ID;
}
	
unsigned int Texture::getID() { return ID; }

bool Texture::isEmpty() { return empty; }

std::unique_ptr<Texture> Texture::newTexture(GLTexture* glTexture)
{
	return std::make_unique<Texture>(false, glTexture->getID());	

}

Texture Texture::emptyTexture() {
	return Texture(true, 0);
}