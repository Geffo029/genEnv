#include "GuiElement.hpp"



using namespace gen;


unsigned int GuiElement::lastFreeIndex = 1; //TODO: l'indice 0 sarebbe riservato agli oggetti vuoti. Cambiare e permette agli indici di essere negativi
GuiElement GuiElement::elementsQueue[5];


GuiElement::GuiElement() 
	: empty(true), transform(Transform::emptyTransform()), mesh(Mesh::emptyMesh()), texture(Texture::emptyTexture())
{
	// std::cout << "Model EMPTY CONSTRUCTOR called" << std::endl;	
}

GuiElement* GuiElement::newGuiElement(std::unique_ptr<Transform> transform, std::unique_ptr<Mesh> mesh, std::unique_ptr<Texture> texture)
{
	GuiElement *currentModel = &elementsQueue[lastFreeIndex];
	currentModel->empty = false;
	currentModel->transform.copyFrom(std::move(transform));
	currentModel->mesh.copyFrom(std::move(mesh));
	currentModel->texture.copyFrom(std::move(texture));
	lastFreeIndex++;
	return currentModel;
}

GuiElement* GuiElement::getElementsQueue()
{
	return elementsQueue;
}

unsigned int GuiElement::getElementsCount()
{
	return lastFreeIndex;
}