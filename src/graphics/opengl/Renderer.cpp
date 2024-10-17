#include "Renderer.h"
#include "Math.h"
#include "ShaderProgram.h"
#include "GLTexture.h"
#include "VAO.h"
#include "Model.h"
#include "Texture.h"
#include <GL/glew.h>
#include <iostream>



using namespace gen;


Renderer::Renderer()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1f, 0.2f, 0.3f, 1);
}

void Renderer::testTriangle()
{
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.5, -0.5);
	glVertex2f(0.5, -0.5);
	glVertex2f(0, 0.5);
	glEnd();
}

void Renderer::setShader(ShaderProgram *shader)
{
	this->shader = shader;
	shader->use();
}

void Renderer::render(VAO *vao)
{
	Mat4 MPVMatrix = Mat4::projectionMatrix_perspective(0.01f, 100.0f, 70.0f, 1280.0f/720);
	shader->setUniform("MVPMatrix", MPVMatrix);
	VAO::bind(vao->getID());
	glDrawElements(GL_TRIANGLES, vao->getElementCount(), GL_UNSIGNED_SHORT, 0);
	VAO::unbind();
}

void Renderer::render(Model *model)
{
	Mat4 projectionMatrix = Mat4::projectionMatrix_perspective(0.01f, 100.0f, 70.0f, 1280.0f/720);
	// std::cout << "Projection matrix: " << std::endl; projectionMatrix.print();
	Mat4 viewMatrix = Mat4::viewMatrix(new float[] {0,0,-1}, new float[] {0,0,0});
	// std::cout << "View matrix: " << std::endl; viewMatrix.print();
	Mat4 modelMatrix = Mat4::modelMatrix(model->getTransform()->getLocation(), model->getTransform()->getRotation(), model->getTransform()->getScale());
	// std::cout << "Model matrix: " << std::endl; modelMatrix.print();

	Mat4 MVPMatrix = Mat4::multiply(projectionMatrix, Mat4::multiply(viewMatrix, modelMatrix) );
	// std::cout << "MVP matrix: " << std::endl; MVPMatrix.print();
	shader->setUniform("MVPMatrix", MVPMatrix);
	
	VAO::bind(model->getMesh()->getID());
	glDrawElements(GL_TRIANGLES, model->getMesh()->getVericesCount(), GL_UNSIGNED_SHORT, 0);
	VAO::unbind();
}

void Renderer::render(Model models[], int count)
{
	Mat4 projectionMatrix = Mat4::projectionMatrix_perspective(0.01f, 100.0f, 70.0f, 1280.0f/720);
	Mat4 viewMatrix = Mat4::viewMatrix(new float[] {0,0,-1}, new float[] {0,0,0});
	for (int i = 0; i < count; i++) {
		Model *model = &models[i];
		if (model->isEmpty()) continue;
		Mat4 modelMatrix = Mat4::modelMatrix(model->getTransform()->getLocation(), model->getTransform()->getRotation(), model->getTransform()->getScale());
		Mat4 MVPMatrix = Mat4::multiply(projectionMatrix, Mat4::multiply(viewMatrix, modelMatrix) );
		shader->setUniform("MVPMatrix", MVPMatrix);
		
		if (!model->getMesh()->isEmpty()) {
			VAO::bind(model->getMesh()->getID());
			if (!model->getTexture()->isEmpty()) GLTexture::bind(model->getTexture()->getID());
			
			glDrawElements(GL_TRIANGLES, model->getMesh()->getVericesCount(), GL_UNSIGNED_SHORT, 0);
			
			GLTexture::unbind();
			VAO::unbind();
		}
	}
}

void Renderer::renderGui(Model guiElements[], int count)
{
	for (int i = 0; i < count; i++) {
		Model *model = &guiElements[i];

		Mat4 modelMatrix = Mat4::modelMatrix(model->getTransform()->getLocation(), model->getTransform()->getRotation(), model->getTransform()->getScale());
		shader->setUniform("ModelMatrix", modelMatrix);
		if (!model->getMesh()->isEmpty()) {
			VAO::bind(model->getMesh()->getID());
			if (!model->getTexture()->isEmpty()) GLTexture::bind(model->getTexture()->getID());
			
			glDrawElements(GL_TRIANGLES, model->getMesh()->getVericesCount(), GL_UNSIGNED_SHORT, 0);
			
			GLTexture::unbind();
			VAO::unbind();
		}
	}
}

void Renderer::clearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::wireframeMode(bool enable)
{
	if (enable) 
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else 
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
