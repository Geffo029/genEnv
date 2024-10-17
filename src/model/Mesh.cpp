#include "Mesh.h"
#include <iostream>



using namespace gen;


// Mesh::Mesh() {
// 	std::cout << "Mesh CONSTRUCTOR called" << std::endl;
// }

Mesh::Mesh(bool empty, unsigned int ID, unsigned int verticesCount)
{
	// std::cout << "Mesh CONSTRUCTOR called" << std::endl;	
	this->empty = empty;
	this->ID = ID;
	this->verticesCount = verticesCount;
}
// Mesh::Mesh(Mesh &&other) {
// 	ID = other.ID;
// 	vertexCount = other.vertexCount;
// 	other.ID = 0;
// 	other.vertexCount = 0;
// }
void Mesh::newFrom(Mesh &&other)
{
	ID = other.ID;
    verticesCount = other.verticesCount;
	other.ID = 0;
	other.verticesCount = 0;
}

void Mesh::copyFrom(std::unique_ptr<Mesh> other)
{
	empty = other->empty;
	ID = other->ID;
    verticesCount = other->verticesCount;
}

bool Mesh::isEmpty() { return empty; }

unsigned int Mesh::getID()
{
	return ID;
}

unsigned int Mesh::getVericesCount()
{
	return verticesCount;
}

Mesh::~Mesh()
{
	// std::cout << "Mesh DESTRUCTOR called" << std::endl;	
}

std::unique_ptr<Mesh> Mesh::newMesh(VAO *vao)
{
	return std::make_unique<Mesh>(false, vao->getID(), vao->getElementCount());	
	// Mesh *mesh = new Mesh(false, vao->getID(), vao->getElementCount());
	// return mesh;	
}

Mesh Mesh::emptyMesh()
{
	return Mesh(true, 0, 0);
}
