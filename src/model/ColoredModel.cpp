#include "ColoredModel.hpp"
#include "Color.hpp"
#include <utility>



using namespace gen;


unsigned int ColoredModel::lastFreeIndex = 1; //TODO: l'indice 0 sarebbe riservato agli oggetti vuoti. Cambiare e permette agli indici di essere negativi
ColoredModel ColoredModel::models[5];

ColoredModel::ColoredModel() 
	: color(Color::emptyColor())
{
	// std::cout << "Model EMPTY CONSTRUCTOR called" << std::endl;	
}


Color* ColoredModel::getColor() { return &this->color; }

ColoredModel* ColoredModel::newModel(std::unique_ptr<Transform> transform, std::unique_ptr<Mesh> mesh, std::unique_ptr<Color> color)
{
	ColoredModel *currentModel = &models[lastFreeIndex];
	currentModel->transform.copyFrom(std::move(transform));
	currentModel->mesh.copyFrom(std::move(mesh));
	currentModel->color.copyFrom(std::move(color));
	lastFreeIndex++;
	return currentModel;
}

ColoredModel* ColoredModel::modelsArray()
{ return models; }

unsigned int ColoredModel::modelsCount()
{ return lastFreeIndex; }

