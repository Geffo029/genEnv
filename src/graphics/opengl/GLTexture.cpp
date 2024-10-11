#include "GLTexture.h"
#include <GL/glew.h>



using namespace gen;


GLTexture::GLTexture(image::data data)
{
	glGenTextures(1, &ID);
	
	bind(ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, data.width, data.height, 0, GL_RGB, GL_UNSIGNED_BYTE, data.pixels);
	
	glGenerateMipmap(GL_TEXTURE_2D);

	unbind();
}

unsigned int GLTexture::getID() { return ID; }

void GLTexture::bind(GLTexture texure)
{
	glBindTexture(GL_TEXTURE_2D, texure.ID);
}

void GLTexture::bind(GLuint ID)
{
	glBindTexture(GL_TEXTURE_2D, ID);
}

void GLTexture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}