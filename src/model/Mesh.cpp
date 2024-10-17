#include "Mesh.h"
#include <iostream>



using namespace gen;


// Mesh::Mesh() {
// 	std::cout << "Mesh CONSTRUCTOR called" << std::endl;
// }

Mesh::Mesh(unsigned int ID, unsigned int verticesCount)
{
	// std::cout << "Mesh CONSTRUCTOR called" << std::endl;	
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
	ID = other->ID;
    verticesCount = other->verticesCount;
}

unsigned int Mesh::getID() { return ID; }

unsigned int Mesh::getVerticesCount() { return verticesCount; }

Mesh::~Mesh()
{
	// std::cout << "Mesh DESTRUCTOR called" << std::endl;	
}

std::unique_ptr<Mesh> Mesh::newMesh(VAO *vao)
{
	return std::make_unique<Mesh>(vao->getID(), vao->getElementCount());	
	// Mesh *mesh = new Mesh(false, vao->getID(), vao->getElementCount());
	// return mesh;	
}

Mesh Mesh::emptyMesh()
{
	return Mesh(0, 0);
}
