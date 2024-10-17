#include "TexturedModel.hpp"
#include "Texture.h"
#include <utility>



using namespace gen;


unsigned int TexturedModel::lastFreeIndex = 1; //TODO: l'indice 0 sarebbe riservato agli oggetti vuoti. Cambiare e permette agli indici di essere negativi
TexturedModel TexturedModel::models[5];

TexturedModel::TexturedModel() 
	: texture(Texture::emptyTexture())
{
	// std::cout << "Model EMPTY CONSTRUCTOR called" << std::endl;	
}


Texture* TexturedModel::getTexture() { return &this->texture; }

TexturedModel* TexturedModel::newModel(std::unique_ptr<Transform> transform, std::unique_ptr<Mesh> mesh, std::unique_ptr<Texture> texture)
{
	TexturedModel *currentModel = &models[lastFreeIndex];
	currentModel->transform.copyFrom(std::move(transform));
	currentModel->mesh.copyFrom(std::move(mesh));
	currentModel->texture.copyFrom(std::move(texture));
	lastFreeIndex++;
	return currentModel;
}

TexturedModel* TexturedModel::modelsArray()
{ return models; }

unsigned int TexturedModel::modelsCount()
{ return lastFreeIndex; }

