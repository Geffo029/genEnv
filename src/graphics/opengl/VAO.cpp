#include "VAO.h"
#include <GL/glew.h>
#include <iostream>
#include <ostream>



using namespace gen;


VAO::VAO(unsigned short verticesCount, float positions[], int positionDimension, 
		 unsigned short indicesCount, unsigned short indices[])
{
	glGenVertexArrays(1, &ID);
	this->verticesCount = verticesCount;
	this->indicesCount = indicesCount;

	bind(ID);

	addBuffer(positions, positionDimension, 0);
	addIndexBuffer(indices);

	unbind();
}

VAO::VAO(unsigned short verticesCount, float positions[], int positionDimension, float colors[], int colorDimension,
		 unsigned short indicesCount, unsigned short indices[])
{
	glGenVertexArrays(1, &ID);
	this->verticesCount = verticesCount;
	this->indicesCount = indicesCount;

	bind(ID);

	addBuffer(positions, positionDimension, 0);
	addBuffer(colors, colorDimension, 1);
	addIndexBuffer(indices);

	unbind();
}

VAO::VAO(obj::data data /*unsigned int positionCount, unsigned int positionDimension, float positions[], 
         unsigned int textureCount, unsigned int textureDimension, float textures[],
		 unsigned int normalCount, unsigned int normalDimension, float normals[],
		 unsigned int indexCount, unsigned short indices[]*/)
{
	verticesCount = data.vCount / data.vDimension;
	indicesCount = data.fCount / data.fDimension;

	// int nVertices = data.vCount / data.vSize;
	float positions[data.vCount];
	float tCoords[data.vtCount];
	// float normals[data.vnCount];
	unsigned short indices[indicesCount];

	for (int i = 0; i < indicesCount; i++) {
		unsigned short i_position = data.f[i*3] - 1;
		unsigned short i_tCoord = data.f[i*3+1] - 1;
		// unsigned short i_normal = data.f[i*3+2] - 1;
		indices[i] = i_position;
		unsigned short i_currentVertex = i_position;

		if (true) { /*TODO: controllare se le celle alla posizione i_currentVertex non siano gia' state riempite*/
			positions[i_currentVertex*3] = data.v[i_position*3];
			positions[i_currentVertex*3+1] = data.v[i_position*3+1];
			positions[i_currentVertex*3+2] = data.v[i_position*3+2];
			tCoords[i_currentVertex*2] = data.vt[i_tCoord*2];
			tCoords[i_currentVertex*2+1] = data.vt[i_tCoord*2+1];
			// normals[i_currentVertex*3] = data.vn[i_normal*3];
			// normals[i_currentVertex*3+1] = data.vn[i_normal*3+1];
			// normals[i_currentVertex*3+2] = data.vn[i_normal*3+2];
		}
	}

	glGenVertexArrays(1, &ID);

	bind(ID);

	addBuffer(positions, data.vDimension, 0);
	addBuffer(tCoords, data.vtDimension, 1);
	// addBuffer(normals, data.vnDimension, 2);
	addIndexBuffer(indices);

	unbind();
}

unsigned int VAO::getID()
{
	return ID;
}

unsigned short VAO::getElementCount() {
	return indicesCount;
}

void VAO::bind(VAO vao) {
	glBindVertexArray(vao.ID);
}

void VAO::bind(GLuint ID) {
	glBindVertexArray(ID);
}

void VAO::unbind() {
	glBindVertexArray(0);
}

void VAO::addBuffer(float data[], GLint dataDimension, GLuint attributeIndex) {
	GLuint VBO; 
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(data[0])*dataDimension*verticesCount, data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(attributeIndex);
	glVertexAttribPointer(attributeIndex, dataDimension, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VAO::addIndexBuffer(unsigned short indices[]) {
	GLuint indexBuffer;
	glGenBuffers(1, &indexBuffer);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0])*indicesCount, indices, GL_STATIC_DRAW);
}
