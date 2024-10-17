#include "Model.h"
#include "Texture.h"
#include <iostream>
#include <memory>
#include <utility>



using namespace gen;


// void ModelManager::createModel(Transform transform, Mesh mesh) {
// 	renderQueue[lastFreeIndex] = Model(transform, mesh); 
// 	lastFreeIndex++;
// }


unsigned int Model::lastFreeIndex = 1; //TODO: l'indice 0 sarebbe riservato agli oggetti vuoti. Cambiare e permette agli indici di essere negativi
Model Model::renderQueue[5];


Model::Model() 
	: empty(true), transform(Transform::emptyTransform()), mesh(Mesh::emptyMesh()), texture(Texture::emptyTexture()), index(0)
{
	// std::cout << "Model EMPTY CONSTRUCTOR called" << std::endl;	
}

// Model::Model(Transform &&transform, Mesh &&mesh, unsigned int index) 
// 	: transform(std::move(transform)), mesh(std::move(mesh))
// {
// 	std::cout << "Model CONSTRUCTOR called" << std::endl;	
// 	// this->transform = transform;
// 	// this->mesh = mesh;
// 	this->index = index;
// }

// void Model::absorb(std::unique_ptr<Model> model)
// {
// 	if (transform.isEmpty()) {
// 		transform.copyFrom( std::move(model->transform) );
// 	}
// }

void Model::move(float delta_x, float delta_y, float delta_z)
{
	float *location = transform.getLocation();
	transform.setLocation(location[0] + delta_x, location[1] + delta_y, location[2] + delta_z);
}
void Model::rotate(float delta_x, float delta_y, float delta_z, float delta_w)
{
	float *rotation = transform.getRotation();
	transform.setRotation(rotation[0] + delta_x, rotation[1] + delta_y, rotation[2] + delta_z, rotation[3] + delta_w);
}
void Model::rescale(float delta_x, float delta_y, float delta_z)
{
	float *scale = transform.getScale();
	transform.setScale(scale[0] + delta_x, scale[1] + delta_y, scale[2] + delta_z);
}

bool Model::isEmpty() { return empty; }

Transform* Model::getTransform() { return &this->transform; }

Mesh* Model::getMesh() { return &this->mesh; }

Texture* Model::getTexture() { return &this->texture; }


void Model::addTransform(std::unique_ptr<Transform> transform)
{
	this->transform.copyFrom(std::move(transform));
}

void Model::addMesh(std::unique_ptr<Mesh> mesh)
{
	this->mesh.copyFrom(std::move(mesh));
}

void Model::addTexture(std::unique_ptr<Texture> texture)
{
	this->texture.copyFrom(std::move(texture));
}

Model::~Model()
{
	// std::cout << "Model DESTRUCTOR called" << std::endl;	
}

Model* Model::newModel() {
	Model *currentModel = &renderQueue[lastFreeIndex];
	currentModel->empty = false;
	lastFreeIndex++;
	return currentModel;
}

Model* Model::newModel(Transform &&transform, Mesh &&mesh)
{
	unsigned int currentIndex = lastFreeIndex;
	renderQueue[currentIndex].empty = false;
	renderQueue[currentIndex].transform.newFrom(std::move(transform));
	renderQueue[currentIndex].mesh.newFrom(std::move(mesh));
	lastFreeIndex++;
	return &renderQueue[currentIndex];
}

Model* Model::newModel(std::unique_ptr<Transform> transform, std::unique_ptr<Mesh> mesh)
{
	// unsigned int currentIndex = lastFreeIndex;
	Model *currentModel = &renderQueue[lastFreeIndex];
	currentModel->empty = false;
	currentModel->transform.copyFrom(std::move(transform));
	currentModel->mesh.copyFrom(std::move(mesh));
	lastFreeIndex++;
	return currentModel;
	// return std::shared_ptr<Model>( &renderQueue[currentIndex]);
}




// std::unique_ptr<Model> Model::newModel(std::unique_ptr<Transform> transform)
// {
// 	unsigned int currentIndex = lastFreeIndex;
// 	renderQueue[currentIndex].transform.copyFrom(std::move(transform));
// 	renderQueue[currentIndex].mesh.emptyMesh();
// 	lastFreeIndex++;
// }


// std::unique_ptr<Model> Model::newModel(std::unique_ptr<Mesh> mesh)
// {
// 	unsigned int currentIndex = lastFreeIndex;
// 	renderQueue[currentIndex].transform.emptyTransform();
// 	renderQueue[currentIndex].mesh.copyFrom(std::move(mesh));
// 	lastFreeIndex++;
// }

Model* Model::modelsQueue() { return renderQueue; }

unsigned int Model::modelsCount() { return lastFreeIndex; }
